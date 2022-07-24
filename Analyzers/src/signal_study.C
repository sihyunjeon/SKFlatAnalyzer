#include "signal_study.h"

void signal_study::initializeAnalyzer(){

}

void signal_study::executeEvent(){

    allMuons = GetAllMuons();
    allElectrons = GetAllElectrons();
    allJets = GetAllJets();
    allFatJets = puppiCorr->Correct(GetAllFatJets());

    AnalyzerParameter param;

    executeEventFromParameter(param);

}

void signal_study::executeEventFromParameter(AnalyzerParameter param){

    double weight = MCweight(true, true)/abs(MCweight(true, true));

    FillHist("COMMON_no_cut", 0., weight, 1, 0., 1.);

    if(!PassMETFilter()) return;

    FillHist("COMMON_pass_met_filter", 0., weight, 1, 0., 1.);

    std::vector<TString> muonIsoTriggers, muonHighPtTriggers, electronTriggers;

    if (DataYear == 2016){

        muonIsoTriggers.push_back("HLT_IsoMu24_v");

        muonHighPtTriggers.push_back("HLT_Mu50_v");
        muonHighPtTriggers.push_back("HLT_TkMu50_v");

        electronTriggers.push_back("HLT_Ele27_WPTight_Gsf_v");
        electronTriggers.push_back("HLT_Photon175_v");
        electronTriggers.push_back("HLT_Ele115_CaloIdVT_GsfTrkIdT_v");

    }
    else if (DataYear == 2017){

        muonIsoTriggers.push_back("HLT_IsoMu27_v");

        muonHighPtTriggers.push_back("HLT_Mu50_v");
        muonHighPtTriggers.push_back("HLT_OldMu100_v");
        muonHighPtTriggers.push_back("HLT_TkMu100_v");

        electronTriggers.push_back("HLT_Ele35_WPTight_Gsf_v");
        electronTriggers.push_back("HLT_Photon200_v");
        electronTriggers.push_back("HLT_Ele115_CaloIdVT_GsfTrkIdT_v");

    }
    else if(DataYear==2018){

        muonIsoTriggers.push_back("HLT_IsoMu24_v");

        muonHighPtTriggers.push_back("HLT_Mu50_v");
        muonHighPtTriggers.push_back("HLT_OldMu100_v");
        muonHighPtTriggers.push_back("HLT_TkMu100_v");

        electronTriggers.push_back("HLT_Ele32_WPTight_Gsf_v");
        electronTriggers.push_back("HLT_Photon200_v");
        electronTriggers.push_back("HLT_Ele115_CaloIdVT_GsfTrkIdT_v");

    }

    Event event = GetEvent();
    Particle missingEt = event.GetMETVector();

    bool passMuonIsoTriggersWithRelIso = event.PassTrigger(muonIsoTriggers);
    bool passMuonIsoTriggersWithMiniIso = event.PassTrigger(muonIsoTriggers);
    bool passMuonHighPtTriggers = event.PassTrigger(muonHighPtTriggers);
    bool passElectronTriggersWithHEEP = event.PassTrigger(electronTriggers);
    bool passElectronTriggersWithCutBased = event.PassTrigger(electronTriggers);
    bool passElectronTriggersWithMVA = event.PassTrigger(electronTriggers);

    std::vector<FatJet> fatjets = SelectFatJets(allFatJets, "tight", 200, 2.1);

    if (fatjets.size() == 0) return;
    FillHist("COMMON_at_least_one_fatjet", 0., weight, 1, 0., 1.);

    if (passMuonIsoTriggersWithRelIso){

        TString triggerString = "passMuonIsoTriggersWithRelIso";

        std::vector<Muon> muonsNoIso = SelectMuons(allMuons, "POGTight", 40., 2.1);
        std::vector<Muon> muons;
        for (unsigned int i=0; i < muonsNoIso.size(); i++){
            if (muonsNoIso.at(i).RelIso() < 0.15){
                muons.push_back(muonsNoIso.at(i));
            }
        }

        if (muons.size() == 1) FillHist(triggerString + "_one_muon", 0., weight, 1, 0., 1.);

    }


    if (passMuonIsoTriggersWithMiniIso){

        TString triggerString = "passMuonIsoTriggersWithMiniIso";

        std::vector<Muon> muonsNoIso = SelectMuons(allMuons, "POGTight", 55., 2.1);
        std::vector<Muon> muons; 
        for (unsigned int i=0; i < muonsNoIso.size(); i++){
            if (muonsNoIso.at(i).MiniRelIso() < 0.15){
                muons.push_back(muonsNoIso.at(i));
            }
        }

        if (muons.size() == 1) FillHist(triggerString + "_one_muon", 0., weight, 1, 0., 1.);

    }


    if (passMuonHighPtTriggers){

        TString triggerString = "passMuonHighPtTriggers";

        std::vector<Muon> muons = SelectMuons(UseTunePMuon(allMuons), "POGHighPtWithLooseTrkIso", 55., 2.1);

        if (muons.size() == 1) FillHist(triggerString + "_one_muon", 0., weight, 1, 0., 1.);

    }


    if (passElectronTriggersWithHEEP){

        TString triggerString = "passElectronTriggersWithHEEP";

        std::vector<Electron> electrons = SelectElectrons(allElectrons, "passHEEPID", 55., 2.1);

        if (electrons.size() == 1) FillHist(triggerString + "_one_electron", 0., weight, 1, 0., 1.);

    }


    if (passElectronTriggersWithCutBased){

        TString triggerString = "passElectronTriggersWithCutBased";

        std::vector<Electron> electrons = SelectElectrons(allElectrons, "passMediumID", 55., 2.1);

        if (electrons.size() == 1) FillHist(triggerString + "_one_electron", 0., weight, 1, 0., 1.);

    }


    if (passElectronTriggersWithMVA){

        TString triggerString = "passElectronTriggersWithMVA";

        std::vector<Electron> electrons = SelectElectrons(allElectrons, "passMVAID_iso_WP80", 55., 2.1);

        if (electrons.size() == 1) FillHist(triggerString + "_one_electron", 0., weight, 1, 0., 1.);

    }

}

signal_study::signal_study(){

}

signal_study::~signal_study(){

}


