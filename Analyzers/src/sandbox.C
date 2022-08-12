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

    bTaggingWP = JetTagging::Parameters(JetTagging::DeepCSV, JetTagging::Medium, JetTagging::incl, JetTagging::comb);

    pNetXbbMD = JetTagging::particleNetMD_Xbb;
    pNetXccMD = JetTagging::particleNetMD_Xcc;
    pNetXqqMD = JetTagging::particleNetMD_Xqq;
    pNetQCDMD = JetTagging::particleNetMD_QCD;


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

    if (!passMuonIsoTriggers) return;

    // define jets ak8
    std::vector<FatJet> fatjetsNoSDMass = SelectFatJets(allFatJets, "tight", 200., 2.1);
    fatjetsNoSDMass = FatJetsVetoLeptonInside(fatjetsNoSDMass, electrons, muons, 0.4);
    std::sort(fatjetsNoSDMass.begin(), fatjetsNoSDMass.end(), PtComparing);
    std::vector<FatJet> fatjets;

    for (unsigned int i=0; i < fatjetsNoSDMass.size(); i++){
        if(fatjetsNoSDMass.at(i).SDMass() > 50.){
            fatjets.push_back(fatjetsNoSDMass.at(i));
        }
    }

    // define jets ak4
    std::vector<Jet> jets = SelectJets(allJets, "tightLepVeto", 30., 2.1);
    jets = JetsAwayFromFatJet(jets, fatjets, 1.2);
    jets = JetsVetoLeptonInside(jets, electrons, muons, 0.4);

    double bTaggingWPMedium = mcCorr->GetJetTaggingCutValue(bTaggingWP.j_Tagger, bTaggingWP.j_WP);
    std::vector<Jet> bjets;
    for (unsigned int i=0; i < jets.size(); i++){
        if( jets.at(i).GetTaggerResult(bTaggingWP.j_Tagger) >= bTaggingWPMedium ) bjets.push_back(jets.at(i));
    }

    double weight = 1.;
    if (!IsDATA){
        weight = weight * MCweight(true, true) ;
//        weight = weight * GetPrefireWeight(0);
//        weight = weight * GetPileUpWeight(nPileUp,0); 
        weight = weight * event.GetTriggerLumi("Full");
    }

    bool isMergedRegion = (fatjets.size() > 0.);
    bool isResolvedRegion = (jets.size() >= 2);
    bool isBBTagged = false;

    FatJet signalFatjet;
    Jet signalJet1, signalJet2;
    double secondaryBosonMass = 0., secondaryBosonPt = 0.;
    if (isMergedRegion){
        signalFatjet = fatjets.at(0);
        secondaryBosonMass = signalFatjet.SDMass();
        secondaryBosonPt = signalFatjet.Pt();
        double pNetScoreXbbMD = GetParticleNetScore(signalFatjet, "XbbMD");
        double pNetScoreXqqMD = GetParticleNetScore(signalFatjet, "XqqMD");
        if (pNetScoreXbbMD > 0.98) isBBTagged = true;
    }
    else if (!isMergedRegion && isResolvedRegion){
        signalJet1 = jets.at(0);
        signalJet2 = jets.at(1);
        secondaryBosonMass = (signalJet1 + signalJet2).M();
        secondaryBosonPt = (signalJet1 + signalJet2).Pt();
        if ((jets.at(0).GetTaggerResult(bTaggingWP.j_Tagger) >= bTaggingWPMedium) && (jets.at(1).GetTaggerResult(bTaggingWP.j_Tagger) >= bTaggingWPMedium)) isBBTagged = true;
    }
    else return;

    std::map<TString, bool> eventRegions;

    eventRegions["Muon_ResolvedRegion"] = passMuonIsoTriggers && isResolvedRegion;
    eventRegions["Muon_ResolvedRegionBBTagged"] = passMuonIsoTriggers && isResolvedRegion && isBBTagged; 
    eventRegions["Muon_ResolvedRegionMassWindow"] = passMuonIsoTriggers && isResolvedRegion && (secondaryBosonMass > 65. && secondaryBosonMass < 145.); 
    eventRegions["Muon_ResolvedRegionBBTaggedMassWindow"] = passMuonIsoTriggers && isResolvedRegion && isBBTagged && (secondaryBosonMass > 65. && secondaryBosonMass < 145.); 
    eventRegions["Muon_ResolvedRegionBBTaggedMassWindowBBBoosted"] = passMuonIsoTriggers && isResolvedRegion && isBBTagged && (secondaryBosonMass > 65. && secondaryBosonMass < 145.) && (secondaryBosonPt > 150.);
    eventRegions["Muon_ResolvedRegionBBTaggedMassWindowBBBoostedLargeMET"] = passMuonIsoTriggers && isResolvedRegion && isBBTagged && (secondaryBosonMass > 65. && secondaryBosonMass < 145.) && (secondaryBosonPt > 150.) && (missingEt.Pt() > 100.);


    eventRegions["Muon_MergedRegion"] = passMuonIsoTriggers && isMergedRegion; 
    eventRegions["Muon_MergedRegionBBTagged"] = passMuonIsoTriggers && isMergedRegion && isBBTagged;
    eventRegions["Muon_MergedRegionMassWindow"] = passMuonIsoTriggers && isMergedRegion && (secondaryBosonMass > 65. && secondaryBosonMass < 145.);
    eventRegions["Muon_MergedRegionBBTaggedMassWindow"] = passMuonIsoTriggers && isMergedRegion && isBBTagged && (secondaryBosonMass > 65. && secondaryBosonMass < 145.);


    std::map<TString, bool>::iterator itEventRegions;

    for (itEventRegions = eventRegions.begin(); itEventRegions != eventRegions.end(); ++itEventRegions){

        if (itEventRegions->second){

            TString eventRegion = itEventRegions->first;
            FillHist(eventRegion + "_nevents_weighted", 0., weight, 1, 0., 1.);
            FillHist(eventRegion + "_mass_secondaryboson", secondaryBosonMass, weight, 5000, 0., 5000.);
            FillHist(eventRegion + "_pt_secondaryboson", secondaryBosonPt, weight, 5000, 0., 5000.);
            FillHist(eventRegion + "_met", missingEt.Pt(), weight, 5000, 0., 5000.);

        }
    }


}

sandbox::sandbox(){

}

sandbox::~sandbox(){

}

double sandbox::GetParticleNetScore(FatJet fatjet, TString tagger){

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

