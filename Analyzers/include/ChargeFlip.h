#ifndef ChargeFlip_h
#define ChargeFlip_h

#include "AnalyzerCore.h"

class ChargeFlip : public AnalyzerCore {

public:

  void initializeAnalyzer();

  void executeEvent(Long64_t Nentry);
  void executeEventFromParameter(AnalyzerParameter param, Long64_t Nentry);
  
  //double GetCFweight(std::vector<Electron> eles, TString id);
  //double GetCFweight_SF(std::vector<Electron> eles, TString id);
  //double GetHalfSampleWeight(const Electron& electron, TString id);

  TString EleTriggerName;
  double lep0ptcut, lep1ptcut;

  vector<TString> EleIDs, EleIDSFKeys;
  vector<Electron> AllEles;
  vector<Muon> AllMuons;
  vector<Jet> AllJets; // Only for Half Sample Test

  int MllLeft;
  int MllRight;
  int MinPt;
  int NBin;

  ChargeFlip();
  ~ChargeFlip();

};



#endif

