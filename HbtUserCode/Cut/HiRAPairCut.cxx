/***************************************************************************
 *
 * $Id: HiRAPairCut.cxx,v 1.3 2000/01/25 17:35:02 laue Exp $
 *
 * Author: Mike Lisa, Ohio State, lisa@mps.ohio-state.edu
 ***************************************************************************
 *
 * Description: part of STAR HBT Framework: StHbtMaker package
 *   a do-nothing pair cut that simply says "true" to every pair
 *
 ***************************************************************************
 *
 * $Log: HiRAPairCut.cxx,v $
 * Revision 1.3  2000/01/25 17:35:02  laue
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
 * Revision 1.2  1999/07/06 22:33:21  lisa
 * Adjusted all to work in pro and new - dev itself is broken
 *
 * Revision 1.1.1.1  1999/06/29 16:02:56  lisa
 * Installation of StHbtMaker
 *
 **************************************************************************/

#include "Cut/HiRAPairCut.h"
#include "Infrastructure/StHbtParticle.hh"
#include "Infrastructure/StHbtTrack.hh"
#include "TMath.h"
#include <cstdio>
#include <string>
#ifdef __ROOT__
ClassImp(HiRAPairCut);
#endif

//__________________
HiRAPairCut::HiRAPairCut() { mNPairsPassed = mNPairsFailed = 0; }

bool HiRAPairCut::Pass(const StHbtPair *pair) {
	// two particle doesnt hit the same tele
	short telescope1 = pair->track1()->GetTelescope();
	short telescope2 = pair->track2()->GetTelescope();

	short csi1 = pair->track1()->GetCsI();
	short csi2 = pair->track2()->GetCsI();

	short ef1 = pair->track1()->GetEFStrip();
	short ef2 = pair->track2()->GetEFStrip();

	short eb1 = pair->track1()->GetEBStrip();
	short eb2 = pair->track2()->GetEBStrip();

	// \sqrt((px1+px2)^2+\cdots)
	double pPairCMS = sqrt(
		pow(pair->track1()->FourMomentum().vect().x() + pair->track2()->FourMomentum().vect().x(), 2) +
		pow(pair->track1()->FourMomentum().vect().y() + pair->track2()->FourMomentum().vect().y(), 2) +
		pow(pair->track1()->FourMomentum().vect().z() + pair->track2()->FourMomentum().vect().z(), 2)
	);

	double pPairLab = sqrt(
		pow(pair->track1()->FourMomentum().vect().x() + pair->track2()->FourMomentum().vect().x(), 2) +
		pow(pair->track1()->FourMomentum().vect().y() + pair->track2()->FourMomentum().vect().y(), 2) +
		pow(pair->track1()->GetPzLab() + pair->track2()->GetPzLab(), 2)
	);

	double ktpaircms = fabs(pair->kT());

	double q = fabs(pair->qInv());

	double theta1 = TMath::ACos(
						(pair->track1()->GetPzLab() /
						 (sqrt(
							 pow(pair->track1()->FourMomentum().vect().x(), 2) +
							 pow(pair->track1()->FourMomentum().vect().y(), 2) + pow(pair->track1()->GetPzLab(), 2)
						 )))
					) *
					(180 / TMath::Pi());

	double theta2 = TMath::ACos(
						(pair->track2()->GetPzLab() /
						 (sqrt(
							 pow(pair->track2()->FourMomentum().vect().x(), 2) +
							 pow(pair->track2()->FourMomentum().vect().y(), 2) + pow(pair->track2()->GetPzLab(), 2)
						 )))
					) *
					(180 / TMath::Pi());

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
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////
	bool goodPair = 1;

	goodPair &= !(telescope1 == telescope2 && csi1 == csi2);
	goodPair &= !(telescope1 == telescope2 && ef1 == ef2);
	goodPair &= !(telescope1 == telescope2 && eb1 == eb2);
	goodPair &= ((pPairCMS > pcmsmin) && (pPairCMS < pcmsmax));
	goodPair &= ((pPairLab > plabmin) && (pPairLab < plabmax));
	goodPair &= ((ktpaircms > pairkTmin) && (ktpaircms < pairkTmax));

	goodPair ? mNPairsPassed++ : mNPairsFailed++;

	return goodPair;
}

//__________________
StHbtString HiRAPairCut::Report() {
	string Stemp = "HiRA Pair Cut \n";
	char Ctemp[100];
	sprintf(Ctemp, "Number of pairs which passed:\t%ld  Number which failed:\t%ld\n", mNPairsPassed, mNPairsFailed);
	Stemp += Ctemp;
	StHbtString returnThis = Stemp;
	return returnThis;
}
//__________________

void HiRAPairCut::SetPCMS(double min, double max) {
	pcmsmin = min;
	pcmsmax = max;
}
void HiRAPairCut::SetPLab(double min, double max) {
	plabmin = min;
	plabmax = max;
}
void HiRAPairCut::SetkT(double min, double max) {
	pairkTmin = min;
	pairkTmax = max;
}
void HiRAPairCut::SetqInv(double min, double max) {
	qInvmin = min;
	qInvmax = max;
}
