import numpy as np
from numpy import random as rd
import matplotlib.pyplot as plt
def InertiaFactor(MOI):
	return 1.0/(2.0*MOI)

def H_min(spin, odd_spin,moi_1, moi_2, moi_3, v, gamma, theta, varphi):
	# check of the two coordinates have valid values:
#	if((theta<0.0 or theta>np.pi) or (varphi<0.0 or varphi>2.0*np.pi)):
#		return f'Invalid coordinates (th,fi)=({theta},{varphi})'
	# change the name of variables for consistency with the actual formula
	#if np.any(t<0 for t in theta[0]):
	#	return f'Invalid coordinates (th,fi)=({theta},{varphi})'
	# print(theta)	
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
#for spin in spins:
#	print(H_min(spin,6.5,72,15,7,2.1,19,np.pi,np.pi))


thetas=[theta for theta in np.arange(0.0,np.pi+np.pi/180,np.pi/180.0)]
phis=[phi for phi in np.arange(0.0,2.0*np.pi+np.pi/180,np.pi/180.0)]

def Rad(angle):
	ret_val=angle*np.pi/180.0
	return np.round(ret_val,2)

def Deg(angle):
	ret_val=angle*180.0/np.pi
	return np.round(ret_val)

#print(list(map(Deg,thetas)))
#print(list(map(Deg,phis)))


# CONSTANTS = [ j, I1, I2, I3, V, gm]
CT=[6.5,72,15,7,2.1,22]

mt=[(x,y) for x in thetas for y in phis]

def SimplifiedH(spin,CT,q1,q2):
	return H_min(spin,CT[0],CT[1],CT[2],CT[3],CT[4],CT[5],q1,q2)


mesh_theta,mesh_phi=np.meshgrid(thetas,phis)	
h_map=SimplifiedH(12.5,CT,mesh_theta,mesh_phi)
plt.contourf(thetas,phis,h_map)
plt.show()
