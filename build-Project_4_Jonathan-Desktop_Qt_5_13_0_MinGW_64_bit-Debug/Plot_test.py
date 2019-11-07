from Py_Functions import readarrays, readmatrices
from numpy import array, zeros, log10, linspace
import matplotlib.pyplot as plt
'''
T = array([1.0,2.4])
E = zeros(shape=(8,2))
M = zeros(shape=(8,2))
Mabs = zeros(shape=(8,2))
Cv = zeros(shape=(8,2))
X = zeros(shape=(8,2))
AC = zeros(shape=(8,2))

N = [10**i for i in range(1,9)]

for i in range(8):
	A = readarrays("Results_4c_order_N_%s_L_20.txt" % N[i])[0]
	E[i][0] = A[1][0]
	E[i][1] = A[1][1]
	M[i][0] = A[2][0]
	M[i][1] = A[2][1]
	Mabs[i][0] = A[3][0]
	Mabs[i][1] = A[3][1]
	AC[i][0] = A[6][0]
	AC[i][1] = A[6][1]

#print AC

plt.plot(log10(N),[E[i][1] for i in range(8)])

Energies = readarrays("Test_energies.txt")[0][0]
print len(Energies)
print "---"
N = linspace(10,10**7,len(Energies))
print len(N)
print "---"
plt.figure()
#plt.plot(log10(N),Energies)

Energy2 = [Energies[i] for i in range(10**4,10**7-100)]
num_bins = int(abs(max(Energy2)/4.))
print num_bins
n, bins, patches = plt.hist(Energy2,num_bins)

plt.show()
'''

A = readmatrices("Test_stuff_N_10000_L_20.txt")[0]
print A
