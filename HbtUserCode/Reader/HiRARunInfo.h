#ifndef HiRARunInfo_h
#define HiRARunInfo_h 1

#include "TCanvas.h"
#include "TCutG.h"
#include "TF1.h"
#include "TFile.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TLorentzVector.h"
#include "TMath.h"
#include "TObject.h"
#include "TTree.h"
#include "TVector3.h"
#include "fstream"
#include "iostream"
#include "string.h"

using namespace std;
using namespace TMath;

class HiRA_RunInfo : public TObject {
public:
	HiRA_RunInfo();
	~HiRA_RunInfo();

	int SystemNum;
	// string SystemTag_All[20];

	string SystemTag_All[20];
	double BetaZ_LabToCM[20];
	double Rapidity_Beam_Lab[20];
	TVector3 BetaVector_LabToCM[20];

	void Initial_LabToCM();
	double Cal_BetaZ_LabToCM(double BeamMassTem, double TargetMassTem, double BeamEnergyTem);
	double Cal_BeamRapidity_Lab(double BeamMassTem, double BeamEnergyTem);

	// the below function is used at the outside.
	int GetSystemIndex(string SystemName);
	double Get_BeamRapidity_Lab(string SystemName) { return Rapidity_Beam_Lab[GetSystemIndex(SystemName)]; }
	double Get_BetaZ_LabToCM(string SystemName) { return BetaZ_LabToCM[GetSystemIndex(SystemName)]; }
	TVector3 Get_BetaVector_LabToCM(string SystemName) { return BetaVector_LabToCM[GetSystemIndex(SystemName)]; }

	// the below is for storing the run Index, bad map version
	int RunNum[20];
	int RunNO[20][200];
	string Run_TriggerCondition[20][200];
	string BadMapVersion[20][200];
	int ShadowBar[20][200]; // now, 0: no shadow bar; 1: with shadow bar in.

	void Read_RunInfo(const string FileWithPath);
	void AddRunInfo(string SystemTagTem, int StartRun, int EndRun, string BadMap, int ShadowBarTag, string Trigger);
	void PrintRunInfo(string SystemName); // single system information
	void PrintRunInfo();				  // all the system information

	int Get_RunNum(string SystemNameTem);
	int Get_RunNO(string SystemNameTem, int Index);
	string Get_BadMapVersion(string SystemNameTem, int Index);
	string Get_Trigger(string SystemNameTem, int Index);

	ClassDef(HiRA_RunInfo, 1)
};

#endif
