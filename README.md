# $^{163}$Lu - Excitation energies
## New approach for TSD4 structure

Project which aims at computing the excitation energies for the wobbling spectrum of $^{163}$Lu using a novel approach for the TSD4 band.

The nucleus $^{163}$Lu has four wobbling bands (including the yrast TSD1) and the excitation spectrum has a rich structure. Each band (denoted by TSD1,2,3, and 4, respectively) has a certain number of *spin states*, with a definite energy for each state.

So far, the calculations involving *wobbling spectrum* of this nucleus were made with the fourth band considered as the coupling of an even-even core with an odd-$j$ particle (the $h=\pi_{11/2}$ *intruder* proton). However, this current approach will consider the fourth band (*three-phonon wobbling band*) as a collection of states with definite energies, but the coupling an odd-$j$ particle will be detached (no more coupling: **the spins in this band will be equivalent to the spin of the core itself**).

___

Main goals of the present project are:

- [ ] Obtain the analytic formulas for the four excited **wobbling bands** in $^{163}$Lu.
- [ ] Write the experimental data set with the known spins and excitation energies for each band.
- [ ] **New formalism**: The spins for the fourth band (namely, TSD4) will represent the values of the *core*, and not the total particle-rotor model (no core+odd-particle coupling).
- [ ] Define the free parameter set which enters in the energy formulas.
- [ ] Compute the RMS of the excitation energies of all the bands w.r.t. to a parameter set $P$.
- [ ] Find the parameter set $P_m$ which provides the best RMS value.

## Initial test run

August 2020:

![](./reports/2020-08-21-17-10-10.png)

The algorithm is using large parameter steps, so accuracy is lost.

Update on the algorithm with optimized computations.

![](./reports/2020-08-22-13-07-58.png)

Simulation implying the triaxiality conditions.

![](./reports/2020-08-22-13-25-53.png)

Optimized search with steps of size `5,5,0.5`, respectively.

![](./reports/2020-08-23-11-20-38.png)

Results in `params.dat`

```
Starting to search for the minimum RMS...
I1= 71
I2= 6
I3= 16
V= 1.01
gm= 30
E_RMS= 0.22564
0.241195,0.539159,0.89377,1.30494,1.77262,2.29675,2.87732,3.51429,4.20766,4.95741,5.76353,6.62601,7.54485,8.52005,9.55159,10.6395,11.7837,12.9843,14.2412,15.5545,16.9241,1.17339,1.62007,2.12254,2.68084,3.29503,3.96515,4.69124,5.47334,6.31148,7.20569,8.156,9.16242,10.225,11.3437,12.5186,13.7497,15.037,1.9352,2.47246,3.06494,3.71275,4.41601,5.17482,5.98927,6.85943,7.78537,8.76714,9.8048,10.8984,12.0479,13.2535,3.85393,4.57549,5.35342,6.18772,7.07839,8.0254,9.02877,10.0885,11.2046,12.377,
Finished computations after 777 valid parameter evaluations...
Total evaluations: 1861111
```

### Computation ran on VM@elk

This calculations were done using the following sizes for the steps:
sI=2.5
gms=1
vs=0.25

```
Initializing rms class...
Starting to search for the minimum RMS...
I1= 66
I2= 71
I3= 3.5
V= 9.76
gm= 28
E_RMS= 0.238275
Finished computations. Process took: 3315.19 s
```

### Compilation using triaxiality and transverse regime.

The step size for I=5

```
Initializing rms class...
Starting to search for the minimum RMS...
I1= 56
I2= 61
I3= 6
V= 9.76
gm= 50
E_RMS= 0.475362
Finished computations. Process took: 498.02 s
```

### Compilation using triaxiality and transverse regime.

The step size for I=2.5

```
Initializing rms class...
Starting to search for the minimum RMS...
I1= 66
I2= 71
I3= 3.5
V= 9.76
gm= 28
E_RMS= 0.238275
Finished computations. Process took: 4546.12 s
```