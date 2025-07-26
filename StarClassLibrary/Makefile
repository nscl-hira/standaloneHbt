CXX           = gcc
ObjSuf        = o
SrcSuf        = cxx
ExeSuf        = exe
DllSuf        = so
IncSuf        = h
StandaloneHbtPath= $(shell pwd)/..
$(info StandaloneHbtPath=$(StandaloneHbtPath))

VPATH = ./src ./inc

CXXFLAGS = -O -g -Wall

INCLUDES = -I. -I./inc -I$(StandaloneHbtPath) -I$(StandaloneHbtPath)/StarClassLibrary/inc -I$(StandaloneHbtPath)/StarClassLibrary -I$(ROOTSYS)/include 

LD	 = g++

ROOTCFLAGS   := $(shell root-config --cflags)
ROOTLIBS     := $(shell root-config --libs)
ROOTGLIBS    := $(shell root-config --glibs)
ROOTGLIBS    += -lNew -lGui -lThread

CXXFLAGS     += $(ROOTCFLAGS)
LIBS          = $(ROOTLIBS) $(SYSLIBS)
GLIBS         = $(ROOTGLIBS) $(SYSLIBS) -lrt

DEFINES =  

CXXFLAGS += $(DEFINES) $(INCLUDES) -fPIC -pipe -Wall -g -Os 
#LDFLAGS  =  -shared -flat_namespace -fPIC
LDFLAGS  =  -shared -fPIC
##############LDFLAGS  =  -arch ppc -bundle  -flat_namespace




OBJS = StAntiNeutrinoMu.o StDMesonZero.o StLorentzVector.o StPositron.o \
DRand48Engine.o StAntiNeutrinoTau.o StDeuteron.o StMath.o StProton.o\
JamesRandom.o StAntiNeutron.o StDsMesonMinus.o StMatrix.o StRandom.o\
RandBreitWigner.o StAntiOmegaMinus.o StDsMesonPlus.o StMemoryInfo.o StRhoMinus.o\
RandEngine.o StAntiOmegacZero.o StElectron.o StMemoryPool.o StRhoPlus.o\
RandExponential.o StAntiProton.o StEta.o StMuonMinus.o StRhoZero.o\
RandFlat.o StAntiSigmaMinus.o StEtaPrime.o StMuonPlus.o StSigmaMinus.o\
RandGauss.o StAntiSigmaPlus.o StFastCircleFitter.o StNeutrinoE.o StSigmaPlus.o\
RandPoisson.o StAntiSigmaZero.o StGamma.o StNeutrinoMu.o StSigmaZero.o\
Random.o StAntiSigmacPlus.o StHe3.o StNeutrinoTau.o StSigmacPlus.o\
RandomEngine.o StAntiSigmacPlusPlus.o StHelix.o StNeutron.o StSigmacPlusPlus.o\
RanecuEngine.o StAntiSigmacZero.o StJPsi.o StOmegaMeson.o StSigmacZero.o\
RanluxEngine.o StAntiXiMinus.o StKaonMinus.o StOmegaMinus.o StTauMinus.o\
StAlpha.o StAntiXiZero.o StKaonPlus.o StOmegacZero.o StTauPlus.o\
StAntiBMesonZero.o StAntiXicPlus.o StKaonStarMinus.o StOpticalPhoton.o StThreeVector.o \
StAntiBsMesonZero.o StAntiXicZero.o StKaonStarPlus.o StParticleDefinition.o StTimer.o\
StAntiDMesonZero.o StBMesonMinus.o StKaonStarZero.o StParticleTable.o StTriton.o\
StAntiKaonStarZero.o StBMesonPlus.o StKaonZero.o StPhi.o StXiMinus.o\
StAntiKaonZero.o StBMesonZero.o StKaonZeroLong.o StPhysicalHelix.o StXiZero.o\
StAntiLambda.o StBsMesonZero.o StKaonZeroShort.o StPionMinus.o StXicPlus.o\
StAntiLambdacPlus.o StDMesonMinus.o StLambda.o StPionPlus.o StXicZero.o\
StAntiNeutrinoE.o StDMesonPlus.o StLambdacPlus.o StPionZero.o probChiSquared.o\
StarClassLibrary_Cint.o

CINTHEADERS = StHelixD.hh StPhysicalHelixD.hh StThreeVectorD.hh StThreeVectorF.hh StLorentzVectorD.hh StLorentzVectorF.hh StMatrixD.hh StMatrixF.hh StarClassLibraryLinkDef.hh


# $@ - full name of a current target
# $? - list of files for current dependency which are out of date
# $< - the source file of the current single dependency


%.o:%.cxx 
	$(CXX) $(INCLUDES) $(CXXFLAGS) -c $<

default: StarClassLibrary.so

StarClassLibrary_Cint.cxx: $(CINTHEADERS)
	rootcint -f StarClassLibrary_Cint.cxx -c $(DEFINES) $(INCLUDES) $(CINTHEADERS)  

objects: $(OBJS) 

StarClassLibrary.so: $(OBJS)
	$(LD) $(OBJS) $(LIBS) $(LDFLAGS) -o $@

clean:
	rm -f $(OBJS) StarClassLibrary.so StarClassLibrary_Cint.cxx StarClassLibrary_Cint.h

