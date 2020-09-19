import numpy as np
import matplotlib.pyplot as plt 

def IF(I):
    return 1.0/(2*I)

def H_En(I,I1,I2,I3,V,gamma,theta,fi):
    # constants
    j=13.0/2.0
    
    A1=IF(I1)
    A2=IF(I2)
    A3=IF(I3)
    t0=I*0.5*(A1+A2)+A3*I**2+0.5*j*(A2+A3)+A1*j**2
    t2=V*(2.0*j-1.0)/(j+1.0)*np.sin(gamma+np.pi/6)
    t3=2*A1*I*j*np.sin(theta)
    subTerm=(A1*np.cos(fi)**2+A2*np.sin(fi)**2-A3)
    t1=I*(I-0.5)*np.sin(theta)**2*subTerm
    T=t0+t1-t3-t2
    return T

I1=73
I2=6
I3=64
gamma=21*np.pi/180.0
V=6.01


thetas=np.arange(0,180.1,1.0)
fis=np.arange(0,360.1,1.0)

thetas=thetas*np.pi/180
fis=fis*np.pi/180

thetaX,fiX=np.meshgrid(thetas,fis)

z=H_En(10.5,I1,I2,I3,V,gamma,thetaX,fiX)

plt.contourf(thetas,fis,z)
plt.colorbar()
plt.xlabel(f'theta [rad]')
plt.ylabel(f'fi [rad]')
plt.savefig('cp_hen.pdf',bbox_inches='tight')