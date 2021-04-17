#include "PrimaryGeneratorAction.hh"

#include "DetectorConstruction.hh"
#include "G4ParticleGun.hh"
#include "G4Event.hh" 
#include "G4ParticleTable.hh"
#include <math.h>



PrimaryGeneratorAction::PrimaryGeneratorAction(DetectorConstruction* det)
:   G4VUserPrimaryGeneratorAction(),
    fDetector(det),
    fParticleGun(nullptr){
    
    G4int nParticle = 1;
    fParticleGun = new G4ParticleGun(nParticle);
    SetDefaultKinematic();
}


PrimaryGeneratorAction::~PrimaryGeneratorAction() {
    delete fParticleGun;
}


void PrimaryGeneratorAction::GeneratePrimaries(G4Event* evt) {
	fParticleGun->GeneratePrimaryVertex(evt);
}


void PrimaryGeneratorAction::SetDefaultKinematic() {
//
// default primary particle: 30 [MeV] e- perpendicular to the target
   G4ParticleDefinition* part = G4ParticleTable::GetParticleTable()->FindParticle( "e-" );
   fParticleGun->SetParticleDefinition( part );
   fParticleGun->SetParticleMomentumDirection( G4ThreeVector(1., 0., 0.) );
   fParticleGun->SetParticleEnergy( 30.*CLHEP::MeV );
   UpdatePosition();
}


// needs to be invoked for all workers at the begining of the run: user might 
// have changed the target thickness
void PrimaryGeneratorAction::UpdateDefinition(G4String partname){
   G4ParticleDefinition* part = G4ParticleTable::GetParticleTable()->FindParticle( partname );
   fParticleGun->SetParticleDefinition( part );
}

void PrimaryGeneratorAction::UpdatePosition() {
    fParticleGun->SetParticlePosition( 
        G4ThreeVector( fDetector->GetGunXPosition(), 0, 0 ) );
}


const G4String& PrimaryGeneratorAction::GetParticleName() const {
	return fParticleGun->GetParticleDefinition()->GetParticleName();
}


G4double PrimaryGeneratorAction::GetParticleEnergy() const {
	return fParticleGun->GetParticleEnergy();
}

