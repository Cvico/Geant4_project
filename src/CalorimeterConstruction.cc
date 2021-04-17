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

#include "CalorimeterConstruction.hh"

#include "G4Material.hh"
#include "G4NistManager.hh"

#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4PVReplica.hh"
#include "G4GlobalMagFieldMessenger.hh"
#include "G4AutoDelete.hh"

#include "G4SDManager.hh"
#include "G4SDChargedFilter.hh"
#include "G4MultiFunctionalDetector.hh"
#include "G4VPrimitiveScorer.hh"
#include "G4PSEnergyDeposit.hh"
#include "G4PSTrackLength.hh"

#include "G4VisAttributes.hh"
#include "G4Colour.hh"

#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4ThreadLocal 
G4GlobalMagFieldMessenger* CalorimeterConstruction::fMagFieldMessenger = 0; 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

CalorimeterConstruction::CalorimeterConstruction()
 : G4VUserDetectorConstruction(),
   fCheckOverlaps(false)
{
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

CalorimeterConstruction::~CalorimeterConstruction()
{ 
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* CalorimeterConstruction::Construct()
{
  // Define materials 
  DefineMaterials();
  
  // Define volumes
  return DefineVolumes();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void CalorimeterConstruction::DefineMaterials()
{ 
  // Lead material defined using NIST Manager


  // Use tin for CMS' HCAL
  auto nistManager = G4NistManager::Instance();
  nistManager->FindOrBuildMaterial("G4_Sn");
  
  // Liquid argon material
  G4double a;  // mass of a mole;
  G4double z;  // z=mean number of protons;  
  G4double density; 
  G4Material* PbWO4 = new G4Material("PbWO4", density= 8.28*g/cm3, 3);
  
  // Define lead tungstate to simulate CMS' ECAL
  PbWO4->AddElement(new G4Element("Lead", "Pb",  82.0, 207.2*CLHEP::g/CLHEP::mole), 1);
  PbWO4->AddElement(new G4Element("Wolframium", "W", 74.0, 183.84*CLHEP::g/CLHEP::mole), 1);
  PbWO4->AddElement(new G4Element("Oxygen", "O", 8.0, 16.0*CLHEP::g/CLHEP::mole), 4);

  // Vacuum
  new G4Material("Galactic", z=1., a=1.01*g/mole,density= universe_mean_density,
                  kStateGas, 2.73*kelvin, 3.e-18*pascal);

  // Print materials
  G4cout << *(G4Material::GetMaterialTable()) << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* CalorimeterConstruction::DefineVolumes()
{
  // I don't want to use a GAP
  // Geometry parameters

  G4int  nofLayers = 1; // 

  G4double  absoThickness = 10.*mm;
  fabsoThickness = absoThickness; // Save it in data-member
  G4double  ecalSizeXY  = 10.*cm;
  G4double  hcalSizeXY  = 10.*cm;

  //auto  layerThickness = absoThickness;
  auto ECALthickness = 0.3*absoThickness;
  auto HCALthickness = 0.7*absoThickness;
  
  auto worldSizeX = 1.2 * absoThickness;
  auto worldSizeYZ  = 1.2 * absoThickness; 
  fworldSizeX = worldSizeX;
  fworldSizeYZ = worldSizeYZ;
  
  // Get materials
  auto worldMaterial = G4Material::GetMaterial("Galactic");
  auto HCALMaterial = G4Material::GetMaterial("G4_Sn");
  auto ECALMaterial = G4Material::GetMaterial("PbWO4");
  
  if ( ! worldMaterial || ! HCALMaterial || ! ECALMaterial ) {
    G4ExceptionDescription msg;
    msg << "Cannot retrieve materials already defined."; 
    G4Exception("CalorimeterConstruction::DefineVolumes()",
      "MyCode0001", FatalException, msg);
  }  
   
  //     
  // World
  //
  auto worldS 
    = new G4Box("World",           // its name
                 worldSizeX/2, worldSizeYZ/2, worldSizeYZ/2); // its size
                         
  auto worldLV
    = new G4LogicalVolume(
                 worldS,           // its solid
                 worldMaterial,  // its material
                 "World");         // its name
                                   
  auto worldPV
    = new G4PVPlacement(
                 0,                // no rotation
                 G4ThreeVector(),  // at (0,0,0)
                 worldLV,          // its logical volume                         
                 "World",          // its name
                 0,                // its mother  volume
                 false,            // no boolean operation
                 0,                // copy number
                 fCheckOverlaps);  // checking overlaps 
  
  //                               
  // Calorimeters (absorbers)
  //  
  // =========== ECAL ============
  auto ECAL
    = new G4Box("ECAL",     // its name
                 ecalSizeXY/2, ecalSizeXY/2, ecalSizeXY/2); // its size
                         
  auto ECALLV
    = new G4LogicalVolume(
                 ECAL,    // its solid
                 ECALMaterial, // its material
                 "ECAL");  // its name
                                   
  new G4PVPlacement(
                 0,                // no rotation
                 G4ThreeVector(),  // at (0,0,0)
                 ECALLV,          // its logical volume                         
                 "ECAL",    // its name
                 worldLV,          // its mother  volume
                 false,            // no boolean operation
                 0,                // copy number
                 fCheckOverlaps);  // checking overlaps 
  
  
  // =========== ECAL ============
  auto HCAL
    = new G4Box("HCAL",     // its name
                 hcalSizeXY/2, hcalSizeXY/2, hcalSizeXY/2); // its size
                         
  auto HCALLV
    = new G4LogicalVolume(
                 HCAL,    // its solid
                 HCALMaterial, // its material
                 "HCAL");  // its name
                                   
  new G4PVPlacement(
                 0,                // no rotation
                 G4ThreeVector(),  // at (0,0,0)
                 HCALLV,          // its logical volume                         
                 "HCAL",    // its name
                 worldLV,          // its mother  volume
                 false,            // no boolean operation
                 0,                // copy number
                 fCheckOverlaps);  // checking overlaps 
  //
  // print parameters
  //
  G4cout
    << G4endl 
    << "------------------------------------------------------------" << G4endl
    << "---> The calorimeter is " << nofLayers << " layers of:  " << G4endl
    << ECALthickness/mm << "mm of " << ECALMaterial->GetName()  
    << " and " 
    << HCALthickness/mm << "mm of " << HCALMaterial->GetName() << G4endl
    << "------------------------------------------------------------" << G4endl;
  
  //                                        
  // Visualization attributes
  //
  worldLV->SetVisAttributes (G4VisAttributes::GetInvisible());

  auto simpleBoxVisAtt= new G4VisAttributes(G4Colour(1.0,1.0,1.0));
  simpleBoxVisAtt->SetVisibility(true);
  ECALLV->SetVisAttributes(simpleBoxVisAtt);
  HCALLV->SetVisAttributes(simpleBoxVisAtt);

  //
  // Always return the physical World
  //
  return worldPV;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void CalorimeterConstruction::ConstructSDandField()
{
  G4SDManager::GetSDMpointer()->SetVerboseLevel(1);
  // 
  // Scorers
  //

  // declare ECAL as a MultiFunctionalDetector scorer
  //  
  setGunXPosition(-0.25*(fworldSizeX + fabsoThickness));  
  auto ECALDetector = new G4MultiFunctionalDetector("ECAL");
  G4SDManager::GetSDMpointer()->AddNewDetector(ECALDetector);

  G4VPrimitiveScorer* primitive;
  primitive = new G4PSEnergyDeposit("Edep");
  ECALDetector->RegisterPrimitive(primitive);

  primitive = new G4PSTrackLength("TrackLength");
  auto charged = new G4SDChargedFilter("chargedFilter");
  primitive ->SetFilter(charged);
  ECALDetector->RegisterPrimitive(primitive);  

  SetSensitiveDetector("ECAL",ECALDetector);
  
  // declare HCAL as a MultiFunctionalDetector scorer
  //  
  auto HCALDetector = new G4MultiFunctionalDetector("HCAL");
  G4SDManager::GetSDMpointer()->AddNewDetector(HCALDetector);

  primitive = new G4PSEnergyDeposit("Edep");
  HCALDetector->RegisterPrimitive(primitive);

  primitive = new G4PSTrackLength("TrackLength");
  primitive ->SetFilter(charged);
  HCALDetector->RegisterPrimitive(primitive);  

  SetSensitiveDetector("HCAL",HCALDetector);
  // 
  // Magnetic field
  //
  // Create global magnetic field messenger.
  // Uniform magnetic field is then created automatically if
  // the field value is not zero.
  G4ThreeVector fieldValue;
  fMagFieldMessenger = new G4GlobalMagFieldMessenger(fieldValue);
  fMagFieldMessenger->SetVerboseLevel(1);
  
  // Register the field messenger for deleting
  G4AutoDelete::Register(fMagFieldMessenger);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
