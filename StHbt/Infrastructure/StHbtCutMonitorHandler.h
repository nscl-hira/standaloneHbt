#ifndef StHbtCutMonitorHandler_hh
#define StHbtCutMonitorHandler_hh

#include "Infrastructure/StHbtTypes.hh"
#include "Infrastructure/StHbtEvent.hh"
#include "Infrastructure/StHbtTrack.hh"
#include "Infrastructure/StHbtV0.hh"
#include "Infrastructure/StHbtKink.hh"
#include "Infrastructure/StHbtPair.hh"               //Gael 12/04/02
#include "Infrastructure/StHbtParticleCollection.hh" // Gael 19/06/02
#include "Infrastructure/StHbtCutMonitorCollection.hh"
#include "Base/StHbtCutMonitor.hh"

class StHbtCutMonitorHandler
{

public:
    StHbtCutMonitorHandler();
    virtual ~StHbtCutMonitorHandler();

    StHbtCutMonitorCollection *PassMonitorColl();
    StHbtCutMonitorCollection *FailMonitorColl();
    StHbtCutMonitor *PassMonitor(int n);
    StHbtCutMonitor *FailMonitor(int n);
    void AddCutMonitor(StHbtCutMonitor *cutMoni1, StHbtCutMonitor *cutMoni2);
    void AddCutMonitor(StHbtCutMonitor *cutMoni);
    void AddCutMonitorPass(StHbtCutMonitor *cutMoni);
    void AddCutMonitorFail(StHbtCutMonitor *cutMoni);
    void FillCutMonitor(const StHbtEvent *event, bool pass);
    void FillCutMonitor(const StHbtTrack *track, bool pass);
    void FillCutMonitor(const StHbtV0 *v0, bool pass);
    void FillCutMonitor(const StHbtKink *kink, bool pass);
    void FillCutMonitor(const StHbtPair *pair, bool pass);                                 // Gael 11/04/02
    void FillCutMonitor(const StHbtParticleCollection *partColl);                          // Gael 19/06/02
    void FillCutMonitor(const StHbtEvent *event, const StHbtParticleCollection *partColl); // Gael 19/06/02
    void Finish();

private:
    bool mCollectionsEmpty;
    StHbtCutMonitorCollection *mPassColl;
    StHbtCutMonitorCollection *mFailColl;
#ifdef __ROOT__
    ClassDef(StHbtCutMonitorHandler, 0)
#endif
};

inline StHbtCutMonitorCollection *StHbtCutMonitorHandler::PassMonitorColl() { return mPassColl; }
inline StHbtCutMonitorCollection *StHbtCutMonitorHandler::FailMonitorColl() { return mFailColl; }

#endif
