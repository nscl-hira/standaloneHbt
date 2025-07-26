#ifndef CorrFctn_hh
#define CorrFctn_hh

#include "Base/StHbtCorrFctn.hh"
#include "Base/StHbtPairCut.h"

#include "TH1D.h"
#include "TH2D.h"

class CorrFctn : public StHbtCorrFctn {
public:
	CorrFctn(const std::string &title, const int &nbins, const float &QinvLo, const float &QinvHi);
	virtual ~CorrFctn();

	virtual StHbtString Report();
	virtual void AddRealPair(const StHbtPair *);
	virtual void AddMixedPair(const StHbtPair *);

	virtual void Finish();

	TH1D *Numerator();
	TH1D *Denominator();

	void WriteOutHistos();

	void SetSpecificPairCut(StHbtPairCut *);

private:
	TH1D *mNumerator;
	TH1D *mDenominator;

	StHbtPairCut *mPairCut;

#ifdef __ROOT__
	ClassDef(CorrFctn, 1)
#endif
};

inline TH1D *CorrFctn::Numerator() { return mNumerator; }
inline TH1D *CorrFctn::Denominator() { return mDenominator; }

inline void CorrFctn::SetSpecificPairCut(StHbtPairCut *paircut) { mPairCut = paircut; }

#endif
