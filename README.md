# Geant4 project
Welcome to the Geant4 simulation framework used for the **High Energy Physics at the Energy frontier** lab session, which is part of the **Advanced Physics Master** imparted at University of Oviedo.

## About the project
We used our application at the end of our development to compute the distribution of energy deposited by 100 [MeV] electrons in 5.6 [um] thin silicon target.

# How to run the code


In the **`scripts`**  folder you can find a bash script which manages all the compilation steps for the simulation. 

## Compilation
If you have never run this code and want to process new simulations, you have to execute 

``sh scripts/runSim.sh 1``

And that will generate a build file and compile the code (this has to be done every time a source or header file is edited).

## Simulation

I have prepared several .mac (macro) files that can be used for different simulations that can be used for standalone simulations. In order to reproduce
the results that go **in each section of the experimental report** one can run:

``sh scripts/runSim.sh 2 {number_of_the_exercise_you_want_to_run}``



## Plotting
In this repo I (will) have included the .dat files that I obtained after running the simulations (so anyone can access that without having to compile everything). 
The plotting macro, stored in ``experiment/exercises.py`` takes the same argumens as the compilation macro, so in order to reproduce the results that I have in
the experimental report you can run 

``python experiment/exercises.py --exercise {number_of_the_exercise_you_want_to_run}``

This will take the .dat or .root files that are stored in ``experiment/inputs/`` and plot the results that I have implemented in my experimental report.

# Built-in macro lists to run the exercises
Here's a (temporary) list of all the exercises that can be run with this script:
 * 1: Run the comparison with Meroli's paper

## references
* Lecturer's repository: https://github.com/folguera/FPFE-Geant4
* Meroli's paper: https://www.researchgate.net/publication/230949562_Energy_loss_measurement_for_charged_particles_in_very_thin_silicon_layers



