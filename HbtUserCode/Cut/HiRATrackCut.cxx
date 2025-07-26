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

#include "Cut/HiRATrackCut.h"
#include "TMath.h"
#include <cstdio>

#ifdef __ROOT__
ClassImp(HiRATrackCut);
#endif

HiRATrackCut::HiRATrackCut() {
	mNTracksPassed = mNTracksFailed = 0;
	mPid = 0;
	mPt[0] = 0.0;
	mPt[1] = 10000.0;
	mP[0] = 0.0;
	mP[1] = 10000.0;
	mRapidity[0] = -10.0;
	mRapidity[1] = 10.0;
	mRapidity2[0] = -10.0;
	mRapidity2[1] = 10.0;
	mThetaLAB[0] = 0;
	mThetaLAB[1] = 180;
	mPhiLAB[0] = -360;
	mPhiLAB[1] = 360;
	mThetaCMS[0] = -10000.;
	mThetaCMS[1] = 1180;
	mPhiCMS[0] = -10000;
	mPhiCMS[1] = 10360;
	mKineticEnergy[0] = 0.0;
	mKineticEnergy[1] = 10000.0;
}

bool HiRATrackCut::Pass(const StHbtTrack *track) {

	auto kineticEnergyCMS = track->GetEnCMS();
	auto thetaCMS = track->GetThetaCMS();
	auto TEnergy = kineticEnergyCMS + mMass;
	auto pmag_cms = std::sqrt(TEnergy * TEnergy - mMass * mMass);
	auto pz_cms = pmag_cms * std::cos(thetaCMS);

	auto TRapidity = 0.5 * ::log((TEnergy + pz_cms) / (TEnergy - pz_cms));

	auto kineticEnergyLab = track->GetEnLab();

	int A = track->GetAid(); // Atomic number

	auto Pt = ::sqrt((track->P().x()) * (track->P().x()) + (track->P().y()) * (track->P().y()));

	auto P = ::sqrt(
		(track->P().x()) * (track->P().x()) + (track->P().y()) * (track->P().y()) + (track->P().z()) * (track->P().z())
	);

	auto ThetaLAB = track->GetThetaLAB() * 180 / TMath::Pi();
	auto ThetaCMS = track->GetThetaCMS() * 180 / TMath::Pi();
	auto PhiCMS = track->GetPhi() * 180 / TMath::Pi();
	auto PhiLAB = track->GetPhi() * 180 / TMath::Pi();

	bool goodrap = ((TRapidity >= mRapidity[0]) && (TRapidity < mRapidity[1]));
	bool goodPt = (Pt >= mPt[0]) && (Pt < mPt[1]);
	bool goodP = (P >= mP[0]) && (P < mP[1]);
	bool goodpid = (track->GetPid() == mPid);
	bool goodtheta = (ThetaLAB >= mThetaLAB[0]) && (ThetaLAB <= mThetaLAB[1]);
	bool goodthetacms = (ThetaCMS >= mThetaCMS[0]) && (ThetaCMS < mThetaCMS[1]);
	bool goodphilab = (PhiLAB >= mPhiLAB[0]) && (PhiLAB < mPhiLAB[1]);
	bool goodphicms = (PhiCMS >= mPhiCMS[0]) && (PhiCMS < mPhiCMS[1]);
	bool goodEnergy = (kineticEnergyLab / A >= mKineticEnergy[0]) && (kineticEnergyLab / A < mKineticEnergy[1]);
	bool goodtesting = 1;

	bool goodmap =
		(track->GetIsBad_Hira() == 0 && track->GetIsBad_CsI() == 0 && track->GetIsBad_StripX() == 0 &&
		 track->GetIsBad_StripY() == 0);

	bool goodTrack = 1;
	goodTrack &= goodrap;
	goodTrack &= goodPt;
	goodTrack &= goodP;
	goodTrack &= goodpid;
	goodTrack &= goodtheta;
	goodTrack &= goodthetacms;
	goodTrack &= goodphilab;
	goodTrack &= goodphicms;
	goodTrack &= goodEnergy;
	goodTrack &= goodmap;
	goodTrack &= goodtesting;

	goodTrack ? mNTracksPassed++ : mNTracksFailed++;

	return goodTrack;
}

StHbtString HiRATrackCut::Report() {
	string Stemp;
	char Ctemp[100];
	sprintf(Ctemp, "Particle mass:\t%E\n", this->Mass());
	Stemp = Ctemp;
	sprintf(Ctemp, "Particle pT:\t%E - %E\n", mPt[0], mPt[1]);
	Stemp += Ctemp;
	sprintf(Ctemp, "Particle p:\t%E - %E\n", mP[0], mP[1]);
	Stemp += Ctemp;
	sprintf(Ctemp, "Particle rapidity:\t%E - %E\n", mRapidity[0], mRapidity[1]);
	Stemp += Ctemp;
	sprintf(Ctemp, "Number of tracks which passed:\t%ld  Number which failed:\t%ld\n", mNTracksPassed, mNTracksFailed);
	Stemp += Ctemp;
	StHbtString returnThis = Stemp;
	return returnThis;
}
