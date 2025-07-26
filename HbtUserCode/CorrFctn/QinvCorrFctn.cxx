/***************************************************************************
 *
 * $Id: QinvCorrFctn.cxx,v 1.4 2000/01/25 17:34:45 laue Exp $
 *
 * Author: Mike Lisa, Ohio State, lisa@mps.ohio-state.edu
 ***************************************************************************
 *
 * Description: part of STAR HBT Framework: StHbtMaker package
 *   a simple Q-invariant correlation function           
 *
 ***************************************************************************
 *
 * $Log: QinvCorrFctn.cxx,v $
 * Revision 1.4  2000/01/25 17:34:45  laue
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
 * Revision 1.3  1999/07/29 02:47:09  lisa
 * 1) add OpeningAngle correlation function 2) add StHbtMcEventReader 3) make histos in CorrFctns do errors correctly
 *
 * Revision 1.2  1999/07/06 22:33:20  lisa
 * Adjusted all to work in pro and new - dev itself is broken
 *
 * Revision 1.1.1.1  1999/06/29 16:02:57  lisa
 * Installation of StHbtMaker
 *
 **************************************************************************/

#include "CorrFctn/QinvCorrFctn.h"
//#include "Infrastructure/StHbtHisto.hh"
#include <cstdio>
#include "TMath.h"

#ifdef __ROOT__ 
ClassImp(QinvCorrFctn)
#endif

//____________________________
QinvCorrFctn::QinvCorrFctn(char* title, const int& nbins, const float& QinvLo, const float& QinvHi){
  // set up numerator
  //  title = "Num Qinv (MeV/c)";
  char TitNum[100] = "Num";
  strcat(TitNum,title);
  mNumerator = new TH1D(TitNum,title,nbins,QinvLo,QinvHi);
  // set up denominator
  //title = "Den Qinv (MeV/c)";
  char TitDen[100] = "Den";
  strcat(TitDen,title);
  mDenominator = new TH1D(TitDen,title,nbins,QinvLo,QinvHi);
  // set up ratio
  //title = "Ratio Qinv (MeV/c)";
  char TitRat[100] = "Rat";
  strcat(TitRat,title);
  mRatio = new TH1D(TitRat,title,nbins,QinvLo,QinvHi);
  // this next bit is unfortunately needed so that we can have many histos of same "title"
  // it is neccessary if we typedef TH1D to TH1d (which we do)
  //mNumerator->SetDirectory(0);
  //mDenominator->SetDirectory(0);
  //mRatio->SetDirectory(0);

  // to enable error bar calculation...
  mNumerator->Sumw2();
  mDenominator->Sumw2();
  mRatio->Sumw2();

}

//____________________________
QinvCorrFctn::~QinvCorrFctn(){
  delete mNumerator;
  delete mDenominator;
  delete mRatio;
}

//_________________________
void QinvCorrFctn::WriteOutHistos(){

  mNumerator->Write();
  mDenominator->Write();

}

//_________________________
void QinvCorrFctn::Finish(){
  // here is where we should normalize, fit, etc...
  // we should NOT Draw() the histos (as I had done it below),
  // since we want to insulate ourselves from root at this level
  // of the code.  Do it instead at root command line with browser.
  //  mNumerator->Draw();
  //mDenominator->Draw();
  //mRatio->Draw();
  mRatio->Divide(mNumerator,mDenominator,1.0,1.0);

}

//____________________________
StHbtString QinvCorrFctn::Report(){
  string stemp = "Qinv Correlation Function Report:\n";
  char ctemp[100];
  sprintf(ctemp,"Number of entries in numerator:\t%E\n",mNumerator->GetEntries());
  stemp += ctemp;
  sprintf(ctemp,"Number of entries in denominator:\t%E\n",mDenominator->GetEntries());
  stemp += ctemp;
  sprintf(ctemp,"Number of entries in ratio:\t%E\n",mRatio->GetEntries());
  stemp += ctemp;
  //  stemp += mCoulombWeight->Report();
  StHbtString returnThis = stemp;
  return returnThis;
}
//____________________________
void QinvCorrFctn::AddRealPair(const StHbtPair* pair){
  double Qinv = fabs(pair->qInv());   // note - qInv() will be negative for identical pairs...
  mNumerator->Fill(Qinv);

  //  cout << "QinvCorrFctn::AddRealPair : " << pair->qInv() << " " << Qinv <<endl;
  /*
    double qOut   = pair->qOutBf(0.);
  double qSide  = pair->qSideBf(0.);
  double qLong  = pair->qLongBf(0.);
  double qOut2  = qOut*qOut;
  double qSide2 = qSide*qSide;
  double qLong2 = qLong*qLong;
  double Qtot   = TMath::Sqrt(qOut2+qSide2+qLong2);
  
  cout<<"Qtot (Lab)  = "<<Qtot<<endl;
  
  qOut   = pair->qOutBf(-0.20113);
  qSide  = pair->qSideBf(-0.20113);
  qLong  = pair->qLongBf(-0.20113);
  qOut2  = qOut*qOut;
  qSide2 = qSide*qSide;
  qLong2 = qLong*qLong;
  Qtot   = TMath::Sqrt(qOut2+qSide2+qLong2);
  
  cout<<"Qtot (Lab0.20113)  = "<<Qtot<<endl;

  qOut   = pair->qOutCMS();
  qSide  = pair->qSideCMS();
  qLong  = pair->qLongCMS();
  qOut2  = qOut*qOut;
  qSide2 = qSide*qSide;
  qLong2 = qLong*qLong;
  Qtot   = TMath::Sqrt(qOut2+qSide2+qLong2);

  cout<<"Qtot (CMS)  = "<<Qtot<<endl;

  qOut   = pair->qOutPf();
  qSide  = pair->qSidePf();
  qLong  = pair->qLongPf();
  qOut2  = qOut*qOut;
  qSide2 = qSide*qSide;
  qLong2 = qLong*qLong;
  Qtot   = TMath::Sqrt(qOut2+qSide2+qLong2);

  cout<<"Qtot (PRF)  = "<<Qtot<<endl;

    double px1 = pair->track1()->FourMomentum().x();
  double py1 = pair->track1()->FourMomentum().y();
  double pz1 = pair->track1()->FourMomentum().z();
  double E1  = ::sqrt(px1*px1 + py1*py1 + pz1*pz1 + 938.272*938.272);

  double px2 = pair->track2()->FourMomentum().x();
  double py2 = pair->track2()->FourMomentum().y();
  double pz2 = pair->track2()->FourMomentum().z();
  double E2  = ::sqrt(px2*px2 + py2*py2 + pz2*pz2 + 938.272*938.272);

  cout<<"1st particle = ("<<px1<<","<<py1<<","<<pz1<<","<<E1<<")"<<endl;
  cout<<"2nd particle = ("<<px2<<","<<py2<<","<<pz2<<","<<E2<<")"<<endl;
  */
}
//____________________________
void QinvCorrFctn::AddMixedPair(const StHbtPair* pair){
  double weight = 1.0;
  double Qinv = fabs(pair->qInv());   // note - qInv() will be negative for identical pairs...
  mDenominator->Fill(Qinv,weight);
}


