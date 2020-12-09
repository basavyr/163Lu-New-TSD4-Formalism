# declare the import paths for math and py files
import angular_values as av
import matplotlib.pyplot as plt

def ImportFunction(file_path):
	table=open(file_path,'r')
	info=table.readlines()
	convert= lambda x: float(x)
	ret_val=[]
	for line in info:
		values=line.split(' ')
		current_h=list(map(convert,values))
		ret_val.append(current_h[2])
	return ret_val

def MathematicaImport(file_path):
	table=open(file_path,'r')
	info=table.readlines()
	convert=lambda x: float(x)
	ret_val=[]
	for line in info:
		values=line.split()
		current_h=list(map(convert,values))
		ret_val.append(current_h[2])
	return ret_val 

#theta evolution
py_theta_values=ImportFunction(av.py_theta_file)
math_theta_values=MathematicaImport(av.math_theta_file)
#print(len(py_theta_values))
#print(len(math_theta_values))
py_phi_values=ImportFunction(av.py_varphi_file)
math_varphi_values=MathematicaImport(av.math_varphi_file)
