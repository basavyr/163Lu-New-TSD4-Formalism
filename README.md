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

## Preliminary results

Key features of the current implementation:

* uses a global array as the container to store the values of the theoretical energies.
  * In this way, re-allocation of the list with each iteration in the rms-search-loop is avoided
  * The time execution of the entire process(as well as the memory pressure on the actual machine) is much more optimal rather than the previous version, where a new array was initialized within each main iteration.
* uses small steps for the fit parameters (`I_step=1`)
* uses fixed $\gamma$: only four values (close to the experimental value $\gamma_{exp}=17$) are considered in the 
* the rms implementation has proper stopping procedures in case the theoretical values are non-physical numbers.
* priority for $\mathcal{I}_1$ maximal MOI is introduced into the fit. 
* special condition for triaxial MOIs
* two formalisms for TSD4 are considered into the fit procedure:
  * TSD4: $(n_{w_1},n_{w_2})=(0,0)$
  * TSD4: $(n_{w_1},n_{w_2})=(1,0)$
* other fixed parameters: $j=13/2$

## Fit results

### TSD4: $(n_{w_1},n_{w_2})=(1,0)$

```
##########################
I1= 73
I2= 3
I3= 67
V= 6.01
gamma= 21
E_RMS= 0.143092
##########################
```

![](2020-08-30-11-34-28.png)