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
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4VPhysicalVolume.hh"
#include "G4PVPlacement.hh"


/*  FOR RUNNING IN MULTITHREAD MODE 

    Geant4 multithread mode is set at installing step, so only
    those who have installed multithread mode will be able to run
    in multithread mode. Comment or uncomment if you want to switch 
    between multithread or sequential modes. 

    You will also have to comment/uncomment the lines regarding
    multithreading in the main() function.
*/

// Comment lines from 34-37 and 39 if you want to go sequential
#ifdef G4MULTITHREADED
#include "G4MTRunManager.hh"
#else
#include "G4RunManager.hh"
#endif


int main(int argc, char** argv){
    // Choose the random engine:
    CLHEP::HepRandom::setTheEngine(new CLHEP::RanecuEngine);
    
    // Detect interactive mode (if no arguments) and define UI: 
    G4UIExecutive* ui=0;
    if (argc == 1 ){
        ui = new G4UIExecutive(argc, argv, "qt");
    }

    // Comment lines from 34-37 and 39 if you want to go sequential
    #ifdef G4MULTITHREADED
    G4MTRunManager* runManager = new G4MTRunManager;
    runManager->SetNumberOfThreads(9);
    #else
    G4RunManager* runManager = new G4RunManager;
    #endif    

    // Build your detector
    //DetectorConstruction* detector = new DetectorConstruction();
    CalorimeterConstruction* detector = new CalorimeterConstruction();
    // Initialize the runManager 
    runManager->SetUserInitialization( detector );

    // Create/obtain a Physics List and register it in the Run-Manager
    G4PhysListFactory physListFactory;
    const G4String plName = "FTFP_BERT";
    G4VModularPhysicsList* pl = physListFactory.GetReferencePhysList( plName );
    runManager->SetUserInitialization( pl ); 
    runManager->SetUserInitialization( new CalorimeterActionInitialization() );
    //runManager->SetUserInitialization( new ActionInitialization(detector) );

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
    
    // Initialize the runManager
//    runManager->Initialize();
    
    delete runManager;
    delete visManager;
    
}
