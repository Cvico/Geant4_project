#include "ActionInitialization.hh"
#include "DetectorConstruction.hh"
#include "RunAction.hh"
#include "EventAction.hh"
#include "SteppingAction.hh"
#include "G4RunManager.hh"


/*
                                                BRIEF DESCRIPTION
------------------------------------------------------------------------------------------------------------------------------------------
Geant4 has two user initialization classes and one user action class whose methods the user must override in order to implement a 
simulation. They require the user to define the detector, specify the physics to be used, and define how initial particles are to 
be generated. These classes are described in Mandatory User Actions and Initializations.

FIND MORE INFORMATION AT
https://geant4-userdoc.web.cern.ch/UsersGuides/ForApplicationDeveloper/html/UserActions/mandatoryActions.html
------------------------------------------------------------------------------------------------------------------------------------------
*/
ActionInitialization::ActionInitialization(DetectorConstruction* detector)  
: G4VUserActionInitialization() { 
  fDetector = detector;   
} 

void ActionInitialization::Build() const {

    PrimaryGeneratorAction* primaryAction = new PrimaryGeneratorAction(fDetector);
    SetUserAction(primaryAction);

    RunAction *runAction = new RunAction(primaryAction);   
    SetUserAction(runAction);

    EventAction * eventAction = new EventAction();
    SetUserAction(eventAction);

    SteppingAction* steppingAction = new SteppingAction(fDetector, eventAction);
    SetUserAction(steppingAction);
}
