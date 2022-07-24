#include "sandbox.h"

void sandbox::initializeAnalyzer(){

    muonIsoTriggers.clear();
    muonHighPtTriggers.clear();
    electronTriggers.clear();

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


}

void sandbox::executeEvent(){

    allMuons.clear();
    allElectrons.clear();
    allJets.clear();
    allFatJets.clear();

    allMuons = GetAllMuons();
    allElectrons = GetAllElectrons();
    allJets = GetAllJets();
    allFatJets = puppiCorr->Correct(GetAllFatJets());

    AnalyzerParameter param;

    executeEventFromParameter(param);

}

void sandbox::executeEventFromParameter(AnalyzerParameter param){

    if(!PassMETFilter()) return;

    Event event = GetEvent();
    Particle missingEt = event.GetMETVector();

    std::vector<Electron> electrons = SelectElectrons(allElectrons, "passMVAID_iso_WP80", 40., 2.1);

    std::vector<Muon> muonsNoIso = SelectMuons(allMuons, "POGTight", 40., 2.1); 
    std::vector<Muon> muons;
    for (unsigned int i=0; i < muonsNoIso.size(); i++){
        if (muonsNoIso.at(i).RelIso() < 0.15){
            muons.push_back(muonsNoIso.at(i));
        }
    }

    bool passMuonIsoTriggers = ((event.PassTrigger(muonIsoTriggers)) && (muons.size() == 1) && (electrons.size() == 0));
    bool passElectronTriggers = ((event.PassTrigger(electronTriggers)) && (muons.size() == 0) && (electrons.size() == 1));

    if (!passMuonIsoTriggers && !passElectronTriggers) return;

    double weight = 1.;
    if (!IsDATA){
        weight = weight * MCweight(true, true) ;
        weight = weight * GetPrefireWeight(0);
        weight = weight * GetPileUpWeight(nPileUp,0); 
        weight = weight * event.GetTriggerLumi("Full");
        /*
        for (unsigned int i=0; i < electrons.size(); i++){
            weight = weight * mcCorr->ElectronReco_SF(electrons.at(i).scEta(), electrons.at(i).UncorrPt(), 0.);
            weight = weight * mcCorr->ElectronID_SF(param.Electron_ID_SF_Key, electrons.at(i).scEta(), electrons.at(i).Pt(), 0.);
            // FIXME no trigger SF
        }
        for (unsigned int i=0; i < muons.size(); i++){
            double muonMiniAODpT = muons.at(i).MiniAODPt() > 120. ? 119.9 :muons.at(i).MiniAODPt();
            weight = weight * mcCorr->MuonID_SF(param.Muon_ID_SF_Key, muons.at(i).Eta(), muonMiniAODpT, 0.);
            weight = weight * mcCorr->MuonISO_SF(param.Muon_ISO_SF_Key, muons.at(i).Eta(), muonMiniAODpT, 0.);
        }
        weight = weight * mcCorr->MuonTrigger_SF(param.Muon_Tight_ID, param.Muon_Trigger_SF_Key, muons);*/
    }

    std::vector<LHE> lhes = GetLHEs();
    for (unsigned int i=0; i < lhes.size(); i++){
        LHE lheptl = lhes.at(i);
        lheptl.Print();        
    }
    /*
    for (unsigned int i=0; i < gens.size(); i++){
        Gen ptl = gens.at(i);
    }*/
}

sandbox::sandbox(){

}

sandbox::~sandbox(){

}


