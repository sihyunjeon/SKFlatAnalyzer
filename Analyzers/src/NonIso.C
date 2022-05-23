#include "NonIso.h"

NonIso::NonIso(){

}

void NonIso::initializeAnalyzer(){

  MuonTightIDs = {"HNTightV1"};
  MuonLooseIDs = {"HNLooseV1"};
  //MuonVetoIDs  = {"ISRVeto"};
  MuonVetoIDs  = {"HNVeto2016"};
  ElectronTightIDs = {"HNTightV1"};
  ElectronLooseIDs = {"HNLooseV1"};
  //ElectronVetoIDs  = {"ISRVeto"};
  ElectronVetoIDs  = {"HNVeto"};
  FakeRateIDs = {"HN"}; //JH : NOTE This is used in fakeEst->ReadHistograms() in m.initializeAnalyzerTools() 

  //==== At this point, sample informations (e.g., IsDATA, DataStream, MCSample, or DataYear) are all set
  //==== You can define sample-dependent or year-dependent variables here
  //==== (Example) Year-dependent variables
  //==== I defined "TString IsoMuTriggerName;" and "double TriggerSafePtCut;" in Analyzers/include/NonIso.h 
  //==== IsoMuTriggerName is a year-dependent variable, and you don't want to do "if(Dataer==~~)" for every event (let's save cpu time).
  //==== Then, do it here, which only ran once for each macro

  MuonTriggers.clear();
  MuonTriggersH.clear();
  MuonTriggersHighPt.clear();
  ElectronTriggers.clear();
  EMuTriggers.clear();
  EMuTriggersH.clear();

  if(DataYear==2016){                                                                   // Lumi values for trigger weight (/pb)
    MuonTriggers.push_back("HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_v");                       // 35918.219492947
    MuonTriggers.push_back("HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_v");                     // 35918.219492947 //JH : NOTE these two are prescaled at 2016H -> https://its.cern.ch/jira/browse/CMSHLT-1002
    MuonTriggersH.push_back("HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v");                   // 8650.628380028
    MuonTriggersH.push_back("HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v");                 // 8650.628380028
    MuonTriggersHighPt.push_back("HLT_Mu50_v");                    
    MuonTriggersHighPt.push_back("HLT_TkMu50_v");                  //JH : to see how many events are cut with high pt
    ElectronTriggers.push_back("HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v");          // 35918.219492947
    EMuTriggers.push_back("HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_v");          // 35918.219492947
    EMuTriggers.push_back("HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v");         // 35918.219492947
    EMuTriggersH.push_back("HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_v");      // 8650.628380028
    EMuTriggersH.push_back("HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v");     // 8650.628380028
    MuonPtCut1 = 20., MuonPtCut2 = 10.;
    ElectronPtCut1 = 25., ElectronPtCut2 = 15.;
    EMuPtCut1 = 25., EMuPtCut2 = 15.; 
  }
  else if(DataYear==2017){
    MuonTriggers.push_back("HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8_v");
    ElectronTriggers.push_back("HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_v");
    EMuTriggers.push_back("HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_v");
    EMuTriggers.push_back("HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v");
    MuonPtCut1 = 20., MuonPtCut2 = 10.;
    ElectronPtCut1 = 25., ElectronPtCut2 = 15.;
    EMuPtCut1 = 25., EMuPtCut2 = 15.;
  }
  else if(DataYear==2018){
    MuonTriggers.push_back("HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8_v");
    ElectronTriggers.push_back("HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_v");
    EMuTriggers.push_back("HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_v");
    EMuTriggers.push_back("HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v");
    MuonPtCut1 = 20., MuonPtCut2 = 10.;
    ElectronPtCut1 = 25., ElectronPtCut2 = 15.;
    EMuPtCut1 = 25., EMuPtCut2 = 15.;

    //ElectronTightIDs.pop_back(); ElectronTightIDs.push_back("HEEP2018_dZ"); //JH 
  }

//  cout << "[NonIso::initializeAnalyzer] IsoMuTriggerName = " << IsoMuTriggerName << endl;
//  cout << "[NonIso::initializeAnalyzer TriggerSafePtCut = " << TriggerSafePtCut << endl;

  //==== B-Tagging
  //==== add taggers and WP that you want to use in analysis
  std::vector<JetTagging::Parameters> jtps;
  //==== If you want to use 1a or 2a method,
  jtps.push_back( JetTagging::Parameters(JetTagging::DeepCSV, JetTagging::Loose, JetTagging::incl, JetTagging::comb) );
  jtps.push_back( JetTagging::Parameters(JetTagging::DeepCSV, JetTagging::Medium, JetTagging::incl, JetTagging::comb) );
  //==== set
  mcCorr->SetJetTaggingParameters(jtps); //JH : NOTE This is used in mcCorr->SetupJetTagging() in m.initializeAnalyzerTools();
}

NonIso::~NonIso(){

  //==== Destructor of this Analyzer

}

void NonIso::executeEvent(){

  //================================================================
  //====  Example 1
  //====  Dimuon Z-peak events with two muon IDs, with systematics
  //================================================================

  //==== *IMPORTANT TO SAVE CPU TIME*
  //==== Every GetMuon() funtion first collect ALL MINIAOD muons with GetAllMuons(),
  //==== and then check ID booleans.
  //==== GetAllMuons not only loops over all MINIAOD muons, but also actually CONSTRUCT muon objects for each muons.
  //==== We are now running systematics, and you don't want to do this for every systematic sources
  //==== So, I defined "vector<Muon> AllMuons;" in Analyzers/include/NonIso.h,
  //==== and save muons objects at the very beginning of executeEvent().
  //==== Later, do "SelectMuons(AllMuons, ID, pt, eta)" to get muons with ID cuts
  AllMuons = GetAllMuons();
  AllElectrons = GetAllElectrons();
  AllJets = GetAllJets();
//  AllFatJets = GetAllFatJets();
  AllFatJets = puppiCorr->Correct(GetAllFatJets()); //JH : puppiCorr = new PuppiSoftdropMassCorr(); in the constructor of AnalyzerCore.C; apply correction to fatjet.SDMass(); the total weight = gen correction * reco correction, from SKFlatAnalyzer/data/Run2Legacy_v4/DataYear/PuppiSoftdropMassCorr/puppiCorr.root

  //==== Get L1Prefire reweight
  //==== If data, 1.;
  //==== If MC && DataYear > 2017, 1.;
  //==== If MC && DataYear <= 2017, we have to reweight the event with this value
  //==== I defined "double weight_Prefire;" in Analyzers/include/NonIso.h
//  weight_Prefire = GetPrefireWeight(0);

  AnalyzerParameter param;

  for(unsigned int it_id=0; it_id<ElectronTightIDs.size(); it_id++){
    TString MuonTightID = MuonTightIDs.at(it_id);
    TString MuonLooseID = MuonLooseIDs.at(it_id); 
    TString MuonVetoID  = MuonVetoIDs.at(it_id);
    TString ElectronTightID = ElectronTightIDs.at(it_id);
    TString ElectronLooseID = ElectronLooseIDs.at(it_id);
    TString ElectronVetoID  = ElectronVetoIDs.at(it_id);
    TString FakeRateID = FakeRateIDs.at(it_id);

    param.Clear();

    param.syst_ = AnalyzerParameter::Central;

//    param.Name = MuonID+"_"+"Central";

    // Muon ID
    param.Muon_Tight_ID = MuonTightID;
    param.Muon_Loose_ID = MuonLooseID;
    param.Muon_Veto_ID  = MuonVetoID;
    param.Muon_FR_ID = FakeRateID;     // ID name in histmap_Muon.txt
    param.Muon_FR_Key = "FR_2D"; // histname
    param.Muon_ID_SF_Key = "NUM_TightID_DEN_genTracks";
    param.Muon_ISO_SF_Key = "NUM_TightRelIso_DEN_TightIDandIPCut";
    param.Muon_Trigger_SF_Key = "";
    if(param.Muon_Tight_ID.Contains("SSWW")){
      param.Muon_UsePtCone = false;
    }
    else if(param.Muon_Tight_ID.Contains("HN")){
      param.Muon_UsePtCone = true;
    }

    // Electron ID
    param.Electron_Tight_ID = ElectronTightID;
    param.Electron_Loose_ID = ElectronLooseID;
    param.Electron_Veto_ID  = ElectronVetoID;
    param.Electron_FR_ID = FakeRateID;     // ID name in histmap_Electron.txt
    param.Electron_FR_Key = "AwayJetPt40"; // histname
    param.Electron_ID_SF_Key = "passTightID";
    param.Electron_Trigger_SF_Key = "";
    if(param.Electron_Tight_ID.Contains("SSWW")){
      param.Electron_UsePtCone = false;
    }
    else if(param.Electron_Tight_ID.Contains("HN")){
      param.Electron_UsePtCone = true;
    }

    // Jet ID
    param.Jet_ID = "HNTight"; //JH : pass only POG tight in UL
    //param.FatJet_ID = "HNTight";
    if(DataYear==2016) param.FatJet_ID = "HNTight0p55";
    else param.FatJet_ID = "HNTight0p45"; //JH : TODO

    executeEventFromParameter(param);

/*  if(RunSyst){
      for(int it_syst=1; it_syst<AnalyzerParameter::NSyst; it_syst++){
        param.syst_ = AnalyzerParameter::Syst(it_syst);
        param.Name = MuonID+"_"+"Syst_"+param.GetSystType();
        executeEventFromParameter(param);
      }
    }*/
  }
}

void NonIso::executeEventFromParameter(AnalyzerParameter param){

  TString IDsuffix = "";
  if(param.Muon_Tight_ID.Contains("SSWW")) IDsuffix = "SSWWrep";
  else if(param.Muon_Tight_ID.Contains("HN")) IDsuffix = "HN";
  TString LepCategory = "TT";
  double cutflow_max = 30.;
  int cutflow_bin = 30;
  double weight = 1.;
  double trigger_lumi = 1., dimu_trig_weight = 0., emu_trig_weight = 0.;
  double muon_miniaodP = 0.;
 
  Event ev = GetEvent();

  //=============
  //==== No Cut
  //=============

  if(!IsDATA){
    weight *= weight_norm_1invpb*ev.GetTriggerLumi("Full"); //JH : weight_norm_1invpb = xsec/sumW; Lumi = 35.9, 41.5, 59.7(fb-1) total 137fb-1
    weight *= ev.MCweight(); //JH : gen_weight in MiniAOD
    weight *= GetPrefireWeight(0); //JH : No issue in 2018, otherwise returns L1PrefireReweight_Central in MiniAOD
    weight *= GetPileUpWeight(nPileUp,0); //JH : mcCorr->GetPileUpWeight(N_pileup, syst); mcCorr->GetPileUpWeight2017(N_pileup, syst); NOTE 2018 not yet added.
  } //JH : total weight calculation done.

  //======================
  //==== Copy All Objects
  //======================

  vector<Electron> this_AllElectrons = AllElectrons;
  vector<Muon> this_AllMuons = UseTunePMuon(AllMuons);
  vector<Jet> this_AllJets = AllJets;
  vector<FatJet> this_AllFatJets = AllFatJets;
  vector<Gen> gens = GetGens();

  //==== Then, for each systematic sources
  //==== 1) Smear or scale them
  //==== 2) Then apply ID selections
  //==== This order should be explicitly followed
  //==== Below are all variables for available systematic sources

/*  if(param.syst_ == AnalyzerParameter::Central){

  }
  else if(param.syst_ == AnalyzerParameter::JetResUp){
    this_AllJets = SmearJets( this_AllJets, +1 );
    //this_AllFatJets = SmearFatJets( this_AllFatJets, +1 );
  }
  else if(param.syst_ == AnalyzerParameter::JetResDown){
    this_AllJets = SmearJets( this_AllJets, -1 );
    //this_AllFatJets = SmearFatJets( this_AllFatJets, -1 );
  }
  else if(param.syst_ == AnalyzerParameter::JetEnUp){
    this_AllJets = ScaleJets( this_AllJets, +1 );
    //this_AllFatJets = ScaleFatJets( this_AllFatJets, +1 );
  }
  else if(param.syst_ == AnalyzerParameter::JetEnDown){
    this_AllJets = ScaleJets( this_AllJets, -1 );
    //this_AllFatJets = ScaleFatJets( this_AllFatJets, -1 );
  }
  else if(param.syst_ == AnalyzerParameter::MuonEnUp){
    this_AllMuons = ScaleMuons( this_AllMuons, +1 );
  }
  else if(param.syst_ == AnalyzerParameter::MuonEnDown){
    this_AllMuons = ScaleMuons( this_AllMuons, -1 );
  }
  else if(param.syst_ == AnalyzerParameter::ElectronResUp){
    //this_AllElectrons = SmearElectrons( this_AllElectrons, +1 );
  }
  else if(param.syst_ == AnalyzerParameter::ElectronResDown){
    //this_AllElectrons = SmearElectrons( this_AllElectrons, -1 );
  }
  else if(param.syst_ == AnalyzerParameter::ElectronEnUp){
    //this_AllElectrons = ScaleElectrons( this_AllElectrons, +1 );
  }
  else if(param.syst_ == AnalyzerParameter::ElectronEnDown){
    //this_AllElectrons = ScaleElectrons( this_AllElectrons, -1 );
  }
  else{
    cout << "[NonIso::executeEventFromParameter] Wrong syst" << endl;
    exit(EXIT_FAILURE);
  }*/

  //==================================================
  //==== Then, apply ID selections using this_AllXXX
  //==================================================

  vector<Muon> muons_highpt = SelectMuons(this_AllMuons, "POGHighPt", 10., 2.4);
  vector<Muon> muons_highptmini = SelectMuons(this_AllMuons, "POGHighPtWithLooseMiniIso", 10., 2.4);
  vector<FatJet> fatjets = SelectFatJets(this_AllFatJets, "Test", 150., 2.7);

  //=======================
  //==== Sort in pt-order
  //=======================

  std::sort(muons_highpt.begin(), muons_highpt.end(), PtComparing);
  std::sort(muons_highptmini.begin(), muons_highptmini.end(), PtComparing);
  std::sort(fatjets.begin(), fatjets.end(), PtComparing);

  //==== B-Tagging 
  int Nbjet_loose = 0, Nbjet_medium = 0;
  JetTagging::Parameters jtp_DeepCSV_Loose = JetTagging::Parameters(JetTagging::DeepCSV,
                                                                     JetTagging::Loose,
                                                                     JetTagging::incl, JetTagging::comb);
  JetTagging::Parameters jtp_DeepCSV_Medium = JetTagging::Parameters(JetTagging::DeepCSV,
                                                                     JetTagging::Medium,
                                                                     JetTagging::incl, JetTagging::comb); //JH : Set b-tagging parameters

  //==== method 1a)
  //==== multiply "btagWeight" to the event weight
//  double btagWeight = mcCorr->GetBTaggingReweight_1a(jets, jtp_DeepCSV_Medium);

  //==== method 2a)
  //for(unsigned int ij=0; ij<jets_bcand.size(); ij++){ 
  //  if(mcCorr->IsBTagged_2a(jtp_DeepCSV_Loose, jets_bcand.at(ij))) Nbjet_loose++; 
  //  if(mcCorr->IsBTagged_2a(jtp_DeepCSV_Medium, jets_bcand.at(ij))) Nbjet_medium++; //JH : count Nbjet. NOTE : AN says they used CVSv2 and medium WP.
  //} 

//  FillHist("Nbjet_loose_"+IDsuffix, Nbjet_loose, weight, 5, 0., 5.);
//  FillHist("Nbjet_medium_"+IDsuffix, Nbjet_medium, weight, 5, 0., 5.);

  //===================================
  //==== Set up pTcone, lepton vector
  //===================================

  Particle METv = ev.GetMETVector();
  double MET = METv.Pt();

  //=========================
  //==== Event selections..
  //========================= 

  // Cutflow 1 : No Cuts
  FillHist("dRlt0p8/Nevents", 0.5, weight, 5, 0., 5.);
  FillHist("dRlt0p8/Nevents_unweighted", 0.5, 1., 5, 0., 5.);
  FillHist("dRgt0p8/Nevents", 0.5, weight, 5, 0., 5.);
  FillHist("dRgt0p8/Nevents_unweighted", 0.5, 1., 5, 0., 5.);
  FillHist("dRgt0p8/mini/Nevents", 0.5, weight, 5, 0., 5.);
  FillHist("dRgt0p8/mini/Nevents_unweighted", 0.5, 1., 5, 0., 5.);

  FillHist("Nocut/Number_Mu_highpt", muons_highpt.size(), weight, 10, 0., 10.);
  FillHist("Nocut/Number_Mu_highptmini", muons_highptmini.size(), weight, 10, 0., 10.);
  FillHist("Nocut/Number_Fatjet", fatjets.size(), weight, 10, 0., 10.);
  FillHist("Nocut/MET", MET, weight, 1500, 0., 1500.);
  if(muons_highpt.size()>0){
    FillHist("Nocut/Mu1_highpt_Pt", muons_highpt.at(0).Pt(), weight, 1500, 0., 1500.);
    FillHist("Nocut/Mu1_highpt_Eta", muons_highpt.at(0).Eta(), weight, 50, -2.5, 2.5);
    FillHist("Nocut/Mu1_highpt_RelIso", muons_highpt.at(0).RelIso(), weight, 100, 0., 1.);
    FillHist("Nocut/Mu1_highpt_MiniRelIso", muons_highpt.at(0).MiniRelIso(), weight, 100, 0., 1.);
  }
  if(muons_highptmini.size()>0){
    FillHist("Nocut/Mu1_highptmini_Pt", muons_highptmini.at(0).Pt(), weight, 1500, 0., 1500.);
    FillHist("Nocut/Mu1_highptmini_Eta", muons_highptmini.at(0).Eta(), weight, 50, -2.5, 2.5);
    FillHist("Nocut/Mu1_highptmini_RelIso", muons_highptmini.at(0).RelIso(), weight, 100, 0., 1.);
    FillHist("Nocut/Mu1_highptmini_MiniRelIso", muons_highptmini.at(0).MiniRelIso(), weight, 100, 0., 1.);
  }
  if(fatjets.size()>0){
    FillHist("Nocut/FatJet_Pt", fatjets.at(0).Pt(), weight, 1500, 0., 1500.);
    FillHist("Nocut/FatJet_Eta", fatjets.at(0).Eta(), weight, 100, -5, 5);
    FillHist("Nocut/FatJet_Mass", fatjets.at(0).SDMass(), weight, 1500, 0., 1500.);
    FillHist("Nocut/FatJet_LSF", fatjets.at(0).LSF(), weight, 20, 0., 2.);
  }
  if(muons_highpt.size()>0&&fatjets.size()>0){
    FillHist("Nocut/dR", muons_highpt.at(0).DeltaR(fatjets.at(0)), weight, 50, 0., 5.);
  }
  if(muons_highptmini.size()>0&&fatjets.size()>0){
    FillHist("Nocut/dR2", muons_highptmini.at(0).DeltaR(fatjets.at(0)), weight, 50, 0., 5.);
  }

  if(!ev.PassTrigger(MuonTriggersHighPt)) return;

  // Cutflow 2 : Highpt Muon Trigger
  FillHist("dRlt0p8/Nevents", 1.5, weight, 5, 0., 5.);
  FillHist("dRlt0p8/Nevents_unweighted", 1.5, 1., 5, 0., 5.);
  FillHist("dRgt0p8/Nevents", 1.5, weight, 5, 0., 5.);
  FillHist("dRgt0p8/Nevents_unweighted", 1.5, 1., 5, 0., 5.);
  FillHist("dRgt0p8/mini/Nevents", 1.5, weight, 5, 0., 5.);
  FillHist("dRgt0p8/mini/Nevents_unweighted", 1.5, 1., 5, 0., 5.);

  FillHist("Trig/Number_Mu_highpt", muons_highpt.size(), weight, 10, 0., 10.);
  FillHist("Trig/Number_Mu_highptmini", muons_highptmini.size(), weight, 10, 0., 10.);
  FillHist("Trig/Number_Fatjet", fatjets.size(), weight, 10, 0., 10.);
  FillHist("Trig/MET", MET, weight, 1500, 0., 1500.);
  if(muons_highpt.size()>0){
    FillHist("Trig/Mu1_highpt_Pt", muons_highpt.at(0).Pt(), weight, 1500, 0., 1500.);
    FillHist("Trig/Mu1_highpt_Eta", muons_highpt.at(0).Eta(), weight, 50, -2.5, 2.5);
    FillHist("Trig/Mu1_highpt_RelIso", muons_highpt.at(0).RelIso(), weight, 100, 0., 1.);
    FillHist("Trig/Mu1_highpt_MiniRelIso", muons_highpt.at(0).MiniRelIso(), weight, 100, 0., 1.);
  }
  if(muons_highptmini.size()>0){
    FillHist("Trig/Mu1_highptmini_Pt", muons_highptmini.at(0).Pt(), weight, 1500, 0., 1500.);
    FillHist("Trig/Mu1_highptmini_Eta", muons_highptmini.at(0).Eta(), weight, 50, -2.5, 2.5);
    FillHist("Trig/Mu1_highptmini_RelIso", muons_highptmini.at(0).RelIso(), weight, 100, 0., 1.);
    FillHist("Trig/Mu1_highptmini_MiniRelIso", muons_highptmini.at(0).MiniRelIso(), weight, 100, 0., 1.);
  }
  if(fatjets.size()>0){
    FillHist("Trig/FatJet_Pt", fatjets.at(0).Pt(), weight, 1500, 0., 1500.);
    FillHist("Trig/FatJet_Eta", fatjets.at(0).Eta(), weight, 100, -5, 5);
    FillHist("Trig/FatJet_Mass", fatjets.at(0).SDMass(), weight, 1500, 0., 1500.);
    FillHist("Trig/FatJet_LSF", fatjets.at(0).LSF(), weight, 20, 0., 2.);
  }
  if(muons_highpt.size()>0&&fatjets.size()>0){
    FillHist("Trig/dR", muons_highpt.at(0).DeltaR(fatjets.at(0)), weight, 50, 0., 5.);
  }
  if(muons_highptmini.size()>0&&fatjets.size()>0){
    FillHist("Trig/dR2", muons_highptmini.at(0).DeltaR(fatjets.at(0)), weight, 50, 0., 5.);
  }

  if(muons_highpt.size()==1 && fatjets.size()==1 && MET>100.){
    if(muons_highpt.at(0).DeltaR(fatjets.at(0))<0.8){
      if(fatjets.at(0).LSF()>0.75){
        FillHist("dRlt0p8/Nevents", 2.5, weight, 5, 0., 5.);
        FillHist("dRlt0p8/Nevents_unweighted", 2.5, 1., 5, 0., 5.);
        FillHist("dRlt0p8/Mu_Pt", muons_highpt.at(0).Pt(), weight, 1500, 0., 1500.);
        FillHist("dRlt0p8/Mu_Eta", muons_highpt.at(0).Eta(), weight, 50, -2.5, 2.5);
        FillHist("dRlt0p8/Mu_RelIso", muons_highpt.at(0).RelIso(), weight, 100, 0., 1.);
        FillHist("dRlt0p8/Mu_MiniRelIso", muons_highpt.at(0).MiniRelIso(), weight, 100, 0., 1.);
        FillHist("dRlt0p8/FatJet_Pt", fatjets.at(0).Pt(), weight, 1500, 0., 1500.);
        FillHist("dRlt0p8/FatJet_Eta", fatjets.at(0).Eta(), weight, 100, -5, 5);
        FillHist("dRlt0p8/FatJet_Mass", fatjets.at(0).SDMass(), weight, 1500, 0., 1500.);
        FillHist("dRlt0p8/FatJet_LSF", fatjets.at(0).LSF(), weight, 20, 0., 2.);
        FillHist("dRlt0p8/dR", muons_highpt.at(0).DeltaR(fatjets.at(0)), weight, 50, 0., 5.);
        FillHist("dRlt0p8/MET", MET, weight, 1500, 0., 1500.);
      }
    }
    else{
      FillHist("dRgt0p8/Nevents", 2.5, weight, 5, 0., 5.);
      FillHist("dRgt0p8/Nevents_unweighted", 2.5, 1., 5, 0., 5.);
      FillHist("dRgt0p8/mini/Nevents", 2.5, weight, 5, 0., 5.);
      FillHist("dRgt0p8/mini/Nevents_unweighted", 2.5, 1., 5, 0., 5.);
      FillHist("dRgt0p8/Number_Mu_highptmini", muons_highptmini.size(), weight, 2, 0., 2.);
      FillHist("dRgt0p8/Number_Mu_highpt", muons_highpt.size(), weight, 2, 0., 2.);
      FillHist("dRgt0p8/dR", muons_highpt.at(0).DeltaR(fatjets.at(0)), weight, 50, 0., 5.);
      if(muons_highptmini.size()>0){
        FillHist("dRgt0p8/mini/Nevents", 3.5, weight, 5, 0., 5.);
        FillHist("dRgt0p8/mini/Nevents_unweighted", 3.5, 1., 5, 0., 5.);
        FillHist("dRgt0p8/mini/Number_Mu_highptmini", muons_highptmini.size(), weight, 2, 0., 2.);
        FillHist("dRgt0p8/mini/Number_Mu_highpt", muons_highpt.size(), weight, 2, 0., 2.);
        FillHist("dRgt0p8/mini/Mu_Pt", muons_highptmini.at(0).Pt(), weight, 1500, 0., 1500.);
        FillHist("dRgt0p8/mini/Mu_Eta", muons_highptmini.at(0).Eta(), weight, 50, -2.5, 2.5);
        FillHist("dRgt0p8/mini/Mu_RelIso", muons_highptmini.at(0).RelIso(), weight, 100, 0., 1.);
        FillHist("dRgt0p8/mini/Mu_MiniRelIso", muons_highptmini.at(0).MiniRelIso(), weight, 100, 0., 1.);
        FillHist("dRgt0p8/mini/FatJet_Pt", fatjets.at(0).Pt(), weight, 1500, 0., 1500.);
        FillHist("dRgt0p8/mini/FatJet_Eta", fatjets.at(0).Eta(), weight, 100, -5, 5);
        FillHist("dRgt0p8/mini/FatJet_Mass", fatjets.at(0).SDMass(), weight, 1500, 0., 1500.);
        FillHist("dRgt0p8/mini/FatJet_LSF", fatjets.at(0).LSF(), weight, 20, 0., 2.);
        FillHist("dRgt0p8/mini/dR", muons_highptmini.at(0).DeltaR(fatjets.at(0)), weight, 50, 0., 5.);
        FillHist("dRgt0p8/mini/dR_validation", muons_highpt.at(0).DeltaR(fatjets.at(0)), weight, 50, 0., 5.);
        FillHist("dRgt0p8/mini/MET", MET, weight, 1500, 0., 1500.);
      }
    }
  }

/*
  FillHist(regionsTypeI.at(it_rg)+"/M1500/Number_Events_"+IDsuffix, 11.5, weight, 5, 0., 5.);
  FillHist(regionsTypeI.at(it_rg)+"/M1500/Number_Events_unweighted_"+IDsuffix, 11.5, 1., 5, 0., 5.);

  FillHist(regionsTypeI.at(it_rg)+"/M1500/Number_Jets_"+IDsuffix, jets.size(), weight, 10, 0., 10.);
  FillHist(regionsTypeI.at(it_rg)+"/M1500/Number_BJets_Loose_"+IDsuffix, Nbjet_loose, weight, 10, 0., 10.);
  FillHist(regionsTypeI.at(it_rg)+"/M1500/Number_BJets_Medium_"+IDsuffix, Nbjet_medium, weight, 10, 0., 10.);
  FillHist(regionsTypeI.at(it_rg)+"/M1500/Number_FatJets_"+IDsuffix, fatjets.size(), weight, 10, 0., 10.);
  FillHist(regionsTypeI.at(it_rg)+"/M1500/DiLep_Mass_"+IDsuffix, DiLep.M(), weight, 1500, 0., 1500.);
  FillHist(regionsTypeI.at(it_rg)+"/M1500/Mu1_Pt_"+IDsuffix, muons.at(0).Pt(), weight, 1500, 0., 1500.);
  FillHist(regionsTypeI.at(it_rg)+"/M1500/Mu2_Pt_"+IDsuffix, muons.at(1).Pt(), weight, 1500, 0., 1500.);
  FillHist(regionsTypeI.at(it_rg)+"/M1500/Mu1_Eta_"+IDsuffix, muons.at(0).Eta(), weight, 50, -2.5, 2.5);
  FillHist(regionsTypeI.at(it_rg)+"/M1500/Mu2_Eta_"+IDsuffix, muons.at(1).Eta(), weight, 50, -2.5, 2.5);
  if(jets.size()>0){
    FillHist(regionsTypeI.at(it_rg)+"/M1500/Jet1_Pt_"+IDsuffix, jets.at(0).Pt(), weight, 1500, 0., 1500.);
    FillHist(regionsTypeI.at(it_rg)+"/M1500/Jet1_Eta_"+IDsuffix, jets.at(0).Eta(), weight, 100, -5, 5);
  }
  if(jets.size()>1){
    FillHist(regionsTypeI.at(it_rg)+"/M1500/Jet2_Pt_"+IDsuffix, jets.at(1).Pt(), weight, 1500, 0., 1500.);
    FillHist(regionsTypeI.at(it_rg)+"/M1500/Jet2_Eta_"+IDsuffix, jets.at(1).Eta(), weight, 100, -5, 5);
    FillHist(regionsTypeI.at(it_rg)+"/M1500/DiJet_Mass_"+IDsuffix, DiJet.M(), weight, 3000, 0., 3000.);
  }
  FillHist(regionsTypeI.at(it_rg)+"/M1500/FatJet_Pt_"+IDsuffix, fatjets.at(j3).Pt(), weight, 1500, 0., 1500.);
  FillHist(regionsTypeI.at(it_rg)+"/M1500/FatJet_Eta_"+IDsuffix, fatjets.at(j3).Eta(), weight, 100, -5, 5);
  FillHist(regionsTypeI.at(it_rg)+"/M1500/FatJet_Mass_"+IDsuffix, fatjets.at(j3).SDMass(), weight, 1500, 0., 1500.);
  FillHist(regionsTypeI.at(it_rg)+"/M1500/l1J_Mass_"+IDsuffix, l1J.M(), weight, 2000, 0., 2000.);
  FillHist(regionsTypeI.at(it_rg)+"/M1500/l2J_Mass_"+IDsuffix, l2J.M(), weight, 2000, 0., 2000.);
  FillHist(regionsTypeI.at(it_rg)+"/M1500/MET_"+IDsuffix, MET, weight, 1000, 0., 1000.);
  FillHist(regionsTypeI.at(it_rg)+"/M1500/MET2ST_"+IDsuffix, MET2ST, weight, 1000, 0., 1000.);
  FillHist(regionsTypeI.at(it_rg)+"/M1500/dPhill_"+IDsuffix, dPhi, weight, 32, 0., 3.2);
  FillHist(regionsTypeI.at(it_rg)+"/M1500/HToverPt1_"+IDsuffix, HT/muons.at(0).Pt(), weight, 10, 0., 10.);
*/

}
