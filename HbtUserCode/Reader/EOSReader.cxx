#include "EOSReader.h"
#include "StPhysicalHelixD.hh"
#include "SystemOfUnits.h"
#include "TChain.h"
#include "TFile.h"
#include "TString.h"
#include "TSystem.h"
#include "TTree.h"
#include "TVector3.h"
#include <math.h>
#include <stdlib.h>
#include <string>
#include <typeinfo>

#include "Infrastructure/StExceptions.hh"
#include "Infrastructure/StHbtEvent.hh"
#include "Infrastructure/StHbtTrack.hh"
#include "Infrastructure/StHbtTrackCollection.hh"
#include "Infrastructure/StHbtVector.hh"

#include "Reader/HiRABadmap.h"
#include "Reader/HiRAPosCali.h"
#include "Reader/HiRARunInfo.h"

ClassImp(EOSReader);

using namespace std;

EOSReader::EOSReader(
	int maxFiles, const char *runinfo, const char *Dir_geoeff, const char *Dir_data, const char *Systemtag,
	const char *Dir_angle, bool IsBadMapAnal, bool IsUsePosCali
) {
	mMaxFiles = maxFiles;
	mDebug = 0;
	mReaderStatus = 0; // "good"
	mRunIndex = 0;
	mEventNO = 0;
	mBadmapNum = 0;
	mSystemtag = string(Systemtag);
	mDirdata = string(Dir_data);
	mDirgeoeff = string(Dir_geoeff);
	mDirAngle = string(Dir_angle);

	mIsBadMapAnal = bool(IsBadMapAnal);

	mTChain = 0;
	mBadmap = new HiRABadmap();
	mRunInfo = new HiRA_RunInfo();
	mRunInfo->Read_RunInfo(runinfo);
	betaCMS = mRunInfo->Get_BetaZ_LabToCM(mSystemtag);

	mRunNum = mRunInfo->Get_RunNum(mSystemtag);

	mPosCali = new HiRAPosCali();
	mPosCali->Read_Hira_PixelAngle(mDirAngle);

	Hira_fmulti = 0;
	uBall_fb = 0;
	uBall_fbhat = 0;
	uBall_fmulti = 0;

	for (int i = 0; i < 30; i++) {
		fnumtel[i] = 0;
		fnumstripf[i] = 0;
		fnumstripb[i] = 0;
		fEnergySifCal[i] = 0;
		fEnergySibCal[i] = 0;
		fEnergycsifCal[i] = 0;
		fKinEnergy[i] = 0;
		fKinEnergyCMS[i] = 0;
		fMomentum[i] = 0;
		fMomentumCMS[i] = 0;
		fTheta[i] = 0;
		fThetaCMS[i] = 0;
		fPhi[i] = 0;
		fZId[i] = 0;
		fAId[i] = 0;
	}

	TDCTriggers_uBallDS_TRG = 0;
	TDCTriggers_uBallHira_TRG = 0;
	TDCTriggers_uBallNW_TRG = 0;
}

//__________________
EOSReader::~EOSReader() {}

//__________________
StHbtString EOSReader::Report() {
	StHbtString temp = "\n This is the EOSReader\n";
	return temp;
}

//__________________
StHbtEvent *EOSReader::ReturnHbtEvent() {
	StHbtEvent *hbtEvent = 0;

	if (mDebug)
		cout << "EOSReader::ReturnHbtEvent()" << endl;

	try {
		hbtEvent = read_with_bad_map();

	} catch (StExceptionEOF e) {
		e.print();
		mReaderStatus = 2;
		return 0;
	} catch (StException e) {
		e.print();
		mReaderStatus = 1;
		return 0;
	}

	if (!hbtEvent)
		cout << "EOSReader::ReturnHbtEvent() - no hbtEvent" << endl;
	return hbtEvent;
}

//__________________

StHbtEvent *EOSReader::read_with_bad_map() {

	int RunNO = mRunInfo->Get_RunNO(mSystemtag, mRunIndex);
	string BadMapVersion = mRunInfo->Get_BadMapVersion(mSystemtag, mRunIndex);
	string Trigger = mRunInfo->Get_Trigger(mSystemtag, mRunIndex);
	mBadmap->Set_BadMapper_Version(mDirgeoeff, BadMapVersion);

	char Nametem[200];
	sprintf(Nametem, "%s/CalibratedData_%d.root", mDirdata.c_str(), RunNO);

	if (!mTChain) {
		mEventNO = 0;
		mTChain = new TChain("E15190", "EOSEvent");
		mTChain->AddFile(Nametem);

		mTChain->SetMakeClass(1);
		mTChain->SetBranchStatus("*", 0);
		mTChain->SetBranchAddress("HiRA.fmulti", &Hira_fmulti);
		mTChain->SetBranchAddress("uBall.fb", &uBall_fb);
		mTChain->SetBranchAddress("uBall.fbhat", &uBall_fbhat);
		mTChain->SetBranchAddress("uBall.fmulti", &uBall_fmulti);
		mTChain->SetBranchAddress("HiRA.fnumtel", fnumtel);
		mTChain->SetBranchAddress("HiRA.fnumcsi", fnumcsi);
		mTChain->SetBranchAddress("HiRA.fnumstripf", fnumstripf);
		mTChain->SetBranchAddress("HiRA.fnumstripb", fnumstripb);
		mTChain->SetBranchAddress("HiRA.fEnergySifCal", fEnergySifCal);
		mTChain->SetBranchAddress("HiRA.fEnergySibCal", fEnergySibCal);
		mTChain->SetBranchAddress("HiRA.fTheta", fTheta);
		mTChain->SetBranchAddress("HiRA.fPhi", fPhi);
		mTChain->SetBranchAddress("HiRA.fKinEnergy", fKinEnergy);
		mTChain->SetBranchAddress("HiRA.fMomentum", fMomentum);
		mTChain->SetBranchAddress("HiRA.fKinEnergyCMS", fKinEnergyCMS);
		mTChain->SetBranchAddress("HiRA.fMomentumCMS", fMomentumCMS);
		mTChain->SetBranchAddress("HiRA.fThetaCMS", fThetaCMS);
		mTChain->SetBranchAddress("HiRA.fAId", fAId);
		mTChain->SetBranchAddress("HiRA.fZId", fZId);
		mTChain->SetBranchAddress("TDCTriggers.uBall_DS_TRG", &TDCTriggers_uBallDS_TRG);
		mTChain->SetBranchAddress("TDCTriggers.uBallHiRA_TRG", &TDCTriggers_uBallHira_TRG);
		mTChain->SetBranchAddress("TDCTriggers.uBallNW_TRG", &TDCTriggers_uBallNW_TRG);
	}

	int nevents = mTChain->GetEntries();
	mTChain->GetEntry(mEventNO);
	mEventNO++;
	double mass;
	int pid;

	if (nevents < mEventNO) {
		throw StExceptionEOF("EOSReader::read()");
	}

	auto hbtEvent = new StHbtEvent();
	hbtEvent->SetEventNumber(mEventNO);
	hbtEvent->SetRunNumber(RunNO);
	hbtEvent->SetCtbMult(0);
	hbtEvent->SetZdcAdcEast(0);
	hbtEvent->SetZdcAdcWest(0);
	hbtEvent->SetNumberOfTpcHits(0);
	hbtEvent->SetNumberOfTracks(Hira_fmulti);
	hbtEvent->SetNumberOfGoodTracks(Hira_fmulti);
	hbtEvent->SetUncorrectedNumberOfPositivePrimaries(0);
	hbtEvent->SetUncorrectedNumberOfNegativePrimaries(0);
	hbtEvent->SetUncorrectedNumberOfPrimaries(uBall_fmulti);
	hbtEvent->SetReactionPlane(0, 0);
	hbtEvent->SetReactionPlaneError(0, 0);
	hbtEvent->SetReactionPlaneSubEventDifference(0, 0);
	hbtEvent->SetTriggerWord(0);
	hbtEvent->SetTriggerActionWord(0);
	hbtEvent->SetL3TriggerAlgorithm(0, 0);
	StThreeVectorF vertex(0., 0., 0.);
	hbtEvent->SetPrimVertPos(vertex);
	hbtEvent->SetBhat(uBall_fbhat);
	hbtEvent->SetEtrans(0);

	hbtEvent->SetuBallDS_TRG(TDCTriggers_uBallDS_TRG);
	hbtEvent->SetuBallHira_TRG(TDCTriggers_uBallHira_TRG);
	hbtEvent->SetuBallNW_TRG(TDCTriggers_uBallNW_TRG);

	StHbtTrackCollection *mTrackCollection = hbtEvent->TrackCollection();

	for (int i = 0; i < Hira_fmulti; i++) {
		StHbtTrack *trackCopy = new StHbtTrack;
		trackCopy->SetHiddenInfo(0);
		trackCopy->SetCharge(fZId[i]);
		trackCopy->SetNHits(30);

		//---- Set dummy values ----//

		trackCopy->SetNHitsDedx(0);
		trackCopy->SetNSigmaElectron(0.);
		trackCopy->SetNSigmaPion(0.);
		trackCopy->SetNSigmaKaon(0.);
		trackCopy->SetNSigmaProton(0.);

		trackCopy->SetPidProbElectron(0.);
		trackCopy->SetPidProbPion(0.);
		trackCopy->SetPidProbKaon(0.);
		trackCopy->SetPidProbProton(0.);
		trackCopy->SetdEdx(100.);
		trackCopy->SetDCAxy(0.);
		trackCopy->SetDCAz(0.);
		trackCopy->SetDCAxyGlobal(0.);
		trackCopy->SetDCAzGlobal(0.);
		trackCopy->SetChiSquaredXY(0.);
		trackCopy->SetChiSquaredZ(0.);

		//---- Get Angle ----//
		// in radian

		auto thetalab = mPosCali->GetTheta(fnumtel[i], fnumstripf[i], fnumstripb[i]) * DegToRad();
		auto philab = mPosCali->GetPhi(fnumtel[i], fnumstripf[i], fnumstripb[i]) * DegToRad();

		pid = 0;
		mass = 1000000000;

		if (fAId[i] == 1 && fZId[i] == 1) {
			mass = 938.272;
			pid = fAId[i] + fZId[i];
		} // p
		if (fAId[i] == 2 && fZId[i] == 1) {
			mass = 1875.610;
			pid = fAId[i] + fZId[i];
		} // d
		if (fAId[i] == 3 && fZId[i] == 1) {
			mass = 2808.9182;
			pid = fAId[i] + fZId[i];
		} // t
		if (fAId[i] == 3 && fZId[i] == 2) {
			mass = 2808.3870;
			pid = fAId[i] + fZId[i];
		} // He3
		if (fAId[i] == 4 && fZId[i] == 2) {
			mass = 3727.374;
			pid = fAId[i] + fZId[i];
		} // He4

		// n1 1 0 939.5654204759348
		// h1 0 1 938.7830734813572
		// h2 1 1 1876.1239277295715
		// h3 2 1 2809.4321181490463
		// he3 1 2 2809.413526132233
		// li3 0 3 2823.1490382533207
		// h4 3 1 3750.597537894952
		// he4 2 2 3728.401325537765

		auto totEnergy = fKinEnergy[i] + mass; // in MeV
		auto plab = std::sqrt(std::pow(totEnergy, 2.) - std::pow(mass, 2.));
		auto px = plab * std::sin(thetalab) * std::cos(philab);
		auto py = plab * std::sin(thetalab) * std::sin(philab);
		auto pz = plab * std::cos(thetalab);

		auto gamma = 1. / std::sqrt(1. - std::pow(betaCMS, 2.));
		auto pznew = gamma * (pz - betaCMS * totEnergy);

		double thetaCMS = TMath::ACos(pznew / TMath::Sqrt(px * px + py * py + pznew * pznew));

		StHbtThreeVector v(px, py, pznew);
		trackCopy->SetEnLab(fKinEnergy[i]);
		trackCopy->SetEnCMS(TMath::Sqrt(px * px + py * py + pznew * pznew + mass * mass) - mass);
		trackCopy->SetPzLab(pz);
		trackCopy->SetPhi(philab);

		trackCopy->SetThetaCMS(thetaCMS);
		trackCopy->SetThetaLAB(thetalab);
		trackCopy->SetDeltaTheta(0);
		trackCopy->SetDeltaPhi(0);

		trackCopy->SetP(v);
		trackCopy->SetPt(sqrt(px * px + py * py));

		const StThreeVectorD p((double)px, (double)py, (double)pznew);
		const StThreeVectorD origin(0., 0., 0.);
		StPhysicalHelixD helix(p, origin, (double)(0.) * kilogauss, (double)(1));
		trackCopy->SetHelix(helix);

		trackCopy->SetWeight(0);
		trackCopy->SetParentIndex(0);

		trackCopy->SetPid(pid);
		trackCopy->SetAid(fAId[i]);
		trackCopy->SetZid(fZId[i]);
		trackCopy->SetTelescope(fnumtel[i]);
		trackCopy->SetCsI(fnumcsi[i]);
		trackCopy->SetEBStrip(fnumstripb[i]);
		trackCopy->SetEFStrip(fnumstripf[i]);

		if (mIsBadMapAnal == 1) {
			bool IsBad_Hira = mBadmap->IsBad_Hira(fnumtel[i]);
			bool IsBad_CsI = mBadmap->IsBad_CsI(fnumtel[i], fnumstripf[i], fnumstripb[i]);
			bool IsBad_StripX = mBadmap->IsBad_StripX(fnumtel[i], fnumstripf[i]);
			bool IsBad_StripY = mBadmap->IsBad_StripY(fnumtel[i], fnumstripb[i]);

			if (IsBad_Hira) {
				trackCopy->SetIsBad_Hira(1);
			} else {
				trackCopy->SetIsBad_Hira(0);
			}
			if (IsBad_CsI) {
				trackCopy->SetIsBad_CsI(1);
			} else {
				trackCopy->SetIsBad_CsI(0);
			}
			if (IsBad_StripX) {
				trackCopy->SetIsBad_StripX(1);
			} else {
				trackCopy->SetIsBad_StripX(0);
			}
			if (IsBad_StripY) {
				trackCopy->SetIsBad_StripY(1);
			} else {
				trackCopy->SetIsBad_StripY(0);
			}

			if (IsBad_Hira || IsBad_CsI || IsBad_StripX || IsBad_StripY) {
				continue;
			}
		}

		mTrackCollection->push_back(trackCopy);

	} // each particle in the same event

	if ((mEventNO) == nevents) {
		mTChain->Delete();
		mTChain = 0;
		mRunIndex++;
	}
	return hbtEvent;
}
