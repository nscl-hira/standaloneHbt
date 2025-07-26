#ifndef HiRAEventCutMonitor_hh
#define HiRAEventCutMonitor_hh

#include "Infrastructure/StHbtTypes.hh"
#include "Infrastructure/StHbtEvent.hh"
#include "Infrastructure/StHbtPair.hh"
#include "Base/StHbtCutMonitor.hh"

#include "TH1D.h"
#include "TH2D.h"
#include "TMath.h"

class HiRAEventCutMonitor : public StHbtCutMonitor{
	
private:
  
	TH1D* mBhatHisto;
	TH1D* mNuBallMultHisto;
	TH1D* mNHiRAMultHisto;

	TH1D* muBallDS_TRGHisto;
	TH1D* muBallHira_TRGHisto;
	TH1D* muBallNW_TRGHisto;



	//ver 2 events with >2 p
	/* TH1D* mNHiRAMultHisto_2p;
	TH1D* mNHiRAMultHisto_2d;
	TH1D* mNHiRAMultHisto_2t;
	TH1D* mNHiRAMultHisto_2He3;
	TH1D* mNHiRAMultHisto_2He4; */


	TH2D* mBhatVsuBallMultHisto;

	//old
	/* TH1D* mEtransHisto;
	TH2D* mEtransVs4PiMultHisto;
	TH1D* mN4PiMultHisto; */
	
public:
	HiRAEventCutMonitor();
	virtual ~HiRAEventCutMonitor();

	virtual StHbtString Report(); 
	virtual void Fill(const StHbtEvent* event);
	virtual void Finish();


	// These dummy Fill() functions were introduced to remove a compiler
	//   warning related to overloaded base-class Fill() functions being 
	//   hidden by a single version of Fill() in this derived class

	void Fill(const StHbtParticleCollection* d) {;}
	void Fill(const StHbtEvent *d1, const StHbtParticleCollection* d2) {;}
	void Fill(const StHbtPair* d) {;}
	void Fill(const StHbtKink* d) {;}
	void Fill(const StHbtV0* d) {;}
	void Fill(const StHbtTrack* d) {;}

	//old
	/* TH1D* N4PiMultHisto()  { return mN4PiMultHisto;}
	TH1D* EtransHisto()  { return mEtransHisto;}
	TH2D* EtransVs4PiMultHisto()  { return mEtransVs4PiMultHisto;} */

	TH1D* NuBallMultHisto() {return mNuBallMultHisto;}
	TH1D* NHiRAMultHisto()  { return mNHiRAMultHisto;}
	TH2D* BhatVsuBallMultHisto() {return mBhatVsuBallMultHisto;}
	TH1D* BhatHisto() {return mBhatHisto;}
	TH1D* uBallDS_TRGHisto() {return muBallDS_TRGHisto;}
	TH1D* uBallHira_TRGHisto() {return muBallHira_TRGHisto;}
	TH1D* uBallNW_TRGHisto() {return muBallNW_TRGHisto;}

	
	/* TH1D* NHiRAMultHisto_2p()  { return mNHiRAMultHisto_2p;}
	TH1D* NHiRAMultHisto_2d()  { return mNHiRAMultHisto_2d;}
	TH1D* NHiRAMultHisto_2t()  { return mNHiRAMultHisto_2t;}
	TH1D* NHiRAMultHisto_2He3()  { return mNHiRAMultHisto_2He3;}
	TH1D* NHiRAMultHisto_2He4()  { return mNHiRAMultHisto_2He4;} */

  

#ifdef __ROOT__ 
	ClassDef(HiRAEventCutMonitor, 1)
#endif
};

#endif
