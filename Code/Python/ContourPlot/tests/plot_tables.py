import matplotlib.pyplot as plt
import import_tables as imp
import numpy as np

path_to_storage="../../../../Resources/Output_Data/ContourPlots/"

theta_compare=list(zip(imp.py_phi_values,imp.math_varphi_values))
varphi_compare=list(zip(imp.py_theta_values,imp.math_theta_values))
#for x in values_to_compare:
#	print(x[0],x[1])


theta_image_path=path_to_storage+'theta.pdf'
varphi_image_path=path_to_storage+'varphi.pdf'

#plot the evolution of H with varphi 
y1=[x[0] for x in theta_compare]
y2=[x[1] for x in theta_compare]

plt.plot(y1,'-r',label='python')
plt.plot(y2,'ob',label='math')
plt.legend(loc='best')
plt.savefig(theta_image_path,bbox_inches='tight',dpi=300)
plt.close()
#plot the evolution of H with theta

w1=[x[0] for x in varphi_compare]
w2=[x[1] for x in varphi_compare]

plt.plot(w1,'-r',label='python')
plt.plot(w2,'ob',label='math')
plt.legend(loc='best')
plt.savefig(varphi_image_path,bbox_inches='tight',dpi=300)
plt.close()
