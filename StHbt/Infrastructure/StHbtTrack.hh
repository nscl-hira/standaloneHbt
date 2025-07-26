/***************************************************************************
 *
 * $Id: StHbtTrack.hh,v 1.24 2005/07/15 17:40:57 kopytin Exp $
 *
 * Author: Mike Lisa, Ohio State, lisa@mps.ohio-state.edu
 ***************************************************************************
 *
 * Description: part of STAR HBT Framework: StHbtMaker package
 *    Intermediate format for particle.  This is built from the
 *    input particle format (e.g. StTrack of StEvent) and presented to
 *    the Analyses for ParticleCuts.
 *
 ***************************************************************************
 *  ... Lots of stuff deleted here ...
 **************************************************************************/

#ifndef StHbtTrack_hh
#define StHbtTrack_hh

#include "Infrastructure/StHbtTypes.hh"
#include "StPhysicalHelixD.hh"
/* Th stuff */
#include "Base/StHbtHiddenInfo.hh"
/***/

#ifndef __NO_STAR_DEPENDENCE_ALLOWED__
class StEvent;
class StTrack;
class StMuDst;
class StMuTrack;
#endif

class StHbtTrack {
public:
	StHbtTrack();
	StHbtTrack(const StHbtTrack &); // copy constructor
#ifndef __NO_STAR_DEPENDENCE_ALLOWED__
#ifdef __ROOT__
	StHbtTrack(const StTrack *, StHbtThreeVector); // c-tor from StTrack of STAR DSTs
	StHbtTrack(const StMuDst *dst, const StMuTrack *t);
#endif
	StHbtTrack(const StEvent *, const StTrack *);
#endif

	~StHbtTrack();
	//    ~StHbtTrack(){/* no-op*/};

	short TrackType() const;
	short Charge() const;
	short NHits() const;
	short NHitsPossible() const;
	short NHitsDedx() const;
	const float *NSigma() const; // Fab private
	float NSigmaElectron() const;
	float NSigmaPion() const;
	float NSigmaKaon() const;
	float NSigmaProton() const;
	float PidProbElectron() const;
	float PidProbPion() const;
	float PidProbKaon() const;
	float PidProbProton() const;
	float dEdx() const;
	float DCAz() const;
	float DCAxy() const;
	float DCAzGlobal() const;
	float DCAxyGlobal() const;
	float ChiSquaredXY() const;
	float ChiSquaredZ() const;
	StHbtThreeVector P() const;
	float Pt() const;
	StHbtThreeVector PGlobal() const;
	float PtGlobal() const;
	const StPhysicalHelixD &Helix() const;
	const StPhysicalHelixD &HelixGlobal() const;
	unsigned int TopologyMap(const unsigned int word) const;
	short TrackId() const;

	void SetTrackType(const short &);
	void SetCharge(const short &);
	void SetNHits(const short &);
	void SetNHitsPossible(const short &);
	void SetNHitsDedx(const short &);
	void SetNSigmaElectron(const float &);
	void SetNSigmaPion(const float &);
	void SetNSigmaKaon(const float &);
	void SetNSigmaProton(const float &);
	void SetPidProbElectron(const float &);
	void SetPidProbPion(const float &);
	void SetPidProbKaon(const float &);
	void SetPidProbProton(const float &);
	void SetdEdx(const float &);
	void SetDCAxy(const float &);
	void SetDCAz(const float &);
	void SetDCAxyGlobal(const float &);
	void SetDCAzGlobal(const float &);
	void SetChiSquaredXY(const float &);
	void SetChiSquaredZ(const float &);
	void SetP(const StHbtThreeVector &);
	void SetPt(const float &);
	void SetPGlobal(const StHbtThreeVector &);
	void SetPtGlobal(const float &);
	void SetHelix(const StPhysicalHelixD &);
	void SetHelixGlobal(const StPhysicalHelixD &);
	void SetTopologyMap(const int word, const unsigned int map);
	void SetTrackId(const short &);

	void SetWeight(const double &);
	double GetWeight() const;
	void SetPid(const int &);
	int GetPid() const;

	void SetAid(const int &);
	int GetAid() const;

	void SetZid(const int &);
	int GetZid() const;

	void SetParentIndex(const int &);
	int GetParentIndex() const;

	void SetEnLab(const double &);
	void SetEnCMS(const double &);

	double GetEnLab() const;
	double GetEnCMS() const;

	void SetPzLab(const double &);
	double GetPzLab() const;

	void SetThetaCMS(const double &);
	double GetThetaCMS() const;

	void SetThetaLAB(const double &);
	double GetThetaLAB() const;

	void SetPhi(const double &);
	double GetPhi() const;

	void SetDeltaTheta(const double &);
	double GetDeltaTheta() const;

	void SetDeltaPhi(const double &);
	double GetDeltaPhi() const;

	// void SetGEff(const double&);
	// double GetGEff() const;

	// void SetReactEff(const double&);
	// double GetReactEff() const;

	void SetTelescope(const unsigned short &tele);
	unsigned short GetTelescope() const;

	void SetEFStrip(const unsigned short &strip);
	unsigned short GetEFStrip() const;

	void SetEBStrip(const unsigned short &strip);
	unsigned short GetEBStrip() const;

	void SetCsI(const unsigned short &csi);
	unsigned short GetCsI() const;

	void SetIsBad_Hira(const unsigned short &h);
	unsigned short GetIsBad_Hira() const;

	void SetIsBad_CsI(const unsigned short &c);
	unsigned short GetIsBad_CsI() const;

	void SetIsBad_StripX(const unsigned short &x);
	unsigned short GetIsBad_StripX() const;

	void SetIsBad_StripY(const unsigned short &y);
	unsigned short GetIsBad_StripY() const;

	/* Th stuff */
	void SetHiddenInfo(StHbtHiddenInfo *aHiddenInfo);
	bool ValidHiddenInfo() const;
	// Fab private : (official : const StHbtHiddenInfo* HiddenInfo() const;
	StHbtHiddenInfo *getHiddenInfo() const;
	/***/

private:
	short mTrackType;
	char mCharge;
	unsigned short mNHits;
	unsigned short mNHitsPoss;
	unsigned short mNHitsDedx;
	float mNSigmaElectron;
	float mNSigmaPion;
	float mNSigmaKaon;
	float mNSigmaProton;
	float mPidProbElectron; // new
	float mPidProbPion;		// new
	float mPidProbKaon;		// new
	float mPidProbProton;	// new
	float mdEdx;
	float mDCAxy;
	float mDCAz;
	float mDCAxyGlobal;
	float mDCAzGlobal;
	float mChiSqXY;
	float mChiSqZ;
	unsigned int mMap[2];
	unsigned int mTrackId;
	double mWeight;
	int mPid;
	int mAid;
	int mZid;
	int mParentIndex;
	double mEnCMS;
	double mEnLab;
	double mPzLab;
	double mThetaCMS;
	double mThetaLAB;
	double mPhi;
	double mDeltaTheta;
	double mDeltaPhi;

	// double mGEff;
	// double mReactionEff;

	unsigned short mTelescope;
	unsigned short mEFStrip;
	unsigned short mEBStrip;
	unsigned short mCsI;
	// 1 = bad 0 = good
	unsigned short mIsBad_Hira;
	unsigned short mIsBad_CsI;
	unsigned short mIsBad_StripX;
	unsigned short mIsBad_StripY;

	StHbtThreeVector mP;
	float mPt;
	StHbtThreeVector mPGlobal;
	float mPtGlobal;
	StPhysicalHelixD mHelix;
	StPhysicalHelixD mHelixGlobal;

	/* Th stuff */
	// Fab private : add mutable
	//  mutable
	StHbtHiddenInfo *mHiddenInfo; //!
								  /***/
};

inline const float *StHbtTrack::NSigma() const { return &mNSigmaElectron; } // Fab private
inline float StHbtTrack::PidProbElectron() const { return mPidProbElectron; }
inline float StHbtTrack::PidProbPion() const { return mPidProbPion; }
inline float StHbtTrack::PidProbKaon() const { return mPidProbKaon; }
inline float StHbtTrack::PidProbProton() const { return mPidProbProton; }
inline StHbtThreeVector StHbtTrack::PGlobal() const { return mPGlobal; }
inline float StHbtTrack::PtGlobal() const { return mPtGlobal; }

inline void StHbtTrack::SetWeight(const double &w) { mWeight = w; }
inline double StHbtTrack::GetWeight() const { return mWeight; }

inline int StHbtTrack::GetPid() const { return mPid; }
inline int StHbtTrack::GetAid() const { return mAid; }
inline int StHbtTrack::GetZid() const { return mZid; }

inline double StHbtTrack::GetEnLab() const { return mEnLab; }
inline void StHbtTrack::SetEnLab(const double &en) { mEnLab = en; }

inline double StHbtTrack::GetEnCMS() const { return mEnCMS; }
inline void StHbtTrack::SetEnCMS(const double &en) { mEnCMS = en; }

inline double StHbtTrack::GetPzLab() const { return mPzLab; }
inline void StHbtTrack::SetPzLab(const double &pz) { mPzLab = pz; }

inline double StHbtTrack::GetThetaCMS() const { return mThetaCMS; }
inline void StHbtTrack::SetThetaCMS(const double &pz) { mThetaCMS = pz; }

inline double StHbtTrack::GetThetaLAB() const { return mThetaLAB; }
inline void StHbtTrack::SetThetaLAB(const double &pz) { mThetaLAB = pz; }

inline double StHbtTrack::GetPhi() const { return mPhi; }
inline void StHbtTrack::SetPhi(const double &pz) { mPhi = pz; }

inline double StHbtTrack::GetDeltaTheta() const { return mDeltaTheta; }
inline void StHbtTrack::SetDeltaTheta(const double &pz) { mDeltaTheta = pz; }

inline double StHbtTrack::GetDeltaPhi() const { return mDeltaPhi; }
inline void StHbtTrack::SetDeltaPhi(const double &p) { mDeltaPhi = p; }

inline void StHbtTrack::SetTelescope(const unsigned short &tele) { mTelescope = tele; }
inline unsigned short StHbtTrack::GetTelescope() const { return mTelescope; }

inline void StHbtTrack::SetEFStrip(const unsigned short &strip) { mEFStrip = strip; }
inline unsigned short StHbtTrack::GetEFStrip() const { return mEFStrip; }

inline void StHbtTrack::SetEBStrip(const unsigned short &strip) { mEBStrip = strip; }
inline unsigned short StHbtTrack::GetEBStrip() const { return mEBStrip; }

inline void StHbtTrack::SetCsI(const unsigned short &csi) { mCsI = csi; }
inline unsigned short StHbtTrack::GetCsI() const { return mCsI; }

inline unsigned short StHbtTrack::GetIsBad_Hira() const { return mIsBad_Hira; }
inline unsigned short StHbtTrack::GetIsBad_CsI() const { return mIsBad_CsI; }
inline unsigned short StHbtTrack::GetIsBad_StripX() const { return mIsBad_StripX; }
inline unsigned short StHbtTrack::GetIsBad_StripY() const { return mIsBad_StripY; }

inline void StHbtTrack::SetIsBad_Hira(const unsigned short &h) { mIsBad_Hira = h; }
inline void StHbtTrack::SetIsBad_CsI(const unsigned short &c) { mIsBad_CsI = c; }
inline void StHbtTrack::SetIsBad_StripX(const unsigned short &x) { mIsBad_StripX = x; }
inline void StHbtTrack::SetIsBad_StripY(const unsigned short &y) { mIsBad_StripY = y; }

#endif
