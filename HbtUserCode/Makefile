
CXX           = gcc
ObjSuf        = o
SrcSuf        = cxx
ExeSuf        = exe
DllSuf        = so
IncSuf        = h
StandaloneHbtPath= $(shell pwd)/..
$(info StandaloneHbtPath=$(StandaloneHbtPath))

VPATH = ./Reader ./CorrFctn ./Cut 

CXXFLAGS = -O -g -Wall


INCLUDES = -I.  -I$(ROOTSYS)/include -I$(StandaloneHbtPath) -I../StHbt -I../StHbt/Base -I../StHbt/Infrastructure -I../StarClassLibrary/inc -I$(ROOTSYS)/include -I.. \
           -I./CorrFctn -I./Reader -I./Cut -I$(StandaloneHbtPath)/HbtUserCode/Reader -I$(StandaloneHbtPath)/HbtUserCode/CorrFctn -I$(StandaloneHbtPath)/HbtUserCode/Cut -I$(StandaloneHbtPath)/HbtUserCode -I$(StandaloneHbtPath)/StHbt/Infrastructure  -I$(StandaloneHbtPath)/StHbt/Base -I$(StandaloneHbtPath)/StHbt -I$(StandaloneHbtPath)/StarClassLibrary/inc


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
#LDFLAGS  =  -shared -flat_namespace
LDFLAGS  =  -shared 



OBJS = \
EOSReader.o \
HiRABadmap.o \
HiRAPosCali.o \
HiRARunInfo.o \
HiRAEventCut.o \
HiRAEventCutMonitor.o \
HiRAPairCut.o \
HiRAPairCutMonitor.o \
HiRATrackCut.o \
HiRATrackCutMonitor.o \
kTPairCut.o \
ManyPairCuts.o \
CorrFctn.o \
HbtUserCode_Cint.o

CINTHEADERS = \
EOSReader.h \
HiRABadmap.h \
HiRAPosCali.h \
HiRARunInfo.h \
HiRAEventCut.h \
HiRAEventCutMonitor.h \
HiRAPairCut.h \
HiRAPairCutMonitor.h \
HiRATrackCut.h \
HiRATrackCutMonitor.h \
kTPairCut.h \
ManyPairCuts.h \
CorrFctn.h \
HbtUserCodeLinkDef.hh


# $@ - full name of a current target
# $? - list of files for current dependency which are out of date
# $< - the source file of the current single dependency


%.o:%.cxx 
	$(CXX) $(INCLUDES) $(CXXFLAGS) -c $<


%.o:%.cc
	$(CXX) $(INCLUDES) $(CXXFLAGS) -c $<

default: HbtUserCode.so

HbtUserCode_Cint.cxx: $(CINTHEADERS)
	rootcint -f HbtUserCode_Cint.cxx -c $(DEFINES) $(INCLUDES) $(CINTHEADERS)  

objects: $(OBJS) 

HbtUserCode.so: $(OBJS)
	$(LD) $(OBJS) $(LIBS) $(LDFLAGS) -o $@

clean:
	rm -f $(OBJS) HbtUserCode.so HbtUserCode_Cint.cxx HbtUserCode_Cint.h

