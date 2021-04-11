#include "EventAction.hh"
#include "RunAction.hh"

#include "G4RunManager.hh"
#include "G4Event.hh"
#include "G4UnitsTable.hh"

#include "Randomize.hh"
#include <iomanip>

#include "Analyser.hh"

EventAction::EventAction() 
  : G4UserEventAction(),
    fEdepPerEvt(0.0),
    fChTrackLengthPerEvt(0.0) {}


EventAction::~EventAction() {}


// Beore each event: reset per-event variables 
void EventAction::BeginOfEventAction(const G4Event* /*anEvent*/) {
  fEdepPerEvt           = 0.0;
  fChTrackLengthPerEvt  = 0.0;	
}


// After each event:
// fill the data collected for this event into the Run global (thread local)
// data Run data object (i.e. into YourRun)  
void EventAction::EndOfEventAction(const G4Event* event) {

  // Accumulate statistics
  //

  // get analysis manager
  auto analysisManager = G4AnalysisManager::Instance();

  // fill histograms
  analysisManager->FillH1(0, fEdepPerEvt);
  analysisManager->FillH1(1, fChTrackLengthPerEvt);

  // fill ntuple
  analysisManager->FillNtupleDColumn(0, fEdepPerEvt);
  analysisManager->FillNtupleDColumn(1, fChTrackLengthPerEvt);
  analysisManager->AddNtupleRow();

  // Print per event (modulo n)
  //
  auto eventID = event->GetEventID();
  auto printModulo = G4RunManager::GetRunManager()->GetPrintProgress();
  if ( ( printModulo > 0 ) && ( eventID % printModulo == 0 ) ) {
    G4cout << "---> End of event: " << eventID << G4endl;

    G4cout
      << "   total energy: " << std::setw(7)
      << G4BestUnit(fEdepPerEvt,"Energy")
      << "   total track length: " << std::setw(7)
      << G4BestUnit(fChTrackLengthPerEvt,"Length")
      << G4endl;
  }
}
