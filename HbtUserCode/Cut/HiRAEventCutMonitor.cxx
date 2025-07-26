#include "Infrastructure/StHbtEvent.hh"
#include "Infrastructure/StHbtTypes.hh"
#include "Cut/HiRAEventCutMonitor.h"
#include "Infrastructure/StHbtTrack.hh"
#include "Infrastructure/StHbtTrackCollection.hh"
#include <cstdio>
#include "TMath.h"
#ifdef __ROOT__ 
ClassImp(HiRAEventCutMonitor)
#endif

HiRAEventCutMonitor::HiRAEventCutMonitor()
{

	mNHiRAMultHisto = new TH1D("NHiRAMultHisto",";Count;HiRA Multiplicity",30,0.,30.);
	mNHiRAMultHisto->Sumw2();
	mNHiRAMultHisto->SetDirectory(0);

	mBhatHisto = new TH1D("mBhatHisto",";Count;#hat{b}bhat",100,0.,1.);
	mBhatHisto->Sumw2();
	mBhatHisto->SetDirectory(0);

	mNuBallMultHisto = new TH1D("NuBallMultHisto",";Count;uBall Multiplicity",50,0.,50.);
	mNuBallMultHisto->Sumw2();
	mNuBallMultHisto->SetDirectory(0);

	mBhatVsuBallMultHisto = new TH2D("BhatVsuBall",";bhat;uBall Multiplicity",100.,0.,1.,30.,0.,30.);
	mBhatVsuBallMultHisto->Sumw2();
	mBhatVsuBallMultHisto->SetDirectory(0); 

	//skipped -9999
	muBallDS_TRGHisto = new TH1D("muBallDS_TRGHisto",";Count;uBallDS_TRG",100,-100,100);
	muBallDS_TRGHisto->Sumw2();
	muBallDS_TRGHisto->SetDirectory(0);
	muBallHira_TRGHisto = new TH1D("muBallHira_TRGHisto",";Count;uBallHira_TRG",100,-100,100);
	muBallHira_TRGHisto->Sumw2();
	muBallHira_TRGHisto->SetDirectory(0);
	muBallNW_TRGHisto = new TH1D("muBallNW_TRGHisto",";Count;uBallNW_TRG",100,-100,100);
	muBallNW_TRGHisto->Sumw2();
	muBallNW_TRGHisto->SetDirectory(0);
	



/* 	mNHiRAMultHisto_2p = new TH1D("NHiRAMultHisto_2p","p>2 Multiplicity",15,0.,15.);
	mNHiRAMultHisto_2p->Sumw2();
	mNHiRAMultHisto_2p->SetDirectory(0); 

	mNHiRAMultHisto_2He3 = new TH1D("NHiRAMultHisto_2He3","He3>2 Multiplicity",15,0.,15.);
	mNHiRAMultHisto_2He3->Sumw2();
	mNHiRAMultHisto_2He3->SetDirectory(0); 

	mNHiRAMultHisto_2He4 = new TH1D("NHiRAMultHisto_2He4","He4>2 HiRA Multiplicity",15,0.,15.);
	mNHiRAMultHisto_2He4->Sumw2();
	mNHiRAMultHisto_2He4->SetDirectory(0); 

	mNHiRAMultHisto_2d = new TH1D("NHiRAMultHisto_2d","d>2 HiRA Multiplicity",15,0.,15.);
	mNHiRAMultHisto_2d->Sumw2();
	mNHiRAMultHisto_2d->SetDirectory(0); 

	mNHiRAMultHisto_2t = new TH1D("NHiRAMultHisto_2t","t>2 Multiplicity",15,0.,15.);
	mNHiRAMultHisto_2t->Sumw2();
	mNHiRAMultHisto_2t->SetDirectory(0);  */

}
//------------------------------
HiRAEventCutMonitor::~HiRAEventCutMonitor()
{
	delete mNHiRAMultHisto;
/* 	delete mNHiRAMultHisto_2p;
	delete mNHiRAMultHisto_2He4;
	delete mNHiRAMultHisto_2He3;
	delete mNHiRAMultHisto_2d;
	delete mNHiRAMultHisto_2t; */

	delete mBhatHisto;
	delete mBhatVsuBallMultHisto;
	delete mNuBallMultHisto;

	delete muBallDS_TRGHisto;
	delete muBallHira_TRGHisto;
	delete muBallNW_TRGHisto;
  
  

  
}

//------------------------------
void HiRAEventCutMonitor::Fill(const StHbtEvent* event)
{

	StHbtTrack* track;                                                   

	int multiplicityHiRA = event->NumberOfTracks();
	mNHiRAMultHisto->Fill(multiplicityHiRA,1.);

	StHbtTrackIterator iter;
	//num of p
	int countp =0;
	int countHe4=0;
	int countHe3=0;
	int countd=0;
	int countt=0;
	for (iter=event->TrackCollection()->begin();iter!=event->TrackCollection()->end();iter++)
	{
		if ((*iter)->GetPid()==2){countp++;}

		if ((*iter)->GetPid()==3){countd++;}
		
		if ((*iter)->GetPid()==4){countt++;}

		if ((*iter)->GetPid()==5){countHe3++;}

		if ((*iter)->GetPid()==6){countHe4++;}
	}
	
/* 	if (countp>1){mNHiRAMultHisto_2p->Fill(countp);}
	if (countd>1){mNHiRAMultHisto_2d->Fill(countd);}
	if (countt>1){mNHiRAMultHisto_2t->Fill(countt);}
	if (countHe3>1){mNHiRAMultHisto_2He3->Fill(countHe3);}
	if (countHe4>1){mNHiRAMultHisto_2He4->Fill(countHe4);} */

	int multiplicityuBall = event->UncorrectedNumberOfPrimaries();
	mNuBallMultHisto->Fill(multiplicityuBall,1.);
	double bhat= event->GetBhat();
	mBhatHisto->Fill(bhat,1.);
	mBhatVsuBallMultHisto->Fill(bhat,multiplicityuBall);

	muBallDS_TRGHisto->Fill(event->GetuBallDS_TRG());
	muBallHira_TRGHisto->Fill(event->GetuBallHira_TRG());
	muBallNW_TRGHisto->Fill(event->GetuBallNW_TRG());
  
  
}

//------------------------------
void HiRAEventCutMonitor::Finish()
{
    cout<<"HiRAEventCutMonitor::Finish()"<<endl;
}

//------------------------------
StHbtString HiRAEventCutMonitor::Report()
{
  string Stemp;
  char Ctemp[100];
  sprintf(Ctemp," HiRAEventCutMonitor");
  Stemp=Ctemp;
  StHbtString returnThis = Stemp;
  return returnThis;
}

