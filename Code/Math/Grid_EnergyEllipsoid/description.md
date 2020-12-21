The project is focused on exporting the trajectories as portable graphical images, to be used within the latex document.

The `GraphicsGrid` function which was previously used provides an output that has defective behavior in terms of figure labelling. More precisely, the axes labelling is missing on some elements inside the grid, while the first element of the grid is missing the subscript terms. 

Potential fix: [according to this answer](https://community.wolfram.com/groups/-/m/t/2140704?p_p_auth=ecOJG8g0) it is best practice to use `Grid[]` instead of `GraphicsGrid`.

As a result, the entire workflow (which consists in making the 3D graphical objects as flat images - 2d -, then generating 1x3 grids with ellipsoids and then export obtained graphs to external files) needs to be changed by using `Graphics`.
