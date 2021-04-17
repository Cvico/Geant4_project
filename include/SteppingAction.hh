#ifndef STEPPINGACTION_HH
#define STEPPINGACTION_HH

#include "G4UserSteppingAction.hh"

// forward declarations
class DetectorConstruction;
class EventAction;
class G4VPhysicalVolume;

class SteppingAction : public G4UserSteppingAction {

  // Method declaration:
  public:
    
    // CTR: 
    //  - detector construction object is used to find out the target volume
    //  - event action is used to fill per-event cumulative values 
    SteppingAction(DetectorConstruction* det, EventAction* evtAction);
    virtual ~SteppingAction();

    // Virtual method called by the kernel after each step
    virtual void UserSteppingAction(const G4Step* step);

    

  // Data member declarations:
  private:

  	DetectorConstruction*    fDetector;

  	EventAction*             fEventAction;
};

#endif