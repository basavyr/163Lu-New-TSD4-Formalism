import sys

sys.path.append('../')

import contour as cp

def TestCoordinates():
	q=cp.mt
	l_theta=len(cp.thetas)
	print(l_theta)
	for id in range(len(q)):
		#print(q[id])
		id=id+10000

def TestThetaEvolution(varphi):
	ret_list=[]
	for id in range(len(cp.thetas)):
		if(id % 10 ==0):
			q=(cp.thetas[id],varphi)
#			print(cp.thetas[id],varphi)
			ret_list.append(q)
	return ret_list		
def TestPhiEvolution(theta):
	ret_list=[]
	for id in range(len(cp.phis)):
		if(id % 10 ==0):
			q=(theta,cp.phis[id])
#			print(theta,cp.phis[id])
			ret_list.append(q)
	return ret_list		

theta_file='theta_evolution.dat'
varphi_file='phi_evolution.dat'


def WriteData(out_file,data):
	f=open(out_file,'w')
	for x_id in data:
		f.write(str(x_id[0])+' , '+str(x_id[1]))
		f.write('\n')
	f.close()
	
WriteData(theta_file,TestThetaEvolution(cp.phis[1]))
WriteData(varphi_file,TestPhiEvolution(cp.thetas[1]))


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
