if __name__ == "__main__":
	import numpy as np

	frame = np.random.randint(1, 10, size = (5, 5)) # Assuming input to be 5 frames of size 1x5.
	shape = frame.shape
	print("frame: \n", frame, "\n\n")
	frame = np.diff(frame, axis=0)
	#print("Difference matrix: \n", frame)
	final = np.zeros((1,25)) # 25 is the number of elements in the frame matrix passed.
							 # Base matrix for final matrix initialized with zeroes with the same shape as expected of final matrix.
	for x in range(5):
		i = int(1)
		zeros = np.zeros((x+1,5)) # Padding with zeroes to maintain initial dimension of frame matrix.
		cum_sum_mat = np.cumsum(frame, axis=0) 
		cum_sum_mat = np.vstack((cum_sum_mat, zeros))
		#print("Cumulative sum matrix: \n", cum_sum_mat)
		frame_flattened = cum_sum_mat.flatten()
		#print("Frame flattened: \n", frame_flattened)
		final = np.vstack((final,frame_flattened))
		#print("final matrix \n", final)
		frame = frame[i:,:]
		i = i+1
		#print("frame after deletion: ", frame)
		#if(frame.any()):
		#	frame = np.delete(frame, (0), axis=0)
		#print("frame after deletion: ", frame)
	final = final[1:,:]
	print("final: \n", final)