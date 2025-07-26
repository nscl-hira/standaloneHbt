/***************************************************************************
 *
 * $Id: StHbtTrack.cc,v 1.19 2005/07/15 17:41:43 kopytin Exp $
 *
 * Author: Frank Laue, Ohio State, laue@mps.ohio-state.edu
 ***************************************************************************
 *
 * Description: part of STAR HBT Framework: StHbtMaker package
 * Implementation of methods
 *
 ***************************************************************************
 * $Log: StHbtTrack.cc,v $
 * Revision 1.19  2005/07/15 17:41:43  kopytin
 * initialized mHiddenInfo in StHbtTrack() to null
 *
 * Revision 1.18  2005/07/10 02:17:21  chajecki
 * Ftpc (Eeat+West) hits included in nHits()
 *
 * Revision 1.17  2005/06/17 21:41:12  chajecki
 * Two bugs fixed:
 * 1. wrong value of mNHits set in one of the constructors
 * StHbtTrack::StHbtTrack(const StTrack* ST, StHbtThreeVector PrimaryVertex)
 *
 * 2. since year 4 the StMuTrack::nHits() returns the total number of hits.
 * We're interested in TPC hits only so this value can be taken by
 *  StMuTrack::topologyMap().numberOfHits(kTpcId);
 * This change is backwards compatible so the code should work also
 * for data <=Y3
 *
 * Revision 1.16  2003/03/18 14:41:48  kisiel
 * Bugfix update for the theoretical part of the code. Reverts the changes to the Lednicky weight calculator, as the
 *previuos one had problems with strong interaction
 *
 * Revision 1.15  2003/01/31 19:57:15  magestro
 * Cleared up simple compiler warnings on i386_linux24
 *
 * Revision 1.14  2003/01/21 17:26:33  magestro
 * Added condition to globalTrack() call so GlobalTracks branch in MuDst can be disabled
 *
 * Revision 1.13  2002/03/21 18:49:31  laue
 * updated for new MuDst reader
 *
 * Revision 1.12  2002/02/04 18:58:33  laue
 * *** empty log message ***
 *
 * Revision 1.11  2001/12/14 23:11:30  fretiere
 * Add class HitMergingCut. Add class fabricesPairCut = HitMerginCut + pair purity cuts. Add TpcLocalTransform function
 *which convert to local tpc coord (not pretty). Modify StHbtTrack, StHbtParticle, StHbtHiddenInfo, StHbtPair to handle
 *the hit information and cope with my code
 *
 * Revision 1.4  2001/06/21 19:15:48  laue
 * Modified fiels:
 *   CTH.hh : new constructor added
 *   StHbtEvent, StHbtKink, StHbtTrack : constructors from the persistent
 *                                   (TTree) classes added
 *   StHbtLikeSignAnalysis : minor changes, for debugging
 *   StHbtTypes: split into different files
 * Added files: for the new TTree muDst's
 *   StExceptions.cxx StExceptions.hh StHbtEnumeration.hh
 *   StHbtHelix.hh StHbtHisto.hh StHbtString.hh StHbtTFile.hh
 *   StHbtTTreeEvent.cxx StHbtTTreeEvent.h StHbtTTreeKink.cxx
 *   StHbtTTreeKink.h StHbtTTreeTrack.cxx StHbtTTreeTrack.h
 *   StHbtTTreeV0.cxx StHbtTTreeV0.h StHbtVector.hh
 *
 * Revision 1.3  2001/05/25 23:23:59  lisa
 * Added in StHbtKink stuff
 *
 *
 ****************************************************************************/

#include "Infrastructure/StHbtTrack.hh"
#ifndef __NO_STAR_DEPENDENCE_ALLOWED__
#ifdef __ROOT__
#include "Infrastructure/StHbtAihongPid.h"
#include "StEvent/StEnumerations.h"
#include "StEventUtilities/StuProbabilityPidAlgorithm.h"
#endif
#endif

#include "StarClassLibrary/inc/StParticleTypes.hh"
#include "StarClassLibrary/inc/SystemOfUnits.h" // has "tesla" in it
// #include "Infrastructure/StHbtTTreeEvent.h"
// #include "Infrastructure/StHbtTTreeTrack.h"

StHbtTrack::StHbtTrack() { mHiddenInfo = NULL; }

StHbtTrack::StHbtTrack(const StHbtTrack &t) { // copy constructor
	mTrackType = t.mTrackType;
	mPid = t.mPid;
	mAid = t.mAid;
	mZid = t.mZid;

	mCharge = t.mCharge;
	mNHits = t.mNHits;
	mNHitsPoss = t.mNHitsPoss;
	mNHitsDedx = t.mNHitsDedx;
	mNSigmaElectron = t.mNSigmaElectron;
	mNSigmaPion = t.mNSigmaPion;
	mNSigmaKaon = t.mNSigmaKaon;
	mNSigmaProton = t.mNSigmaProton;
	mPidProbElectron = t.mPidProbElectron;
	mPidProbPion = t.mPidProbPion;
	mPidProbKaon = t.mPidProbKaon;
	mPidProbProton = t.mPidProbProton;
	mdEdx = t.mdEdx;
	mDCAxy = t.mDCAxy;
	mDCAz = t.mDCAz;
	mDCAxyGlobal = t.mDCAxyGlobal;
	mDCAzGlobal = t.mDCAzGlobal;
	mChiSqXY = t.mChiSqXY;
	mChiSqZ = t.mChiSqZ;
	mP = t.mP;
	mPt = t.mPt;
	mPGlobal = t.mPGlobal;
	mPtGlobal = t.mPtGlobal;
	mHelix = t.mHelix;
	mHelixGlobal = t.mHelixGlobal;
	mMap[0] = t.mMap[0];
	mMap[1] = t.mMap[1];
	mTrackId = t.mTrackId;
	if (t.ValidHiddenInfo())
		mHiddenInfo = t.getHiddenInfo()->clone();
	else
		mHiddenInfo = NULL;

	mWeight = t.mWeight;
	mEnLab = t.mEnLab;
	mPzLab = t.mPzLab;
	mThetaCMS = t.mThetaCMS;
	mThetaLAB = t.mThetaLAB;
	mPhi = t.mPhi;
	mDeltaPhi = t.mDeltaPhi;
	mDeltaTheta = t.mDeltaTheta;
	// mGEff = t.mGEff;
	// mReactionEff = t.mReactionEff;
	mTelescope = t.mTelescope;
	mEFStrip = t.mEFStrip;
	mEBStrip = t.mEBStrip;
	mCsI = t.mCsI;

	mIsBad_Hira = t.mIsBad_Hira;
	mIsBad_CsI = t.mIsBad_CsI;
	mIsBad_StripX = t.mIsBad_StripX;
	mIsBad_StripY = t.mIsBad_StripY;
};
//___________________________________________________
#ifndef __NO_STAR_DEPENDENCE_ALLOWED__

#ifdef __ROOT__
#include "StEvent/StEnumerations.h"
#include "StEvent/StTpcDedxPidAlgorithm.h"
#include "StEventTypes.h"
#include "StEventUtilities/StuRefMult.hh"
#endif

StHbtTrack::StHbtTrack(const StTrack *ST, StHbtThreeVector PrimaryVertex) {
	StTpcDedxPidAlgorithm PidAlgorithm;

	// while getting the bestGuess, the pidAlgorithm (StTpcDedxPidAlgorithm) is set up.
	// pointers to track and pidTraits are set
	// So, even though BestGuess will generate a "variable not used" warning, DO NOT DELETE THE NEXT LINE
	// StParticleDefinition* BestGuess = (StParticleDefinition*)ST->pidTraits(PidAlgorithm);

	// the following just point to particle definitions in StEvent
	StElectron *Electron = StElectron::instance();
	StPionPlus *Pion = StPionPlus::instance();
	StKaonPlus *Kaon = StKaonPlus::instance();
	StProton *Proton = StProton::instance();

	// OK let's go...
	mHiddenInfo = 0;
	mTrackType = ST->type();
	mCharge = ST->geometry()->charge();
	mNHits = ST->detectorInfo()->numberOfPoints(kTpcId);
	mNHitsPoss = ST->numberOfPossiblePoints(kTpcId);
	mNHitsDedx = ST->fitTraits().numberOfFitPoints(kTpcId);

	mNSigmaElectron = PidAlgorithm.numberOfSigma(Electron);
	mNSigmaPion = PidAlgorithm.numberOfSigma(Pion);
	mNSigmaKaon = PidAlgorithm.numberOfSigma(Kaon);
	mNSigmaProton = PidAlgorithm.numberOfSigma(Proton);
	if (PidAlgorithm.traits())
		mdEdx = PidAlgorithm.traits()->mean();
	else
		cout << "StHbtTrack(const StTrack* ST, StHbtThreeVector PrimaryVertex) - no traits " << endl;

	mChiSqXY = ST->fitTraits().chi2(0);
	mChiSqZ = ST->fitTraits().chi2(1);

	mP = ST->geometry()->momentum();
	mPt = mP.perp();
	mHelix = ST->geometry()->helix();
	double pathlength = ST->geometry()->helix().pathLength(PrimaryVertex);
	StHbtThreeVector DCAxyz = ST->geometry()->helix().at(pathlength) - PrimaryVertex;
	mDCAxy = DCAxyz.perp();
	mDCAz = DCAxyz.z();

	mHelixGlobal = ST->node()->track(global)->geometry()->helix();
	double pathlengthGlobal = mHelixGlobal.pathLength(PrimaryVertex);
	StHbtThreeVector DCAxyzGlobal = mHelixGlobal.at(pathlengthGlobal) - PrimaryVertex;
	mDCAxyGlobal = DCAxyzGlobal.perp();
	mDCAzGlobal = DCAxyzGlobal.z();
	mPGlobal = ST->node()->track(global)->geometry()->momentum();
	mPtGlobal = mPGlobal.perp();

	mMap[0] = ST->topologyMap().data(0);
	mMap[1] = ST->topologyMap().data(1);
	mTrackId = ST->key();
}

StHbtTrack::StHbtTrack(const StEvent *EV, const StTrack *ST) {
	StTpcDedxPidAlgorithm PidAlgorithm;
	// while getting the bestGuess, the pidAlgorithm (StTpcDedxPidAlgorithm) is set up.
	// pointers to track and pidTraits are set
	// So, even though BestGuess will generate a "variable not used" warning, DO NOT DELETE THE NEXT LINE
	ST->pidTraits(PidAlgorithm);

	// the following just point to particle definitions in StEvent
	StElectron *Electron = StElectron::instance();
	StPionPlus *Pion = StPionPlus::instance();
	StKaonPlus *Kaon = StKaonPlus::instance();
	StProton *Proton = StProton::instance();

	// OK let's go...
	mHiddenInfo = 0;
	mTrackType = ST->type();
	mCharge = ST->geometry()->charge();
	mNHits = ST->detectorInfo()->numberOfPoints(kTpcId);
	mNHitsPoss = ST->numberOfPossiblePoints(kTpcId);
	mNHitsDedx = ST->fitTraits().numberOfFitPoints(kTpcId);

	mNSigmaElectron = PidAlgorithm.numberOfSigma(Electron);
	mNSigmaPion = PidAlgorithm.numberOfSigma(Pion);
	mNSigmaKaon = PidAlgorithm.numberOfSigma(Kaon);
	mNSigmaProton = PidAlgorithm.numberOfSigma(Proton);
	mdEdx = PidAlgorithm.traits()->mean();

	mChiSqXY = ST->fitTraits().chi2(0);
	mChiSqZ = ST->fitTraits().chi2(1);

	StHbtThreeVector primaryVertex = EV->primaryVertex()->position();

	mHelix = ST->geometry()->helix();
	double pathlength = mHelix.pathLength(primaryVertex);
	StHbtThreeVector DCAxyz = mHelix.at(pathlength) - primaryVertex;
	mDCAxy = DCAxyz.perp();
	mDCAz = DCAxyz.z();
	mP = mHelix.momentumAt(pathlength, EV->summary()->magneticField() * kilogauss);
	mPt = mP.perp();

	if (dynamic_cast<const StPrimaryTrack *>(ST)) {
		mHelixGlobal = ST->node()->track(global)->geometry()->helix();
	} else {
		mHelixGlobal = mHelix;
	}
	double pathlengthGlobal = mHelixGlobal.pathLength(primaryVertex);
	StHbtThreeVector DCAxyzGlobal = mHelixGlobal.at(pathlengthGlobal) - primaryVertex;
	mDCAxyGlobal = DCAxyzGlobal.perp();
	mDCAzGlobal = DCAxyzGlobal.z();
	mPGlobal = mHelixGlobal.momentumAt(pathlengthGlobal, EV->summary()->magneticField() * kilogauss);
	mPtGlobal = mPGlobal.perp();

	mMap[0] = ST->topologyMap().data(0);
	mMap[1] = ST->topologyMap().data(1);
	mTrackId = ST->key();

	// On the fly pid probability calculation
	static int previousEventNumber = 0;
	static StHbtAihongPid *hbtAihongPid = StHbtAihongPid::Instance();
	static StuProbabilityPidAlgorithm *aihongPid = hbtAihongPid->aihongPid();
	if ((mPidProbElectron + mPidProbPion + mPidProbKaon + mPidProbProton) <= 0.) {
		if (previousEventNumber != EV->info()->id()) {
			// must do the below because uncorrectedNumberOfPositivePrimaries() function does not have const argument
			StEvent *TempEv = (StEvent *)EV;
			hbtAihongPid->updateEvent(uncorrectedNumberOfPositivePrimaries(*TempEv));
			//      hbtAihongPid->updateEvent(uncorrectedNumberOfPositivePrimaries(*EV));
			previousEventNumber = EV->info()->id();
		}
		hbtAihongPid->updateTrack((int)mCharge, mP.mag(), mP.pseudoRapidity(), mNHitsDedx, mdEdx);
		mPidProbElectron = (mCharge > 0) ? aihongPid->beingPositronProb() : aihongPid->beingElectronProb();
		mPidProbPion = (mCharge > 0) ? aihongPid->beingPionPlusProb() : aihongPid->beingPionMinusProb();
		mPidProbKaon = (mCharge > 0) ? aihongPid->beingKaonPlusProb() : aihongPid->beingKaonMinusProb();
		mPidProbProton = (mCharge > 0) ? aihongPid->beingProtonProb() : aihongPid->beingAntiProtonProb();
	}
}

#include "StMuDSTMaker/COMMON/StMuDst.h"
#include "StMuDSTMaker/COMMON/StMuEvent.h"
#include "StMuDSTMaker/COMMON/StMuTrack.h"
StHbtTrack::StHbtTrack(const StMuDst *dst, const StMuTrack *t) { // copy constructor
	StMuEvent *ev = dst->event();
	mTrackType = t->type();
	mTrackId = t->id();

	mNHits = t->topologyMap().numberOfHits(kTpcId) + t->topologyMap().numberOfHits(kFtpcEastId) +
			 t->topologyMap().numberOfHits(kFtpcWestId);

	mNHitsPoss = t->nHitsPoss();
	mNHitsDedx = t->nHitsDedx();
	mNSigmaElectron = t->nSigmaElectron();
	mNSigmaPion = t->nSigmaPion();
	mNSigmaKaon = t->nSigmaKaon();
	mNSigmaProton = t->nSigmaProton();
	mPidProbElectron = t->pidProbElectron();
	mPidProbPion = t->pidProbPion();
	mPidProbKaon = t->pidProbKaon();
	mPidProbProton = t->pidProbProton();
	mdEdx = t->dEdx();
	mChiSqXY = t->chi2xy();
	mChiSqZ = t->chi2z();
	mMap[0] = t->topologyMap().data(0);
	mMap[1] = t->topologyMap().data(1);
	mHelix = t->helix();
	if (t->globalTrack())
		mHelixGlobal = t->globalTrack()->helix();
	mCharge = t->charge();

	double pathlength = mHelix.pathLength(ev->primaryVertexPosition());
	mP = mHelix.momentumAt(pathlength, ev->magneticField() * kilogauss);
	mPt = mP.perp();
	StThreeVectorD dca(mHelix.at(pathlength) - ev->primaryVertexPosition());
	mDCAxy = dca.perp();
	mDCAz = dca.z();

	if (t->globalTrack()) {
		double pathlengthGlobal = mHelixGlobal.pathLength(ev->primaryVertexPosition());
		mPGlobal = mHelixGlobal.momentumAt(pathlengthGlobal, ev->magneticField() * kilogauss);
		mPtGlobal = mPGlobal.perp();
		StThreeVectorD dcaGlobal(mHelixGlobal.at(pathlengthGlobal) - ev->primaryVertexPosition());
		mDCAxyGlobal = dcaGlobal.perp();
		mDCAzGlobal = dcaGlobal.z();
	}

	mHiddenInfo = 0;
};

#endif // __NO_STAR_DEPENDENCE_ALLOWED__

void StHbtTrack::SetTrackType(const short &t) { mTrackType = t; }
void StHbtTrack::SetCharge(const short &ch) { mCharge = ch; }
void StHbtTrack::SetNHits(const short &nh) { mNHits = nh; }
void StHbtTrack::SetNHitsPossible(const short &nh) { mNHitsPoss = nh; }
void StHbtTrack::SetNHitsDedx(const short &nh) { mNHitsDedx = nh; }
void StHbtTrack::SetNSigmaElectron(const float &x) { mNSigmaElectron = x; }
void StHbtTrack::SetNSigmaPion(const float &x) { mNSigmaPion = x; }
void StHbtTrack::SetNSigmaKaon(const float &x) { mNSigmaKaon = x; }
void StHbtTrack::SetNSigmaProton(const float &x) { mNSigmaProton = x; }
void StHbtTrack::SetPidProbElectron(const float &x) { mPidProbElectron = x; }
void StHbtTrack::SetPidProbPion(const float &x) { mPidProbPion = x; }
void StHbtTrack::SetPidProbKaon(const float &x) { mPidProbKaon = x; }
void StHbtTrack::SetPidProbProton(const float &x) { mPidProbProton = x; }

void StHbtTrack::SetdEdx(const float &x) { mdEdx = x; }

void StHbtTrack::SetDCAxy(const float &x) { mDCAxy = x; }
void StHbtTrack::SetDCAz(const float &x) { mDCAz = x; }
void StHbtTrack::SetDCAxyGlobal(const float &x) { mDCAxyGlobal = x; }
void StHbtTrack::SetDCAzGlobal(const float &x) { mDCAzGlobal = x; }
void StHbtTrack::SetChiSquaredXY(const float &x) { mChiSqXY = x; }
void StHbtTrack::SetChiSquaredZ(const float &x) { mChiSqZ = x; }
void StHbtTrack::SetP(const StHbtThreeVector &p) { mP = p; }
void StHbtTrack::SetPt(const float &pt) { mPt = pt; }
void StHbtTrack::SetPGlobal(const StHbtThreeVector &p) { mP = p; }
void StHbtTrack::SetPtGlobal(const float &pt) { mPt = pt; }
void StHbtTrack::SetHelix(const StPhysicalHelixD &h) { mHelix = h; }
void StHbtTrack::SetHelixGlobal(const StPhysicalHelixD &h) { mHelixGlobal = h; }
void StHbtTrack::SetTopologyMap(const int word, const unsigned int map) { mMap[word] = map; }
void StHbtTrack::SetTrackId(const short &id) { mTrackId = id; }

short StHbtTrack::TrackType() const { return mTrackType; }
short StHbtTrack::Charge() const { return mCharge; }
short StHbtTrack::NHits() const { return mNHits; }
short StHbtTrack::NHitsPossible() const { return mNHitsPoss; }
short StHbtTrack::NHitsDedx() const { return mNHitsDedx; }
float StHbtTrack::NSigmaElectron() const { return mNSigmaElectron; }
float StHbtTrack::NSigmaPion() const { return mNSigmaPion; }
float StHbtTrack::NSigmaKaon() const { return mNSigmaKaon; }
float StHbtTrack::NSigmaProton() const { return mNSigmaProton; }
float StHbtTrack::dEdx() const { return mdEdx; }

float StHbtTrack::DCAxy() const { return mDCAxy; }
float StHbtTrack::DCAz() const { return mDCAz; }
float StHbtTrack::DCAxyGlobal() const { return mDCAxyGlobal; }
float StHbtTrack::DCAzGlobal() const { return mDCAzGlobal; }
float StHbtTrack::ChiSquaredXY() const { return mChiSqXY; }
float StHbtTrack::ChiSquaredZ() const { return mChiSqZ; }
StHbtThreeVector StHbtTrack::P() const { return mP; }
float StHbtTrack::Pt() const { return mPt; }
const StPhysicalHelixD &StHbtTrack::Helix() const { return mHelix; }
const StPhysicalHelixD &StHbtTrack::HelixGlobal() const { return mHelixGlobal; }
unsigned int StHbtTrack::TopologyMap(const unsigned int word) const { return mMap[word]; }
short StHbtTrack::TrackId() const { return mTrackId; }

void StHbtTrack::SetHiddenInfo(StHbtHiddenInfo *aHiddenInfo) { mHiddenInfo = aHiddenInfo; }
bool StHbtTrack::ValidHiddenInfo() const {
	if (mHiddenInfo)
		return true;
	else
		return false;
}
StHbtHiddenInfo *StHbtTrack::getHiddenInfo() const { return mHiddenInfo; }

StHbtTrack::~StHbtTrack() {
	if (mHiddenInfo)
		delete mHiddenInfo;
}

void StHbtTrack::SetPid(const int &pid) { mPid = pid; }
void StHbtTrack::SetAid(const int &aid) { mAid = aid; }
void StHbtTrack::SetZid(const int &zid) { mZid = zid; }

void StHbtTrack::SetParentIndex(const int &index) { mParentIndex = index; }

int StHbtTrack::GetParentIndex() const { return mParentIndex; }
