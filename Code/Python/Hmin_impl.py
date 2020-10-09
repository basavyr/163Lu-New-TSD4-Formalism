# testing the H_min function with a defined set of parameters

import numpy as np


def IF(I):
    return 1.0/(2.0*I)


SPINS = np.arange(6.5, 48.5, 1.0)


def H_min(spin, params):
    # THE ODD PARTICLE IS FIXED TO THE PROTON ON THE j=13/2 ORBITAL
    ODD_SPIN = 6.5
    A1 = IF(params[0])
    A2 = IF(params[1])
    A3 = IF(params[2])
    V = params[3]
    gm = params[4]
    h = (A2+A3)*(spin+ODD_SPIN)*0.5+A1*np.power(spin-ODD_SPIN, 2)-V * \
        (2.0*ODD_SPIN-1.0)/(ODD_SPIN+1)*np.sin(gm*np.pi/180.0+np.pi/6.0)
    return h


PARAMS = [73.0, 68.0, 3.0, 8.1, 15.0]

file = open("/Users/basavyr/Library/Mobile Documents/com~apple~CloudDocs/Work/Pipeline/DFT/163Lu-New-TSD4-Formalism/Resources/Output_Data/hmin_data.dat", 'w')
file.write('Evolution of the H_min function from the excitation energy with respect to the total angular momentum I\n')
file.write(
    f'I_1={str(PARAMS[0])}   |   I_2={str(PARAMS[1])}   |   I_3={str(PARAMS[2])}\n')
file.write(f'V={str(PARAMS[3])}\n')
file.write(f'gamma={str(PARAMS[4])}\n')
file.write(f'**********************************\n')
file.write(f'I      H_min(I)\n')
for spin in SPINS:
    line = str(spin)+'   '+str(H_min(spin, PARAMS))+'\n'
    file.write(line)
