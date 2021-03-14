#include "ActionInitialization.hh"
#include "DetectorConstruction.hh"

void ActionInitialization::Build() const {
    PrimaryGeneratorAction* primaryAction = new PrimaryGeneratorAction(fDetector);
    SetUserAction(primaryAction);
    
}