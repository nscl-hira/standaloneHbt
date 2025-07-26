/***************************************************************************
 *
 * $Id: StAntiKaonStarZero.hh,v 1.1 1999/05/14 18:49:36 ullrich Exp $
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
 * $Log: StAntiKaonStarZero.hh,v $
 * Revision 1.1  1999/05/14 18:49:36  ullrich
 * Initial Revision
 *
 **************************************************************************/
#ifndef StAntiKaonStarZero_hh
#define StAntiKaonStarZero_hh

#include "StMeson.hh"

class StAntiKaonStarZero : public StMeson {
public:
    static StAntiKaonStarZero* instance() {return &mAntiKaonStarZero;}
    static StAntiKaonStarZero* antiKaonStarZero() {return &mAntiKaonStarZero;}
    
private:
    static StAntiKaonStarZero mAntiKaonStarZero;
    
    StAntiKaonStarZero(const string  &  aName,  
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
