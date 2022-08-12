#include "singlelepton_analysis.h"

singlelepton_analysis::singlelepton_analysis(){


}

void singlelepton_analysis::initializeAnalyzer(){

    if (HasFlag("nonprompt")){
        invertLeptonIsolation = true;
    }

    muonTightIDs.clear();
    muonLooseIDs.clear();
    electronTightIDs.clear();
    electronLooseIDs.clear();
    jetIDs.clear();
    fatjetIDs.clear();

    muonTightIDs.push_back("POGTight");
    muonLooseIDs.push_back("POGMedium");

//    electronTightIDs.push_back("passMediumID");
//    electronLooseIDs.push_back("passLooseID");
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
        muonPtCut = 40.;
        electronPtCut = 40.;
        leptonPtCut = 10.;
    }
    else if (DataYear == 2017){
        muonTriggers.push_back("HLT_IsoMu27_v");
        electronTriggers.push_back("HLT_Ele35_WPTight_Gsf_v");
        electronTriggers.push_back("HLT_Photon200_v");
        electronTriggers.push_back("HLT_Ele115_CaloIdVT_GsfTrkIdT_v");
        muonPtCut = 40.;
        electronPtCut = 40.;
        leptonPtCut = 10.;
    }
    else if(DataYear==2018){
        muonTriggers.push_back("HLT_IsoMu24_v");
        electronTriggers.push_back("HLT_Ele32_WPTight_Gsf_v");
        electronTriggers.push_back("HLT_Photon200_v");
        electronTriggers.push_back("HLT_Ele115_CaloIdVT_GsfTrkIdT_v");
        muonPtCut = 40.;
        electronPtCut = 40.;
        leptonPtCut = 10.;
    }

    jetPtCut = 30.; fatjetPtCut = 200.;

    bTaggingWP = JetTagging::Parameters(JetTagging::DeepJet, JetTagging::Medium, JetTagging::incl, JetTagging::comb);

    mcCorr->SetJetTaggingParameters({bTaggingWP});

    pNetXbbMD = JetTagging::particleNetMD_Xbb;
    pNetXccMD = JetTagging::particleNetMD_Xcc;
    pNetXqqMD = JetTagging::particleNetMD_Xqq;
    pNetQCDMD = JetTagging::particleNetMD_QCD;

}


singlelepton_analysis::~singlelepton_analysis(){


}

void singlelepton_analysis::executeEvent(){

    allMuons = GetAllMuons();
    allElectrons = GetAllElectrons();
    allJets = GetAllJets();
    allFatJets = puppiCorr->Correct(GetAllFatJets());

    AnalyzerParameter param; param.Clear();

    param.syst_ = AnalyzerParameter::Central;

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

    executeEventFromParameter(param);

}

void singlelepton_analysis::executeEventFromParameter(AnalyzerParameter param){

    if(!PassMETFilter()) return;

    Event event = GetEvent();

    if (!(event.PassTrigger(muonTriggers) || event.PassTrigger(electronTriggers))) return;

    // define leptons
    std::vector<Muon> muonsLooseNoIso = SelectMuons(allMuons, param.Muon_Loose_ID, leptonPtCut, 2.4);
    std::vector<Muon> muonsLoose;
    for (unsigned int i=0 ; i < muonsLooseNoIso.size(); i++){
        Muon lepton = muonsLooseNoIso.at(i);
        if (lepton.RelIso() < 0.60){
            muonsLoose.push_back(lepton);
        }
    }
    std::vector<Muon> muons;
    for (unsigned int i=0 ; i < muonsLoose.size(); i++){
        Muon lepton = muonsLoose.at(i);
        if (lepton.PassID(param.Muon_Tight_ID)){
            if (!invertLeptonIsolation && (lepton.RelIso() < 0.15)){
                muons.push_back(lepton);
            }
            if (invertLeptonIsolation && (lepton.RelIso() > 0.20)){
                muons.push_back(lepton);
            }
        }
    }
    std::sort(muons.begin(), muons.end(), PtComparing);

    std::vector<Electron> electronsLoose = SelectElectrons(allElectrons, param.Electron_Loose_ID, leptonPtCut, 2.5, true);
    std::vector<Electron> electrons = SelectElectrons(electronsLoose, param.Electron_Tight_ID, leptonPtCut, 2.1);
    std::sort(electrons.begin(), electrons.end(), PtComparing);

    // define jets ak8
    std::vector<FatJet> fatjetsNoSDMass = SelectFatJets(allFatJets, param.FatJet_ID, fatjetPtCut, 2.4);
    fatjetsNoSDMass = FatJetsVetoLeptonInside(fatjetsNoSDMass, electronsLoose, muonsLoose, 0.4);
    std::sort(fatjetsNoSDMass.begin(), fatjetsNoSDMass.end(), PtComparing);
    std::vector<FatJet> fatjets;

    std::vector<FatJet> xtobbfatjets, xtoqqfatjets;
    for (unsigned int i=0; i < fatjetsNoSDMass.size(); i++){
        if(fatjetsNoSDMass.at(i).SDMass() > 50.){
            fatjets.push_back(fatjetsNoSDMass.at(i));
        }
    }

    // define jets ak4
    std::vector<Jet> jets = SelectJets(allJets, param.Jet_ID, jetPtCut, 2.4);
    jets = JetsAwayFromFatJet(jets, fatjets, 1.2);

    //std::vector<Jet> jets = SelectJetsPileupMVA(JetsVetoLeptonInside(jetsLoose, electronsLoose, muonsLoose, 0.4), "loose");
    jets = JetsVetoLeptonInside(jets, electronsLoose, muonsLoose, 0.4);
    std::sort(jets.begin(), jets.end(), PtComparing);

    double bTaggingWPMedium = mcCorr->GetJetTaggingCutValue(bTaggingWP.j_Tagger, bTaggingWP.j_WP);
    std::vector<Jet> bjets;
    for (unsigned int i=0; i < jets.size(); i++){
        if( jets.at(i).GetTaggerResult(bTaggingWP.j_Tagger) >= bTaggingWPMedium ) bjets.push_back(jets.at(i));
    }

    // define missing et
    Particle missingEt = event.GetMETVector();

    std::vector<Lepton> leptons; leptons.clear();
    for (unsigned int i=0; i < muons.size(); i++) leptons.push_back(muons.at(i));
    for (unsigned int i=0; i < electrons.size(); i++) leptons.push_back(electrons.at(i));
    std::sort(leptons.begin(), leptons.end(), PtComparing);

    double weight = 1.; double top_pt_weight = 1.;
    if (!IsDATA){
        weight = weight * MCweight(true, true) ;
        weight = weight * GetPrefireWeight(0);
        weight = weight * GetPileUpWeight(nPileUp,0); 
        weight = weight * event.GetTriggerLumi("Full");
        weight = weight * mcCorr->GetBTaggingReweight_1a(jets, bTaggingWP);
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
        weight = weight * mcCorr->MuonTrigger_SF(param.Muon_Tight_ID, param.Muon_Trigger_SF_Key, muons);
        if(MCSample.Contains("TT") && MCSample.Contains("powheg")){
            std::vector<Gen> gens = GetGens();
            top_pt_weight = mcCorr->GetTopPtReweight(gens);
            FillHist("top_pt_weight", top_pt_weight, 1., 200, 0., 2.);
        }
    }

    // trigger settings
    bool passMuonTrigger = (event.PassTrigger(muonTriggers) && muons.size()>= 1) ? muons.at(0).Pt() > muonPtCut : false;
    bool passElectronTrigger = (event.PassTrigger(electronTriggers) && electrons.size() >= 1) ? electrons.at(0).Pt() > electronPtCut : false;

    // lepton related selections
    bool hasAtLeastOneLepton = (leptons.size() >= 1);
    bool hasOneMuon = hasAtLeastOneLepton ? (muons.size() == 1 && muonsLoose.size() == 1) : false;
    bool hasOneElectron = hasAtLeastOneLepton ? (electrons.size() == 1 && electronsLoose.size() == 1) : false;
    bool hasZeroMuon = (muonsLoose.size() == 0);
    bool hasZeroElectron = (electronsLoose.size() == 0);
    bool hasTwoLepton = (hasOneMuon && hasOneElectron);

    // jet related selections
    bool hasAtLeastOneFatjet = (fatjets.size() >= 1);

    // signal preselection
    bool hasSignalObject = (hasAtLeastOneLepton && hasAtLeastOneFatjet);
    bool hasMissingEtAbove50 = (missingEt.Pt() > 50.);
    bool hasMissingEtAbove100 = (missingEt.Pt() > 100.);

    if (!hasSignalObject) return;

    Lepton signalLepton = leptons.at(0);
    FatJet signalFatjet = fatjets.at(0);
    Particle signalPrimaryBoson = (signalLepton + signalFatjet + missingEt);

    // others
    bool hasZeroJet = (jets.size() == 0);
    bool hasZeroBJet =  true; //(bjets.size() == 0);
    bool hasMtLeptonMissingEtAbove200 = (signalLepton + missingEt).Mt() > 200.;
    bool hasPositiveCharge = (signalLepton.Charge() > 0);

    // boosted signal region definitions
    bool hasFatjetMassIncl = ((signalFatjet.SDMass() >= 65.) && (signalFatjet.SDMass() < 145.));
    bool hasFatjetMassHigh = ((signalFatjet.SDMass() >= 105.) && (signalFatjet.SDMass() < 145.));
    bool hasFatjetMassLow = ((signalFatjet.SDMass() >= 65.) && (signalFatjet.SDMass() < 105.));

    bool hasFatjetPtIncl = (signalFatjet.Pt() >= 200.);
    bool hasFatjetPtHigh = (signalFatjet.Pt() > 350.);
    bool hasFatjetPtLow = ((signalFatjet.Pt() <= 350.) && (signalFatjet.Pt() >= 200.));

    double pNetScoreXbbMD = GetParticleNetScore(signalFatjet, "XbbMD");
    double pNetScoreXqqMD = GetParticleNetScore(signalFatjet, "XqqMD");

    bool hasBoostedXbb = (pNetScoreXbbMD > 0.98);
    bool hasBoostedXqq = (!hasBoostedXbb) ? (pNetScoreXqqMD > 0.82) : false;

    Particle signalNeutrino = GetReconstructedNeutrino(signalLepton, missingEt);
    int signalNeutrinoDet = GetReconstructedNeutrinoDet(signalLepton, missingEt);

    double ST = missingEt.Pt();
    Particle signalEff = missingEt;
    for (unsigned int i=0; i < leptons.size(); i++){
        Particle ptl = leptons.at(i);
        ST = ST + ptl.Pt();
        signalEff = signalEff + ptl;
    }
    for (unsigned int i=0; i < fatjets.size(); i++){
        Particle ptl = fatjets.at(i);
        ST = ST + ptl.Pt();
        signalEff = signalEff + ptl;
    }
    for (unsigned int i=0; i < jets.size(); i++){
        Particle ptl = jets.at(i);
        ST = ST + ptl.Pt();
        signalEff = signalEff + ptl;
    }

    bool hasStBelow500 = (ST < 500.0);

    bool isSignalBin0 = (signalPrimaryBoson.Mt() > 500.0 && signalPrimaryBoson.Mt() <= 700.0);
    bool isSignalBin1 = (signalPrimaryBoson.Mt() > 700.0 && signalPrimaryBoson.Mt() <= 1000.0);
    bool isSignalBin2 = (signalPrimaryBoson.Mt() > 1000.0 && signalPrimaryBoson.Mt() <= 1200.0);
    bool isSignalBin3 = (signalPrimaryBoson.Mt() > 1200.0 && signalPrimaryBoson.Mt() <= 1500.0);
    bool isSignalBin4 = (signalPrimaryBoson.Mt() > 1500.0);

    bool hasDeltaPhiLeptonMissingEtAbove1p0 = (fabs(signalLepton.DeltaPhi(missingEt)) > 1.0);

    std::map<TString, bool> eventRegions;
    bool isBarrelLepton = (std::fabs(signalLepton.Eta()) < 0.9);
    if (invertLeptonIsolation){
        eventRegions["DataDriven_NonIsolatedMuon-Inclusive"] = passMuonTrigger && hasOneMuon && hasZeroElectron && hasFatjetMassIncl;

        eventRegions["DataDriven_NonIsolatedMuon-Barrel"] = eventRegions["DataDriven_NonIsolatedMuon-Inclusive"] && isBarrelLepton;
        eventRegions["DataDriven_NonIsolatedMuon-Endcap"] = eventRegions["DataDriven_NonIsolatedMuon-Inclusive"] && !isBarrelLepton;

        eventRegions["DataDriven_NonIsolatedMuon-BarrelHighMissingEt"] = eventRegions["DataDriven_NonIsolatedMuon-Barrel"] && hasMissingEtAbove50;
        eventRegions["DataDriven_NonIsolatedMuon-EndcapHighMissingEt"] = eventRegions["DataDriven_NonIsolatedMuon-Endcap"] && hasMissingEtAbove50;
        eventRegions["DataDriven_NonIsolatedMuon-BarrelLowMissingEt"] = eventRegions["DataDriven_NonIsolatedMuon-Barrel"] && !hasMissingEtAbove50;
        eventRegions["DataDriven_NonIsolatedMuon-EndcapLowMissingEt"] = eventRegions["DataDriven_NonIsolatedMuon-Endcap"] && !hasMissingEtAbove50;
    }

    if (!invertLeptonIsolation){

        eventRegions["DataDriven_IsolatedMuon-Inclusive"] = passMuonTrigger && hasOneMuon && hasZeroElectron && hasFatjetMassIncl;

        eventRegions["DataDriven_IsolatedMuon-Barrel"] = eventRegions["DataDriven_NonIsolatedMuon-Inclusive"] && isBarrelLepton;
        eventRegions["DataDriven_IsolatedMuon-Endcap"] = eventRegions["DataDriven_NonIsolatedMuon-Inclusive"] && !isBarrelLepton;

        eventRegions["DataDriven_IsolatedMuon-BarrelHighMissingEt"] = eventRegions["DataDriven_NonIsolatedMuon-Barrel"] && hasMissingEtAbove50;
        eventRegions["DataDriven_IsolatedMuon-EndcapHighMissingEt"] = eventRegions["DataDriven_NonIsolatedMuon-Endcap"] && hasMissingEtAbove50;
        eventRegions["DataDriven_IsolatedMuon-BarrelLowMissingEt"] = eventRegions["DataDriven_NonIsolatedMuon-Barrel"] && !hasMissingEtAbove50;
        eventRegions["DataDriven_IsolatedMuon-EndcapLowMissingEt"] = eventRegions["DataDriven_NonIsolatedMuon-Endcap"] && !hasMissingEtAbove50;

        eventRegions["Preselection_MuonPreselection"] = passMuonTrigger && hasOneMuon && hasZeroElectron && hasMissingEtAbove50 && hasFatjetMassIncl;
        eventRegions["Preselection_ElectronPreselection"] = passElectronTrigger && hasZeroMuon && hasOneElectron && hasMissingEtAbove50 && hasFatjetMassIncl;

        eventRegions["Signal_MuonSignalRegionXbb-HighMassHighPtJ"] = eventRegions["Preselection_MuonPreselection"] && hasZeroBJet && hasMtLeptonMissingEtAbove200 && hasBoostedXbb && hasFatjetMassHigh && hasFatjetPtHigh;
        eventRegions["Signal_MuonSignalRegionXbb-LowMassHighPtJ"] = eventRegions["Preselection_MuonPreselection"] && hasZeroBJet && hasMtLeptonMissingEtAbove200 && hasBoostedXbb && hasFatjetMassLow && hasFatjetPtHigh;
        eventRegions["Signal_MuonSignalRegionXbb-HighMassLowPtJ"] = eventRegions["Preselection_MuonPreselection"] && hasZeroBJet && hasMtLeptonMissingEtAbove200 && hasBoostedXbb && hasFatjetMassHigh && hasFatjetPtLow;
        eventRegions["Signal_MuonSignalRegionXbb-LowMassLowPtJ"] = eventRegions["Preselection_MuonPreselection"] && hasZeroBJet && hasMtLeptonMissingEtAbove200 && hasBoostedXbb && hasFatjetMassLow && hasFatjetPtLow;

        eventRegions["Signal_MuonSignalRegionXqq-HighMassHighPtJ"] = eventRegions["Preselection_MuonPreselection"] && hasZeroBJet && hasMtLeptonMissingEtAbove200 && hasBoostedXqq && hasFatjetMassHigh && hasFatjetPtHigh;
        eventRegions["Signal_MuonSignalRegionXqq-LowMassHighPtJ"] = eventRegions["Preselection_MuonPreselection"] && hasZeroBJet && hasMtLeptonMissingEtAbove200 && hasBoostedXqq && hasFatjetMassLow && hasFatjetPtHigh;
        eventRegions["Signal_MuonSignalRegionXqq-HighMassLowPtJ"] = eventRegions["Preselection_MuonPreselection"] && hasZeroBJet && hasMtLeptonMissingEtAbove200 && hasBoostedXqq && hasFatjetMassHigh && hasFatjetPtLow;
        eventRegions["Signal_MuonSignalRegionXqq-LowMassLowPtJ"] = eventRegions["Preselection_MuonPreselection"] && hasZeroBJet && hasMtLeptonMissingEtAbove200 && hasBoostedXqq && hasFatjetMassLow && hasFatjetPtLow;

        /*
        eventRegions["Control_MuonControlRegionXbb-InvB"] = eventRegions["Preselection_MuonPreselection"] && !hasZeroBJet && hasMtLeptonMissingEtAbove200 && hasBoostedXbb;
        eventRegions["Control_MuonControlRegionXbb-InvMt"] = eventRegions["Preselection_MuonPreselection"] && hasZeroBJet && !hasMtLeptonMissingEtAbove200 && hasBoostedXbb;
        eventRegions["Control_MuonControlRegionXbb-InvDeltaPhi"] = (passMuonTrigger && hasOneMuon && hasZeroElectron && hasMissingEtAbove50) && hasZeroBJet && hasBoostedXbb && !hasDeltaPhiLeptonMissingEtAbove1p0;
        eventRegions["Control_MuonControlRegionXqq-InvB"] = eventRegions["Preselection_MuonPreselection"] && !hasZeroBJet && hasMtLeptonMissingEtAbove200 && hasBoostedXqq;
        eventRegions["Control_MuonControlRegionXqq-InvMt"] = eventRegions["Preselection_MuonPreselection"] && hasZeroBJet && !hasMtLeptonMissingEtAbove200 && hasBoostedXqq;
        eventRegions["Control_MuonControlRegionXqq-InvDeltaPhi"] = (passMuonTrigger && hasOneMuon && hasZeroElectron && hasMissingEtAbove50) && hasZeroBJet && hasBoostedXqq && !hasDeltaPhiLeptonMissingEtAbove1p0;

        eventRegions["Control_ElectronControlRegionXbb-InvB"] = eventRegions["Preselection_ElectronPreselection"] && !hasZeroBJet && hasMtLeptonMissingEtAbove200 && hasBoostedXbb;
        eventRegions["Control_ElectronControlRegionXbb-InvMt"] = eventRegions["Preselection_ElectronPreselection"] && hasZeroBJet && !hasMtLeptonMissingEtAbove200 && hasBoostedXbb;
        eventRegions["Control_ElectronControlRegionXbb-InvDeltaPhi"] = (passElectronTrigger && hasZeroMuon && hasOneElectron && hasMissingEtAbove50) && hasZeroBJet && hasBoostedXbb && !hasDeltaPhiLeptonMissingEtAbove1p0;

        eventRegions["Control_ElectronControlRegionXqq-InvB"] = eventRegions["Preselection_ElectronPreselection"] && !hasZeroBJet && hasMtLeptonMissingEtAbove200 && hasBoostedXqq;
        eventRegions["Control_ElectronControlRegionXqq-InvMt"] = eventRegions["Preselection_ElectronPreselection"] && hasZeroBJet && !hasMtLeptonMissingEtAbove200 && hasBoostedXqq;
        eventRegions["Control_ElectronControlRegionXqq-InvDeltaPhi"] = (passElectronTrigger && hasZeroMuon && hasOneElectron && hasMissingEtAbove50) && hasZeroBJet && hasBoostedXqq && !hasDeltaPhiLeptonMissingEtAbove1p0;
        */

    }

    std::map<TString, bool>::iterator itEventRegions;

    for (itEventRegions = eventRegions.begin(); itEventRegions != eventRegions.end(); ++itEventRegions){

        if (itEventRegions->second){

            TString eventRegion = itEventRegions->first;

            FillHist(eventRegion + "_dphi_leptonmet", signalLepton.DeltaPhi(missingEt), weight, 100, -5., 5.);
            FillHist(eventRegion + "_dphi_fatjetmet", missingEt.DeltaPhi(signalFatjet), weight, 100, -5., 5.);
            FillHist(eventRegion + "_dphi_fatjetlepton", signalLepton.DeltaPhi(signalFatjet), weight, 100, -5., 5.);

            FillHist(eventRegion + "_masst_leptonmet", (signalLepton + missingEt).Mt(), weight, 5000, 0., 5000.);
            FillHist(eventRegion + "_masst_fatjetmet", (signalFatjet + missingEt).Mt(), weight, 5000, 0., 5000.);
            FillHist(eventRegion + "_mass_fatjetlepton", (signalLepton + signalFatjet).M(), weight, 5000, 0., 5000.);

            FillHist(eventRegion + "_eta_lepton", signalLepton.Eta(), weight, 100, -5., 5.);
            FillHist(eventRegion + "_pt_lepton", signalLepton.Pt(), weight, 5000,0., 5000.);
            FillHist(eventRegion + "_reliso_lepton", signalLepton.RelIso(), weight, 50, 0., 1.);

            FillHist(eventRegion + "_sdmass_fatjet", signalFatjet.SDMass(), weight, 5000, 0., 5000.);
            FillHist(eventRegion + "_pt_fatjet", signalFatjet.Pt(), weight, 5000, 0., 5000.);

            FillHist(eventRegion + "_met", missingEt.Pt(), weight, 5000,0., 5000.);
            FillHist(eventRegion + "_st", ST, weight, 5000,0., 5000.);

            FillHist(eventRegion + "_masst_leptonmetfatjet", signalPrimaryBoson.Mt(), weight, 5000,0., 5000.);

            FillHist(eventRegion + "_pnetscorexbbmd_fatjet", pNetScoreXbbMD, weight, 50, 0., 1.);
            FillHist(eventRegion + "_pnetscorexqqmd_fatjet", pNetScoreXqqMD, weight, 50, 0., 1.);

            FillHist(eventRegion + "_n_events_weighted", 0, weight, 1, 0., 1.);
            FillHist(eventRegion + "_n_events_unweighted", 0, 1., 1, 0., 1.);
            FillHist(eventRegion + "_n_lep", (muons.size() + electrons.size()), weight, 5, 0., 5.);
            FillHist(eventRegion + "_n_jet", jets.size(), weight, 5, 0., 5.);
            FillHist(eventRegion + "_n_bjet", bjets.size(), weight, 5, 0., 5.);
            FillHist(eventRegion + "_n_fatjet", fatjets.size(), weight, 5, 0., 5.);
        }
    }

    return;
}

double singlelepton_analysis::GetReconstructedNeutrinoDet(Lepton lepton, Particle missingEt){

    double mW = 80.4;
    double A = mW*mW + 2*missingEt.Px()*lepton.Px() + 2*missingEt.Py()*lepton.Py();
    double a = 4*lepton.Pz()*lepton.Pz() - 4*lepton.E()*lepton.E();
    double b = 4*lepton.Pz()*A;
    double c = A*A - 4*lepton.E()*lepton.E()*missingEt.Pt()*missingEt.Pt();
    double det = b*b - 4*a*c;

    if (det < 0) return 0.;
    else return 1.;

}

Particle singlelepton_analysis::GetReconstructedNeutrino(Lepton lepton, Particle missingEt){

    double pz;
    double mW = 80.4;

    double A = mW*mW + 2*missingEt.Px()*lepton.Px() + 2*missingEt.Py()*lepton.Py();
    double a = 4*lepton.Pz()*lepton.Pz() - 4*lepton.E()*lepton.E();
    double b = 4*lepton.Pz()*A;
    double c = A*A - 4*lepton.E()*lepton.E()*missingEt.Pt()*missingEt.Pt();
    double det = b*b - 4*a*c;

    if (det < 0){
        pz = -b / (2*a);
    }
    else{
        if (TMath::Abs(-b + TMath::Sqrt(det)) < TMath::Abs(-b - TMath::Sqrt(det))) pz = (-b + TMath::Sqrt(det)) / (2*a);
        else pz = (-b - TMath::Sqrt(det)) / (2*a);
    }


    Particle neutrino;
    neutrino.SetPxPyPzE(missingEt.Px(), missingEt.Py(), pz, TMath::Sqrt(missingEt.E()*missingEt.E() + pz*pz));

    return neutrino;

}

double singlelepton_analysis::GetParticleNetScore(FatJet fatjet, TString tagger){

     double pNetProbXbbMD = fatjet.GetTaggerResult(pNetXbbMD);
     double pNetProbXccMD = fatjet.GetTaggerResult(pNetXccMD);
     double pNetProbXqqMD = fatjet.GetTaggerResult(pNetXqqMD);
     double pNetProbQCDMD = fatjet.GetTaggerResult(pNetQCDMD);
     double pNetScoreXbbMD = pNetProbXbbMD / (pNetProbXbbMD + pNetProbQCDMD);
     double pNetScoreXqqMD = (pNetProbXccMD + pNetProbXqqMD) / (pNetProbXccMD + pNetProbXqqMD + pNetProbQCDMD);

     if (tagger == "XbbMD") return pNetScoreXbbMD;
     if (tagger == "XqqMD") return pNetScoreXqqMD;

     return -1.;

}


