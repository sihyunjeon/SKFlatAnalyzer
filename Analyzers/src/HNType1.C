#include "HNType1.h"

HNType1::HNType1(){

}

void HNType1::initializeAnalyzer(){

  //==== if you use "--userflags RunSyst" with SKFlat.py, HasFlag("RunSyst") will return "true"
//  RunSyst = HasFlag("RunSyst");
//  cout << "[HNType1::initializeAnalyzer] RunSyst = " << RunSyst << endl;
  RunFake = HasFlag("RunFake");
  RunCF = HasFlag("RunCF");

  //MuonTightIDs = {"SSWW_tight","HNTightV1"};
  //MuonLooseIDs = {"SSWW_loose","HNLooseV1"};
  //MuonVetoIDs  = {"ISRVeto","ISRVeto"};
  //if(DataYear==2016){
  //  ElectronTightIDs = {"SSWW_tight2016","HNTightV1"};
  //  ElectronLooseIDs = {"SSWW_loose2016","HNLooseV1"};
  //}
  //else{
  //  ElectronTightIDs = {"SSWW_tight","HNTightV1"};
  //  ElectronLooseIDs = {"SSWW_loose","HNLooseV1"};
  //}
  //ElectronVetoIDs  = {"SSWW_loose","ISRVeto"};
  //FakeRateIDs = {"SSWW","HN"}; //JH : NOTE This is used in fakeEst->ReadHistograms() in m.initializeAnalyzerTools() 
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
  //==== I defined "TString IsoMuTriggerName;" and "double TriggerSafePtCut;" in Analyzers/include/HNType1.h 
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

//  cout << "[HNType1::initializeAnalyzer] IsoMuTriggerName = " << IsoMuTriggerName << endl;
//  cout << "[HNType1::initializeAnalyzer TriggerSafePtCut = " << TriggerSafePtCut << endl;

  //==== B-Tagging
  //==== add taggers and WP that you want to use in analysis
  std::vector<JetTagging::Parameters> jtps;
  //==== If you want to use 1a or 2a method,
  jtps.push_back( JetTagging::Parameters(JetTagging::DeepCSV, JetTagging::Loose, JetTagging::incl, JetTagging::comb) );
  jtps.push_back( JetTagging::Parameters(JetTagging::DeepCSV, JetTagging::Medium, JetTagging::incl, JetTagging::comb) );
  //==== set
  mcCorr->SetJetTaggingParameters(jtps); //JH : NOTE This is used in mcCorr->SetupJetTagging() in m.initializeAnalyzerTools();
}

HNType1::~HNType1(){

  //==== Destructor of this Analyzer

}

void HNType1::executeEvent(){

  //================================================================
  //====  Example 1
  //====  Dimuon Z-peak events with two muon IDs, with systematics
  //================================================================

  //==== *IMPORTANT TO SAVE CPU TIME*
  //==== Every GetMuon() funtion first collect ALL MINIAOD muons with GetAllMuons(),
  //==== and then check ID booleans.
  //==== GetAllMuons not only loops over all MINIAOD muons, but also actually CONSTRUCT muon objects for each muons.
  //==== We are now running systematics, and you don't want to do this for every systematic sources
  //==== So, I defined "vector<Muon> AllMuons;" in Analyzers/include/HNType1.h,
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
  //==== I defined "double weight_Prefire;" in Analyzers/include/HNType1.h
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

void HNType1::executeEventFromParameter(AnalyzerParameter param){

  vector<TString> regionsTypeI = {"highSR1", "highSR1_1jet", "highSR2"}; 
  vector<TString> regionsSSWW = {"SR", "SR_inv", "btag", "WZ", "WZb"}; 
  //vector<TString> regionsSM = {"DYmm", "DYee", "DYemu", "TTmm", "TTee", "TTemu", "WZ", "ZG", "WG", "ZZ"}; 
  vector<TString> channels3L = {"mmm", "mme", "mee", "eee"}; //JH : iterate for the number of e
  vector<TString> channels4L = {"mmmm", "mmee", "eeee"}; //JH : iterate for the number of e / 2
  vector<TString> channels;
  if(IsDATA){
    if(DataStream.Contains("DoubleMuon")) channels.push_back("dimu");
    else if(DataStream.Contains("DoubleEG") || DataStream.Contains("EGamma")) channels.push_back("diel");
    else if(DataStream.Contains("MuonEG")) channels.push_back("emu");
  }
  else channels = {"dimu", "diel", "emu"};
  vector<TString> regions = {"fakeCR1", "SR1", "CR1", "SR2", "CR2_inv", "CR2_btag", "CR2_WZ", "CR2_WZb", "SR3", "CR3"};
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
  vector<TString> Pre_labels = {"nocut", "MET", "trig", "2l", "ptcut", "SS", "3lveto", "mll", "Njet"};
  vector<TString> fakeCR2_labels = {"nocut", "MET", "trig", "2l", "ptcut", "SS", "3lveto", "mll", "Njet", "dRll"};

  //=============
  //==== No Cut
  //=============

  if(!IsDATA){
    weight *= weight_norm_1invpb*ev.GetTriggerLumi("Full"); //JH : weight_norm_1invpb = xsec/sumW; Lumi = 35.9, 41.5, 59.7(fb-1) total 137fb-1
    weight *= ev.MCweight(); //JH : gen_weight in MiniAOD
    weight *= GetPrefireWeight(0); //JH : No issue in 2018, otherwise returns L1PrefireReweight_Central in MiniAOD
    weight *= GetPileUpWeight(nPileUp,0); //JH : mcCorr->GetPileUpWeight(N_pileup, syst); mcCorr->GetPileUpWeight2017(N_pileup, syst); NOTE 2018 not yet added.
  } //JH : total weight calculation done.

  // Cutflow 1 : No Cuts
  for(unsigned int it_ch=0; it_ch<channels.size(); it_ch++){
    FillHistLabel(channels.at(it_ch)+"/Pre/Nevents_"+IDsuffix, Pre_labels, "nocut", weight);
    FillHistLabel(channels.at(it_ch)+"/Pre/Nevents_unweighted_"+IDsuffix, Pre_labels, "nocut", 1.);
    FillHistLabel(channels.at(it_ch)+"/fakeCR2/Nevents_"+IDsuffix, fakeCR2_labels, "nocut", weight);
    FillHistLabel(channels.at(it_ch)+"/fakeCR2/Nevents_unweighted_"+IDsuffix, fakeCR2_labels, "nocut", 1.);
  }

  //========================
  //==== MET Filter
  //========================

  if(!PassMETFilter()) return;

  // Cutflow 2 : MET filter
  for(unsigned int it_ch=0; it_ch<channels.size(); it_ch++){
    FillHistLabel(channels.at(it_ch)+"/Pre/Nevents_"+IDsuffix, Pre_labels, "MET", weight);
    FillHistLabel(channels.at(it_ch)+"/Pre/Nevents_unweighted_"+IDsuffix, Pre_labels, "MET", 1.);
    FillHistLabel(channels.at(it_ch)+"/fakeCR2/Nevents_"+IDsuffix, fakeCR2_labels, "MET", weight);
    FillHistLabel(channels.at(it_ch)+"/fakeCR2/Nevents_unweighted_"+IDsuffix, fakeCR2_labels, "MET", 1.);
  }

  //======================
  //==== Copy All Objects
  //======================

  vector<Electron> this_AllElectrons = AllElectrons;
  vector<Muon> this_AllMuons;
  if(param.Muon_Tight_ID.Contains("HighPt")) this_AllMuons = UseTunePMuon(AllMuons);
  else this_AllMuons = AllMuons;
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
    cout << "[HNType1::executeEventFromParameter] Wrong syst" << endl;
    exit(EXIT_FAILURE);
  }*/

  //==================================================
  //==== Then, apply ID selections using this_AllXXX
  //==================================================

  TString MuonID = param.Muon_Tight_ID;
  TString ElectronID = param.Electron_Tight_ID;
  if(RunFake){
    MuonID = param.Muon_Loose_ID;
    ElectronID = param.Electron_Loose_ID;
  }

  vector<Muon> muons = MuonPromptOnly(SelectMuons(this_AllMuons, MuonID, 10., 2.4), gens);
  vector<Muon> muons_veto = SelectMuons(this_AllMuons, param.Muon_Veto_ID, 10., 2.4);
  vector<Electron> electrons = ElectronPromptOnlyHN(SelectElectrons(this_AllElectrons, ElectronID, 10., 2.5), gens);
  vector<Electron> electrons_loose = SelectElectrons(this_AllElectrons, param.Electron_Loose_ID, 10., 2.5);
  vector<Electron> electrons_veto = SelectElectrons(this_AllElectrons, param.Electron_Veto_ID, 10., 2.5); //JH : lepton selection done
  vector<Jet> jets_forward_nolepveto = SelectJetsPileupMVA(SelectJets(this_AllJets, param.Jet_ID, 20., 4.7), "loose"); // JH : we might see how to set pt cut later
  vector<Jet> jets_nolepveto = SelectJets(this_AllJets, param.Jet_ID, 20., 2.7);
  vector<Jet> jets_bcand = SelectJets(this_AllJets, param.Jet_ID, 20., 2.4); //JH : to reject bjets
  vector<FatJet> fatjets_nolepveto = SelectFatJets(this_AllFatJets, param.FatJet_ID, 200., 2.7);

  // Jet, FatJet selection to avoid double counting due to jets matched geometrically with a lepton
  vector<FatJet> fatjets;
  vector<Jet> jets_forward_lepveto;
  vector<Jet> jets_forward;
  vector<Jet> jets_lepveto;
  vector<Jet> jets;
  jets_forward_lepveto.clear();
  jets_forward.clear();
  jets_lepveto.clear();
  jets.clear();
  fatjets.clear();

  fatjets = FatJetsVetoLeptonInside(fatjets_nolepveto, electrons_veto, muons_veto); // 0.8
  jets_forward_lepveto = JetsVetoLeptonInside(jets_forward_nolepveto, electrons_veto, muons_veto); // 0.4
  jets_forward = JetsAwayFromFatJet(jets_forward_lepveto, fatjets); // 1.0
  jets_lepveto = JetsVetoLeptonInside(jets_nolepveto, electrons_veto, muons_veto); // 0.4
  jets = JetsAwayFromFatJet(jets_lepveto, fatjets); // 1.0
  // Jet, FatJet selection done.

///////////////////////////////////////////TEST////////////////////////////////////////////////////
  vector<Jet> jets_forward_noPUID = JetsAwayFromFatJet(JetsVetoLeptonInside(SelectJets(this_AllJets, param.Jet_ID, 20., 4.7), electrons_veto, muons_veto), fatjets);
  vector<Jet> jets_all = JetsAwayFromFatJet(JetsVetoLeptonInside(SelectJets(this_AllJets, param.Jet_ID, 20., 100.), electrons_veto, muons_veto), fatjets);
///////////////////////////////////////////////////////////////////////////////////////////////////

  //=======================
  //==== Sort in pt-order
  //=======================

  std::sort(muons.begin(), muons.end(), PtComparing);
  std::sort(muons_veto.begin(), muons_veto.end(), PtComparing);
  std::sort(electrons.begin(), electrons.end(), PtComparing);
  std::sort(electrons_loose.begin(), electrons_loose.end(), PtComparing);
  std::sort(electrons_veto.begin(), electrons_veto.end(), PtComparing);
  std::sort(jets_forward.begin(), jets_forward.end(), PtComparing);
  std::sort(jets.begin(), jets.end(), PtComparing);
  std::sort(jets_bcand.begin(), jets_bcand.end(), PtComparing);
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
  for(unsigned int ij=0; ij<jets_bcand.size(); ij++){ 
//    double this_discr = jets_bcand.at(ij).GetTaggerResult(JetTagging::DeepCSV);
      //==== No SF
//      if( this_discr > mcCorr->GetJetTaggingCutValue(JetTagging::DeepCSV, JetTagging::Medium) ) NBJets_NoSF++;
    if(mcCorr->IsBTagged_2a(jtp_DeepCSV_Loose, jets_bcand.at(ij))) Nbjet_loose++; 
    if(mcCorr->IsBTagged_2a(jtp_DeepCSV_Medium, jets_bcand.at(ij))) Nbjet_medium++; //JH : count Nbjet. NOTE : AN says they used CVSv2 and medium WP.
  } 

//  FillHist("Nbjet_loose_"+IDsuffix, Nbjet_loose, weight, 5, 0., 5.);
//  FillHist("Nbjet_medium_"+IDsuffix, Nbjet_medium, weight, 5, 0., 5.);

  //===================================
  //==== Set up pTcone, lepton vector
  //===================================

  Particle METv = ev.GetMETVector();
  METv = UpdateMETSmearedJet(METv, jets);
  METv = UpdateMETMuon(METv, muons);
  METv = UpdateMETElectron(METv, electrons);
  double MET = METv.Pt(); // JH : MET propagated

  double Mt = 0.;
  double Mt3l = 0.;
  double ST = 0.;
  double HT = 0.;
  double MET2ST = 0.;
  double MZ = 91.1876;
  double MW = 80.379;
  double muon_recosf = 1.;
  double muon_idsf = 1.;
  double muon_isosf = 1.;
  double muon_trigsf = 1.;
  double ele_idsf = 1.;
  double ele_recosf = 1.;
  int lepton_veto_size = 0;
  double LeptonPtCut1 = 0., LeptonPtCut2 = 0.;
  Particle ZCand, WCand, Wtemp;
  Particle llj, l1j, l2j,  lljj, l1jj, l2jj, l1J, l2J;
  Particle WtagLep, DiLep, DiJet, DiForwardJet, TriLep, ZtagLep1, ZtagLep2, Ztemp, Ztemp1, Ztemp2, Ztemp3, Ztemp4, ZCand1, ZCand2, GammaCand, GammaLep1, GammaLep2;
  int ossf_mass10 = 0;
  
  // Set tight_iso cut & calculate pTcone
  double mu_tight_iso = 0.07;
  double el_tight_iso = 0.;
  double this_ptcone_muon = 0., this_ptcone_electron = 0.;

  // Set pTcone
  for(unsigned int i=0; i<muons.size(); i++){
    this_ptcone_muon = muons.at(i).CalcPtCone(muons.at(i).RelIso(), mu_tight_iso); //JH : CalcPtCone() in Lepton.h; this returns (i) pt for more tightly isolated leptons than the tight_iso, or (ii) pt + pt*(RelIso-tight_iso) which is the proxy for the mother parton's pt -> used for fake estimation
    muons.at(i).SetPtCone(this_ptcone_muon);
  }
  for(unsigned int i=0; i<electrons.size(); i++){
    if(IDsuffix == "HN2016") el_tight_iso = 0.08;
    if(param.Electron_Tight_ID.Contains("HNTight")){ // POG cut-based tight WP
      el_tight_iso = 0.0287+0.506/electrons.at(i).UncorrPt();
      if(fabs(electrons.at(i).scEta()) > 1.479) el_tight_iso = 0.0445+0.963/electrons.at(i).UncorrPt();
    }
    this_ptcone_electron = electrons.at(i).CalcPtCone(electrons.at(i).RelIso(), el_tight_iso);
    electrons.at(i).SetPtCone(this_ptcone_electron);
  }

  if(RunFake){
      //==== Correct MET if RunFake=true, because pT was replaced by pTcone
      METv = UpdateMETFake(METv, electrons, muons);

      muons = MuonUsePtCone(muons);
      electrons = ElectronUsePtCone(electrons);
      std::sort(muons.begin(), muons.end(), PtComparing);
      std::sort(electrons.begin(), electrons.end(), PtComparing);
  }

  //if(muons.size()==2 && electrons.size()==0){
  //  FillHist("Pt_muon1", muons.at(0).Pt(), weight, 1000, 0., 1000.);
  //  FillHist("Pt_muon2", muons.at(1).Pt(), weight, 1000, 0., 1000.);
  //  FillHist("PtCone_muon1", muons.at(0).PtCone(), weight, 1000, 0., 1000.);
  //  FillHist("PtCone_muon2", muons.at(1).PtCone(), weight, 1000, 0., 1000.);
  //}
  //if(muons.size()==0 && electrons.size()==2){
  //  FillHist("Pt_electron1", electrons.at(0).Pt(), weight, 1000, 0., 1000.);
  //  FillHist("Pt_electron2", electrons.at(1).Pt(), weight, 1000, 0., 1000.);
  //  FillHist("PtCone_electron1", electrons.at(0).PtCone(), weight, 1000, 0., 1000.);
  //  FillHist("PtCone_electron2", electrons.at(1).PtCone(), weight, 1000, 0., 1000.);
  //} //JH : Draw lepton pt and ptcone

//  if(electrons.size() > 0) cout << electrons.at(0).PtCone() << endl;

  // Shift electron energy when RunCF=true
  vector<Electron> electrons_beforeShift;
  vector<Electron> electrons_afterShift;
  electrons_beforeShift.clear();
  electrons_afterShift.clear();
  if(RunCF){
    if(muons.size()==0 && electrons.size()==2){
      electrons_beforeShift.push_back(electrons.at(0));
      electrons_beforeShift.push_back(electrons.at(1));
      electrons = ShiftElectronEnergy(electrons, param, true);
      electrons_afterShift.push_back(electrons.at(0));
      electrons_afterShift.push_back(electrons.at(1));
      METv = UpdateMETElectronCF(METv, electrons_beforeShift, electrons_afterShift);
    }
  }

  std::vector<Lepton*> leptons, leptons_minus, leptons_plus, leptons_veto;

  // Define leptons (pT order)
  for(unsigned int i=0; i<muons.size(); i++) leptons.push_back(&muons.at(i));
  for(unsigned int i=0; i<electrons.size(); i++) leptons.push_back(&electrons.at(i));
  std::sort(leptons.begin(), leptons.end(), PtComparingPtr);

  // Define leptons passing veto IDs
  for(unsigned int i=0; i<muons_veto.size(); i++) leptons_veto.push_back(&muons_veto.at(i));
  for(unsigned int i=0; i<electrons_veto.size(); i++) leptons_veto.push_back(&electrons_veto.at(i));

  // leptons (minus, plus charge)
  for(unsigned int i=0; i<muons.size(); i++){
    if(muons.at(i).Charge() < 0) leptons_minus.push_back(&muons.at(i));
    if(muons.at(i).Charge() > 0) leptons_plus.push_back(&muons.at(i));
  }
  for(unsigned int i=0; i<electrons.size(); i++){
    if(electrons.at(i).Charge() < 0) leptons_minus.push_back(&electrons.at(i));
    if(electrons.at(i).Charge() > 0) leptons_plus.push_back(&electrons.at(i));
  }

  lepton_veto_size = leptons_veto.size() - leptons.size();

  // Define HT, ST, MET^2/ST
  for(unsigned int i=0; i<jets_forward.size(); i++) HT += jets_forward.at(i).Pt();
  for(unsigned int i=0; i<jets.size(); i++) ST += jets.at(i).Pt();
  for(unsigned int i=0; i<fatjets.size(); i++) ST += fatjets.at(i).Pt();
  for(unsigned int i=0; i<leptons.size(); i++) ST += leptons.at(i)->Pt();
  ST += MET;
  MET2ST = MET*MET/ST;

  //=========================
  //==== Event selections..
  //========================= 

  // Loop for each channel : it_ch (0,1,2) = (mumu, ee, emu) for MC, it_ch == 0 always for data
  for(unsigned int it_ch=0; it_ch<channels.size(); it_ch++){

    if(channels.at(it_ch)=="dimu"){ LeptonPtCut1 = MuonPtCut1; LeptonPtCut2 = MuonPtCut2; }
    else if(channels.at(it_ch)=="diel"){ LeptonPtCut1 = ElectronPtCut1; LeptonPtCut2 = ElectronPtCut2; }
    else if(channels.at(it_ch)=="emu"){ LeptonPtCut1 = EMuPtCut1; LeptonPtCut2 = EMuPtCut2; }
    if( (channels.at(it_ch).Contains("mu")) && RunCF) continue; //JH : mumu, emu are irrelevant to CF

    // Triggers for each channel
    if(HasFlag("PeriodH")){
      if(channels.at(it_ch)=="dimu" && !ev.PassTrigger(MuonTriggersH)) continue;
      if(channels.at(it_ch)=="diel" && !ev.PassTrigger(ElectronTriggers)) continue;
      if(channels.at(it_ch)=="emu" && !ev.PassTrigger(EMuTriggersH)) continue;
    }
    else{
      if(channels.at(it_ch)=="dimu" && !ev.PassTrigger(MuonTriggers)) continue;
      if(channels.at(it_ch)=="diel" && !ev.PassTrigger(ElectronTriggers)) continue;
      if(channels.at(it_ch)=="emu" && !ev.PassTrigger(EMuTriggers)) continue;
    }

    // Period-dependent trigger weight (only for 2016 MC)
    trigger_lumi = 1., dimu_trig_weight = 0., emu_trig_weight = 0.;
    if(!IsDATA){
      if(DataEra=="2016postVFP"){
        if(channels.at(it_ch)=="dimu"){
          if(ev.PassTrigger(MuonTriggers)) dimu_trig_weight += 8072.032;
          if(ev.PassTrigger(MuonTriggersH)) dimu_trig_weight += 8740.119;
          trigger_lumi = dimu_trig_weight;
        }
        if(channels.at(it_ch)=="diel"){
          trigger_lumi = ev.GetTriggerLumi("Full");
        }
        if(channels.at(it_ch)=="emu"){
          if(ev.PassTrigger(EMuTriggers)) emu_trig_weight += 8072.032;
          if(ev.PassTrigger(EMuTriggersH)) emu_trig_weight += 8740.119;
          trigger_lumi = emu_trig_weight;
        }
      }
      else{
        trigger_lumi = ev.GetTriggerLumi("Full");
      }
    }

    weight = 1.;
    if(!IsDATA){
      weight *= weight_norm_1invpb*trigger_lumi;
      weight *= ev.MCweight();
      weight *= GetPrefireWeight(0);
      weight *= GetPileUpWeight(nPileUp,0);
    } //JH : recalculate total weight for 2016 period dependency.

    // Cutflow 3 : passing dilepton triggers
    FillHistLabel(channels.at(it_ch)+"/Pre/Nevents_"+IDsuffix, Pre_labels, "trig", weight);
    FillHistLabel(channels.at(it_ch)+"/Pre/Nevents_unweighted_"+IDsuffix, Pre_labels, "trig", 1.);
    FillHistLabel(channels.at(it_ch)+"/fakeCR2/Nevents_"+IDsuffix, fakeCR2_labels, "trig", weight);
    FillHistLabel(channels.at(it_ch)+"/fakeCR2/Nevents_unweighted_"+IDsuffix, fakeCR2_labels, "trig", 1.);

    if(channels.at(it_ch)=="dimu"){
      if(!(muons.size()==2 && electrons.size()==0)) continue;
    }
    if(channels.at(it_ch)=="diel"){
      if(!(muons.size()==0 && electrons.size()==2)) continue;
    }
    if(channels.at(it_ch)=="emu"){
      if(!(muons.size()==1 && electrons.size()==1)) continue;
    }

    DiLep = *leptons.at(0) + *leptons.at(1);

    weight = 1., muon_recosf = 1., muon_idsf = 1., muon_isosf = 1., ele_idsf = 1., ele_recosf = 1.;
    // weights for MC
    if(!IsDATA){
      weight *= weight_norm_1invpb*trigger_lumi; //JH : trigger_lumi for period dependency
      weight *= ev.MCweight();
      weight *= GetPrefireWeight(0);
      weight *= GetPileUpWeight(nPileUp,0);

      for(unsigned int i=0; i<muons.size(); i++){
        if(param.Muon_Tight_ID.Contains("HighPt")){
          muon_miniaodP = sqrt( muons.at(i).MiniAODPt()*muons.at(i).MiniAODPt() + muons.at(i).Pz()*muons.at(i).Pz() );
          muon_recosf   = mcCorr->MuonReco_SF("HighPtMuonRecoSF", muons.at(i).Eta(), muon_miniaodP, 0);
          muon_idsf     = mcCorr->MuonID_SF("NUM_HighPtID_DEN_genTracks",  muons.at(i).Eta(), muons.at(i).MiniAODPt(), 0);
          muon_isosf    = mcCorr->MuonISO_SF("NUM_LooseRelTkIso_DEN_HighPtIDandIPCut", muons.at(i).Eta(), muons.at(i).MiniAODPt(), 0);
        }
        else{
          muon_recosf = 1.;
          muon_idsf   = mcCorr->MuonID_SF(param.Muon_Tight_ID, muons.at(i).Eta(), muons.at(i).MiniAODPt(), 0); //JH
          muon_isosf  = 1.;
        }
        weight *= muon_recosf*muon_idsf*muon_isosf; //JH : FIXME no muon iso SF applied
      }
      for(unsigned int j=0; j<electrons.size(); j++){
        ele_recosf = mcCorr->ElectronReco_SF(electrons.at(j).scEta(), electrons.at(j).UncorrPt(), 0);
        if(param.Electron_Tight_ID.Contains("HEEP")){
          ele_idsf   = mcCorr->ElectronID_SF("HEEP", electrons.at(j).scEta(), electrons.at(j).UncorrPt(), 0);
        }
        else ele_idsf = mcCorr->ElectronID_SF(param.Electron_ID_SF_Key, electrons.at(j).scEta(), electrons.at(j).UncorrPt(), 0); // FIXME passTightID for now
        weight *= ele_recosf*ele_idsf; //JH : recalculate total weight applying 2016 trigger lumi dependency && lepton SF
      }
    } //JH : Now total weight including 2016 trigger lumi and lepton SF done && lepton gen-matching (for first 2 leptons only) done

    // weight for fake, CF
    if(RunFake){
      weight *= fakeEst->GetWeight(leptons, param); //JH : fakeEst = new FakeBackgroundEstimator(); in the constructor in AnalyzerCore.C, which is constructed when you call an instance of class analyzer.. and then fakeEst->ReadHistograms() in initialilzeAnalyzerTools() gets histogram(Run2Legacy_v4/DataYear/FakeRate/*.root) from FakeRateIDs in initializeAnalyzer(); then GetWeight() call GetElectronFakeRate which get FR from lepton's pt, eta and calculate FR weight.
//      FillHist("weight_FR", weight, 1., 220, -1.1, 1.1);
    }
    if(RunCF) weight *= GetCFweight(leptons, param, true, 0); //JH : TODO Must look into those GetWeight functions later

    // Cutflow 4 : 2 tight leptons (gen-matched)
    FillHistLabel(channels.at(it_ch)+"/Pre/Nevents_"+IDsuffix, Pre_labels, "2l", weight);
    FillHistLabel(channels.at(it_ch)+"/Pre/Nevents_unweighted_"+IDsuffix, Pre_labels, "2l", 1.);
    FillHistLabel(channels.at(it_ch)+"/fakeCR2/Nevents_"+IDsuffix, fakeCR2_labels, "2l", weight);
    FillHistLabel(channels.at(it_ch)+"/fakeCR2/Nevents_unweighted_"+IDsuffix, fakeCR2_labels, "2l", 1.);

    if(!(leptons.at(0)->Pt()>LeptonPtCut1 && leptons.at(1)->Pt()>LeptonPtCut2)) continue;

    // Cutflow 5 : trigger safe pT cut
    FillHistLabel(channels.at(it_ch)+"/Pre/Nevents_"+IDsuffix, Pre_labels, "ptcut", weight);
    FillHistLabel(channels.at(it_ch)+"/Pre/Nevents_unweighted_"+IDsuffix, Pre_labels, "ptcut", 1.);
    FillHistLabel(channels.at(it_ch)+"/fakeCR2/Nevents_"+IDsuffix, fakeCR2_labels, "ptcut", weight);
    FillHistLabel(channels.at(it_ch)+"/fakeCR2/Nevents_unweighted_"+IDsuffix, fakeCR2_labels, "ptcut", 1.);

    if(!RunCF && leptons.at(0)->Charge()*leptons.at(1)->Charge()<0) continue;
    if(RunCF && leptons.at(0)->Charge()*leptons.at(1)->Charge()>0) continue;

    // Cutflow 6 : same-sign (oppsite-sign when RunCF=true)
    FillHistLabel(channels.at(it_ch)+"/Pre/Nevents_"+IDsuffix, Pre_labels, "SS", weight);
    FillHistLabel(channels.at(it_ch)+"/Pre/Nevents_unweighted_"+IDsuffix, Pre_labels, "SS", 1.);
    FillHistLabel(channels.at(it_ch)+"/fakeCR2/Nevents_"+IDsuffix, fakeCR2_labels, "SS", weight);
    FillHistLabel(channels.at(it_ch)+"/fakeCR2/Nevents_unweighted_"+IDsuffix, fakeCR2_labels, "SS", 1.);

    if(lepton_veto_size > 0) continue;

    // Cutflow 7 : veto 3rd leptons using veto ID
    FillHistLabel(channels.at(it_ch)+"/Pre/Nevents_"+IDsuffix, Pre_labels, "3lveto", weight);
    FillHistLabel(channels.at(it_ch)+"/Pre/Nevents_unweighted_"+IDsuffix, Pre_labels, "3lveto", 1.);
    FillHistLabel(channels.at(it_ch)+"/fakeCR2/Nevents_"+IDsuffix, fakeCR2_labels, "3lveto", weight);
    FillHistLabel(channels.at(it_ch)+"/fakeCR2/Nevents_unweighted_"+IDsuffix, fakeCR2_labels, "3lveto", 1.);

    if(!(DiLep.M() > 10.)) continue;
    if(channels.at(it_ch)=="diel" && IsOnZ(DiLep.M(), 15.)) continue;

    // Cutflow 8 : m(ll) > 10 GeV, |m(ll)-m(Z)| > 15 GeV for ee 
    FillHistLabel(channels.at(it_ch)+"/Pre/Nevents_"+IDsuffix, Pre_labels, "mll", weight);
    FillHistLabel(channels.at(it_ch)+"/Pre/Nevents_unweighted_"+IDsuffix, Pre_labels, "mll", 1.);
    FillHistLabel(channels.at(it_ch)+"/fakeCR2/Nevents_"+IDsuffix, fakeCR2_labels, "mll", weight);
    FillHistLabel(channels.at(it_ch)+"/fakeCR2/Nevents_unweighted_"+IDsuffix, fakeCR2_labels, "mll", 1.);

    // Lepton categories for the fake background
    if(channels.at(it_ch)=="dimu"){
      if(muons.at(0).PassID(param.Muon_Tight_ID) && !(muons.at(1).PassID(param.Muon_Tight_ID))) LepCategory = "TL";
      if(!(muons.at(0).PassID(param.Muon_Tight_ID)) && muons.at(1).PassID(param.Muon_Tight_ID)) LepCategory = "LT";
      if(!(muons.at(1).PassID(param.Muon_Tight_ID)) && !(muons.at(0).PassID(param.Muon_Tight_ID))) LepCategory = "LL";
    }
    else if(channels.at(it_ch)=="diel"){
      if(electrons.at(0).PassID(param.Electron_Tight_ID) && !(electrons.at(1).PassID(param.Electron_Tight_ID))) LepCategory = "TL";
      if(!(electrons.at(0).PassID(param.Electron_Tight_ID)) && electrons.at(1).PassID(param.Electron_Tight_ID)) LepCategory = "LT";
      if(!(electrons.at(0).PassID(param.Electron_Tight_ID)) && !(electrons.at(1).PassID(param.Electron_Tight_ID))) LepCategory = "LL";
    }
    else{
      if(muons.at(0).Pt() > electrons.at(0).Pt()){
        if(muons.at(0).PassID(param.Muon_Tight_ID) && !(electrons.at(0).PassID(param.Electron_Tight_ID))) LepCategory = "TL";
        if(!(muons.at(0).PassID(param.Muon_Tight_ID)) && electrons.at(0).PassID(param.Electron_Tight_ID)) LepCategory = "LT";
        if(!(muons.at(0).PassID(param.Muon_Tight_ID)) && !(electrons.at(0).PassID(param.Electron_Tight_ID))) LepCategory = "LL";
      }
      else{
        if(electrons.at(0).PassID(param.Electron_Tight_ID) && !(muons.at(0).PassID(param.Muon_Tight_ID))) LepCategory = "TL";
        if(!(electrons.at(0).PassID(param.Electron_Tight_ID)) && muons.at(0).PassID(param.Muon_Tight_ID)) LepCategory = "LT";
        if(!(electrons.at(0).PassID(param.Electron_Tight_ID)) && !(muons.at(0).PassID(param.Muon_Tight_ID))) LepCategory = "LL";
      }
    }

    // non-prompt CR2 : no jets && same-sign back-to-back 2 leptons
    if(jets_forward.size()+fatjets.size()==0 && Nbjet_medium==0){

      // Cutflow 9 : jet requirement for non-prompt CR2 
      FillHistLabel(channels.at(it_ch)+"/fakeCR2/Nevents_"+IDsuffix, fakeCR2_labels, "Njet", weight);
      FillHistLabel(channels.at(it_ch)+"/fakeCR2/Nevents_unweighted_"+IDsuffix, fakeCR2_labels, "Njet", 1.);

      if(!(leptons.at(0)->DeltaR(*leptons.at(1)) > 2.5)) continue;
      FillHistLabel(channels.at(it_ch)+"/fakeCR2/Nevents_"+IDsuffix, fakeCR2_labels, "dRll", weight);
      FillHistLabel(channels.at(it_ch)+"/fakeCR2/Nevents_unweighted_"+IDsuffix, fakeCR2_labels, "dRll", 1.);
      FillHist(channels.at(it_ch)+"/fakeCR2/Njets_"+IDsuffix, jets.size(), weight, 10, 0., 10.);
      FillHist(channels.at(it_ch)+"/fakeCR2/Nbjets_Loose_"+IDsuffix, Nbjet_loose, weight, 10, 0., 10.);
      FillHist(channels.at(it_ch)+"/fakeCR2/Nbjets_Medium_"+IDsuffix, Nbjet_medium, weight, 10, 0., 10.);
      FillHist(channels.at(it_ch)+"/fakeCR2/Nfatjets_"+IDsuffix, fatjets.size(), weight, 10, 0., 10.);
      FillHist(channels.at(it_ch)+"/fakeCR2/DiLep_Mass_"+IDsuffix, DiLep.M(), weight, 1000, 0., 1000.);
      FillHist(channels.at(it_ch)+"/fakeCR2/Lep1_Pt_"+IDsuffix, leptons.at(0)->Pt(), weight, 1000, 0., 1000.);
      FillHist(channels.at(it_ch)+"/fakeCR2/Lep2_Pt_"+IDsuffix, leptons.at(1)->Pt(), weight, 1000, 0., 1000.);
      FillHist(channels.at(it_ch)+"/fakeCR2/Lep1_Eta_"+IDsuffix, leptons.at(0)->Eta(), weight, 50, -2.5, 2.5);
      FillHist(channels.at(it_ch)+"/fakeCR2/Lep2_Eta_"+IDsuffix, leptons.at(1)->Eta(), weight, 50, -2.5, 2.5);
      FillHist(channels.at(it_ch)+"/fakeCR2/MET_"+IDsuffix, MET, weight, 1000, 0., 1000.);
      FillHist(channels.at(it_ch)+"/fakeCR2/MET2ST_"+IDsuffix, MET2ST, weight, 1000, 0., 1000.);

      if(RunFake){
        FillHist(channels.at(it_ch)+"/fakeCR2/"+LepCategory+"/Nevents_"+IDsuffix, 0.5, weight, cutflow_bin, 0., cutflow_max);
        FillHist(channels.at(it_ch)+"/fakeCR2/"+LepCategory+"/Njets_"+IDsuffix, jets.size(), weight, 10, 0., 10.);
        FillHist(channels.at(it_ch)+"/fakeCR2/"+LepCategory+"/DiLep_Mass_"+IDsuffix, DiLep.M(), weight, 1000, 0., 1000.);
        FillHist(channels.at(it_ch)+"/fakeCR2/"+LepCategory+"/Lep1_Pt_"+IDsuffix, leptons.at(0)->Pt(), weight, 1000, 0., 1000.);
        FillHist(channels.at(it_ch)+"/fakeCR2/"+LepCategory+"/Lep2_Pt_"+IDsuffix, leptons.at(1)->Pt(), weight, 1000, 0., 1000.);
        FillHist(channels.at(it_ch)+"/fakeCR2/"+LepCategory+"/Lep1_Eta_"+IDsuffix, leptons.at(0)->Eta(), weight, 50, -2.5, 2.5);
        FillHist(channels.at(it_ch)+"/fakeCR2/"+LepCategory+"/Lep2_Eta_"+IDsuffix, leptons.at(1)->Eta(), weight, 50, -2.5, 2.5);
        FillHist(channels.at(it_ch)+"/fakeCR2/"+LepCategory+"/MET_"+IDsuffix, MET, weight, 1000, 0., 1000.);
        FillHist(channels.at(it_ch)+"/fakeCR2/"+LepCategory+"/MET2ST_"+IDsuffix, MET2ST, weight, 1000, 0., 1000.);

        FillHist(channels.at(it_ch)+"/fakeCR2/"+LepCategory+"/Nevents_unweighted_"+IDsuffix, 0.5, 1., cutflow_bin, 0., cutflow_max);
        FillHist(channels.at(it_ch)+"/fakeCR2/"+LepCategory+"/Njets_unweighted_"+IDsuffix, jets.size(), 1., 10, 0., 10.);
        FillHist(channels.at(it_ch)+"/fakeCR2/"+LepCategory+"/DiLep_Mass_unweighted_"+IDsuffix, DiLep.M(), 1., 1000, 0., 1000.);
        FillHist(channels.at(it_ch)+"/fakeCR2/"+LepCategory+"/Lep1_Pt_unweighted_"+IDsuffix, leptons.at(0)->Pt(), 1., 1000, 0., 1000.);
        FillHist(channels.at(it_ch)+"/fakeCR2/"+LepCategory+"/Lep2_Pt_unweighted_"+IDsuffix, leptons.at(1)->Pt(), 1., 1000, 0., 1000.);
        FillHist(channels.at(it_ch)+"/fakeCR2/"+LepCategory+"/Lep1_Eta_unweighted_"+IDsuffix, leptons.at(0)->Eta(), 1., 50, -2.5, 2.5);
        FillHist(channels.at(it_ch)+"/fakeCR2/"+LepCategory+"/Lep2_Eta_unweighted_"+IDsuffix, leptons.at(1)->Eta(), 1., 50, -2.5, 2.5);
        FillHist(channels.at(it_ch)+"/fakeCR2/"+LepCategory+"/MET_unweighted_"+IDsuffix, MET, 1., 1000, 0., 1000.);
        FillHist(channels.at(it_ch)+"/fakeCR2/"+LepCategory+"/MET2ST_unweighted_"+IDsuffix, MET2ST, 1., 1000, 0., 1000.);
      }
    }
    // what if we just require no central jets?
    if(jets.size()+fatjets.size()==0 && Nbjet_medium==0){
      FillHistLabel(channels.at(it_ch)+"/fakeCR3/Nevents_"+IDsuffix, fakeCR2_labels, "Njet", weight);
      FillHistLabel(channels.at(it_ch)+"/fakeCR3/Nevents_unweighted_"+IDsuffix, fakeCR2_labels, "Njet", 1.);

      if(!(leptons.at(0)->DeltaR(*leptons.at(1)) > 2.5)) continue;
      FillHistLabel(channels.at(it_ch)+"/fakeCR3/Nevents_"+IDsuffix, fakeCR2_labels, "dRll", weight);
      FillHistLabel(channels.at(it_ch)+"/fakeCR3/Nevents_unweighted_"+IDsuffix, fakeCR2_labels, "dRll", 1.);
      FillHist(channels.at(it_ch)+"/fakeCR3/Njets_"+IDsuffix, jets.size(), weight, 10, 0., 10.);
      FillHist(channels.at(it_ch)+"/fakeCR3/Nbjets_Loose_"+IDsuffix, Nbjet_loose, weight, 10, 0., 10.);
      FillHist(channels.at(it_ch)+"/fakeCR3/Nbjets_Medium_"+IDsuffix, Nbjet_medium, weight, 10, 0., 10.);
      FillHist(channels.at(it_ch)+"/fakeCR3/Nfatjets_"+IDsuffix, fatjets.size(), weight, 10, 0., 10.);
      FillHist(channels.at(it_ch)+"/fakeCR3/DiLep_Mass_"+IDsuffix, DiLep.M(), weight, 1000, 0., 1000.);
      FillHist(channels.at(it_ch)+"/fakeCR3/Lep1_Pt_"+IDsuffix, leptons.at(0)->Pt(), weight, 1000, 0., 1000.);
      FillHist(channels.at(it_ch)+"/fakeCR3/Lep2_Pt_"+IDsuffix, leptons.at(1)->Pt(), weight, 1000, 0., 1000.);
      FillHist(channels.at(it_ch)+"/fakeCR3/Lep1_Eta_"+IDsuffix, leptons.at(0)->Eta(), weight, 50, -2.5, 2.5);
      FillHist(channels.at(it_ch)+"/fakeCR3/Lep2_Eta_"+IDsuffix, leptons.at(1)->Eta(), weight, 50, -2.5, 2.5);
      FillHist(channels.at(it_ch)+"/fakeCR3/MET_"+IDsuffix, MET, weight, 1000, 0., 1000.);
      FillHist(channels.at(it_ch)+"/fakeCR3/MET2ST_"+IDsuffix, MET2ST, weight, 1000, 0., 1000.);

      if(RunFake){
        FillHist(channels.at(it_ch)+"/fakeCR3/"+LepCategory+"/Nevents_"+IDsuffix, 0.5, weight, cutflow_bin, 0., cutflow_max);
        FillHist(channels.at(it_ch)+"/fakeCR3/"+LepCategory+"/Njets_"+IDsuffix, jets.size(), weight, 10, 0., 10.);
        FillHist(channels.at(it_ch)+"/fakeCR3/"+LepCategory+"/DiLep_Mass_"+IDsuffix, DiLep.M(), weight, 1000, 0., 1000.);
        FillHist(channels.at(it_ch)+"/fakeCR3/"+LepCategory+"/Lep1_Pt_"+IDsuffix, leptons.at(0)->Pt(), weight, 1000, 0., 1000.);
        FillHist(channels.at(it_ch)+"/fakeCR3/"+LepCategory+"/Lep2_Pt_"+IDsuffix, leptons.at(1)->Pt(), weight, 1000, 0., 1000.);
        FillHist(channels.at(it_ch)+"/fakeCR3/"+LepCategory+"/Lep1_Eta_"+IDsuffix, leptons.at(0)->Eta(), weight, 50, -2.5, 2.5);
        FillHist(channels.at(it_ch)+"/fakeCR3/"+LepCategory+"/Lep2_Eta_"+IDsuffix, leptons.at(1)->Eta(), weight, 50, -2.5, 2.5);
        FillHist(channels.at(it_ch)+"/fakeCR3/"+LepCategory+"/MET_"+IDsuffix, MET, weight, 1000, 0., 1000.);
        FillHist(channels.at(it_ch)+"/fakeCR3/"+LepCategory+"/MET2ST_"+IDsuffix, MET2ST, weight, 1000, 0., 1000.);

        FillHist(channels.at(it_ch)+"/fakeCR3/"+LepCategory+"/Nevents_unweighted_"+IDsuffix, 0.5, 1., cutflow_bin, 0., cutflow_max);
        FillHist(channels.at(it_ch)+"/fakeCR3/"+LepCategory+"/Njets_unweighted_"+IDsuffix, jets.size(), 1., 10, 0., 10.);
        FillHist(channels.at(it_ch)+"/fakeCR3/"+LepCategory+"/DiLep_Mass_unweighted_"+IDsuffix, DiLep.M(), 1., 1000, 0., 1000.);
        FillHist(channels.at(it_ch)+"/fakeCR3/"+LepCategory+"/Lep1_Pt_unweighted_"+IDsuffix, leptons.at(0)->Pt(), 1., 1000, 0., 1000.);
        FillHist(channels.at(it_ch)+"/fakeCR3/"+LepCategory+"/Lep2_Pt_unweighted_"+IDsuffix, leptons.at(1)->Pt(), 1., 1000, 0., 1000.);
        FillHist(channels.at(it_ch)+"/fakeCR3/"+LepCategory+"/Lep1_Eta_unweighted_"+IDsuffix, leptons.at(0)->Eta(), 1., 50, -2.5, 2.5);
        FillHist(channels.at(it_ch)+"/fakeCR3/"+LepCategory+"/Lep2_Eta_unweighted_"+IDsuffix, leptons.at(1)->Eta(), 1., 50, -2.5, 2.5);
        FillHist(channels.at(it_ch)+"/fakeCR3/"+LepCategory+"/MET_unweighted_"+IDsuffix, MET, 1., 1000, 0., 1000.);
        FillHist(channels.at(it_ch)+"/fakeCR3/"+LepCategory+"/MET2ST_unweighted_"+IDsuffix, MET2ST, 1., 1000, 0., 1000.);
      }
    }

    if(!( fatjets.size()>0 || jets_forward.size()>0 )) continue; //JH : new preselection

    // Cutflow 9 : jet requirement for preselection
    FillHistLabel(channels.at(it_ch)+"/Pre/Nevents_"+IDsuffix, Pre_labels, "Njet", weight);
    FillHistLabel(channels.at(it_ch)+"/Pre/Nevents_unweighted_"+IDsuffix, Pre_labels, "Njet", 1.);
 
    double avgEta, dEta, max_zep;
    if(jets.size()>1) DiJet = jets.at(0)+jets.at(1);
    if(jets_forward.size()>1){
      DiForwardJet = jets_forward.at(0)+jets_forward.at(1);
      avgEta = 0.5*(jets_forward.at(0).Eta()+jets_forward.at(1).Eta());
      dEta = fabs(jets_forward.at(0).Eta()-jets_forward.at(1).Eta());
      max_zep = std::max(fabs(leptons.at(0)->Eta()-avgEta),fabs(leptons.at(1)->Eta()-avgEta))/dEta;
    }

    double dPhill = fabs(leptons.at(0)->DeltaPhi(*leptons.at(1)));
    double HToverPt1 = HT/leptons.at(0)->Pt();

    FillHist(channels.at(it_ch)+"/Pre/Njets_forward_"+IDsuffix, jets_forward.size(), weight, 10, 0., 10.);
    FillHist(channels.at(it_ch)+"/Pre/Njets_"+IDsuffix, jets.size(), weight, 10, 0., 10.);
    FillHist(channels.at(it_ch)+"/Pre/Nfatjets_"+IDsuffix, fatjets.size(), weight, 10, 0., 10.);
    FillHist(channels.at(it_ch)+"/Pre/DiLep_Mass_"+IDsuffix, DiLep.M(), weight, 1500, 0., 1500.);
    FillHist(channels.at(it_ch)+"/Pre/Lep1_Pt_"+IDsuffix, leptons.at(0)->Pt(), weight, 1500, 0., 1500.);
    FillHist(channels.at(it_ch)+"/Pre/Lep2_Pt_"+IDsuffix, leptons.at(1)->Pt(), weight, 1500, 0., 1500.);
    FillHist(channels.at(it_ch)+"/Pre/Lep1_Eta_"+IDsuffix, leptons.at(0)->Eta(), weight, 50, -2.5, 2.5);
    FillHist(channels.at(it_ch)+"/Pre/Lep2_Eta_"+IDsuffix, leptons.at(1)->Eta(), weight, 50, -2.5, 2.5);
    if(jets_forward.size()>0){
      FillHist(channels.at(it_ch)+"/Pre/ForwardJet1_Pt_"+IDsuffix, jets_forward.at(0).Pt(), weight, 1500, 0., 1500.);
      FillHist(channels.at(it_ch)+"/Pre/ForwardJet1_Eta_"+IDsuffix, jets_forward.at(0).Eta(), weight, 100, -5, 5);
    } 
    if(jets_forward.size()>1){
      FillHist(channels.at(it_ch)+"/Pre/ForwardJet2_Pt_"+IDsuffix, jets_forward.at(1).Pt(), weight, 1500, 0., 1500.);
      FillHist(channels.at(it_ch)+"/Pre/ForwardJet2_Eta_"+IDsuffix, jets_forward.at(1).Eta(), weight, 100, -5, 5);
      FillHist(channels.at(it_ch)+"/Pre/DiForwardJet_Mass_"+IDsuffix, DiForwardJet.M(), weight, 3000, 0., 3000.);
      FillHist(channels.at(it_ch)+"/Pre/Zep_"+IDsuffix, max_zep, weight, 150, 0., 1.5);
      FillHist(channels.at(it_ch)+"/Pre/dEtajj_"+IDsuffix, dEta, weight, 100, 0., 10.);
    }
    if(jets.size()>0){
      FillHist(channels.at(it_ch)+"/Pre/Jet1_Pt_"+IDsuffix, jets.at(0).Pt(), weight, 1500, 0., 1500.);
      FillHist(channels.at(it_ch)+"/Pre/Jet1_Eta_"+IDsuffix, jets.at(0).Eta(), weight, 100, -5, 5);
    }
    if(jets.size()>1){
      FillHist(channels.at(it_ch)+"/Pre/Jet2_Pt_"+IDsuffix, jets.at(1).Pt(), weight, 1500, 0., 1500.);
      FillHist(channels.at(it_ch)+"/Pre/Jet2_Eta_"+IDsuffix, jets.at(1).Eta(), weight, 100, -5, 5);
      FillHist(channels.at(it_ch)+"/Pre/DiJet_Mass_"+IDsuffix, DiJet.M(), weight, 3000, 0., 3000.);
    }
    if(fatjets.size()>0){
      FillHist(channels.at(it_ch)+"/Pre/FatJet1_Pt_"+IDsuffix, fatjets.at(0).Pt(), weight, 1500, 0., 1500.);
      FillHist(channels.at(it_ch)+"/Pre/FatJet1_Eta_"+IDsuffix, fatjets.at(0).Eta(), weight, 100, -5, 5);
    }
    if(fatjets.size()>1){
      FillHist(channels.at(it_ch)+"/Pre/FatJet2_Pt_"+IDsuffix, fatjets.at(1).Pt(), weight, 1500, 0., 1500.);
      FillHist(channels.at(it_ch)+"/Pre/FatJet2_Eta_"+IDsuffix, fatjets.at(1).Eta(), weight, 100, -5, 5);
    }
    FillHist(channels.at(it_ch)+"/Pre/MET_"+IDsuffix, MET, weight, 1000, 0., 1000.);
    FillHist(channels.at(it_ch)+"/Pre/MET2ST_"+IDsuffix, MET2ST, weight, 1000, 0., 1000.);
    FillHist(channels.at(it_ch)+"/Pre/dPhill_"+IDsuffix, dPhill, weight, 32, 0., 3.2);
    FillHist(channels.at(it_ch)+"/Pre/HToverPt1_"+IDsuffix, HToverPt1, weight, 20, 0., 10.);

    // non-prompt CR1 : SS 2 leptons with b-tagged jets
    vector<TString> fakeCR1_labels = {"Pre", "Nbjet"};
    FillHistLabel(channels.at(it_ch)+"/fakeCR1/Nevents_"+IDsuffix, fakeCR1_labels, "Pre", weight);
    FillHistLabel(channels.at(it_ch)+"/fakeCR1/Nevents_unweighted_"+IDsuffix, fakeCR1_labels, "Pre", 1.);

    if(Nbjet_medium > 0){
      FillHistLabel(channels.at(it_ch)+"/fakeCR1/Nevents_"+IDsuffix, fakeCR1_labels, "Nbjet", weight);
      FillHistLabel(channels.at(it_ch)+"/fakeCR1/Nevents_unweighted_"+IDsuffix, fakeCR1_labels, "Nbjet", 1.);
      FillHist(channels.at(it_ch)+"/fakeCR1/DiLep_Mass_"+IDsuffix, DiLep.M(), weight, 1000, 0., 1000.);
      FillHist(channels.at(it_ch)+"/fakeCR1/DiLep_Pt_"+IDsuffix, DiLep.Pt(), weight, 1000, 0., 1000.);
      FillHist(channels.at(it_ch)+"/fakeCR1/Lep1_Pt_"+IDsuffix, leptons.at(0)->Pt(), weight, 1000, 0., 1000.);
      FillHist(channels.at(it_ch)+"/fakeCR1/Lep2_Pt_"+IDsuffix, leptons.at(1)->Pt(), weight, 1000, 0., 1000.);
      FillHist(channels.at(it_ch)+"/fakeCR1/Lep1_Eta_"+IDsuffix, leptons.at(0)->Eta(), weight, 50, -2.5, 2.5);
      FillHist(channels.at(it_ch)+"/fakeCR1/Lep2_Eta_"+IDsuffix, leptons.at(1)->Eta(), weight, 50, -2.5, 2.5);
      FillHist(channels.at(it_ch)+"/fakeCR1/MET_"+IDsuffix, MET, weight, 1000, 0., 1000.);
      FillHist(channels.at(it_ch)+"/fakeCR1/MET2ST_"+IDsuffix, MET2ST, weight, 1000, 0., 1000.);

      if(RunFake){
        FillHist(channels.at(it_ch)+"/fakeCR1/"+LepCategory+"/Nevents_"+IDsuffix, 0.5, weight, cutflow_bin, 0., cutflow_max);
        FillHist(channels.at(it_ch)+"/fakeCR1/"+LepCategory+"/DiLep_Mass_"+IDsuffix, DiLep.M(), weight, 1000, 0., 1000.);
        FillHist(channels.at(it_ch)+"/fakeCR1/"+LepCategory+"/DiLep_Pt_"+IDsuffix, DiLep.Pt(), weight, 1000, 0., 1000.);
        FillHist(channels.at(it_ch)+"/fakeCR1/"+LepCategory+"/Lep1_Pt_"+IDsuffix, leptons.at(0)->Pt(), weight, 1000, 0., 1000.);
        FillHist(channels.at(it_ch)+"/fakeCR1/"+LepCategory+"/Lep2_Pt_"+IDsuffix, leptons.at(1)->Pt(), weight, 1000, 0., 1000.);
        FillHist(channels.at(it_ch)+"/fakeCR1/"+LepCategory+"/Lep1_Eta_"+IDsuffix, leptons.at(0)->Eta(), weight, 50, -2.5, 2.5);
        FillHist(channels.at(it_ch)+"/fakeCR1/"+LepCategory+"/Lep2_Eta_"+IDsuffix, leptons.at(1)->Eta(), weight, 50, -2.5, 2.5);
        FillHist(channels.at(it_ch)+"/fakeCR1/"+LepCategory+"/MET_"+IDsuffix, MET, weight, 1000, 0., 1000.);
        FillHist(channels.at(it_ch)+"/fakeCR1/"+LepCategory+"/MET2ST_"+IDsuffix, MET2ST, weight, 1000, 0., 1000.);

        FillHist(channels.at(it_ch)+"/fakeCR1/"+LepCategory+"/Nevents_unweighted_"+IDsuffix, 0.5, 1., cutflow_bin, 0., cutflow_max);
        FillHist(channels.at(it_ch)+"/fakeCR1/"+LepCategory+"/DiLep_Mass_unweighted_"+IDsuffix, DiLep.M(), 1., 1000, 0., 1000.);
        FillHist(channels.at(it_ch)+"/fakeCR1/"+LepCategory+"/DiLep_Pt_unweighted_"+IDsuffix, DiLep.Pt(), 1., 1000, 0., 1000.);
        FillHist(channels.at(it_ch)+"/fakeCR1/"+LepCategory+"/Lep1_Pt_unweighted_"+IDsuffix, leptons.at(0)->Pt(), 1., 1000, 0., 1000.);
        FillHist(channels.at(it_ch)+"/fakeCR1/"+LepCategory+"/Lep2_Pt_unweighted_"+IDsuffix, leptons.at(1)->Pt(), 1., 1000, 0., 1000.);
        FillHist(channels.at(it_ch)+"/fakeCR1/"+LepCategory+"/Lep1_Eta_unweighted_"+IDsuffix, leptons.at(0)->Eta(), 1., 50, -2.5, 2.5);
        FillHist(channels.at(it_ch)+"/fakeCR1/"+LepCategory+"/Lep2_Eta_unweighted_"+IDsuffix, leptons.at(1)->Eta(), 1., 50, -2.5, 2.5);
        FillHist(channels.at(it_ch)+"/fakeCR1/"+LepCategory+"/MET_unweighted_"+IDsuffix, MET, 1., 1000, 0., 1000.);
        FillHist(channels.at(it_ch)+"/fakeCR1/"+LepCategory+"/MET2ST_unweighted_"+IDsuffix, MET2ST, 1., 1000, 0., 1000.);
      }
    }

    // Start signal region selection
    vector<TString> SR_summary_labels = {"Pre", "SR1_pass", "SR1_fail", "SR2_pass", "SR2_fail", "SR3_pass", "SR3_fail", "SR3_forward_pass", "SR3_forward_fail",
                                         "SR3_forward_mW_pass", "SR3_forward_mW_fail", "SR3_forward_mW_HToverPt1_pass", "SR3_forward_mW_HToverPt1_fail",
                                         "SR3_forward_mW_HToverPt0p5_pass", "SR3_forward_mW_HToverPt0p5_fail"};
    FillHistLabel(channels.at(it_ch)+"/SR_Central_summary_"+IDsuffix, SR_summary_labels, "Pre", weight);
    FillHistLabel(channels.at(it_ch)+"/SR_Central_summary_unweighted_"+IDsuffix, SR_summary_labels, "Pre", 1.);

    if(fatjets.size()>0){ //JH : at least 1 fatjet --> SR1, CR1
      vector<TString> SR1_opts = {"Central", "bveto_loose", "mW50to150", "MET2ST_20"};
      vector<TString> SR1_labels;
      vector<double> SR1_cuts;
      for(int i=0; i<SR1_opts.size(); i++){
        if(SR1_opts[i]=="Central"){
          SR1_labels = {"Nfatjet", "bveto", "mW", "MET2ST"};
          SR1_cuts = {Nbjet_medium, 40., 130., 15.};
          if(RunSR1(channels.at(it_ch), SR1_opts[i], IDsuffix, leptons, jets, jets_forward, fatjets, MET, SR1_labels, SR1_cuts, weight, 1)){
            FillHistLabel(channels.at(it_ch)+"/SR_Central_summary_"+IDsuffix, SR_summary_labels, "SR1_pass", weight);
            FillHistLabel(channels.at(it_ch)+"/SR_Central_summary_unweighted_"+IDsuffix, SR_summary_labels, "SR1_pass", 1.);
          }
          else{
            FillHistLabel(channels.at(it_ch)+"/SR_Central_summary_"+IDsuffix, SR_summary_labels, "SR1_fail", weight);
            FillHistLabel(channels.at(it_ch)+"/SR_Central_summary_unweighted_"+IDsuffix, SR_summary_labels, "SR1_fail", 1.);
          }
        }
        //else if(SR1_opts[i]=="bveto_loose"){
        //  SR1_labels = {"Nfatjet", "bveto", "mW", "MET2ST"};
        //  SR1_cuts = {Nbjet_loose, 40., 130., 15.};
        //  RunSR1(channels.at(it_ch), SR1_opts[i], IDsuffix, leptons, jets, jets_forward, fatjets, MET, SR1_labels, SR1_cuts, weight, 1);
        //}
        //else if(SR1_opts[i]=="mW50to150"){
        //  SR1_labels = {"Nfatjet", "bveto", "mW", "MET2ST"};
        //  SR1_cuts = {Nbjet_medium, 50., 150., 15.};
        //  RunSR1(channels.at(it_ch), SR1_opts[i], IDsuffix, leptons, jets, jets_forward, fatjets, MET, SR1_labels, SR1_cuts, weight, 0);
        //}
        //else if(SR1_opts[i]=="MET2ST_20"){
        //  SR1_labels = {"Nfatjet", "bveto", "mW", "MET2ST"};
        //  SR1_cuts = {Nbjet_medium, 40., 130., 20.};
        //  RunSR1(channels.at(it_ch), SR1_opts[i], IDsuffix, leptons, jets, jets_forward, fatjets, MET, SR1_labels, SR1_cuts, weight, 0);
        //}
      }
    }
    else{ // no fatjet
      vector<TString> SR2_opts = {"Central"};
      vector<TString> SR2_labels;
      vector<double> SR2_cuts;
      for(int i=0; i<SR2_opts.size(); i++){
        if(SR2_opts[i]=="Central"){
          SR2_labels = {"nofatjet", "Nforwardjet", "lpt", "mll", "max_zep", "j2pt", "detajj", "mjj", "bveto", "dphill", "HToverPt1"};
          SR2_cuts = {2., 30., 20., 0.75, 30., 2.5, 750., Nbjet_medium, 2., 1.,};
          if(RunSR2(channels.at(it_ch), SR2_opts[i], IDsuffix, leptons, jets, jets_forward, fatjets, MET, SR2_labels, SR2_cuts, weight, 1)){
            FillHistLabel(channels.at(it_ch)+"/SR_Central_summary_"+IDsuffix, SR_summary_labels, "SR2_pass", weight);
            FillHistLabel(channels.at(it_ch)+"/SR_Central_summary_unweighted_"+IDsuffix, SR_summary_labels, "SR2_pass", 1.);
          }
          else{ // SR2 fail
            FillHistLabel(channels.at(it_ch)+"/SR_Central_summary_"+IDsuffix, SR_summary_labels, "SR2_fail", weight);
            FillHistLabel(channels.at(it_ch)+"/SR_Central_summary_unweighted_"+IDsuffix, SR_summary_labels, "SR2_fail", 1.);

            vector<TString> SR3_opts = {"Central", "forward", "forward_mW", "forward_mW_HToverPt1", "forward_mW_HToverPt0p5"};
            vector<TString> SR3_labels;
            vector<double> SR3_cuts;
            for(int i=0; i<SR3_opts.size(); i++){
              if(SR3_opts[i]=="Central"){
                SR3_labels = {"VBFfail", "Njet", "bveto", "mW", "j1pt", "MET2ST"};
                SR3_cuts = {2., Nbjet_medium, 30., 150., 25., 15.};
                if(RunSR3(channels.at(it_ch), SR3_opts[i], IDsuffix, leptons, jets, jets_forward, fatjets, MET, SR3_labels, SR3_cuts, weight, 1)){
                  FillHistLabel(channels.at(it_ch)+"/SR_Central_summary_"+IDsuffix, SR_summary_labels, "SR3_pass", weight);
                  FillHistLabel(channels.at(it_ch)+"/SR_Central_summary_unweighted_"+IDsuffix, SR_summary_labels, "SR3_pass", 1.);
                }
                else{
                  FillHistLabel(channels.at(it_ch)+"/SR_Central_summary_"+IDsuffix, SR_summary_labels, "SR3_fail", weight);
                  FillHistLabel(channels.at(it_ch)+"/SR_Central_summary_unweighted_"+IDsuffix, SR_summary_labels, "SR3_fail", 1.);

                  DrawEvent(channels.at(it_ch), "SR3_Central_fail", IDsuffix, leptons, jets, jets_forward, fatjets, MET, weight);
                }
              }
              else if(SR3_opts[i]=="forward"){
                SR3_labels = {"VBFfail", "Njet", "bveto", "mW", "j1pt", "MET2ST"};
                SR3_cuts = {2., Nbjet_medium, 30., 150., 25., 15.};
                if(RunSR3(channels.at(it_ch), SR3_opts[i], IDsuffix, leptons, jets, jets_forward, fatjets, MET, SR3_labels, SR3_cuts, weight, 1)){
                  FillHistLabel(channels.at(it_ch)+"/SR_Central_summary_"+IDsuffix, SR_summary_labels, "SR3_forward_pass", weight);
                  FillHistLabel(channels.at(it_ch)+"/SR_Central_summary_unweighted_"+IDsuffix, SR_summary_labels, "SR3_forward_pass", 1.);
                }
                else{
                  FillHistLabel(channels.at(it_ch)+"/SR_Central_summary_"+IDsuffix, SR_summary_labels, "SR3_forward_fail", weight);
                  FillHistLabel(channels.at(it_ch)+"/SR_Central_summary_unweighted_"+IDsuffix, SR_summary_labels, "SR3_forward_fail", 1.);

                  DrawEvent(channels.at(it_ch), "SR3_forward_fail", IDsuffix, leptons, jets, jets_forward, fatjets, MET, weight);
                }
              }
              else if(SR3_opts[i]=="forward_mW"){
                SR3_labels = {"VBFfail", "Njet", "bveto", "mW", "j1pt", "MET2ST"};
                SR3_cuts = {2., Nbjet_medium, 0., 15000., 25., 15.};
                if(RunSR3(channels.at(it_ch), SR3_opts[i], IDsuffix, leptons, jets, jets_forward, fatjets, MET, SR3_labels, SR3_cuts, weight, 0)){
                  FillHistLabel(channels.at(it_ch)+"/SR_Central_summary_"+IDsuffix, SR_summary_labels, "SR3_forward_mW_pass", weight);
                  FillHistLabel(channels.at(it_ch)+"/SR_Central_summary_unweighted_"+IDsuffix, SR_summary_labels, "SR3_forward_mW_pass", 1.);
                }
                else{
                  FillHistLabel(channels.at(it_ch)+"/SR_Central_summary_"+IDsuffix, SR_summary_labels, "SR3_forward_mW_fail", weight);
                  FillHistLabel(channels.at(it_ch)+"/SR_Central_summary_unweighted_"+IDsuffix, SR_summary_labels, "SR3_forward_mW_fail", 1.);

                  DrawEvent(channels.at(it_ch), "SR3_forward_mW_fail", IDsuffix, leptons, jets, jets_forward, fatjets, MET, weight);
                }
              }
              else if(SR3_opts[i]=="forward_mW_HToverPt1"){
                SR3_labels = {"VBFfail", "Njet", "bveto", "mW", "j1pt", "MET2ST", "HToverPt1"};
                SR3_cuts = {2., Nbjet_medium, 0., 15000., 25., 15., 1.};
                if(RunSR3(channels.at(it_ch), SR3_opts[i], IDsuffix, leptons, jets, jets_forward, fatjets, MET, SR3_labels, SR3_cuts, weight, 0)){
                  FillHistLabel(channels.at(it_ch)+"/SR_Central_summary_"+IDsuffix, SR_summary_labels, "SR3_forward_mW_HToverPt1_pass", weight);
                  FillHistLabel(channels.at(it_ch)+"/SR_Central_summary_unweighted_"+IDsuffix, SR_summary_labels, "SR3_forward_mW_HToverPt1_pass", 1.);
                }
                else{
                  FillHistLabel(channels.at(it_ch)+"/SR_Central_summary_"+IDsuffix, SR_summary_labels, "SR3_forward_mW_HToverPt1_fail", weight);
                  FillHistLabel(channels.at(it_ch)+"/SR_Central_summary_unweighted_"+IDsuffix, SR_summary_labels, "SR3_forward_mW_HToverPt1_fail", 1.);

                  DrawEvent(channels.at(it_ch), "SR3_forward_mW_HToverPt1_fail", IDsuffix, leptons, jets, jets_forward, fatjets, MET, weight);
                }
              }
              else if(SR3_opts[i]=="forward_mW_HToverPt0p5"){
                SR3_labels = {"VBFfail", "Njet", "bveto", "mW", "j1pt", "MET2ST", "HToverPt0p5"};
                SR3_cuts = {2., Nbjet_medium, 0., 15000., 25., 15., 0.5};
                if(RunSR3(channels.at(it_ch), SR3_opts[i], IDsuffix, leptons, jets, jets_forward, fatjets, MET, SR3_labels, SR3_cuts, weight, 0)){
                  FillHistLabel(channels.at(it_ch)+"/SR_Central_summary_"+IDsuffix, SR_summary_labels, "SR3_forward_mW_HToverPt0p5_pass", weight);
                  FillHistLabel(channels.at(it_ch)+"/SR_Central_summary_unweighted_"+IDsuffix, SR_summary_labels, "SR3_forward_mW_HToverPt0p5_pass", 1.);
                }
                else{
                  FillHistLabel(channels.at(it_ch)+"/SR_Central_summary_"+IDsuffix, SR_summary_labels, "SR3_forward_mW_HToverPt0p5_fail", weight);
                  FillHistLabel(channels.at(it_ch)+"/SR_Central_summary_unweighted_"+IDsuffix, SR_summary_labels, "SR3_forward_mW_HToverPt0p5_fail", 1.);

                  DrawEvent(channels.at(it_ch), "SR3_forward_mW_HToverPt0p5_fail", IDsuffix, leptons, jets, jets_forward, fatjets, MET, weight);
                }
              }
            } // SR3 done

          }
        }
      }
    }

  } // each lepton channel




  /*


  //=====================================================================================
  //=====================================================================================
  //==== SSWW regions (SR, Inverted SR, b-tagged CR, WZ CR, WZb CR)
  //=====================================================================================
  //=====================================================================================

  // jet pt>20, |eta|<4.7, tight lepton cleaned with dR<0.3, pass loose PU, 2a-bjet pt>20, |eta|<2.4, electron pt>10, |eta|<2.5, muon pt>10, |eta|<2.4 

  for(unsigned int it_rg=0; it_rg<regionsSSWW.size(); it_rg++){

    if(electrons.size() > 0) continue;

    if(RunFake){
      weight = 1.;
      weight *= fakeEst->GetWeight(leptons, param);
    }
    // Cutflow 4 : loose electron veto
    FillHist(regionsSSWW.at(it_rg)+"/Number_Events_"+IDsuffix, 3.5, weight, cutflow_bin, 0., cutflow_max);
    FillHist(regionsSSWW.at(it_rg)+"/Number_Events_unweighted_"+IDsuffix, 3.5, 1., cutflow_bin, 0., cutflow_max);
  
    if(! (muons.size()>=2) ) continue;
    // Cutflow 5 : at least 2 tight muons
    FillHist(regionsSSWW.at(it_rg)+"/Number_Events_"+IDsuffix, 4.5, weight, cutflow_bin, 0., cutflow_max);
    FillHist(regionsSSWW.at(it_rg)+"/Number_Events_unweighted_"+IDsuffix, 4.5, 1., cutflow_bin, 0., cutflow_max);
  
    if(! (jets.size()>=2) ) continue;
    // Cutflow 6 : at least 2 AK4 jets
    FillHist(regionsSSWW.at(it_rg)+"/Number_Events_"+IDsuffix, 5.5, weight, cutflow_bin, 0., cutflow_max);
    FillHist(regionsSSWW.at(it_rg)+"/Number_Events_unweighted_"+IDsuffix, 5.5, 1., cutflow_bin, 0., cutflow_max);

    DiJet = jets.at(0)+jets.at(1);
    double avgEta = 0.5*(jets.at(0).Eta()+jets.at(1).Eta());
    double dEta = fabs(jets.at(0).Eta()-jets.at(1).Eta());
    double max_zep = std::max(fabs(muons.at(0).Eta()-avgEta),fabs(muons.at(1).Eta()-avgEta))/dEta;

    if(it_rg<=2){ // SR, SR_inv, b-tagged CR

      if(! (muons.size()==2 && muons.at(0).Charge()*muons.at(1).Charge()==1) ) continue;
      // SR Cutflow 7 : 2 same sign tight muons
      FillHist(regionsSSWW.at(it_rg)+"/Number_Events_"+IDsuffix, 6.5, weight, cutflow_bin, 0., cutflow_max);
      FillHist(regionsSSWW.at(it_rg)+"/Number_Events_unweighted_"+IDsuffix, 6.5, 1., cutflow_bin, 0., cutflow_max);

      if(muons.at(0).PassID(param.Muon_Tight_ID) && !(muons.at(1).PassID(param.Muon_Tight_ID))) LepCategory = "TL";
      if(!(muons.at(0).PassID(param.Muon_Tight_ID)) && muons.at(1).PassID(param.Muon_Tight_ID)) LepCategory = "LT";
      if(!(muons.at(1).PassID(param.Muon_Tight_ID)) && !(muons.at(0).PassID(param.Muon_Tight_ID))) LepCategory = "LL";

      if(! (muons.at(0).Pt()>30. && muons.at(1).Pt()>30.) ) continue;
      // SR Cutflow 8 : muon pt > 30/30 GeV
      FillHist(regionsSSWW.at(it_rg)+"/Number_Events_"+IDsuffix, 7.5, weight, cutflow_bin, 0., cutflow_max);
      FillHist(regionsSSWW.at(it_rg)+"/Number_Events_unweighted_"+IDsuffix, 7.5, 1., cutflow_bin, 0., cutflow_max);

      DiLep = muons.at(0)+muons.at(1);

      if(! (DiLep.M()>20.) ) continue;
      // SR Cutflow 9 : m(ll) > 20 GeV
      FillHist(regionsSSWW.at(it_rg)+"/Number_Events_"+IDsuffix, 8.5, weight, cutflow_bin, 0., cutflow_max);
      FillHist(regionsSSWW.at(it_rg)+"/Number_Events_unweighted_"+IDsuffix, 8.5, 1., cutflow_bin, 0., cutflow_max);

      if(! (max_zep<0.75) ) continue;
      // SR Cutflow 10 : max zeppenfeld < 0.75
      FillHist(regionsSSWW.at(it_rg)+"/Number_Events_"+IDsuffix, 9.5, weight, cutflow_bin, 0., cutflow_max);
      FillHist(regionsSSWW.at(it_rg)+"/Number_Events_unweighted_"+IDsuffix, 9.5, 1., cutflow_bin, 0., cutflow_max);

      if(! (jets.at(1).Pt()>30.) ) continue;
      // SR Cutflow 11 : jet pt > 30 GeV
      FillHist(regionsSSWW.at(it_rg)+"/Number_Events_"+IDsuffix, 10.5, weight, cutflow_bin, 0., cutflow_max);
      FillHist(regionsSSWW.at(it_rg)+"/Number_Events_unweighted_"+IDsuffix, 10.5, 1., cutflow_bin, 0., cutflow_max);

      if(! (dEta>2.5) ) continue;
      // SR Cutflow 12 : dEta(jj) > 2.5
      FillHist(regionsSSWW.at(it_rg)+"/Number_Events_"+IDsuffix, 11.5, weight, cutflow_bin, 0., cutflow_max);
      FillHist(regionsSSWW.at(it_rg)+"/Number_Events_unweighted_"+IDsuffix, 11.5, 1., cutflow_bin, 0., cutflow_max);

      if(! (DiJet.M()>750.) ) continue;
      // SR Cutflow 13 : m(jj) > 750 GeV
      FillHist(regionsSSWW.at(it_rg)+"/Number_Events_"+IDsuffix, 12.5, weight, cutflow_bin, 0., cutflow_max);
      FillHist(regionsSSWW.at(it_rg)+"/Number_Events_unweighted_"+IDsuffix, 12.5, 1., cutflow_bin, 0., cutflow_max);

      // Skip the tau veto for now;

      if(it_rg<2){ // SRs
        if(! (Nbjet_medium==0) ) continue;
        // SR Cutflow 14 : b-veto
        FillHist(regionsSSWW.at(it_rg)+"/Number_Events_"+IDsuffix, 13.5, weight, cutflow_bin, 0., cutflow_max);
        FillHist(regionsSSWW.at(it_rg)+"/Number_Events_unweighted_"+IDsuffix, 13.5, 1., cutflow_bin, 0., cutflow_max);

        double dPhi = fabs(muons.at(0).DeltaPhi(muons.at(1)));
        if(it_rg==0){
          if(dPhi>2.){
            // SR Cutflow 15 : dPhi(ll) > 2
            FillHist(regionsSSWW.at(it_rg)+"/Number_Events_"+IDsuffix, 14.5, weight, cutflow_bin, 0., cutflow_max);
            FillHist(regionsSSWW.at(it_rg)+"/Number_Events_unweighted_"+IDsuffix, 14.5, 1., cutflow_bin, 0., cutflow_max);
            if(HasFlag("fatjet_veto")){
              if(! (fatjets.size()==0) ) continue; // no fatjet
              // SR Cutflow 16 : no fatjet
              FillHist(regionsSSWW.at(it_rg)+"/Number_Events_"+IDsuffix, 15.5, weight, cutflow_bin, 0., cutflow_max);
              FillHist(regionsSSWW.at(it_rg)+"/Number_Events_unweighted_"+IDsuffix, 15.5, 1., cutflow_bin, 0., cutflow_max);
            }

            FillHist(regionsSSWW.at(it_rg)+"/Number_Jets_"+IDsuffix, jets.size(), weight, 10, 0., 10.);
            FillHist(regionsSSWW.at(it_rg)+"/Number_BJets_Loose_"+IDsuffix, Nbjet_loose, weight, 10, 0., 10.);
            FillHist(regionsSSWW.at(it_rg)+"/Number_BJets_Medium_"+IDsuffix, Nbjet_medium, weight, 10, 0., 10.);
            FillHist(regionsSSWW.at(it_rg)+"/Number_FatJets_"+IDsuffix, fatjets.size(), weight, 10, 0., 10.);
            if(fatjets.size()>0){
              FillHist(regionsTypeI.at(it_rg)+"/FatJet_Pt_"+IDsuffix, fatjets.at(0).Pt(), weight, 1500, 0., 1500.);
              FillHist(regionsTypeI.at(it_rg)+"/FatJet_Eta_"+IDsuffix, fatjets.at(0).Eta(), weight, 100, -5, 5);
              FillHist(regionsTypeI.at(it_rg)+"/FatJet_Mass_"+IDsuffix, fatjets.at(0).SDMass(), weight, 1500, 0., 1500.);
            }
            FillHist(regionsSSWW.at(it_rg)+"/DiLep_Mass_"+IDsuffix, DiLep.M(), weight, 1500, 0., 1500.);
            FillHist(regionsSSWW.at(it_rg)+"/DiJet_Mass_"+IDsuffix, DiJet.M(), weight, 3000, 0., 3000.);
            FillHist(regionsSSWW.at(it_rg)+"/Mu1_Pt_"+IDsuffix, muons.at(0).Pt(), weight, 1500, 0., 1500.);
            FillHist(regionsSSWW.at(it_rg)+"/Mu2_Pt_"+IDsuffix, muons.at(1).Pt(), weight, 1500, 0., 1500.);
            FillHist(regionsSSWW.at(it_rg)+"/Mu1_Eta_"+IDsuffix, muons.at(0).Eta(), weight, 50, -2.5, 2.5);
            FillHist(regionsSSWW.at(it_rg)+"/Mu2_Eta_"+IDsuffix, muons.at(1).Eta(), weight, 50, -2.5, 2.5);
            FillHist(regionsSSWW.at(it_rg)+"/Jet1_Pt_"+IDsuffix, jets.at(0).Pt(), weight, 1500, 0., 1500.);
            FillHist(regionsSSWW.at(it_rg)+"/Jet2_Pt_"+IDsuffix, jets.at(1).Pt(), weight, 1500, 0., 1500.);
            FillHist(regionsSSWW.at(it_rg)+"/Jet1_Eta_"+IDsuffix, jets.at(0).Eta(), weight, 100, -5, 5);
            FillHist(regionsSSWW.at(it_rg)+"/Jet2_Eta_"+IDsuffix, jets.at(1).Eta(), weight, 100, -5, 5);
            FillHist(regionsSSWW.at(it_rg)+"/MET_"+IDsuffix, MET, weight, 1000, 0., 1000.);
            FillHist(regionsSSWW.at(it_rg)+"/Zep_"+IDsuffix, max_zep, weight, 150, 0., 1.5);
            FillHist(regionsSSWW.at(it_rg)+"/dEtajj_"+IDsuffix, dEta, weight, 100, 0., 10.);
            FillHist(regionsSSWW.at(it_rg)+"/dPhill_"+IDsuffix, dPhi, weight, 32, 0., 3.2);
            FillHist(regionsSSWW.at(it_rg)+"/HToverPt1_"+IDsuffix, HT/muons.at(0).Pt(), weight, 10, 0., 10.);
            if(HT/muons.at(0).Pt()<1.){
              // SR Cutflow 17 : M1500 optimization 1
              FillHist(regionsSSWW.at(it_rg)+"/M1500_1/Number_Events_"+IDsuffix, 16.5, weight, cutflow_bin, 0., cutflow_max);
              FillHist(regionsSSWW.at(it_rg)+"/M1500_1/Number_Events_unweighted_"+IDsuffix, 16.5, 1., cutflow_bin, 0., cutflow_max);
              FillHist(regionsSSWW.at(it_rg)+"/M1500_1/Number_Jets_"+IDsuffix, jets.size(), weight, 10, 0., 10.);
              FillHist(regionsSSWW.at(it_rg)+"/M1500_1/Number_BJets_Loose_"+IDsuffix, Nbjet_loose, weight, 10, 0., 10.);
              FillHist(regionsSSWW.at(it_rg)+"/M1500_1/Number_BJets_Medium_"+IDsuffix, Nbjet_medium, weight, 10, 0., 10.);
              FillHist(regionsSSWW.at(it_rg)+"/M1500_1/Number_FatJets_"+IDsuffix, fatjets.size(), weight, 10, 0., 10.);
              if(fatjets.size()>0){
                FillHist(regionsTypeI.at(it_rg)+"/M1500_1/FatJet_Pt_"+IDsuffix, fatjets.at(0).Pt(), weight, 1500, 0., 1500.);
                FillHist(regionsTypeI.at(it_rg)+"/M1500_1/FatJet_Eta_"+IDsuffix, fatjets.at(0).Eta(), weight, 100, -5, 5);
                FillHist(regionsTypeI.at(it_rg)+"/M1500_1/FatJet_Mass_"+IDsuffix, fatjets.at(0).SDMass(), weight, 1500, 0., 1500.);
              }
              FillHist(regionsSSWW.at(it_rg)+"/M1500_1/DiLep_Mass_"+IDsuffix, DiLep.M(), weight, 1500, 0., 1500.);
              FillHist(regionsSSWW.at(it_rg)+"/M1500_1/DiJet_Mass_"+IDsuffix, DiJet.M(), weight, 3000, 0., 3000.);
              FillHist(regionsSSWW.at(it_rg)+"/M1500_1/Mu1_Pt_"+IDsuffix, muons.at(0).Pt(), weight, 1500, 0., 1500.);
              FillHist(regionsSSWW.at(it_rg)+"/M1500_1/Mu2_Pt_"+IDsuffix, muons.at(1).Pt(), weight, 1500, 0., 1500.);
              FillHist(regionsSSWW.at(it_rg)+"/M1500_1/Mu1_Eta_"+IDsuffix, muons.at(0).Eta(), weight, 50, -2.5, 2.5);
              FillHist(regionsSSWW.at(it_rg)+"/M1500_1/Mu2_Eta_"+IDsuffix, muons.at(1).Eta(), weight, 50, -2.5, 2.5);
              FillHist(regionsSSWW.at(it_rg)+"/M1500_1/Jet1_Pt_"+IDsuffix, jets.at(0).Pt(), weight, 1500, 0., 1500.);
              FillHist(regionsSSWW.at(it_rg)+"/M1500_1/Jet2_Pt_"+IDsuffix, jets.at(1).Pt(), weight, 1500, 0., 1500.);
              FillHist(regionsSSWW.at(it_rg)+"/M1500_1/Jet1_Eta_"+IDsuffix, jets.at(0).Eta(), weight, 100, -5, 5);
              FillHist(regionsSSWW.at(it_rg)+"/M1500_1/Jet2_Eta_"+IDsuffix, jets.at(1).Eta(), weight, 100, -5, 5);
              FillHist(regionsSSWW.at(it_rg)+"/M1500_1/MET_"+IDsuffix, MET, weight, 1000, 0., 1000.);
              FillHist(regionsSSWW.at(it_rg)+"/M1500_1/Zep_"+IDsuffix, max_zep, weight, 150, 0., 1.5);
              FillHist(regionsSSWW.at(it_rg)+"/M1500_1/dEtajj_"+IDsuffix, dEta, weight, 100, 0., 10.);
              FillHist(regionsSSWW.at(it_rg)+"/M1500_1/dPhill_"+IDsuffix, dPhi, weight, 32, 0., 3.2);
              FillHist(regionsSSWW.at(it_rg)+"/M1500_1/HToverPt1_"+IDsuffix, HT/muons.at(0).Pt(), weight, 10, 0., 10.);
            }
            if(HT/muons.at(0).Pt()<2.){
              // SR Cutflow 17 : M1500 optimization 2
              FillHist(regionsSSWW.at(it_rg)+"/M1500_2/Number_Events_"+IDsuffix, 16.5, weight, cutflow_bin, 0., cutflow_max);
              FillHist(regionsSSWW.at(it_rg)+"/M1500_2/Number_Events_unweighted_"+IDsuffix, 16.5, 1., cutflow_bin, 0., cutflow_max);
              FillHist(regionsSSWW.at(it_rg)+"/M1500_2/Number_Jets_"+IDsuffix, jets.size(), weight, 10, 0., 10.);
              FillHist(regionsSSWW.at(it_rg)+"/M1500_2/Number_BJets_Loose_"+IDsuffix, Nbjet_loose, weight, 10, 0., 10.);
              FillHist(regionsSSWW.at(it_rg)+"/M1500_2/Number_BJets_Medium_"+IDsuffix, Nbjet_medium, weight, 10, 0., 10.);
              FillHist(regionsSSWW.at(it_rg)+"/M1500_2/Number_FatJets_"+IDsuffix, fatjets.size(), weight, 10, 0., 10.);
              if(fatjets.size()>0){
                FillHist(regionsTypeI.at(it_rg)+"/M1500_2/FatJet_Pt_"+IDsuffix, fatjets.at(0).Pt(), weight, 1500, 0., 1500.);
                FillHist(regionsTypeI.at(it_rg)+"/M1500_2/FatJet_Eta_"+IDsuffix, fatjets.at(0).Eta(), weight, 100, -5, 5);
                FillHist(regionsTypeI.at(it_rg)+"/M1500_2/FatJet_Mass_"+IDsuffix, fatjets.at(0).SDMass(), weight, 1500, 0., 1500.);
              }
              FillHist(regionsSSWW.at(it_rg)+"/M1500_2/DiLep_Mass_"+IDsuffix, DiLep.M(), weight, 1500, 0., 1500.);
              FillHist(regionsSSWW.at(it_rg)+"/M1500_2/DiJet_Mass_"+IDsuffix, DiJet.M(), weight, 3000, 0., 3000.);
              FillHist(regionsSSWW.at(it_rg)+"/M1500_2/Mu1_Pt_"+IDsuffix, muons.at(0).Pt(), weight, 1500, 0., 1500.);
              FillHist(regionsSSWW.at(it_rg)+"/M1500_2/Mu2_Pt_"+IDsuffix, muons.at(1).Pt(), weight, 1500, 0., 1500.);
              FillHist(regionsSSWW.at(it_rg)+"/M1500_2/Mu1_Eta_"+IDsuffix, muons.at(0).Eta(), weight, 50, -2.5, 2.5);
              FillHist(regionsSSWW.at(it_rg)+"/M1500_2/Mu2_Eta_"+IDsuffix, muons.at(1).Eta(), weight, 50, -2.5, 2.5);
              FillHist(regionsSSWW.at(it_rg)+"/M1500_2/Jet1_Pt_"+IDsuffix, jets.at(0).Pt(), weight, 1500, 0., 1500.);
              FillHist(regionsSSWW.at(it_rg)+"/M1500_2/Jet2_Pt_"+IDsuffix, jets.at(1).Pt(), weight, 1500, 0., 1500.);
              FillHist(regionsSSWW.at(it_rg)+"/M1500_2/Jet1_Eta_"+IDsuffix, jets.at(0).Eta(), weight, 100, -5, 5);
              FillHist(regionsSSWW.at(it_rg)+"/M1500_2/Jet2_Eta_"+IDsuffix, jets.at(1).Eta(), weight, 100, -5, 5);
              FillHist(regionsSSWW.at(it_rg)+"/M1500_2/MET_"+IDsuffix, MET, weight, 1000, 0., 1000.);
              FillHist(regionsSSWW.at(it_rg)+"/M1500_2/Zep_"+IDsuffix, max_zep, weight, 150, 0., 1.5);
              FillHist(regionsSSWW.at(it_rg)+"/M1500_2/dEtajj_"+IDsuffix, dEta, weight, 100, 0., 10.);
              FillHist(regionsSSWW.at(it_rg)+"/M1500_2/dPhill_"+IDsuffix, dPhi, weight, 32, 0., 3.2);
              FillHist(regionsSSWW.at(it_rg)+"/M1500_2/HToverPt1_"+IDsuffix, HT/muons.at(0).Pt(), weight, 10, 0., 10.);
            }
          }
        }
        else if(it_rg==1){
          if(dPhi<=2.){
            // Inverted SR Cutflow 15 : dPhi(ll) <= 2
            FillHist(regionsSSWW.at(it_rg)+"/Number_Events_"+IDsuffix, 14.5, weight, cutflow_bin, 0., cutflow_max);
            FillHist(regionsSSWW.at(it_rg)+"/Number_Events_unweighted_"+IDsuffix, 14.5, 1., cutflow_bin, 0., cutflow_max);
            if(HasFlag("fatjet_veto")){
              if(! (fatjets.size()==0) ) continue; // no fatjet
              // SR Cutflow 16 : no fatjet
              FillHist(regionsSSWW.at(it_rg)+"/Number_Events_"+IDsuffix, 15.5, weight, cutflow_bin, 0., cutflow_max);
              FillHist(regionsSSWW.at(it_rg)+"/Number_Events_unweighted_"+IDsuffix, 15.5, 1., cutflow_bin, 0., cutflow_max);
            }

            FillHist(regionsSSWW.at(it_rg)+"/Number_Jets_"+IDsuffix, jets.size(), weight, 10, 0., 10.);
            FillHist(regionsSSWW.at(it_rg)+"/Number_BJets_Loose_"+IDsuffix, Nbjet_loose, weight, 10, 0., 10.);
            FillHist(regionsSSWW.at(it_rg)+"/Number_BJets_Medium_"+IDsuffix, Nbjet_medium, weight, 10, 0., 10.);
            FillHist(regionsSSWW.at(it_rg)+"/Number_FatJets_"+IDsuffix, fatjets.size(), weight, 10, 0., 10.);
            if(fatjets.size()>0){
              FillHist(regionsTypeI.at(it_rg)+"/FatJet_Pt_"+IDsuffix, fatjets.at(0).Pt(), weight, 1500, 0., 1500.);
              FillHist(regionsTypeI.at(it_rg)+"/FatJet_Eta_"+IDsuffix, fatjets.at(0).Eta(), weight, 100, -5, 5);
              FillHist(regionsTypeI.at(it_rg)+"/FatJet_Mass_"+IDsuffix, fatjets.at(0).SDMass(), weight, 1500, 0., 1500.);
            }
            FillHist(regionsSSWW.at(it_rg)+"/DiLep_Mass_"+IDsuffix, DiLep.M(), weight, 1500, 0., 1500.);
            FillHist(regionsSSWW.at(it_rg)+"/DiJet_Mass_"+IDsuffix, DiJet.M(), weight, 3000, 0., 3000.);
            FillHist(regionsSSWW.at(it_rg)+"/Mu1_Pt_"+IDsuffix, muons.at(0).Pt(), weight, 1500, 0., 1500.);
            FillHist(regionsSSWW.at(it_rg)+"/Mu2_Pt_"+IDsuffix, muons.at(1).Pt(), weight, 1500, 0., 1500.);
            FillHist(regionsSSWW.at(it_rg)+"/Mu1_Eta_"+IDsuffix, muons.at(0).Eta(), weight, 50, -2.5, 2.5);
            FillHist(regionsSSWW.at(it_rg)+"/Mu2_Eta_"+IDsuffix, muons.at(1).Eta(), weight, 50, -2.5, 2.5);
            FillHist(regionsSSWW.at(it_rg)+"/Jet1_Pt_"+IDsuffix, jets.at(0).Pt(), weight, 1500, 0., 1500.);
            FillHist(regionsSSWW.at(it_rg)+"/Jet2_Pt_"+IDsuffix, jets.at(1).Pt(), weight, 1500, 0., 1500.);
            FillHist(regionsSSWW.at(it_rg)+"/Jet1_Eta_"+IDsuffix, jets.at(0).Eta(), weight, 100, -5, 5);
            FillHist(regionsSSWW.at(it_rg)+"/Jet2_Eta_"+IDsuffix, jets.at(1).Eta(), weight, 100, -5, 5);
            FillHist(regionsSSWW.at(it_rg)+"/MET_"+IDsuffix, MET, weight, 1000, 0., 1000.);
            FillHist(regionsSSWW.at(it_rg)+"/Zep_"+IDsuffix, max_zep, weight, 150, 0., 1.5);
            FillHist(regionsSSWW.at(it_rg)+"/dEtajj_"+IDsuffix, dEta, weight, 100, 0., 10.);
            FillHist(regionsSSWW.at(it_rg)+"/dPhill_"+IDsuffix, dPhi, weight, 32, 0., 3.2);
            FillHist(regionsSSWW.at(it_rg)+"/HToverPt1_"+IDsuffix, HT/muons.at(0).Pt(), weight, 10, 0., 10.);
          }
        }
      }
      else if(it_rg==2){ // b-tagged CR
        if(Nbjet_medium==0) continue;
        // b-tagged CR Cutflow 14 : b-veto inversion
        FillHist(regionsSSWW.at(it_rg)+"/Number_Events_"+IDsuffix, 13.5, weight, cutflow_bin, 0., cutflow_max);
        FillHist(regionsSSWW.at(it_rg)+"/Number_Events_unweighted_"+IDsuffix, 13.5, 1., cutflow_bin, 0., cutflow_max);

        FillHist(regionsSSWW.at(it_rg)+"/Number_Jets_"+IDsuffix, jets.size(), weight, 10, 0., 10.);
        FillHist(regionsSSWW.at(it_rg)+"/Number_BJets_Loose_"+IDsuffix, Nbjet_loose, weight, 10, 0., 10.);
        FillHist(regionsSSWW.at(it_rg)+"/Number_BJets_Medium_"+IDsuffix, Nbjet_medium, weight, 10, 0., 10.);
        FillHist(regionsSSWW.at(it_rg)+"/Number_FatJets_"+IDsuffix, fatjets.size(), weight, 10, 0., 10.);
        FillHist(regionsSSWW.at(it_rg)+"/DiLep_Mass_"+IDsuffix, DiLep.M(), weight, 1500, 0., 1500.);
        FillHist(regionsSSWW.at(it_rg)+"/DiJet_Mass_"+IDsuffix, DiJet.M(), weight, 3000, 0., 3000.);
        FillHist(regionsSSWW.at(it_rg)+"/Mu1_Pt_"+IDsuffix, muons.at(0).Pt(), weight, 1500, 0., 1500.);
        FillHist(regionsSSWW.at(it_rg)+"/Mu2_Pt_"+IDsuffix, muons.at(1).Pt(), weight, 1500, 0., 1500.);
        FillHist(regionsSSWW.at(it_rg)+"/Mu1_Eta_"+IDsuffix, muons.at(0).Eta(), weight, 50, -2.5, 2.5);
        FillHist(regionsSSWW.at(it_rg)+"/Mu2_Eta_"+IDsuffix, muons.at(1).Eta(), weight, 50, -2.5, 2.5);
        FillHist(regionsSSWW.at(it_rg)+"/Jet1_Pt_"+IDsuffix, jets.at(0).Pt(), weight, 1500, 0., 1500.);
        FillHist(regionsSSWW.at(it_rg)+"/Jet2_Pt_"+IDsuffix, jets.at(1).Pt(), weight, 1500, 0., 1500.);
        FillHist(regionsSSWW.at(it_rg)+"/Jet1_Eta_"+IDsuffix, jets.at(0).Eta(), weight, 100, -5, 5);
        FillHist(regionsSSWW.at(it_rg)+"/Jet2_Eta_"+IDsuffix, jets.at(1).Eta(), weight, 100, -5, 5);
        FillHist(regionsSSWW.at(it_rg)+"/MET_"+IDsuffix, MET, weight, 1000, 0., 1000.);
        FillHist(regionsSSWW.at(it_rg)+"/Zep_"+IDsuffix, max_zep, weight, 150, 0., 1.5);
        FillHist(regionsSSWW.at(it_rg)+"/dEtajj_"+IDsuffix, dEta, weight, 100, 0., 10.);
        FillHist(regionsSSWW.at(it_rg)+"/HToverPt1_"+IDsuffix, HT/muons.at(0).Pt(), weight, 10, 0., 10.);

        if(RunFake){
          FillHist(regionsSSWW.at(it_rg)+"/"+LepCategory+"/Number_Jets_"+IDsuffix, jets.size(), weight, 10, 0., 10.);
          FillHist(regionsSSWW.at(it_rg)+"/"+LepCategory+"/Number_BJets_Loose_"+IDsuffix, Nbjet_loose, weight, 10, 0., 10.);
          FillHist(regionsSSWW.at(it_rg)+"/"+LepCategory+"/Number_BJets_Medium_"+IDsuffix, Nbjet_medium, weight, 10, 0., 10.);
          FillHist(regionsSSWW.at(it_rg)+"/"+LepCategory+"/Number_FatJets_"+IDsuffix, fatjets.size(), weight, 10, 0., 10.);
          FillHist(regionsSSWW.at(it_rg)+"/"+LepCategory+"/DiLep_Mass_"+IDsuffix, DiLep.M(), weight, 1500, 0., 1500.);
          FillHist(regionsSSWW.at(it_rg)+"/"+LepCategory+"/DiJet_Mass_"+IDsuffix, DiJet.M(), weight, 3000, 0., 3000.);
          FillHist(regionsSSWW.at(it_rg)+"/"+LepCategory+"/Mu1_Pt_"+IDsuffix, muons.at(0).Pt(), weight, 1500, 0., 1500.);
          FillHist(regionsSSWW.at(it_rg)+"/"+LepCategory+"/Mu2_Pt_"+IDsuffix, muons.at(1).Pt(), weight, 1500, 0., 1500.);
          FillHist(regionsSSWW.at(it_rg)+"/"+LepCategory+"/Mu1_Eta_"+IDsuffix, muons.at(0).Eta(), weight, 50, -2.5, 2.5);
          FillHist(regionsSSWW.at(it_rg)+"/"+LepCategory+"/Mu2_Eta_"+IDsuffix, muons.at(1).Eta(), weight, 50, -2.5, 2.5);
          FillHist(regionsSSWW.at(it_rg)+"/"+LepCategory+"/Jet1_Pt_"+IDsuffix, jets.at(0).Pt(), weight, 1500, 0., 1500.);
          FillHist(regionsSSWW.at(it_rg)+"/"+LepCategory+"/Jet2_Pt_"+IDsuffix, jets.at(1).Pt(), weight, 1500, 0., 1500.);
          FillHist(regionsSSWW.at(it_rg)+"/"+LepCategory+"/Jet1_Eta_"+IDsuffix, jets.at(0).Eta(), weight, 100, -5, 5);
          FillHist(regionsSSWW.at(it_rg)+"/"+LepCategory+"/Jet2_Eta_"+IDsuffix, jets.at(1).Eta(), weight, 100, -5, 5);
          FillHist(regionsSSWW.at(it_rg)+"/"+LepCategory+"/MET_"+IDsuffix, MET, weight, 1000, 0., 1000.);
          FillHist(regionsSSWW.at(it_rg)+"/"+LepCategory+"/Zep_"+IDsuffix, max_zep, weight, 150, 0., 1.5);
          FillHist(regionsSSWW.at(it_rg)+"/"+LepCategory+"/dEtajj_"+IDsuffix, dEta, weight, 100, 0., 10.);
          FillHist(regionsSSWW.at(it_rg)+"/"+LepCategory+"/HToverPt1_"+IDsuffix, HT/muons.at(0).Pt(), weight, 10, 0., 10.);

          FillHist(regionsSSWW.at(it_rg)+"/"+LepCategory+"/Number_Jets_unweighted_"+IDsuffix, jets.size(), 1., 10, 0., 10.);
          FillHist(regionsSSWW.at(it_rg)+"/"+LepCategory+"/Number_BJets_Loose_unweighted_"+IDsuffix, Nbjet_loose, 1., 10, 0., 10.);
          FillHist(regionsSSWW.at(it_rg)+"/"+LepCategory+"/Number_BJets_Medium_unweighted_"+IDsuffix, Nbjet_medium, 1., 10, 0., 10.);
          FillHist(regionsSSWW.at(it_rg)+"/"+LepCategory+"/Number_FatJets_unweighted_"+IDsuffix, fatjets.size(), 1., 10, 0., 10.);
          FillHist(regionsSSWW.at(it_rg)+"/"+LepCategory+"/DiLep_Mass_unweighted_"+IDsuffix, DiLep.M(), 1., 1500, 0., 1500.);
          FillHist(regionsSSWW.at(it_rg)+"/"+LepCategory+"/DiJet_Mass_unweighted_"+IDsuffix, DiJet.M(), 1., 3000, 0., 3000.);
          FillHist(regionsSSWW.at(it_rg)+"/"+LepCategory+"/Mu1_Pt_unweighted_"+IDsuffix, muons.at(0).Pt(), 1., 1500, 0., 1500.);
          FillHist(regionsSSWW.at(it_rg)+"/"+LepCategory+"/Mu2_Pt_unweighted_"+IDsuffix, muons.at(1).Pt(), 1., 1500, 0., 1500.);
          FillHist(regionsSSWW.at(it_rg)+"/"+LepCategory+"/Mu1_Eta_unweighted_"+IDsuffix, muons.at(0).Eta(), 1., 50, -2.5, 2.5);
          FillHist(regionsSSWW.at(it_rg)+"/"+LepCategory+"/Mu2_Eta_unweighted_"+IDsuffix, muons.at(1).Eta(), 1., 50, -2.5, 2.5);
          FillHist(regionsSSWW.at(it_rg)+"/"+LepCategory+"/Jet1_Pt_unweighted_"+IDsuffix, jets.at(0).Pt(), 1., 1500, 0., 1500.);
          FillHist(regionsSSWW.at(it_rg)+"/"+LepCategory+"/Jet2_Pt_unweighted_"+IDsuffix, jets.at(1).Pt(), 1., 1500, 0., 1500.);
          FillHist(regionsSSWW.at(it_rg)+"/"+LepCategory+"/Jet1_Eta_unweighted_"+IDsuffix, jets.at(0).Eta(), 1., 100, -5, 5);
          FillHist(regionsSSWW.at(it_rg)+"/"+LepCategory+"/Jet2_Eta_unweighted_"+IDsuffix, jets.at(1).Eta(), 1., 100, -5, 5);
          FillHist(regionsSSWW.at(it_rg)+"/"+LepCategory+"/MET_unweighted_"+IDsuffix, MET, 1., 1000, 0., 1000.);
          FillHist(regionsSSWW.at(it_rg)+"/"+LepCategory+"/Zep_unweighted_"+IDsuffix, max_zep, 1., 150, 0., 1.5);
          FillHist(regionsSSWW.at(it_rg)+"/"+LepCategory+"/dEtajj_unweighted_"+IDsuffix, dEta, 1., 100, 0., 10.);
          FillHist(regionsSSWW.at(it_rg)+"/"+LepCategory+"/HToverPt1_unweighted_"+IDsuffix, HT/muons.at(0).Pt(), 1., 10, 0., 10.);
        }

      }

    }
    else{ // WZ, WZb CR

      if(! (muons.size()==3 && abs(muons.at(0).Charge()+muons.at(1).Charge()+muons.at(2).Charge())==1) ) continue;
      // CR Cutflow 7 : 1 OSSF muon pair + 1 muon
      FillHist(regionsSSWW.at(it_rg)+"/Number_Events_"+IDsuffix, 6.5, weight, cutflow_bin, 0., cutflow_max);
      FillHist(regionsSSWW.at(it_rg)+"/Number_Events_unweighted_"+IDsuffix, 6.5, 1., cutflow_bin, 0., cutflow_max);

      TriLep = muons.at(0)+muons.at(1)+muons.at(2);

      // select ZCand, ZtagLep1, ZtagLep2, WtagLep
      int l1 = -999, l2 = -999;
      double tmpMassDiff = 1000000.; 
      int dilep_mass20 = 0;
      for(int ilep1=0; ilep1<2; ilep1++){
        for(int ilep2=ilep1+1; ilep2<3; ilep2++){ // for each pair (01, 02, 12)
          DiLep = muons.at(ilep1) + muons.at(ilep2);
          if(DiLep.M()>20.) dilep_mass20++; // count m(ll) > 20 GeV
          if(muons.at(ilep1).Charge()*muons.at(ilep2).Charge()>0) continue; // now skip the same sign
          Ztemp = muons.at(ilep1) + muons.at(ilep2);
          if(fabs(Ztemp.M() - MZ) < tmpMassDiff){
            tmpMassDiff = fabs(Ztemp.M() - MZ);
            ZCand = Ztemp; l1 = ilep1; l2 = ilep2; //JH : l1, l2 are the closest to m(Z)
          }
        }
      }
      ZtagLep1 = muons.at(l1);
      ZtagLep2 = muons.at(l2);
      for(int ilep3=0; ilep3<3; ilep3++){
        if(ilep3!=l1 && ilep3!=l2) WtagLep = muons.at(ilep3);
      }
      if(! (WtagLep.Pt()>0.) ){
        cout << "In SSWW WZ CR :: WtagLep pt is not positive. Something's wrong!!" << endl;
        cout << "WtagLep pt : " << WtagLep.Pt() << endl;
        exit(EXIT_FAILURE);
      }

      if(! (ZtagLep1.Pt()>25. && ZtagLep2.Pt()>10. && WtagLep.Pt()>25.) ) continue;
      // CR Cutflow 8 : muon pt > 25/10/25 GeV
      FillHist(regionsSSWW.at(it_rg)+"/Number_Events_"+IDsuffix, 7.5, weight, cutflow_bin, 0., cutflow_max);
      FillHist(regionsSSWW.at(it_rg)+"/Number_Events_unweighted_"+IDsuffix, 7.5, 1., cutflow_bin, 0., cutflow_max);

      if(! (dilep_mass20==3) ) continue;
      // CR Cutflow 9 : m(ll) > 20 GeV
      FillHist(regionsSSWW.at(it_rg)+"/Number_Events_"+IDsuffix, 8.5, weight, cutflow_bin, 0., cutflow_max);
      FillHist(regionsSSWW.at(it_rg)+"/Number_Events_unweighted_"+IDsuffix, 8.5, 1., cutflow_bin, 0., cutflow_max);

      if(! (max_zep<1.) ) continue;
      // CR Cutflow 10 : max zeppenfeld < 1.
      FillHist(regionsSSWW.at(it_rg)+"/Number_Events_"+IDsuffix, 9.5, weight, cutflow_bin, 0., cutflow_max);
      FillHist(regionsSSWW.at(it_rg)+"/Number_Events_unweighted_"+IDsuffix, 9.5, 1., cutflow_bin, 0., cutflow_max);

      if(! (jets.at(1).Pt()>30.) ) continue;
      // CR Cutflow 11 : jet pt > 30 GeV
      FillHist(regionsSSWW.at(it_rg)+"/Number_Events_"+IDsuffix, 10.5, weight, cutflow_bin, 0., cutflow_max);
      FillHist(regionsSSWW.at(it_rg)+"/Number_Events_unweighted_"+IDsuffix, 10.5, 1., cutflow_bin, 0., cutflow_max);

      if(! (dEta>2.5) ) continue;
      // CR Cutflow 12 : dEta(jj) > 2.5
      FillHist(regionsSSWW.at(it_rg)+"/Number_Events_"+IDsuffix, 11.5, weight, cutflow_bin, 0., cutflow_max);
      FillHist(regionsSSWW.at(it_rg)+"/Number_Events_unweighted_"+IDsuffix, 11.5, 1., cutflow_bin, 0., cutflow_max);

      if(! (DiJet.M()>750.) ) continue;
      // CR Cutflow 13 : m(jj) > 750 GeV
      FillHist(regionsSSWW.at(it_rg)+"/Number_Events_"+IDsuffix, 12.5, weight, cutflow_bin, 0., cutflow_max);
      FillHist(regionsSSWW.at(it_rg)+"/Number_Events_unweighted_"+IDsuffix, 12.5, 1., cutflow_bin, 0., cutflow_max);

      // Skip the tau veto for now;

      if(! (MET>30.) ) continue;
      // CR Cutflow 14 : MET > 30 GeV
      FillHist(regionsSSWW.at(it_rg)+"/Number_Events_"+IDsuffix, 13.5, weight, cutflow_bin, 0., cutflow_max);
      FillHist(regionsSSWW.at(it_rg)+"/Number_Events_unweighted_"+IDsuffix, 13.5, 1., cutflow_bin, 0., cutflow_max);

      if(! (IsOnZ(ZCand.M(), 15.)) ) continue;
      // CR Cutflow 15 : |m(ll)-m(Z)| < 15 GeV
      FillHist(regionsSSWW.at(it_rg)+"/Number_Events_"+IDsuffix, 14.5, weight, cutflow_bin, 0., cutflow_max);
      FillHist(regionsSSWW.at(it_rg)+"/Number_Events_unweighted_"+IDsuffix, 14.5, 1., cutflow_bin, 0., cutflow_max);

      if(! (TriLep.M()>100.) ) continue;
      // CR Cutflow 16 : m(lll) > 100 GeV
      FillHist(regionsSSWW.at(it_rg)+"/Number_Events_"+IDsuffix, 15.5, weight, cutflow_bin, 0., cutflow_max);
      FillHist(regionsSSWW.at(it_rg)+"/Number_Events_unweighted_"+IDsuffix, 15.5, 1., cutflow_bin, 0., cutflow_max);

      if(it_rg==3){ // WZ CR
        if(! (Nbjet_medium==0) ) continue;
        // WZ CR Cutflow 17 : b-veto
        FillHist(regionsSSWW.at(it_rg)+"/Number_Events_"+IDsuffix, 16.5, weight, cutflow_bin, 0., cutflow_max);
        FillHist(regionsSSWW.at(it_rg)+"/Number_Events_unweighted_"+IDsuffix, 16.5, 1., cutflow_bin, 0., cutflow_max);

        FillHist(regionsSSWW.at(it_rg)+"/Number_Jets_"+IDsuffix, jets.size(), weight, 10, 0., 10.);
        FillHist(regionsSSWW.at(it_rg)+"/Number_BJets_Loose_"+IDsuffix, Nbjet_loose, weight, 10, 0., 10.);
        FillHist(regionsSSWW.at(it_rg)+"/Number_BJets_Medium_"+IDsuffix, Nbjet_medium, weight, 10, 0., 10.);
        FillHist(regionsSSWW.at(it_rg)+"/Number_FatJets_"+IDsuffix, fatjets.size(), weight, 10, 0., 10.);
        FillHist(regionsSSWW.at(it_rg)+"/ZCand_Mass_"+IDsuffix, ZCand.M(), weight, 1500, 0., 1500.);
        FillHist(regionsSSWW.at(it_rg)+"/TriLep_Mass_"+IDsuffix, TriLep.M(), weight, 1500, 0., 1500.);
        FillHist(regionsSSWW.at(it_rg)+"/DiJet_Mass_"+IDsuffix, DiJet.M(), weight, 3000, 0., 3000.);
        FillHist(regionsSSWW.at(it_rg)+"/Mu1_Pt_"+IDsuffix, muons.at(0).Pt(), weight, 1500, 0., 1500.);
        FillHist(regionsSSWW.at(it_rg)+"/Mu2_Pt_"+IDsuffix, muons.at(1).Pt(), weight, 1500, 0., 1500.);
        FillHist(regionsSSWW.at(it_rg)+"/Mu3_Pt_"+IDsuffix, muons.at(2).Pt(), weight, 1500, 0., 1500.);
        FillHist(regionsSSWW.at(it_rg)+"/ZtagLep1_Pt_"+IDsuffix, ZtagLep1.Pt(), weight, 1500, 0., 1500.);
        FillHist(regionsSSWW.at(it_rg)+"/ZtagLep2_Pt_"+IDsuffix, ZtagLep2.Pt(), weight, 1500, 0., 1500.);
        FillHist(regionsSSWW.at(it_rg)+"/WtagLep_Pt_"+IDsuffix, WtagLep.Pt(), weight, 1500, 0., 1500.);
        FillHist(regionsSSWW.at(it_rg)+"/Mu1_Eta_"+IDsuffix, muons.at(0).Eta(), weight, 50, -2.5, 2.5);
        FillHist(regionsSSWW.at(it_rg)+"/Mu2_Eta_"+IDsuffix, muons.at(1).Eta(), weight, 50, -2.5, 2.5);
        FillHist(regionsSSWW.at(it_rg)+"/Mu3_Eta_"+IDsuffix, muons.at(2).Eta(), weight, 50, -2.5, 2.5);
        FillHist(regionsSSWW.at(it_rg)+"/ZtagLep1_Eta_"+IDsuffix, ZtagLep1.Eta(), weight, 50, -2.5, 2.5);
        FillHist(regionsSSWW.at(it_rg)+"/ZtagLep2_Eta_"+IDsuffix, ZtagLep2.Eta(), weight, 50, -2.5, 2.5);
        FillHist(regionsSSWW.at(it_rg)+"/WtagLep_Eta_"+IDsuffix, WtagLep.Eta(), weight, 50, -2.5, 2.5);
        FillHist(regionsSSWW.at(it_rg)+"/Jet1_Pt_"+IDsuffix, jets.at(0).Pt(), weight, 1500, 0., 1500.);
        FillHist(regionsSSWW.at(it_rg)+"/Jet2_Pt_"+IDsuffix, jets.at(1).Pt(), weight, 1500, 0., 1500.);
        FillHist(regionsSSWW.at(it_rg)+"/Jet1_Eta_"+IDsuffix, jets.at(0).Eta(), weight, 100, -5, 5);
        FillHist(regionsSSWW.at(it_rg)+"/Jet2_Eta_"+IDsuffix, jets.at(1).Eta(), weight, 100, -5, 5);
        FillHist(regionsSSWW.at(it_rg)+"/MET_"+IDsuffix, MET, weight, 1000, 0., 1000.);
        FillHist(regionsSSWW.at(it_rg)+"/Zep_"+IDsuffix, max_zep, weight, 150, 0., 1.5);
        FillHist(regionsSSWW.at(it_rg)+"/dEtajj_"+IDsuffix, dEta, weight, 100, 0., 10.);
        FillHist(regionsSSWW.at(it_rg)+"/HToverPt1_"+IDsuffix, HT/muons.at(0).Pt(), weight, 10, 0., 10.);
      }
      else if(it_rg==4){ // WZb CR
        if(Nbjet_medium==0) continue;
        // WZb CR Cutflow 17 : b-veto inversion
        FillHist(regionsSSWW.at(it_rg)+"/Number_Events_"+IDsuffix, 16.5, weight, cutflow_bin, 0., cutflow_max);
        FillHist(regionsSSWW.at(it_rg)+"/Number_Events_unweighted_"+IDsuffix, 16.5, 1., cutflow_bin, 0., cutflow_max);

        FillHist(regionsSSWW.at(it_rg)+"/Number_Jets_"+IDsuffix, jets.size(), weight, 10, 0., 10.);
        FillHist(regionsSSWW.at(it_rg)+"/Number_BJets_Loose_"+IDsuffix, Nbjet_loose, weight, 10, 0., 10.);
        FillHist(regionsSSWW.at(it_rg)+"/Number_BJets_Medium_"+IDsuffix, Nbjet_medium, weight, 10, 0., 10.);
        FillHist(regionsSSWW.at(it_rg)+"/Number_FatJets_"+IDsuffix, fatjets.size(), weight, 10, 0., 10.);
        FillHist(regionsSSWW.at(it_rg)+"/ZCand_Mass_"+IDsuffix, ZCand.M(), weight, 1500, 0., 1500.);
        FillHist(regionsSSWW.at(it_rg)+"/TriLep_Mass_"+IDsuffix, TriLep.M(), weight, 1500, 0., 1500.);
        FillHist(regionsSSWW.at(it_rg)+"/DiJet_Mass_"+IDsuffix, DiJet.M(), weight, 3000, 0., 3000.);
        FillHist(regionsSSWW.at(it_rg)+"/Mu1_Pt_"+IDsuffix, muons.at(0).Pt(), weight, 1500, 0., 1500.);
        FillHist(regionsSSWW.at(it_rg)+"/Mu2_Pt_"+IDsuffix, muons.at(1).Pt(), weight, 1500, 0., 1500.);
        FillHist(regionsSSWW.at(it_rg)+"/Mu3_Pt_"+IDsuffix, muons.at(2).Pt(), weight, 1500, 0., 1500.);
        FillHist(regionsSSWW.at(it_rg)+"/ZtagLep1_Pt_"+IDsuffix, ZtagLep1.Pt(), weight, 1500, 0., 1500.);
        FillHist(regionsSSWW.at(it_rg)+"/ZtagLep2_Pt_"+IDsuffix, ZtagLep2.Pt(), weight, 1500, 0., 1500.);
        FillHist(regionsSSWW.at(it_rg)+"/WtagLep_Pt_"+IDsuffix, WtagLep.Pt(), weight, 1500, 0., 1500.);
        FillHist(regionsSSWW.at(it_rg)+"/Mu1_Eta_"+IDsuffix, muons.at(0).Eta(), weight, 50, -2.5, 2.5);
        FillHist(regionsSSWW.at(it_rg)+"/Mu2_Eta_"+IDsuffix, muons.at(1).Eta(), weight, 50, -2.5, 2.5);
        FillHist(regionsSSWW.at(it_rg)+"/Mu3_Eta_"+IDsuffix, muons.at(2).Eta(), weight, 50, -2.5, 2.5);
        FillHist(regionsSSWW.at(it_rg)+"/ZtagLep1_Eta_"+IDsuffix, ZtagLep1.Eta(), weight, 50, -2.5, 2.5);
        FillHist(regionsSSWW.at(it_rg)+"/ZtagLep2_Eta_"+IDsuffix, ZtagLep2.Eta(), weight, 50, -2.5, 2.5);
        FillHist(regionsSSWW.at(it_rg)+"/WtagLep_Eta_"+IDsuffix, WtagLep.Eta(), weight, 50, -2.5, 2.5);
        FillHist(regionsSSWW.at(it_rg)+"/Jet1_Pt_"+IDsuffix, jets.at(0).Pt(), weight, 1500, 0., 1500.);
        FillHist(regionsSSWW.at(it_rg)+"/Jet2_Pt_"+IDsuffix, jets.at(1).Pt(), weight, 1500, 0., 1500.);
        FillHist(regionsSSWW.at(it_rg)+"/Jet1_Eta_"+IDsuffix, jets.at(0).Eta(), weight, 100, -5, 5);
        FillHist(regionsSSWW.at(it_rg)+"/Jet2_Eta_"+IDsuffix, jets.at(1).Eta(), weight, 100, -5, 5);
        FillHist(regionsSSWW.at(it_rg)+"/MET_"+IDsuffix, MET, weight, 1000, 0., 1000.);
        FillHist(regionsSSWW.at(it_rg)+"/Zep_"+IDsuffix, max_zep, weight, 150, 0., 1.5);
        FillHist(regionsSSWW.at(it_rg)+"/dEtajj_"+IDsuffix, dEta, weight, 100, 0., 10.);
        FillHist(regionsSSWW.at(it_rg)+"/HToverPt1_"+IDsuffix, HT/muons.at(0).Pt(), weight, 10, 0., 10.);
      }

    }

  } //SSWW SR, CR done

  // Now estimate if there are any SSWWTypeI signals falling into HNTypeI signal region

  for(unsigned int it_rg=0; it_rg<regionsTypeI.size(); it_rg++){

    if(! (muons.size()==2 && electrons.size()==0 && muons.at(0).Charge()*muons.at(1).Charge()==1) ) continue;
    if(RunFake){
      weight = 1.;
      weight *= fakeEst->GetWeight(leptons, param);
    }
    // Cutflow 4 : 2 same-sign tight muons (gen-matched)
    FillHist(regionsTypeI.at(it_rg)+"/Number_Events_"+IDsuffix, 3.5, weight, cutflow_bin, 0., cutflow_max);
    FillHist(regionsTypeI.at(it_rg)+"/Number_Events_unweighted_"+IDsuffix, 3.5, 1., cutflow_bin, 0., cutflow_max);

    if(HasFlag("Pt10")){
      if(! (muons.at(0).Pt()>20. && muons.at(1).Pt()>10.) ) continue;
    }
    else{
      if(! (muons.at(0).Pt()>20. && muons.at(1).Pt()>15.) ) continue; // Note I use pt > 15 GeV, due to WG, ZG sample
    }
    // Cutflow 5 : muon pt > 20/15 GeV
    FillHist(regionsTypeI.at(it_rg)+"/Number_Events_"+IDsuffix, 4.5, weight, cutflow_bin, 0., cutflow_max);
    FillHist(regionsTypeI.at(it_rg)+"/Number_Events_unweighted_"+IDsuffix, 4.5, 1., cutflow_bin, 0., cutflow_max);

    if(lepton_veto_size > 0) continue; // 3rd lepton veto
    // Cutflow 6 : 3rd lepton veto
    FillHist(regionsTypeI.at(it_rg)+"/Number_Events_"+IDsuffix, 5.5, weight, cutflow_bin, 0., cutflow_max);
    FillHist(regionsTypeI.at(it_rg)+"/Number_Events_unweighted_"+IDsuffix, 5.5, 1., cutflow_bin, 0., cutflow_max);

    DiLep = muons.at(0)+muons.at(1);
    double dPhi = fabs(muons.at(0).DeltaPhi(muons.at(1)));

    if(! (DiLep.M() > 10.) ) continue; // m(ll) > 10 GeV
    // Cutflow 7 : m(ll) > 10 GeV
    FillHist(regionsTypeI.at(it_rg)+"/Number_Events_"+IDsuffix, 6.5, weight, cutflow_bin, 0., cutflow_max);
    FillHist(regionsTypeI.at(it_rg)+"/Number_Events_unweighted_"+IDsuffix, 6.5, 1., cutflow_bin, 0., cutflow_max);

    if(! (Nbjet_medium == 0) ) continue;
    // Cutflow 8 : b-veto
    FillHist(regionsTypeI.at(it_rg)+"/Number_Events_"+IDsuffix, 7.5, weight, cutflow_bin, 0., cutflow_max);
    FillHist(regionsTypeI.at(it_rg)+"/Number_Events_unweighted_"+IDsuffix, 7.5, 1., cutflow_bin, 0., cutflow_max);

    if(it_rg==0){ // high SR1
      if(! (jets.size()>=2) ) continue;
      // Cutflow 9 : at least 2 jets
      FillHist(regionsTypeI.at(it_rg)+"/Number_Events_"+IDsuffix, 8.5, weight, cutflow_bin, 0., cutflow_max);
      FillHist(regionsTypeI.at(it_rg)+"/Number_Events_unweighted_"+IDsuffix, 8.5, 1., cutflow_bin, 0., cutflow_max);

      // Now let's invert the SSWW cut
      DiJet = jets.at(0)+jets.at(1);
      double avgEta = 0.5*(jets.at(0).Eta()+jets.at(1).Eta());
      double dEta = fabs(jets.at(0).Eta()-jets.at(1).Eta());
      double max_zep = std::max(fabs(muons.at(0).Eta()-avgEta),fabs(muons.at(1).Eta()-avgEta))/dEta;

      if(HasFlag("Pass_VBF")) {}
      else{
        if( (electrons.size()==0)&&(muons.at(0).Pt()>30. && muons.at(1).Pt()>30.)&&(DiLep.M()>20.)&&(max_zep<0.75)&&(jets.at(1).Pt()>30.)&&(dEta>2.5)&&(DiJet.M()>750.)&&(Nbjet_medium==0) ) continue;
      }
      // Cutflow 10 : SSWW signal failure
      FillHist(regionsTypeI.at(it_rg)+"/Number_Events_"+IDsuffix, 9.5, weight, cutflow_bin, 0., cutflow_max);
      FillHist(regionsTypeI.at(it_rg)+"/Number_Events_unweighted_"+IDsuffix, 9.5, 1., cutflow_bin, 0., cutflow_max);

      if(! (fatjets.size()==0) ) continue; // no fatjet
      // Cutflow 11 : no fatjet
      FillHist(regionsTypeI.at(it_rg)+"/Number_Events_"+IDsuffix, 10.5, weight, cutflow_bin, 0., cutflow_max);
      FillHist(regionsTypeI.at(it_rg)+"/Number_Events_unweighted_"+IDsuffix, 10.5, 1., cutflow_bin, 0., cutflow_max);

      // Select two jets that makes m(jj) closest to m(W)
      double tmpMassDiff = 10000.;
      int j1 = 0, j2 = 0;
      for(unsigned int k=0; k<jets.size(); k++){
        for(unsigned int l=k+1; l<jets.size(); l++){
          Wtemp = jets.at(k) + jets.at(l);
          if(fabs(Wtemp.M() - MW) < tmpMassDiff){
            tmpMassDiff = fabs(Wtemp.M() - MW);
            j1 = k; j2 = l; //JH : this saves (k,l) tuple if that combination gives a smaller difference than the former combination
          }
        }
      }
      WCand = jets.at(j1) + jets.at(j2);
      lljj = *leptons.at(0) + *leptons.at(1) + jets.at(j1) + jets.at(j2);
      l1jj = *leptons.at(0) + jets.at(j1) + jets.at(j2);
      l2jj = *leptons.at(1) + jets.at(j1) + jets.at(j2);

      if(! (30. < WCand.M() && WCand.M() < 150.) ) continue;
      // Cutflow 12 : 30 < m(WCand) < 150 GeV 
      FillHist(regionsTypeI.at(it_rg)+"/Number_Events_"+IDsuffix, 11.5, weight, cutflow_bin, 0., cutflow_max);
      FillHist(regionsTypeI.at(it_rg)+"/Number_Events_unweighted_"+IDsuffix, 11.5, 1., cutflow_bin, 0., cutflow_max);

      if(! (MET2ST < 15.) ) continue;
      // Cutflow 13 : MET2ST < 15 GeV
      FillHist(regionsTypeI.at(it_rg)+"/Number_Events_"+IDsuffix, 12.5, weight, cutflow_bin, 0., cutflow_max);
      FillHist(regionsTypeI.at(it_rg)+"/Number_Events_unweighted_"+IDsuffix, 12.5, 1., cutflow_bin, 0., cutflow_max);

      FillHist(regionsTypeI.at(it_rg)+"/Number_Jets_"+IDsuffix, jets.size(), weight, 10, 0., 10.);
      FillHist(regionsTypeI.at(it_rg)+"/Number_BJets_Loose_"+IDsuffix, Nbjet_loose, weight, 10, 0., 10.);
      FillHist(regionsTypeI.at(it_rg)+"/Number_BJets_Medium_"+IDsuffix, Nbjet_medium, weight, 10, 0., 10.);
      FillHist(regionsTypeI.at(it_rg)+"/Number_FatJets_"+IDsuffix, fatjets.size(), weight, 10, 0., 10.);
      FillHist(regionsTypeI.at(it_rg)+"/DiLep_Mass_"+IDsuffix, DiLep.M(), weight, 1500, 0., 1500.);
      FillHist(regionsTypeI.at(it_rg)+"/DiJet_Mass_"+IDsuffix, DiJet.M(), weight, 3000, 0., 3000.);
      FillHist(regionsTypeI.at(it_rg)+"/Mu1_Pt_"+IDsuffix, muons.at(0).Pt(), weight, 1500, 0., 1500.);
      FillHist(regionsTypeI.at(it_rg)+"/Mu2_Pt_"+IDsuffix, muons.at(1).Pt(), weight, 1500, 0., 1500.);
      FillHist(regionsTypeI.at(it_rg)+"/Mu1_Eta_"+IDsuffix, muons.at(0).Eta(), weight, 50, -2.5, 2.5);
      FillHist(regionsTypeI.at(it_rg)+"/Mu2_Eta_"+IDsuffix, muons.at(1).Eta(), weight, 50, -2.5, 2.5);
      FillHist(regionsTypeI.at(it_rg)+"/Jet1_Pt_"+IDsuffix, jets.at(0).Pt(), weight, 1500, 0., 1500.);
      FillHist(regionsTypeI.at(it_rg)+"/Jet2_Pt_"+IDsuffix, jets.at(1).Pt(), weight, 1500, 0., 1500.);
      FillHist(regionsTypeI.at(it_rg)+"/Jet1_Eta_"+IDsuffix, jets.at(0).Eta(), weight, 100, -5, 5);
      FillHist(regionsTypeI.at(it_rg)+"/Jet2_Eta_"+IDsuffix, jets.at(1).Eta(), weight, 100, -5, 5);
      FillHist(regionsTypeI.at(it_rg)+"/MET_"+IDsuffix, MET, weight, 1000, 0., 1000.);
      FillHist(regionsTypeI.at(it_rg)+"/MET2ST_"+IDsuffix, MET2ST, weight, 1000, 0., 1000.);
      FillHist(regionsTypeI.at(it_rg)+"/Zep_"+IDsuffix, max_zep, weight, 150, 0., 1.5);
      FillHist(regionsTypeI.at(it_rg)+"/dEtajj_"+IDsuffix, dEta, weight, 100, 0., 10.);
      FillHist(regionsTypeI.at(it_rg)+"/dPhill_"+IDsuffix, dPhi, weight, 32, 0., 3.2);
      FillHist(regionsTypeI.at(it_rg)+"/HToverPt1_"+IDsuffix, HT/muons.at(0).Pt(), weight, 10, 0., 10.);
      FillHist(regionsTypeI.at(it_rg)+"/WCand_Mass_"+IDsuffix, WCand.M(), weight, 1000, 0., 1000.);
      FillHist(regionsTypeI.at(it_rg)+"/lljj_Mass_"+IDsuffix, lljj.M(), weight, 2000, 0., 2000.);
      FillHist(regionsTypeI.at(it_rg)+"/l1jj_Mass_"+IDsuffix, l1jj.M(), weight, 2000, 0., 2000.);
      FillHist(regionsTypeI.at(it_rg)+"/l2jj_Mass_"+IDsuffix, l2jj.M(), weight, 2000, 0., 2000.);

      int Njet_out = 0;
      for(int i=0; i<jets.size(); i++){
        if(! (jets.at(i).Pt()>20.) ) Njet_out++;
        if(! (fabs(jets.at(i).Eta())<2.7) ) Njet_out++;
      }
      if(Njet_out==0){
        // Cutflow 14 : jet pt > 20, jet eta < 2.7
        FillHist(regionsTypeI.at(it_rg)+"/Number_Events_"+IDsuffix, 13.5, weight, cutflow_bin, 0., cutflow_max);
        FillHist(regionsTypeI.at(it_rg)+"/Number_Events_unweighted_"+IDsuffix, 13.5, 1., cutflow_bin, 0., cutflow_max);

        FillHist(regionsTypeI.at(it_rg)+"/jeta2p7/Number_Jets_"+IDsuffix, jets.size(), weight, 10, 0., 10.);
        FillHist(regionsTypeI.at(it_rg)+"/jeta2p7/Number_BJets_Loose_"+IDsuffix, Nbjet_loose, weight, 10, 0., 10.);
        FillHist(regionsTypeI.at(it_rg)+"/jeta2p7/Number_BJets_Medium_"+IDsuffix, Nbjet_medium, weight, 10, 0., 10.);
        FillHist(regionsTypeI.at(it_rg)+"/jeta2p7/Number_FatJets_"+IDsuffix, fatjets.size(), weight, 10, 0., 10.);
        FillHist(regionsTypeI.at(it_rg)+"/jeta2p7/DiLep_Mass_"+IDsuffix, DiLep.M(), weight, 1500, 0., 1500.);
        FillHist(regionsTypeI.at(it_rg)+"/jeta2p7/DiJet_Mass_"+IDsuffix, DiJet.M(), weight, 3000, 0., 3000.);
        FillHist(regionsTypeI.at(it_rg)+"/jeta2p7/Mu1_Pt_"+IDsuffix, muons.at(0).Pt(), weight, 1500, 0., 1500.);
        FillHist(regionsTypeI.at(it_rg)+"/jeta2p7/Mu2_Pt_"+IDsuffix, muons.at(1).Pt(), weight, 1500, 0., 1500.);
        FillHist(regionsTypeI.at(it_rg)+"/jeta2p7/Mu1_Eta_"+IDsuffix, muons.at(0).Eta(), weight, 50, -2.5, 2.5);
        FillHist(regionsTypeI.at(it_rg)+"/jeta2p7/Mu2_Eta_"+IDsuffix, muons.at(1).Eta(), weight, 50, -2.5, 2.5);
        FillHist(regionsTypeI.at(it_rg)+"/jeta2p7/Jet1_Pt_"+IDsuffix, jets.at(0).Pt(), weight, 1500, 0., 1500.);
        FillHist(regionsTypeI.at(it_rg)+"/jeta2p7/Jet2_Pt_"+IDsuffix, jets.at(1).Pt(), weight, 1500, 0., 1500.);
        FillHist(regionsTypeI.at(it_rg)+"/jeta2p7/Jet1_Eta_"+IDsuffix, jets.at(0).Eta(), weight, 100, -5, 5);
        FillHist(regionsTypeI.at(it_rg)+"/jeta2p7/Jet2_Eta_"+IDsuffix, jets.at(1).Eta(), weight, 100, -5, 5);
        FillHist(regionsTypeI.at(it_rg)+"/jeta2p7/MET_"+IDsuffix, MET, weight, 1000, 0., 1000.);
        FillHist(regionsTypeI.at(it_rg)+"/jeta2p7/MET2ST_"+IDsuffix, MET2ST, weight, 1000, 0., 1000.);
        FillHist(regionsTypeI.at(it_rg)+"/jeta2p7/Zep_"+IDsuffix, max_zep, weight, 150, 0., 1.5);
        FillHist(regionsTypeI.at(it_rg)+"/jeta2p7/dEtajj_"+IDsuffix, dEta, weight, 100, 0., 10.);
        FillHist(regionsTypeI.at(it_rg)+"/jeta2p7/dPhill_"+IDsuffix, dPhi, weight, 32, 0., 3.2);
        FillHist(regionsTypeI.at(it_rg)+"/jeta2p7/HToverPt1_"+IDsuffix, HT/muons.at(0).Pt(), weight, 10, 0., 10.);
        FillHist(regionsTypeI.at(it_rg)+"/jeta2p7/WCand_Mass_"+IDsuffix, WCand.M(), weight, 1000, 0., 1000.);
        FillHist(regionsTypeI.at(it_rg)+"/jeta2p7/lljj_Mass_"+IDsuffix, lljj.M(), weight, 2000, 0., 2000.);
        FillHist(regionsTypeI.at(it_rg)+"/jeta2p7/l1jj_Mass_"+IDsuffix, l1jj.M(), weight, 2000, 0., 2000.);
        FillHist(regionsTypeI.at(it_rg)+"/jeta2p7/l2jj_Mass_"+IDsuffix, l2jj.M(), weight, 2000, 0., 2000.);
      }
      if(jets.size()<4){
        // Cutflow 14 : M100 optimization - 1
        FillHist(regionsTypeI.at(it_rg)+"/M100/Number_Events_"+IDsuffix, 13.5, weight, cutflow_bin, 0., cutflow_max);
        FillHist(regionsTypeI.at(it_rg)+"/M100/Number_Events_unweighted_"+IDsuffix, 13.5, 1., cutflow_bin, 0., cutflow_max);
      }
      if(jets.size()<4 && jets.at(0).Pt()>25.){
        // Cutflow 15 : M100 optimization - 2
        FillHist(regionsTypeI.at(it_rg)+"/M100/Number_Events_"+IDsuffix, 14.5, weight, cutflow_bin, 0., cutflow_max);
        FillHist(regionsTypeI.at(it_rg)+"/M100/Number_Events_unweighted_"+IDsuffix, 14.5, 1., cutflow_bin, 0., cutflow_max);
      }
      if(jets.size()<4 && jets.at(0).Pt()>25. && leptons.at(1)->DeltaR(WCand)<3.1){
        // Cutflow 16 : M100 optimization - 3
        FillHist(regionsTypeI.at(it_rg)+"/M100/Number_Events_"+IDsuffix, 15.5, weight, cutflow_bin, 0., cutflow_max);
        FillHist(regionsTypeI.at(it_rg)+"/M100/Number_Events_unweighted_"+IDsuffix, 15.5, 1., cutflow_bin, 0., cutflow_max);
      }
      if(jets.size()<4 && jets.at(0).Pt()>25. && leptons.at(1)->DeltaR(WCand)<3.1 && leptons.at(0)->Pt()>25.){
        // Cutflow 17 : M100 optimization - 4
        FillHist(regionsTypeI.at(it_rg)+"/M100/Number_Events_"+IDsuffix, 16.5, weight, cutflow_bin, 0., cutflow_max);
        FillHist(regionsTypeI.at(it_rg)+"/M100/Number_Events_unweighted_"+IDsuffix, 16.5, 1., cutflow_bin, 0., cutflow_max);
      }
      if(jets.size()<4 && jets.at(0).Pt()>25. && leptons.at(1)->DeltaR(WCand)<3.1 && leptons.at(0)->Pt()>25. && leptons.at(1)->Pt()>15.){
        // Cutflow 18 : M100 optimization - 5
        FillHist(regionsTypeI.at(it_rg)+"/M100/Number_Events_"+IDsuffix, 17.5, weight, cutflow_bin, 0., cutflow_max);
        FillHist(regionsTypeI.at(it_rg)+"/M100/Number_Events_unweighted_"+IDsuffix, 17.5, 1., cutflow_bin, 0., cutflow_max);
      }
      if(jets.size()<4 && jets.at(0).Pt()>25. && leptons.at(1)->DeltaR(WCand)<3.1 && leptons.at(0)->Pt()>25. && leptons.at(1)->Pt()>15. && 50.<WCand.M()){
        // Cutflow 19 : M100 optimization - 6
        FillHist(regionsTypeI.at(it_rg)+"/M100/Number_Events_"+IDsuffix, 18.5, weight, cutflow_bin, 0., cutflow_max);
        FillHist(regionsTypeI.at(it_rg)+"/M100/Number_Events_unweighted_"+IDsuffix, 18.5, 1., cutflow_bin, 0., cutflow_max);
      }
      if(jets.size()<4 && jets.at(0).Pt()>25. && leptons.at(1)->DeltaR(WCand)<3.1 && leptons.at(0)->Pt()>25. && leptons.at(1)->Pt()>15. && 50.<WCand.M()&&WCand.M()<120.){
        // Cutflow 20 : M100 optimization - 7
        FillHist(regionsTypeI.at(it_rg)+"/M100/Number_Events_"+IDsuffix, 19.5, weight, cutflow_bin, 0., cutflow_max);
        FillHist(regionsTypeI.at(it_rg)+"/M100/Number_Events_unweighted_"+IDsuffix, 19.5, 1., cutflow_bin, 0., cutflow_max);
      }
      if(jets.size()<4 && jets.at(0).Pt()>25. && leptons.at(1)->DeltaR(WCand)<3.1 && leptons.at(0)->Pt()>25. && leptons.at(1)->Pt()>15. && 50.<WCand.M()&&WCand.M()<120. && lljj.M()>110.){
        // Cutflow 21 : M100 optimization - 8
        FillHist(regionsTypeI.at(it_rg)+"/M100/Number_Events_"+IDsuffix, 20.5, weight, cutflow_bin, 0., cutflow_max);
        FillHist(regionsTypeI.at(it_rg)+"/M100/Number_Events_unweighted_"+IDsuffix, 20.5, 1., cutflow_bin, 0., cutflow_max);
      }
      if(jets.size()<4 && jets.at(0).Pt()>25. && leptons.at(1)->DeltaR(WCand)<3.1 && leptons.at(0)->Pt()>25. && leptons.at(1)->Pt()>15. && 50.<WCand.M()&&WCand.M()<120. && lljj.M()>110. && 55.<l1jj.M()){
        // Cutflow 22 : M100 optimization - 9
        FillHist(regionsTypeI.at(it_rg)+"/M100/Number_Events_"+IDsuffix, 21.5, weight, cutflow_bin, 0., cutflow_max);
        FillHist(regionsTypeI.at(it_rg)+"/M100/Number_Events_unweighted_"+IDsuffix, 21.5, 1., cutflow_bin, 0., cutflow_max);
      }
      if(jets.size()<4 && jets.at(0).Pt()>25. && leptons.at(1)->DeltaR(WCand)<3.1 && leptons.at(0)->Pt()>25. && leptons.at(1)->Pt()>15. && 50.<WCand.M()&&WCand.M()<120. && lljj.M()>110. && ((55.<l1jj.M()&&l1jj.M()<115.)||(55.<l2jj.M()&&l2jj.M()<115.))){
        // Cutflow 23 : M100 optimization - 10
        FillHist(regionsTypeI.at(it_rg)+"/M100/Number_Events_"+IDsuffix, 22.5, weight, cutflow_bin, 0., cutflow_max);
        FillHist(regionsTypeI.at(it_rg)+"/M100/Number_Events_unweighted_"+IDsuffix, 22.5, 1., cutflow_bin, 0., cutflow_max);
      }
      if(jets.size()<4 && jets.at(0).Pt()>25. && leptons.at(1)->DeltaR(WCand)<3.1 && leptons.at(0)->Pt()>25. && leptons.at(1)->Pt()>15. && 50.<WCand.M()&&WCand.M()<120. && lljj.M()>110. && ((55.<l1jj.M()&&l1jj.M()<115.)||(55.<l2jj.M()&&l2jj.M()<115.)) && MET2ST<9.){
        // Cutflow 24 : M100 optimization - done
        FillHist(regionsTypeI.at(it_rg)+"/M100/Number_Events_"+IDsuffix, 23.5, weight, cutflow_bin, 0., cutflow_max);
        FillHist(regionsTypeI.at(it_rg)+"/M100/Number_Events_unweighted_"+IDsuffix, 23.5, 1., cutflow_bin, 0., cutflow_max);

        FillHist(regionsTypeI.at(it_rg)+"/M100/Number_Jets_"+IDsuffix, jets.size(), weight, 10, 0., 10.);
        FillHist(regionsTypeI.at(it_rg)+"/M100/Number_BJets_Loose_"+IDsuffix, Nbjet_loose, weight, 10, 0., 10.);
        FillHist(regionsTypeI.at(it_rg)+"/M100/Number_BJets_Medium_"+IDsuffix, Nbjet_medium, weight, 10, 0., 10.);
        FillHist(regionsTypeI.at(it_rg)+"/M100/Number_FatJets_"+IDsuffix, fatjets.size(), weight, 10, 0., 10.);
        FillHist(regionsTypeI.at(it_rg)+"/M100/DiLep_Mass_"+IDsuffix, DiLep.M(), weight, 1500, 0., 1500.);
        FillHist(regionsTypeI.at(it_rg)+"/M100/DiJet_Mass_"+IDsuffix, DiJet.M(), weight, 3000, 0., 3000.);
        FillHist(regionsTypeI.at(it_rg)+"/M100/Mu1_Pt_"+IDsuffix, muons.at(0).Pt(), weight, 1500, 0., 1500.);
        FillHist(regionsTypeI.at(it_rg)+"/M100/Mu2_Pt_"+IDsuffix, muons.at(1).Pt(), weight, 1500, 0., 1500.);
        FillHist(regionsTypeI.at(it_rg)+"/M100/Mu1_Eta_"+IDsuffix, muons.at(0).Eta(), weight, 50, -2.5, 2.5);
        FillHist(regionsTypeI.at(it_rg)+"/M100/Mu2_Eta_"+IDsuffix, muons.at(1).Eta(), weight, 50, -2.5, 2.5);
        FillHist(regionsTypeI.at(it_rg)+"/M100/Jet1_Pt_"+IDsuffix, jets.at(0).Pt(), weight, 1500, 0., 1500.);
        FillHist(regionsTypeI.at(it_rg)+"/M100/Jet2_Pt_"+IDsuffix, jets.at(1).Pt(), weight, 1500, 0., 1500.);
        FillHist(regionsTypeI.at(it_rg)+"/M100/Jet1_Eta_"+IDsuffix, jets.at(0).Eta(), weight, 100, -5, 5);
        FillHist(regionsTypeI.at(it_rg)+"/M100/Jet2_Eta_"+IDsuffix, jets.at(1).Eta(), weight, 100, -5, 5);
        FillHist(regionsTypeI.at(it_rg)+"/M100/MET_"+IDsuffix, MET, weight, 1000, 0., 1000.);
        FillHist(regionsTypeI.at(it_rg)+"/M100/MET2ST_"+IDsuffix, MET2ST, weight, 1000, 0., 1000.);
        FillHist(regionsTypeI.at(it_rg)+"/M100/Zep_"+IDsuffix, max_zep, weight, 150, 0., 1.5);
        FillHist(regionsTypeI.at(it_rg)+"/M100/dEtajj_"+IDsuffix, dEta, weight, 100, 0., 10.);
        FillHist(regionsTypeI.at(it_rg)+"/M100/dPhill_"+IDsuffix, dPhi, weight, 32, 0., 3.2);
        FillHist(regionsTypeI.at(it_rg)+"/M100/HToverPt1_"+IDsuffix, HT/muons.at(0).Pt(), weight, 10, 0., 10.);
        FillHist(regionsTypeI.at(it_rg)+"/M100/WCand_Mass_"+IDsuffix, WCand.M(), weight, 1000, 0., 1000.);
        FillHist(regionsTypeI.at(it_rg)+"/M100/lljj_Mass_"+IDsuffix, lljj.M(), weight, 2000, 0., 2000.);
        FillHist(regionsTypeI.at(it_rg)+"/M100/l1jj_Mass_"+IDsuffix, l1jj.M(), weight, 2000, 0., 2000.);
        FillHist(regionsTypeI.at(it_rg)+"/M100/l2jj_Mass_"+IDsuffix, l2jj.M(), weight, 2000, 0., 2000.);
      }
      if(jets.at(0).Pt()>25. && leptons.at(0)->Pt()>25. && leptons.at(1)->Pt()>15. && lljj.M()>110. && ((55.<l1jj.M()&&l1jj.M()<115.)||(55.<l2jj.M()&&l2jj.M()<115.)) && MET2ST<9.){
        // Cutflow 14 : M100 optimization from arxiv 1806.10905
        FillHist(regionsTypeI.at(it_rg)+"/M100_new/Number_Events_"+IDsuffix, 13.5, weight, cutflow_bin, 0., cutflow_max);
        FillHist(regionsTypeI.at(it_rg)+"/M100_new/Number_Events_unweighted_"+IDsuffix, 13.5, 1., cutflow_bin, 0., cutflow_max);

        FillHist(regionsTypeI.at(it_rg)+"/M100_new/Number_Jets_"+IDsuffix, jets.size(), weight, 10, 0., 10.);
        FillHist(regionsTypeI.at(it_rg)+"/M100_new/Number_BJets_Loose_"+IDsuffix, Nbjet_loose, weight, 10, 0., 10.);
        FillHist(regionsTypeI.at(it_rg)+"/M100_new/Number_BJets_Medium_"+IDsuffix, Nbjet_medium, weight, 10, 0., 10.);
        FillHist(regionsTypeI.at(it_rg)+"/M100_new/Number_FatJets_"+IDsuffix, fatjets.size(), weight, 10, 0., 10.);
        FillHist(regionsTypeI.at(it_rg)+"/M100_new/DiLep_Mass_"+IDsuffix, DiLep.M(), weight, 1500, 0., 1500.);
        FillHist(regionsTypeI.at(it_rg)+"/M100_new/DiJet_Mass_"+IDsuffix, DiJet.M(), weight, 3000, 0., 3000.);
        FillHist(regionsTypeI.at(it_rg)+"/M100_new/Mu1_Pt_"+IDsuffix, muons.at(0).Pt(), weight, 1500, 0., 1500.);
        FillHist(regionsTypeI.at(it_rg)+"/M100_new/Mu2_Pt_"+IDsuffix, muons.at(1).Pt(), weight, 1500, 0., 1500.);
        FillHist(regionsTypeI.at(it_rg)+"/M100_new/Mu1_Eta_"+IDsuffix, muons.at(0).Eta(), weight, 50, -2.5, 2.5);
        FillHist(regionsTypeI.at(it_rg)+"/M100_new/Mu2_Eta_"+IDsuffix, muons.at(1).Eta(), weight, 50, -2.5, 2.5);
        FillHist(regionsTypeI.at(it_rg)+"/M100_new/Jet1_Pt_"+IDsuffix, jets.at(0).Pt(), weight, 1500, 0., 1500.);
        FillHist(regionsTypeI.at(it_rg)+"/M100_new/Jet2_Pt_"+IDsuffix, jets.at(1).Pt(), weight, 1500, 0., 1500.);
        FillHist(regionsTypeI.at(it_rg)+"/M100_new/Jet1_Eta_"+IDsuffix, jets.at(0).Eta(), weight, 100, -5, 5);
        FillHist(regionsTypeI.at(it_rg)+"/M100_new/Jet2_Eta_"+IDsuffix, jets.at(1).Eta(), weight, 100, -5, 5);
        FillHist(regionsTypeI.at(it_rg)+"/M100_new/MET_"+IDsuffix, MET, weight, 1000, 0., 1000.);
        FillHist(regionsTypeI.at(it_rg)+"/M100_new/MET2ST_"+IDsuffix, MET2ST, weight, 1000, 0., 1000.);
        FillHist(regionsTypeI.at(it_rg)+"/M100_new/Zep_"+IDsuffix, max_zep, weight, 150, 0., 1.5);
        FillHist(regionsTypeI.at(it_rg)+"/M100_new/dEtajj_"+IDsuffix, dEta, weight, 100, 0., 10.);
        FillHist(regionsTypeI.at(it_rg)+"/M100_new/dPhill_"+IDsuffix, dPhi, weight, 32, 0., 3.2);
        FillHist(regionsTypeI.at(it_rg)+"/M100_new/HToverPt1_"+IDsuffix, HT/muons.at(0).Pt(), weight, 10, 0., 10.);
        FillHist(regionsTypeI.at(it_rg)+"/M100_new/WCand_Mass_"+IDsuffix, WCand.M(), weight, 1000, 0., 1000.);
        FillHist(regionsTypeI.at(it_rg)+"/M100_new/lljj_Mass_"+IDsuffix, lljj.M(), weight, 2000, 0., 2000.);
        FillHist(regionsTypeI.at(it_rg)+"/M100_new/l1jj_Mass_"+IDsuffix, l1jj.M(), weight, 2000, 0., 2000.);
        FillHist(regionsTypeI.at(it_rg)+"/M100_new/l2jj_Mass_"+IDsuffix, l2jj.M(), weight, 2000, 0., 2000.);
      }
      if(jets.size()<4 && jets.at(0).Pt()>25. && leptons.at(0)->Pt()>110. && leptons.at(1)->Pt()>60. && 50.<WCand.M()&&WCand.M()<120. && lljj.M()>610. && ((370.<l1jj.M()&&l1jj.M()<550.)||(370.<l2jj.M()&&l2jj.M()<550.)) && MET2ST<7.){
        // Cutflow 14 : M500 optimization
        FillHist(regionsTypeI.at(it_rg)+"/M500/Number_Events_"+IDsuffix, 13.5, weight, cutflow_bin, 0., cutflow_max);
        FillHist(regionsTypeI.at(it_rg)+"/M500/Number_Events_unweighted_"+IDsuffix, 13.5, 1., cutflow_bin, 0., cutflow_max);

        FillHist(regionsTypeI.at(it_rg)+"/M500/Number_Jets_"+IDsuffix, jets.size(), weight, 10, 0., 10.);
        FillHist(regionsTypeI.at(it_rg)+"/M500/Number_BJets_Loose_"+IDsuffix, Nbjet_loose, weight, 10, 0., 10.);
        FillHist(regionsTypeI.at(it_rg)+"/M500/Number_BJets_Medium_"+IDsuffix, Nbjet_medium, weight, 10, 0., 10.);
        FillHist(regionsTypeI.at(it_rg)+"/M500/Number_FatJets_"+IDsuffix, fatjets.size(), weight, 10, 0., 10.);
        FillHist(regionsTypeI.at(it_rg)+"/M500/DiLep_Mass_"+IDsuffix, DiLep.M(), weight, 1500, 0., 1500.);
        FillHist(regionsTypeI.at(it_rg)+"/M500/DiJet_Mass_"+IDsuffix, DiJet.M(), weight, 3000, 0., 3000.);
        FillHist(regionsTypeI.at(it_rg)+"/M500/Mu1_Pt_"+IDsuffix, muons.at(0).Pt(), weight, 1500, 0., 1500.);
        FillHist(regionsTypeI.at(it_rg)+"/M500/Mu2_Pt_"+IDsuffix, muons.at(1).Pt(), weight, 1500, 0., 1500.);
        FillHist(regionsTypeI.at(it_rg)+"/M500/Mu1_Eta_"+IDsuffix, muons.at(0).Eta(), weight, 50, -2.5, 2.5);
        FillHist(regionsTypeI.at(it_rg)+"/M500/Mu2_Eta_"+IDsuffix, muons.at(1).Eta(), weight, 50, -2.5, 2.5);
        FillHist(regionsTypeI.at(it_rg)+"/M500/Jet1_Pt_"+IDsuffix, jets.at(0).Pt(), weight, 1500, 0., 1500.);
        FillHist(regionsTypeI.at(it_rg)+"/M500/Jet2_Pt_"+IDsuffix, jets.at(1).Pt(), weight, 1500, 0., 1500.);
        FillHist(regionsTypeI.at(it_rg)+"/M500/Jet1_Eta_"+IDsuffix, jets.at(0).Eta(), weight, 100, -5, 5);
        FillHist(regionsTypeI.at(it_rg)+"/M500/Jet2_Eta_"+IDsuffix, jets.at(1).Eta(), weight, 100, -5, 5);
        FillHist(regionsTypeI.at(it_rg)+"/M500/MET_"+IDsuffix, MET, weight, 1000, 0., 1000.);
        FillHist(regionsTypeI.at(it_rg)+"/M500/MET2ST_"+IDsuffix, MET2ST, weight, 1000, 0., 1000.);
        FillHist(regionsTypeI.at(it_rg)+"/M500/Zep_"+IDsuffix, max_zep, weight, 150, 0., 1.5);
        FillHist(regionsTypeI.at(it_rg)+"/M500/dEtajj_"+IDsuffix, dEta, weight, 100, 0., 10.);
        FillHist(regionsTypeI.at(it_rg)+"/M500/dPhill_"+IDsuffix, dPhi, weight, 32, 0., 3.2);
        FillHist(regionsTypeI.at(it_rg)+"/M500/HToverPt1_"+IDsuffix, HT/muons.at(0).Pt(), weight, 10, 0., 10.);
        FillHist(regionsTypeI.at(it_rg)+"/M500/WCand_Mass_"+IDsuffix, WCand.M(), weight, 1000, 0., 1000.);
        FillHist(regionsTypeI.at(it_rg)+"/M500/lljj_Mass_"+IDsuffix, lljj.M(), weight, 2000, 0., 2000.);
        FillHist(regionsTypeI.at(it_rg)+"/M500/l1jj_Mass_"+IDsuffix, l1jj.M(), weight, 2000, 0., 2000.);
        FillHist(regionsTypeI.at(it_rg)+"/M500/l2jj_Mass_"+IDsuffix, l2jj.M(), weight, 2000, 0., 2000.);
      }
      if(jets.size()<4 && jets.at(0).Pt()>25. && leptons.at(0)->Pt()>110. && 50.<WCand.M()&&WCand.M()<120. && lljj.M()>800. && ((370.<l1jj.M()&&l1jj.M()<1230.)||(370.<l2jj.M()&&l2jj.M()<1230.)) && MET2ST<7.){
        // Cutflow 14 : M1000 optimization
        FillHist(regionsTypeI.at(it_rg)+"/M1000/Number_Events_"+IDsuffix, 13.5, weight, cutflow_bin, 0., cutflow_max);
        FillHist(regionsTypeI.at(it_rg)+"/M1000/Number_Events_unweighted_"+IDsuffix, 13.5, 1., cutflow_bin, 0., cutflow_max);

        FillHist(regionsTypeI.at(it_rg)+"/M1000/Number_Jets_"+IDsuffix, jets.size(), weight, 10, 0., 10.);
        FillHist(regionsTypeI.at(it_rg)+"/M1000/Number_BJets_Loose_"+IDsuffix, Nbjet_loose, weight, 10, 0., 10.);
        FillHist(regionsTypeI.at(it_rg)+"/M1000/Number_BJets_Medium_"+IDsuffix, Nbjet_medium, weight, 10, 0., 10.);
        FillHist(regionsTypeI.at(it_rg)+"/M1000/Number_FatJets_"+IDsuffix, fatjets.size(), weight, 10, 0., 10.);
        FillHist(regionsTypeI.at(it_rg)+"/M1000/DiLep_Mass_"+IDsuffix, DiLep.M(), weight, 1500, 0., 1500.);
        FillHist(regionsTypeI.at(it_rg)+"/M1000/DiJet_Mass_"+IDsuffix, DiJet.M(), weight, 3000, 0., 3000.);
        FillHist(regionsTypeI.at(it_rg)+"/M1000/Mu1_Pt_"+IDsuffix, muons.at(0).Pt(), weight, 1500, 0., 1500.);
        FillHist(regionsTypeI.at(it_rg)+"/M1000/Mu2_Pt_"+IDsuffix, muons.at(1).Pt(), weight, 1500, 0., 1500.);
        FillHist(regionsTypeI.at(it_rg)+"/M1000/Mu1_Eta_"+IDsuffix, muons.at(0).Eta(), weight, 50, -2.5, 2.5);
        FillHist(regionsTypeI.at(it_rg)+"/M1000/Mu2_Eta_"+IDsuffix, muons.at(1).Eta(), weight, 50, -2.5, 2.5);
        FillHist(regionsTypeI.at(it_rg)+"/M1000/Jet1_Pt_"+IDsuffix, jets.at(0).Pt(), weight, 1500, 0., 1500.);
        FillHist(regionsTypeI.at(it_rg)+"/M1000/Jet2_Pt_"+IDsuffix, jets.at(1).Pt(), weight, 1500, 0., 1500.);
        FillHist(regionsTypeI.at(it_rg)+"/M1000/Jet1_Eta_"+IDsuffix, jets.at(0).Eta(), weight, 100, -5, 5);
        FillHist(regionsTypeI.at(it_rg)+"/M1000/Jet2_Eta_"+IDsuffix, jets.at(1).Eta(), weight, 100, -5, 5);
        FillHist(regionsTypeI.at(it_rg)+"/M1000/MET_"+IDsuffix, MET, weight, 1000, 0., 1000.);
        FillHist(regionsTypeI.at(it_rg)+"/M1000/MET2ST_"+IDsuffix, MET2ST, weight, 1000, 0., 1000.);
        FillHist(regionsTypeI.at(it_rg)+"/M1000/Zep_"+IDsuffix, max_zep, weight, 150, 0., 1.5);
        FillHist(regionsTypeI.at(it_rg)+"/M1000/dEtajj_"+IDsuffix, dEta, weight, 100, 0., 10.);
        FillHist(regionsTypeI.at(it_rg)+"/M1000/dPhill_"+IDsuffix, dPhi, weight, 32, 0., 3.2);
        FillHist(regionsTypeI.at(it_rg)+"/M1000/HToverPt1_"+IDsuffix, HT/muons.at(0).Pt(), weight, 10, 0., 10.);
        FillHist(regionsTypeI.at(it_rg)+"/M1000/WCand_Mass_"+IDsuffix, WCand.M(), weight, 1000, 0., 1000.);
        FillHist(regionsTypeI.at(it_rg)+"/M1000/lljj_Mass_"+IDsuffix, lljj.M(), weight, 2000, 0., 2000.);
        FillHist(regionsTypeI.at(it_rg)+"/M1000/l1jj_Mass_"+IDsuffix, l1jj.M(), weight, 2000, 0., 2000.);
        FillHist(regionsTypeI.at(it_rg)+"/M1000/l2jj_Mass_"+IDsuffix, l2jj.M(), weight, 2000, 0., 2000.);
      }
      if(jets.size()<4 && jets.at(0).Pt()>25. && leptons.at(0)->Pt()>110. && 50.<WCand.M()&&WCand.M()<120. && lljj.M()>800. && ((370.<l1jj.M()&&l1jj.M()<2220.)||(370.<l2jj.M()&&l2jj.M()<2220.)) && MET2ST<7.){
        // Cutflow 14 : M1500 optimization
        FillHist(regionsTypeI.at(it_rg)+"/M1500/Number_Events_"+IDsuffix, 13.5, weight, cutflow_bin, 0., cutflow_max);
        FillHist(regionsTypeI.at(it_rg)+"/M1500/Number_Events_unweighted_"+IDsuffix, 13.5, 1., cutflow_bin, 0., cutflow_max);

        FillHist(regionsTypeI.at(it_rg)+"/M1500/Number_Jets_"+IDsuffix, jets.size(), weight, 10, 0., 10.);
        FillHist(regionsTypeI.at(it_rg)+"/M1500/Number_BJets_Loose_"+IDsuffix, Nbjet_loose, weight, 10, 0., 10.);
        FillHist(regionsTypeI.at(it_rg)+"/M1500/Number_BJets_Medium_"+IDsuffix, Nbjet_medium, weight, 10, 0., 10.);
        FillHist(regionsTypeI.at(it_rg)+"/M1500/Number_FatJets_"+IDsuffix, fatjets.size(), weight, 10, 0., 10.);
        FillHist(regionsTypeI.at(it_rg)+"/M1500/DiLep_Mass_"+IDsuffix, DiLep.M(), weight, 1500, 0., 1500.);
        FillHist(regionsTypeI.at(it_rg)+"/M1500/DiJet_Mass_"+IDsuffix, DiJet.M(), weight, 3000, 0., 3000.);
        FillHist(regionsTypeI.at(it_rg)+"/M1500/Mu1_Pt_"+IDsuffix, muons.at(0).Pt(), weight, 1500, 0., 1500.);
        FillHist(regionsTypeI.at(it_rg)+"/M1500/Mu2_Pt_"+IDsuffix, muons.at(1).Pt(), weight, 1500, 0., 1500.);
        FillHist(regionsTypeI.at(it_rg)+"/M1500/Mu1_Eta_"+IDsuffix, muons.at(0).Eta(), weight, 50, -2.5, 2.5);
        FillHist(regionsTypeI.at(it_rg)+"/M1500/Mu2_Eta_"+IDsuffix, muons.at(1).Eta(), weight, 50, -2.5, 2.5);
        FillHist(regionsTypeI.at(it_rg)+"/M1500/Jet1_Pt_"+IDsuffix, jets.at(0).Pt(), weight, 1500, 0., 1500.);
        FillHist(regionsTypeI.at(it_rg)+"/M1500/Jet2_Pt_"+IDsuffix, jets.at(1).Pt(), weight, 1500, 0., 1500.);
        FillHist(regionsTypeI.at(it_rg)+"/M1500/Jet1_Eta_"+IDsuffix, jets.at(0).Eta(), weight, 100, -5, 5);
        FillHist(regionsTypeI.at(it_rg)+"/M1500/Jet2_Eta_"+IDsuffix, jets.at(1).Eta(), weight, 100, -5, 5);
        FillHist(regionsTypeI.at(it_rg)+"/M1500/MET_"+IDsuffix, MET, weight, 1000, 0., 1000.);
        FillHist(regionsTypeI.at(it_rg)+"/M1500/MET2ST_"+IDsuffix, MET2ST, weight, 1000, 0., 1000.);
        FillHist(regionsTypeI.at(it_rg)+"/M1500/Zep_"+IDsuffix, max_zep, weight, 150, 0., 1.5);
        FillHist(regionsTypeI.at(it_rg)+"/M1500/dEtajj_"+IDsuffix, dEta, weight, 100, 0., 10.);
        FillHist(regionsTypeI.at(it_rg)+"/M1500/dPhill_"+IDsuffix, dPhi, weight, 32, 0., 3.2);
        FillHist(regionsTypeI.at(it_rg)+"/M1500/HToverPt1_"+IDsuffix, HT/muons.at(0).Pt(), weight, 10, 0., 10.);
        FillHist(regionsTypeI.at(it_rg)+"/M1500/WCand_Mass_"+IDsuffix, WCand.M(), weight, 1000, 0., 1000.);
        FillHist(regionsTypeI.at(it_rg)+"/M1500/lljj_Mass_"+IDsuffix, lljj.M(), weight, 2000, 0., 2000.);
        FillHist(regionsTypeI.at(it_rg)+"/M1500/l1jj_Mass_"+IDsuffix, l1jj.M(), weight, 2000, 0., 2000.);
        FillHist(regionsTypeI.at(it_rg)+"/M1500/l2jj_Mass_"+IDsuffix, l2jj.M(), weight, 2000, 0., 2000.);
      }
    }
    else if(it_rg==1){ // high SR1 w/ 1 jet
      if(! (jets.size()==1 && fatjets.size()==0) ) continue;
      // Cutflow 9 : only 1 jet, no fatjet
      FillHist(regionsTypeI.at(it_rg)+"/Number_Events_"+IDsuffix, 8.5, weight, cutflow_bin, 0., cutflow_max);
      FillHist(regionsTypeI.at(it_rg)+"/Number_Events_unweighted_"+IDsuffix, 8.5, 1., cutflow_bin, 0., cutflow_max);

      FillHist(regionsTypeI.at(it_rg)+"/Number_Jets_"+IDsuffix, jets.size(), weight, 10, 0., 10.);
      FillHist(regionsTypeI.at(it_rg)+"/Number_BJets_Loose_"+IDsuffix, Nbjet_loose, weight, 10, 0., 10.);
      FillHist(regionsTypeI.at(it_rg)+"/Number_BJets_Medium_"+IDsuffix, Nbjet_medium, weight, 10, 0., 10.);
      FillHist(regionsTypeI.at(it_rg)+"/Number_FatJets_"+IDsuffix, fatjets.size(), weight, 10, 0., 10.);
      FillHist(regionsTypeI.at(it_rg)+"/DiLep_Mass_"+IDsuffix, DiLep.M(), weight, 1500, 0., 1500.);
      FillHist(regionsTypeI.at(it_rg)+"/Mu1_Pt_"+IDsuffix, muons.at(0).Pt(), weight, 1500, 0., 1500.);
      FillHist(regionsTypeI.at(it_rg)+"/Mu2_Pt_"+IDsuffix, muons.at(1).Pt(), weight, 1500, 0., 1500.);
      FillHist(regionsTypeI.at(it_rg)+"/Mu1_Eta_"+IDsuffix, muons.at(0).Eta(), weight, 50, -2.5, 2.5);
      FillHist(regionsTypeI.at(it_rg)+"/Mu2_Eta_"+IDsuffix, muons.at(1).Eta(), weight, 50, -2.5, 2.5);
      FillHist(regionsTypeI.at(it_rg)+"/Jet1_Pt_"+IDsuffix, jets.at(0).Pt(), weight, 1500, 0., 1500.);
      FillHist(regionsTypeI.at(it_rg)+"/Jet1_Eta_"+IDsuffix, jets.at(0).Eta(), weight, 100, -5, 5);
      FillHist(regionsTypeI.at(it_rg)+"/MET_"+IDsuffix, MET, weight, 1000, 0., 1000.);
      FillHist(regionsTypeI.at(it_rg)+"/dPhill_"+IDsuffix, dPhi, weight, 32, 0., 3.2);
      FillHist(regionsTypeI.at(it_rg)+"/HToverPt1_"+IDsuffix, HT/muons.at(0).Pt(), weight, 10, 0., 10.);

      if(jets.at(0).Pt()>20. && fabs(jets.at(0).Eta())<2.7){
        // Cutflow 10 : jet pt > 20, jet eta < 2.7
        FillHist(regionsTypeI.at(it_rg)+"/Number_Events_"+IDsuffix, 9.5, weight, cutflow_bin, 0., cutflow_max);
        FillHist(regionsTypeI.at(it_rg)+"/Number_Events_unweighted_"+IDsuffix, 9.5, 1., cutflow_bin, 0., cutflow_max);

        FillHist(regionsTypeI.at(it_rg)+"/jeta2p7/Number_Jets_"+IDsuffix, jets.size(), weight, 10, 0., 10.);
        FillHist(regionsTypeI.at(it_rg)+"/jeta2p7/Number_BJets_Loose_"+IDsuffix, Nbjet_loose, weight, 10, 0., 10.);
        FillHist(regionsTypeI.at(it_rg)+"/jeta2p7/Number_BJets_Medium_"+IDsuffix, Nbjet_medium, weight, 10, 0., 10.);
        FillHist(regionsTypeI.at(it_rg)+"/jeta2p7/Number_FatJets_"+IDsuffix, fatjets.size(), weight, 10, 0., 10.);
        FillHist(regionsTypeI.at(it_rg)+"/jeta2p7/DiLep_Mass_"+IDsuffix, DiLep.M(), weight, 1500, 0., 1500.);
        FillHist(regionsTypeI.at(it_rg)+"/jeta2p7/Mu1_Pt_"+IDsuffix, muons.at(0).Pt(), weight, 1500, 0., 1500.);
        FillHist(regionsTypeI.at(it_rg)+"/jeta2p7/Mu2_Pt_"+IDsuffix, muons.at(1).Pt(), weight, 1500, 0., 1500.);
        FillHist(regionsTypeI.at(it_rg)+"/jeta2p7/Mu1_Eta_"+IDsuffix, muons.at(0).Eta(), weight, 50, -2.5, 2.5);
        FillHist(regionsTypeI.at(it_rg)+"/jeta2p7/Mu2_Eta_"+IDsuffix, muons.at(1).Eta(), weight, 50, -2.5, 2.5);
        FillHist(regionsTypeI.at(it_rg)+"/jeta2p7/Jet1_Pt_"+IDsuffix, jets.at(0).Pt(), weight, 1500, 0., 1500.);
        FillHist(regionsTypeI.at(it_rg)+"/jeta2p7/Jet1_Eta_"+IDsuffix, jets.at(0).Eta(), weight, 100, -5, 5);
        FillHist(regionsTypeI.at(it_rg)+"/jeta2p7/MET_"+IDsuffix, MET, weight, 1000, 0., 1000.);
        FillHist(regionsTypeI.at(it_rg)+"/jeta2p7/dPhill_"+IDsuffix, dPhi, weight, 32, 0., 3.2);
        FillHist(regionsTypeI.at(it_rg)+"/jeta2p7/HToverPt1_"+IDsuffix, HT/muons.at(0).Pt(), weight, 10, 0., 10.);
      }
    }
    else if(it_rg==2){ // high SR2
      if(HasFlag("fatjet_veto")){
        if(! (fatjets.size()>0) ) continue; // at least 1 fatjet
      }
      else{
        if(! (jets.size()<2 && fatjets.size()>0) ) continue; // at best 1 jet && at least 1 fatjet
      }
      // Cutflow 9 : (at best 1 jet), at least 1 fatjet
      FillHist(regionsTypeI.at(it_rg)+"/Number_Events_"+IDsuffix, 8.5, weight, cutflow_bin, 0., cutflow_max);
      FillHist(regionsTypeI.at(it_rg)+"/Number_Events_unweighted_"+IDsuffix, 8.5, 1., cutflow_bin, 0., cutflow_max);

      double tmpMassDiff = 10000.;
      int j3 = 0;
      for(unsigned int k=0; k<fatjets.size(); k++){
        if(fabs(fatjets.at(k).M() - MW) < tmpMassDiff){
          tmpMassDiff = fabs(fatjets.at(k).SDMass() - MW);
          j3 = k;
        }
      }
      l1J = *leptons.at(0) + fatjets.at(j3);
      l2J = *leptons.at(1) + fatjets.at(j3);

      if(! (fatjets.at(j3).SDMass() < 150.) ) continue;
      // Cutflow 10 : m(WCand) < 150 GeV 
      FillHist(regionsTypeI.at(it_rg)+"/Number_Events_"+IDsuffix, 9.5, weight, cutflow_bin, 0., cutflow_max);
      FillHist(regionsTypeI.at(it_rg)+"/Number_Events_unweighted_"+IDsuffix, 9.5, 1., cutflow_bin, 0., cutflow_max);

      if(! (MET2ST < 15.) ) continue;
      // Cutflow 11 : MET2ST < 15 GeV
      FillHist(regionsTypeI.at(it_rg)+"/Number_Events_"+IDsuffix, 10.5, weight, cutflow_bin, 0., cutflow_max);
      FillHist(regionsTypeI.at(it_rg)+"/Number_Events_unweighted_"+IDsuffix, 10.5, 1., cutflow_bin, 0., cutflow_max);

      FillHist(regionsTypeI.at(it_rg)+"/Number_Jets_"+IDsuffix, jets.size(), weight, 10, 0., 10.);
      FillHist(regionsTypeI.at(it_rg)+"/Number_BJets_Loose_"+IDsuffix, Nbjet_loose, weight, 10, 0., 10.);
      FillHist(regionsTypeI.at(it_rg)+"/Number_BJets_Medium_"+IDsuffix, Nbjet_medium, weight, 10, 0., 10.);
      FillHist(regionsTypeI.at(it_rg)+"/Number_FatJets_"+IDsuffix, fatjets.size(), weight, 10, 0., 10.);
      FillHist(regionsTypeI.at(it_rg)+"/DiLep_Mass_"+IDsuffix, DiLep.M(), weight, 1500, 0., 1500.);
      FillHist(regionsTypeI.at(it_rg)+"/Mu1_Pt_"+IDsuffix, muons.at(0).Pt(), weight, 1500, 0., 1500.);
      FillHist(regionsTypeI.at(it_rg)+"/Mu2_Pt_"+IDsuffix, muons.at(1).Pt(), weight, 1500, 0., 1500.);
      FillHist(regionsTypeI.at(it_rg)+"/Mu1_Eta_"+IDsuffix, muons.at(0).Eta(), weight, 50, -2.5, 2.5);
      FillHist(regionsTypeI.at(it_rg)+"/Mu2_Eta_"+IDsuffix, muons.at(1).Eta(), weight, 50, -2.5, 2.5);
      FillHist(regionsTypeI.at(it_rg)+"/FatJet_Pt_"+IDsuffix, fatjets.at(j3).Pt(), weight, 1500, 0., 1500.);
      FillHist(regionsTypeI.at(it_rg)+"/FatJet_Eta_"+IDsuffix, fatjets.at(j3).Eta(), weight, 100, -5, 5);
      FillHist(regionsTypeI.at(it_rg)+"/FatJet_Mass_"+IDsuffix, fatjets.at(j3).SDMass(), weight, 1500, 0., 1500.);
      FillHist(regionsTypeI.at(it_rg)+"/l1J_Mass_"+IDsuffix, l1J.M(), weight, 2000, 0., 2000.);
      FillHist(regionsTypeI.at(it_rg)+"/l2J_Mass_"+IDsuffix, l2J.M(), weight, 2000, 0., 2000.);
      if(jets.size()>0){
        FillHist(regionsTypeI.at(it_rg)+"/Jet1_Pt_"+IDsuffix, jets.at(0).Pt(), weight, 1500, 0., 1500.);
        FillHist(regionsTypeI.at(it_rg)+"/Jet1_Eta_"+IDsuffix, jets.at(0).Eta(), weight, 100, -5, 5);
      }
      if(jets.size()>1){
        FillHist(regionsTypeI.at(it_rg)+"/Jet2_Pt_"+IDsuffix, jets.at(1).Pt(), weight, 1500, 0., 1500.);
        FillHist(regionsTypeI.at(it_rg)+"/Jet2_Eta_"+IDsuffix, jets.at(1).Eta(), weight, 100, -5, 5);
        FillHist(regionsTypeI.at(it_rg)+"/DiJet_Mass_"+IDsuffix, DiJet.M(), weight, 3000, 0., 3000.);
      }
      FillHist(regionsTypeI.at(it_rg)+"/MET_"+IDsuffix, MET, weight, 1000, 0., 1000.);
      FillHist(regionsTypeI.at(it_rg)+"/MET2ST_"+IDsuffix, MET2ST, weight, 1000, 0., 1000.);
      FillHist(regionsTypeI.at(it_rg)+"/dPhill_"+IDsuffix, dPhi, weight, 32, 0., 3.2);
      FillHist(regionsTypeI.at(it_rg)+"/HToverPt1_"+IDsuffix, HT/muons.at(0).Pt(), weight, 10, 0., 10.);

      int Njet_out = 0;
      for(int i=0; i<jets.size(); i++){
        if(! (jets.at(i).Pt()>20.) ) Njet_out++;
        if(! (fabs(jets.at(i).Eta())<2.7) ) Njet_out++;
      }
      if(Njet_out==0){
        // Cutflow 12 : jet pt > 20, jet eta < 2.7
        FillHist(regionsTypeI.at(it_rg)+"/Number_Events_"+IDsuffix, 11.5, weight, cutflow_bin, 0., cutflow_max);
        FillHist(regionsTypeI.at(it_rg)+"/Number_Events_unweighted_"+IDsuffix, 11.5, 1., cutflow_bin, 0., cutflow_max);

        FillHist(regionsTypeI.at(it_rg)+"/jeta2p7/Number_Jets_"+IDsuffix, jets.size(), weight, 10, 0., 10.);
        FillHist(regionsTypeI.at(it_rg)+"/jeta2p7/Number_BJets_Loose_"+IDsuffix, Nbjet_loose, weight, 10, 0., 10.);
        FillHist(regionsTypeI.at(it_rg)+"/jeta2p7/Number_BJets_Medium_"+IDsuffix, Nbjet_medium, weight, 10, 0., 10.);
        FillHist(regionsTypeI.at(it_rg)+"/jeta2p7/Number_FatJets_"+IDsuffix, fatjets.size(), weight, 10, 0., 10.);
        FillHist(regionsTypeI.at(it_rg)+"/jeta2p7/DiLep_Mass_"+IDsuffix, DiLep.M(), weight, 1500, 0., 1500.);
        FillHist(regionsTypeI.at(it_rg)+"/jeta2p7/Mu1_Pt_"+IDsuffix, muons.at(0).Pt(), weight, 1500, 0., 1500.);
        FillHist(regionsTypeI.at(it_rg)+"/jeta2p7/Mu2_Pt_"+IDsuffix, muons.at(1).Pt(), weight, 1500, 0., 1500.);
        FillHist(regionsTypeI.at(it_rg)+"/jeta2p7/Mu1_Eta_"+IDsuffix, muons.at(0).Eta(), weight, 50, -2.5, 2.5);
        FillHist(regionsTypeI.at(it_rg)+"/jeta2p7/Mu2_Eta_"+IDsuffix, muons.at(1).Eta(), weight, 50, -2.5, 2.5);
        if(jets.size()>0){
          FillHist(regionsTypeI.at(it_rg)+"/jeta2p7/Jet1_Pt_"+IDsuffix, jets.at(0).Pt(), weight, 1500, 0., 1500.);
          FillHist(regionsTypeI.at(it_rg)+"/jeta2p7/Jet1_Eta_"+IDsuffix, jets.at(0).Eta(), weight, 100, -5, 5);
        }
        if(jets.size()>1){
          FillHist(regionsTypeI.at(it_rg)+"/jeta2p7/Jet2_Pt_"+IDsuffix, jets.at(1).Pt(), weight, 1500, 0., 1500.);
          FillHist(regionsTypeI.at(it_rg)+"/jeta2p7/Jet2_Eta_"+IDsuffix, jets.at(1).Eta(), weight, 100, -5, 5);
          FillHist(regionsTypeI.at(it_rg)+"/jeta2p7/DiJet_Mass_"+IDsuffix, DiJet.M(), weight, 3000, 0., 3000.);
        }
        FillHist(regionsTypeI.at(it_rg)+"/jeta2p7/FatJet_Pt_"+IDsuffix, fatjets.at(j3).Pt(), weight, 1500, 0., 1500.);
        FillHist(regionsTypeI.at(it_rg)+"/jeta2p7/FatJet_Eta_"+IDsuffix, fatjets.at(j3).Eta(), weight, 100, -5, 5);
        FillHist(regionsTypeI.at(it_rg)+"/jeta2p7/FatJet_Mass_"+IDsuffix, fatjets.at(j3).SDMass(), weight, 1500, 0., 1500.);
        FillHist(regionsTypeI.at(it_rg)+"/jeta2p7/l1J_Mass_"+IDsuffix, l1J.M(), weight, 2000, 0., 2000.);
        FillHist(regionsTypeI.at(it_rg)+"/jeta2p7/l2J_Mass_"+IDsuffix, l2J.M(), weight, 2000, 0., 2000.);
        FillHist(regionsTypeI.at(it_rg)+"/jeta2p7/MET_"+IDsuffix, MET, weight, 1000, 0., 1000.);
        FillHist(regionsTypeI.at(it_rg)+"/jeta2p7/MET2ST_"+IDsuffix, MET2ST, weight, 1000, 0., 1000.);
        FillHist(regionsTypeI.at(it_rg)+"/jeta2p7/dPhill_"+IDsuffix, dPhi, weight, 32, 0., 3.2);
        FillHist(regionsTypeI.at(it_rg)+"/jeta2p7/HToverPt1_"+IDsuffix, HT/muons.at(0).Pt(), weight, 10, 0., 10.);
      }
      if(leptons.at(0)->Pt()>25. && leptons.at(1)->Pt()>15. && 40.<fatjets.at(j3).M()&&fatjets.at(j3).M()<130. && 98.<l1J.M()&&l1J.M()<145.){
        // Cutflow 12 : M100 optimization
        FillHist(regionsTypeI.at(it_rg)+"/M100/Number_Events_"+IDsuffix, 11.5, weight, cutflow_bin, 0., cutflow_max);
        FillHist(regionsTypeI.at(it_rg)+"/M100/Number_Events_unweighted_"+IDsuffix, 11.5, 1., cutflow_bin, 0., cutflow_max);

        FillHist(regionsTypeI.at(it_rg)+"/M100/Number_Jets_"+IDsuffix, jets.size(), weight, 10, 0., 10.);
        FillHist(regionsTypeI.at(it_rg)+"/M100/Number_BJets_Loose_"+IDsuffix, Nbjet_loose, weight, 10, 0., 10.);
        FillHist(regionsTypeI.at(it_rg)+"/M100/Number_BJets_Medium_"+IDsuffix, Nbjet_medium, weight, 10, 0., 10.);
        FillHist(regionsTypeI.at(it_rg)+"/M100/Number_FatJets_"+IDsuffix, fatjets.size(), weight, 10, 0., 10.);
        FillHist(regionsTypeI.at(it_rg)+"/M100/DiLep_Mass_"+IDsuffix, DiLep.M(), weight, 1500, 0., 1500.);
        FillHist(regionsTypeI.at(it_rg)+"/M100/Mu1_Pt_"+IDsuffix, muons.at(0).Pt(), weight, 1500, 0., 1500.);
        FillHist(regionsTypeI.at(it_rg)+"/M100/Mu2_Pt_"+IDsuffix, muons.at(1).Pt(), weight, 1500, 0., 1500.);
        FillHist(regionsTypeI.at(it_rg)+"/M100/Mu1_Eta_"+IDsuffix, muons.at(0).Eta(), weight, 50, -2.5, 2.5);
        FillHist(regionsTypeI.at(it_rg)+"/M100/Mu2_Eta_"+IDsuffix, muons.at(1).Eta(), weight, 50, -2.5, 2.5);
        if(jets.size()>0){
          FillHist(regionsTypeI.at(it_rg)+"/M100/Jet1_Pt_"+IDsuffix, jets.at(0).Pt(), weight, 1500, 0., 1500.);
          FillHist(regionsTypeI.at(it_rg)+"/M100/Jet1_Eta_"+IDsuffix, jets.at(0).Eta(), weight, 100, -5, 5);
        }
        if(jets.size()>1){
          FillHist(regionsTypeI.at(it_rg)+"/M100/Jet2_Pt_"+IDsuffix, jets.at(1).Pt(), weight, 1500, 0., 1500.);
          FillHist(regionsTypeI.at(it_rg)+"/M100/Jet2_Eta_"+IDsuffix, jets.at(1).Eta(), weight, 100, -5, 5);
          FillHist(regionsTypeI.at(it_rg)+"/M100/DiJet_Mass_"+IDsuffix, DiJet.M(), weight, 3000, 0., 3000.);
        }
        FillHist(regionsTypeI.at(it_rg)+"/M100/FatJet_Pt_"+IDsuffix, fatjets.at(j3).Pt(), weight, 1500, 0., 1500.);
        FillHist(regionsTypeI.at(it_rg)+"/M100/FatJet_Eta_"+IDsuffix, fatjets.at(j3).Eta(), weight, 100, -5, 5);
        FillHist(regionsTypeI.at(it_rg)+"/M100/FatJet_Mass_"+IDsuffix, fatjets.at(j3).SDMass(), weight, 1500, 0., 1500.);
        FillHist(regionsTypeI.at(it_rg)+"/M100/l1J_Mass_"+IDsuffix, l1J.M(), weight, 2000, 0., 2000.);
        FillHist(regionsTypeI.at(it_rg)+"/M100/l2J_Mass_"+IDsuffix, l2J.M(), weight, 2000, 0., 2000.);
        FillHist(regionsTypeI.at(it_rg)+"/M100/MET_"+IDsuffix, MET, weight, 1000, 0., 1000.);
        FillHist(regionsTypeI.at(it_rg)+"/M100/MET2ST_"+IDsuffix, MET2ST, weight, 1000, 0., 1000.);
        FillHist(regionsTypeI.at(it_rg)+"/M100/dPhill_"+IDsuffix, dPhi, weight, 32, 0., 3.2);
        FillHist(regionsTypeI.at(it_rg)+"/M100/HToverPt1_"+IDsuffix, HT/muons.at(0).Pt(), weight, 10, 0., 10.);
      }
      if(leptons.at(0)->Pt()>140. && leptons.at(1)->Pt()>65. && 40.<fatjets.at(j3).M()&&fatjets.at(j3).M()<130. && 445.<l1J.M()&&l1J.M()<560.){
        // Cutflow 12 : M500 optimization
        FillHist(regionsTypeI.at(it_rg)+"/M500/Number_Events_"+IDsuffix, 11.5, weight, cutflow_bin, 0., cutflow_max);
        FillHist(regionsTypeI.at(it_rg)+"/M500/Number_Events_unweighted_"+IDsuffix, 11.5, 1., cutflow_bin, 0., cutflow_max);

        FillHist(regionsTypeI.at(it_rg)+"/M500/Number_Jets_"+IDsuffix, jets.size(), weight, 10, 0., 10.);
        FillHist(regionsTypeI.at(it_rg)+"/M500/Number_BJets_Loose_"+IDsuffix, Nbjet_loose, weight, 10, 0., 10.);
        FillHist(regionsTypeI.at(it_rg)+"/M500/Number_BJets_Medium_"+IDsuffix, Nbjet_medium, weight, 10, 0., 10.);
        FillHist(regionsTypeI.at(it_rg)+"/M500/Number_FatJets_"+IDsuffix, fatjets.size(), weight, 10, 0., 10.);
        FillHist(regionsTypeI.at(it_rg)+"/M500/DiLep_Mass_"+IDsuffix, DiLep.M(), weight, 1500, 0., 1500.);
        FillHist(regionsTypeI.at(it_rg)+"/M500/Mu1_Pt_"+IDsuffix, muons.at(0).Pt(), weight, 1500, 0., 1500.);
        FillHist(regionsTypeI.at(it_rg)+"/M500/Mu2_Pt_"+IDsuffix, muons.at(1).Pt(), weight, 1500, 0., 1500.);
        FillHist(regionsTypeI.at(it_rg)+"/M500/Mu1_Eta_"+IDsuffix, muons.at(0).Eta(), weight, 50, -2.5, 2.5);
        FillHist(regionsTypeI.at(it_rg)+"/M500/Mu2_Eta_"+IDsuffix, muons.at(1).Eta(), weight, 50, -2.5, 2.5);
        if(jets.size()>0){
          FillHist(regionsTypeI.at(it_rg)+"/M500/Jet1_Pt_"+IDsuffix, jets.at(0).Pt(), weight, 1500, 0., 1500.);
          FillHist(regionsTypeI.at(it_rg)+"/M500/Jet1_Eta_"+IDsuffix, jets.at(0).Eta(), weight, 100, -5, 5);
        }
        if(jets.size()>1){
          FillHist(regionsTypeI.at(it_rg)+"/M500/Jet2_Pt_"+IDsuffix, jets.at(1).Pt(), weight, 1500, 0., 1500.);
          FillHist(regionsTypeI.at(it_rg)+"/M500/Jet2_Eta_"+IDsuffix, jets.at(1).Eta(), weight, 100, -5, 5);
          FillHist(regionsTypeI.at(it_rg)+"/M500/DiJet_Mass_"+IDsuffix, DiJet.M(), weight, 3000, 0., 3000.);
        }
        FillHist(regionsTypeI.at(it_rg)+"/M500/FatJet_Pt_"+IDsuffix, fatjets.at(j3).Pt(), weight, 1500, 0., 1500.);
        FillHist(regionsTypeI.at(it_rg)+"/M500/FatJet_Eta_"+IDsuffix, fatjets.at(j3).Eta(), weight, 100, -5, 5);
        FillHist(regionsTypeI.at(it_rg)+"/M500/FatJet_Mass_"+IDsuffix, fatjets.at(j3).SDMass(), weight, 1500, 0., 1500.);
        FillHist(regionsTypeI.at(it_rg)+"/M500/l1J_Mass_"+IDsuffix, l1J.M(), weight, 2000, 0., 2000.);
        FillHist(regionsTypeI.at(it_rg)+"/M500/l2J_Mass_"+IDsuffix, l2J.M(), weight, 2000, 0., 2000.);
        FillHist(regionsTypeI.at(it_rg)+"/M500/MET_"+IDsuffix, MET, weight, 1000, 0., 1000.);
        FillHist(regionsTypeI.at(it_rg)+"/M500/MET2ST_"+IDsuffix, MET2ST, weight, 1000, 0., 1000.);
        FillHist(regionsTypeI.at(it_rg)+"/M500/dPhill_"+IDsuffix, dPhi, weight, 32, 0., 3.2);
        FillHist(regionsTypeI.at(it_rg)+"/M500/HToverPt1_"+IDsuffix, HT/muons.at(0).Pt(), weight, 10, 0., 10.);
      }
      if(leptons.at(0)->Pt()>140. && 40.<fatjets.at(j3).M()&&fatjets.at(j3).M()<130. && 900.<l1J.M()&&l1J.M()<1205.){
        // Cutflow 12 : M1000 optimization
        FillHist(regionsTypeI.at(it_rg)+"/M1000/Number_Events_"+IDsuffix, 11.5, weight, cutflow_bin, 0., cutflow_max);
        FillHist(regionsTypeI.at(it_rg)+"/M1000/Number_Events_unweighted_"+IDsuffix, 11.5, 1., cutflow_bin, 0., cutflow_max);

        FillHist(regionsTypeI.at(it_rg)+"/M1000/Number_Jets_"+IDsuffix, jets.size(), weight, 10, 0., 10.);
        FillHist(regionsTypeI.at(it_rg)+"/M1000/Number_BJets_Loose_"+IDsuffix, Nbjet_loose, weight, 10, 0., 10.);
        FillHist(regionsTypeI.at(it_rg)+"/M1000/Number_BJets_Medium_"+IDsuffix, Nbjet_medium, weight, 10, 0., 10.);
        FillHist(regionsTypeI.at(it_rg)+"/M1000/Number_FatJets_"+IDsuffix, fatjets.size(), weight, 10, 0., 10.);
        FillHist(regionsTypeI.at(it_rg)+"/M1000/DiLep_Mass_"+IDsuffix, DiLep.M(), weight, 1500, 0., 1500.);
        FillHist(regionsTypeI.at(it_rg)+"/M1000/Mu1_Pt_"+IDsuffix, muons.at(0).Pt(), weight, 1500, 0., 1500.);
        FillHist(regionsTypeI.at(it_rg)+"/M1000/Mu2_Pt_"+IDsuffix, muons.at(1).Pt(), weight, 1500, 0., 1500.);
        FillHist(regionsTypeI.at(it_rg)+"/M1000/Mu1_Eta_"+IDsuffix, muons.at(0).Eta(), weight, 50, -2.5, 2.5);
        FillHist(regionsTypeI.at(it_rg)+"/M1000/Mu2_Eta_"+IDsuffix, muons.at(1).Eta(), weight, 50, -2.5, 2.5);
        if(jets.size()>0){
          FillHist(regionsTypeI.at(it_rg)+"/M1000/Jet1_Pt_"+IDsuffix, jets.at(0).Pt(), weight, 1500, 0., 1500.);
          FillHist(regionsTypeI.at(it_rg)+"/M1000/Jet1_Eta_"+IDsuffix, jets.at(0).Eta(), weight, 100, -5, 5);
        }
        if(jets.size()>1){
          FillHist(regionsTypeI.at(it_rg)+"/M1000/Jet2_Pt_"+IDsuffix, jets.at(1).Pt(), weight, 1500, 0., 1500.);
          FillHist(regionsTypeI.at(it_rg)+"/M1000/Jet2_Eta_"+IDsuffix, jets.at(1).Eta(), weight, 100, -5, 5);
          FillHist(regionsTypeI.at(it_rg)+"/M1000/DiJet_Mass_"+IDsuffix, DiJet.M(), weight, 3000, 0., 3000.);
        }
        FillHist(regionsTypeI.at(it_rg)+"/M1000/FatJet_Pt_"+IDsuffix, fatjets.at(j3).Pt(), weight, 1500, 0., 1500.);
        FillHist(regionsTypeI.at(it_rg)+"/M1000/FatJet_Eta_"+IDsuffix, fatjets.at(j3).Eta(), weight, 100, -5, 5);
        FillHist(regionsTypeI.at(it_rg)+"/M1000/FatJet_Mass_"+IDsuffix, fatjets.at(j3).SDMass(), weight, 1500, 0., 1500.);
        FillHist(regionsTypeI.at(it_rg)+"/M1000/l1J_Mass_"+IDsuffix, l1J.M(), weight, 2000, 0., 2000.);
        FillHist(regionsTypeI.at(it_rg)+"/M1000/l2J_Mass_"+IDsuffix, l2J.M(), weight, 2000, 0., 2000.);
        FillHist(regionsTypeI.at(it_rg)+"/M1000/MET_"+IDsuffix, MET, weight, 1000, 0., 1000.);
        FillHist(regionsTypeI.at(it_rg)+"/M1000/MET2ST_"+IDsuffix, MET2ST, weight, 1000, 0., 1000.);
        FillHist(regionsTypeI.at(it_rg)+"/M1000/dPhill_"+IDsuffix, dPhi, weight, 32, 0., 3.2);
        FillHist(regionsTypeI.at(it_rg)+"/M1000/HToverPt1_"+IDsuffix, HT/muons.at(0).Pt(), weight, 10, 0., 10.);
      }
      if(leptons.at(0)->Pt()>140. && 40.<fatjets.at(j3).M()&&fatjets.at(j3).M()<130. && 1330.<l1J.M()&&l1J.M()<1800.){
        // Cutflow 12 : M1500 optimization
        FillHist(regionsTypeI.at(it_rg)+"/M1500/Number_Events_"+IDsuffix, 11.5, weight, cutflow_bin, 0., cutflow_max);
        FillHist(regionsTypeI.at(it_rg)+"/M1500/Number_Events_unweighted_"+IDsuffix, 11.5, 1., cutflow_bin, 0., cutflow_max);

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
      }

    }

  }

  */

}
