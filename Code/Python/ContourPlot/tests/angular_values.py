import sys
import os

sys.path.append('../')

import contour as cp

def H(spin,q):
	CT=cp.CT
	ret_val=cp.SimplifiedH(spin,CT,q)
	return ret_val

def TestCoordinates():
	q=cp.mt
	l_theta=len(cp.thetas)
	print(l_theta)
	for id in range(len(q)):
		#print(q[id])
		id=id+10000

def TestThetaEvolution(spin,varphi):
	ret_list=[]
	for id in range(len(cp.thetas)):
		if(id % 10 ==0):
			q=(cp.Deg(cp.thetas[id]),cp.Deg(varphi),H(spin,[cp.thetas[id],varphi]))
#			print(cp.thetas[id],varphi)
			ret_list.append(q)
	return ret_list		
def TestPhiEvolution(spin,theta):
	ret_list=[]
	for id in range(len(cp.phis)):
		if(id % 10 ==0):
			# q=(theta,cp.phis[id])
			q=(cp.Deg(theta),cp.Deg(cp.phis[id]),H(spin,[theta,cp.phis[id]]))
#			print(theta,cp.phis[id])
			ret_list.append(q)
	return ret_list		

# files from python
py_files_path="/Users/robertpoenaru/Library/Mobile Documents/com~apple~CloudDocs/Work/Pipeline/DFT/163Lu-New-TSD4-Formalism/Resources/Output_Data/ContourPlots/py/"
math_files_path="/Users/robertpoenaru/Library/Mobile Documents/com~apple~CloudDocs/Work/Pipeline/DFT/163Lu-New-TSD4-Formalism/Resources/Output_Data/ContourPlots/math/"
# the files from python
py_theta_file=py_files_path+'theta_evolution.dat'
py_varphi_file=py_files_path+'phi_evolution.dat'

# the files from math
math_theta_file=math_files_path+'theta_evolution.dat'
math_varphi_file=math_files_path+'varphi_evolution.dat'


# os.system(f'ls {py_files_path}')
# os.system(f'ls {math_files_path}')
def WriteData(out_file,data):
	f=open(out_file,'w')
	for x_id in data:
		f.write(str(x_id[0])+' '+str(x_id[1])+' '+str(x_id[2]))
		f.write('\n')
	f.close()

I=12.5
WriteData(py_theta_file,TestThetaEvolution(I,cp.phis[60]))
WriteData(py_varphi_file,TestPhiEvolution(I,cp.thetas[60]))

# Opening the test files for saving the data
# f1=open(theta_file,'w')
# f2=open(varphi_file,'w')
# 
# f1.write(str(cp.mt))
# f2.write(str(cp.mt))

# Closing the files before ending the tests
# f1.close()
# f2.close()

		
	

#TestCoordinates()
