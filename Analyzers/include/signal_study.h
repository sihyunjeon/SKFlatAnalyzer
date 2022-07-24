#ifndef signal_study_h
#define signal_study_h

#include "AnalyzerCore.h"

class signal_study : public AnalyzerCore {

public:

  void initializeAnalyzer();
  void executeEventFromParameter(AnalyzerParameter param);
  void executeEvent();

  std::vector<Muon> allMuons;
  std::vector<Electron> allElectrons;
  std::vector<Jet> allJets;
  std::vector<FatJet> allFatJets;

  signal_study();
  ~signal_study();

};



#endif

