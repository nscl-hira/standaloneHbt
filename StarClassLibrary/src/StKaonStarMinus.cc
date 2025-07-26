/***************************************************************************
 *
 * $Id: StKaonStarMinus.cc,v 1.1 1999/05/14 18:47:51 ullrich Exp $
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
 * $Log: StKaonStarMinus.cc,v $
 * Revision 1.1  1999/05/14 18:47:51  ullrich
 * Initial Revision
 *
 **************************************************************************/
#include "StKaonStarMinus.hh" 
#include "PhysicalConstants.h"

StKaonStarMinus::StKaonStarMinus(const string  &  aName,  
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
			 double           lifetime)
    : StMeson(aName, mass, width, charge, iSpin, iParity,
	      iConjugation, iIsospin, iIsospinZ, gParity,
	      pType, lepton, baryon, encoding, stable,
	      lifetime) {/* noop */}

// ......................................................................
// ...                 static member definitions                      ...
// ......................................................................
//     
//    Arguments for constructor are as follows
//               name             mass          width         charge
//             2*spin           parity  C-conjugation
//          2*Isospin       2*Isospin3       G-parity
//               type    lepton number  baryon number   PDG encoding
//             stable         lifetime   
//
StKaonStarMinus StKaonStarMinus::mKaonStarMinus(
	      "kaonStar-",    0.89166*GeV,       50.8*MeV,    -1.*eplus, 
		    2,              -1,             0,          
		    1,              -1,             0,             
	      "meson",               0,             0,        -323,
		false,       0.0*nanosecond
);
