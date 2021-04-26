# Geant4 project
Welcome to the Geant4 simulation framework used for the **High Energy Physics at the Energy frontier** lab session, which is part of the **Advanced Physics Master** imparted at University of Oviedo.


## DISCLAIMER
I have prepared some scripts to easily reproduce what I did to obtain the results, but one can certainly run everything by hand, you just have to write the correspondant macro file, compile with make and then plot. However, the plotting macro is specifically designed for plotting the results that appear in the experimental report.

# How to run the code
In the **`scripts`**  folder you can find a bash script which manages all the compilation steps for the simulation. 

## Compilation
If you have never run this code and want to process new simulations, you have to execute 
``sh scripts/runSim.sh 1``

And that will generate a build file and compile the code (this has to be done every time a source or header file is edited).
## Simulation
In the ``macros/`` folder you can find the original macros I used for running the simulations.

# List of available simulations:
In this list I have gathered all the already available simulations:
| Exercise  number | Description  			   | Notes |  
|---        |---           				       | ---
|  1        |  Comparison with Meroli's paper  | None |
|  2        |  Different target thicknesses    | None |
|  3        |  CMS replica simulation          | WARNING: In order to run this, you have to change the detector usage in the main.cc file and re-compile.   **Recommended:** use multithreading. |

To run any of the available simulations, take the exercise  number of the first column and run:

``sh scripts/runSim.sh 2 {number_of_the_exercise_you_want_to_run}``

## Plotting
In this repo I have included the ``root`` files that I obtained after running the simulations (so anyone can access that without having to compile everything). 
The plotting macro, stored in ``experiment/exercises.py`` takes the same argumens as the compilation macro, so in order to reproduce the results for each exercise you can run:

``python experiment/exercises.py {number_of_the_exercise_you_want_to_run}``

This will take the .root files that are stored in ``experiment/inputs/`` and plot the results that I have implemented in my experimental report.


# Some examples
## Run Meroli's comparison exercise:

``sh scripts/runSim.sh 1``

``sh scripts/runSim.sh 2 1``

``python experiment/exercise 1``

## Run CMS-replica simulation
In main.cc change the useDetector variable and set it to 2
**RECOMMENDED**: Allow multithreading by setting the useMultithread variable to ``true``. Also be careful with the number of cores you use. **By default, multithreading is off**. Now just run the exercise like:

``sh scripts/runSim.sh 1``

``sh scripts/runSim.sh 2 3``

``python experiment/exercise 3``

## references
* Lecturer's repository: https://github.com/folguera/FPFE-Geant4
* Meroli's paper: https://www.researchgate.net/publication/230949562_Energy_loss_measurement_for_charged_particles_in_very_thin_silicon_layers



