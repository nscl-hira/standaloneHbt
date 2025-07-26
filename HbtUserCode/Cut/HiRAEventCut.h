/***************************************************************************
 *
 * $Id: HiRAEventCut.h,v 1.5 2000/03/23 22:57:28 laue Exp $
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
 * $Log: HiRAEventCut.h,v $
 * Revision 1.5  2000/03/23 22:57:28  laue
 * Clone() function implemented
 *
 * Revision 1.4  2000/01/25 17:35:02  laue
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
 * Revision 1.3  1999/10/15 01:57:04  lisa
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
 * Revision 1.2  1999/07/06 22:33:21  lisa
 * Adjusted all to work in pro and new - dev itself is broken
 *
 * Revision 1.1.1.1  1999/06/29 16:02:56  lisa
 * Installation of StHbtMaker
 *
 **************************************************************************/

#ifndef HiRAEventCut_hh
#define HiRAEventCut_hh

#include "Base/StHbtEventCut.h"

class HiRAEventCut : public StHbtEventCut {

public:
	HiRAEventCut();
	HiRAEventCut(HiRAEventCut &);
	//~HiRAEventCut();

	void SetEventMult(const int &lo, const int &hi);
	void SetVertZPos(const float &lo, const float &hi);
	void SetEt(const float &lo, const float &hi);
	void SetBhat(const float &blow, const float &bhigh);

	int NEventsPassed();
	int NEventsFailed();

	virtual StHbtString Report();
	virtual bool Pass(const StHbtEvent *);

	HiRAEventCut *Clone();

private:				// here are the quantities I want to cut on...
	int mEventMult[2];	// range of multiplicity
	float mVertZPos[2]; // range of z-position of vertex
	float mEt[2];
	float mBhat[2];

	long mNEventsPassed;
	long mNEventsFailed;

#ifdef __ROOT__
	ClassDef(HiRAEventCut, 1);
#endif
};

inline void HiRAEventCut::SetEventMult(const int &lo, const int &hi) {
	mEventMult[0] = lo;
	mEventMult[1] = hi;
}
inline void HiRAEventCut::SetVertZPos(const float &lo, const float &hi) {
	mVertZPos[0] = lo;
	mVertZPos[1] = hi;
}
inline void HiRAEventCut::SetEt(const float &lo, const float &hi) {
	mEt[0] = lo;
	mEt[1] = hi;
}
inline void HiRAEventCut::SetBhat(const float &blow, const float &bhigh) {
	mBhat[0] = blow;
	mBhat[1] = bhigh;
}
inline int HiRAEventCut::NEventsPassed() { return mNEventsPassed; }
inline int HiRAEventCut::NEventsFailed() { return mNEventsFailed; }
inline HiRAEventCut *HiRAEventCut::Clone() {
	HiRAEventCut *c = new HiRAEventCut(*this);
	return c;
}
inline HiRAEventCut::HiRAEventCut(HiRAEventCut &c) : StHbtEventCut(c) {
	mEventMult[0] = c.mEventMult[0];
	mEventMult[1] = c.mEventMult[1];
	mVertZPos[0] = c.mVertZPos[0];
	mVertZPos[1] = c.mVertZPos[1];
	mNEventsPassed = 0;
	mNEventsFailed = 0;
	mEt[0] = c.mEt[0];
	mEt[1] = c.mEt[1];
	mBhat[0] = c.mBhat[0];
	mBhat[1] = c.mBhat[1];
}

#endif
