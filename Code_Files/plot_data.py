from numpy import *
from matplotlib.pyplot import *

# Read from files
m=100000
n = array([i for i in range(0,m)]) # List of number of monte carlo cycles
E_mean_L20_T1_ord = array([random.randn() for _ in range(m)]) #Syntax: Value_mean_Lattice-size_Tepmerature_ordered/unordered-spin
E_mean_L20_T1_unord = array([random.randn() for _ in range(m)])
E_mean_L20_T24_ord = array([random.randn() for _ in range(m)])
E_mean_L20_T24_unord = array([random.randn() for _ in range(m)])
M_mean_L20_T1_ord = array([random.randn() for _ in range(m)])
M_mean_L20_T1_unord = array([random.randn() for _ in range(m)])
M_mean_L20_T24_ord = array([random.randn() for _ in range(m)])
M_mean_L20_T24_unord = array([random.randn() for _ in range(m)])


# The most likely state
fig1, (ax1, ax2, ax3, ax4) = subplots(4, 1, sharex=True)
line1 = ax1.plot(n,E_mean_L20_T1_ord,label="a)")
ax1.text(1,1, 'a', horizontalalignment='left', verticalalignment='bottom', transform=ax1.transAxes)
ax1.set_ylabel("$\\langle E\\rangle$")
line2 = ax2.plot(n,E_mean_L20_T1_unord,label="b)")
ax2.text(1,1, 'b', horizontalalignment='left', verticalalignment='bottom', transform=ax2.transAxes)
ax2.set_ylabel("$\\langle E\\rangle$")
line3 = ax3.plot(n,E_mean_L20_T24_ord,label="c)")
ax3.text(1,1, 'c', horizontalalignment='left', verticalalignment='bottom', transform=ax3.transAxes)
ax3.set_ylabel("$\\langle E\\rangle$")
line4 = ax4.plot(n,E_mean_L20_T24_unord,label="d)")
ax4.text(1,1, 'd', horizontalalignment='left', verticalalignment='bottom', transform=ax4.transAxes)
ax4.set_ylabel("$\\langle E\\rangle$")
xlabel("# of MC-cycles (n)")
#savefig("../Figures/E_mean_L20.pdf")
#show()

fig2, (ax1, ax2, ax3, ax4) = subplots(4, 1, sharex=True)
line1 = ax1.plot(n,M_mean_L20_T1_ord,label="a)")
ax1.text(1,1, 'a', horizontalalignment='left', verticalalignment='bottom', transform=ax1.transAxes)
ax1.set_ylabel("$\\langle M\\rangle$")
line2 = ax2.plot(n,M_mean_L20_T1_unord,label="b)")
ax2.text(1,1, 'b', horizontalalignment='left', verticalalignment='bottom', transform=ax2.transAxes)
ax2.set_ylabel("$\\langle M\\rangle$")
line3 = ax3.plot(n,M_mean_L20_T24_ord,label="c)")
ax3.text(1,1, 'c', horizontalalignment='left', verticalalignment='bottom', transform=ax3.transAxes)
ax3.set_ylabel("$\\langle M\\rangle$")
line4 = ax4.plot(n,M_mean_L20_T24_unord,label="d)")
ax4.text(1,1, 'd', horizontalalignment='left', verticalalignment='bottom', transform=ax4.transAxes)
ax4.set_ylabel("$\\langle M\\rangle$")
xlabel("# of MC-cycles (n)")
#savefig("../Figures/M_mean_L20.pdf")
#show()

# Probability distribution
fig3, (ax1, ax2, ax3, ax4) = subplots(4, 1, sharex=True)
line1 = ax1.hist(E_mean_L20_T1_ord, 50, normed=True, facecolor='g', alpha=0.75)
ax1.set_ylabel("$\\rho_{\\langle E\\rangle}$")
line2 = ax2.hist(E_mean_L20_T1_unord, 50, normed=True, facecolor='g', alpha=0.75)
ax2.set_ylabel("$\\rho_{\\langle E\\rangle}$")
line3 = ax3.hist(E_mean_L20_T24_ord, 50, normed=True, facecolor='g', alpha=0.75)
ax3.set_ylabel("$\\rho_{\\langle E\\rangle}$")
line4 = ax4.hist(E_mean_L20_T24_unord, 50, normed=True, facecolor='g', alpha=0.75)
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
xlabel("$\\langle E\\rangle$")
#savefig("../Figures/M_mean_L20_probability.pdf")

show()

# Phase transition and critical temperature
