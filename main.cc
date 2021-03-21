// ================================== //
//    Author: Carlos Vico Villalba    //
// ================================== //


#include <iostream>
#include "G4Types.hh"
#include "globals.hh"
#include "G4RunManager.hh"
#include "G4PhysListFactory.hh"
#include "DetectorConstruction.hh"
#include "ActionInitialization.hh"
#include "G4UImanager.hh"
#include "G4Material.hh"
#include "G4NistManager.hh"
#include "G4UIExecutive.hh"
#include "G4VisExecutive.hh"
#include "G4VisManager.hh"
#include "Materials.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4VPhysicalVolume.hh"
#include "G4PVPlacement.hh"




void importMaterials(Materials* obj){
    // Import all the materials we want to have available for detector
    // construction. Define here the materials

    //  -- See: http://www.apc.univ-paris7.fr/~franco/g4doxy/html/classG4Material.html
    //  for more information on different constructors.
    obj->addMaterial("G4_Al");
    obj->addMaterial("G4_Si");
    obj->addMaterial(new G4Material("Uranium", 92., 238.03*CLHEP::g/CLHEP::mole, 18.950*CLHEP::g/CLHEP::cm3));
    obj->addMaterial(new G4Material("air", 1.290*CLHEP::mg/CLHEP::cm3, 2));
    obj->addMaterial(new G4Material("aerogel", 0.2*CLHEP::g/CLHEP::cm3, 3));
    obj->addMaterial("G4_lAr");
    obj->addMaterial("G4_CONCRETE");

    //  -- See: http://www.apc.univ-paris7.fr/~franco/g4doxy/html/classG4Element.html
    //  for more information on different constructors.
    obj->addElement(new G4Element("Nytrogen", "N", 7.0, 14.0067*CLHEP::g/CLHEP::mole));
    obj->addElement(new G4Element("Oxygen", "O", 8.0, 16.0*CLHEP::g/CLHEP::mole));
    obj->addElement(new G4Element("Hydrogen", "H", 1.0, 1.01*CLHEP::g/CLHEP::mole));

    //  -- See: http://www.apc.univ-paris7.fr/~franco/g4doxy/html/classG4Isotope.html
    //  for more information on different constructors.

    return;
}


int main(int argc, char** argv){

    // Choose the random engine:
    CLHEP::HepRandom::setTheEngine(new CLHEP::RanecuEngine);
    
    // Detect interactive mode (if no arguments) and define UI: 
    G4UIExecutive* ui=0;
    if (argc ==1 ){
        ui = new G4UIExecutive(argc, argv, "tcsh");
    }
    
    // initialize the runManager
    G4RunManager* runManager = new G4RunManager();
    
    // Build your detector
    DetectorConstruction* detector = new DetectorConstruction();

    // Initialize the runManager 
    runManager->SetUserInitialization( detector );

    // Create/obtain a Physics List and register it in the Run-Manager
    G4PhysListFactory physListFactory;
    const G4String plName = "FTFP_BERT";
    G4VModularPhysicsList* pl = physListFactory.GetReferencePhysList( plName );
    runManager->SetUserInitialization( pl ); 

    // Set User action classes
    runManager->SetUserInitialization( new ActionInitialization(detector) );
    // Initialize the visualisation manager:
    G4VisManager* visManager = new G4VisExecutive;
    visManager->Initialize();
    
      // Detect batch-mode: 
    G4UImanager* UImanager = G4UImanager::GetUIpointer();
    if ( argc != 1 ) {
        G4String cmd = "/control/execute ";
        G4String scmd = argv[1];
        UImanager->ApplyCommand(cmd + scmd);
    } else {
    UImanager->ApplyCommand("/control/execute vis.mac");
    ui->SessionStart();
    delete ui;
    }
    
    // Initialize the runManager
    runManager->Initialize();

    //G4EventManager::GetEventManager()->GetTrackingManager()->SetVerboseLevel(1);
    //runManager->BeamOn(10);

    
    delete runManager;
    delete visManager;
    
}
