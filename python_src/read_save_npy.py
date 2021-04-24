import scipy.io
import numpy as np

mat = scipy.io.loadmat('data.mat')

#FFS_stack = mat['FFS_stack']

#np.save("FFS_stack", mat['FFS_stack'])
#np.save("pFIS_stack", mat['pFIS_stack'])


FFS_stack = []
#data = np.load("../build/arr1.npy", allow_pickle=True)
#data = np.load("FFS_stack.npy", allow_pickle=True)
#for i in range(0, mat["FFS_stack"].shape[0]):
FFS_stack.append(np.array2string(mat["FFS_stack"][0][0][0]))

FFS_stack = np.array(FFS_stack)
print(FFS_stack)

np.save("FFS_stack", FFS_stack)

#print(data.shape)
#print(data.files)
#for item in data.files:
#    print(item)
#    print(data[item])
