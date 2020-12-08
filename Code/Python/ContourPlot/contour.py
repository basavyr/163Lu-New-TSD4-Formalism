import numpy as np
from numpy import random as rd

def InertiaFactor(MOI):
	return 1.0/(2.0*MOI)

def H_min(spin, odd_spin,moi_1, moi_2, moi_3, v, gamma, theta, varphi):
	# change the name of variables for consistency with the actual formula
	A1=InertiaFactor(moi_1)
	A2=InertiaFactor(moi_2)
	A3=InertiaFactor(moi_3)
	I=spin
	j=odd_spin
	term1=0.5*I*(A1+A2)+A3*np.power(I,2)
	H=term1
	return H

spins=np.arange(8.5,48.5,2.0)
for spin in spins:
	print(H_min(spin,6.5,72,15,7,2.1,19,20,20))
