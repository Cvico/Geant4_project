#include "DetectorMessenger.hh"
#include "G4UIdirectory.hh"


DetectorMessenger::DetectorMessenger(DetectorConstruction* det)
:   G4UImessenger(),
    fDetector(det),
    fDirCMD(nullptr),
    fTargetThicknessCMD(nullptr),
    fTargetMaterialCMD(nullptr){
        fDirCMD = new G4UIdirectory("/App/det/");
        fDirCMD->SetGuidance("UI commands specific to the detector construction");

        fTargetThicknessCMD = new G4UIcmdWithADoubleAndUnit("/App/det/setTargetThickness", this);
        fTargetThicknessCMD->SetGuidance("Sets the thickness of the target");
	fTargetThicknessCMD->SetParameterName("TargetSizeX", false);
	fTargetThicknessCMD->SetRange("TargetSizeX>0.");
	fTargetThicknessCMD->SetUnitCategory("Length");
	fTargetThicknessCMD->AvailableForStates(G4State_PreInit, G4State_Idle);
	fTargetThicknessCMD->SetToBeBroadcasted(false);

        fTargetMaterialCMD = new G4UIcmdWithAString("/App/det/setTargetMaterial", this);
        fTargetMaterialCMD->SetGuidance("Sets the material of the target.");
	fTargetMaterialCMD->SetParameterName("TargetMaterial", false);
	fTargetMaterialCMD->AvailableForStates(G4State_PreInit, G4State_Idle);
    }

DetectorMessenger::~DetectorMessenger(){
    delete fTargetThicknessCMD;
    delete fTargetMaterialCMD;
    delete fDirCMD;
}

void DetectorMessenger::SetNewValue(G4UIcommand* cmd, G4String value){
    if (cmd == fTargetThicknessCMD) {
        G4double thickness = fTargetThicknessCMD->GetNewDoubleValue(value);
        fDetector->setTargetThickness(thickness);
    } 
    if (cmd == fTargetMaterialCMD) {
        fDetector->setTargetMaterial(value);
    }
}
