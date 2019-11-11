from numpy import *
from matplotlib.pyplot import *
from numba import jit

def plotMostLikelyState(lst,temp,n):

    T = temp
    h = int(n/len(lst[0][1][0])) #Step size
    n_values = linspace(h,n+h,int(n/h))
    fig1, axs1 = subplots(4,1,sharex=True,gridspec_kw={'hspace': 0})
    fig1.suptitle("Mean energy as function of MC-cycles.")
    fig2, axs2 = subplots(4,1,sharex=True,gridspec_kw={'hspace': 0})
    fig2.suptitle("Mean absolute magnetization as function of MC-cycles.")
    state = 1
    plt = 0
    for i in lst:
        initial = 0
        if state == 1:
            initial = "Ordered"
        else:
            initial = "Random"
        index = 0
        for j in i[1]:
            E_mean = j
            axs1[plt].plot(log10(n_values),E_mean,label="T="+str(T[index][0])+", "+initial)
            axs1[plt].set_ylabel("$\\langle E\\rangle$")
            axs1[plt].legend()
            plt += 1
            index += 1

        plt -= 2
        index = 0
        for j in i[3]:
            M_abs = j
            axs2[plt].plot(log10(n_values),M_abs,label="T="+str(T[index][0])+", "+initial)
            axs2[plt].set_ylabel("$\\langle |M|\\rangle$")
            axs2[plt].legend()
            plt += 1
            index += 1

        state += 1
    axs1[-1].set_xlabel("$log_{10}$(# of MC-cycles)")
    axs2[-1].set_xlabel("$log_{10}$(# of MC-cycles)")
    fig1.savefig("Most_Likely_State_E_mean_L_20.pdf")
    fig2.savefig("Most_Likely_State_M_abs_L_20.pdf")
    show()

def plotAcceptedConfigurations(lst,temp,n):

    T = temp
    h = int(n/len(lst[0][6][0])) #Step size
    n_values = linspace(h,n+h,int(n/h))
    fig1, axs1 = subplots(4,1,sharex=True,gridspec_kw={'hspace': 0})
    fig1.suptitle("Accepted configurations as function of MC-cycles.")
    state = 1
    plt = 0
    for i in lst:
        initial = 0
        if state == 1:
            initial = "Ordered"
        else:
            initial = "Random"
        index = 0
        for j in i[6]:
            Accepted_configs = j
            axs1[plt].loglog(n_values,Accepted_configs,label="T="+str(T[index][0])+", "+initial)
            axs1[plt].set_ylabel("Acc. conf.")
            axs1[plt].legend()
            plt += 1
            index += 1

        state += 1
    axs1[-1].set_xlabel("# of MC-cycles")
    fig1.savefig("Number_of_Accepted_Configs_L_20.pdf")
    show()


@jit
def plotProbabilityDistribution():
    return 0

@jit
def plotPhaseTransition(lst,temp,n):
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
        for j in i[3]: # Loop over Magnetizations per temperature
            M[index] = j[-1]
            index += 1
        figure(2)
        plot(T,M,label="L = "+str(L[size]))
        index = 0
        for j in i[4]: # Loop over Magnetizations per temperature
            Cv[index] = j[-1]
            index += 1
        figure(3)
        plot(T,Cv,label="L = "+str(L[size]))
        index = 0
        for j in i[5]: # Loop over Magnetizations per temperature
            X[index] = j[-1]
            index += 1
        figure(4)
        plot(T,X,label="L = "+str(L[size]))
        size += 1
    figure(1)
    legend()
    xlabel("Temperature (T)")
    ylabel("$\\langle E\\rangle (T)$")
    savefig("E_of_T_N_"+str(n)+".pdf")
    figure(2)
    legend()
    xlabel("Temperature (T)")
    ylabel("$\\langle M\\rangle (T)$")
    savefig("M_of_T_N_"+str(n)+".pdf")
    figure(3)
    legend()
    xlabel("Temperature (T)")
    ylabel("$C_{V} (T)$")
    savefig("Cv_of_T_N_"+str(n)+".pdf")
    figure(4)
    legend()
    xlabel("Temperature (T)")
    ylabel("$\\chi (T)$")
    savefig("X_of_T_N_"+str(n)+".pdf")
    show()
