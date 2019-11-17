from numpy import array, ones

Tc = array([2.2985,2.2765,2.263,2.2685])

L = array([40,60,80,100])

R = []

i = 0
jmax = 4
for i in range(3):
	for j in range(i+1,jmax):
		R.append((L[i]*Tc[i]-L[j]*Tc[j])/(L[i]-L[j]))
	
R = array(R)
B = R - 2.269*ones(6)
print B
print 2.2885-2.269


print (60*2.2765 - 100*2.2685)/(60.-100.)
