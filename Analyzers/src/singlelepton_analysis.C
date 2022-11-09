#include "singlelepton_analysis.h"

singlelepton_analysis::singlelepton_analysis(){


}

void singlelepton_analysis::initializeAnalyzer(){

    if (HasFlag("syst") && !IsDATA)  runSystematics = true;
    else runSystematics = false;
    if (HasFlag("hem")) runWithHEM = true;
    else runWithHEM = false;
    if (HasFlag("toppt")) runWithoutTopPtRwgt = true;
    else runWithoutTopPtRwgt = false;
    if (HasFlag("systpropmet")) runSystPropMET = true;
    else runSystPropMET = false;

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

    bTaggingWP = JetTagging::Parameters(JetTagging::DeepJet, JetTagging::Medium, JetTagging::incl, JetTagging::comb); // 1a
//    bTaggingWP = JetTagging::Parameters(JetTagging::DeepJet, JetTagging::Medium, JetTagging::iterativefit, JetTagging::iterativefit); // check what JS did and muonisosf idsf not working properly
    mcCorr->SetJetTaggingParameters({bTaggingWP});

    pNetXbbMD = JetTagging::particleNetMD_Xbb;
    pNetXccMD = JetTagging::particleNetMD_Xcc;
    pNetXqqMD = JetTagging::particleNetMD_Xqq;
    pNetQCDMD = JetTagging::particleNetMD_QCD;

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
    if (runSystematics){
        for (unsigned int i=0; i<AnalyzerParameter::NSyst; i++){
            param.syst_ = AnalyzerParameter::Syst(i);
            param.Name = "SYST_" + param.GetSystType();
            executeEventFromParameter(param);
        }
    }
    if (runWithHEM){
        param.Name = "WithHEM";
        executeEventFromParameter(param);
    }
    if (runWithoutTopPtRwgt){
        param.Name = "WithoutTopPtRwgt";
        executeEventFromParameter(param);
    }
    if (runSystPropMET){
        param.Name = "WithMuonEnUpSystWithMET";
        executeEventFromParameter(param);
        param.Name = "WithMuonEnDownSystWithMET";
        executeEventFromParameter(param);
        param.Name = "WithElectronEnUpSystWithMET";
        executeEventFromParameter(param);
        param.Name = "WithElectronEnDownSystWithMET";
        executeEventFromParameter(param);
    }

}

void singlelepton_analysis::executeEventFromParameter(AnalyzerParameter param){

    double weight = 1., weight_cutflow = 1.;
    if(!IsDATA){
        weight = MCweight(true, true);
        weight_cutflow = weight;
    }

    FillHist(param.Name + "/cutflow__preselction__no_cut", 0, weight, 1, 0., 1.);
    if(!PassMETFilter()) return;
    FillHist(param.Name + "/cutflow__preselction__met_filter", 0, weight, 1, 0., 1.);
    Event event = GetEvent();

    if (!(event.PassTrigger(muonTriggers) || event.PassTrigger(electronTriggers))) return;
    FillHist(param.Name + "/cutflow__preselction__pass_trigger", 0, weight, 1, 0., 1.);
    int syst_MuRecoSF = 0;
    int syst_MuIDSF = 0;
    int syst_MuIsoSF = 0;
    int syst_MuTrigSF = 0;
    int syst_ElRecoSF = 0;
    int syst_ElIDSF = 0;
    int syst_ElTrigSF = 0;
    int syst_PileUp = 0;
    int syst_Prefire = 0;
    TString syst_BTag = "central";
    TString syst_TopPt = "weighted";
    // define missing et
    Particle missingEt = event.GetMETVector();

    std::vector<Jet> allJets = centralAllJets;
    std::vector<FatJet> allFatJets = centralAllFatJets;
    std::vector<Muon> allMuons = centralAllMuons;
    std::vector<Electron> allElectrons = centralAllElectrons;

    if (WrongMissingEt()) return;

    bool RunSignalSyst = false;
    if(param.syst_ == AnalyzerParameter::Central){
        if (MCSample.Contains("TypeI")){
            RunSignalSyst = true;
            double signal_weight = MCweight(true, true);
            TString signal_region = "NoCut";
            FillHist("SYST_Signal/DEN_" +signal_region + "_Nominal", 0, signal_weight, 1, 0., 1.);
            for (unsigned int i=0; i<weight_Scale->size(); i++){
                FillHist("SYST_Signal/DEN_" +signal_region + "_Scale" + TString::Itoa(i,10), 0, weight_Scale->at(i)*signal_weight, 1, 0., 1.);
            }
            for (unsigned int i=0; i<weight_PDF->size(); i++){
                FillHist("SYST_Signal/DEN_" + signal_region + "_Error" + TString::Itoa(i,10), 0, weight_PDF->at(i)*signal_weight, 1, 0., 1.);
            }
            for (unsigned int i=0; i<weight_AlphaS->size(); i++){
                FillHist("SYST_Signal/DEN_" + signal_region + "_AlphaS" + TString::Itoa(i,10), 0, weight_AlphaS->at(i)*signal_weight, 1, 0., 1.);
            }
        }
        if(param.Name == "WithElectronEnUpSystWithMET"){
            std::vector<Electron> unscaled = allElectrons;
            allElectrons = ScaleElectrons(allElectrons, +1);
            std::vector<Electron> scaled = allElectrons;
            missingEt = ScaleLeptonMissingEtPropagation(missingEt, unscaled, scaled);
        }
        else if(param.Name == "WithElectronEnDownSystWithMET"){
            std::vector<Electron> unscaled = allElectrons;
            allElectrons = ScaleElectrons(allElectrons, -1);
            std::vector<Electron> scaled = allElectrons;
            missingEt = ScaleLeptonMissingEtPropagation(missingEt, unscaled, scaled);
        }
        else if(param.Name == "WithMuonEnUpSystWithMET"){
            std::vector<Muon> unscaled = allMuons;
            allMuons = ScaleMuons(allMuons, +1);
            std::vector<Muon> scaled = allMuons;
            missingEt = ScaleLeptonMissingEtPropagation(missingEt, unscaled, scaled);
        }
        else if(param.Name == "WithMuonEnDownSystWithMET"){
            std::vector<Muon> unscaled = allMuons;
            allMuons = ScaleMuons(allMuons, -1);
            std::vector<Muon> scaled = allMuons;
            missingEt = ScaleLeptonMissingEtPropagation(missingEt, unscaled, scaled);
        }

    }
    else if(param.syst_ == AnalyzerParameter::JetResUp){
        allJets = SmearJets( allJets, +1 );
        allFatJets = SmearFatJets( allFatJets, +1 );
        missingEt.SetPtEtaPhiM(PuppiMET_Type1_pt_shifts->at(0), 0., PuppiMET_Type1_phi_shifts->at(0), 0.);
    }
    else if(param.syst_ == AnalyzerParameter::JetResDown){
        allJets = SmearJets( allJets, -1 );
        allFatJets = SmearFatJets( allFatJets, -1 );
        missingEt.SetPtEtaPhiM(PuppiMET_Type1_pt_shifts->at(1), 0., PuppiMET_Type1_phi_shifts->at(1), 0.);
    }
    else if(param.syst_ == AnalyzerParameter::JetEnUp){
        allJets = ScaleJets( allJets, +1 );
        allFatJets = ScaleFatJets( allFatJets, +1 );
        missingEt.SetPtEtaPhiM(PuppiMET_Type1_pt_shifts->at(2), 0., PuppiMET_Type1_phi_shifts->at(2), 0.);
    }
    else if(param.syst_ == AnalyzerParameter::JetEnDown){
        allJets = ScaleJets( allJets, -1 );
        allFatJets = ScaleFatJets( allFatJets, -1 );
        missingEt.SetPtEtaPhiM(PuppiMET_Type1_pt_shifts->at(3), 0., PuppiMET_Type1_phi_shifts->at(3), 0.);
    }
    else if(param.syst_ == AnalyzerParameter::JetMassScaleUp){
        allFatJets = ScaleSDMassFatJets( allFatJets, +1 );
    }
    else if(param.syst_ == AnalyzerParameter::JetMassScaleDown){
        allFatJets = ScaleSDMassFatJets( allFatJets, -1 );
    }
    else if(param.syst_ == AnalyzerParameter::JetMassResUp){
        allFatJets = SmearSDMassFatJets( allFatJets, +1 );
    }
    else if(param.syst_ == AnalyzerParameter::JetMassResDown){
        allFatJets = SmearSDMassFatJets( allFatJets, -1 );
    }
    else if(param.syst_ == AnalyzerParameter::UnclEnUp){
        missingEt.SetPtEtaPhiM(PuppiMET_Type1_pt_shifts->at(10), 0., PuppiMET_Type1_phi_shifts->at(10), 0.);
    }
    else if(param.syst_ == AnalyzerParameter::UnclEnDown){
        missingEt.SetPtEtaPhiM(PuppiMET_Type1_pt_shifts->at(11), 0., PuppiMET_Type1_phi_shifts->at(11), 0.);
    }
    else if(param.syst_ == AnalyzerParameter::MuonEnUp){

        std::vector<Muon> unscaled = allMuons;
        allMuons = ScaleMuons(allMuons, +1);
        std::vector<Muon> scaled = allMuons;
//        missingEt = ScaleLeptonMissingEtPropagation(missingEt, unscaled, scaled);

    }
    else if(param.syst_ == AnalyzerParameter::MuonEnDown){

        std::vector<Muon> unscaled = allMuons;
        allMuons = ScaleMuons(allMuons, -1);
        std::vector<Muon> scaled = allMuons;
//        missingEt = ScaleLeptonMissingEtPropagation(missingEt, unscaled, scaled);

    }
    else if(param.syst_ == AnalyzerParameter::ElectronResUp){
        allElectrons = SmearElectrons( allElectrons, +1 );
    }
    else if(param.syst_ == AnalyzerParameter::ElectronResDown){
        allElectrons = SmearElectrons( allElectrons, -1 );
    }
    else if(param.syst_ == AnalyzerParameter::ElectronEnUp){

        std::vector<Electron> unscaled = allElectrons;
        allElectrons = ScaleElectrons(allElectrons, +1);
        std::vector<Electron> scaled = allElectrons;
//        missingEt = ScaleLeptonMissingEtPropagation(missingEt, unscaled, scaled);
        
    }
    else if(param.syst_ == AnalyzerParameter::ElectronEnDown){

        std::vector<Electron> unscaled = allElectrons;
        allElectrons = ScaleElectrons(allElectrons, -1);
        std::vector<Electron> scaled = allElectrons;
//        missingEt = ScaleLeptonMissingEtPropagation(missingEt, unscaled, scaled);

    }
    else if(param.syst_ == AnalyzerParameter::MuonRecoSFUp){
        syst_MuRecoSF = +1;
    }
    else if(param.syst_ == AnalyzerParameter::MuonRecoSFDown){
        syst_MuRecoSF = -1;
    }
    else if(param.syst_ == AnalyzerParameter::MuonIDSFUp){
        syst_MuIDSF = +1;
    }
    else if(param.syst_ == AnalyzerParameter::MuonIDSFDown){
        syst_MuIDSF = -1;
    }
    else if(param.syst_ == AnalyzerParameter::MuonISOSFUp){
        syst_MuIsoSF = +1;
    }
    else if(param.syst_ == AnalyzerParameter::MuonISOSFDown){
        syst_MuIsoSF = -1;
    }
    else if(param.syst_ == AnalyzerParameter::MuonTriggerSFUp){
        syst_MuTrigSF = +1;
    }
    else if(param.syst_ == AnalyzerParameter::MuonTriggerSFDown){
        syst_MuTrigSF = -1;
    }
    else if(param.syst_ == AnalyzerParameter::ElectronRecoSFUp){
        syst_ElRecoSF = +1;
    }
    else if(param.syst_ == AnalyzerParameter::ElectronRecoSFDown){
        syst_ElRecoSF = -1;
    }
    else if(param.syst_ == AnalyzerParameter::ElectronIDSFUp){
        syst_ElIDSF = +1;
    }
    else if(param.syst_ == AnalyzerParameter::ElectronIDSFDown){
        syst_ElIDSF = -1;
    }
    else if(param.syst_ == AnalyzerParameter::ElectronTriggerSFUp){
        syst_ElTrigSF = +1;
    }// TODO
    else if(param.syst_ == AnalyzerParameter::ElectronTriggerSFDown){
        syst_ElTrigSF = -1;
    }// TODO
    else if(param.syst_ == AnalyzerParameter::PileupUp){
        syst_PileUp = +1;
    }
    else if(param.syst_ == AnalyzerParameter::PileupDown){
        syst_PileUp = -1;
    }
    else if(param.syst_ == AnalyzerParameter::PrefireUp){
        syst_Prefire = +1;
    }
    else if(param.syst_ == AnalyzerParameter::PrefireDown){
        syst_Prefire = -1;
    }
    else if(param.syst_ == AnalyzerParameter::BTagCorrHUp){
        syst_BTag = "SystUpCorrHTag";
    }
    else if(param.syst_ == AnalyzerParameter::BTagCorrHDown){
        syst_BTag = "SystDownCorrHTag";
    }
    else if(param.syst_ == AnalyzerParameter::BTagCorrLUp){
        syst_BTag = "SystUpCorrLTag";
    }
    else if(param.syst_ == AnalyzerParameter::BTagCorrLDown){
        syst_BTag = "SystDownCorrLTag";
    }
    else if(param.syst_ == AnalyzerParameter::BTagUnCorrHUp){
        syst_BTag = "SystUpUnCorrHTag";
    }
    else if(param.syst_ == AnalyzerParameter::BTagUnCorrHDown){
        syst_BTag = "SystDownUnCorrHTag";
    }
    else if(param.syst_ == AnalyzerParameter::BTagUnCorrLUp){
        syst_BTag = "SystUpUnCorrLTag";
    }
    else if(param.syst_ == AnalyzerParameter::BTagUnCorrLDown){
        syst_BTag = "SystDownUnCorrLTag";
    }
    else if(param.syst_ == AnalyzerParameter::TopPtReweightUp){
        syst_TopPt = "unweighted";
    }
    else if(param.syst_ == AnalyzerParameter::TopPtReweightDown){
        syst_TopPt = "weighted";
    }
    else{
        std::cout << "[ERROR] Parameter not found" << std::endl;
        return;
        // particlenet
    }// TODO
    InitializeVariables();
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
    std::vector<Electron> electronsLoose = SelectElectrons(allElectrons, param.Electron_Loose_ID, leptonPtCut, 2.5, !(param.Name == "WithHEM"));
    std::vector<Electron> electrons = SelectElectrons(electronsLoose, param.Electron_Tight_ID, leptonPtCut, 2.1, !(param.Name == "WithHEM"));
    std::sort(electrons.begin(), electrons.end(), PtComparing);

    // trigger settings
    bool isMuonTrigger = (event.PassTrigger(muonTriggers) && muons.size()>= 1) ? muons.at(0).Pt() > muonPtCut : false;
    bool isElectronTrigger = (event.PassTrigger(electronTriggers) && electrons.size() >= 1) ? electrons.at(0).Pt() > electronPtCut : false;
    if (!(isMuonTrigger || isElectronTrigger)) return;
    FillHist(param.Name + "/cutflow__preselction__lepton", 0, weight, 1, 0., 1.);
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

    std::vector<Lepton> leptons; leptons.clear();
    for (unsigned int i=0; i < muons.size(); i++){
        leptons.push_back(muons.at(i));
    }
    for (unsigned int i=0; i < electrons.size(); i++){
        leptons.push_back(electrons.at(i));
    }
    std::sort(leptons.begin(), leptons.end(), PtComparing);

    double top_pt_weight = 1.;
    if (!IsDATA){
        weight = weight * GetPrefireWeight(syst_Prefire);
        weight = weight * GetPileUpWeight(nPileUp, syst_PileUp); 
        weight = weight * event.GetTriggerLumi("Full");
        weight = weight * mcCorr->GetBTaggingReweight_1a(jets, bTaggingWP, string(syst_BTag));
        for (unsigned int i=0; i < electrons.size(); i++){
            weight = weight * mcCorr->ElectronReco_SF(electrons.at(i).scEta(), electrons.at(i).UncorrPt(), syst_ElRecoSF);
            weight = weight * mcCorr->ElectronID_SF(param.Electron_ID_SF_Key, electrons.at(i).scEta(), electrons.at(i).Pt(), syst_ElIDSF);
            // FIXME no trigger SF
        }
        for (unsigned int i=0; i < muons.size(); i++){
            double muonMiniAODpT = muons.at(i).MiniAODPt() > 120. ? 119.9 :muons.at(i).MiniAODPt();
            weight = weight * mcCorr->MuonID_SF(param.Muon_ID_SF_Key, muons.at(i).Eta(), muonMiniAODpT, syst_MuIDSF);
            weight = weight * mcCorr->MuonISO_SF(param.Muon_ISO_SF_Key, muons.at(i).Eta(), muonMiniAODpT, syst_MuIsoSF);
        }
        weight = weight * mcCorr->MuonTrigger_SF(param.Muon_Tight_ID, param.Muon_Trigger_SF_Key, muons, syst_MuTrigSF);
        if(MCSample.Contains("TT") && MCSample.Contains("powheg")){
            if (!(param.Name == "WithoutTopPtRwgt")){
                std::vector<Gen> gens = GetGens();
                top_pt_weight = mcCorr->GetTopPtReweight(gens, syst_TopPt);
                weight = weight * top_pt_weight;
            }
        }
    }
    bool isOneMuon = (muons.size() == 1) && (muonsLoose.size() == 1);
    bool isOneElectron = (electrons.size() == 1) && (electronsLoose.size() == 1);
    bool isZeroMuon = (muonsLoose.size() == 0);
    bool isZeroElectron = (electronsLoose.size() == 0);
    bool isMergedRegion = (fatjets.size() >= 1);
    bool isResolvedRegion = !isMergedRegion && (jets.size() >= 2);

    Particle neutrino = GetReconstructedNeutrino(leptons.at(0), missingEt);

    varLeptonPt = leptons.at(0).Pt();
    varLeptonEta = leptons.at(0).Eta();
    varLeptonPhi = leptons.at(0).Phi();
    varMET = missingEt.Pt();
    varMETPhi = missingEt.Phi();
    varMETandLeptonDeltaPhi = fabs(missingEt.DeltaPhi(leptons.at(0)));
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
        varTopKillerMass = (leptons.at(0) + fatjets.at(0)).M();
        varResonanceMass1 = (leptons.at(0) + fatjets.at(0)).M();
        varResonanceMass2 = (fatjets.at(0) + missingEt).Mt();
        varResonanceMinMass = min(varResonanceMass1, varResonanceMass2);
        varResonanceMaxMass = max(varResonanceMass1, varResonanceMass2);
        varSecondaryBosonEta = fatjets.at(0).Eta();

        if (GetParticleNetScore(fatjets.at(0), "XbbMD") > 0.94) varSecondaryBosonTag = "MergedXbb";
        else if (GetParticleNetScore(fatjets.at(0), "XqqMD") > 0.82) varSecondaryBosonTag = "MergedXqq";
        else varSecondaryBosonTag = "MergedXxx";

    }
    else if (isResolvedRegion){

        varSecondaryBosonMass = (jets.at(0) + jets.at(1)).M();
        varSecondaryBosonPt = (jets.at(0) + jets.at(1)).Pt();
        varPrimaryBosonMass = (leptons.at(0) + jets.at(0) + jets.at(1) + missingEt).Mt();
        varTopKillerMass = min((leptons.at(0) + jets.at(0)).M(), (leptons.at(0) + jets.at(1)).M());
        varResonanceMass1 = (leptons.at(0) + jets.at(0) + jets.at(1)).M();
        varResonanceMass2 = (missingEt + jets.at(0) + jets.at(1)).Mt();
        varResonanceMinMass = min(varResonanceMass1, varResonanceMass2);
        varResonanceMaxMass = max(varResonanceMass1, varResonanceMass2);
        varSecondaryBosonEta = (jets.at(0) + jets.at(1)).Eta();

        if (((GetBTaggingScore(jets.at(0)) > bTaggingWPCutValue) + (GetBTaggingScore(jets.at(1)) > bTaggingWPCutValue)) == 2) varSecondaryBosonTag = "ResolvedXbb";
        else if (((GetBTaggingScore(jets.at(0)) > bTaggingWPCutValue) + (GetBTaggingScore(jets.at(1)) > bTaggingWPCutValue)) == 1) varSecondaryBosonTag = "ResolvedXbq";
        else if (((GetBTaggingScore(jets.at(0)) > bTaggingWPCutValue) + (GetBTaggingScore(jets.at(1)) > bTaggingWPCutValue)) == 0) varSecondaryBosonTag = "ResolvedXqq";
        else varSecondaryBosonTag = "ResolvedXxx";

    }
    else{

        return;

    }
    FillHist(param.Name + "/cutflow__preselction__jets", 0, weight, 1, 0., 1.);

    std::map<TString, bool> eventRegions;

    bool isBarrelLepton = (std::fabs(varLeptonEta) < 0.9);
    bool isLeptonPtAbove100 = (varLeptonPt > 100.0);

    bool isEffectiveMassAbove500 = (varPrimaryBosonMass > 500.0);

    bool isSecondaryBosonMassIncl = (varSecondaryBosonMass >= 65.0) && (varSecondaryBosonMass < 145.0);
    bool isSecondaryBosonPtIncl = (varSecondaryBosonPt >= 100.0);

    bool isZeroBJet = (varNBJet == 0);
    bool isMETAbove100 = (varMET > 100.0);
    bool isMtLeptonMETAbove250 = (varMETandLeptonMassT > 250.0);
    bool isDPhiLeptonMETAbove0p4Pi = (fabs(varMETandLeptonDeltaPhi) > 0.4 * TMath::Pi());
    bool isMtAndDPhiLeptonMET = isMtLeptonMETAbove250 && isDPhiLeptonMETAbove0p4Pi;

    // define how leptons are selected
    bool Preselection_Muon = isMuonTrigger && isOneMuon && isZeroElectron;
    bool Preselection_Electron = isElectronTrigger && isOneElectron && isZeroMuon;

    // define how to ensure the searche range for mN
    bool Preselection = isEffectiveMassAbove500 && isMETAbove100 && isSecondaryBosonPtIncl;
    bool Preselection_Merged = Preselection && isMergedRegion;
    bool Preselection_Resolved = Preselection && isResolvedRegion;

    bool SignalSelection_Merged = isSecondaryBosonMassIncl && isMtAndDPhiLeptonMET && isZeroBJet;
    bool SignalSelection_Resolved = isSecondaryBosonMassIncl && isMtAndDPhiLeptonMET;

    bool ControlSelection_MergedInvMTDPhi = isSecondaryBosonMassIncl && !isMtAndDPhiLeptonMET && isZeroBJet;
    bool ControlSelection_ResolvedInvMTDPhi = isSecondaryBosonMassIncl && !isMtAndDPhiLeptonMET;
    bool ControlSelection_MergedDomW = !isSecondaryBosonMassIncl && isZeroBJet; // W dedicated
    bool ControlSelection_ResolvedDomW = !isSecondaryBosonMassIncl && isZeroBJet; // W dedicated
    bool ControlSelection_MergedDomTT = isSecondaryBosonMassIncl && !isZeroBJet; // TT dedicated
    bool ControlSelection_ResolvedDomTT = !isSecondaryBosonMassIncl && !isZeroBJet; // TT dedicated

    eventRegions["Preselection_MuonMerged"] = Preselection_Muon && Preselection_Merged;
    eventRegions["Preselection_MuonResolved"] = Preselection_Muon && Preselection_Resolved;
    eventRegions["Preselection_ElectronMerged"] = Preselection_Electron && Preselection_Merged;
    eventRegions["Preselection_ElectronResolved"] = Preselection_Electron && Preselection_Resolved;

    eventRegions["SignalRegion_MuonMergedInclusive"] = Preselection_Muon && Preselection_Merged && SignalSelection_Merged;
    eventRegions["SignalRegion_MuonResolvedInclusive"] = Preselection_Muon && Preselection_Resolved && SignalSelection_Resolved;
    eventRegions["SignalRegion_ElectronMergedInclusive"] = Preselection_Electron && Preselection_Merged && SignalSelection_Merged;
    eventRegions["SignalRegion_ElectronResolvedInclusive"] = Preselection_Electron && Preselection_Resolved && SignalSelection_Resolved;

    eventRegions["SignalRegion_MuonMergedXbbSelection"] = Preselection_Muon && Preselection_Merged && SignalSelection_Merged && varSecondaryBosonTag.Contains("Xbb");
    eventRegions["SignalRegion_MuonMergedXqqSelection"] = Preselection_Muon && Preselection_Merged && SignalSelection_Merged && varSecondaryBosonTag.Contains("Xqq");
    eventRegions["SignalRegion_MuonResolvedXbbSelection"] = Preselection_Muon && Preselection_Resolved && SignalSelection_Resolved && varSecondaryBosonTag.Contains("Xbb");
    eventRegions["SignalRegion_MuonResolvedXbqSelection"] = Preselection_Muon && Preselection_Resolved && SignalSelection_Resolved && varSecondaryBosonTag.Contains("Xbq");
    eventRegions["SignalRegion_MuonResolvedXqqSelection"] = Preselection_Muon && Preselection_Resolved && SignalSelection_Resolved && varSecondaryBosonTag.Contains("Xqq");

    eventRegions["ControlRegion_MuonMergedXbbInvMTDPhiSelection"] = Preselection_Muon && Preselection_Merged && ControlSelection_MergedInvMTDPhi && varSecondaryBosonTag.Contains("Xbb");
    eventRegions["ControlRegion_MuonMergedXqqInvMTDPhiSelection"] = Preselection_Muon && Preselection_Merged && ControlSelection_MergedInvMTDPhi && varSecondaryBosonTag.Contains("Xqq");
    eventRegions["ControlRegion_MuonMergedDomWSelection"] = Preselection_Muon && Preselection_Merged && ControlSelection_MergedDomW;
    eventRegions["ControlRegion_MuonMergedDomTTSelection"] = Preselection_Muon && Preselection_Merged && ControlSelection_MergedDomTT;

    eventRegions["ControlRegion_MuonResolvedXbbInvMTDPhiSelection"] = Preselection_Muon && Preselection_Resolved && ControlSelection_ResolvedInvMTDPhi && varSecondaryBosonTag.Contains("Xbb");
    eventRegions["ControlRegion_MuonResolvedXbqInvMTDPhiSelection"] = Preselection_Muon && Preselection_Resolved && ControlSelection_ResolvedInvMTDPhi && varSecondaryBosonTag.Contains("Xbq");
    eventRegions["ControlRegion_MuonResolvedXqqInvMTDPhiSelection"] = Preselection_Muon && Preselection_Resolved && ControlSelection_ResolvedInvMTDPhi && varSecondaryBosonTag.Contains("Xqq");
    eventRegions["ControlRegion_MuonResolvedDomWSelection"] = Preselection_Muon && Preselection_Resolved && ControlSelection_ResolvedDomW;
    eventRegions["ControlRegion_MuonResolvedDomTTSelection"] = Preselection_Muon && Preselection_Resolved && ControlSelection_ResolvedDomTT;

    eventRegions["SignalRegion_ElectronMergedXbbSelection"] = Preselection_Electron && Preselection_Merged && SignalSelection_Merged && varSecondaryBosonTag.Contains("Xbb");
    eventRegions["SignalRegion_ElectronMergedXqqSelection"] = Preselection_Electron && Preselection_Merged && SignalSelection_Merged && varSecondaryBosonTag.Contains("Xqq");
    eventRegions["SignalRegion_ElectronResolvedXbbSelection"] = Preselection_Electron && Preselection_Resolved && SignalSelection_Resolved && varSecondaryBosonTag.Contains("Xbb");
    eventRegions["SignalRegion_ElectronResolvedXbqSelection"] = Preselection_Electron && Preselection_Resolved && SignalSelection_Resolved && varSecondaryBosonTag.Contains("Xbq");
    eventRegions["SignalRegion_ElectronResolvedXqqSelection"] = Preselection_Electron && Preselection_Resolved && SignalSelection_Resolved && varSecondaryBosonTag.Contains("Xqq");

    eventRegions["ControlRegion_ElectronMergedXbbInvMTDPhiSelection"] = Preselection_Electron && Preselection_Merged && ControlSelection_MergedInvMTDPhi && varSecondaryBosonTag.Contains("Xbb");
    eventRegions["ControlRegion_ElectronMergedXqqInvMTDPhiSelection"] = Preselection_Electron && Preselection_Merged && ControlSelection_MergedInvMTDPhi && varSecondaryBosonTag.Contains("Xqq");
    eventRegions["ControlRegion_ElectronMergedDomWSelection"] = Preselection_Electron && Preselection_Merged && ControlSelection_MergedDomW;
    eventRegions["ControlRegion_ElectronMergedDomTTSelection"] = Preselection_Electron && Preselection_Merged && ControlSelection_MergedDomTT;

    eventRegions["ControlRegion_ElectronResolvedXbbInvMTDPhiSelection"] = Preselection_Electron && Preselection_Resolved && ControlSelection_ResolvedInvMTDPhi && varSecondaryBosonTag.Contains("Xbb");
    eventRegions["ControlRegion_ElectronResolvedXbqInvMTDPhiSelection"] = Preselection_Electron && Preselection_Resolved && ControlSelection_ResolvedInvMTDPhi && varSecondaryBosonTag.Contains("Xbq");
    eventRegions["ControlRegion_ElectronResolvedXqqInvMTDPhiSelection"] = Preselection_Electron && Preselection_Resolved && ControlSelection_ResolvedInvMTDPhi && varSecondaryBosonTag.Contains("Xqq");
    eventRegions["ControlRegion_ElectronResolvedDomWSelection"] = Preselection_Electron && Preselection_Resolved && ControlSelection_ResolvedDomW;
    eventRegions["ControlRegion_ElectronResolvedDomTTSelection"] = Preselection_Electron && Preselection_Resolved && ControlSelection_ResolvedDomTT;

    double bins_varPrimaryBosonMass_Merged[5] = {500., 600., 750., 900., 1300.};
    double bins_varPrimaryBosonMass_Resolved[4] = {500., 600., 750., 1300.};
    double bins_varMETandLeptonMassT[6] = {0., 250., 300., 350., 400., 850.};
    double bins_varSecondaryBosonMass[7] = {0., 50., 65., 105., 145., 200., 450.};
    double bins_varMETandLeptonDeltaPhi[7] = {0., 0.2, 0.5, 0.25*TMath::Pi(), 0.40*TMath::Pi(), 0.70*TMath::Pi(), TMath::Pi()};
    double bins_varMET[5] = {100., 150., 200., 250., 650.};
    double bins_varLeptonPt[5] = {50., 100., 150., 200., 650.};
    double bins_varNJet[6] = {0., 1., 2., 3., 4., 5.};
    double bins_varNBJet[6] = {0., 1., 2., 3., 4., 5.};

    if (RunSignalSyst){
        double signal_weight = MCweight(true, true);
        TString signal_region = "NONE";
        if (eventRegions["SignalRegion_MuonMerged"] || eventRegions["SignalRegion_ElectronMerged"]) signal_region = "Merged";
        if (eventRegions["SignalRegion_MuonResolved"] || eventRegions["SignalRegion_ElectronResolved"]) signal_region = "Resolved";
        if (eventRegions["SignalRegion_MuonMerged"] || eventRegions["SignalRegion_MuonResolved"]) signal_region = "Muon" + signal_region;
        if (eventRegions["SignalRegion_ElectronMerged"] || eventRegions["SignalRegion_ElectronResolved"]) signal_region = "Electron" + signal_region;

        if (signal_region != "NONE"){
            FillHist("SYST_Signal/NUM_" +signal_region + "_Nominal", 0, signal_weight, 1, 0., 1.);
            for (unsigned int i=0; i<weight_Scale->size(); i++){
                FillHist("SYST_Signal/NUM_" +signal_region + "_Scale" + TString::Itoa(i,10), 0, weight_Scale->at(i)*signal_weight, 1, 0., 1.);
            }
            for (unsigned int i=0; i<weight_PDF->size(); i++){
                FillHist("SYST_Signal/NUM_" + signal_region + "_Error" + TString::Itoa(i,10), 0, weight_PDF->at(i)*signal_weight, 1, 0., 1.);
            }
            for (unsigned int i=0; i<weight_AlphaS->size(); i++){
                FillHist("SYST_Signal/NUM_" + signal_region + "_AlphaS" + TString::Itoa(i,10), 0, weight_AlphaS->at(i)*signal_weight, 1, 0., 1.);
            }  
        }
    }

    std::map<TString, bool>::iterator itEventRegions;

    for (itEventRegions = eventRegions.begin(); itEventRegions != eventRegions.end(); ++itEventRegions){

        if (itEventRegions->second){

            TString eventRegion = itEventRegions->first;
            varSignalRegion = GetSignalRegion(eventRegion, varSecondaryBosonPt, varSecondaryBosonMass);

            if (runWithHEM && eventRegion.Contains("Signal")) continue;
            if (runWithoutTopPtRwgt && eventRegion.Contains("Signal")) continue;

            if (eventRegion.Contains("Merged")){
                FillBinnedHist(param.Name + "/" + eventRegion + "_masst_recopriboson", varPrimaryBosonMass, weight, 4, bins_varPrimaryBosonMass_Merged);
            }
            if (eventRegion.Contains("Resolved")){
                FillBinnedHist(param.Name + "/" + eventRegion + "_masst_recopriboson", varPrimaryBosonMass, weight, 3, bins_varPrimaryBosonMass_Resolved);
            }
            FillBinnedHist(param.Name + "/" + eventRegion + "_masst_leptonmet", varMETandLeptonMassT, weight, 5, bins_varMETandLeptonMassT);
            FillHist(param.Name + "/" + eventRegion + "_masst_leptonmet_binned", varMETandLeptonMassT, weight, 1000, 0., 1000.);

            FillBinnedHist(param.Name + "/" + eventRegion + "_mass_recosecboson", varSecondaryBosonMass, weight, 6, bins_varSecondaryBosonMass);
            FillBinnedHist(param.Name + "/" + eventRegion + "_dphi_leptonmet", fabs(varMETandLeptonDeltaPhi), weight, 6, bins_varMETandLeptonDeltaPhi);
            FillHist(param.Name + "/" + eventRegion + "_dphi_leptonmet_binned", fabs(varMETandLeptonDeltaPhi), weight, 50, 0., 5.);

            FillBinnedHist(param.Name + "/" + eventRegion + "_met", varMET, weight, 4, bins_varMET);
            FillBinnedHist(param.Name + "/" + eventRegion + "_pt_lepton", varLeptonPt, weight, 4, bins_varLeptonPt);
            FillBinnedHist(param.Name + "/" + eventRegion + "_n_jet", varNJet, weight, 5, bins_varNJet);
            FillBinnedHist(param.Name + "/" + eventRegion + "_n_bjet", varNBJet, weight, 5, bins_varNBJet);

            FillHist(param.Name + "/" + eventRegion + "_pt_recosecboson", varSecondaryBosonPt, weight, 5000, 0., 5000.);
            FillHist(param.Name + "/" + eventRegion + "_n_events_weighted", 0, weight, 1, 0., 1.);
            FillHist(param.Name + "/" + eventRegion + "_n_events_unweighted", 0, 1., 1, 0., 1.);
            FillHist(param.Name + "/" + eventRegion + "_masst_leptonmet_vs_dphi_leptonmet", varMETandLeptonMassT, fabs(varMETandLeptonDeltaPhi), weight, 5000, 0., 1000., 20, 0., 5.);

            FillHist(param.Name + "/" + eventRegion + "_phi_met", varMETPhi, weight, 100, -5., 5.);

            if (runWithHEM || param.Name == "CENTRAL"){
                FillHist(param.Name + "/" + eventRegion + "CheckHEM_eta_lepton", varLeptonEta, weight, 20, -2.5, 2.5);
                FillHist(param.Name + "/" + eventRegion + "CheckHEM_phi_lepton", varLeptonPhi, weight, 40, -5.0, 5.0);
                if (varLeptonEta < 0){
                    FillHist(param.Name + "/" + eventRegion + "CheckEta1HEM_eta_lepton", varLeptonEta, weight, 20, -2.5, 2.5);
                    FillHist(param.Name + "/" + eventRegion + "CheckEta1HEM_phi_lepton", varLeptonPhi, weight, 40, -5.0, 5.0);
                }
                else{
                    FillHist(param.Name + "/" + eventRegion + "CheckEta2HEM_eta_lepton", varLeptonEta, weight, 20, -2.5, 2.5);
                    FillHist(param.Name + "/" + eventRegion + "CheckEta2HEM_phi_lepton", varLeptonPhi, weight, 40, -5.0, 5.0);
                }
                if (varLeptonPhi < TMath::Pi() && TMath::Pi()/2. < varLeptonPhi){
                    FillHist(param.Name + "/" + eventRegion + "CheckPhi1HEM_eta_lepton", varLeptonEta, weight, 20, -2.5, 2.5);
                    FillHist(param.Name + "/" + eventRegion + "CheckPhi1HEM_phi_lepton", varLeptonPhi, weight, 40, -5.0, 5.0);
                }
                else if (varLeptonPhi <= TMath::Pi()/2. && 0. < varLeptonPhi){
                    FillHist(param.Name + "/" + eventRegion + "CheckPhi2HEM_eta_lepton", varLeptonEta, weight, 20, -2.5, 2.5);
                    FillHist(param.Name + "/" + eventRegion + "CheckPhi2HEM_phi_lepton", varLeptonPhi, weight, 40, -5.0, 5.0);
                }
                else if (varLeptonPhi <= 0. && (-1.*TMath::Pi()/2.) < varLeptonPhi){
                    FillHist(param.Name + "/" + eventRegion + "CheckPhi3HEM_eta_lepton", varLeptonEta, weight, 20, -2.5, 2.5);
                    FillHist(param.Name + "/" + eventRegion + "CheckPhi3HEM_phi_lepton", varLeptonPhi, weight, 40, -5.0, 5.0);
                }
                else{
                    FillHist(param.Name + "/" + eventRegion + "CheckPhi4HEM_eta_lepton", varLeptonEta, weight, 20, -2.5, 2.5);
                    FillHist(param.Name + "/" + eventRegion + "CheckPhi4HEM_phi_lepton", varLeptonPhi, weight, 40, -5.0, 5.0);
                }

            }


            if (!(eventRegion.Contains("SignalRegion") && eventRegion.Contains("Selection"))){


                if (eventRegion.Contains("Merged")){
                    FillHist(param.Name + "/" + eventRegion + "_pnetxbb", GetParticleNetScore(fatjets.at(0), "XbbMD"), weight, 100,  0., 1.);
                    FillHist(param.Name + "/" + eventRegion + "_pnetxqq", GetParticleNetScore(fatjets.at(0), "XqqMD"), weight, 100,  0., 1.);
                }
                if(eventRegion.Contains("Resolved")){
                    FillHist(param.Name + "/" + eventRegion + "_pt_jet0", jets.at(0).Pt(), weight, 5000, 0., 5000.);
                    FillHist(param.Name + "/" + eventRegion + "_pt_jet1", jets.at(1).Pt(), weight, 5000, 0., 5000.);
                    FillHist(param.Name + "/" + eventRegion + "_pt_jet", jets.at(0).Pt(), weight, 5000, 0., 5000.);
                    FillHist(param.Name + "/" + eventRegion + "_pt_jet", jets.at(1).Pt(), weight, 5000, 0., 5000.);
                }
            }
        }
    }

    return;
}

void singlelepton_analysis::FillBinnedHist(TString hist_name, double hist_var, double weight, int hist_nbins, double *hist_bins){

    if (hist_var > hist_bins[hist_nbins]){
        hist_var = hist_bins[hist_nbins] - 0.0001;
    }

    FillHist(hist_name, hist_var, weight, hist_nbins, hist_bins);

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

    cutFlowIndicator = 0;

    varSecondaryBosonMass = 0.;
    varSecondaryBosonPt = 0.;
    varSecondaryBosonEta = 0.;

    varSecondaryBosonTag = "";

    varPrimaryBosonMass = 0.;
    varResonanceMass1 = 0.;
    varResonanceMass2 = 0.;
    varResonanceMinMass = 0.;
    varResonanceMaxMass = 0.;
    varTopKillerMass = 0.;

    varLeptonPt = 0.;
    varLeptonEta = 0.;
    varLeptonPhi = 0.;

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

int singlelepton_analysis::GetSignalRegion(TString eventRegion, double varSecondaryBosonPt, double varSecondaryBosonMass){

    int signalRegion = 0;

    if (eventRegion.Contains("Preselection") || eventRegion.Contains("Check")) return -1;
    if (!(eventRegion.Contains("SignalRegion") || eventRegion.Contains("ControlRegion"))) return -1;
    if (!(eventRegion.Contains("Merged") || eventRegion.Contains("Resolved"))) return -1;
    if (!eventRegion.Contains("Selection")) return -1;

    double varSecondaryBosonPtCut = 300.;
    double varSecondaryBosonMassCut = 105.;

    if (eventRegion.Contains("SignalRegion")){
        if (eventRegion.Contains("Merged")){
            if (eventRegion.Contains("Xbb")) {
                if (varSecondaryBosonMass >= varSecondaryBosonMassCut) signalRegion = 1;
                else signalRegion = 2;
            }
            else if (eventRegion.Contains("Xqq")){
                if (varSecondaryBosonMass >= varSecondaryBosonMassCut) signalRegion = -1;
                else signalRegion = 3;
            }
            else signalRegion = -1;
        }
        else if (eventRegion.Contains("Resolved")){
            if (eventRegion.Contains("Xbb")) {
                if (varSecondaryBosonMass >= varSecondaryBosonMassCut) signalRegion = 4;
                else signalRegion = 5;
            }
            else if (eventRegion.Contains("Xbq")) {
                if (varSecondaryBosonMass >= varSecondaryBosonMassCut) signalRegion = 6;
                else signalRegion = 7;
            }
            else if (eventRegion.Contains("Xqq")) {
                if (varSecondaryBosonMass >= varSecondaryBosonMassCut) signalRegion = -1;
                else signalRegion = 8;
            }
            else signalRegion = -1;
        }
        else signalRegion = -1;

    }


    else if (eventRegion.Contains("ControlRegion")){
        if (eventRegion.Contains("Merged")){
            if (eventRegion.Contains("XbbInvMTDPhi")) signalRegion = 9;
            else if (eventRegion.Contains("XqqInvMTDPhi")) signalRegion = 10;
            else if (eventRegion.Contains("DomW")) signalRegion = 11;
            else if (eventRegion.Contains("DomTT")) signalRegion = 12;
            else signalRegion = -1;
        }
        else if (eventRegion.Contains("Resolved")){
            if (eventRegion.Contains("XbbInvMTDPhi")) signalRegion = 13;
            else if (eventRegion.Contains("XbqInvMTDPhi")) signalRegion = 14;
            else if (eventRegion.Contains("XqqInvMTDPhi")) signalRegion = 15;
            else if (eventRegion.Contains("DomW")) signalRegion = 16;
            else if (eventRegion.Contains("DomTT")) signalRegion = 17;
            else signalRegion = -1;
        }
        else signalRegion = -1;
    }
    else signalRegion = -1;

    return signalRegion;

}

int singlelepton_analysis::GetCutFlowHistogram(TString cutLabel, double weight_cutflow, TString systName, int cutFlowIndicator){

//    FillHist(systName + "/cutflow_" + cutLabel, cutFlowIndicator, weight_cutflow, 1, cutFlowIndicator, cutFlowIndicator + 1);
    cutFlowIndicator = cutFlowIndicator + 1;

    return cutFlowIndicator;
}

Particle singlelepton_analysis::GetPOGCorrMET(Particle UncorrMET, bool IsPuppiMET){

    int npv = min(nPV,100);

    TString runera = "";

    double METxcorr = 0., METycorr = 0.;
    double uncormet = UncorrMET.Pt();
    double uncormet_phi = UncorrMET.Phi();

    if (!IsPuppiMET){
        if (DataYear == 2016){

            if (IsDATA){
                if (GetDataPeriod() == "B") { METxcorr = -(-0.0214894*npv +-0.188255); METycorr = -(0.0876624*npv +0.812885); }
                else if (GetDataPeriod() == "C") { METxcorr = -(-0.032209*npv +0.067288); METycorr = -(0.113917*npv +0.743906); }
                else if (GetDataPeriod() == "D") { METxcorr = -(-0.0293663*npv +0.21106); METycorr = -(0.11331*npv +0.815787); }
                else if (GetDataPeriod() == "E") { METxcorr = -(-0.0132046*npv +0.20073); METycorr = -(0.134809*npv +0.679068); }
                else if (GetDataPeriod() == "F") {
                    if (GetEraShort()=="2016a") { METxcorr = -(-0.0543566*npv +0.816597); METycorr = -(0.114225*npv +1.17266); }
                    else if (GetEraShort() == "2016b") { METxcorr = -(0.134616*npv +-0.89965); METycorr = -(0.0397736*npv +1.0385); }
                }
                else if (GetDataPeriod() == "G"){ METxcorr = -(0.121809*npv +-0.584893); METycorr = -(0.0558974*npv +0.891234); }
                else if (GetDataPeriod() == "H"){ METxcorr = -(0.0868828*npv +-0.703489); METycorr = -(0.0888774*npv +0.902632); }
            }
            else{
                if (GetEraShort()=="2016a") { METxcorr = -(-0.188743*npv +0.136539); METycorr = -(0.0127927*npv +0.117747); }
                else if (GetEraShort() == "2016b") { METxcorr = -(-0.153497*npv +-0.231751); METycorr = -(0.00731978*npv +0.243323); }
            }

        }
        else if (DataYear == 2017){

            if (IsDATA){
                if (GetDataPeriod() == "B") { METxcorr = -(-0.211161*npv +0.419333); METycorr = -(0.251789*npv +-1.28089); }
                else if (GetDataPeriod() == "C") { METxcorr = -(-0.185184*npv +-0.164009); METycorr = -(0.200941*npv +-0.56853); }
                else if (GetDataPeriod() == "D") { METxcorr = -(-0.201606*npv +0.426502); METycorr = -(0.188208*npv +-0.58313); }
                else if (GetDataPeriod() == "E") { METxcorr = -(-0.162472*npv +0.176329); METycorr = -(0.138076*npv +-0.250239); }
                else if (GetDataPeriod() == "F") { METxcorr = -(-0.210639*npv +0.72934); METycorr = -(0.198626*npv +1.028); }
            }
            else{
                METxcorr = -(-0.300155*npv +1.90608); METycorr = -(0.300213*npv +-2.02232);
            }

        }
        else if (DataYear == 2018){

            if (IsDATA){
                if (GetDataPeriod() == "A") { METxcorr = -(0.263733*npv +-1.91115); METycorr = -(0.0431304*npv +-0.112043); }
                else if (GetDataPeriod() == "B"){ METxcorr = -(0.400466*npv +-3.05914); METycorr = -(0.146125*npv +-0.533233); }
                else if (GetDataPeriod() == "C"){ METxcorr = -(0.430911*npv +-1.42865); METycorr = -(0.0620083*npv +-1.46021); }
                else if (GetDataPeriod() == "D"){ METxcorr = -(0.457327*npv +-1.56856); METycorr = -(0.0684071*npv +-0.928372); }

            }
            else{
                METxcorr = -(0.183518*npv +0.546754); METycorr = -(0.192263*npv +-0.42121);
            }
        }
    }

    double CorrectedMET_x = uncormet * TMath::Cos(uncormet_phi) + METxcorr;
    double CorrectedMET_y = uncormet * TMath::Sin(uncormet_phi) + METycorr;
    double CorrectedMET = TMath::Sqrt( CorrectedMET_x * CorrectedMET_x + CorrectedMET_y * CorrectedMET_y);
    double CorrectedMETPhi = 0.;

    if(CorrectedMET_x==0 && CorrectedMET_y > 0) CorrectedMETPhi = TMath::Pi();
    else if (CorrectedMET_x==0 && CorrectedMET_y < 0 )CorrectedMETPhi = -TMath::Pi();
    else if (CorrectedMET_x > 0) CorrectedMETPhi = TMath::ATan(CorrectedMET_y/CorrectedMET_x);
    else if (CorrectedMET_x < 0 && CorrectedMET_y > 0) CorrectedMETPhi = TMath::ATan(CorrectedMET_y/CorrectedMET_x) + TMath::Pi();
    else if (CorrectedMET_x < 0 && CorrectedMET_y < 0) CorrectedMETPhi = TMath::ATan(CorrectedMET_y/CorrectedMET_x) - TMath::Pi();
    else CorrectedMETPhi =0;

    Particle corrMET;
    corrMET.SetPtEtaPhiM(CorrectedMET, 0., CorrectedMETPhi, 0.);

    return corrMET;
}

template <typename T>
Particle singlelepton_analysis::ScaleLeptonMissingEtPropagation(Particle missingEt, T unscaled, T scaled){

    Particle unscaledSum;
    unscaledSum.SetPxPyPzE(0.,0.,0.,0.);
    for (unsigned int i=0; i < unscaled.size(); i++){
        Particle lepton = unscaled.at(i);
        unscaledSum = unscaledSum + lepton;
    }

    Particle scaledSum;
    scaledSum.SetPxPyPzE(0.,0.,0.,0.);
    for (unsigned int i=0; i < scaled.size(); i++){
        Particle lepton = scaled.at(i);
        scaledSum = scaledSum + lepton;
    }

    Particle scaledMissingEt;

    double scaledMissingEtPx = (missingEt + unscaledSum - scaledSum).Px();
    double scaledMissingEtPy = (missingEt + unscaledSum - scaledSum).Py();
    double scaledMissingEtPt = (missingEt + unscaledSum - scaledSum).Pt();

    scaledMissingEt.SetPxPyPzE(scaledMissingEtPx, scaledMissingEtPy, 0., scaledMissingEtPt);

    return scaledMissingEt;

}

bool singlelepton_analysis::WrongMissingEt(void){

    if (!isfinite(PuppiMET_Type1_pt)) return true;
    if (!IsDATA){
        if (!isfinite(PuppiMET_Type1_pt_shifts->at(0))) return true;
        if (!isfinite(PuppiMET_Type1_pt_shifts->at(1))) return true;
        if (!isfinite(PuppiMET_Type1_pt_shifts->at(2))) return true;
        if (!isfinite(PuppiMET_Type1_pt_shifts->at(3))) return true;
        if (!isfinite(PuppiMET_Type1_pt_shifts->at(10))) return true;
        if (!isfinite(PuppiMET_Type1_pt_shifts->at(11))) return true;
    }

    return false;

}
