std::map<int, double> massMap = {
	{2, 938.272},	// proton
	{3, 1875.610},	// deuteron
	{4, 2808.9182}, // triton
	{5, 2808.3870}, // 3He
	{6, 3727.374}	// alpha
};

std::map<int, double> kinergylowMap = {
	{2, 20.}, // proton
	{3, 15.}, // deuteron
	{4, 12.}, // triton
	{5, 20.}, // 3He
	{6, 18.}  // alpha
};

std::map<int, double> kinergyhighMap = {
	{2, 198.},	// proton
	{3, 131.5}, // deuteron
	{4, 104.},	// triton
	{5, 200.},	// 3He
	{6, 200.}	// alpha
};

void analHira(
	// clang-format off
    const int& nevents = 1000000000, // 1000000000
    const std::string& outputfile = "output.root",
    const int& PartID1 = 2, // 2 for proton
    const int& PartID2 = 6, // 6 for alpha
    const std::string& Systemtag = "Ca48Ni64E140",
    const std::string& Dir_data = "/data/HiRA_Cali/48Ca64Ni_140MeVu",
    const std::string& runinfo = "database/RunInfo.data",  
    const std::string& Dir_geoeff = "database/GeoEff",
    const std::string& Dir_angle = "database/PixelAngle_BeamPos_0_0_0.dat",
    const int MinSizePartCollection = 1, // minimum size of particle collection
    bool IsBadMapAnal = true, // whether to consider bad map analysis
    bool IsUsePosCali = true // whether to use position calibration
) {
	// clang-format on

	//*****************************Parameters***************************************
	// fixed gates

	const int uBall_Multi_Cut = 128; // event cut
	const double pMin = 0.;			 // track cut
	const double pMax = 10000.;		 // track cut
	const double pcmsmin = 0.;		 // pair cut
	const double pcmsmax = 10000.;	 // pair cut
	const double plabmin = 0.;		 // pair cut
	const double plabmax = 10000.;	 // pair cut
	const double qInvmin = 0.;		 // pair cut
	const double qInvmax = 20000.;	 // pair cut

	auto mass1 = massMap[PartID1];
	auto mass2 = massMap[PartID2];

	Int_t NumOfBin = 600; // number of bins in CF
	Int_t UpLimit = 600;  // upper limit of the range
	Int_t LowLimit = 0;	  // lower

	Int_t NumToMix = 10;	// number of event to mix
	Int_t NumOfRegion = 10; // number of region divided, mix events with similar bhat

	//*****************************Parameters ends***************************************

	auto Reader = new EOSReader(
		nevents, runinfo.c_str(), Dir_geoeff.c_str(), Dir_data.c_str(), Systemtag.c_str(), Dir_angle.c_str(),
		IsBadMapAnal, IsUsePosCali
	);
	Reader->SetDebug(0);
	TheManager = new StHbtManager();
	TheManager->SetEventReader(Reader);

	double bhat1, bhat2;
	double PCMS1, PCMS2;
	double rapidity1, rapidity2, rapidity3, rapidity4;
	double kt1, kt2;
	double pt1, pt2;

	const int rapmax = 8;
	const int cenmax = 4;
	const int pCMSmax = 4;
	const int pairkTmax = 15;

	//-- now set up an Analysis
	StHbtBhatAnalysis *anal[rapmax][cenmax][pCMSmax][pairkTmax];
	HiRAEventCut *evcut[rapmax][cenmax][pCMSmax][pairkTmax];
	HiRAEventCutMonitor *eventPass[rapmax][cenmax][pCMSmax][pairkTmax];
	HiRAEventCutMonitor *eventFail[rapmax][cenmax][pCMSmax][pairkTmax];

	HiRATrackCut *trkcut[rapmax][cenmax][pCMSmax][pairkTmax];
	HiRATrackCutMonitor *trackPass[rapmax][cenmax][pCMSmax][pairkTmax];
	HiRATrackCutMonitor *trackFail[rapmax][cenmax][pCMSmax][pairkTmax];

	HiRATrackCut *trkcut2[rapmax][cenmax][pCMSmax][pairkTmax];
	HiRATrackCutMonitor *trackPass2[rapmax][cenmax][pCMSmax][pairkTmax];
	HiRATrackCutMonitor *trackFail2[rapmax][cenmax][pCMSmax][pairkTmax];

	ManyPairCuts *paircuts[rapmax][cenmax][pCMSmax][pairkTmax];
	HiRAPairCut *prcut[rapmax][cenmax][pCMSmax][pairkTmax];
	HiRAPairCutMonitor *PairMoniPass[rapmax][cenmax][pCMSmax][pairkTmax];
	HiRAPairCutMonitor *PairMoniFail[rapmax][cenmax][pCMSmax][pairkTmax];

	//**************************************************************************************//

	CorrFctn *CF[rapmax][cenmax][pCMSmax][pairkTmax];

	TString analname = "HiRA_"; // analysis name prefix

	// i=rap, j=bhat, k=pair kt, l=pt
	for (int i = 0; i < 1; i++) {
		switch (i) {
		case 0:
			rapidity1 = -0.15;
			rapidity2 = 0.15;
			rapidity3 = -0.15;
			rapidity4 = 0.15;
			break;
		}

		for (int j = 0; j < 1; j++) {
			switch (j) {
			// case 0 : bhat1 = 0.0; bhat2=1.0; break;
			// case 0 : bhat1 = 0.0; bhat2=0.2; break;
			case 0:
				bhat1 = 0.0;
				bhat2 = 0.4;
				break;
			}

			for (int k = 0; k < 1; k++) {
				switch (k) {
				case 0:
					kt1 = 0;
					kt2 = 20000;
					break;
				}

				for (int l = 0; l < 1; l++) {
					switch (l) {
					case 0:
						pt1 = 0;
						pt2 = 20000;
						break;
					}

					anal[i][j][k][l] = new StHbtBhatAnalysis(NumOfRegion, bhat1, bhat2);
					anal[i][j][k][l]->SetMinSizePartCollection(MinSizePartCollection);
					evcut[i][j][k][l] = new HiRAEventCut();
					evcut[i][j][k][l]->SetEventMult(1, uBall_Multi_Cut);
					evcut[i][j][k][l]->SetVertZPos(-1000.0, 1000.0);
					evcut[i][j][k][l]->SetBhat(bhat1, bhat2);

					eventPass[i][j][k][l] = new HiRAEventCutMonitor();
					eventFail[i][j][k][l] = new HiRAEventCutMonitor();

					evcut[i][j][k][l]->AddCutMonitor(eventPass[i][j][k][l], eventFail[i][j][k][l]);

					anal[i][j][k][l]->SetEventCut(evcut[i][j][k][l]);

					trkcut[i][j][k][l] = new HiRATrackCut();
					trkcut[i][j][k][l]->SetPt(pt1, pt2);
					trkcut[i][j][k][l]->SetP(pMin, pMax);
					trkcut[i][j][k][l]->SetRapidity(rapidity1, rapidity2);
					trkcut[i][j][k][l]->SetRapidity2(rapidity3, rapidity4);
					trkcut[i][j][k][l]->SetThetaLAB(30, 75); // theta in LAB frame
					trkcut[i][j][k][l]->SetKineticEnergy(
						kinergylowMap[PartID1],
						kinergyhighMap[PartID1]
					); // kinetic energy range
					trkcut[i][j][k][l]->SetMass(mass1);
					trkcut[i][j][k][l]->SetPid(PartID1);
					trackPass[i][j][k][l] = new HiRATrackCutMonitor((analname + "trackPass").Data());
					trackFail[i][j][k][l] = new HiRATrackCutMonitor((analname + "trackFail").Data());
					trkcut[i][j][k][l]->AddCutMonitor(trackPass[i][j][k][l], trackFail[i][j][k][l]);

					if (PartID1 == PartID2) {
						trkcut2[i][j][k][l] = trkcut[i][j][k][l]; // if same particle, use the same cut

					} else {
						trkcut2[i][j][k][l] = new HiRATrackCut();
						trkcut2[i][j][k][l] = new HiRATrackCut();
						trkcut2[i][j][k][l]->SetPt(pt1, pt2);
						trkcut2[i][j][k][l]->SetP(pMin, pMax);
						trkcut2[i][j][k][l]->SetRapidity(rapidity1, rapidity2);
						trkcut2[i][j][k][l]->SetRapidity2(rapidity3, rapidity4);
						trkcut2[i][j][k][l]->SetThetaLAB(30, 75); // theta in LAB frame
						trkcut2[i][j][k][l]->SetKineticEnergy(
							kinergylowMap[PartID2],
							kinergyhighMap[PartID2]
						); // kinetic energy range
						trkcut2[i][j][k][l]->SetMass(mass2);
						trkcut2[i][j][k][l]->SetPid(PartID2);
						trackPass2[i][j][k][l] = new HiRATrackCutMonitor((analname + "trackPass2").Data());
						trackFail2[i][j][k][l] = new HiRATrackCutMonitor((analname + "trackFail2").Data());
						trkcut2[i][j][k][l]->AddCutMonitor(trackPass2[i][j][k][l], trackFail2[i][j][k][l]);
					}

					anal[i][j][k][l]->SetFirstParticleCut(trkcut[i][j][k][l]);
					anal[i][j][k][l]->SetSecondParticleCut(trkcut2[i][j][k][l]);

					paircuts[i][j][k][l] = new ManyPairCuts();

					prcut[i][j][k][l] = new HiRAPairCut();

					prcut[i][j][k][l]->SetPCMS(pcmsmin, pcmsmax);
					prcut[i][j][k][l]->SetPLab(plabmin, plabmax);
					prcut[i][j][k][l]->SetkT(kt1, kt2);
					prcut[i][j][k][l]->SetqInv(qInvmin, qInvmax);

					paircuts[i][j][k][l]->AddPairCut(prcut[i][j][k][l]);

					PairMoniPass[i][j][k][l] = new HiRAPairCutMonitor();
					PairMoniFail[i][j][k][l] = new HiRAPairCutMonitor();

					paircuts[i][j][k][l]->AddCutMonitor(PairMoniPass[i][j][k][l], PairMoniFail[i][j][k][l]);

					anal[i][j][k][l]->SetPairCut(paircuts[i][j][k][l]);

					CF[i][j][k][l] = new CorrFctn(analname.Data(), NumOfBin, LowLimit, UpLimit);

					anal[i][j][k][l]->AddCorrFctn(CF[i][j][k][l]);
					anal[i][j][k][l]->SetNumEventsToMix(NumToMix);
					TheManager->AddAnalysis(anal[i][j][k][l]);
				}
			}
		}
	}

	//---------------------------------------------------------------------

	if (TheManager->Init()) {
		std::cout << "Problem? - non-zero initialization value\n";
	}

	int ReaderStatus;
	int nEventsProcessed = 0;

	do {
		nEventsProcessed++;
		if (!(nEventsProcessed % 100000)) {
			std::cout << " +++++++++++++++++++++++++++ EVENT " << nEventsProcessed << " +++++++++++++++++++++++++++\n";
		}
		ReaderStatus = TheManager->ProcessEvent();
	} while ((!ReaderStatus) && (nEventsProcessed < nevents));

	TheManager->Finish();
	std::cout << nEventsProcessed << " processed\n";

	TheManager->Report();

	// --------------------- to save histograms ---------------------- //
	TFile histoOutput(outputfile.c_str(), "RECREATE");

	for (int i = 0; i < 1; i++) {
		switch (i) {
		case 0:
			rapidity1 = -0.15;
			rapidity2 = 0.15;
			rapidity3 = -0.15;
			rapidity4 = 0.15;
			break;
		}

		for (int j = 0; j < 1; j++) {
			switch (j) {
			case 0:
				bhat1 = 0.0;
				bhat2 = 0.4;
				break;
			}

			for (int k = 0; k < 1; k++) {
				switch (k) {
				case 0:
					kt1 = 0;
					kt2 = 20000;
					break;
				}

				for (int l = 0; l < 1; l++) {
					switch (l) {
					case 0:
						pt1 = 0;
						pt2 = 20000;
						break;
					}

					CF[i][j][k][l]->WriteOutHistos();

					eventPass[i][j][k][l]->NHiRAMultHisto()->Write((analname + "EventHiRAMultPass").Data());
					eventFail[i][j][k][l]->NHiRAMultHisto()->Write((analname + "EventHiRAMultFail").Data());

					eventPass[i][j][k][l]->NuBallMultHisto()->Write((analname + "EventuBallMultPass").Data());
					eventFail[i][j][k][l]->NuBallMultHisto()->Write((analname + "EventuBallMultFail").Data());

					eventPass[i][j][k][l]->BhatHisto()->Write((analname + "EventBhatPass").Data());
					eventFail[i][j][k][l]->BhatHisto()->Write((analname + "EventBhatFail").Data());

					eventPass[i][j][k][l]->BhatVsuBallMultHisto()->Write(
						(analname + "EventBhatVsuBallMultPass").Data()
					);
					eventFail[i][j][k][l]->BhatVsuBallMultHisto()->Write(
						(analname + "EventBhatVsuBallMultFail").Data()
					);

					eventPass[i][j][k][l]->uBallDS_TRGHisto()->Write((analname + "EventuBallDS_TRGPass").Data());
					eventFail[i][j][k][l]->uBallDS_TRGHisto()->Write((analname + "EventuBallDS_TRGFail").Data());

					eventPass[i][j][k][l]->uBallHira_TRGHisto()->Write((analname + "EventuBallHira_TRGPass").Data());
					eventFail[i][j][k][l]->uBallHira_TRGHisto()->Write((analname + "EventuBallHira_TRGFail").Data());

					eventPass[i][j][k][l]->uBallNW_TRGHisto()->Write((analname + "EventuBallNW_TRGPass").Data());
					eventFail[i][j][k][l]->uBallNW_TRGHisto()->Write((analname + "EventuBallNW_TRGFail").Data());

					trackPass[i][j][k][l]->WriteHistos();
					trackFail[i][j][k][l]->WriteHistos();

					if (PartID1 != PartID2) {
						trackPass2[i][j][k][l]->WriteHistos();
						trackFail2[i][j][k][l]->WriteHistos();
					}

					PairMoniPass[i][j][k][l]->KtHisto()->Write((analname + "kTPass").Data());
					PairMoniFail[i][j][k][l]->KtHisto()->Write((analname + "kTFail").Data());
					PairMoniPass[i][j][k][l]->PCMSHisto()->Write((analname + "PCMSPass").Data());
					PairMoniFail[i][j][k][l]->PCMSHisto()->Write((analname + "PCMSFail").Data());
					PairMoniPass[i][j][k][l]->PLabHisto()->Write((analname + "PLabPass").Data());
					PairMoniFail[i][j][k][l]->PLabHisto()->Write((analname + "PLabFail").Data());
				}
			}
		}
	}

	histoOutput.Write();
	histoOutput.Close();
}
