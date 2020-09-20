import numpy as np
import matplotlib.pyplot as plt
import time


def IF(I):
    return 1.0/(2*I)


def H_En(I, I1, I2, I3, V, gamma, theta, fi):
    # constants
    j = 13.0/2.0

    A1 = IF(I1)
    A2 = IF(I2)
    A3 = IF(I3)

    t0 = I*0.5*(A1+A2)+A3*I**2+0.5*j*(A2+A3)+A1*j**2

    t2 = 2*A1*I*j*np.sin(theta)

    # gamma should be given in radians
    t3 = V*(2.0*j-1.0)/(j+1.0)*np.sin(gamma+np.pi/6)

    subTerm = (A1*np.cos(fi)**2+A2*np.sin(fi)**2-A3)
    t1 = I*(I-0.5)*np.sin(theta)**2*subTerm

    T = t0+t1-t2-t3
    return T


def CreateContourPlot(plotname, constants, spin):
    I1 = constants[0]
    I2 = constants[1]
    I3 = constants[2]
    V = constants[3]
    gamma = constants[4]

    # declare the coordinates in terms of degrees
    thetas = np.arange(0, 180.1, 1.0)
    fis = np.arange(0, 360.1, 1.0)

    # change the coordinates into radians
    thetas = thetas*np.pi/180
    fis = fis*np.pi/180

    THETAS, FIS = np.meshgrid(thetas, fis)

    # Constructing the contour plot from the meshgrid with the coordinates
    # The CP variable will be a matrix which contains at each [x,y]==[theta,varphi] the actual value of the energy function
    CP = H_En(spin, I1, I2, I3, V, gamma, THETAS, FIS)
    
    # initialize the plot with the option of setting the aspect ratio
    #the aspect ratio is used for proper scaling of the trajectories inside the contour plot, with respect to the two coordinates 
    fig, axs=plt.subplots()
    axs.contourf(thetas, fis, CP)
    
    # axs.colorbar()
    
    plt.xlabel(f'$\\theta$ [rad]')
    plt.ylabel(f'$\\varphi$ [rad]')
    plt.title(r'The Energy Function $\mathcal{H}(\theta,\varphi)$' +
              f'\n @ $I$={spin} MOIs={I1}:{I2}:{I3} V={V} $\gamma$={round(gamma*180.0/np.pi,0)}')

    # save the file in both pdf and png
    pdf = plotname+'.pdf'
    png = plotname+'.png'

    #set aspect ratio to properly render the plot
    axs.set_aspect('equal')
    plt.savefig(pdf, bbox_inches='tight')
    plt.savefig(png, bbox_inches='tight')
    plt.close()


# I1 = 73
# I2 = 6
# I3 = 67
# gamma = round(21*np.pi/180.0, 3)
# V = 6.01
# spinvalue = 12.5
CONSTANTS = [73, 3, 67, 6.01, 60.0*np.pi/180.0]
PLOTNAME = '../../Reports/py3_contours/CP-'
SPINS = [25.0/2.0, 31.0/2.0, 37.0/2.0, 51.0/2.0]

count = 1
# for spin in SPINS:
#     print(f'Started plotting CP-{count}...')
#     # Adjust the name of the plot accordingly
#     plotname = PLOTNAME+str(count)
#     CreateContourPlot(plotname, CONSTANTS, spin)
#     print(f'Finished plotting CP-{count}...\n')
#     count = count+1


def SaveEnergyData(spins,constants,filename):
    f=open(filename,'w')
    
    #declare the x-y values (spherical coordinates)
    thetas=(np.arange(0,180.1,20))*np.pi/180
    fis=(np.arange(0,360.1,20))*np.pi/180

    f.write('################\n')
    f.write(f'I={10}\n')
    for x in thetas:
        for y in fis:
            stringer='H('+str(x)+','+str(y)+ ') = '+'z'+'\n'
            f.write(stringer)
    f.write('################\n')
    f.close()

datafile='../../Reports/python_data_out.dat'

SaveEnergyData(SPINS,CONSTANTS,datafile)