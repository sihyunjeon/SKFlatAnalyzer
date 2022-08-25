#include "singlelepton_analysis.h"

singlelepton_analysis::singlelepton_analysis(){


}

void singlelepton_analysis::initializeAnalyzer(){

    if (HasFlag("nonprompt")) invertLeptonIsolation = true;
    else invertLeptonIsolation = false;

    if (HasFlag("syst") && !IsDATA)  runSystematics = true;
    else runSystematics = false;

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

    jetPtCut = 30.; fatjetPtCut = 250.;

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

    if (runSystematics){
        for (unsigned int i=0; i<AnalyzerParameter::NSyst; i++){
            param.syst_ = AnalyzerParameter::Syst(i);
            param.Name = "SYST_" + param.GetSystType();
            executeEventFromParameter(param);
        }
    }
}

void singlelepton_analysis::executeEventFromParameter(AnalyzerParameter param){

    if(!PassMETFilter()) return;

    Event event = GetEvent();

    if (!(event.PassTrigger(muonTriggers) || event.PassTrigger(electronTriggers))) return;


    if(param.syst_ == AnalyzerParameter::Central){

    }
    else if(param.syst_ == AnalyzerParameter::JetResUp){
        allJets = SmearJets( allJets, +1 );
        allFatJets = SmearFatJets( allFatJets, +1 );
    }
    else if(param.syst_ == AnalyzerParameter::JetResDown){
        allJets = SmearJets( allJets, -1 );
        allFatJets = SmearFatJets( allFatJets, -1 );
    }
    else if(param.syst_ == AnalyzerParameter::JetEnUp){
        allJets = ScaleJets( allJets, +1 );
        allFatJets = ScaleFatJets( allFatJets, +1 );
    }
    else if(param.syst_ == AnalyzerParameter::JetEnDown){
        allJets = ScaleJets( allJets, -1 );
        allFatJets = ScaleFatJets( allFatJets, -1 );
    }

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
    std::vector<Electron> electrons = SelectElectrons(electronsLoose, param.Electron_Tight_ID, leptonPtCut, 2.1);
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

    // define jets ak4 b-tagged
    double bTaggingWPCutValue = mcCorr->GetJetTaggingCutValue(bTaggingWP.j_Tagger, bTaggingWP.j_WP);
    std::vector<Jet> bjets;
    for (unsigned int i=0; i < jets.size(); i++){
        Jet jet = jets.at(i);
        if( GetBTaggingScore(jet) >= bTaggingWPCutValue ){
            bjets.push_back(jet);
        }
    }

    // define missing et
    Particle missingEt = event.GetMETVector();

    std::vector<Lepton> leptons; leptons.clear();
    for (unsigned int i=0; i < muons.size(); i++){
        leptons.push_back(muons.at(i));
    }
    for (unsigned int i=0; i < electrons.size(); i++){
        leptons.push_back(electrons.at(i));
    }
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
/*        if(MCSample.Contains("TT") && MCSample.Contains("powheg")){
            std::vector<Gen> gens = GetGens();
            top_pt_weight = mcCorr->GetTopPtReweight(gens);
            FillHist("top_pt_weight", top_pt_weight, 1., 200, 0., 2.);
        }*/
    }

    bool isOneMuon = (muons.size() == 1) && (muonsLoose.size() == 1);
    bool isOneElectron = (electrons.size() == 1) && (electronsLoose.size() == 1);
    bool isZeroMuon = (muonsLoose.size() == 0);
    bool isZeroElectron = (electronsLoose.size() == 0);
    bool isMergedRegion = (fatjets.size() >= 1);
    bool isResolvedRegion = !isMergedRegion && (jets.size() >= 2);

    Particle neutrino = GetReconstructedNeutrino(leptons.at(0), missingEt);

    InitializeVariables();

    varLeptonPt = leptons.at(0).Pt();
    varLeptonEta = leptons.at(0).Eta();
    varMET = missingEt.Pt();
    varMETPhi = missingEt.Phi();
    varMETandLeptonDeltaPhi = missingEt.DeltaPhi(leptons.at(0));
    varNeutrinoandLeptonDeltaR = neutrino.DeltaR(leptons.at(0));
    varMETandLeptonMassT = (leptons.at(0) + missingEt).Mt();
    varNJet = jets.size();
    varNBJet = bjets.size();
    for (unsigned int i=0; i < fatjets.size(); i++){
        FatJet fatjet = fatjets.at(i);
        varHT = varHT + fatjet.Pt();
    }
    for (unsigned int i=0; i < jets.size(); i++){
        Jet jet = jets.at(i);
        varHT = varHT + jet.Pt();
    }
    varMEToverHT = varMET/varHT;

    if (isMergedRegion){

        varSecondaryBosonMass = fatjets.at(0).SDMass();
        varSecondaryBosonPt = fatjets.at(0).Pt();
        varPrimaryBosonMass = (leptons.at(0) + fatjets.at(0) + missingEt).Mt();
        varSecondaryBosonEta = fatjets.at(0).Eta();

        if (GetParticleNetScore(fatjets.at(0), "XbbMD") > 0.94) varSecondaryBosonTag = "MergedXbb";
        else if (GetParticleNetScore(fatjets.at(0), "XqqMD") > 0.82) varSecondaryBosonTag = "MergedXqq";
        else varSecondaryBosonTag = "MergedXxx";

    }
    else if (isResolvedRegion){

        varSecondaryBosonMass = (jets.at(0) + jets.at(1)).M();
        varSecondaryBosonPt = (jets.at(0) + jets.at(1)).Pt();
        varPrimaryBosonMass = (leptons.at(0) + jets.at(0) + jets.at(1) + missingEt).Mt();
        varSecondaryBosonEta = (jets.at(0) + jets.at(1)).Eta();

        if (((GetBTaggingScore(jets.at(0)) > bTaggingWPCutValue) + (GetBTaggingScore(jets.at(1)) > bTaggingWPCutValue)) == 2) varSecondaryBosonTag = "ResolvedXbb";
        else if (((GetBTaggingScore(jets.at(0)) > bTaggingWPCutValue) + (GetBTaggingScore(jets.at(1)) > bTaggingWPCutValue)) == 1) varSecondaryBosonTag = "ResolvedXbq";
        else if (((GetBTaggingScore(jets.at(0)) > bTaggingWPCutValue) + (GetBTaggingScore(jets.at(1)) > bTaggingWPCutValue)) == 0) varSecondaryBosonTag = "ResolvedXqq";
        else varSecondaryBosonTag = "ResolvedXxx";

    }
    else{

        return;

    }

    std::map<TString, bool> eventRegions;
    bool isBarrelLepton = (std::fabs(varLeptonEta) < 0.9);

    bool isSecondaryBosonMassIncl = (varSecondaryBosonMass >= 70.0) && (varSecondaryBosonMass < 140.0);
    bool isSecondaryBosonMassHigh = isSecondaryBosonMassIncl && (varSecondaryBosonMass >= 110.0);
    bool isSecondaryBosonMassLow = isSecondaryBosonMassIncl && (varSecondaryBosonMass < 110.0);

    bool isSecondaryBosonPtIncl = (varSecondaryBosonPt >= 250.0);
    bool isSecondaryBosonPtHigh = isSecondaryBosonPtIncl && (varSecondaryBosonPt >= 350.0);
    bool isSecondaryBosonPtLow = isSecondaryBosonPtIncl && (varSecondaryBosonPt < 350.0);

    bool isSecondaryBosonTagged = (!(varSecondaryBosonTag.Contains("Xxx")));

    bool isEffectiveMassAbove500 = (varPrimaryBosonMass > 500.0);

    bool isNoMoreBJet = (isMergedRegion ? (varNBJet == 0) : (isResolvedRegion ? (varNBJet <= 2) : false));
    bool isMETAbove100 = (varMET > 100.0);
    bool isMtLeptonMETAbove250 = (varMETandLeptonMassT > 250.0);
    bool isDPhiLeptonMETAbove0p5Pi = (fabs(varMETandLeptonDeltaPhi) > 0.5 * TMath::Pi());
    bool isMtAndDPhiLeptonMET = isMtLeptonMETAbove250 && isDPhiLeptonMETAbove0p5Pi;
    bool isMEToverHTAbove0p25 = (varMEToverHT > 0.25);

    bool isSecondaryBosonMassAndPt = isSecondaryBosonMassIncl && isSecondaryBosonPtIncl;

    bool Preselection_Muon = isMuonTrigger && isOneMuon && isZeroElectron && isEffectiveMassAbove500;
    bool Preselection_Electron = isElectronTrigger && isOneElectron && isZeroMuon && isEffectiveMassAbove500;

    bool Preselection_Merged = isMergedRegion && isSecondaryBosonMassAndPt;
    bool Preselection_Resolved = isResolvedRegion && isSecondaryBosonMassAndPt;

    bool SignalSelection_Merged = isMtAndDPhiLeptonMET && isNoMoreBJet && isMEToverHTAbove0p25;
    bool SignalSelection_Resolved = isMtAndDPhiLeptonMET && isMEToverHTAbove0p25;
    bool ControlSelection_MergedInvMTDPhi = !isMtAndDPhiLeptonMET && isNoMoreBJet && isMEToverHTAbove0p25;
    bool ControlSelection_ResolvedInvMTDPhi = !isMtAndDPhiLeptonMET && isSecondaryBosonMassIncl && isMEToverHTAbove0p25;
    bool ControlSelection_MergedInvB = isMtAndDPhiLeptonMET && !isNoMoreBJet && isMEToverHTAbove0p25;
    bool ControlSelection_MergedInvMETHT = isMtAndDPhiLeptonMET && isNoMoreBJet && !isMEToverHTAbove0p25;
    bool ControlSelection_ResolvedInvMETHT = isMtAndDPhiLeptonMET && isSecondaryBosonMassIncl && !isMEToverHTAbove0p25;

//    if (invertLeptonIsolation){
//        eventRegions["DataDriven_NonIsolatedMuon-Inclusive"] = passMuonTrigger && hasOneMuon && hasZeroElectron && hasFatjetMassIncl;
/*
        eventRegions["DataDriven_NonIsolatedMuon-Barrel"] = eventRegions["DataDriven_NonIsolatedMuon-Inclusive"] && isBarrelLepton;
        eventRegions["DataDriven_NonIsolatedMuon-Endcap"] = eventRegions["DataDriven_NonIsolatedMuon-Inclusive"] && !isBarrelLepton;

        eventRegions["DataDriven_NonIsolatedMuon-BarrelHighMissingEt"] = eventRegions["DataDriven_NonIsolatedMuon-Barrel"] && hasMissingEtAbove50;
        eventRegions["DataDriven_NonIsolatedMuon-EndcapHighMissingEt"] = eventRegions["DataDriven_NonIsolatedMuon-Endcap"] && hasMissingEtAbove50;
        eventRegions["DataDriven_NonIsolatedMuon-BarrelLowMissingEt"] = eventRegions["DataDriven_NonIsolatedMuon-Barrel"] && !hasMissingEtAbove50;
        eventRegions["DataDriven_NonIsolatedMuon-EndcapLowMissingEt"] = eventRegions["DataDriven_NonIsolatedMuon-Endcap"] && !hasMissingEtAbove50;
*/
//    }

    if (!invertLeptonIsolation){

        eventRegions["Preselection_MuonMergedHighPt"] = Preselection_Muon && Preselection_Merged && isSecondaryBosonPtHigh;
        eventRegions["Preselection_MuonMergedLowPt"] = Preselection_Muon && Preselection_Merged && isSecondaryBosonPtLow;

        eventRegions["Preselection_MuonMergedHighPt"] = Preselection_Muon && Preselection_Merged && SignalSelection_Merged && isSecondaryBosonPtHigh;
        eventRegions["Preselection_MuonMergedLowPt"] = Preselection_Muon && Preselection_Merged && SignalSelection_Merged && isSecondaryBosonPtLow;


        eventRegions["SignalRegion_MuonMergedXbb"] = Preselection_Muon && Preselection_Merged && SignalSelection_Merged && varSecondaryBosonTag.Contains("Xbb");
        eventRegions["SignalRegion_MuonMergedXqq"] = Preselection_Muon && Preselection_Merged && SignalSelection_Merged && varSecondaryBosonTag.Contains("Xqq");
        eventRegions["SignalRegion_MuonResolvedXbb"] = Preselection_Muon && Preselection_Resolved && SignalSelection_Resolved && varSecondaryBosonTag.Contains("Xbb");
        eventRegions["SignalRegion_MuonResolvedXbq"] = Preselection_Muon && Preselection_Resolved && SignalSelection_Resolved && varSecondaryBosonTag.Contains("Xbq");
        eventRegions["SignalRegion_MuonResolvedXqq"] = Preselection_Muon && Preselection_Resolved && SignalSelection_Resolved && varSecondaryBosonTag.Contains("Xqq");

        eventRegions["SignalRegion_ElectronMergedXbb"] = Preselection_Electron && Preselection_Merged && SignalSelection_Merged && varSecondaryBosonTag.Contains("Xbb");
        eventRegions["SignalRegion_ElectronMergedXqq"] = Preselection_Electron && Preselection_Merged && SignalSelection_Merged && varSecondaryBosonTag.Contains("Xqq");
        eventRegions["SignalRegion_ElectronResolvedXbb"] = Preselection_Electron && Preselection_Resolved && SignalSelection_Resolved && varSecondaryBosonTag.Contains("Xbb");
        eventRegions["SignalRegion_ElectronResolvedXbq"] = Preselection_Electron && Preselection_Resolved && SignalSelection_Resolved && varSecondaryBosonTag.Contains("Xbq");
        eventRegions["SignalRegion_ElectronResolvedXqq"] = Preselection_Electron && Preselection_Resolved && SignalSelection_Resolved && varSecondaryBosonTag.Contains("Xqq");

        eventRegions["ControlRegion_MuonMergedInvMTDPhi"] = Preselection_Muon && Preselection_Merged && ControlSelection_MergedInvMTDPhi;
        eventRegions["ControlRegion_MuonMergedInvB"] = Preselection_Muon && Preselection_Merged && ControlSelection_MergedInvB;
        eventRegions["ControlRegion_MuonMergedInvMETHT"] = Preselection_Muon && Preselection_Merged && ControlSelection_MergedInvMETHT;
        eventRegions["ControlRegion_MuonResolvedInvMTDPhi"] = Preselection_Muon && Preselection_Resolved && ControlSelection_ResolvedInvMTDPhi;
        eventRegions["ControlRegion_MuonResolvedInvMETHT"] = Preselection_Muon && Preselection_Resolved && ControlSelection_ResolvedInvMETHT;
        eventRegions["ControlRegion_MuonResolvedTT"] = isMuonTrigger && isOneMuon && isOneElectron && Preselection_Resolved && SignalSelection_Resolved ? (muons.at(0).Pt() > electrons.at(0).Pt()) : false;

        eventRegions["ControlRegion_ElectronMergedInvMTDPhi"] = Preselection_Electron && Preselection_Merged && ControlSelection_MergedInvMTDPhi;
        eventRegions["ControlRegion_ElectronMergedInvB"] = Preselection_Electron && Preselection_Merged && ControlSelection_MergedInvB;
        eventRegions["ControlRegion_ElectronMergedInvMETHT"] = Preselection_Electron && Preselection_Merged && ControlSelection_MergedInvMETHT;
        eventRegions["ControlRegion_ElectronResolvedInvMTDPhi"] = Preselection_Electron && Preselection_Resolved && ControlSelection_ResolvedInvMTDPhi;
        eventRegions["ControlRegion_ElectronResolvedInvMETHT"] = Preselection_Electron && Preselection_Resolved && ControlSelection_ResolvedInvMETHT;
        eventRegions["ControlRegion_ElectronResolvedTT"] = isElectronTrigger && isOneMuon && isOneElectron && Preselection_Resolved && SignalSelection_Resolved ? (muons.at(0).Pt() < electrons.at(0).Pt()) : false;

    }

    if (Preselection_Merged){
        if (varSecondaryBosonTag.Contains("Xbb")){
            if (isSecondaryBosonPtHigh && isSecondaryBosonMassHigh) varSignalRegion = 1;
            else if (isSecondaryBosonPtHigh && isSecondaryBosonMassLow) varSignalRegion = 2;
            else if (isSecondaryBosonPtLow && isSecondaryBosonMassHigh) varSignalRegion = 3;
            else if (isSecondaryBosonPtLow && isSecondaryBosonMassLow) varSignalRegion = 4;
            else varSignalRegion = -1;
        }
        else if (varSecondaryBosonTag.Contains("Xqq")){
            if (isSecondaryBosonPtHigh) varSignalRegion = 5;
            else if (isSecondaryBosonPtLow) varSignalRegion = 6;
            else varSignalRegion = -1;
        }
        else varSignalRegion = -1;
    }
    else if (Preselection_Resolved){
        if (varSecondaryBosonTag.Contains("Xbb")){
            if (isSecondaryBosonMassHigh) varSignalRegion = 7;
            else if (isSecondaryBosonMassLow) varSignalRegion = 8;
            else varSignalRegion = -1;
        }
        else if (varSecondaryBosonTag.Contains("Xbq")) varSignalRegion = 9;
        else if (varSecondaryBosonTag.Contains("Xqq")) varSignalRegion = 10;
        else varSignalRegion = -1;
    }
    else varSignalRegion = -1;

    std::map<TString, bool>::iterator itEventRegions;

    for (itEventRegions = eventRegions.begin(); itEventRegions != eventRegions.end(); ++itEventRegions){

        if (itEventRegions->second){

            TString eventRegion = itEventRegions->first;

            if (eventRegion.Contains("SignalRegion_Muon")){
                FillHist("SignalRegion_MuonCombined_signalregion" + param.Name, varSignalRegion, weight, 12, -1, 11);
                FillHist("SignalRegion_MuonCombined_signalregion" + param.Name, 0, weight, 12, -1, 11);
            }
            if (eventRegion.Contains("SignalRegion_Electron")){
                FillHist("SignalRegion_ElectronCombined_signalregion" + param.Name, varSignalRegion, weight, 12, -1, 11);
                FillHist("SignalRegion_ElectronCombined_signalregion" + param.Name, 0, weight, 12, -1, 11);
            }

            FillHist(eventRegion + "_dphi_leptonmet" + param.Name, varMETandLeptonDeltaPhi, weight, 100, -5., 5.);
            FillHist(eventRegion + "_masst_leptonmet" + param.Name, varMETandLeptonMassT, weight, 5000, 0., 5000.);
            FillHist(eventRegion + "_masst_recopriboson" + param.Name, varPrimaryBosonMass, weight, 5000, 0., 5000.);
            FillHist(eventRegion + "_mass_recosecboson" + param.Name, varSecondaryBosonMass, weight, 5000, 0., 5000.);
            FillHist(eventRegion + "_pt_recosecboson" + param.Name, varSecondaryBosonPt, weight, 5000, 0., 5000.);
            FillHist(eventRegion + "_eta_recosecboson" + param.Name, varSecondaryBosonEta, weight, 100, -5., 5.);

            FillHist(eventRegion + "_eta_lepton" + param.Name, varLeptonEta, weight, 100, -5., 5.);
            FillHist(eventRegion + "_pt_lepton" + param.Name, varLeptonPt, weight, 5000,0., 5000.);

            FillHist(eventRegion + "_n_events_weighted" + param.Name, 0, weight, 1, 0., 1.);
            FillHist(eventRegion + "_n_events_unweighted" + param.Name, 0, 1., 1, 0., 1.);
            FillHist(eventRegion + "_n_jet" + param.Name, varNJet, weight, 5, 0., 5.);
            FillHist(eventRegion + "_n_bjet" + param.Name, varNBJet, weight, 5, 0., 5.);

            FillHist(eventRegion + "_masst_leptonmet_vs_dphi_leptonmet" + param.Name, varMETandLeptonMassT, varMETandLeptonDeltaPhi, weight, 5000, 0., 5000., 100, -5., 5.);
            FillHist(eventRegion + "_masst_leptonmet_vs_dr_leptonmet" + param.Name, varMETandLeptonMassT, varNeutrinoandLeptonDeltaR, weight, 5000, 0., 5000., 100, 0., 5.);

            FillHist(eventRegion + "_met" + param.Name, varMET, weight, 5000,0., 5000.);
            FillHist(eventRegion + "_met_phi" + param.Name, varMETPhi, weight, 100, -5., 5.);
            FillHist(eventRegion + "_met_over_ht" + param.Name, varMEToverHT, weight, 100, 0., 5.);

            if(eventRegion.Contains("Merged")){
                FillHist(eventRegion + "_pnetxbb" + param.Name, GetParticleNetScore(fatjets.at(0), "XbbMD"), weight, 100,  0., 1.);
                FillHist(eventRegion + "_pnetxqq" + param.Name, GetParticleNetScore(fatjets.at(0), "XqqMD"), weight, 100,  0., 1.);
            }
            if(eventRegion.Contains("Resolved")){
                FillHist(eventRegion + "_deltar_jetjet" + param.Name, jets.at(0).DeltaR(jets.at(1)), weight, 50, 0., 5.);
                FillHist(eventRegion + "_eta_jet" + param.Name, jets.at(0).Eta(), weight, 100, -5., 5.);
                FillHist(eventRegion + "_eta_jet" + param.Name, jets.at(1).Eta(), weight, 100, -5., 5.);
                FillHist(eventRegion + "_pt_jet0" + param.Name, jets.at(0).Pt(), weight, 5000, 0., 5000.);
                FillHist(eventRegion + "_pt_jet1" + param.Name, jets.at(1).Pt(), weight, 5000, 0., 5000.);
                FillHist(eventRegion + "_pt_jet" + param.Name, jets.at(0).Pt(), weight, 5000, 0., 5000.);
                FillHist(eventRegion + "_pt_jet" + param.Name, jets.at(1).Pt(), weight, 5000, 0., 5000.);
            }

//            FillHist(eventRegion + "_signal_region", signalRegionBin, weight, 5, 0., 5.);

//            if(hasMergedXbb) FillHist(eventRegion + "_pnetxbb", pNetScoreXbbMD, weight, 100, 0., 1.);
//            if(hasMergedXqq) FillHist(eventRegion + "_pnetxqq", pNetScoreXqqMD, weight, 100, 0., 1.);

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

double singlelepton_analysis::GetBTaggingScore(Jet jet){

    double bTagScore = jet.GetTaggerResult(bTaggingWP.j_Tagger);

    return bTagScore;

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

void singlelepton_analysis::InitializeVariables(void){

    varSecondaryBosonMass = 0.;
    varSecondaryBosonPt = 0.;
    varSecondaryBosonEta = 0.;

    varSecondaryBosonTag = "";

    varPrimaryBosonMass = 0.;

    varLeptonPt = 0.;
    varLeptonEta = 0.;

    varMET = 0.;
    varMETandLeptonDeltaPhi = 0.;
    varMETandLeptonMassT = 0.;
    varNeutrinoandLeptonDeltaR = 0.;
    varHT = 0.;
    varMEToverHT = 0.;
    varMETPhi = 0.;
    varNJet = 0;
    varNBJet = 0;

    varSignalRegion =0;

    return;

}
