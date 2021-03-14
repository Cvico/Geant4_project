#include "SteppingAction.hh"
#include "RunAction.hh"
#include "EventAction.hh"
#include "DetectorConstruction.hh"
#include "EventAction.hh"

#include "G4Step.hh"
#include "G4RunManager.hh"

SteppingAction::SteppingAction(DetectorConstruction* det, EventAction* evtAction) 
:   G4UserSteppingAction(), 
    fDetector(det),
    fEventAction(evtAction) { }


SteppingAction::~SteppingAction() {}


//
// Score only if the step was done in the Target:
//  - cllect energy deposit for the mean (per-event) energy deposit computation
//  - same for the charged particle track length
void SteppingAction::UserSteppingAction(const G4Step* theStep) {
  // Score steps done only in the target: i.e. pre-step point was in target
  
  if (theStep->GetPreStepPoint()->GetTouchableHandle()->GetVolume() 
      != fDetector->GetTargetPhysicalVolume() )  return; 

  // energy deposit
  auto eDep   = theStep->GetTotalEnergyDeposit();
  
  // track length (only for charged particles)
  auto trackL = 0.;   
  if ( theStep->GetTrack()->GetDefinition()->GetPDGCharge() != 0. ) {
    trackL = theStep->GetStepLength(); 
  }
  
  // place the information inside the event action
  fEventAction->Add( eDep, trackL );
}