// ================================== //
//    Author: Carlos Vico Villalba    //
// ================================== //
#include <iostream>
#include "G4Types.hh"
#include "globals.hh"
#include "G4PhysListFactory.hh"
#include "CalorimeterActionInitialization.hh"
#include "DetectorConstruction.hh"
#include "CalorimeterConstruction.hh"
#include "ActionInitialization.hh"
#include "G4UImanager.hh"
#include "G4Material.hh"
#include "G4NistManager.hh"
#include "G4UIExecutive.hh"
#include "G4VisExecutive.hh"
#include "G4VisManager.hh"



// ------------------------------------
#include "G4MTRunManager.hh"
#include "G4RunManager.hh"
// ------------------------------------



template <typename manager>
void loadPhysicsList(manager* runManager);
template <typename manager>
void runSimulation(manager* runManager, int useDetector, int argc, char** argv, std::string visType);


int main(int argc, char** argv){
    // ---
    // Detector = 1 --> Meroli's
    // Detector = 2 --> Calorimeters
    std::string visType = "tcsh";
    int useDetector = 2;
    bool useMultithread = true;
    int nThreads = 8;

    if (useMultithread){
        G4MTRunManager* runManager = new G4MTRunManager; 
        runManager->SetNumberOfThreads(nThreads);
        runSimulation(runManager, useDetector, argc, argv, visType);
        }

    else{ 
        G4RunManager* runManager = new G4RunManager;
        runSimulation(runManager, useDetector, argc, argv, visType);
        }
    
}

template <typename manager>
void runSimulation(manager* runManager, int useDetector, int argc, char** argv, std::string visType){
    // Choose the random engine:
    CLHEP::HepRandom::setTheEngine(new CLHEP::RanecuEngine);
    
    // Detect interactive mode (if no arguments) and define UI: 
    G4UIExecutive* ui=0;
    if (argc == 1 ){
        ui = new G4UIExecutive(argc, argv, visType);
    }

    if ( useDetector == 1){ 
        DetectorConstruction* detector = new DetectorConstruction(); 
        runManager->SetUserInitialization( detector );
        loadPhysicsList(runManager);    
        runManager->SetUserInitialization( new ActionInitialization(detector) );
        } else { 
        CalorimeterConstruction* detector = new CalorimeterConstruction(); 
        runManager->SetUserInitialization( detector );
        loadPhysicsList(runManager);    
        runManager->SetUserInitialization( new CalorimeterActionInitialization() );
        }
    
    // Handle visualization
    G4VisManager* visManager = new G4VisExecutive;
    visManager->Initialize();
    
    // Detect batch-mode: 
    G4UImanager* UImanager = G4UImanager::GetUIpointer();
    UImanager->ApplyCommand("/control/macroPath ../macros/");
    if ( !ui ) {
        G4String cmd = "/control/execute ";
        G4String scmd = argv[1];
        UImanager->ApplyCommand(cmd + scmd);
    } else {
    UImanager->ApplyCommand("/control/execute init_vis.mac");
    ui->SessionStart();
    delete ui;
    }
    
    delete runManager;
    delete visManager;
}

template <typename manager>
void loadPhysicsList(manager* runManager){
    // Create/obtain a Physics List and register it in the Run-Manager
    G4PhysListFactory physListFactory;
    G4VModularPhysicsList* pl = physListFactory.GetReferencePhysList( "FTFP_BERT" );
    runManager->SetUserInitialization( pl ); 
}
