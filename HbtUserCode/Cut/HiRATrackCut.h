/***************************************************************************
 *
 * $Id:
 *
 * Author: Mike Lisa, Ohio State, lisa@mps.ohio-state.edu
 ***************************************************************************
 *
 * Description: part of STAR HBT Framework: StHbtMaker package
 *    a simple particle cut that selects on phasespace, #hits, DCA, and PID
 *
 ***************************************************************************
 *
 * $Log:
 **************************************************************************/

#ifndef HiRATrackCut_hh
#define HiRATrackCut_hh

#include "Base/StHbtTrackCut.h"

class HiRATrackCut : public StHbtTrackCut {

public:
	HiRATrackCut();

	virtual bool Pass(const StHbtTrack *);

	virtual StHbtString Report();

	void SetPt(const float &lo, const float &hi);
	void SetP(const float &lo, const float &hi);
	void SetRapidity(const float &lo, const float &hi);
	void SetRapidity2(const float &lo, const float &hi);
	void SetPid(const int &);

	void SetThetaLAB(const float &lo, const float &hi);
	void SetPhiLAB(const float &lo, const float &hi);
	void SetThetaCMS(const float &lo, const float &hi);
	void SetPhiCMS(const float &lo, const float &hi);
	void SetKineticEnergy(const float &lo, const float &hi);

private: // here are the quantities I want to cut on...
	int mPid;

	float mPt[2];
	float mP[2];
	float mRapidity[2];
	float mRapidity2[2];
	float mThetaLAB[2];
	float mPhiLAB[2];
	float mThetaCMS[2];
	float mPhiCMS[2];
	float mKineticEnergy[2];

	long mNTracksPassed;
	long mNTracksFailed;

#ifdef __ROOT__
	ClassDef(HiRATrackCut, 1)
#endif
};

inline void HiRATrackCut::SetP(const float &lo, const float &hi) {
	mP[0] = lo;
	mP[1] = hi;
}
inline void HiRATrackCut::SetPt(const float &lo, const float &hi) {
	mPt[0] = lo;
	mPt[1] = hi;
}
inline void HiRATrackCut::SetRapidity(const float &lo, const float &hi) {
	mRapidity[0] = lo;
	mRapidity[1] = hi;
}
inline void HiRATrackCut::SetRapidity2(const float &lo, const float &hi) {
	mRapidity2[0] = lo;
	mRapidity2[1] = hi;
}
inline void HiRATrackCut::SetPid(const int &pid) { mPid = pid; }

inline void HiRATrackCut::SetThetaLAB(const float &lo, const float &hi) {
	mThetaLAB[0] = lo;
	mThetaLAB[1] = hi;
}
inline void HiRATrackCut::SetPhiLAB(const float &lo, const float &hi) {
	mPhiLAB[0] = lo;
	mPhiLAB[1] = hi;
}
inline void HiRATrackCut::SetThetaCMS(const float &lo, const float &hi) {
	mThetaCMS[0] = lo;
	mThetaCMS[1] = hi;
}
inline void HiRATrackCut::SetPhiCMS(const float &lo, const float &hi) {
	mPhiCMS[0] = lo;
	mPhiCMS[1] = hi;
}
inline void HiRATrackCut::SetKineticEnergy(const float &lo, const float &hi) {
	mKineticEnergy[0] = lo;
	mKineticEnergy[1] = hi;
}

#endif
