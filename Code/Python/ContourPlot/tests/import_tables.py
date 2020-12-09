# declare the import paths for math and py files
import angular_values as av

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

fct=ImportFunction(av.py_theta_file)
print(fct)
