//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
//


#include "CalorimeterEventAction.hh"
#include "Analyser.hh"

#include "G4RunManager.hh"
#include "G4Event.hh"
#include "G4SDManager.hh"
#include "G4HCofThisEvent.hh"
#include "G4UnitsTable.hh"

#include "Randomize.hh"
#include <iomanip>

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

CalorimeterEventAction::CalorimeterEventAction()
 : G4UserEventAction(),
   fHCALEdepHCID(-1),
   fECALEdepHCID(-1),
   fHCALTrackLengthHCID(-1),
   fECALTrackLengthHCID(-1)
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

CalorimeterEventAction::~CalorimeterEventAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4THitsMap<G4double>* 
CalorimeterEventAction::GetHitsCollection(G4int hcID,
                                  const G4Event* event) const
{
  auto hitsCollection 
    = static_cast<G4THitsMap<G4double>*>(
        event->GetHCofThisEvent()->GetHC(hcID));
  
  if ( ! hitsCollection ) {
    G4ExceptionDescription msg;
    msg << "Cannot access hitsCollection ID " << hcID; 
    G4Exception("CalorimeterEventAction::GetHitsCollection()",
      "MyCode0003", FatalException, msg);
  }         

  return hitsCollection;
}    

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4double CalorimeterEventAction::GetSum(G4THitsMap<G4double>* hitsMap) const
{
  G4double sumValue = 0.;
  for ( auto it : *hitsMap->GetMap() ) {
    // hitsMap->GetMap() returns the map of std::map<G4int, G4double*>
    sumValue += *(it.second);
  }
  return sumValue;  
}  

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void CalorimeterEventAction::PrintEventStatistics(
                            G4double ecalEdep, G4double ecalTrackLength,
                            G4double hcalEdep, G4double hcalTrackLength) const
{
  // Print event statistics
  //
  G4cout
     << "   ECAL: total energy: " 
     << std::setw(7) << G4BestUnit(ecalEdep, "Energy")
     << "       total track length: " 
     << std::setw(7) << G4BestUnit(ecalTrackLength, "Length")
     << G4endl
     << "   HCAL: total energy: " 
     << std::setw(7) << G4BestUnit(hcalEdep, "Energy")
     << "         total track length: " 
     << std::setw(7) << G4BestUnit(hcalTrackLength, "Length")
     << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void CalorimeterEventAction::BeginOfEventAction(const G4Event* /*event*/)
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void CalorimeterEventAction::EndOfEventAction(const G4Event* event)
{  
   // Get hist collections IDs
  if ( fECALEdepHCID == -1 ) {
    fECALEdepHCID 
      = G4SDManager::GetSDMpointer()->GetCollectionID("ECAL/Edep");
    fHCALEdepHCID 
      = G4SDManager::GetSDMpointer()->GetCollectionID("HCAL/Edep");
    fECALTrackLengthHCID 
      = G4SDManager::GetSDMpointer()->GetCollectionID("ECAL/TrackLength");
    fHCALTrackLengthHCID 
      = G4SDManager::GetSDMpointer()->GetCollectionID("HCAL/TrackLength");
  }
  
  // Get sum values from hits collections
  //
  auto ecalEdep = GetSum(GetHitsCollection(fECALEdepHCID, event));
  auto hcalEdep = GetSum(GetHitsCollection(fHCALEdepHCID, event));

  auto ecalTrackLength 
    = GetSum(GetHitsCollection(fECALTrackLengthHCID, event));
  auto hcalTrackLength 
    = GetSum(GetHitsCollection(fHCALTrackLengthHCID, event));

  // get analysis manager
  auto analysisManager = G4AnalysisManager::Instance();

  // fill histograms
  //  
  analysisManager->FillH1(0, ecalEdep);
  analysisManager->FillH1(1, hcalEdep);
  analysisManager->FillH1(2, ecalTrackLength);
  analysisManager->FillH1(3, hcalTrackLength);
  
  // fill ntuple
  //
  analysisManager->FillNtupleDColumn(0, ecalEdep);
  analysisManager->FillNtupleDColumn(1, hcalEdep);
  analysisManager->FillNtupleDColumn(2, ecalTrackLength);
  analysisManager->FillNtupleDColumn(3, hcalTrackLength);
  analysisManager->AddNtupleRow();  
  
  //print per event (modulo n)
  //
  auto eventID = event->GetEventID();
  auto printModulo = G4RunManager::GetRunManager()->GetPrintProgress();
  if ( ( printModulo > 0 ) && ( eventID % printModulo == 0 ) ) {
    G4cout << "---> End of event: " << eventID << G4endl;     
    PrintEventStatistics(ecalEdep, ecalTrackLength, hcalEdep, hcalTrackLength);
  }
}  

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
