from Py_Functions import readarrays
from numpy import array, zeros, log10, linspace
import matplotlib.pyplot as plt

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

Energies = readarrays("Test_energies.txt")[0][0]
print len(Energies)
print "---"
N = linspace(10,10**7,len(Energies))
print len(N)
print "---"
plt.plot(log10(N),Energies)


#plt.plot(log10(N),[E[i][1] for i in range(8)])
plt.show()
