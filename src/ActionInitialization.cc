#include "ActionInitialization.hh"
#include "DetectorConstruction.hh"
#include "RunAction.hh"

void ActionInitialization::Build() const {
    PrimaryGeneratorAction* primaryAction = new PrimaryGeneratorAction(fDetector);
    SetUserAction(primaryAction);

    RunAction *runAction = new RunAction(primaryAction);   
    SetUserAction(runAction);
}