#ifndef EVENTACTION_HH
#define EVENTACTION_HH

#include "G4UserEventAction.hh"
#include "globals.hh"
/**
 * @brief It defines data members to hold the energy deposit and 
 * @brief track lengths of charged particles in the Absorber and Gap layers. 
 * @brief In EndOfEventAction(), these quantities are printed and filled in 
 * @brief H1D histograms and ntuple to accumulate statistic and compute 
 * @brief dispersion.
 */
class EventAction : public G4UserEventAction {

  // Method declaration:
  public:
    
    // CTR: 
    EventAction();
    virtual ~EventAction();

    // Two virtual method called at the beginning and at the end of each event 
    virtual void BeginOfEventAction(const G4Event* anEvent);
    virtual void EndOfEventAction(const G4Event* anEvent);

    // Public method (used by the SteppingAction) to add energy deposit and 
    // charged particle track length information to this object after each step.
    void Add(G4double edep, G4double trackL) {
      fEdepPerEvt += edep;
      fChTrackLengthPerEvt += trackL;
    }

  // Data member declarations:
  private:
    G4double   fEdepPerEvt;
    G4double   fChTrackLengthPerEvt;

};


#endif