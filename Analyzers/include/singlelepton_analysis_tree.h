#ifndef singlelepton_analysis_tree_h
#define singlelepton_analysis_tree_h

#include "AnalyzerCore.h"

class singlelepton_analysis_tree : public AnalyzerCore {

public:

    void initializeAnalyzer();

    void executeEventFromParameter(AnalyzerParameter param);
    void executeEvent();

    bool RunSyst;
    bool RunNewPDF;
    bool RunXSecSyst;

    bool invertLeptonIsolation;

    std::vector<TString> muonTightIDs, muonLooseIDs;
    std::vector<TString> electronTightIDs, electronLooseIDs;
    std::vector<TString> jetIDs, fatjetIDs;

    JetTagging::Parameters bTaggingWP;
    JetTagging::Tagger pNetXbbMD, pNetXqqMD, pNetXccMD, pNetQCDMD;
    double GetParticleNetScore(FatJet fatjet, TString tagger);

    std::vector<TString> muonTriggers, electronTriggers;

    double muonPtCut, electronPtCut, jetPtCut, fatjetPtCut, leptonPtCut;

    std::vector<Muon> allMuons;
    std::vector<Electron> allElectrons;
    std::vector<Jet> allJets;
    std::vector<FatJet> allFatJets;

    void WriteHist();

    TTree *myTreeMuonXbb;
    TTree *myTreeMuonXqq;
    TTree *myTreeElectronXbb;
    TTree *myTreeElectronXqq;

    Int_t tree_charge;
    Float_t tree_dphi_leptonmet;
    Float_t tree_masst_fatjetmet;
    Float_t tree_mass_fatjetlepton;
    Float_t tree_masst_fatjetleptonmet;
    Float_t tree_masst_leptonmet;
    Float_t tree_met;
    Int_t tree_n_jet;
    Float_t tree_pt_lepton;
    Float_t tree_sdmass_fatjet;
    Float_t tree_st;
    Float_t tree_ht;
    Float_t tree_weight;

    double GetReconstructedNeutrinoDet(Lepton lepton, Particle missingEt);
    Particle GetReconstructedNeutrino(Lepton lepton, Particle missingEt);

    singlelepton_analysis_tree();
    ~singlelepton_analysis_tree();

};

#endif
