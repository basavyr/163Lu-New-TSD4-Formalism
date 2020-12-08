import numpy as np
from numpy import random as rd

def InertiaFactor(MOI):
	return 1.0/(2.0*MOI)

def H_min(spin, odd_spin,moi_1, moi_2, moi_3, v, gamma, theta, varphi):
	# check of the two coordinates have valid values:
	if((theta<0.0 or theta>np.pi) or (varphi<0.0 or varphi>2.0*np.pi)):
		return f'Invalid coordinates (th,fi)=({theta},{varphi})'
	# change the name of variables for consistency with the actual formula
	A1=InertiaFactor(moi_1)
	A2=InertiaFactor(moi_2)
	A3=InertiaFactor(moi_3)
	I=spin
	j=odd_spin
	V=v
	# transform gamma from degrees into radians
	gamma_radians=gamma*np.pi/180.0
	angle=gamma_radians+np.pi/6.0
	constant_term=0.5*I*(A1+A2)+A3*np.power(I,2)+0.5*j*(A2+A3)+A1*np.power(j,2)-V*(2.0*j-1.0)/(j+1.0)*np.sin(angle)
	theta_term=-2.0*A1*I*j*np.sin(theta)
	mixed_term=I*(I-0.5)*np.power(np.sin(theta),2)*(A1*np.power(np.cos(varphi),2)+A2*np.power(np.sin(varphi),2)-A3)
	H=constant_term+theta_term+mixed_term
	return H

spins=np.arange(8.5,48.5,2.0)
for spin in spins:
	print(H_min(spin,6.5,72,15,7,2.1,19,np.pi,np.pi))
