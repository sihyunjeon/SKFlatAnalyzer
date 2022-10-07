#ifndef SkimTree_boohft_calib_h
#define SkimTree_boohft_calib_h

#include "AnalyzerCore.h"

class SkimTree_boohft_calib : public AnalyzerCore {

public:

  void initializeAnalyzer();
  void executeEventFromParameter(AnalyzerParameter param);
  void executeEvent();

  SkimTree_boohft_calib();
  ~SkimTree_boohft_calib();

  TTree *newtree;

  vector<TString> triggers;
  void WriteHist();

};

#endif

