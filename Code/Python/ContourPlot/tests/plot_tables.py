import matplotlib.pyplot as plt
import import_tables as imp
import numpy as np


values_to_compare=list(zip(imp.py_phi_values,imp.math_varphi_values))
#for x in values_to_compare:
#	print(x[0],x[1])


y1=[x[0] for x in values_to_compare]
y2=[x[1] for x in values_to_compare]
# print(y1)
# print(y2)
plt.plot(y1,'-r',label='python')
plt.plot(y2,'ob',label='math')
plt.legend(loc='best')
plt.savefig('plot.pdf',bbox_inches='tight',dpi=300)
