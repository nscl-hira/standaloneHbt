#include "Cut/HiRATrackCutMonitor.h"
#include "Infrastructure/StHbtTrack.hh"
#include <cstdio>
#include <string>
// #include "StLorentzVector.hh"
#include "TMath.h"

#ifdef __ROOT__
ClassImp(HiRATrackCutMonitor)
#endif

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////
	HiRATrackCutMonitor::HiRATrackCutMonitor(const char *name) { // default constructor
	string s("HiRATrackCutMonitor");
	string n(name);

	mPid = new TH1D((s + n + "_Pid").c_str(), ";PId;Count", 10, 0, 10);
	mEDist = new TH1D((s + n + "_EDist").c_str(), ";KE_{cms}[MeV];Count", 150, 0, 150);
	mELabDist = new TH1D((s + n + "_ELabDist").c_str(), ";KE_{lab}[MeV];Count", 250, 0, 250);
	mPLabDist = new TH1D((s + n + "_PLabDist").c_str(), ";P_{lab}[MeV/c];Count", 900, 100, 1000);
	mPxDist = new TH1D((s + n + "_PxDist").c_str(), ";p_{x}[MeV/c];Count", 400, -700, 500);
	mPyDist = new TH1D((s + n + "_PyDist").c_str(), ";p_{y}[MeV/c];Count", 250, -500, 500);
	mPzDist = new TH1D((s + n + "_PzDist").c_str(), ";p_{z}[MeV/c];Count", 250, -500, 500);
	mPtDist = new TH1D((s + n + "_PtDist").c_str(), ";p_{t}[MeV/c];Count", 250, 0., 1000);
	mPDist = new TH1D((s + n + "_PDist").c_str(), ";P_{cms}[MeV/c];Count", 250, 0., 1000);
	mRapidityDist = new TH1D((s + n + "_RapidityDist").c_str(), ";Rapidity;Count", 100, -0.5, 0.5);

	mfnumtele = new TH1D((s + n + "_fnumtele").c_str(), ";Telescope NO.;Count", 12, 0, 12);
	mfnumcsi = new TH1D((s + n + "_fnumcsi").c_str(), ";CsI NO.;Count", 4, -0, 4);
	mfstripb = new TH1D((s + n + "_fstripb").c_str(), ";EStripb NO.;Count", 32, 0, 32);
	mfstripf = new TH1D((s + n + "_fstripf").c_str(), ";EStripf NO.;Count", 32, 0, 32);

	mPhiLABvsThetaLABDist =
		new TH2D((s + n + "_PhiLABvsThetaLABDist").c_str(), ";#theta_{lab};#phi_{lab}", 70, 20, 90, 110, 150, 260);
	mPhiCMSvsThetaCMSDist =
		new TH2D((s + n + "_PhiCMSvsThetaCMSDist").c_str(), ";#theta_{cms};#phi_{cms}", 180, 0, 180, 200, 100, 300);
	mEnCMSvsThetaCMSDist =
		new TH2D((s + n + "_ECMSvsThetaCMSDist").c_str(), ";#theta_{cms};KE_{cms}", 180, 0, 180, 250, 0, 250);
	mEnCMSvsPhiCMSDist =
		new TH2D((s + n + "_ECMSvsPhiCMSDist").c_str(), ";#phi_{cms};KE_{cms}", 200, 100, 300, 250, 0, 250);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
HiRATrackCutMonitor::HiRATrackCutMonitor(const HiRATrackCutMonitor &cutMoni) {

	mPid = new TH1D(*(cutMoni.mPid));
	mEDist = new TH1D(*(cutMoni.mEDist));
	mELabDist = new TH1D(*(cutMoni.mELabDist));
	mPLabDist = new TH1D(*(cutMoni.mPLabDist));
	mPDist = new TH1D(*(cutMoni.mPDist));
	mPxDist = new TH1D(*(cutMoni.mPxDist));
	mPyDist = new TH1D(*(cutMoni.mPyDist));
	mPzDist = new TH1D(*(cutMoni.mPzDist));
	mPtDist = new TH1D(*(cutMoni.mPtDist));
	mRapidityDist = new TH1D(*(cutMoni.mRapidityDist));

	mfnumtele = new TH1D(*(cutMoni.mfnumtele));
	mfnumcsi = new TH1D(*(cutMoni.mfnumcsi));
	mfstripb = new TH1D(*(cutMoni.mfstripb));
	mfstripf = new TH1D(*(cutMoni.mfstripf));

	mPhiLABvsThetaLABDist = new TH2D(*(cutMoni.mPhiLABvsThetaLABDist));
	mPhiCMSvsThetaCMSDist = new TH2D(*(cutMoni.mPhiCMSvsThetaCMSDist));
	mEnCMSvsThetaCMSDist = new TH2D(*(cutMoni.mEnCMSvsThetaCMSDist));
	mEnCMSvsPhiCMSDist = new TH2D(*(cutMoni.mEnCMSvsPhiCMSDist));
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
HiRATrackCutMonitor::~HiRATrackCutMonitor() {
	delete mPid;

	delete mEDist;
	delete mELabDist;
	delete mPLabDist;
	delete mPxDist;
	delete mPyDist;
	delete mPzDist;
	delete mPtDist;
	delete mPDist;
	delete mRapidityDist;
	delete mfnumtele;
	delete mfnumcsi;
	delete mfstripb;
	delete mfstripf;

	delete mPhiLABvsThetaLABDist;
	delete mPhiCMSvsThetaCMSDist;
	// delete mPhiLABvsPhiCMSDist;
	// delete mThetaLABvsThetaCMSDist;
	delete mEnCMSvsThetaCMSDist;
	// delete mEnLABvsThetaLABDist;
	delete mEnCMSvsPhiCMSDist;
	// delete mEnLABvsPhiLABDist;

	// delete mDeltaPhiVsPhi;
	// delete mDeltaThetaVsTheta;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
void HiRATrackCutMonitor::Fill(const StHbtTrack *track) {

	double px = track->P().x();
	double py = track->P().y();
	double pz = track->P().z();
	double pt = track->P().perp();
	double p = track->P().mag();
	int pid = track->GetPid();
	int aid = track->GetAid();
	int zid = track->GetZid();

	double mass;
	switch (pid) {
	case 2:
		mass = 938.272;
		break; // p
	case 3:
		mass = 1875.610;
		break; // d
	case 4:
		mass = 2808.9182;
		break; // t
	case 5:
		mass = 2808.3870;
		break; // 3He
	case 6:
		mass = 3727.374;
		break; // 4He
	case 0:
		mass = 1000000000;
		break;
	}

	double EnCMS = sqrt(track->P().mag2() + mass * mass) - mass;
	StHbtLorentzVector L;
	L.setVect(track->P());
	L.setE(track->P().massHypothesis(mass));
	double rap = L.rapidity();
	double EnLAB = track->GetEnLab();
	double PLAB = sqrt(pow(EnLAB + mass, 2) - mass * mass);

	double calmass = (pow(p, 2.) - pow(EnCMS, 2.)) / 2. / EnCMS;

	mPid->Fill(pid);
	mEDist->Fill(EnCMS);
	mELabDist->Fill(EnLAB);
	mPLabDist->Fill(PLAB);
	mPxDist->Fill(px);
	mPyDist->Fill(py);
	mPzDist->Fill(pz);
	mPtDist->Fill(pt);
	mPDist->Fill(p);
	mRapidityDist->Fill(rap);
	mfnumtele->Fill(track->GetTelescope());
	mfnumcsi->Fill(track->GetCsI());
	mfstripb->Fill(track->GetEBStrip());
	mfstripf->Fill(track->GetEFStrip());

	double ThetaLAB1 =
		TMath::ACos(
			(track->GetPzLab() / (sqrt(pow(track->P().x(), 2) + pow(track->P().y(), 2) + pow(track->GetPzLab(), 2))))
		) *
		(180 / TMath::Pi());

	double ThetaLAB = track->GetThetaLAB() * 180 / TMath::Pi();
	double ThetaCMS = track->GetThetaCMS() * 180 / TMath::Pi();
	double PhiCMS = track->GetPhi() * 180 / TMath::Pi();
	double PhiLAB = track->GetPhi() * 180 / TMath::Pi();
	mPhiLABvsThetaLABDist->Fill(ThetaLAB, PhiLAB);
	mPhiCMSvsThetaCMSDist->Fill(ThetaCMS, PhiCMS);
	mEnCMSvsThetaCMSDist->Fill(ThetaCMS, EnCMS);
	mEnCMSvsPhiCMSDist->Fill(PhiCMS, EnCMS);
}

void HiRATrackCutMonitor::WriteHistos() {

	mPid->Write();
	mEDist->Write();
	mELabDist->Write();
	mPLabDist->Write();
	mPxDist->Write();
	mPyDist->Write();
	mPzDist->Write();
	mPtDist->Write();
	mPDist->Write();
	mRapidityDist->Write();
	mfnumtele->Write();
	mfnumcsi->Write();
	mfstripb->Write();
	mfstripf->Write();

	// mTeleVsEb->Write();
	// mTeleVsEf->Write();

	// mPtVsThetaLab->Write();
	// mPtVsThetaCMS->Write();
	// mPVsThetaLab->Write();
	// mPVsThetaCMS->Write();
	// mPtVsRap->Write();

	// mEvsRapidityDist->Write();
	// mECMSvsELABDist->Write();
	mPhiLABvsThetaLABDist->Write();
	mPhiCMSvsThetaCMSDist->Write();
	// mPhiLABvsPhiCMSDist->Write();
	// mThetaLABvsThetaCMSDist->Write();
	mEnCMSvsThetaCMSDist->Write();
	// mEnLABvsThetaLABDist->Write();
	mEnCMSvsPhiCMSDist->Write();
	// mEnLABvsPhiLABDist->Write();

	// mDeltaPhiVsPhi->Write();
	// mDeltaThetaVsTheta->Write();
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
