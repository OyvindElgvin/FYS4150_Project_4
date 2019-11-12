from numpy import *
from matplotlib.pyplot import *
import plotFunctions
import Py_Functions

'''
# 1 The most likely state
n_ML = 100000000 #ML = Most likely
A_20_order = Py_Functions.readmatrices("../Results_4c_order_N_%s_L_20.txt" % n_ML)[0]
A_20_random = Py_Functions.readmatrices("../Results_4c_random_N_%s_L_20.txt" % n_ML)[0]

T_ML = [i for i in A_20_order[0]]
lst_ML = [A_20_order,A_20_random]

plotFunctions.plotMostLikelyState(lst_ML,T_ML,n_ML)
plotFunctions.plotAcceptedConfigurations(lst_ML,T_ML,n_ML)
'''

'''
# 2 Probability distribution
n_PD = 1000000000 #PD = Probability distribution
A_20_Energies = Py_Functions.readmatrices("../Results_4d_N_%s_L_20.txt" % n_PD)[0]

T_PD = [i for i in A_20_Energies[0]]

plotFunctions.plotProbabilityDistribution(A_20_Energies,T_PD,n_PD)
'''


# 3 Phase transition and critical temperature
n = 100000000
A_40 = Py_Functions.readmatrices("../Results_4e_2_N_%s_L_40.txt" % n)[0]
print("Read 40")
A_60 = Py_Functions.readmatrices("../Results_4e_2_N_%s_L_60.txt" % n)[0]
print("Read 60")
A_80 = Py_Functions.readmatrices("../Results_4e_2_N_%s_L_80.txt" % n)[0]
print("Read 80")
A_100 = Py_Functions.readmatrices("../Results_4e_2_N_%s_L_100.txt" % n)[0]
print("Read 100")
T = [i for i in A_40[0]]
lst = [A_40,A_60,A_80,A_100]

plotFunctions.plotPhaseTransition(lst,T,n)
