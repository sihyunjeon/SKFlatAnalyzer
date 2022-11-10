#include "singlelepton_analysis.h"

singlelepton_analysis::singlelepton_analysis(){


}

void singlelepton_analysis::initializeAnalyzer(){

    muonTightIDs.clear();
    muonLooseIDs.clear();
    electronTightIDs.clear();
    electronLooseIDs.clear();
    jetIDs.clear();
    fatjetIDs.clear();

    muonTightIDs.push_back("POGTight");
    muonLooseIDs.push_back("POGMedium");

    electronTightIDs.push_back("passMVAID_iso_WP80");
    electronLooseIDs.push_back("passMVAID_iso_WP90");

    fatjetIDs.push_back("tight");
    jetIDs.push_back("tightLepVeto");

    muonTriggers.clear();
    electronTriggers.clear();

    if (DataYear == 2016){
        muonTriggers.push_back("HLT_IsoMu24_v");
        electronTriggers.push_back("HLT_Ele27_WPTight_Gsf_v");
        electronTriggers.push_back("HLT_Photon175_v");
        electronTriggers.push_back("HLT_Ele115_CaloIdVT_GsfTrkIdT_v");
        muonPtCut = 50.;
        electronPtCut = 50.;
        leptonPtCut = 10.;
    }
    else if (DataYear == 2017){
        muonTriggers.push_back("HLT_IsoMu27_v");
        electronTriggers.push_back("HLT_Ele35_WPTight_Gsf_v");
        electronTriggers.push_back("HLT_Photon200_v");
        electronTriggers.push_back("HLT_Ele115_CaloIdVT_GsfTrkIdT_v");
        muonPtCut = 50.;
        electronPtCut = 50.;
        leptonPtCut = 10.;
    }
    else if(DataYear==2018){
        muonTriggers.push_back("HLT_IsoMu24_v");
        electronTriggers.push_back("HLT_Ele32_WPTight_Gsf_v");
        electronTriggers.push_back("HLT_Photon200_v");
        electronTriggers.push_back("HLT_Ele115_CaloIdVT_GsfTrkIdT_v");
        muonPtCut = 50.;
        electronPtCut = 50.;
        leptonPtCut = 10.;
    }

    jetPtCut = 30.; fatjetPtCut = 200.;

}


singlelepton_analysis::~singlelepton_analysis(){


}

void singlelepton_analysis::executeEvent(){

    centralAllMuons = GetAllMuons();
    centralAllElectrons = GetAllElectrons();
    centralAllJets = GetAllJets();
    centralAllFatJets = puppiCorr->Correct(GetAllFatJets());

    AnalyzerParameter param; param.Clear();

    param.Muon_Tight_ID = muonTightIDs.at(0);
    param.Muon_Loose_ID = muonLooseIDs.at(0);
    param.Electron_Tight_ID = electronTightIDs.at(0);
    param.Electron_Loose_ID = electronLooseIDs.at(0);
    param.Jet_ID = jetIDs.at(0);
    param.FatJet_ID = fatjetIDs.at(0);

    param.Muon_ID_SF_Key = "NUM_TightID_DEN_TrackerMuons";
    param.Muon_ISO_SF_Key = "NUM_TightRelIso_DEN_TightIDandIPCut";
    if (DataYear == 2016){
        param.Muon_Trigger_SF_Key = "IsoMu24";
    }
    if (DataYear == 2017){
        param.Muon_Trigger_SF_Key = "IsoMu27";
    }
    if (DataYear == 2018){
        param.Muon_Trigger_SF_Key = "IsoMu24";
    }

    param.Electron_ID_SF_Key = "passMVAID_iso_WP80";
    param.Electron_Trigger_SF_Key = "";

    param.Name = "CENTRAL";
    executeEventFromParameter(param);

}

void singlelepton_analysis::executeEventFromParameter(AnalyzerParameter param){

    double weight = 1.;
    if(!IsDATA){
        weight = MCweight(true, true);
    }

    if(!PassMETFilter()) return;
    Event event = GetEvent();

    if (!(event.PassTrigger(muonTriggers) || event.PassTrigger(electronTriggers))) return;

    // define missing et
    Particle missingEt = event.GetMETVector();

    std::vector<Jet> allJets = centralAllJets;
    std::vector<FatJet> allFatJets = centralAllFatJets;
    std::vector<Muon> allMuons = centralAllMuons;
    std::vector<Electron> allElectrons = centralAllElectrons;

    // define muons
    std::vector<Muon> muonsLooseNoIso = SelectMuons(allMuons, param.Muon_Loose_ID, leptonPtCut, 2.4);
    std::vector<Muon> muons, muonsLoose;
    for (unsigned int i=0 ; i < muonsLooseNoIso.size(); i++){
        Muon lepton = muonsLooseNoIso.at(i);
        if (lepton.RelIso() < 0.60){
            muonsLoose.push_back(lepton);
        }
    }
    for (unsigned int i=0 ; i < muonsLoose.size(); i++){
        Muon lepton = muonsLoose.at(i);
        if (lepton.PassID(param.Muon_Tight_ID)){
            if (lepton.RelIso() < 0.15){
                if (fabs(lepton.Eta()) < 2.1){
                    muons.push_back(lepton);
                }
            }
        }
    }

    std::sort(muons.begin(), muons.end(), PtComparing);

    // define electrons
    std::vector<Electron> electronsLoose = SelectElectrons(allElectrons, param.Electron_Loose_ID, leptonPtCut, 2.5, true);
    std::vector<Electron> electrons = SelectElectrons(electronsLoose, param.Electron_Tight_ID, leptonPtCut, 2.1, true);
    std::sort(electrons.begin(), electrons.end(), PtComparing);

    // trigger settings
    bool isMuonTrigger = (event.PassTrigger(muonTriggers) && muons.size()>= 1) ? muons.at(0).Pt() > muonPtCut : false;
    bool isElectronTrigger = (event.PassTrigger(electronTriggers) && electrons.size() >= 1) ? electrons.at(0).Pt() > electronPtCut : false;
    if (!(isMuonTrigger || isElectronTrigger)) return;

    // define jets ak8
    std::vector<FatJet> fatjetsNoSDMass = SelectFatJets(allFatJets, param.FatJet_ID, fatjetPtCut, 2.4);
    std::vector<FatJet> fatjets;
    for (unsigned int i=0; i < fatjetsNoSDMass.size(); i++){
        FatJet fatjet = fatjetsNoSDMass.at(i);
        if (fatjet.SDMass() > 50.0){
            fatjets.push_back(fatjet); 
        }
    }
    fatjets = FatJetsVetoLeptonInside(fatjets, electronsLoose, muonsLoose, 0.4);
    std::sort(fatjets.begin(), fatjets.end(), PtComparing);

    // define jets ak4
    std::vector<Jet> jets = SelectJets(allJets, param.Jet_ID, jetPtCut, 2.4);
    jets = JetsAwayFromFatJet(jets, fatjets, 1.2);
    jets = JetsVetoLeptonInside(jets, electronsLoose, muonsLoose, 0.4);
    std::sort(jets.begin(), jets.end(), PtComparing);

    // TODO : Also need to add jets that doesn't veto from AK8 jet overlaps

    std::vector<Lepton> leptons; leptons.clear();
    for (unsigned int i=0; i < muons.size(); i++){
        leptons.push_back(muons.at(i));
    }
    for (unsigned int i=0; i < electrons.size(); i++){
        leptons.push_back(electrons.at(i));
    }
    std::sort(leptons.begin(), leptons.end(), PtComparing);

    bool isOneMuon = (muons.size() == 1) && (muonsLoose.size() == 1);
    bool isOneElectron = (electrons.size() == 1) && (electronsLoose.size() == 1);
    bool isZeroMuon = (muonsLoose.size() == 0);
    bool isZeroElectron = (electronsLoose.size() == 0);
    bool isMergedRegion = (fatjets.size() >= 1);
    bool isResolvedRegion = !isMergedRegion && (jets.size() >= 2);

    if (isMergedRegion){

    }
    else if (isResolvedRegion){

    }
    else{

        return;

    }

    return;
}

