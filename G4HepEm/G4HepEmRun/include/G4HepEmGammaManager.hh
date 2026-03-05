#include "ad_type.h"

#ifndef G4HepEmGammaManager_HH
#define G4HepEmGammaManager_HH

#include "G4HepEmMacros.hh"

struct G4HepEmData;
struct G4HepEmParameters;
struct G4HepEmGammaData;

class  G4HepEmTLData;
class  G4HepEmGammaTrack;
class  G4HepEmTrack;

/**
 * @file    G4HepEmGammaManager.hh
 * @struct  G4HepEmGammaManager
 * @author  M. Novak
 * @date    2021
 *
 * @brief The top level run-time manager for \f$\gamma\f$ transport simulations.
 *
 * It will be the same for \f$\gamma\f$ as the G4HepEmElectronManager for e-/e+.
 */

class G4HepEmGammaManager {
private:
  G4HepEmGammaManager() = delete;

public:
  // step length
  static void HowFar(struct G4HepEmData* /*hepEmData*/, struct G4HepEmParameters* /*hepEmPars*/, G4HepEmTLData* /*tlData*/, int numStep);

  G4HepEmHostDevice
  static void HowFar(struct G4HepEmData* hepEmData, struct G4HepEmParameters* hepEmPars, G4HepEmGammaTrack* theTrack, int numStep);


  // interactions
  static void Perform(struct G4HepEmData* /*hepEmData*/, struct G4HepEmParameters* /*hepEmPars*/, G4HepEmTLData* /*tlData*/);

  G4HepEmHostDevice
  static void UpdateNumIALeft(G4HepEmTrack* theTrack);

  /** Configure derivative-only regularization for gamma UpdateNumIALeft.
    *
    * @param mfpFloor denominator floor [mm] used only in derivative coefficients.
    *                 Set to 0 to disable regularization.
    */
  static void ConfigureNumIALeftDerivativeRegularization(G4double mfpFloor);

  /** Configure derivative-only regularization for gamma photoelectric 1/E terms.
    *
    * @param ekinFloor denominator floor [MeV] used only in derivative coefficients
    *                  of 1/ekin in GetMacXSecPE. Set to 0 to disable.
    */
  static void ConfigurePhotoelectricDerivativeRegularization(G4double ekinFloor);
  

  G4HepEmHostDevice
  static G4double GetMacXSec(const struct G4HepEmGammaData* gmData, const int imat, const G4double ekin,
                            const G4double lekin, const int iprocess);

  G4HepEmHostDevice
  static G4double GetMacXSecPE(const struct G4HepEmData* hepEmData, const int imat, const G4double ekin);

};

#endif // G4HepEmGammaManager_HH
