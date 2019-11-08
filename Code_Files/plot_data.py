from numpy import *
from matplotlib.pyplot import *
import Py_Functions
# 1 The most likely state
'''
#Initialize
n = array([pow(10,i) for i in range(1,9)])
T = array([1.0,2.4])
E = zeros((len(n),2))
M = zeros((len(n),2))
Mabs = zeros((len(n),2))
Cv = zeros((len(n),2))
X = zeros((len(n),2))
AC = zeros((len(n),2))
E_ran = zeros((len(n),2))
M_ran = zeros((len(n),2))
Mabs_ran = zeros((len(n),2))
Cv_ran = zeros((len(n),2))
X_ran = zeros((len(n),2))
AC_ran = zeros((len(n),2))

# Read from files
for i in range(len(n)):
    A = Py_Functions.readmatrices("Results_4e_N_%s_L_20.txt" % n[i])[0]
    A_ran = Py_Functions.readmatrices("Results_4e_N_%s_L_20.txt" % n[i])[0]
    E[i][0] = A[1][0]
    E[i][1] = A[1][1]
    M[i][0] = A[2][0]
    M[i][1] = A[2][1]
    Mabs[i][0] = A[3][0]
    Mabs[i][1] = A[3][1]
    AC[i][0] = A[6][0]
    AC[i][1] = A[6][1]
    E_ran[i][0] = A_ran[1][0]
    E_ran[i][1] = A_ran[1][1]
    M_ran[i][0] = A_ran[2][0]
    M_ran[i][1] = A_ran[2][1]
    Mabs_ran[i][0] = A_ran[3][0]
    Mabs_ran[i][1] = A_ran[3][1]
    AC_ran[i][0] = A_ran[6][0]
    AC_ran[i][1] = A_ran[6][1]


fig1, (ax1, ax2, ax3, ax4) = subplots(4, 1, sharex=True)
line1 = ax1.plot(log10(n),E[:,0],label="T=1, Ordered")
ax1.text(1,1, "T=1.0, Ordered", horizontalalignment='right', verticalalignment='bottom', transform=ax1.transAxes)
ax1.set_ylabel("$\\langle E\\rangle$")
line2 = ax2.plot(log10(n),E_ran[:,0],label="T=1, Unordered")
ax2.text(1,1, "T=1.0, Unordered", horizontalalignment='right', verticalalignment='bottom', transform=ax2.transAxes)
ax2.set_ylabel("$\\langle E\\rangle$")
line3 = ax3.plot(log10(n),E[:,1],label="T=2.4, Ordered")
ax3.text(1,1, "T=2.4, Ordered", horizontalalignment='right', verticalalignment='bottom', transform=ax3.transAxes)
ax3.set_ylabel("$\\langle E\\rangle$")
line4 = ax4.plot(log10(n),E_ran[:,1],label="T=2.4, Unordered")
ax4.text(1,1, "T=2.4, Unordered", horizontalalignment='right', verticalalignment='bottom', transform=ax4.transAxes)
ax4.set_ylabel("$\\langle E\\rangle$")
xlabel("# of MC-cycles (n)")
#savefig("../Figures/E_mean_L20.pdf")

fig2, (ax1, ax2, ax3, ax4) = subplots(4, 1, sharex=True)
line1 = ax1.plot(log10(n),M[:,0],label="T=1, Ordered")
ax1.text(1,1, "T=1.0, Ordered", horizontalalignment='right', verticalalignment='bottom', transform=ax1.transAxes)
ax1.set_ylabel("$\\langle M\\rangle$")
line2 = ax2.plot(log10(n),M_ran[:,0],label="T=1, Unordered")
ax2.text(1,1, "T=1.0, Unordered", horizontalalignment='right', verticalalignment='bottom', transform=ax2.transAxes)
ax2.set_ylabel("$\\langle M\\rangle$")
line3 = ax3.plot(log10(n),M[:,1],label="T=2.4, Ordered")
ax3.text(1,1, "T=2.4, Ordered", horizontalalignment='right', verticalalignment='bottom', transform=ax3.transAxes)
ax3.set_ylabel("$\\langle M\\rangle$")
line4 = ax4.plot(log10(n),M_ran[:,1],label="T=2.4, Unordered")
ax4.text(1,1, "T=2.4, Unordered", horizontalalignment='right', verticalalignment='bottom', transform=ax4.transAxes)
ax4.set_ylabel("$\\langle M\\rangle$")
xlabel("# of MC-cycles ($log_{10}(n)$)")
#savefig("../Figures/M_mean_L20.pdf")


# 2 Probability distribution
fig3, (ax1, ax2, ax3, ax4) = subplots(4, 1, sharex=True)
line1 = ax1.hist(E[:,0], int((max(E[:,0]-min(E[:,0])))/4), normed=True, facecolor='g', alpha=0.75)
ax1.set_ylabel("$\\rho_{\\langle E\\rangle}$")
line2 = ax2.hist(E_ran[:,0], 50, normed=True, facecolor='g', alpha=0.75)
ax2.set_ylabel("$\\rho_{\\langle E\\rangle}$")
line3 = ax3.hist(E[:,1], 50, normed=True, facecolor='g', alpha=0.75)
ax3.set_ylabel("$\\rho_{\\langle E\\rangle}$")
line4 = ax4.hist(E_ran[:,1], 50, normed=True, facecolor='g', alpha=0.75)
ax4.set_ylabel("$\\rho_{\\langle E\\rangle}$")
xlabel("$\\langle E\\rangle$")
#savefig("../Figures/E_mean_L20_probability.pdf")


fig4, (ax1, ax2, ax3, ax4) = subplots(4, 1, sharex=True)
line1 = ax1.hist(M_mean_L20_T1_ord, 50, normed=True, facecolor='g', alpha=0.75)
ax1.set_ylabel("$\\rho_{\\langle M\\rangle}$")
line2 = ax2.hist(M_mean_L20_T1_unord, 50, normed=True, facecolor='g', alpha=0.75)
ax2.set_ylabel("$\\rho_{\\langle M\\rangle}$")
line3 = ax3.hist(M_mean_L20_T24_ord, 50, normed=True, facecolor='g', alpha=0.75)
ax3.set_ylabel("$\\rho_{\\langle M\\rangle}$")
line4 = ax4.hist(M_mean_L20_T24_unord, 50, normed=True, facecolor='g', alpha=0.75)
ax4.set_ylabel("$\\rho_{\\langle M\\rangle}$")
xlabel("$\\langle M\\rangle$")
#savefig("../Figures/M_mean_L20_probability.pdf")
'''

# 3 Phase transition and critical temperature

# Read from files
n = 1000000
A_40 = Py_Functions.readmatrices("Results_4e_N_%s_L_40.txt" % n)[0]
A_60 = Py_Functions.readmatrices("Results_4e_N_%s_L_60.txt" % n)[0]
A_80 = Py_Functions.readmatrices("Results_4e_N_%s_L_80.txt" % n)[0]
A_100 = Py_Functions.readmatrices("Results_4e_N_%s_L_100.txt" % n)[0]

lst = [A_40,A_60,A_80,A_100]
L = [40,60,80,100]

T = [i for i in A_40[0]]
E = zeros(len(A_40[0]))

size = 0
for i in lst: #Loop over all different L calculations
    index = 0
    for j in i[1]: # Loop over Energies per temperature in given LxL system
        #print(j[-1]) #Read last value
        E[index] = j[-1]
        index += 1
    print(E)
    plot(T,E,label="L = "+str(L[size]))
    #for j in i[2]: # Loop over Magnetizations per temperature
    size += 1
xlabel("Temperature (T)")
ylabel("$\\langle E\\rangle (T)$")
show()
