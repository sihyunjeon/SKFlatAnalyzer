#include "singlelepton_analysis_tree.h"

singlelepton_analysis_tree::singlelepton_analysis_tree(){

    myTreeMuonXbb = new TTree("myTreeMuonXbb", "myTreeMuonXbb");
    myTreeMuonXqq = new TTree("myTreeMuonXqq", "myTreeMuonXqq");

    myTreeElectronXbb = new TTree("myTreeElectronXbb", "myTreeElectronXbb");
    myTreeElectronXqq = new TTree("myTreeElectronXqq", "myTreeElectronXqq");

    tree_charge = 0.;
    tree_dphi_leptonmet = 0.;
    tree_masst_fatjetmet = 0.;
    tree_masst_leptonmet = 0.;
    tree_mass_fatjetlepton = 0.;
    tree_masst_fatjetleptonmet = 0.;
    tree_met = 0.;
    tree_n_jet = 0.;
    tree_pt_lepton = 0.;
    tree_sdmass_fatjet = 0.;
    tree_st = 0.;
    tree_ht = 0.;

    myTreeMuonXbb->Branch("tree_charge", &tree_charge, "tree_charge/I");
    myTreeMuonXbb->Branch("tree_dphi_leptonmet", &tree_dphi_leptonmet, "tree_dphi_leptonmet/F");
    myTreeMuonXbb->Branch("tree_masst_fatjetmet", &tree_masst_fatjetmet, "tree_masst_fatjetmet/F");
    myTreeMuonXbb->Branch("tree_masst_leptonmet", &tree_masst_leptonmet, "tree_masst_leptonmet/F");
    myTreeMuonXbb->Branch("tree_mass_fatjetlepton", &tree_mass_fatjetlepton, "tree_mass_fatjetlepton/F");
    myTreeMuonXbb->Branch("tree_masst_fatjetleptonmet", &tree_masst_fatjetleptonmet, "tree_masst_fatjetleptonmet/F");
    myTreeMuonXbb->Branch("tree_met", &tree_met, "tree_met/F");
    myTreeMuonXbb->Branch("tree_n_jet", &tree_n_jet, "tree_n_jet/I");
    myTreeMuonXbb->Branch("tree_pt_lepton", &tree_pt_lepton, "tree_pt_lepton/F");
    myTreeMuonXbb->Branch("tree_sdmass_fatjet", &tree_sdmass_fatjet, "tree_sdmass_fatjet/F");
    myTreeMuonXbb->Branch("tree_st", &tree_st, "tree_st/F");
    myTreeMuonXbb->Branch("tree_ht", &tree_ht, "tree_ht/F");
    myTreeMuonXbb->Branch("tree_weight", &tree_weight, "tree_weight/F");

    myTreeMuonXqq->Branch("tree_charge", &tree_charge, "tree_charge/I");
    myTreeMuonXqq->Branch("tree_dphi_leptonmet", &tree_dphi_leptonmet, "tree_dphi_leptonmet/F");
    myTreeMuonXqq->Branch("tree_masst_fatjetmet", &tree_masst_fatjetmet, "tree_masst_fatjetmet/F");
    myTreeMuonXqq->Branch("tree_masst_leptonmet", &tree_masst_leptonmet, "tree_masst_leptonmet/F");
    myTreeMuonXqq->Branch("tree_mass_fatjetlepton", &tree_mass_fatjetlepton, "tree_mass_fatjetlepton/F");
    myTreeMuonXqq->Branch("tree_masst_fatjetleptonmet", &tree_masst_fatjetleptonmet, "tree_masst_fatjetleptonmet/F");
    myTreeMuonXqq->Branch("tree_met", &tree_met, "tree_met/F");
    myTreeMuonXqq->Branch("tree_n_jet", &tree_n_jet, "tree_n_jet/I");
    myTreeMuonXqq->Branch("tree_pt_lepton", &tree_pt_lepton, "tree_pt_lepton/F");
    myTreeMuonXqq->Branch("tree_sdmass_fatjet", &tree_sdmass_fatjet, "tree_sdmass_fatjet/F");
    myTreeMuonXqq->Branch("tree_st", &tree_st, "tree_st/F");
    myTreeMuonXqq->Branch("tree_ht", &tree_ht, "tree_ht/F");
    myTreeMuonXqq->Branch("tree_weight", &tree_weight, "tree_weight/F");

    myTreeElectronXbb->Branch("tree_charge", &tree_charge, "tree_charge/I");
    myTreeElectronXbb->Branch("tree_dphi_leptonmet", &tree_dphi_leptonmet, "tree_dphi_leptonmet/F");
    myTreeElectronXbb->Branch("tree_masst_fatjetmet", &tree_masst_fatjetmet, "tree_masst_fatjetmet/F");
    myTreeElectronXbb->Branch("tree_masst_leptonmet", &tree_masst_leptonmet, "tree_masst_leptonmet/F");
    myTreeElectronXbb->Branch("tree_mass_fatjetlepton", &tree_mass_fatjetlepton, "tree_mass_fatjetlepton/F");
    myTreeElectronXbb->Branch("tree_masst_fatjetleptonmet", &tree_masst_fatjetleptonmet, "tree_masst_fatjetleptonmet/F");
    myTreeElectronXbb->Branch("tree_met", &tree_met, "tree_met/F");
    myTreeElectronXbb->Branch("tree_n_jet", &tree_n_jet, "tree_n_jet/I");
    myTreeElectronXbb->Branch("tree_pt_lepton", &tree_pt_lepton, "tree_pt_lepton/F");
    myTreeElectronXbb->Branch("tree_sdmass_fatjet", &tree_sdmass_fatjet, "tree_sdmass_fatjet/F");
    myTreeElectronXbb->Branch("tree_st", &tree_st, "tree_st/F");
    myTreeElectronXbb->Branch("tree_ht", &tree_ht, "tree_ht/F");
    myTreeElectronXbb->Branch("tree_weight", &tree_weight, "tree_weight/F");

    myTreeElectronXqq->Branch("tree_charge", &tree_charge, "tree_charge/I");
    myTreeElectronXqq->Branch("tree_dphi_leptonmet", &tree_dphi_leptonmet, "tree_dphi_leptonmet/F");
    myTreeElectronXqq->Branch("tree_masst_fatjetmet", &tree_masst_fatjetmet, "tree_masst_fatjetmet/F");
    myTreeElectronXqq->Branch("tree_masst_leptonmet", &tree_masst_leptonmet, "tree_masst_leptonmet/F");
    myTreeElectronXqq->Branch("tree_mass_fatjetlepton", &tree_mass_fatjetlepton, "tree_mass_fatjetlepton/F");
    myTreeElectronXqq->Branch("tree_masst_fatjetleptonmet", &tree_masst_fatjetleptonmet, "tree_masst_fatjetleptonmet/F");
    myTreeElectronXqq->Branch("tree_met", &tree_met, "tree_met/F");
    myTreeElectronXqq->Branch("tree_n_jet", &tree_n_jet, "tree_n_jet/I");
    myTreeElectronXqq->Branch("tree_pt_lepton", &tree_pt_lepton, "tree_pt_lepton/F");
    myTreeElectronXqq->Branch("tree_sdmass_fatjet", &tree_sdmass_fatjet, "tree_sdmass_fatjet/F");
    myTreeElectronXqq->Branch("tree_st", &tree_st, "tree_st/F");
    myTreeElectronXqq->Branch("tree_ht", &tree_ht, "tree_ht/F");
    myTreeElectronXqq->Branch("tree_weight", &tree_weight, "tree_weight/F");

}

void singlelepton_analysis_tree::initializeAnalyzer(){

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

    bTaggingWP = JetTagging::Parameters(JetTagging::DeepCSV, JetTagging::Medium, JetTagging::incl, JetTagging::comb);

    mcCorr->SetJetTaggingParameters({bTaggingWP});

    pNetXbbMD = JetTagging::particleNetMD_Xbb;
    pNetXccMD = JetTagging::particleNetMD_Xcc;
    pNetXqqMD = JetTagging::particleNetMD_Xqq;
    pNetQCDMD = JetTagging::particleNetMD_QCD;

}


singlelepton_analysis_tree::~singlelepton_analysis_tree(){

    delete myTreeMuonXbb;
    delete myTreeMuonXqq;
    delete myTreeElectronXbb;
    delete myTreeElectronXqq;

}

void singlelepton_analysis_tree::executeEvent(){

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

void singlelepton_analysis_tree::executeEventFromParameter(AnalyzerParameter param){

    if(!PassMETFilter()) return;

    Event event = GetEvent();

    if (!(event.PassTrigger(muonTriggers) || event.PassTrigger(electronTriggers))) return;

    // define leptons
    std::vector<Muon> muonsLooseNoIso = SelectMuons(allMuons, param.Muon_Loose_ID, leptonPtCut, 2.1);
    std::vector<Muon> muonsLoose;
    for (unsigned int i=0 ; i < muonsLooseNoIso.size(); i++){
        Muon lepton = muonsLooseNoIso.at(i);
        if (lepton.RelIso() < 0.40){
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
            if (invertLeptonIsolation && (lepton.RelIso() > 0.30)){
                muons.push_back(lepton);
            }
        }
    }
    std::sort(muons.begin(), muons.end(), PtComparing);

    std::vector<Electron> electronsLoose = SelectElectrons(allElectrons, param.Electron_Loose_ID, leptonPtCut, 2.1, true);
    std::vector<Electron> electrons = SelectElectrons(electronsLoose, param.Electron_Tight_ID, leptonPtCut, 2.1);
    std::sort(electrons.begin(), electrons.end(), PtComparing);

    // define jets ak8
    std::vector<FatJet> fatjetsNoSDMass = SelectFatJets(allFatJets, param.FatJet_ID, fatjetPtCut, 2.1);
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
    std::vector<Jet> jets = SelectJets(allJets, param.Jet_ID, jetPtCut, 2.1);
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

    // boosted signal region definitions
    bool hasFatjetMassIncl = ((fatjets.at(0).SDMass() >= 60.) && (fatjets.at(0).SDMass() < 150.));

    double pNetScoreXbbMD = GetParticleNetScore(signalFatjet, "XbbMD");
    double pNetScoreXqqMD = GetParticleNetScore(signalFatjet, "XqqMD");

    bool hasBoostedXbb = (pNetScoreXbbMD > 0.90);
    bool hasBoostedXqq = (!hasBoostedXbb) ? (pNetScoreXqqMD > 0.80) : false;

    // others
    bool hasZeroBJet = (bjets.size() == 0);
    bool hasMtLeptonMissingEtAbove200 = (signalLepton + missingEt).Mt() > 200.;

    double ST = missingEt.Pt(); double HT = 0.;
    for (unsigned int i=0; i < leptons.size(); i++){
        Particle ptl = leptons.at(i);
        ST = ST + ptl.Pt();
    }
    for (unsigned int i=0; i < fatjets.size(); i++){
        Particle ptl = fatjets.at(i);
        ST = ST + ptl.Pt();
        HT = HT + ptl.Pt();
    }
    for (unsigned int i=0; i < jets.size(); i++){
        Particle ptl = jets.at(i);
        ST = ST + ptl.Pt();
        HT = HT + ptl.Pt();
    }

    tree_charge = signalLepton.Charge();
    tree_dphi_leptonmet = signalLepton.DeltaPhi(missingEt);
    tree_masst_fatjetmet = (signalFatjet + missingEt).Mt();
    tree_masst_leptonmet = (signalLepton + missingEt).Mt();
    tree_mass_fatjetlepton = (signalFatjet + signalLepton).M();
    tree_masst_fatjetleptonmet = (signalFatjet + signalLepton + missingEt).Mt();
    tree_met = missingEt.Pt();
    tree_n_jet = jets.size();
    tree_pt_lepton = signalLepton.Pt();
    tree_sdmass_fatjet = signalFatjet.SDMass();
    tree_st = ST;
    tree_ht = HT;
    tree_weight = weight;

    std::map<TString, bool> eventRegions;

    eventRegions["Preselection_MuonXbb"] = passMuonTrigger && hasOneMuon && hasZeroElectron && hasMissingEtAbove50 && hasFatjetMassIncl && hasMtLeptonMissingEtAbove200 && hasBoostedXbb && hasZeroBJet;
    eventRegions["Preselection_MuonXqq"] = passMuonTrigger && hasOneMuon && hasZeroElectron && hasMissingEtAbove50 && hasFatjetMassIncl && hasMtLeptonMissingEtAbove200 && hasBoostedXqq && hasZeroBJet;
    eventRegions["Preselection_ElectronXbb"] = passElectronTrigger && hasZeroMuon && hasOneElectron && hasMissingEtAbove50 && hasFatjetMassIncl && hasMtLeptonMissingEtAbove200 && hasBoostedXbb && hasZeroBJet;
    eventRegions["Preselection_ElectronXqq"] = passElectronTrigger && hasZeroMuon && hasOneElectron && hasMissingEtAbove50 && hasFatjetMassIncl && hasMtLeptonMissingEtAbove200 && hasBoostedXqq && hasZeroBJet;

    if (eventRegions["Preselection_MuonXbb"]) myTreeMuonXbb->Fill();
    if (eventRegions["Preselection_MuonXqq"]) myTreeMuonXqq->Fill();
    if (eventRegions["Preselection_ElectronXbb"]) myTreeElectronXbb->Fill();
    if (eventRegions["Preselection_ElectronXqq"]) myTreeElectronXqq->Fill();

    return;
}

double singlelepton_analysis_tree::GetReconstructedNeutrinoDet(Lepton lepton, Particle missingEt){

    double mW = 80.4;
    double A = mW*mW + 2*missingEt.Px()*lepton.Px() + 2*missingEt.Py()*lepton.Py();
    double a = 4*lepton.Pz()*lepton.Pz() - 4*lepton.E()*lepton.E();
    double b = 4*lepton.Pz()*A;
    double c = A*A - 4*lepton.E()*lepton.E()*missingEt.Pt()*missingEt.Pt();
    double det = b*b - 4*a*c;

    if (det < 0) return 0.;
    else return 1.;

}

Particle singlelepton_analysis_tree::GetReconstructedNeutrino(Lepton lepton, Particle missingEt){

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

double singlelepton_analysis_tree::GetParticleNetScore(FatJet fatjet, TString tagger){

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

void singlelepton_analysis_tree::WriteHist(){

  outfile->cd();

  myTreeMuonXbb->Write();
  myTreeMuonXqq->Write();
  myTreeElectronXbb->Write();
  myTreeElectronXqq->Write();

  outfile->cd();

}
