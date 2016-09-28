import scipy.sparse        as spy
import numpy               as npy

def __option1__(cond : spy.spmatrix, ifClause : spy.spmatrix) -> spy.spmatrix:
	"""
	Choose from this matrix if condition evaluates to True
	:param cond:
	:param ifClause:
	:return:
	"""

	row, col, data = spy.find(cond) # effectively the coo format
	data = npy.ones(data.shape, dtype = ifClause.dtype)
	zs = spy.coo_matrix((data, (row, col)), shape = cond.shape)
	xx = ifClause.tocsr()[row, col][0]
	zs.data[:] = xx
	zs = zs.tocsr()
	zs.eliminate_zeros()
	return zs


def __option2__(cond: spy.spmatrix, thenClause: spy.spmatrix) -> spy.spmatrix:
	"""
	Choose from this matrix if condition not True
	:param cond:
	:param y:
	:return:
	"""
	row, col, data = spy.find(cond)
	zs = thenClause.copy().tolil()  # faster for this than the csr format
	zs[row, col] = 0
	zs = zs.tocsr()
	zs.eliminate_zeros()
	return zs


def where(cond: spy.spmatrix, ifClause: spy.spmatrix, thenClause: spy.spmatrix) -> spy.spmatrix:
	"""
	Emulates numpy.where for sparse matrices.
	:param cond:
	:param ifClause:
	:param thenClause:
	:return:
	"""
	ws1 = __option1__(cond, ifClause)
	ws2 = __option2__(cond, thenClause)
	ws = ws1 + ws2

	return ws

def unique(array : npy.ndarray) -> npy.ndarray:
	"""

	:param array:
	:return:
	"""
	check       = npy.ascontiguousarray(array)
	uniques     = npy.unique(check.view([('', check.dtype)] * check.shape[1]))
	return uniques.view(check.dtype).reshape((uniques.shape[0], check.shape[1]))