#ifndef PRIMARYGENERATORACTION_HH
#define PRIMARYGENERATORACTION_HH

#include "G4VUserPrimaryGeneratorAction.hh"
#include "globals.hh"
#include "G4ParticleMomentum.hh"
// forward declaration
class DetectorConstruction;
class G4ParticleGun;
class G4Event;
class G4String;

/**
 * @brief G4VuserPrimaryGeneratorAction is one of the mandatory classes available for deriving your own concrete class. 
 * @brief In your concrete class, you have to specify how a primary event should be generated. Actual generation of 
 * @brief primary particles will be done by concrete classes of G4VPrimaryGenerator, explained in the following sub-section. 
 * @brief Your G4VUserPrimaryGeneratorAction concrete class just arranges the way primary particles are generated.
 */

class PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction {
  // Method declaration:
  public:
    PrimaryGeneratorAction(DetectorConstruction* det);
    virtual ~PrimaryGeneratorAction();

    virtual void   GeneratePrimaries(G4Event*);

    // Additional custom methods: 
    // Getters
    G4ParticleGun*  GetParticleGun() { return fParticleGun; }
    const G4String& GetParticleName() const;
    G4double        GetParticleEnergy() const;

    // Setters-kindof

    void SetDefaultKinematic();
    void UpdateDefinition(G4String partname);
    void UpdateMomentum(G4double momentum);
    void UpdateMomentumDirection(G4ThreeVector momentumDir);
    void UpdateEnergy(G4double partEnergy);
    void UpdatePosition();
    void UpdateNumberOfParticles(G4int nparticles);



  // Data member declarations:
  private:
  	DetectorConstruction* fDetector;
    G4ParticleGun*        fParticleGun; 
    G4ParticleMomentum fMomentum;
    G4ThreeVector fMomentumDir;
    G4double fPartEnergy;
    G4ThreeVector fPartPosition;
    G4int fNparticles;
};

#endif
