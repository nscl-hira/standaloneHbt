/***************************************************************************
 *
 * $Id: HiRAEventCut.cxx,v 1.7 2000/02/18 21:27:10 laue Exp $
 *
 * Author: Mike Lisa, Ohio State, lisa@mps.ohio-state.edu
 ***************************************************************************
 *
 * Description: part of STAR HBT Framework: StHbtMaker package
 *   A simple event-wise cut that selects on multiplicity and z-position
 *   of primary vertex           
 *
 ***************************************************************************
 *
 * $Log: HiRAEventCut.cxx,v $
 * Revision 1.7  2000/02/18 21:27:10  laue
 * franksTrackCut changed. If mCharge is set to '0' there will be no cut
 * on charge. This is important for front-loaded cuts.
 *
 * Revision 1.6  2000/01/25 17:35:02  laue
 * I. In order to run the stand alone version of the StHbtMaker the following
 * changes have been done:
 * a) all ClassDefs and ClassImps have been put into #ifdef __ROOT__ statements
 * b) unnecessary includes of StMaker.h have been removed
 * c) the subdirectory StHbtMaker/doc/Make has been created including everything
 * needed for the stand alone version
 *
 * II. To reduce the amount of compiler warning
 * a) some variables have been type casted
 * b) some destructors have been declared as virtual
 *
 * Revision 1.5  1999/10/15 01:57:03  lisa
 * Important enhancement of StHbtMaker - implement Franks CutMonitors
 * ----------------------------------------------------------
 * This means 3 new files in Infrastructure area (CutMonitor),
 * several specific CutMonitor classes in the Cut area
 * and a new base class in the Base area (StHbtCutMonitor).
 * This means also changing all Cut Base class header files from .hh to .h
 * so we have access to CutMonitor methods from Cint command line.
 * This last means
 * 1) files which include these header files are slightly modified
 * 2) a side benefit: the TrackCuts and V0Cuts no longer need
 * a SetMass() implementation in each Cut class, which was stupid.
 * Also:
 * -----
 * Include Franks StHbtAssociationReader
 * ** None of these changes should affect any user **
 *
 * Revision 1.4  1999/07/24 16:24:20  lisa
 * adapt StHbtMaker to dev version of library - solaris still gives problems with strings
 *
 * Revision 1.3  1999/07/19 14:24:04  hardtke
 * modifications to implement uDST
 *
 * Revision 1.2  1999/07/06 22:33:21  lisa
 * Adjusted all to work in pro and new - dev itself is broken
 *
 * Revision 1.1.1.1  1999/06/29 16:02:56  lisa
 * Installation of StHbtMaker
 *
 **************************************************************************/

#include "Cut/HiRAEventCut.h"
#include <cstdio>

#ifdef __ROOT__
ClassImp(HiRAEventCut)
#endif

HiRAEventCut::HiRAEventCut(){
  mNEventsPassed =  mNEventsFailed = 0;
  mEt[0]= 0; mEt[1] = 100000;
  mBhat[0]=0; mBhat[1]=1;
  
} 
//------------------------------
//HiRAEventCut::~HiRAEventCut(){
//  /* noop */
//}
//------------------------------
bool HiRAEventCut::Pass(const StHbtEvent* event){
  int mult =  event->NumberOfTracks();
  double VertexZPos = event->PrimVertPos().z();
  double Etrans = event->GetEtrans();
  double bhat=event->GetBhat();
  double uball_multiplicity=event->UncorrectedNumberOfPrimaries();
  double uBallDS_TRG = event->GetuBallDS_TRG();
  double uBallHira_TRG = event->GetuBallHira_TRG();
  double uBallNW_TRG = event->GetuBallNW_TRG();
  
  
  
#ifdef DEBUGYN
  cout << "HiRAEventCut:: mult:       " << mEventMult[0] << " < " << mult << " < " << mEventMult[1] << endl;
  cout << "HiRAEventCut:: VertexZPos: " << mVertZPos[0] << " < " << VertexZPos << " < " << mVertZPos[1] << endl;
  cout<< "HiRAEventCut:: Bhat:       " << mBhat[0]<<" < "<<bhat<<" < "<<mBhat[1]<<endl; 
#endif
  bool gooduBallDS_TRG = (uBallDS_TRG>-9999);
  bool gooduBallHira_TRG = 1;//(uBallHira_TRG>-9999);
  bool gooduBallNW_TRG = (uBallNW_TRG>-9999);
  
  
  bool goodEvent = 
	  gooduBallHira_TRG &&
     ((mult >= mEventMult[0]) && 
     (mult < mEventMult[1])&& 
     (VertexZPos >= mVertZPos[0]) &&
     (VertexZPos < mVertZPos[1]) &&
	 (bhat>=mBhat[0]) &&
	 (bhat<=mBhat[1]) &&
	 (uball_multiplicity>5)
	 );
     //(Etrans >= mEt[0]) &&
     //(Etrans < mEt[1]) ); 
	 
	 
  goodEvent ? mNEventsPassed++ : mNEventsFailed++ ;	
  //if (!goodEvent){cout<<mult<<"  "<<VertexZPos<<"   "<<bhat<<endl;}
#ifdef DEBUGYN
  cout << "HiRAEventCut:: return : " << goodEvent << endl;
#endif
  return (goodEvent);
}
//------------------------------
StHbtString HiRAEventCut::Report(){
  string Stemp;
  char Ctemp[100];
  sprintf(Ctemp,"\nMultiplicity:\t %d-%d",mEventMult[0],mEventMult[1]);
  Stemp = Ctemp;
  sprintf(Ctemp,"\nVertex Z-position:\t %E-%E",mVertZPos[0],mVertZPos[1]);
  Stemp += Ctemp;
  //sprintf(Ctemp,"\nEt :\t %E-%E",mEt[0],mEt[1]);
  sprintf(Ctemp,"\nbhat :\t %E-%E",mBhat[0],mBhat[1]);
  Stemp += Ctemp;
  sprintf(Ctemp,"\nNumber of events which passed:\t%ld  Number which failed:\t%ld",mNEventsPassed,mNEventsFailed);
  Stemp += Ctemp;
  StHbtString returnThis = Stemp;
  return returnThis;
}
