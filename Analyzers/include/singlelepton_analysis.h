#ifndef singlelepton_analysis_h
#define singlelepton_analysis_h

#include "AnalyzerCore.h"

class singlelepton_analysis : public AnalyzerCore {

public:

    void initializeAnalyzer();

    void executeEventFromParameter(AnalyzerParameter param);
    void executeEvent();

    bool RunSyst;
    bool RunNewPDF;
    bool RunXSecSyst;

    bool invertLeptonIsolation;
    bool runSystematics;

    std::vector<TString> muonTightIDs, muonLooseIDs;
    std::vector<TString> electronTightIDs, electronLooseIDs;
    std::vector<TString> jetIDs, fatjetIDs;

    JetTagging::Parameters bTaggingWP;
    double GetBTaggingScore(Jet jet);
    JetTagging::Tagger pNetXbbMD, pNetXqqMD, pNetXccMD, pNetQCDMD;
    double GetParticleNetScore(FatJet fatjet, TString tagger);

    std::vector<TString> muonTriggers, electronTriggers;

    double muonPtCut, electronPtCut, jetPtCut, fatjetPtCut, leptonPtCut;

    std::vector<Muon> allMuons;
    std::vector<Electron> allElectrons;
    std::vector<Jet> allJets;
    std::vector<FatJet> allFatJets;

    double GetReconstructedNeutrinoDet(Lepton lepton, Particle missingEt);
    Particle GetReconstructedNeutrino(Lepton lepton, Particle missingEt);

    int GetSignalRegion(TString eventRegion, double varSecondaryBosonPt, double varSecondaryBosonMass);
    int GetCutFlowHistogram(TString cutLabel, double weight_cutflow, TString systName, int cutFlowIndicator);

    int cutFlowIndicator;

    void InitializeVariables();

    double varSecondaryBosonMass;
    double varSecondaryBosonPt;
    double varSecondaryBosonEta;
    TString varSecondaryBosonTag;
    double varPrimaryBosonMass;
    double varResonanceMass1;
    double varResonanceMass2;
    double varResonanceMinMass;
    double varResonanceMaxMass;
    double varTopKillerMass;
    double varLeptonPt;
    double varLeptonEta;
    double varHT;
    double varMET;
    double varMEToverHT;
    double varMETPhi;
    double varMETandLeptonDeltaPhi;
    double varNeutrinoandLeptonDeltaR;
    double varMETandLeptonMassT;
    int varNJet;
    int varNBJet;
    int varSignalRegion;

    Particle GetPOGCorrMET(Particle UncorrMET, bool IsPuppiMET);

    bool WrongMissingEt(void);

    singlelepton_analysis();
    ~singlelepton_analysis();

};

#endif
