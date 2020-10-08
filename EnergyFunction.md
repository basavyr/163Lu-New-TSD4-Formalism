# The energy function of $^{163}$Lu

The current project must also compute the energy function of this nucleus, in terms of its spherical components (that are replaced in the expressions of the angular momentum components).

The energy function represents the evolution of the minimum energy points with respect to different values of spin $I$, but also the relevant deformation parameters (e.g. the parameter set used in calculating the `rms`).

Expression for the energy function $\mathcal{H}$ is given below (initial calculations done by Raduta in [this document](Resources/Documentation/HLu163.pdf)):

$$\mathcal{H}=\frac{I}{2}(A_1+A_2)+A_3I^2+I(I-\frac{1}{2})\sin^2\theta(A_1\cos^2\varphi+A_2\sin^2\varphi-A_3)+\frac{j}{2}(A_2+A_3)+A_1j^2-2A_1Ij\sin\theta-V\frac{2j-1}{j+1}\sin(\gamma+\frac{\pi}{6})$$

This energy function is computed by replacing in the original structure of $\mathcal{H}$ the coordinates $(\psi,t)$ with $(0,j)$ and the term $r=I(1+\cos\theta)$.

*Original expression of the energy function (given in [this article](Towards%20a%20new%20semi-classical%20interpretation%20of%20the%20wobbling%20motion%20in%20163Lu.pdf)).*
![](2020-09-12-10-10-43.png)

## Contour Plot

The contour plot for $^{163}$Lu has been calculated within the Mathematica document `EnergyFunction.nb` (dedicated to solve the main problem). For a fixed value of spin, and arbitrary test parameters, the output file can be seen in the graphical representation shown below. This is how every contour plot representation should look like for every approach there is, namely A1, A2, B1 and B2.

The required graphical representation for the data.
![full_contours](SIGNATURE_FORMALISM/full_contours.png)

## Study of the energy function with respect to the spherical variables

* The energy $\mathcal{H}$ is evaluated at changes in both the coordinates $(\theta,\varphi)$, but also the fit parameters (deformation parameters).
* This function has free terms and coordinate-dependent terms.
* Evolution of the energy function with a change in the *free terms* magnitude might indicate the minimum value of $\mathcal{H}$.
* Understanding the smallness of the mixed terms could indicate if the function has stable points (or trajectories) around global minima (m) or maxima (M).

![evolution_study](SIGNATURE_FORMALISM/energy_function_free_terms.svg)

### Evolution of the free term $T_0$

The free term has the following expression:

```
t0[I_, j_, a1_, a2_, a3_, V_, \[Gamma]_] := 
  I/2 (a1 + a2) + a3*I^2 + j/2 (a2 + a3) + a1*j^2 - 
   V (2 j - 1)/(j + 1) Sin[\[Gamma] + \[Pi]/6];
```

The triaxiality parameter $\gamma$ and the single-particle potential strength $V$ enter in the expression of $T_0$. Due to this, two separate evolutions of $T_0$ should be done, at fixed moments of inertia: one w.r.t. $\gamma$ and one w.r.t. $V$.

#### Free term - evolution with $\gamma$

The inertial parameters are fixed, together with $V$. These values are obtained from the fitting procedure part. In this study, $\gamma$ varies inside: $[0,\frac{\pi}{6}]$.

![evolution with gamma](T0_gm.jpeg)

#### Free term - evolution with $V$

The inertial parameters are fixed, together with $\gamma$. These values are obtained from the fitting procedure part. In this study, $V$ varies inside: $[0,10]$.

![evolution with gamma](T0_V.jpeg)

### Evolution of $T_1$

This is a mixed term. Depends on both coordinates.

#### $T_1$ as a function of $\theta$

![](T1_th.jpeg)

#### $T_1$ as a function of $\varphi$

![](T1_fi.jpeg)

### Evolution of $T_2$

This term only contains the $\theta$ coordinate.

#### $T_2$ evolution with $\theta$

![](T2_th.jpeg)

## Python vs. Mathematica

There is a consistency between both implementations.

```
Do[Print[th, " ", 
  Hen[spinTSD1, \[Pi]/2, th, A1, A2, A3, 
   V, \[Gamma]]], {th, {0, \[Pi]/4, \[Pi]/2, \[Pi]}}]

0 -5.57223

\[Pi]/4 6.41407

\[Pi]/2 18.4004

\[Pi] -5.57223
```

These values correspond to the numerical results printed via python within this segment of [py3-impl](../Code/Python/EnergyFunction.py).

```
phi_test_values=[0,np.pi/4.0,np.pi/2.0,np.pi]
for fi in phi_test_values:
    print(H_En(SPINS[0],CONSTANTS[0],CONSTANTS[1],CONSTANTS[2],CONSTANTS[3],CONSTANTS[4],np.pi/2,fi))
```
