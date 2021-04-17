#include "CalorimeterActionInitialization.hh"
#include "CalorimeterRunAction.hh"
#include "CalorimeterEventAction.hh"
#include "SteppingAction.hh"
#include "G4RunManager.hh"


CalorimeterActionInitialization::CalorimeterActionInitialization()  
: G4VUserActionInitialization() { }

// Only used in multithread mode
void CalorimeterActionInitialization::BuildForMaster() const
{
  SetUserAction(new CalorimeterRunAction);
}

void CalorimeterActionInitialization::Build() const {
    SetUserAction(new CalorimeterPrimaryGeneratorAction);
    SetUserAction(new CalorimeterRunAction);
    SetUserAction(new CalorimeterEventAction);
}
