#ifndef EOSReader_hh
#define EOSReader_hh

#include "Base/StHbtEventReader.hh"

#include "TArrayI.h"
#include "TChain.h"
#include "TMath.h"
#include "TRandom.h"
#include "TVector.h"

#include <stdlib.h>
#include <string>

class StHbtEvent;
class TFile;
class TTree;
class TChain;
class HiRABadmap;
class HiRA_RunInfo;
class HiRAPosCali;

class EOSReader : public StHbtEventReader {

private:
	string mSystemtag;
	string mDirgeoeff;
	string mDirdata;
	string mDirAngle;

	bool mIsBadMapAnal;
	bool mIsUsePosCali;

	int mMaxFiles;
	int mRunNum;   // total number of run for a system
	int mRunIndex; // runfile index
	int mEventNO;  // event id of one file
	int mBadmapNum;
	int mDebug;
	float betaCMS;

	TChain *mTChain;

	string mInputDir;
	StHbtEvent *mHbtEvent;
	HiRABadmap *mBadmap;
	HiRA_RunInfo *mRunInfo;
	HiRAPosCali *mPosCali;

	// branches
	Int_t uBall_fmulti;
	Int_t Hira_fmulti;
	Double_t uBall_fb;
	Double_t uBall_fbhat;
	Int_t fnumtel[30];
	Int_t fnumstripf[30];
	Int_t fnumstripb[30];
	Int_t fnumcsi[30];
	Double_t fEnergySifCal[30];
	Double_t fEnergySibCal[30];
	Double_t fEnergycsifCal[30];
	Double_t fKinEnergy[30];
	Double_t fKinEnergyCMS[30];
	Double_t fMomentum[30];
	Double_t fMomentumCMS[30];
	Double_t fTheta[30];
	Double_t fThetaCMS[30];
	Double_t fPhi[30];
	Int_t fZId[30];
	Int_t fAId[30];
	Double_t fA[30];
	Double_t fZ[30];

	Double_t TDCTriggers_uBallDS_TRG;
	Double_t TDCTriggers_uBallHira_TRG;
	Double_t TDCTriggers_uBallNW_TRG;

	// class functions
	StHbtEvent *read_with_bad_map();

protected:
public:
	EOSReader(
		int maxFiles, const char *runinfo, const char *dir_geoeff, const char *dir_data, const char *Systemtag,
		const char *Dir_angle, bool IsBadMapAnal = true, bool IsUsePosCali = true
	);

	~EOSReader();

	StHbtEvent *ReturnHbtEvent();

	StHbtString Report();

	void SetDebug(int);

	ClassDef(EOSReader, 1)
};

inline void EOSReader::SetDebug(int debug) { mDebug = debug; }

#endif
