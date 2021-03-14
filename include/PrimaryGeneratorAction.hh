#ifndef PRIMARYGENERATORACTION_HH
#define PRIMARYGENERATORACTION_HH

#include "G4VUserPrimaryGeneratorAction.hh"

#include "globals.hh"

// forward declaration
class DetectorConstruction;
class G4ParticleGun;
class G4Event;
class G4String;


class PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction {

  // Method declaration:
  public:
    
    // CTR & DTR
    PrimaryGeneratorAction(DetectorConstruction* det);
    virtual ~PrimaryGeneratorAction();

    // (Pure) virtual method to generata primary events
    virtual void   GeneratePrimaries(G4Event*);

    //
    // Additional custom methods: 

    // Public method to obtain the G4ParticleGun object pointer and some other 
    // primary particle realted values
    G4ParticleGun*  GetParticleGun() { return fParticleGun; }

    // Public method to get the primary particle name.
    const G4String& GetParticleName() const;

    // Public method to get the primary particle kinetic energy.
    G4double        GetParticleEnergy() const;

    // Public method to set the default primary particle kinematics
    void            SetDefaultKinematic();

    // Public method to set the position of the particle gun: will be taken for
    // the actual detector construction
    void            UpdatePosition();


  // Data member declarations:
  private:

  	DetectorConstruction* fDetector;

  	G4ParticleGun*            fParticleGun; 

};

#endif