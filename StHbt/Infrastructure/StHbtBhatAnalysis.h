/***************************************************************************
 *
 * $Id: StHbtBhatAnalysis.h,v 1.5 2002/11/03 16:37:43 magestro Exp $
 *
 * Author: Frank Laue, Ohio State, laue@mps.ohio-state.edu
 ***************************************************************************
 *
 * Description: part of STAR HBT Framework: StHbtMaker package
 *      This is the Class for Analysis objects.  Each of the simultaneous
 *      Analyses running should have one of these instantiated.  They link
 *      into the Manager in an Analysis Collection.
 *
 ***************************************************************************
 *
 * $Log: StHbtBhatAnalysis.h,v $
 * Revision 1.5  2002/11/03 16:37:43  magestro
 * Moved StHbtPicoEventCollectionVectorHideAway object to StHbtAnalysis for circular event-mixing
 *
 * Revision 1.4  2000/08/31 22:31:32  laue
 * StHbtAnalysis: output changed (a little bit less)
 * StHbtEvent: new version, members for reference mult added
 * StHbtIOBinary: new IO for new StHbtEvent version
 * StHbtTypes: TTree typedef to StHbtTTree added
 * StHbtBhatAnalysis: overflow and underflow added
 *
 * Revision 1.1  2000/07/16 21:44:11  laue
 * Collection and analysis for vertex dependent event mixing
 *
 *
 **************************************************************************/

#ifndef StHbtBhatAnalysis_hh
#define StHbtBhatAnalysis_hh

#include "Infrastructure/StHbtAnalysis.h"        // base analysis class

class StHbtBhatAnalysis : public StHbtAnalysis {

public:

  StHbtBhatAnalysis(unsigned int =10, double =0., double=1.);
  StHbtBhatAnalysis(const StHbtBhatAnalysis&);  // copy constructor
  virtual void ProcessEvent(const StHbtEvent*);
  virtual ~StHbtBhatAnalysis();
  virtual StHbtString Report();       //! returns reports of all cuts applied and correlation functions being done
  virtual unsigned int Overflow() { return mOverFlow;}
  virtual unsigned int Underflow() { return mUnderFlow;}
protected:
  double mBhat[2];
  unsigned int mBhatBins;
  unsigned int mOverFlow;
  unsigned int mUnderFlow;
  
#ifdef __ROOT__
  ClassDef(StHbtBhatAnalysis, 0)
#endif
    
};

#endif
