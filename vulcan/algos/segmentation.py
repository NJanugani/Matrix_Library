import typing              as chk
import scipy.sparse        as spy
import scipy.special       as scp
import numpy               as npy
import tempfile            as tpf
import os
import joblib              as jbl
import sys

import algos.corpus        as cpr
import ordered_set         as ost
import collections         as col
import pprint              as ppt
import itertools           as itr
import string              as stg

import utils               as utl
import tabulate            as tbl
import warnings            as wrn
import numpy_indexed       as npi
import functools           as ftl
import operator            as opr

# noinspection PyAttributeOutsideInit
class Segmentor(object):
	"""

	"""

	MAX_ROWS           = 1
	MAX_COLS           = 1000000
	MAX_LENGTH         = 64
	DTYPE              = npy.float32
	SELECTION_CUTOFF   = 0.5
	EPSILON            = 1e-05

	__slots__ =\
	(
		'__vocabulary__',
		'__index__',
		'__encodings__',
		'__spans__',
		'__vocab_locus__',
		'__enc_locus__',
		'__filters__',
		'__idx_locus__',
		'__changeset__',
		'__dirty__'
	)

	def __init__(self, name: str,  locus : str = tpf.gettempdir()):
		"""

		:param name:
		:param locus:
		"""
		self.__vocab_locus__    = os.path.join(locus, '-'.join((name, 'vocab.dat')))
		self.__filters__        = os.path.join(locus, '-'.join((name, 'filters.dat')))
		self.__idx_locus__      = os.path.join(locus, '-'.join((name, 'idx.dat')))
		encodeLocus             = os.path.join(locus, 'encodings', name)
		if not os.path.exists(encodeLocus):
			os.makedirs(encodeLocus)
		self.__enc_locus__      = os.path.join(locus, 'encodings', name, 'encoding')
		self.__dirty__          = False

		if os.path.exists(self.__enc_locus__):
			self.__encodings__, self.__spans__  = jbl.load(self.__enc_locus__, 'r+')
		else:
			self.__encodings__      = {}     #type: chk.Dict[str, spy.csr_matrix]
			self.__spans__          = spy.csr_matrix((self.MAX_ROWS, self.MAX_COLS), dtype = npy.uint32)






	def loadFrom(self, source: str = os.path.join(os.path.dirname(os.path.dirname(__file__))), **options: chk.Dict[str, chk.Any]) -> 'Segmentor':
		"""
		Loads the vocabulary from disk and populates the __vocabulary__ slot with a list
		:param source:       either file or directory.
		                    If directory, reads all files in subdirectories matching the .cor extensions.
		:param options   :
			reload       : Forces reload of vocabulary
		:return:            Encoder
		"""
		translator = str.maketrans('', '', stg.punctuation)

		filters = '+'
		if os.path.exists(self.__filters__):
			filters = jbl.load(self.__filters__)

		newFilters = '-'
		if 'names' in options:
			newFilters = options['names']
			jbl.dump(newFilters, self.__filters__)

		reload = True if newFilters != filters else options.get('reload', False)

		if os.path.exists(self.__vocab_locus__) and not reload:
			vocabulary = cpr.Corporator(source, after = int(os.path.getmtime(self.__vocab_locus__)), **options)
		else:
			vocabulary = cpr.Corporator(source, **options)

		genVocab    =  (line.rstrip().translate(translator) for f, c in vocabulary for line in c)
		# noinspection PyTypeChecker
		self.load(genVocab)
		return self

	def load(self, vocabulary: chk.Iterable[str]) -> 'Segmentor':
		"""
		Loads the vocabulary from the provided list
		:param vocabulary:  The list of words in the vocabulary
		:return:            Segmentor
		"""

		self.__changeset__ = ost.OrderedSet(vocabulary)
		if os.path.exists(self.__vocab_locus__):
			self.__vocabulary__ = jbl.load(self.__vocab_locus__, 'r+')
			self.__vocabulary__ |= self.__changeset__
			jbl.dump(self.__vocabulary__, self.__vocab_locus__)
			if not os.path.exists(self.__idx_locus__):
				self.__changeset__ = self.__vocabulary__


		else:
			self.__vocabulary__ = self.__changeset__
			jbl.dump(self.__vocabulary__, self.__vocab_locus__)

		return self




	def index(self) -> 'Segmentor':
		"""

		:return:            Segmentor
		"""



		def tokenize(word):
			"""

			:param word:
			:return:
			"""

			def findLocii(word, character):
				hits = []
				idxLast = -1
				while True:
					try:
						idxLast = word.index(character, idxLast + 1)
					except ValueError:
						break
					else:
						hits.append(idxLast + 1)
				return hits


			if len(word) > self.MAX_LENGTH:
				print("Word {} has {} letters which exceeds the max letter limit {}".format(word, len(word), self.MAX_LENGTH))
				yield

			word    = word.lower()

			weight  = sum([pow(w, 2) for w in range(1, len(word) + 1)])
			counter = col.Counter(word)
			locii   = {letter : npy.asarray(findLocii(word, letter)) for letter in list(word)}
			for letter, value in locii.items():

				if npy.alen(value) > 1:
					weights = npy.ones_like(value)
					weights[0]  = npy.nan_to_num((value[-1] - value[ 1 : -2].sum())/ value[0])
					weights[-1] *= -1
					weights     += value

				else:
					weights = value[:]


				locii[letter]   = (value, weights)

			letters             =\
			[
				(
                   self.__vocabulary__.index(word),
                   letter,
                   (
                       # locii[letter][0][npy.argwhere(locii[letter][0] == (idx + 1))[0]] *
                       locii[letter][1][npy.argwhere(locii[letter][0] == (idx + 1))[0]]
                   )[0] / weight
				)
			    for idx, letter in enumerate(list(word))
			]

			yield from letters


		if os.path.exists(self.__idx_locus__):
			self.__index__  = jbl.load(self.__idx_locus__, 'r+')
		else:
			self.__index__  = col.defaultdict(set)


		indexGenerator      = (tokenize(word) for word in self.__changeset__)
		for doc, symbol, idx in itr.chain(*indexGenerator):
			self.__index__[symbol].add((doc, idx, len(self.__changeset__[doc])))
			self.__dirty__  = True

		if self.__dirty__:
			jbl.dump(self.__index__, self.__idx_locus__)

		return self

	def encode(self):

		if self.__dirty__:

			for key, values in self.__index__.items():
				data                    =\
				(
					npy.array
					(
						[idx for _, idx, _ in values],
						dtype = self.DTYPE
					)
				)
				spans = \
				(
					npy.array
					(
						[span for _, _, span in values],
						dtype = npy.uint32
					)
				)

				rows                    = npy.zeros(len(values))
				cols                    = npy.array([int(doc) for doc, _, _ in values])
				encoding                = spy.csr_matrix((data, (rows, cols)), shape = (self.MAX_ROWS, self.MAX_COLS))
				self.__encodings__[key] = encoding
				widths                  = self.__spans__.todok()
				widths[rows, cols]      = spans
				self.__spans__          = widths.tocsr().asfptype()




			jbl.dump((self.__encodings__, self.__spans__), self.__enc_locus__)

		return self

	@utl.profile(suppress = True)
	def segment(self, sequence: str) -> chk.Generator[chk.Tuple[float, chk.Sequence[str]], None, None]:
		"""

		:param sequence:    The query string
		:return:            A generator that emits possible segments prefixed by their score.
		"""



		def encode(locii : npy.ndarray, shape : chk.Tuple[int, int], mask : npy.ndarray = None, scores : npy.ndarray = None) -> npy.ndarray:
			"""

			:param locii:
			:param shape:
			:param mask:
			:param scores:
			:return:
			"""
			rows, cols                          = shape
			out                                 = locii[:]
			out[:, 0]                           = npy.floor(locii[:, 0] / rows)
			out[:, 1]                           = locii[:, 1]  if mask is  None else decode(mask, locii[:, 1])


			spans                               = locii[:, 0] % rows + 1 - out[:, 0]
			if scores is not None:
				with wrn.catch_warnings():
					wrn.simplefilter('ignore')
					normedScores                = scores / scores.sum()
				normedScores                    = normedScores.reshape(out.shape[0], 1)
			return \
			(
				npy.hstack((out, spans.reshape(out.shape[0], 1)))
				if scores is  None
				else
				npy.hstack((out, spans.reshape(out.shape[0], 1), normedScores))
			)

		def decode(mask : npy.ndarray, locus : int or npy.ndarray) -> int or npy.ndarray:
			"""

			:param mask:
			:param locus:
			:return:
			"""
			codes = npy.argwhere(mask).ravel()
			if isinstance(locus, npy.ndarray):

				def decoder(value, relevance):
					return codes[value]
				vectorizer  = npy.vectorize(decoder, otypes = [npy.int32], excluded = ['relevance'])
				retVal      = vectorizer(locus, relevance = mask )
				return retVal

			return codes[locus]

		inverts  =\
		[
			self.__encodings__.get(symbol, spy.csr_matrix((self.MAX_ROWS, self.MAX_COLS), dtype = self.DTYPE))
			for symbol in list(sequence)
		]

		idxInverted         = spy.vstack(inverts, format = 'coo')
		indicators          = npy.asarray(npi.group_by(idxInverted.col, idxInverted.data, lambda vals: npy.unique(vals).sum()))[:, 1]
		spans               = self.__spans__.tocoo()
		normedSpans         = spy.coo_matrix((2 * (spans.data + 1) / 3, (spans.row, spans.col)), spans.shape)
		normedCutoffs       = spy.coo_matrix((indicators, (spans.row, spans.col)), spans.shape)
		thresholds          = normedSpans.multiply(normedCutoffs)
		cutoffs             = thresholds.data
		relevants           = cutoffs > self.SELECTION_CUTOFF
		idxRelevants        = npy.unique(npy.where(relevants)[0])

		# print("Relevants:\n", [self.__vocabulary__[idx] for idx in idxRelevants])

		significants        = idxInverted.tocsr()[:, idxRelevants]
		ones                = npy.ones((significants.shape[0], significants.shape[0]), npy.float32)

		spanner             = npy.tile(npy.arange(1, significants.shape[0] + 1), (idxInverted.shape[0], 1))
		multipliers         = npy.tile(npy.tril(ones) * spanner, (idxInverted.shape[0], 1))

		for diag in range(significants.shape[0]):

			baseline         = significants.shape[0] * diag
			multipliers[baseline: baseline + significants.shape[0], : ]\
							-= diag

		multipliers[multipliers < 0] = 0.

		trail              = npy.abs((multipliers * significants) - 1.).astype(npy.float32)

		check              = trail[:]
		check[check < self.EPSILON] = 0.
		print(tbl.tabulate(check, headers = [self.__vocabulary__[idx] for idx in idxRelevants], tablefmt = 'fancy_grid', showindex = True))

		indices            = npy.unravel_index(trail.argsort(axis = None), trail.shape)
		cutoff             = trail[indices] < self.EPSILON
		fRows, fCols       = indices[0][cutoff], indices[1][cutoff]
		fWeights           = trail[fRows, fCols]
		focii              = npy.hstack((npy.asarray(fRows).reshape(-1, 1), npy.asarray(fCols).reshape(-1, 1)))
		checkCandidates    = encode(focii, significants.shape, relevants, fWeights)

		candidates         = \
		(
			npy.rec.fromarrays
			(
				(
					checkCandidates[:, 0],
					[len(self.__vocabulary__[idx]) for idx in checkCandidates[:, 1].astype(npy.uint32)],
					checkCandidates[:, 2],
					checkCandidates[:, 3],
					[self.__vocabulary__[idx] for idx in checkCandidates[:, 1].astype(npy.uint32)]

				),
				dtype =
				npy.dtype
				(
					[
						('Start',       'uint32'),
						('ExpSpan',     'uint32'),
						('ActualSpan', 'uint32'),
						('Score',       'float32'),
						('word',        'object')]
				)
			)
		)


		#
		# with wrn.catch_warnings():
		# 	wrn.simplefilter('ignore')
		# 	spans          = npy.where(delta == 0., 1., npy.reciprocal(delta))
		#

		#
		# sortIdxs    = npy.lexsort((candidates['doc'], candidates['end'], candidates['start'], -candidates['score']))
		# candidates  =  candidates[sortIdxs]
		#


		return candidates


if __name__     == "__main__":

	query = 'drawaredcircle'
	print("Query: ", query)
	segments    =\
	(
		Segmentor('test', '/tmp')
		.loadFrom(names = 'test*')
		.index()
		.encode()
		.segment(query)

	)



	# print(tbl.tabulate(segments, headers = segments.dtype.names))
