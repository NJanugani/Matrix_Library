import typing as chk
import io
import os
import glob
import time                         as tme

def insensitivize(pattern : str):
	'''

	:param pattern:
	:return:
	'''
	def swizzle(lex : str) -> str:
		if lex.isalpha():
			return '[{}{}]'.format(lex.lower(), lex.upper())
		else:
			return lex

	return ''.join(map(swizzle, pattern))

class Corporator(object):
	'''

	'''

	def __init__(self, name : str, root : str = os.path.join(os.path.dirname(os.path.dirname(__file__)), 'codenes'), **filters : chk.Dict):
		'''

		:param name:
		:param root:
		:param filters:
		'''
		self.__root__ = os.path.join(root, name)
		if not os.path.exists(self.__root__):
			raise NotADirectoryError("{} is not a valid repository!".format(name))

		names           = '*'
		if 'names' in filters:
			names       = insensitivize(filters['names'])
		self.__path__   = os.path.join(self.__root__, '**','{}.cor'.format(names))

		self.__cutoff__ = filters.get('after', 0)

	@property
	def Root(self) -> str:
		return self.__root__

	def __len__(self) -> int:
		return sum(1 for f in glob.iglob(self.__path__, recursive = True) if os.path.getmtime(f) > self.__cutoff__)



	def __contains__(self, item : str ) -> bool:
		'''
		:param item:
		:return:
		'''
		if item.endswith('.cor'):
			item = item.rsplit('.', maxsplit = 1)[0]
		item    = insensitivize(item)
		target  = '{}.cor'.format(item)
		query   = os.path.join(self.__root__, '**', target)
		return any([1 for f in glob.iglob(query, recursive = True) if os.path.getmtime(f) > self.__cutoff__])


	def __getitem__(self, item : str) -> str:
		'''

		:param item:
		:return:
		'''

		if item.endswith('.cor'):
			item = item.rsplit('.', maxsplit = 1)[0]
		item = insensitivize(item)
		target = '{}.cor'.format(item)
		query   = os.path.join(self.__root__, '**', target)
		retVal  =  [f for f in glob.iglob(query, recursive = True) if os.path.getmtime(f) > self.__cutoff__]
		if not len(retVal):
			raise KeyError("{} not present in current corpora.".format(item))
		return retVal

	def __iter__(self) -> io.IOBase:
		'''
		:return:
		'''
		for file in glob.iglob(self.__path__, recursive = True):
			if os.path.getmtime(file) > self.__cutoff__:
				with open(file, 'r') as corpus:
					yield (file, corpus)








