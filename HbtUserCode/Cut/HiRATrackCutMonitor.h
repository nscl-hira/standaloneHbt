#ifndef HiRATrackCutMonitor_hh
#define HiRATrackCutMonitor_hh

class StHbtTrack;

#include "Base/StHbtCutMonitor.hh"
#include "Infrastructure/StHbtPair.hh"
#include "Infrastructure/StHbtTypes.hh"

#include "TH1D.h"
#include "TH2D.h"
#include "TH3D.h"

class HiRATrackCutMonitor : public StHbtCutMonitor {

private:
	TH1D *mPid;	 // pid
	TH1D *mmass; // mass

	TH1D *mRapidityDist; // rapidity
	TH1D *mEDist;		 // Ke CMS
	TH1D *mELabDist;	 // Ke Lab
	TH1D *mPLabDist;	 // momentum lab
	TH1D *mPDist;		 // momentum cms
	TH1D *mPxDist;		 // px cms
	TH1D *mPyDist;		 // py cms
	TH1D *mPzDist;		 // pz cms
	TH1D *mPtDist;		 // pt cms
	TH1D *mfnumtele;	 // tele
	TH1D *mfnumcsi;		 // csi
	TH1D *mfstripb;		 // eb
	TH1D *mfstripf;		 // ef

	// TH2D* mTeleVsEb;					//tele vs eb
	// TH2D* mTeleVsEf;					//tele vs ef

	// TH2D* mPtVsThetaLab;				//pt vs theta in lab frame
	// TH2D* mPtVsThetaCMS;				//pt vs theta in cms frame
	// TH2D* mPVsThetaLab; 				//p  vs theta in lab frame
	// TH2D* mPVsThetaCMS;				//p  vs theta in cms frame
	// TH2D* mPtVsRap;					//pt vs rap in cms frame

	// TH2D* mEvsRapidityDist;			//Ke_CMS vs rap
	// TH2D* mECMSvsELABDist;			//Ke_CMS vs Ke_lab
	TH2D *mPhiLABvsThetaLABDist; // phi vs theta in lab
	TH2D *mPhiCMSvsThetaCMSDist; // phi vs theta in cms
	// TH2D* mPhiLABvsPhiCMSDist;		//phi lab vs phi cms
	// TH2D* mThetaLABvsThetaCMSDist;	//theta lab vs theta cms
	TH2D *mEnCMSvsThetaCMSDist; // Ke_CMS vs thetaCMS
	// TH2D* mEnLABvsThetaLABDist;		//Ke_lab vs thetaLAB
	TH2D *mEnCMSvsPhiCMSDist; // Ke_CMS vs phiCMS
							  // TH2D* mEnLABvsPhiLABDist;			//Ke_LAB vs phiLAB

	// TH2D* mDeltaThetaVsTheta;
	// TH2D* mDeltaPhiVsPhi;
public:
	HiRATrackCutMonitor(const char *); // default constructor
	HiRATrackCutMonitor(const HiRATrackCutMonitor &cutMoni);
	virtual ~HiRATrackCutMonitor();

	virtual void Fill(const StHbtTrack *track);

	void Fill(const StHbtParticleCollection *d) { ; }
	void Fill(const StHbtEvent *d1, const StHbtParticleCollection *d2) { ; }
	void Fill(const StHbtPair *d) { ; }
	void Fill(const StHbtKink *d) { ; }
	void Fill(const StHbtV0 *d) { ; }
	void Fill(const StHbtEvent *d) { ; }

	void WriteHistos();

#ifdef __ROOT__
	ClassDef(HiRATrackCutMonitor, 1)
#endif
};

#endif
