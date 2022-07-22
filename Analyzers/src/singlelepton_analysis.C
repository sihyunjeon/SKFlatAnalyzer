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

    bTaggingWPMedium = JetTagging::Parameters(JetTagging::DeepCSV, JetTagging::Medium, JetTagging::incl, JetTagging::comb);

    mcCorr->SetJetTaggingParameters({bTaggingWPMedium});

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
    std::vector<Muon> muonsNoIso = SelectMuons(muonsLoose, param.Muon_Tight_ID, leptonPtCut, 2.1);
    std::vector<Muon> muons;
    for (unsigned int i=0 ; i < muonsNoIso.size(); i++){
        if (muonsNoIso.at(i).RelIso() < 0.15){
            muons.push_back(muonsNoIso.at(i));
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

    std::vector<Jet> bjets;
    for (unsigned int i=0; i < jets.size(); i++){
        if( jets.at(i).GetTaggerResult(bTaggingWPMedium.j_Tagger) >= mcCorr->GetJetTaggingCutValue(bTaggingWPMedium.j_Tagger, bTaggingWPMedium.j_WP) ) bjets.push_back(jets.at(i));
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
        weight = weight * mcCorr->GetBTaggingReweight_1a(jets, bTaggingWPMedium);
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
    bool hasOneMuon = (muons.size() == 1 && muonsLoose.size() == 1);
    bool hasOneElectron = (electrons.size() == 1 && electronsLoose.size() == 1);
    bool hasZeroMuon = (muons.size() == 0 && muonsLoose.size() == 0);
    bool hasZeroElectron = (electrons.size() == 0 && electronsLoose.size() == 0);

    // jet related selections
    bool hasAtLeastOneFatjet = (fatjets.size() >= 1);
    bool hasAtLeastTwoJet = (jets.size() >= 2);

    // signal region specific selections
    // preselection
    bool hasLepton = ((hasOneMuon && hasZeroElectron) || (hasOneElectron && hasZeroMuon)); // preselection
    bool hasBoostedJet = hasAtLeastOneFatjet; // preselection
    bool hasResolvedJet = (!hasBoostedJet && hasAtLeastTwoJet); // preselection
    bool hasJet = (hasBoostedJet || hasResolvedJet); // preselection
    bool hasObject = hasLepton && hasJet; // preselection

    Lepton signalLepton;
    Particle signalSecondaryBoson;
    Particle signalPrimaryBoson;
    Particle signalNeutrino;

    int signalNeutrinoDet = -1.;
    double signalSecondaryBosonMass = -1.;
    double pNetScoreXbbMD = -1., pNetScoreXqqMD = -1.;

    if (hasObject){

        signalLepton = leptons.at(0);

        if (hasBoostedJet){

            signalSecondaryBosonMass = fatjets.at(0).SDMass();
            signalSecondaryBoson = fatjets.at(0);

            double pNetProbXbbMD = fatjets.at(0).GetTaggerResult(pNetXbbMD);
            double pNetProbXccMD = fatjets.at(0).GetTaggerResult(pNetXccMD);
            double pNetProbXqqMD = fatjets.at(0).GetTaggerResult(pNetXqqMD);
            double pNetProbQCDMD = fatjets.at(0).GetTaggerResult(pNetQCDMD);
            pNetScoreXbbMD = pNetProbXbbMD / (pNetProbXbbMD + pNetProbQCDMD);
            pNetScoreXqqMD = (pNetProbXccMD + pNetProbXqqMD) / (pNetProbXccMD + pNetProbXqqMD + pNetProbQCDMD);

        }
        if (hasResolvedJet) {

            if (!IsDATA){
                weight = weight * top_pt_weight;
            }

            signalSecondaryBosonMass = (jets.at(0) + jets.at(1)).M();
            signalSecondaryBoson = jets.at(0) + jets.at(1);

        }

        signalPrimaryBoson = signalLepton + signalSecondaryBoson;
        signalNeutrino = GetReconstructedNeutrino(signalLepton, missingEt);
        signalNeutrinoDet = GetReconstructedNeutrinoDet(signalLepton, missingEt);

    }

    // preselection
    bool hasMtLeptonMissingEtAbove150 = hasObject ? ((signalLepton + missingEt).Mt() > 150) : false; // preselection

    // boosted signal region definitions
    bool hasBoostedXbb = hasBoostedJet ? (pNetScoreXbbMD > 0.94) : false;
    bool hasBoostedXqq = hasBoostedJet ? (!hasBoostedXbb && pNetScoreXqqMD > 0.82) : false;

    // resolved signal region definitions
    double bTaggingWP = mcCorr->GetJetTaggingCutValue(bTaggingWPMedium.j_Tagger, bTaggingWPMedium.j_WP);
    bool hasOneBJet = (hasObject && hasResolvedJet) ? ((jets.at(0).GetTaggerResult(bTaggingWPMedium.j_Tagger) >= bTaggingWP) + (jets.at(1).GetTaggerResult(bTaggingWPMedium.j_Tagger) >= bTaggingWP) == 1) : false;
    bool hasTwoBJet = (hasObject && hasResolvedJet) ? ((jets.at(0).GetTaggerResult(bTaggingWPMedium.j_Tagger) >= bTaggingWP) + (jets.at(1).GetTaggerResult(bTaggingWPMedium.j_Tagger) >= bTaggingWP) == 2) : false;

    // signal region selection
    bool hasSecondaryBosonMassInclH = hasObject ? ((signalSecondaryBosonMass >= 70.) && (signalSecondaryBosonMass <= 145.)) : false;
    bool hasSecondaryBosonMassExclH = hasObject ? ((signalSecondaryBosonMass >= 60.) && (signalSecondaryBosonMass <= 110.)) : false;


    // others
    bool hasImaginarySolution = (signalNeutrinoDet == 0);
    bool hasZeroBJet = (bjets.size() == 0);   

    std::map<TString, bool> eventRegions;

    eventRegions["Signal_MuonPreselection"] = passMuonTrigger && hasOneMuon && hasZeroElectron && hasMtLeptonMissingEtAbove150 && hasJet;
    eventRegions["Signal_ElectronPreselection"] = passElectronTrigger && hasZeroMuon && hasOneElectron && hasMtLeptonMissingEtAbove150 && hasJet;

    eventRegions["Signal_MuonBoostedPreselection"] = eventRegions["Signal_MuonPreselection"] && hasBoostedJet;
    eventRegions["Signal_ElectronBoostedPreselection"] = eventRegions["Signal_ElectronPreselection"] && hasBoostedJet;
    eventRegions["Signal_MuonBoostedSR1"] = eventRegions["Signal_MuonBoostedPreselection"] && hasBoostedXbb && hasSecondaryBosonMassInclH && hasZeroBJet;
    eventRegions["Signal_ElectronBoostedSR1"] = eventRegions["Signal_ElectronBoostedPreselection"] && hasBoostedXbb && hasSecondaryBosonMassInclH && hasZeroBJet;
    eventRegions["Signal_MuonBoostedSR2"] = eventRegions["Signal_MuonBoostedPreselection"] && hasBoostedXqq && hasSecondaryBosonMassExclH && hasZeroBJet;
    eventRegions["Signal_ElectronBoostedSR2"] = eventRegions["Signal_ElectronBoostedPreselection"] && hasBoostedXqq && hasSecondaryBosonMassExclH && hasZeroBJet;

    eventRegions["Signal_MuonResolvedPreselection"] = eventRegions["Signal_MuonPreselection"] && hasResolvedJet;
    eventRegions["Signal_ElectronResolvedPreselection"] = eventRegions["Signal_ElectronPreselection"] && hasResolvedJet;
    eventRegions["Signal_MuonResolvedSR1"] = eventRegions["Signal_MuonResolvedPreselection"] && hasTwoBJet && hasSecondaryBosonMassInclH;
    eventRegions["Signal_ElectronResolvedSR1"] = eventRegions["Signal_ElectronResolvedPreselection"] && hasTwoBJet && hasSecondaryBosonMassInclH;
    eventRegions["Signal_MuonResolvedSR2"] = eventRegions["Signal_MuonResolvedPreselection"] && hasOneBJet && hasSecondaryBosonMassInclH;
    eventRegions["Signal_ElectronResolvedSR2"] = eventRegions["Signal_ElectronResolvedPreselection"] && hasOneBJet && hasSecondaryBosonMassInclH;


    std::map<TString, bool>::iterator itEventRegions;

    for (itEventRegions = eventRegions.begin(); itEventRegions != eventRegions.end(); ++itEventRegions){

        if (itEventRegions->second){
            TString eventRegion = itEventRegions->first;

            if (hasObject){
                FillHist(eventRegion + "_dphi_leptonmet", signalLepton.DeltaPhi(missingEt), weight, 100, -5., 5.);
                FillHist(eventRegion + "_masst_leptonmet", (signalLepton + missingEt).Mt(), weight, 5000, 0., 5000.);

                FillHist(eventRegion + "_eta_lepton", signalLepton.Eta(), weight, 100, -5., 5.);
                FillHist(eventRegion + "_pt_lepton", signalLepton.Pt(), weight, 5000,0., 5000.);
                FillHist(eventRegion + "_phi_lepton", signalLepton.Phi(), weight, 100, -5., 5.);

                FillHist(eventRegion + "_eta_secondaryboson", signalSecondaryBoson.Eta(), weight, 100, -5., 5.);
                FillHist(eventRegion + "_mass_secondaryboson", signalSecondaryBosonMass, weight, 5000, 0., 5000.);
                FillHist(eventRegion + "_pt_secondaryboson", signalSecondaryBoson.Pt(), weight, 5000, 0., 5000.);

                FillHist(eventRegion + "_met", missingEt.Pt(), weight, 5000,0., 5000.);
                if (hasBoostedJet){
                    FillHist(eventRegion + "_pnetscorexbbmd_fatjet", pNetScoreXbbMD, weight, 50, 0., 1.);
                    FillHist(eventRegion + "_pnetscorexqqmd_fatjet", pNetScoreXqqMD, weight, 50, 0., 1.);
                }
            }


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
