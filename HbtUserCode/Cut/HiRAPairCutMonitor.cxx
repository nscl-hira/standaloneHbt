/***************************************************************************
 *
 * $Id: HiRAEventCutMonitor.cxx,v 1.1 2002/04/09 15:14:46 HiRA Exp $
 *
 * Author: HiRA Lopez Noriega , Ohio State, HiRA@pacific.mps.ohio-state.edu
 *
 ***************************************************************************
 *
 * Event Cut Monitor that plots just the tracks that passed 
 * HiRAStarStandardEventCut in the multiplicity plot
 * Plots: EventMultiplicity (just # of tracks that passed the event cut),
 * ZVertexPosition, and 2D plot: EventMultiplicity vs Tracks (# of tracks that 
 * passed the cuts vs # of tracks in the event) 
 * 
 ***************************************************************************
 *
 * $Log: HiRAEventCutMonitor.cxx,v $
 * Revision 1.1  2002/04/09 15:14:46  HiRA
 * Event Cut Monitor for HiRAStarStandardEventCut
 *
 *
 **************************************************************************/





#include "Infrastructure/StHbtPair.hh"
#include "Infrastructure/StHbtTypes.hh"
#include "Cut/HiRAPairCutMonitor.h"
#include <cstdio>
#include "TMath.h"
//#include <string>

#ifdef __ROOT__ 
ClassImp(HiRAPairCutMonitor)
#endif

HiRAPairCutMonitor::HiRAPairCutMonitor(){
	
	mKtHisto = new TH1D("KtDist",";Count;pair kT[MeV/c]",500,0.,1500);
	mKtHisto->SetDirectory(0);
	mPCMSHisto = new TH1D("PCMSsum",";Count;pair P_{cms}[MeV/c]",500,0.,2000);
	mPCMSHisto->SetDirectory(0);
	mPLabHisto = new TH1D("PLABsum",";Count;pair P_{lab}",500,0.,2000);
	mPLabHisto->SetDirectory(0);
	//meaHisto = new TH1D("mea","mea",120,0.,360);
	//meaHisto->SetDirectory(0);

	//mRapVsqInv1 = new TH2D("mRapVsqInv1",";Rapidity;q[MeV/c]",35,0,140,600,-0.4,0.4);
	//mRapVsqInv2= new TH2D("mRapVsqInv2","mRapVsqInv2",35,0,140,600,-0.4,0.4);
	//mThetaLabVsqInv1= new TH2D("mThetaLabVsqInv1",";#theta_{lab};q[MeV/c]",35,0,140,180,0,180);
	//mThetaLabVsqInv2= new TH2D("mThetaLabVsqInv2","mThetaLabVsqInv2",35,0,140,180,0,180);

	//mkTVsqInv= new TH2D("mkTVsqInv",";kT[MeV/c];q[MeV/c]",35,0,140,500,0.,1500);
	//mPCMSVsqInv= new TH2D("mPCMSVsqInv",";pair P_{cms};q[MeV/c]",35,0,140,500,0.,2000);



	//mTelescopeVsqInv1= new TH2D("mTelescopeVsqInv1",";Telescope NO.;q[MeV/c]",35,0,140,12,0,12);
	//mTelescopeVsqInv2= new TH2D("mTelescopeVsqInv2","mTelescopeVsqInv2",35,0,140,12,0,12);
	//mCsIVsqInv1= new TH2D("mCsIVsqInv1",";CsI NO.;q[MeV/c]",35,0,140,4,0,4);
	//mCsIVsqInv2= new TH2D("mCsIVsqInv2","mCsIVsqInv2",35,0,140,4,0,4);
	//mEBVsqInv1= new TH2D("mEBVsqInv1",";EStripb NO.;q[MeV/c]",35,0,140,32,0,32);
	//mEBVsqInv2= new TH2D("mEBVsqInv2","mEBVsqInv2",35,0,140,32,0,32);
	//mEFVsqInv1= new TH2D("mEFVsqInv1",";EStripf NO.;q[MeV/c]",35,0,140,32,0,32);
	//mEFVsqInv2= new TH2D("mEFVsqInv2","mEFVsqInv2",35,0,140,32,0,32);
  
  
}
//------------------------------
HiRAPairCutMonitor::~HiRAPairCutMonitor(){
	delete mKtHisto;
	delete mPCMSHisto;
	delete mPLabHisto;
	//delete meaHisto;

	//delete mRapVsqInv1;
	//delete mRapVsqInv2;
	//delete mThetaLabVsqInv1;
	//delete mThetaLabVsqInv2;

	//delete mkTVsqInv;
	//delete mPCMSVsqInv;
	//delete mTelescopeVsqInv1;
	//delete mTelescopeVsqInv2;
	//delete mCsIVsqInv1;
	//delete mCsIVsqInv2;
	//delete mEBVsqInv1;
	//delete mEBVsqInv2;
	//delete mEFVsqInv1;
	//delete mEFVsqInv2;
  
  
  
}

//------------------------------
void HiRAPairCutMonitor::Fill(const StHbtPair* pair){

  double Kt = fabs(pair->kT());

  //  double P = fabs(pair->mInv());

  double pi=3.1415926535;
  double pxTotal = pair->fourMomentumSum().x();
  double pyTotal = pair->fourMomentumSum().y();
  double Phi = atan2(pyTotal,pxTotal)*180.0/pi;
  if (Phi<0.0) Phi+=360.0;

// it is easier for the cuts I'm doing to rotate Phi by 45 degrees
// Phip => Phi-45 so 45=>0
// The usual y (up spin in TPC) axis is now at 45 degrees
  double Phip=Phi-45;
  if (Phip<0.0) Phip+=360.0;

  double PCMS = sqrt(pow(pair->track1()->FourMomentum().vect().x() + pair->track2()->FourMomentum().vect().x(),2) + 
		      pow(pair->track1()->FourMomentum().vect().y() + pair->track2()->FourMomentum().vect().y(),2) +
		      pow(pair->track1()->FourMomentum().vect().z() + pair->track2()->FourMomentum().vect().z(),2));


  double PLab = sqrt(pow(pair->track1()->FourMomentum().vect().x() + pair->track2()->FourMomentum().vect().x(),2) + 
		      pow(pair->track1()->FourMomentum().vect().y() + pair->track2()->FourMomentum().vect().y(),2) +
		      pow(pair->track1()->GetPzLab() + pair->track2()->GetPzLab(),2));



  double q = fabs(pair->qInv());
  double rap1 = pair->track1()->FourMomentum().rapidity();	
  double rap2 = pair->track2()->FourMomentum().rapidity();	
  
  
  double theta1= TMath::ACos(( pair->track1()->GetPzLab() / (sqrt( pow(pair->track1()->FourMomentum().vect().x(),2) + pow(pair->track1()->FourMomentum().vect().y(),2) + pow(pair->track1()->GetPzLab(),2) )) ))*(180/TMath::Pi());
  
  double theta2=TMath::ACos(( pair->track2()->GetPzLab() / (sqrt( pow(pair->track2()->FourMomentum().vect().x(),2) + pow(pair->track2()->FourMomentum().vect().y(),2) + pow(pair->track2()->GetPzLab(),2) )) ))*(180/TMath::Pi());
  
  int tele1 = pair->track1()->GetTelescope();
  int tele2 = pair->track2()->GetTelescope();
  
  int csi1 = pair->track1()->GetCsI();
  int csi2 = pair->track2()->GetCsI();
  
  int eb1 = pair->track1()->GetEBStrip();
  int eb2 = pair->track2()->GetEBStrip();
  int ef1 = pair->track1()->GetEFStrip();
  int ef2 = pair->track2()->GetEFStrip();
  
  
  mKtHisto->Fill(Kt,1.);
  mPCMSHisto->Fill(PCMS,1.);
  mPLabHisto->Fill(PLab,1.);
  //meaHisto->Fill(Phip,1.);
  
  
/*   mRapVsqInv1->Fill(q,rap1);
  mRapVsqInv2->Fill(q,rap2);
  mThetaLabVsqInv1->Fill(q,rap1);
  mThetaLabVsqInv2->Fill(q,rap1);
  
  mkTVsqInv->Fill(q,Kt);
  mPCMSVsqInv->Fill(q,PCMS);
  
  mTelescopeVsqInv1->Fill(q,tele1);
  mTelescopeVsqInv2->Fill(q,tele2);
  mCsIVsqInv1->Fill(q,csi1);
  mCsIVsqInv2->Fill(q,csi2);
  mEBVsqInv1->Fill(q,eb1);
  mEBVsqInv2->Fill(q,eb2);
  mEFVsqInv1->Fill(q,ef1);
  mEFVsqInv2->Fill(q,ef2); */
  
  
  
  
}
//------------------------------
void HiRAPairCutMonitor::Finish(){
  cout << " entries in Kt histogram : " << mKtHisto->Integral() << endl;
  cout << " entries in PCMS histogram : " << mPCMSHisto->Integral() << endl;
  cout << " entries in PLab histogram : " << mPLabHisto->Integral() << endl;
  //cout << " entries in ea histogram : " << meaHisto->Integral() << endl;
}
//------------------------------
StHbtString HiRAPairCutMonitor::Report(){
  string Stemp;
  char Ctemp[100];
  sprintf(Ctemp," HiRAPairCutMonitor");
  Stemp=Ctemp;
  StHbtString returnThis = Stemp;
  return returnThis;
}

