#ifndef DETECTORMESSENGER_HH
#define DETECTORMESSENGER_HH

#include "G4UImessenger.hh"
#include "DetectorConstruction.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithAString.hh"

class DetectorConstruction;
class G4UIdirectory;
class G4UIcmdWithADoubleAndUnit;
class G4UIcmdWithAString;
class G4String;


class DetectorMessenger : public G4UImessenger {
    public:
        DetectorMessenger(DetectorConstruction* det);
        ~DetectorMessenger();

        virtual void SetNewValue(G4UIcommand* cmd, G4String value);
    private:
        DetectorConstruction*      fDetector;
        G4UIdirectory*             fDirCMD;
        G4UIcmdWithADoubleAndUnit* fTargetThicknessCMD;
        G4UIcmdWithAString*        fTargetMaterialCMD;
};

#endif
