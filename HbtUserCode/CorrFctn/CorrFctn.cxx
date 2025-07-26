#include "CorrFctn/CorrFctn.h"
#include "TMath.h"
#include "TString.h"
#include <cstdio>

#ifdef __ROOT__
ClassImp(CorrFctn);
#endif

CorrFctn::CorrFctn(const std::string &title, const int &nbins, const float &QinvLo, const float &QinvHi) {
	mPairCut = 0;

	mNumerator = new TH1D(Form("%s%s", title.c_str(), "Num"), "Numerator", nbins, QinvLo, QinvHi);
	mDenominator = new TH1D(Form("%s%s", title.c_str(), "Den"), "Denominator", nbins, QinvLo, QinvHi);

	mNumerator->Sumw2();
	mDenominator->Sumw2();
}

//____________________________
CorrFctn::~CorrFctn() {
	delete mNumerator;
	delete mDenominator;
}

void CorrFctn::WriteOutHistos() {

	mNumerator->Write();
	mDenominator->Write();
}

void CorrFctn::Finish() {}

StHbtString CorrFctn::Report() {
	string stemp = "Qinv Correlation Function Report:\n";
	char ctemp[100];
	sprintf(ctemp, "Number of entries in numerator:\t%E\n", mNumerator->GetEntries());
	stemp += ctemp;
	sprintf(ctemp, "Number of entries in denominator:\t%E\n", mDenominator->GetEntries());

	if (mPairCut) {
		sprintf(ctemp, "Here is the PairCut specific to this CorrFctn\n");
		stemp += ctemp;
		stemp += mPairCut->Report();
	} else {
		sprintf(ctemp, "No PairCut specific for this CorrFctn\n");
		stemp += ctemp;
	}
	StHbtString returnThis = stemp;
	return returnThis;
}

void CorrFctn::AddRealPair(const StHbtPair *pair) {

	if (mPairCut) {
		if (!(mPairCut->Pass(pair)))
			return;
	}

	double mass;
	double mass2;
	switch (pair->track1()->GetPid()) {

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
	}

	switch (pair->track2()->GetPid()) {

	case 2:
		mass2 = 938.272;
		break; // p
	case 3:
		mass2 = 1875.610;
		break; // d
	case 4:
		mass2 = 2808.9182;
		break; // t
	case 5:
		mass2 = 2808.3870;
		break; // 3He
	case 6:
		mass2 = 3727.374;
		break; // 4He
	case 0:
		mass2 = 1000000000;
	}

	double px1 = pair->track1()->FourMomentum().x();
	double py1 = pair->track1()->FourMomentum().y();
	double pz1 = pair->track1()->FourMomentum().z();
	double pz1lab = pair->track1()->GetPzLab();
	double E1 = ::sqrt(px1 * px1 + py1 * py1 + pz1 * pz1 + mass * mass);

	double px2 = pair->track2()->FourMomentum().x();
	double py2 = pair->track2()->FourMomentum().y();
	double pz2 = pair->track2()->FourMomentum().z();
	double pz2lab = pair->track2()->GetPzLab();
	double E2 = ::sqrt(px2 * px2 + py2 * py2 + pz2 * pz2 + mass2 * mass2);

	double rap1 = pair->track1()->FourMomentum().rapidity();
	double rap2 = pair->track2()->FourMomentum().rapidity();
	double pt1 = ::sqrt(pow(px1, 2.) + pow(py1, 2.));
	double pt2 = ::sqrt(pow(px2, 2.) + pow(py2, 2.));
	double pcms1 = ::sqrt(pow(pt1, 2.) + pow(pz1, 2.));
	double pcms2 = ::sqrt(pow(pt2, 2.) + pow(pz2, 2.));

	double theta1 =
		TMath::ACos(pair->track1()->GetPzLab() / sqrt(px1 * px1 + py1 * py1 + pow(pair->track1()->GetPzLab(), 2))) *
		(180 / TMath::Pi());

	double theta2 =
		TMath::ACos(pair->track2()->GetPzLab() / sqrt(px2 * px2 + py2 * py2 + pow(pair->track2()->GetPzLab(), 2))) *
		(180 / TMath::Pi());

	//************************************************************************************************
	double phi1 = TMath::ATan((pair->track1()->FourMomentum().vect().y() / pair->track1()->FourMomentum().vect().x())) *
				  (180 / TMath::Pi());
	double phi2 = TMath::ATan((pair->track2()->FourMomentum().vect().y() / pair->track2()->FourMomentum().vect().x())) *
				  (180 / TMath::Pi());

	// converting phi back to the second and third quadrant as recorded in the original data.
	if (phi1 < 0. && phi1 > -90.)
		phi1 += 180.;
	else if (phi1 < -90. && phi1 > -180.)
		phi1 += 360.;
	else if (phi1 > 0. && phi1 < 90.)
		phi1 += 180.;
	else if (phi1 > 270. && phi1 < 360.)
		phi1 -= 180.;

	if (phi2 < 0. && phi2 > -90.)
		phi2 += 180.;
	else if (phi2 < -90. && phi2 > -180.)
		phi2 += 360.;
	else if (phi2 > 0. && phi2 < 90.)
		phi2 += 180.;
	else if (phi2 > 270. && phi2 < 360.)
		phi2 -= 180.;

	//************************************************************************************************

	auto mu = mass * mass2 / (mass + mass2);
	auto velocity1 = pair->track1()->FourMomentum().vect() / mass;
	auto velocity2 = pair->track2()->FourMomentum().vect() / mass2;
	auto q = mu * (velocity2 - velocity1).mag();
	mNumerator->Fill(q);
}

void CorrFctn::AddMixedPair(const StHbtPair *pair) {

	if (mPairCut) {
		if (!(mPairCut->Pass(pair)))
			return;
	}

	double mass;
	double mass2;

	switch (pair->track1()->GetPid()) {

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
	}

	switch (pair->track2()->GetPid()) {

	case 2:
		mass2 = 938.272;
		break; // p
	case 3:
		mass2 = 1875.610;
		break; // d
	case 4:
		mass2 = 2808.9182;
		break; // t
	case 5:
		mass2 = 2808.3870;
		break; // 3He
	case 6:
		mass2 = 3727.374;
		break; // 4He
	case 0:
		mass2 = 1000000000;
	}

	auto mu = mass * mass2 / (mass + mass2);
	auto velocity1 = pair->track1()->FourMomentum().vect() / mass;
	auto velocity2 = pair->track2()->FourMomentum().vect() / mass2;
	auto q = mu * (velocity2 - velocity1).mag();
	mDenominator->Fill(q, 1.);
}
