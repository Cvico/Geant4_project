#include "ActionInitialization.hh"
#include "DetectorConstruction.hh"
#include "RunAction.hh"
#include "EventAction.hh"
#include "SteppingAction.hh"

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