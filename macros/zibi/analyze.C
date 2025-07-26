#include <iostream>


void analyze ( const Int_t nevents    = 1000000000,
	       const Char_t *outputfile="zbigoutput.root",
	       const Char_t *list = (char*)"40Ca.list",
	       const int rap = 0,
	       const int centrality = 0,
	       const int MinSizePartCollection = 2,
	       const double beta = 0.20113,
	       const double pMin = 0.,
	       const double pMax = 10000.,
	       const double pTmin = 0.,
	       const double pTmax = 10000.)
{
  // instantiate Reader and tell it where to get data
  //  HiRAReader* Reader = new HiRAReader("lists/","40Ca.list","root",1000000, 0.20113);
  HiRAReader* Reader = new HiRAReader("lists/",list,"root",1000000, 0.20113);

  Reader->SetDebug(0);
    
  // instantiate Manager and give it its Reader
  TheManager = new StHbtManager();
  TheManager->SetEventReader(Reader);
  
  double etmin, etmax;
  double PLABmin, PLABmax;
  double rapMin, rapMax;
  double thetaLABmin, thetaLABmax;
  
    const int rapMAX = 8;
    const int cenMAX = 4;
    const int pMAX = 4;
    const int thetaLABMAX = 4;
    //-- now set up an Analysis
    StHbtVertexMultAnalysis *anal[rapMAX][cenMAX][pMAX][thetaLABMAX];
    HiRAEventCut* evcut[rapMAX][cenMAX][pMAX][thetaLABMAX];
    //HiRAEventCutMonitor *eventPass[rapMAX][cenMAX][pMAX][thetaLABMAX];
    //HiRAEventCutMonitor *eventFail[rapMAX][cenMAX][pMAX][thetaLABMAX];
    HiRATrackCut* trkcut[rapMAX][cenMAX][pMAX][thetaLABMAX];
    //HiRATrackCutMonitor *trackPass[rapMAX][cenMAX][pMAX][thetaLABMAX];
    //HiRATrackCutMonitor *trackFail[rapMAX][cenMAX][pMAX][thetaLABMAX];
    ManyPairCuts *paircuts[rapMAX][cenMAX][pMAX][thetaLABMAX];
    HiRAPairCut* prcut[rapMAX][cenMAX][pMAX][thetaLABMAX];
    //HiRAPairCutMonitor *PairMoniPass[rapMAX][cenMAX][pMAX][thetaLABMAX];
    //HiRAPairCutMonitor *PairMoniFail[rapMAX][cenMAX][pMAX][thetaLABMAX];

    //MinvCorrFctn* MinvCF[rapMAX][cenMAX][pMAX][thetaLABMAX];
    QinvCorrFctn_MomCons* QinvCF[rapMAX][cenMAX][pMAX][thetaLABMAX];

    /* KstarCorrFctn_MomCons* KstarCF[rapMAX][cenMAX][pMAX][thetaLABMAX];

    BPLCMSFrame3DCorrFctn_MomCons *LCMSCF[rapMAX][cenMAX][pMAX][thetaLABMAX];
    PRFrame3DCorrFctn_MomCons *PRCF[rapMAX][cenMAX][pMAX][thetaLABMAX];
    LabFrame3DCorrFctn_MomCons *LabCF[rapMAX][cenMAX][pMAX][thetaLABMAX];

    QtotCosThetaPhi3DcorrFctn_MomCons* QtotLCMS_CF[rapMAX][cenMAX][pMAX][thetaLABMAX];
    LabFrameQtotCosThetaPhi3DcorrFctn_MomCons* QtotLab_CF[rapMAX][cenMAX][pMAX][thetaLABMAX];
    PRFrameQtotCosThetaPhi3DcorrFctn_MomCons* QtotPR_CF[rapMAX][cenMAX][pMAX][thetaLABMAX]; */

    TString analname;    
    char SrapMax[5];
    char SrapMin[5];
    char Setmin[5];
    char Setmax[5];
    char SPLABmin[5];
    char SPLABmax[5];
    char SThetaLABmin[5];
    char SThetaLABmax[5];

    for (int rap=0; rap <1; rap++)
      {
	switch (rap)
	  {
	  case 0 : rapMin = -0.05; rapMax = 0.05; break;
	  case 1 : rapMin = -1.; rapMax = 1.; break;
	  case 2 : rapMin = -0.05; rapMax = 0.00; break;
	  case 3 : rapMin =  0.00; rapMax = 0.05; break;
	  case 4 : rapMin =  0.05; rapMax = 0.10; break;
	  case 5 : rapMin =  0.10; rapMax = 0.15; break;
	  case 6 : rapMin =  0.15; rapMax = 0.20; break;
	  case 7 : rapMin =  0.20; rapMax = 0.25; break;
	  }
	for (int centrality=0; centrality<1; centrality++)
	  {
	    switch(centrality)
	      {
	      case 0 : etmin = 0.; etmax = 1000.; break;
	      case 1 : etmin = 150.; etmax = 1000.; break;
	      case 2 : etmin = 110.; etmax = 150.; break;
	      case 3 : etmin = 10.; etmax = 110.; break;
	      }
	    
	    for (int mom = 0; mom<1; mom++)
	      {
		switch (mom)
		  {
		  case 0 : PLABmin = 0; PLABmax = 1000; break;
		  case 1 : PLABmin = 500; PLABmax = 640; break;
		  //case 2 : PLABmin = 640; PLABmax = 740; break;
		  case 2 : PLABmin = 740; PLABmax = 900; break;
		  }

		for (int theta=0; theta<1; theta++)
		  {
		
		  switch(theta)
		    {
		    case 0 : thetaLABmin = 0; thetaLABmax = 90; break;
		    case 1 : thetaLABmin = 18; thetaLABmax = 26; break;
		    case 2 : thetaLABmin = 26; thetaLABmax = 33; break;
		    case 3 : thetaLABmin = 33; thetaLABmax = 58; break;
		    }
		  
		  /* sprintf(SrapMax,"%.2f",rapMax);
		  sprintf(SrapMin,"%.2f",rapMin);
		  sprintf(Setmin,"%.0f",etmin);
		  sprintf(Setmax,"%.0f",etmax);
		  sprintf(SPLABmin,"%.0f",PLABmin);
		  sprintf(SPLABmax,"%.0f",PLABmax);
		  sprintf(SThetaLABmin,"%.0f",thetaLABmin);
		  sprintf(SThetaLABmax,"%.0f",thetaLABmax);
		  analname = "rapMin";
		  analname += SrapMin;
		  analname += "_rapMax";
		  analname += SrapMax;
		  analname += "_Etmin";
		  analname += Setmin;
		  analname += "_Etmax";
		  analname += Setmax;
		  analname += "_PLABmin";
		  analname += SPLABmin;
		  analname += "_PLABmax";
		  analname += SPLABmax;
		  analname += "_ThetaLABmin";
		  analname += SThetaLABmin;
		  analname += "_ThetaLABmax";
		  analname += SThetaLABmax;
		  analname += ""; */
		  //		cout<<"xx = " <<analname<<endl;
		  
		  //-- now set up an Analysis
		  anal[rap][centrality][mom][theta] = new StHbtVertexMultAnalysis(1,-100.0,100.0,6,1,31);
		  anal[rap][centrality][mom][theta]->SetMinSizePartCollection(MinSizePartCollection);
		  // 1) The cuts...
		  //     a) EventCuts - instantiate+configure+plug
		  evcut[rap][centrality][mom][theta] = new HiRAEventCut;
		  evcut[rap][centrality][mom][theta]->SetEventMult(1,80000);  
		  evcut[rap][centrality][mom][theta]->SetVertZPos(-1000.0,1000.0);
		  evcut[rap][centrality][mom][theta]->SetEt(etmin,etmax);
		  

		 //eventPass[rap][centrality][mom][theta] = new HiRAEventCutMonitor();
		 //eventFail[rap][centrality][mom][theta] = new HiRAEventCutMonitor();
		  
		  //evcut[rap][centrality][mom][theta]->AddCutMonitor(eventPass[rap][centrality][mom][theta],eventFail[rap][centrality][mom][theta]);
		  
		  anal[rap][centrality][mom][theta]->SetEventCut(evcut[rap][centrality][mom][theta]);
		  
		  
		  //     b) Track/V0/Kink/Xi Cuts - instantiate+configure+plug
		  trkcut[rap][centrality][mom][theta] = new HiRATrackCut;
		  trkcut[rap][centrality][mom][theta]->SetPt(pTmin, pTmax);  
		  trkcut[rap][centrality][mom][theta]->SetP(pMin, pMax);  
		  trkcut[rap][centrality][mom][theta]->SetRapidity(rapMin, rapMax);
		  trkcut[rap][centrality][mom][theta]->SetMass(938.272);
		  trkcut[rap][centrality][mom][theta]->SetPid(2212);
		  
		  //trackPass[rap][centrality][mom][theta] = new HiRATrackCutMonitor((analname+"trackPass").Data());
		  //trackFail[rap][centrality][mom][theta] = new HiRATrackCutMonitor((analname+"trackFail").Data());
		  //trkcut[rap][centrality][mom][theta]->AddCutMonitor(trackPass[rap][centrality][mom][theta],trackFail[rap][centrality][mom][theta]);
		  
		  anal[rap][centrality][mom][theta]->SetFirstParticleCut(trkcut[rap][centrality][mom][theta]);
		  anal[rap][centrality][mom][theta]->SetSecondParticleCut(trkcut[rap][centrality][mom][theta]);
		  //     c) PairCuts - instantiate+configure+plug
		  
		  paircuts[rap][centrality][mom][theta] = new ManyPairCuts;
		  prcut[rap][centrality][mom][theta] = new HiRAPairCut;
		  prcut[rap][centrality][mom][theta]->SetPCMS(0.0,100000.0);
		  prcut[rap][centrality][mom][theta]->SetPLab(PLABmin, PLABmax);
		  paircuts[rap][centrality][mom][theta]->AddPairCut(prcut[rap][centrality][mom][theta]);
		  
		  //PairMoniPass[rap][centrality][mom][theta] = new HiRAPairCutMonitor;
		  //PairMoniFail[rap][centrality][mom][theta] = new HiRAPairCutMonitor;
		  
		  //paircuts[rap][centrality][mom][theta]->AddCutMonitor(PairMoniPass[rap][centrality][mom][theta],//PairMoniFail[rap][centrality][mom][theta]);
		  
		  anal[rap][centrality][mom][theta]->SetPairCut(paircuts[rap][centrality][mom][theta]);
		  
		  QinvCF[rap][centrality][mom][theta] = new QinvCorrFctn_MomCons((char*)("Qinv"),35,0.0,140);
		  anal[rap][centrality][mom][theta]->AddCorrFctn(QinvCF[rap][centrality][mom][theta]);  
		  
		  
		  // 3) Final detail and then give the Analysis to the Manager
		  anal[rap][centrality][mom][theta]->SetNumEventsToMix(40);
		  TheManager->AddAnalysis(anal[rap][centrality][mom][theta]);
		  }
	      }
	  }
      }

    //---------------------------------------------------------------------


    // ----------------- process the events
    if (TheManager->Init()) std::cout << "Problem? - non-zero initialization value\n";

    //    TheManager->PrintInfo();

    int ReaderStatus;
    int nEventsProcessed = 0;
    do {
      nEventsProcessed++;
      if (!(nEventsProcessed % 100000))
	//     if (!(nEventsProcessed % 1))
	{
	  std::cout << " +++++++++++++++++++++++++++ EVENT " << nEventsProcessed
	     << " +++++++++++++++++++++++++++\n";
	}
      ReaderStatus = TheManager->ProcessEvent();
    } while ((!ReaderStatus)&&(nEventsProcessed<nevents));
    TheManager->Finish();
    std::cout << nEventsProcessed << " processed\n";

   TheManager->Report();  
    
   /*
   cout<<"a"<<endl;
   evcut->Report();
   paircuts->Report();
   prcut->Report();
   anal->Report();
   */
  // --------------------- to save histograms ---------------------- //

    TFile histoOutput (outputfile,"RECREATE");
     
    for (int rap=0; rap <1; rap++)
      {
	switch (rap)
	  {
	  case 0 : rapMin = -0.05; rapMax = 0.05; break;
	  case 1 : rapMin = -1.; rapMax = 1.; break;
	  case 2 : rapMin = -0.05; rapMax = 0.00; break;
	  case 3 : rapMin =  0.00; rapMax = 0.05; break;
	  case 4 : rapMin =  0.05; rapMax = 0.10; break;
	  case 5 : rapMin =  0.10; rapMax = 0.15; break;
	  case 6 : rapMin =  0.15; rapMax = 0.20; break;
	  case 7 : rapMin =  0.20; rapMax = 0.25; break;
	  }
	for (int centrality=0; centrality<1; centrality++)
	  {
	    switch(centrality)
	      {
	      case 0 : etmin = 0.; etmax = 1000.; break;
	      case 1 : etmin = 150.; etmax = 1000.; break;
	      case 2 : etmin = 110.; etmax = 150.; break;
	      case 3 : etmin = 10.; etmax = 110.; break;
	      }
	    
	    for (int mom = 0; mom<1; mom++)
	      {
		switch (mom)
		  {
		  case 0 : PLABmin = 0; PLABmax = 1000; break;
		  case 1 : PLABmin = 500; PLABmax = 640; break;
		  //case 2 : PLABmin = 640; PLABmax = 740; break;
		  case 2 : PLABmin = 740; PLABmax = 900; break;
		  }

		for (int theta=0; theta<1; theta++)
		  {
		
		  switch(theta)
		    {
		    case 0 : thetaLABmin = 0; thetaLABmax = 90; break;
		    case 1 : thetaLABmin = 18; thetaLABmax = 26; break;
		    case 2 : thetaLABmin = 26; thetaLABmax = 33; break;
		    case 3 : thetaLABmin = 33; thetaLABmax = 58; break;
		    }
		  
		 /*  sprintf(SrapMax,"%.2f",rapMax);
		  sprintf(SrapMin,"%.2f",rapMin);
		  sprintf(Setmin,"%.0f",etmin);
		  sprintf(Setmax,"%.0f",etmax);
		  sprintf(SPLABmin,"%.0f",PLABmin);
		  sprintf(SPLABmax,"%.0f",PLABmax);
		  sprintf(SThetaLABmin,"%.0f",thetaLABmin);
		  sprintf(SThetaLABmax,"%.0f",thetaLABmax);
		  analname = "rapMin";
		  analname += SrapMin;
		  analname += "_rapMax";
		  analname += SrapMax;
		  analname += "_Etmin";
		  analname += Setmin;
		  analname += "_Etmax";
		  analname += Setmax;
		  analname += "_PLABmin";
		  analname += SPLABmin;
		  analname += "_PLABmax";
		  analname += SPLABmax;
		  analname += "_ThetaLABmin";
		  analname += SThetaLABmin;
		  analname += "_ThetaLABmax";
		  analname += SThetaLABmax; */
 	

		  QinvCF[rap][centrality][mom][theta]->WriteOutHistos();

		  /* eventPass[rap][centrality][mom][theta]->NHiRAMultHisto()->Write("EventHiRAMultPass");
		  eventFail[rap][centrality][mom][theta]->NHiRAMultHisto()->Write("EventHiRAMultFail");
		  eventPass[rap][centrality][mom][theta]->N4PiMultHisto()->Write("Event4PiMultPass");
		  eventFail[rap][centrality][mom][theta]->N4PiMultHisto()->Write("Event4PiMultFail");
		  eventPass[rap][centrality][mom][theta]->EtransHisto()->Write("EventEtransPass");
		  eventFail[rap][centrality][mom][theta]->EtransHisto()->Write("EventEtransFail");
		  eventPass[rap][centrality][mom][theta]->EtransVs4PiMultHisto()->Write("EventEtransVs4PiMultPass");
		  eventFail[rap][centrality][mom][theta]->EtransVs4PiMultHisto()->Write("EventEtransVs4PiMultFail");
		  
		  trackPass[rap][centrality][mom][theta]->WriteHistos();
		  trackFail[rap][centrality][mom][theta]->WriteHistos();
		  
		  PairMoniPass[rap][centrality][mom][theta]->KtHisto()->Write((analname+"kTPass").Data());
		  PairMoniFail[rap][centrality][mom][theta]->KtHisto()->Write((analname+"kTFail").Data());
		  PairMoniPass[rap][centrality][mom][theta]->PCMSHisto()->Write((analname+"PCMSsumPass").Data());
		  PairMoniPass[rap][centrality][mom][theta]->PLabHisto()->Write((analname+"PLABsumPass").Data());
		  PairMoniFail[rap][centrality][mom][theta]->PCMSHisto()->Write((analname+"PCMSsumFail").Data());
		  PairMoniFail[rap][centrality][mom][theta]->PLabHisto()->Write((analname+"PLABsumFail").Data()); */

		  /*
		    MinvCF[rap][centrality][mom][theta]->WriteOutHistos();
		  KstarCF[rap][centrality][mom][theta]->WriteOutHistos();

		  LCMSCF[rap][centrality][mom][theta]->WriteOutHistos(); 
		  PRCF[rap][centrality][mom][theta]->WriteOutHistos(); 
		  LabCF[rap][centrality][mom][theta]->WriteOutHistos(); 
		  QtotLCMS_CF[rap][centrality][mom][theta]->WriteOutHistos();
		  QtotLab_CF[rap][centrality][mom][theta]->WriteOutHistos();
		  QtotPR_CF[rap][centrality][mom][theta]->WriteOutHistos();
		  
		  
		  */
		  }
	      }
	  }
      }
    histoOutput.Write();
    histoOutput.Close(); 
   

}

