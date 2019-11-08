from numpy import *
from matplotlib.pyplot import *
from numba import jit

@jit
def plotPhaseTransition(lst,temp):
    L = [40,60,80,100]

    T = temp
    E = zeros(len(lst[0][0]))
    M = zeros(len(lst[0][0]))
    Cv = zeros(len(lst[0][0]))
    X = zeros(len(lst[0][0]))

    size = 0
    for i in lst: #Loop over all different L calculations
        print(size)
        index = 0
        for j in i[1]: # Loop over Energies per temperature in given LxL system
            E[index] = j[-1]
            index += 1
        figure(1)
        plot(T,E,label="L = "+str(L[size]))
        index = 0
        for j in i[2]: # Loop over Magnetizations per temperature
            M[index] = j[-1]
            index += 1
        figure(2)
        plot(T,M,label="L = "+str(L[size]))
        size += 1
    figure(1)
    legend()
    xlabel("Temperature (T)")
    ylabel("$\\langle E\\rangle (T)$")
    savefig("E_of_T.pdf")
    figure(2)
    legend()
    xlabel("Temperature (T)")
    ylabel("$\\langle M\\rangle (T)$")
    savefig("M_of_T.pdf")
    show()
