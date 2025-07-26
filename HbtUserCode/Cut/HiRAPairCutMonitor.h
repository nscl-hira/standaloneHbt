/***************************************************************************
 *
 * $Id: HiRAEventCutMonitor.h,v 1.1 2002/04/09 15:14:34 HiRA Exp $
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
 * $Log: HiRAEventCutMonitor.h,v $
 * Revision 1.1  2002/04/09 15:14:34  HiRA
 * Event Cut Monitor for HiRAStarStandardEventCut
 *
 *
 **************************************************************************/


#ifndef HiRAPairCutMonitor_hh
#define HiRAPairCutMonitor_hh

#include "Infrastructure/StHbtTypes.hh"
#include "Infrastructure/StHbtPair.hh"
#include "Base/StHbtCutMonitor.hh"

#include "TH1D.h"
#include "TH2D.h"
class HiRAPairCutMonitor : public StHbtCutMonitor{

private:

  TH1D* mKtHisto; 
  TH1D* mPCMSHisto; 
  TH1D* mPLabHisto; 
  //TH1D* meaHisto; 
  
  //TH2D* mRapVsqInv1;
  //TH2D* mRapVsqInv2;
  //TH2D* mThetaLabVsqInv1;
  //TH2D* mThetaLabVsqInv2;
  
  //TH2D* mkTVsqInv;
  //TH2D* mPCMSVsqInv;
  
  
  
  //TH2D* mTelescopeVsqInv1;
  //TH2D* mTelescopeVsqInv2;
  //TH2D* mCsIVsqInv1;
  //TH2D* mCsIVsqInv2;
  //TH2D* mEBVsqInv1;
  //TH2D* mEBVsqInv2;
  //TH2D* mEFVsqInv1;
  //TH2D* mEFVsqInv2;
  
  
  
public:
  HiRAPairCutMonitor();
  virtual ~HiRAPairCutMonitor();

  virtual StHbtString Report(); 
  virtual void Fill(const StHbtPair* pair);
  virtual void Finish();

  void Fill(const StHbtParticleCollection* d) {;}
  void Fill(const StHbtEvent *d1, const StHbtParticleCollection* d2) {;}
  void Fill(const StHbtEvent *d) {;}
  void Fill(const StHbtKink* d) {;}
  void Fill(const StHbtV0* d) {;}
  void Fill(const StHbtTrack* d) {;}
    
  TH1D* KtHisto() {return mKtHisto;}
  TH1D* PCMSHisto() {return mPCMSHisto;}
  TH1D* PLabHisto() {return mPLabHisto;}
  //TH1D* eaHisto() {return meaHisto;}
  
  //TH2D* RapVsqInv1(){return mRapVsqInv1;}
  //TH2D* RapVsqInv2(){return mRapVsqInv2;}
  //TH2D* ThetaLabVsqInv1(){return mThetaLabVsqInv1;}
  //TH2D* ThetaLabVsqInv2(){return mThetaLabVsqInv2;}
  //TH2D* kTVsqInv(){return mkTVsqInv;}
  //TH2D* PCMSVsqInv(){return mPCMSVsqInv;
  //TH2D* TelescopeVsqInv1(){return mTelescopeVsqInv1;}
  //TH2D* TelescopeVsqInv2(){return mTelescopeVsqInv2;}
  //TH2D* CsIVsqInv1(){return mCsIVsqInv1;}
  //TH2D* CsIVsqInv2(){return mCsIVsqInv2;}
  //TH2D* EBVsqInv1(){return mEBVsqInv1;}
  //TH2D* EBVsqInv2(){return mEBVsqInv2;}
  //TH2D* EFVsqInv1(){return mEFVsqInv1;}
  //TH2D* EFVsqInv2(){return mEFVsqInv2;}
  
  
#ifdef __ROOT__ 
 ClassDef(HiRAPairCutMonitor, 1)
#endif
};

#endif
