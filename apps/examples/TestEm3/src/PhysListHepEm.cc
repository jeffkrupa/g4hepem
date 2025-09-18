
#include "PhysListHepEm.hh"

// include the G4HepEmProcess from the G4HepEm lib.
#include "G4HepEmProcess.hh"

#include "G4StopGradAlong.hh"             


#include "G4ParticleDefinition.hh"
#include "G4ProcessManager.hh"
#include "G4PhysicsListHelper.hh"
#include "G4EmParameters.hh"
#include "G4BuilderType.hh"
#include "G4SystemOfUnits.hh"


PhysListHepEm::PhysListHepEm(const G4String& name)
: G4VPhysicsConstructor(name) {
  G4EmParameters* param = G4EmParameters::Instance();
  param->SetDefaults();

  param->SetMscRangeFactor(0.04);

  SetPhysicsType(bElectromagnetic);
}


PhysListHepEm::~PhysListHepEm() {}
/*
void PhysListHepEm::ConstructProcess() {
  G4PhysicsListHelper* ph = G4PhysicsListHelper::GetPhysicsListHelper();

  // Single HepEm process shared across e-/e+/gamma
  G4HepEmProcess* hepEmProcess = new G4HepEmProcess();

  auto aParticleIterator = GetParticleIterator();
  aParticleIterator->reset();
  while ((*aParticleIterator)()) {
    G4ParticleDefinition* particle = aParticleIterator->value();
    const G4String& particleName = particle->GetParticleName();
    G4ProcessManager* pm = particle->GetProcessManager();

    if (particleName == "gamma") {
      pm->AddProcess(hepEmProcess, -1, -1, 1);

      // If you also want the fix for gammas, set includeGammas=true
      // auto* fixG = new G4StopGradAlong("StopGradAlong", 1e-1, true);
      // pm->AddProcess(fixG, -1, 1, -1);
      // pm->SetProcessOrderingToFirst(fixG, idxAlongStep);

    } else if (particleName == "e-") {
      pm->AddProcess(hepEmProcess, -1, -1, 1);

      auto* fixE = new G4StopGradAlong("StopGradAlong", 1e-1, false);
      pm->AddProcess(fixE, -1, 1, -1);                 // Along-step slot
      pm->SetProcessOrderingToFirst(fixE, idxAlongStep); // Make it FIRST

    } else if (particleName == "e+") {
      pm->AddProcess(hepEmProcess, -1, -1, 1);

      auto* fixP = new G4StopGradAlong("StopGradAlong", 1e-1, false);
      pm->AddProcess(fixP, -1, 1, -1);
      pm->SetProcessOrderingToFirst(fixP, idxAlongStep);
    }
  }
}
*/

void PhysListHepEm::ConstructProcess() {
  G4PhysicsListHelper* ph = G4PhysicsListHelper::GetPhysicsListHelper();

  // creae the only one G4HepEm process that will be assigned to e-/e+ and gamma
  G4HepEmProcess* hepEmProcess = new G4HepEmProcess();

  // Add standard EM Processes
  //
  auto aParticleIterator = GetParticleIterator();
  aParticleIterator->reset();
  while( (*aParticleIterator)() ){
    G4ParticleDefinition* particle = aParticleIterator->value();
    G4String particleName = particle->GetParticleName();

    if (particleName == "gamma") {

      // Add G4HepEm process to gamma: includes Conversion, Compton and photoelectric effect.
      particle->GetProcessManager()->AddProcess(hepEmProcess, -1, -1, 1);

    } else if (particleName == "e-") {

      // Add G4HepEm process to e-: includes Ionisation, Bremsstrahlung, MSC for e-
     particle->GetProcessManager()->AddProcess(hepEmProcess, -1, -1, 1);

    } else if (particleName == "e+") {

      // Add G4HepEm process to e+: includes Ionisation, Bremsstrahlung, MSC and e+e-
      // annihilation into 2 gamma interactions for e+
      particle->GetProcessManager()->AddProcess(hepEmProcess, -1, -1, 1);

    }
  }
}
