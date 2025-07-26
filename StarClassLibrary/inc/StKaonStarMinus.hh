/***************************************************************************
 *
 * $Id: StKaonStarMinus.hh,v 1.1 1999/05/14 18:49:34 ullrich Exp $
 *
 * Author: Frank Laue, laue@bnl.gov, 07/29/04 
 ***************************************************************************
 *
 * The design of the StParticleDefinition class and all concrete
 * classes derived from it is largely based on the design of the 
 * G4ParticleDefinition class from Geant4 (RD44).
 * Although the code is in large parts different (modified or rewritten)
 * and adapted to the STAR framework the basic idea stays the same.
 *
 ***************************************************************************
 *
 * $Log: StKaonStarMinus.hh,v $
 * Revision 1.1  1999/05/14 18:49:34  ullrich
 * Initial Revision
 *
 **************************************************************************/
#ifndef StKaonStarMinus_hh
#define StKaonStarMinus_hh

#include "StMeson.hh"

class StKaonStarMinus : public StMeson {
public:
    static StKaonStarMinus* instance() {return &mKaonStarMinus;}
    static StKaonStarMinus* KaonStarMinus() {return &mKaonStarMinus;}
    
private:
    static StKaonStarMinus mKaonStarMinus;
    
    StKaonStarMinus(const string  &  aName,  
		double           mass,     
		double           width,
		double           charge,   
		int              iSpin,
		int              iParity,
		int              iConjugation,
		int              iIsospin,   
		int              iIsospinZ, 
		int              gParity,
		const string  &  pType,
		int              lepton,
		int              baryon,
		int              encoding,
		bool             stable,
		double           lifetime);
};

#endif
