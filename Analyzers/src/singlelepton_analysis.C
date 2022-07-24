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
        leptonPtCut = 20.;
    }
    else if (DataYear == 2017){
        muonTriggers.push_back("HLT_IsoMu27_v");
        electronTriggers.push_back("HLT_Ele35_WPTight_Gsf_v");
        electronTriggers.push_back("HLT_Photon200_v");
        electronTriggers.push_back("HLT_Ele115_CaloIdVT_GsfTrkIdT_v");
        muonPtCut = 40.;
        electronPtCut = 40.;
        leptonPtCut = 20.;
    }
    else if(DataYear==2018){
        muonTriggers.push_back("HLT_IsoMu24_v");
        electronTriggers.push_back("HLT_Ele32_WPTight_Gsf_v");
        electronTriggers.push_back("HLT_Photon200_v");
        electronTriggers.push_back("HLT_Ele115_CaloIdVT_GsfTrkIdT_v");
        muonPtCut = 40.;
        electronPtCut = 40.;
        leptonPtCut = 20.;
    }

    jetPtCut = 30.; fatjetPtCut = 200.;

    bTaggingWP = JetTagging::Parameters(JetTagging::DeepCSV, JetTagging::Medium, JetTagging::incl, JetTagging::comb);

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
    std::vector<Muon> muonsLoose = SelectMuons(allMuons, param.Muon_Loose_ID, leptonPtCut, 2.1);
    std::vector<Muon> muonsLooseIso;
    for (unsigned int i=0 ; i < muonsLoose.size(); i++){
        if (muonsLoose.at(i).RelIso() < 0.15){
            muonsLooseIso.push_back(muonsLoose.at(i));
        }
    }
    std::vector<Muon> muons = SelectMuons(muonsLooseIso, param.Muon_Tight_ID, leptonPtCut, 2.1);

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

    // boosted signal region definitions
    bool hasFatjetMassIncl = ((fatjets.at(0).SDMass() >= 50.) && (fatjets.at(0).SDMass() <= 160.));
    bool hasFatjetMassHigh = ((fatjets.at(0).SDMass() >= 100.) && (fatjets.at(0).SDMass() <= 150.));
    bool hasFatjetMassLow = ((fatjets.at(0).SDMass() >= 60.) && (fatjets.at(0).SDMass() <= 100.));

    double pNetScoreXbbMD = GetParticleNetScore(signalFatjet, "XbbMD");
    double pNetScoreXqqMD = GetParticleNetScore(signalFatjet, "XqqMD");

    bool hasBoostedXbb = (pNetScoreXbbMD > 0.94);
    bool hasBoostedXqq = (!hasBoostedXbb) ? (pNetScoreXqqMD > 0.82) : false;

    // others
    bool hasZeroBJet = (bjets.size() == 0);
    bool hasMtLeptonMissingEtAbove200 = (signalLepton + missingEt).Mt() > 200.;
    bool hasPositiveCharge = (signalLepton.Charge() > 0);

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

    std::map<TString, bool> eventRegions;

    eventRegions["MuonPreselection"] = passMuonTrigger && hasOneMuon && hasZeroElectron && hasMissingEtAbove50 && hasFatjetMassIncl;
    eventRegions["ElectronPreselection"] = passElectronTrigger && hasZeroMuon && hasOneElectron && hasMissingEtAbove50 && hasFatjetMassIncl;

    eventRegions["Signal_MuonSignalRegionXbb-HighMassJ"] = eventRegions["MuonPreselection"] && hasZeroBJet && hasMtLeptonMissingEtAbove200 && hasBoostedXbb && hasFatjetMassHigh;
    eventRegions["Signal_MuonSignalRegionXbb-LowMassJ"] = eventRegions["MuonPreselection"] && hasZeroBJet && hasMtLeptonMissingEtAbove200 && hasBoostedXbb && hasFatjetMassLow;
    eventRegions["Signal_MuonSignalRegionXqq-LowMassJ"] = eventRegions["MuonPreselection"] && hasZeroBJet && hasMtLeptonMissingEtAbove200 && hasBoostedXqq && hasFatjetMassLow && hasMissingEtAbove100;
    eventRegions["Signal_ElectronSignalRegionXbb-HighMassJ"] = eventRegions["ElectronPreselection"] && hasZeroBJet && hasMtLeptonMissingEtAbove200 && hasBoostedXbb && hasFatjetMassHigh;
    eventRegions["Signal_ElectronSignalRegionXbb-LowMassJ"] = eventRegions["ElectronPreselection"] && hasZeroBJet && hasMtLeptonMissingEtAbove200 && hasBoostedXbb && hasFatjetMassLow;
    eventRegions["Signal_ElectronSignalRegionXqq-LowMassJ"] = eventRegions["ElectronPreselection"] && hasZeroBJet && hasMtLeptonMissingEtAbove200 && hasBoostedXqq && hasFatjetMassLow && hasMissingEtAbove100;

    eventRegions["Control_MuonControlRegionXbb-InvB"] = eventRegions["MuonPreselection"] && !hasZeroBJet && hasMtLeptonMissingEtAbove200 && hasBoostedXbb;
    eventRegions["Control_MuonControlRegionXbb-InvMt"] = eventRegions["MuonPreselection"] && hasZeroBJet && !hasMtLeptonMissingEtAbove200 && hasBoostedXbb;
    eventRegions["Control_MuonControlRegionXqq-InvB"] = eventRegions["MuonPreselection"] && !hasZeroBJet && hasMtLeptonMissingEtAbove200 && hasBoostedXqq;
    eventRegions["Control_MuonControlRegionXqq-InvMt"] = eventRegions["MuonPreselection"] && hasZeroBJet && !hasMtLeptonMissingEtAbove200 && hasBoostedXqq;
    eventRegions["Control_MuonControlRegion-InvXbbXqq"] = (passMuonTrigger && hasOneMuon && hasZeroElectron && hasMissingEtAbove50 && !hasFatjetMassIncl) && hasZeroBJet && (!hasBoostedXbb && !hasBoostedXqq);

    eventRegions["Control_ElectronControlRegionXbb-InvB"] = eventRegions["ElectronPreselection"] && !hasZeroBJet && hasMtLeptonMissingEtAbove200 && hasBoostedXbb;
    eventRegions["Control_ElectronControlRegionXbb-InvMt"] = eventRegions["ElectronPreselection"] && hasZeroBJet && !hasMtLeptonMissingEtAbove200 && hasBoostedXbb;
    eventRegions["Control_ElectronControlRegionXqq-InvB"] = eventRegions["ElectronPreselection"] && !hasZeroBJet && hasMtLeptonMissingEtAbove200 && hasBoostedXqq;
    eventRegions["Control_ElectronControlRegionXqq-InvMt"] = eventRegions["ElectronPreselection"] && hasZeroBJet && !hasMtLeptonMissingEtAbove200 && hasBoostedXqq;
    eventRegions["Control_ElectronControlRegion-InvXbbXqq"] = (passElectronTrigger && hasZeroMuon && hasOneElectron && hasMissingEtAbove50 && !hasFatjetMassIncl) && hasZeroBJet && (!hasBoostedXbb && !hasBoostedXqq);

    std::map<TString, bool>::iterator itEventRegions;

    for (itEventRegions = eventRegions.begin(); itEventRegions != eventRegions.end(); ++itEventRegions){

        if (itEventRegions->second){
            TString eventRegion = itEventRegions->first;

            FillHist(eventRegion + "_dphi_leptonmet", signalLepton.DeltaPhi(missingEt), weight, 100, -5., 5.);
            FillHist(eventRegion + "_masst_leptonmet", (signalLepton + missingEt).Mt(), weight, 5000, 0., 5000.);

            FillHist(eventRegion + "_eta_lepton", signalLepton.Eta(), weight, 100, -5., 5.);
            FillHist(eventRegion + "_pt_lepton", signalLepton.Pt(), weight, 5000,0., 5000.);
            FillHist(eventRegion + "_phi_lepton", signalLepton.Phi(), weight, 100, -5., 5.);

            FillHist(eventRegion + "_eta_secondaryboson", signalFatjet.Eta(), weight, 100, -5., 5.);
            FillHist(eventRegion + "_mass_secondaryboson", signalFatjet.SDMass(), weight, 5000, 0., 5000.);
            FillHist(eventRegion + "_pt_secondaryboson", signalFatjet.Pt(), weight, 5000, 0., 5000.);

            FillHist(eventRegion + "_met", missingEt.Pt(), weight, 5000,0., 5000.);
            FillHist(eventRegion + "_st", ST, weight, 5000,0., 5000.);

            FillHist(eventRegion + "_masst_primaryboson", signalPrimaryBoson.Mt(), weight, 5000,0., 5000.);

            FillHist(eventRegion + "_mass_effective", signalEff.M(), weight, 5000,0., 5000.);
            FillHist(eventRegion + "_masst_effective", signalEff.Mt(), weight, 5000,0., 5000.);

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
