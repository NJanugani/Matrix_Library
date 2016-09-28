import cProfile         as cpr
import pstats           as pst
import typing           as chk
import math             as mth

import io


class profile(object):
	"""

	"""
	def __init__(self, suppress : bool = False):
		"""

		:param suppress:
		"""
		self.__suppress__ = suppress

	def __call__(self, func : chk.Callable):
		"""

		:param func:
		:return:
		"""

		def worker(*args : chk.List[chk.Any], **kwargs : chk.Dict[chk.Any, chk.Any]):

			if self.__suppress__:
				retVal = func(*args, **kwargs)
			else:
				pr = cpr.Profile()
				pr.enable()
				retVal = func(*args, **kwargs)
				pr.disable()
				s = io.StringIO()
				sortby = 'cumulative'
				ps = pst.Stats(pr, stream = s).sort_stats(sortby)
				ps.print_stats()
				print("Function {} :\n {}".format(func.__name__, s.getvalue()))
			return retVal
		return worker

def isPowerOfTwo(number : int) -> bool:
	"""

	:param number:
	:return:
	"""
	return ((number & (number - 1)) == 0) and number != 0


def lowestBit(number : int) -> int:
	"""

	:param number:
	:return:
	"""
	low = (number & -number)
	lowBit = -1
	while (low):
		low >>= 1
		lowBit += 1
	return (lowBit)

def highestBit(number : int) -> int:
	"""

	:param number:
	:return:
	"""
	return number.bit_length() - 1

def radius(mask : int) -> int:
	"""
	Returns the count of the ones in the specified bitmask
	:param mask: The encoded bit mask
	:return:
	"""
	mask = int(mask)
	if bin(mask).count('1') == 1:
		return 1
	return highestBit(mask) - lowestBit(mask) + 1

def countOf(mask : int) -> int:
	"""

	:param mask:
	:return:
	"""
	mask = int(mask)
	count = 0
	while (mask):
		mask &= mask - 1
		count += 1
	return (count)

if __name__ == "__main__":

	import numpy        as npy
	import scipy.sparse as spy

	value = (2).to_bytes(8, byteorder = 'big') + (1).to_bytes(8, byteorder = 'big')
	print("Value: ", value)

	kind  = npy.dtype({'names': ['loword', 'hiword'], 'formats': [npy.uint64, npy.uint64]})

	test =\
	(
		npy.array
		(
			[
				(1).to_bytes(8, byteorder = 'big') + (2).to_bytes(8, byteorder = 'big')
			],
			kind
		)
	)

	print\
	(
			"Values: \n \t Hiword: ", int.from_bytes(test[0]['hiword'], byteorder = 'big'),
			"\n\t Loword: ", int.from_bytes(test[0]['loword'], byteorder = 'big')
	)

	mask = 5
	print("Radius: {} for mask {} ({}) with high bit {} and low bit {}".format(radius(mask), mask, bin(mask), highestBit(mask), lowestBit(mask)))
	print("Count: ", countOf(mask))

	one             = (1).to_bytes(8, byteorder = 'little')
	onetwoseven     = (0).to_bytes(8, byteorder = 'little') + (1).to_bytes(8, byteorder = 'little')
	three           = (3).to_bytes(8, byteorder = 'little')
	four            = (4).to_bytes(8, byteorder = 'little')
	sixtyseven      = (0).to_bytes(8, byteorder = 'little') + (4).to_bytes(8, byteorder = 'little')

	data            = npy.asarray([one, onetwoseven, three, four, sixtyseven], dtype = kind)

	sparse = spy.coo_matrix(([1., 0 + 1j, 3, 0 + 4j, 5], ([0,0,0,0,0], [0,1,2,3,4])), shape = (1, 10000), dtype = npy.complex128)

	sparse2 = spy.coo_matrix((data, ([0, 0, 0, 0, 0], [0, 1, 2, 3, 4])), shape = (1, 10000), dtype = kind)
	result = sparse2.data['loword'] > 1
	print(sparse2, "\n", sparse2.col[result])