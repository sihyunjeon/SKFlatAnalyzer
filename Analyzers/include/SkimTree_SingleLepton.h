#ifndef SkimTree_SingleLepton_h
#define SkimTree_SingleLepton_h

#include "AnalyzerCore.h"

class SkimTree_SingleLepton : public AnalyzerCore {

public:

  void initializeAnalyzer();
  void executeEventFromParameter(AnalyzerParameter param);
  void executeEvent();

  SkimTree_SingleLepton();
  ~SkimTree_SingleLepton();

  TTree *newtree;

  vector<TString> triggers;
  void WriteHist();

};

#endif

