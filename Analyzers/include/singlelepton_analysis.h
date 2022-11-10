#ifndef singlelepton_analysis_h
#define singlelepton_analysis_h

#include "AnalyzerCore.h"

class singlelepton_analysis : public AnalyzerCore {

public:

    void initializeAnalyzer();

    void executeEventFromParameter(AnalyzerParameter param);
    void executeEvent();

    std::vector<TString> muonTightIDs, muonLooseIDs;
    std::vector<TString> electronTightIDs, electronLooseIDs;
    std::vector<TString> jetIDs, fatjetIDs;

    std::vector<TString> muonTriggers, electronTriggers;

    double muonPtCut, electronPtCut, jetPtCut, fatjetPtCut, leptonPtCut;

    std::vector<Muon> centralAllMuons;
    std::vector<Electron> centralAllElectrons;
    std::vector<Jet> centralAllJets;
    std::vector<FatJet> centralAllFatJets;

    singlelepton_analysis();
    ~singlelepton_analysis();

};

#endif
