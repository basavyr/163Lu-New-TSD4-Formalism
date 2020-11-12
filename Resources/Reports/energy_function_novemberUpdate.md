# Lu163 Energy Function – November update

1. Study the evolution of the three minima of the energy function, with the change in angular momentum $I$ (for a fixed set of moments of inertia, $V$, $\gamma$ and $j$).
   * For a given set of MOIs, the location of the minimum points of the energy function $\mathcal{H}$ won't change their location with the change in spin (i.e. $p^k_{min}=\{\theta_{k},\varphi_k\}$ will remain in the same positions within the $\theta-\varphi$ plane).
   * The change in rotational spin $I$ will only change the value of $\mathcal{H}$ itself.
2. Check the expression of the energy function in cartesian coordinates using the new quantization axis: $x_3$ is the quantization axis: $x_3=I\cos\theta$.
   * The expression of the Energy function from Raduta calculations use power series expansion to approximate the linear term $-2A_1Ij\sin\theta$.
   * For this reason, there is an inconsistency between the analytic result obtain by pure replacement of the cartesian components within the expression of $H$, Raduta method, and the initial Hamiltonian given by formula (1) in [this document](../Documentation/HLu163_Nov_Update.pdf).

Calculations for the new Energy Function expression (in cartesian coordinates) are given in [this Mathematica doc](Code/Math/EnergyFunction_NovemberUpdate.nb).