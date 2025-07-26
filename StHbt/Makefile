CXX           = gcc
ObjSuf        = o
SrcSuf        = cxx
ExeSuf        = exe
DllSuf        = so
IncSuf        = h
StandaloneHbtPath= $(shell pwd)/..
$(info StandaloneHbtPath=$(StandaloneHbtPath))

VPATH = ./Infrastructure ./Base

CXXFLAGS = -O -g -Wall


INCLUDES = -I. -I./Base -I./Infrastructure  -I$(StandaloneHbtPath) -I$(StandaloneHbtPath)/StHbt/Infrastructure  -I$(StandaloneHbtPath)/StHbt/Base  -I$(StandaloneHbtPath)/StHbt/ -I../StarClassLibrary/inc -I$(StandaloneHbtPath)/StarClassLibrary/inc -I$(ROOTSYS)/include -I..


LD	 = g++

ROOTCFLAGS   := $(shell root-config --cflags)
ROOTLIBS     := $(shell root-config --libs)
ROOTGLIBS    := $(shell root-config --glibs)
ROOTGLIBS    += -lNew -lGui -lThread

CXXFLAGS     += $(ROOTCFLAGS)
LIBS          = $(ROOTLIBS) $(SYSLIBS)
GLIBS         = $(ROOTGLIBS) $(SYSLIBS) -lrt

DEFINES = -D__NO_STAR_DEPENDENCE_ALLOWED__

CXXFLAGS += $(DEFINES) $(INCLUDES) -fPIC -pipe -Wall -g -Os 
#LDFLAGS  =  -O -Wl -shared -flat_namespace
LDFLAGS  =  -O  -shared 

###LDFLAGS  =  -arch ppc -bundle -mmacosx-version-min=10.3  -undefined dynamic_lookup -flat_namespace


### Note: I leave out StHbtCoulomb since (1) it needs some further edits and (2) it's not necc right now

OBJS = \
StHbtAnalysis.o \
StHbtBhatAnalysis.o \
StHbtCutMonitorHandler.o \
StHbtEvent.o \
StHbtKink.o \
StHbtLikeSignAnalysis.o \
StHbtManager.o \
StHbtPair.o \
StHbtParticle.o \
StHbtPicoEvent.o \
StHbtPicoEventCollectionVectorHideAway.o \
StHbtTrack.o \
StHbtV0.o \
StHbtVertexAnalysis.o \
StHbtVertexMultAnalysis.o \
StHbtXi.o \
TpcLocalTransform.o \
StHbtEventReader.o \
StHbt_Cint.o

CINTHEADERS = \
StHbtBaseAnalysis.h \
StHbtEventCut.h \
StHbtEventReader.hh \
StHbtKinkCut.h \
StHbtPairCut.h \
StHbtParticleCut.h \
StHbtTrackCut.h \
StHbtV0Cut.h \
StHbtXiCut.h \
StHbtAnalysis.h \
StHbtBhatAnalysis.h \
StHbtCutMonitorHandler.h \
StHbtLikeSignAnalysis.h \
StHbtManager.h \
StHbtVertexAnalysis.h \
StHbtVertexMultAnalysis.h \
StHbtLinkDef.hh



# $@ - full name of a current target
# $? - list of files for current dependency which are out of date
# $< - the source file of the current single dependency


%.o:%.cxx 
	$(CXX) $(INCLUDES) $(CXXFLAGS) -c $<


%.o:%.cc
	$(CXX) $(INCLUDES) $(CXXFLAGS) -c $<

default: StHbt.so

StHbt_Cint.cxx: $(CINTHEADERS)
	rootcint -f StHbt_Cint.cxx -c $(DEFINES) $(INCLUDES) $(CINTHEADERS)  

objects: $(OBJS) 

StHbt.so: $(OBJS)
	$(LD) $(OBJS) $(LIBS) $(LDFLAGS) -o $@

clean:
	rm -f $(OBJS) StHbt.so StHbt_Cint.cxx StHbt_Cint.h

