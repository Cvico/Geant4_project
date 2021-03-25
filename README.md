# Geant4 project
Welcome to the Geant4 simulation framework used for the **High Energy Physics at the Energy frontier** lab session, which is part of the **Advanced Physics Master** imparted at University of Oviedo.

## About the project
We used our application at the end of our development to compute the distribution of energy deposited by 100 [MeV] electrons in 5.6 [um] thin silicon target.

# How to run the code
In the **`scripts`**  folder you can find a bash script which manages all the compilation steps for the simulation. Basically this macro takes a parameter which is the step of the simulation one wants to compute. In this simulation there are 2 stages: compilation and plotting, so the list of available parameters is:
 
* 1) For running compilation + simulation: This will basically create a _build_ (if necessary) folder in which we are going to compile our code. Once the build folder is created, then the code is compiled with CMake.
* 2) For running the plotter macro: In this stage, it is necessary to have generated a rootfile with events that were recorded during the simulation (which by default should be created in the build folder). If this requirement is satisfied, then a folder _results_ would be created under the _experiment_ folder with the corresponding results.
* 3) For running both stages

Thus, the correct syntax for running the simulation is:
 `sh scripts/runSim.sh [MODE]`

where MODE takes 1,2 and 3 as valid arguments.

## references
* Lecturer's repository: https://github.com/folguera/FPFE-Geant4
* Meroli's paper: https://www.researchgate.net/publication/230949562_Energy_loss_measurement_for_charged_particles_in_very_thin_silicon_layers



