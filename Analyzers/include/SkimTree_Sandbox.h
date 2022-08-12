#ifndef SkimTree_Sandbox_h
#define SkimTree_Sandbox_h

#include "AnalyzerCore.h"

class SkimTree_Sandbox : public AnalyzerCore {

public:

  void initializeAnalyzer();
  void executeEventFromParameter(AnalyzerParameter param);
  void executeEvent();

  SkimTree_Sandbox();
  ~SkimTree_Sandbox();

  TTree *newtree;

  vector<TString> triggers;
  void WriteHist();

  double LeptonPtCut, AK4JetPtCut, AK8JetPtCut;

};

#endif

