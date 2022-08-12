#ifndef sandbox_h
#define sandbox_h

#include "AnalyzerCore.h"

class sandbox : public AnalyzerCore {

public:

    void initializeAnalyzer();
    void executeEventFromParameter(AnalyzerParameter param);
    void executeEvent();

    std::vector<Muon> allMuons;
    std::vector<Electron> allElectrons;
    std::vector<Jet> allJets;
    std::vector<FatJet> allFatJets;

    std::vector<TString> muonIsoTriggers, muonHighPtTriggers, electronTriggers;

    double GetParticleNetScore(FatJet fatjet, TString tagger);
    JetTagging::Tagger pNetXbbMD, pNetXqqMD, pNetXccMD, pNetQCDMD;

    JetTagging::Parameters bTaggingWP;

    sandbox();
    ~sandbox();

};



#endif

