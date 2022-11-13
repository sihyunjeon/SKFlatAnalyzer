#include "GenSigStudy.h"

void GenSigStudy::initializeAnalyzer(){

  All2l=false, SS2l=false, OS2l=false;
  TrAccCheck=false, TrRateCheck=false;
  FakeRun=false, ConvRun=false, FlipRun=false, SystRun=false; 
  for(unsigned int i=0; i<Userflags.size(); i++){
    if(Userflags.at(i).Contains("All2l"))      All2l      = true;
    if(Userflags.at(i).Contains("OS2l"))       OS2l       = true;
    if(Userflags.at(i).Contains("SS2l"))       SS2l       = true;
    if(Userflags.at(i).Contains("TrAccCheck") ) TrAccCheck  = true;
    if(Userflags.at(i).Contains("TrRateCheck")) TrRateCheck = true;
    if(Userflags.at(i).Contains("FakeRun"))    FakeRun    = true; 
    if(Userflags.at(i).Contains("ConvRun"))    ConvRun    = true; 
    if(Userflags.at(i).Contains("FlipRun"))    FlipRun    = true; 
    if(Userflags.at(i).Contains("SystRun"))    SystRun    = true; 
  }

  DblMu=false, DblEG=false, MuEG=false;
  if     (DataStream.Contains("DoubleMuon")) DblMu=true;
  else if(DataStream.Contains("MuonEG"))     MuEG =true;
  else if(DataStream.Contains("DoubleEG"))   DblEG=true;
  else if(DataYear==2018 and DataStream.Contains("EGamma")) DblEG=true;

  if(GetEraShort()=="2016a"){
    TrigList_SglMu = {"HLT_IsoMu24_v", "HLT_IsoTkMu24_v"}; TrigList_SglEl = {"HLT_Ele27_WPTight_Gsf_v"};
    TrigList_DblMu = {"HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_v", "HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_v"};
    TrigList_DblEG = {"HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v"};
    TrigList_MuEG  = {"HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_v", "HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL_v"};
  }
  else if(GetEraShort()=="2016b"){
    TrigList_SglMu = {"HLT_IsoMu24_v", "HLT_IsoTkMu24_v"}; TrigList_SglEl = {"HLT_Ele27_WPTight_Gsf_v"};
    TrigList_DblMu = {"HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v", "HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v", "HLT_TkMu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v"};
    TrigList_DblEG = {"HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v"};
    TrigList_MuEG  = {"HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_v", "HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v"};
  }
  else if(DataYear==2017){
    TrigList_SglMu = {"HLT_IsoMu27_v"}; TrigList_SglEl = {"HLT_Ele32_WPTight_Gsf_L1DoubleEG_v"};
    TrigList_DblMu = {"HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v", "HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8_v"};
    TrigList_DblEG = {"HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_v"};
    TrigList_MuEG  = {"HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v", "HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_v"};
  }
  else if(DataYear==2018){
    TrigList_SglMu = {"HLT_IsoMu24_v"}; TrigList_SglEl = {"HLT_Ele32_WPTight_Gsf_v"};
    TrigList_DblMu = {"HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v", "HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8_v"};
    TrigList_DblEG = {"HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_v"};
    TrigList_MuEG  = {"HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v", "HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_v"};
  }


  //Set up the tagger map only for the param settings to be used.
  vector<JetTagging::Parameters> jtps;
  jtps.push_back( JetTagging::Parameters(JetTagging::DeepJet, JetTagging::Medium, JetTagging::incl, JetTagging::mujets) );
  mcCorr->SetJetTaggingParameters(jtps);


  outfile->cd();
}


void GenSigStudy::executeEvent(){


  Event ev = GetEvent();
  float weight = 1., w_GenNorm=1., w_BR=1., w_PU=1.;
  if(!IsDATA){
    w_GenNorm = MCweight()*GetKFactor()*ev.GetTriggerLumi("Full");
    w_BR      = GetBRWeight();
    w_PU      = GetPileUpWeight(nPileUp, 0);
    weight *= w_GenNorm * w_BR * w_PU;
  }
  FillHist("CutFlow", 0., weight, 20, 0., 20.);

  bool PassTrig=false;
  if(All2l or SS2l or OS2l){ PassTrig = ev.PassTrigger(TrigList_DblEG) or ev.PassTrigger(TrigList_DblMu); }
  if(TrAccCheck or TrRateCheck) PassTrig=true;
  if(!PassTrig) return;
  FillHist("CutFlow", 1., weight, 20, 0., 20.);
  if(!PassMETFilter()) return;
  FillHist("CutFlow", 2., weight, 20, 0., 20.);

  bool PreCutPass=false;
  vector<Muon>     muonPreColl     = GetMuons("NOCUT", 5., 2.4);
  vector<Electron> electronPreColl = GetElectrons("NOCUT", 5., 2.5);
  sort(muonPreColl.begin(), muonPreColl.end(), PtComparing);
  sort(electronPreColl.begin(), electronPreColl.end(), PtComparing);
  int NPreMu=muonPreColl.size(), NPreEl=electronPreColl.size();
  if(SS2l){
    if( (NPreMu+NPreEl)>2 ) PreCutPass=true;
    else if(NPreMu==2 and SumCharge(muonPreColl)!=0) PreCutPass=true;
    else if(NPreEl==2 and SumCharge(electronPreColl)!=0) PreCutPass=true;
  }
  if((All2l or OS2l) && (NPreMu+NPreEl)>1 && NPreEl>0) PreCutPass=true;
  if(TrAccCheck or TrRateCheck) PreCutPass=true;
  
  if(!PreCutPass) return;


  TString IDSSLabel = "SS", TLabel = FakeRun? "L":"T";
  TString MuTID = "TopHNT", MuLID = "TopHNL";
  TString ElTID = "TopHNSST", ElLID = "TopHNSSL_"+GetEraShort(), ElVID = "TopHNL_"+GetEraShort();
  float PTminEl = ElTID.Contains("SS")? 15.:10.;
  vector<Muon>     muonTightColl     = SelectMuons(muonPreColl, MuTID, 10., 2.4);
  vector<Electron> electronTightColl = SelectElectrons(electronPreColl, ElTID, PTminEl, 2.5);
  vector<Muon>     muonLooseColl     = SelectMuons(muonPreColl, MuLID, 10., 2.4);
  vector<Electron> electronLooseColl = SelectElectrons(electronPreColl, ElLID, PTminEl, 2.5);
  vector<Muon>     muonVetoColl      = SelectMuons(muonPreColl, MuLID, 10., 2.4);
  vector<Electron> electronVetoColl  = SelectElectrons(electronPreColl, ElVID, 10., 2.5);


  JetTagging::Parameters param_jets = JetTagging::Parameters(JetTagging::DeepJet, JetTagging::Medium, JetTagging::incl, JetTagging::mujets);
  vector<Jet> jetPreColl = GetAllJets();
  sort(jetPreColl.begin(), jetPreColl.end(), PtComparing);
  vector<Jet> jetColl  = SelectJets(jetPreColl, muonLooseColl, electronVetoColl, "tight", 25., 2.4, "LVeto");
  vector<Jet> bjetColl = SelBJets(jetColl, param_jets);


  Particle vMET_T1xy = GetvMET("PUPPIMETT1xyCorr");


  bool FillGenColl = TrAccCheck or TrRateCheck;
  if(FillGenColl) truthColl = GetGens();

  bool EventCand = false;
  if(All2l or SS2l or OS2l){
    EventCand = (muonTightColl.size()+electronTightColl.size())==2;
  }
  if(TrAccCheck or TrRateCheck) EventCand=false;

  float w_TopPtRW = 1., w_Prefire = 1., sf_Trig = 1., w_FR=1.;
  float sf_MuTk = 1., sf_MuID = 1., sf_MuIso = 1., sf_ElReco = 1., sf_ElID = 1., sf_BTag = 1.;
  if((!IsDATA) and EventCand){
    //w_TopPtRW = mcCorr->GetTopPtReweight(truthColl);
    //sf_MuID   = GetMuonSF(muonTightColl, "TopHNID_TkMu", "ID");
    sf_ElReco = GetElectronSF(electronTightColl, "", "Reco");
    sf_ElID   = GetElectronSF(electronTightColl, ElTID, "ID");
    sf_BTag   = mcCorr->GetBTaggingReweight_1a(jetColl, param_jets);
    TString SFKey_Trig_All = muonTightColl.size()==2? "DiMuIso_HNTopID":electronTightColl.size()==2? "DiElIso_HNTopIDSS":""; 
    sf_Trig   = SFKey_Trig_All!=""? mcCorr->GetTriggerSF(electronTightColl, muonTightColl, SFKey_Trig_All, ""):1.;
    w_Prefire = GetPrefireWeight(0);
  }
  weight *= w_TopPtRW * w_Prefire * sf_Trig * w_FR;
  weight *= sf_MuTk * sf_MuID * sf_MuIso * sf_ElReco * sf_ElID * sf_BTag;

  if(TrAccCheck ) TrigAccCheck(weight, ""); 
  if(TrRateCheck) RecoTrigRateCheck(muonPreColl, electronPreColl, ev, "TopHNT", "TopHNSST", weight, ""); 
  if(SystRun && ((!IsDATA) or FakeRun)){
  }
}

void GenSigStudy::TrigAccCheck(float weight, TString Label)
{
  if( !(MCSample.Contains("TT_HeavyN") && MCSample.Contains("_2L_")) ) return;

  int NMatchElSig=0, NMatchMuSig=0;
  vector<Gen> l_tlNCands, l_NffCands, l_SigCands;
  for(unsigned int it=2; it<truthColl.size(); it++){
    int PID = truthColl.at(it).PID(), aPID = abs(PID);
    if( !(aPID==11 or aPID==13)  ) continue;

    int MIdx = truthColl.at(it).MotherIndex(), MPID = MIdx>=0? truthColl.at(MIdx).PID():0, aMPID = abs(MPID);
    int GenSt = truthColl.at(it).Status();
    //muon pt is from track; should be close to state after FSR
    //electron pt is from SC, FSR photons and FSR photon->conversion electrons are included in the reco E.
    if(   aPID==11 && PID==MPID  ) continue;
    if(   aPID==13 && GenSt!=1   ) continue;

    int LastSelfIdx = LastSelfMotherIdx(it,truthColl);
    int MIdxOrig = truthColl.at(LastSelfIdx).MotherIndex();
    int MPIDOrig = truthColl.at(MIdxOrig).PID(), aMPIDOrig = abs(MPIDOrig);
    if( aPID==11 ){
      if( aMPID==11 or aMPID==13 or aMPID==15 ) continue;
      if( !(aMPID==6 or aMPID==24 or aMPID>9900000) ) continue;
      l_SigCands.push_back(truthColl.at(it));
      NMatchElSig++;
    }
    if( aPID==13 ){
      if( aMPIDOrig==11 or aMPIDOrig==13 or aMPIDOrig==15 ) continue;
      if( !(aMPIDOrig==6 or aMPIDOrig==24 or aMPIDOrig>9900000) ) continue;
      l_SigCands.push_back(truthColl.at(it));
      NMatchMuSig++;
    }
  }

  sort(l_SigCands.begin(), l_SigCands.end(), PtComparing);

  for(unsigned int il=0; il<l_SigCands.size(); il++){
    int MPID = truthColl.at( l_SigCands.at(il).MotherIndex() ).PID(), aMPID = abs(MPID);
    if(aMPID>9900000) l_NffCands.push_back(l_SigCands.at(il));
    else if(aMPID==6 or aMPID==24) l_tlNCands.push_back(l_SigCands.at(il));
  }
  FillHist("NMatchElSig", NMatchElSig, weight, 10, 0., 10.);
  FillHist("NMatchMuSig", NMatchMuSig, weight, 10, 0., 10.);
  //if(NMatchMuSig!=2){ PrintGen(truthColl); }

  if(l_tlNCands.size()>0 && l_NffCands.size()>0){
    FillHist("PTl_tlNCand"+Label, l_tlNCands.at(0).Pt(), weight, 40, 0., 200.);
    FillHist("PTl_NffCand"+Label, l_NffCands.at(0).Pt(), weight, 40, 0., 200.);
    if( (MCSample.Contains("Mu") && fabs(l_tlNCands.at(0).Eta())<2.4 && fabs(l_NffCands.at(0).Eta())<2.4)
     or (MCSample.Contains("El") && fabs(l_tlNCands.at(0).Eta())<2.5 && fabs(l_NffCands.at(0).Eta())<2.5) ){
      FillHist("PTl_EtaAcc_tlNCand"+Label, l_tlNCands.at(0).Pt(), weight, 40, 0., 200.);
      FillHist("PTl_EtaAcc_NffCand"+Label, l_NffCands.at(0).Pt(), weight, 40, 0., 200.);
    }
  }
  else FillHist("NCount_Not_tlNORNff"+Label, 0., weight, 1, 0., 1.);
  if(l_SigCands.size()>1){
    float PTl1 = l_SigCands.at(0).Pt(), PTl2 = l_SigCands.at(1).Pt();
    float Etal1 = l_SigCands.at(0).Eta(), Etal2 = l_SigCands.at(1).Eta();
    float fEtal1 = fabs(Etal1), fEtal2 = fabs(Etal2);
    //float Mll = (l_SigCands.at(0)+l_SigCands.at(1)).M();
    FillHist("PTl1_Sig"+Label, PTl1, weight, 40, 0., 200.);
    FillHist("PTl2_Sig"+Label, PTl2, weight, 40, 0., 200.);
    if( (MCSample.Contains("Mu") && fEtal1<2.4 && fEtal2<2.4)
     or (MCSample.Contains("El") && fEtal1<2.5 && fEtal2<2.5) ){
      FillHist("PTl1_EtaAcc_Sig"+Label, PTl1, weight, 40, 0., 200.);
      FillHist("PTl2_EtaAcc_Sig"+Label, PTl2, weight, 40, 0., 200.);
    }
    bool PassAcc_2EEta = fEtal1<2.5 && fEtal2<2.5;
    bool PassAcc_2MEta = fEtal1<2.4 && fEtal2<2.4;
    bool PassAcc_2ETr = PTl1>25 && PTl2>15 && fEtal1<2.5 && fEtal2<2.5;
    bool PassAcc_2MTr = PTl1>20 && PTl2>10 && fEtal1<2.4 && fEtal2<2.4;
    bool PassAcc_1MTrv1 = PTl1>27 && PTl2>5 && fEtal1<2.4 && fEtal2<2.4;
    bool PassAcc_1MTrv2 = PTl1>30 && PTl2>5 && fEtal1<2.4 && fEtal2<2.4;
    bool PassAcc_1ETrv1 = PTl1>30 && PTl2>5 && fEtal1<2.5 && fEtal2<2.5;
    bool PassAcc_1ETrv2 = PTl1>35 && PTl2>5 && fEtal1<2.5 && fEtal2<2.5;
    bool PassAcc_Dbl_1MTrv1 = PTl2>27 && fEtal1<2.4 && fEtal2<2.4;
    bool PassAcc_Dbl_1MTrv2 = PTl2>30 && fEtal1<2.4 && fEtal2<2.4;
    bool PassAcc_Dbl_1ETrv1 = PTl2>30 && fEtal1<2.5 && fEtal2<2.5;
    bool PassAcc_Dbl_1ETrv2 = PTl2>35 && fEtal1<2.5 && fEtal2<2.5;
    float LumiRun2 = 19.517+16.812+41.477+59.827;
    float FrLumi16 = (19.517+16.812)/LumiRun2;
    float FrLumi17 = 41.477/LumiRun2;
    float FrLumi18 = 59.827/LumiRun2;

    FillHist("NAcc_2EEta"+Label, 0., weight, 2, 0., 2.);
    if(PassAcc_2EEta ) FillHist("NAcc_2EEta"+Label, 1., weight, 2, 0., 2.);
    FillHist("NAcc_2MEta"+Label, 0., weight, 2, 0., 2.);
    if(PassAcc_2MEta ) FillHist("NAcc_2MEta"+Label, 1., weight, 2, 0., 2.);
    FillHist("NAcc_2ETr"+Label, 0., weight, 2, 0., 2.);
    if(PassAcc_2ETr  ) FillHist("NAcc_2ETr"+Label, 1., weight, 2, 0., 2.);
    FillHist("NAcc_2MTr"+Label, 0., weight, 2, 0., 2.);
    if(PassAcc_2MTr  ) FillHist("NAcc_2MTr"+Label, 1., weight, 2, 0., 2.);
    FillHist("NAcc_1ETrv1"+Label, 0., weight, 2, 0., 2.);
    if(PassAcc_1ETrv1) FillHist("NAcc_1ETrv1"+Label, 1., weight, 2, 0., 2.);
    FillHist("NAcc_1ETrv2"+Label, 0., weight, 2, 0., 2.);
    if(PassAcc_1ETrv2) FillHist("NAcc_1ETrv2"+Label, 1., weight, 2, 0., 2.);
    FillHist("NAcc_1MTrv1"+Label, 0., weight, 2, 0., 2.);
    if(PassAcc_1MTrv1) FillHist("NAcc_1MTrv1"+Label, 1., weight, 2, 0., 2.);
    FillHist("NAcc_1MTrv2"+Label, 0., weight, 2, 0., 2.);
    if(PassAcc_1MTrv2) FillHist("NAcc_1MTrv2"+Label, 1., weight, 2, 0., 2.);
    FillHist("NAcc_1ETrComb"+Label, 0., weight, 2, 0., 2.);
    if(PassAcc_1ETrv1) FillHist("NAcc_1ETrComb"+Label, 1., weight*FrLumi16, 2, 0., 2.);
    if(PassAcc_1ETrv2) FillHist("NAcc_1ETrComb"+Label, 1., weight*(FrLumi17+FrLumi18), 2, 0., 2.);
    FillHist("NAcc_1MTrComb"+Label, 0., weight, 2, 0., 2.);
    if(PassAcc_1MTrv1) FillHist("NAcc_1MTrComb"+Label, 1., weight*(FrLumi16+FrLumi18), 2, 0., 2.);
    if(PassAcc_1MTrv2) FillHist("NAcc_1MTrComb"+Label, 1., weight*FrLumi17, 2, 0., 2.);
    if(PassAcc_2ETr ) FillHist("NAcc2EBoost_1ETrv1"+Label, 0., weight, 2, 0., 2.);
    if(PassAcc_2ETr && PassAcc_Dbl_1ETrv1 ) FillHist("NAcc2EBoost_1ETrv1"+Label, 1., weight, 2, 0., 2.);
    if(PassAcc_2ETr ) FillHist("NAcc2EBoost_1ETrv2"+Label, 0., weight, 2, 0., 2.);
    if(PassAcc_2ETr && PassAcc_Dbl_1ETrv2 ) FillHist("NAcc2EBoost_1ETrv2"+Label, 1., weight, 2, 0., 2.);
    if(PassAcc_2MTr ) FillHist("NAcc2MBoost_1MTrv1"+Label, 0., weight, 2, 0., 2.);
    if(PassAcc_2MTr && PassAcc_Dbl_1MTrv1 ) FillHist("NAcc2MBoost_1MTrv1"+Label, 1., weight, 2, 0., 2.);
    if(PassAcc_2MTr ) FillHist("NAcc2MBoost_1MTrv2"+Label, 0., weight, 2, 0., 2.);
    if(PassAcc_2MTr && PassAcc_Dbl_1MTrv2 ) FillHist("NAcc2MBoost_1MTrv2"+Label, 1., weight, 2, 0., 2.);
  }
  else FillHist("NCount_Not_2lSig"+Label, 0., weight, 1, 0., 1.);

}


void GenSigStudy::RecoTrigRateCheck(vector<Muon>& MuPreColl, vector<Electron>& ElPreColl, Event& Ev, TString MuTID, TString ElTID, float weight, TString Label)
{

  vector<Muon> MuRecoColl; vector<Electron> ElRecoColl;
  vector<Muon> MuIDColl; vector<Electron> ElIDColl;
  int NPrMuReco=0, NPrMuID=0, NPrElReco=0, NPrElID=0;
  int Q1stPrMuReco=0, Q1stPrElReco=0, Q1stPrMuID=0, Q1stPrElID=0;
  for(unsigned int im=0; im<MuPreColl.size(); im++){
    Muon* Mu = &MuPreColl.at(im);
    if(Mu->Pt()<5) continue; 
    //bool PassID = Mu->PassID(MuTID), CheckType = MCSample.Contains("powheg")? PassID:true;
    bool CheckType=true;
    int LepType = CheckType? GetLeptonType(*Mu, truthColl):0;
    if(MCSample.Contains("TT_HeavyN") && LepType>0){
      MuRecoColl.push_back(*Mu);
      if(Mu->PassID(MuTID)) MuIDColl.push_back(*Mu);
    }
    else{
      if(LepType>0){
        if     (NPrMuReco==0              ){ MuRecoColl.push_back(*Mu); Q1stPrMuReco=Mu->Charge(); }
        else if(Mu->Charge()==Q1stPrMuReco)  MuRecoColl.push_back(*Mu);
        if(Mu->PassID(MuTID)){
          if     (NPrMuID==0              ){ MuIDColl.push_back(*Mu); Q1stPrMuID=Mu->Charge(); }
          else if(Mu->Charge()==Q1stPrMuID)  MuIDColl.push_back(*Mu);
        }
      }
      else{
        MuRecoColl.push_back(*Mu);
        if(Mu->PassID(MuTID)) MuIDColl.push_back(*Mu);
      }
    }
  }
  for(unsigned int im=0; im<ElPreColl.size(); im++){
    Electron* El = &ElPreColl.at(im);
    if(El->Pt()<5) continue; 
    //bool PassID = El->PassID(ElTID), CheckType = MCSample.Contains("powheg")? PassID:true;
    bool CheckType=true;
    int LepType = CheckType? GetLeptonType(*El, truthColl):0;
    if(MCSample.Contains("TT_HeavyN") && LepType>0){
      ElRecoColl.push_back(*El);
      if(El->PassID(ElTID)) ElIDColl.push_back(*El);
    }
    else{
      if(LepType>0){
        if     (NPrElReco==0              ){ ElRecoColl.push_back(*El); Q1stPrElReco=El->Charge(); }
        else if(El->Charge()==Q1stPrElReco)  ElRecoColl.push_back(*El);
        if(El->PassID(ElTID)){
          if     (NPrElID==0              ){ ElIDColl.push_back(*El); Q1stPrElID=El->Charge(); }
          else if(El->Charge()==Q1stPrElID)  ElIDColl.push_back(*El);
        }
      }
      else{
        ElRecoColl.push_back(*El);
        if(El->PassID(ElTID)) ElIDColl.push_back(*El);
      }
    }
  }

  float sf_MuID   = GetMuonSF(MuIDColl, MuTID, "ID");
  float sf_ElReco = GetElectronSF(ElIDColl, "", "Reco");
  float sf_ElID   = GetElectronSF(ElIDColl, ElTID, "ID");
  float w_Pref = GetPrefireWeight(0);

  //check rate without ID effect; Reco+Acc+Tr
  FillHist("NRecoAcc_2MTr"+Label, 0., weight, 2, 0., 2.);
  FillHist("NRecoAcc_1MTr"+Label, 0., weight, 2, 0., 2.);
  FillHist("NRecoAccTr_2MTr"+Label, 0., weight, 2, 0., 2.);
  FillHist("NRecoAccTr_1MTr"+Label, 0., weight, 2, 0., 2.);
  FillHist("NRecoAccTr_1MOR2MTr"+Label, 0., weight, 2, 0., 2.);
  if(MuRecoColl.size()>1 && MuRecoColl.at(0).Charge()==MuRecoColl.at(1).Charge()){ 
    float PTl1 = MuRecoColl.at(0).Pt(), PTl2 = MuRecoColl.at(1).Pt();
    float Mll = (MuRecoColl.at(0)+MuRecoColl.at(1)).M();
    bool PassEtaAcc = fabs(MuRecoColl.at(0).Eta())<2.4 && fabs(MuRecoColl.at(1).Eta())<2.4;
    bool PassAcc_2MTr = PTl1>20 && PTl2>10 && Mll>4 && PassEtaAcc;
    bool PassAcc_1MTr = DataYear!=2017? PTl1>27 && PassEtaAcc: PTl1>30 && PassEtaAcc;
    bool PassAccTr_2MTr = PassAcc_2MTr && Ev.PassTrigger(TrigList_DblMu);
    bool PassAccTr_1MTr = PassAcc_1MTr && Ev.PassTrigger(TrigList_SglMu);
    bool PassAccTr_1MOR2MTr = PassAcc_2MTr && (Ev.PassTrigger(TrigList_SglMu) or Ev.PassTrigger(TrigList_DblMu));
    if(PassAcc_2MTr) FillHist("NRecoAcc_2MTr"+Label, 1., weight*w_Pref, 2, 0., 2.);
    if(PassAcc_1MTr) FillHist("NRecoAcc_1MTr"+Label, 1., weight*w_Pref, 2, 0., 2.);
    if(PassAccTr_2MTr) FillHist("NRecoAccTr_2MTr"+Label, 1., weight*w_Pref, 2, 0., 2.);
    if(PassAccTr_1MTr) FillHist("NRecoAccTr_1MTr"+Label, 1., weight*w_Pref, 2, 0., 2.);
    if(PassAccTr_1MOR2MTr) FillHist("NRecoAccTr_1MOR2MTr"+Label, 1., weight*w_Pref, 2, 0., 2.);
  }
  FillHist("NRecoAcc_2ETr"+Label, 0., weight, 2, 0., 2.);
  FillHist("NRecoAcc_1ETr"+Label, 0., weight, 2, 0., 2.);
  FillHist("NRecoAccTr_2ETr"+Label, 0., weight, 2, 0., 2.);
  FillHist("NRecoAccTr_1ETr"+Label, 0., weight, 2, 0., 2.);
  FillHist("NRecoAccTr_1EOR2ETr"+Label, 0., weight, 2, 0., 2.);
  if(ElRecoColl.size()>1 && ElRecoColl.at(0).Charge()==ElRecoColl.at(1).Charge()){ 
    float PTl1 = ElRecoColl.at(0).Pt(), PTl2 = ElRecoColl.at(1).Pt();
    bool PassEtaAcc = fabs(ElRecoColl.at(0).Eta())<2.5 && fabs(ElRecoColl.at(1).Eta())<2.5;
    bool PassAcc_2ETr = PTl1>25 && PTl2>15 && PassEtaAcc;
    bool PassAcc_1ETr = DataYear!=2016? PTl1>35 && PassEtaAcc: PTl1>30 && PassEtaAcc;
    bool PassAccTr_2ETr = PassAcc_2ETr && Ev.PassTrigger(TrigList_DblEG);
    bool PassAccTr_1ETr = PassAcc_1ETr && Ev.PassTrigger(TrigList_SglEl);
    bool PassAccTr_1EOR2ETr = PassAcc_2ETr && (Ev.PassTrigger(TrigList_SglEl) or Ev.PassTrigger(TrigList_DblEG));
    if(PassAcc_2ETr) FillHist("NRecoAcc_2ETr"+Label, 1., weight*w_Pref*sf_ElReco, 2, 0., 2.);
    if(PassAcc_1ETr) FillHist("NRecoAcc_1ETr"+Label, 1., weight*w_Pref*sf_ElReco, 2, 0., 2.);
    if(PassAccTr_2ETr) FillHist("NRecoAccTr_2ETr"+Label, 1., weight*w_Pref*sf_ElReco, 2, 0., 2.);
    if(PassAccTr_1ETr) FillHist("NRecoAccTr_1ETr"+Label, 1., weight*w_Pref*sf_ElReco, 2, 0., 2.);
    if(PassAccTr_1EOR2ETr) FillHist("NRecoAccTr_1EOR2ETr"+Label, 1., weight*w_Pref*sf_ElReco, 2, 0., 2.);
  }


  //ID+Reco+Acc+Tr check
  FillHist("NIDAcc_2MTr"+Label, 0., weight, 2, 0., 2.);
  FillHist("NIDAcc_1MTr"+Label, 0., weight, 2, 0., 2.);
  FillHist("NIDAccTr_2MTr"+Label, 0., weight, 2, 0., 2.);
  FillHist("NIDAccTr_1MTr"+Label, 0., weight, 2, 0., 2.);
  FillHist("NIDAccTr_1MOR2MTr"+Label, 0., weight, 2, 0., 2.);
  if(MuIDColl.size()==2 && MuIDColl.at(0).Charge()==MuIDColl.at(1).Charge()){ 
    float PTl1 = MuIDColl.at(0).Pt(), PTl2 = MuIDColl.at(1).Pt();
    float Mll = (MuIDColl.at(0)+MuIDColl.at(1)).M();
    bool PassEtaAcc = fabs(MuIDColl.at(0).Eta())<2.4 && fabs(MuIDColl.at(1).Eta())<2.4;
    bool PassAcc_2MTr = PTl1>20 && PTl2>10 && Mll>4 && PassEtaAcc;
    bool PassAcc_1MTr = DataYear!=2017? PTl1>27 && PassEtaAcc: PTl1>30 && PassEtaAcc;
    bool PassAccTr_2MTr = PassAcc_2MTr && Ev.PassTrigger(TrigList_DblMu);
    bool PassAccTr_1MTr = PassAcc_1MTr && Ev.PassTrigger(TrigList_SglMu);
    bool PassAccTr_1MOR2MTr = PassAcc_2MTr && (Ev.PassTrigger(TrigList_SglMu) or Ev.PassTrigger(TrigList_DblMu));
    if(PassAcc_2MTr) FillHist("NIDAcc_2MTr"+Label, 1., weight*w_Pref*sf_MuID, 2, 0., 2.);
    if(PassAcc_1MTr) FillHist("NIDAcc_1MTr"+Label, 1., weight*w_Pref*sf_MuID, 2, 0., 2.);
    if(PassAccTr_2MTr) FillHist("NIDAccTr_2MTr"+Label, 1., weight*w_Pref*sf_MuID, 2, 0., 2.);
    if(PassAccTr_1MTr) FillHist("NIDAccTr_1MTr"+Label, 1., weight*w_Pref*sf_MuID, 2, 0., 2.);
    if(PassAccTr_1MOR2MTr) FillHist("NIDAccTr_1MOR2MTr"+Label, 1., weight*w_Pref*sf_MuID, 2, 0., 2.);
  }
  FillHist("NIDAcc_2ETr"+Label, 0., weight, 2, 0., 2.);
  FillHist("NIDAcc_1ETr"+Label, 0., weight, 2, 0., 2.);
  FillHist("NIDAccTr_2ETr"+Label, 0., weight, 2, 0., 2.);
  FillHist("NIDAccTr_1ETr"+Label, 0., weight, 2, 0., 2.);
  FillHist("NIDAccTr_1EOR2ETr"+Label, 0., weight, 2, 0., 2.);
  if(ElIDColl.size()==2 && ElIDColl.at(0).Charge()==ElIDColl.at(1).Charge()){ 
    float PTl1 = ElIDColl.at(0).Pt(), PTl2 = ElIDColl.at(1).Pt();
    bool PassEtaAcc = fabs(ElIDColl.at(0).Eta())<2.5 && fabs(ElIDColl.at(1).Eta())<2.5;
    bool PassAcc_2ETr = PTl1>25 && PTl2>15 && PassEtaAcc;
    bool PassAcc_1ETr = DataYear!=2016? PTl1>35 && PassEtaAcc: PTl1>30 && PassEtaAcc;
    bool PassAccTr_2ETr = PassAcc_2ETr && Ev.PassTrigger(TrigList_DblEG);
    bool PassAccTr_1ETr = PassAcc_1ETr && Ev.PassTrigger(TrigList_SglEl);
    bool PassAccTr_1EOR2ETr = PassAcc_2ETr && (Ev.PassTrigger(TrigList_SglEl) or Ev.PassTrigger(TrigList_DblEG));
    if(PassAcc_2ETr) FillHist("NIDAcc_2ETr"+Label, 1., weight*w_Pref*sf_ElReco*sf_ElID, 2, 0., 2.);
    if(PassAcc_1ETr) FillHist("NIDAcc_1ETr"+Label, 1., weight*w_Pref*sf_ElReco*sf_ElID, 2, 0., 2.);
    if(PassAccTr_2ETr) FillHist("NIDAccTr_2ETr"+Label, 1., weight*w_Pref*sf_ElReco*sf_ElID, 2, 0., 2.);
    if(PassAccTr_1ETr) FillHist("NIDAccTr_1ETr"+Label, 1., weight*w_Pref*sf_ElReco*sf_ElID, 2, 0., 2.);
    if(PassAccTr_1EOR2ETr) FillHist("NIDAccTr_1EOR2ETr"+Label, 1., weight*w_Pref*sf_ElReco*sf_ElID, 2, 0., 2.);
  }

}


void GenSigStudy::GetMassDists(vector<Muon>& MuTColl, vector<Muon>& MuLColl, vector<Muon>& MuVColl,
                                 vector<Electron>& ElTColl, vector<Electron>& ElLColl, vector<Electron>& ElVColl,
                                 vector<Jet>& JetColl, vector<Jet>& BJetColl, Particle& vMET, float weight, TString Label)
{
  int NMuT=MuTColl.size(), NElT=ElTColl.size(), NMuL=MuLColl.size(), NElL=ElLColl.size(), NMuV=MuVColl.size(), NElV=ElVColl.size();
  bool IsSS2l=false;  double Mll=-1.;
  if( FakeRun      and weight==0.  ) return; 
  if( !( NElT==2   and NMuT==0 ) ) return;
  if( !(NMuT==NMuL and NElT==NElL) ) return;
  if( !(NMuT==NMuV and NElT==NElV) ) return;
  if(NElT==2){
    if( ElTColl.at(0).Charge()==ElTColl.at(1).Charge()  ) IsSS2l=true;
    if(!(ElTColl.at(0).Pt()>25 && ElTColl.at(1).Pt()>15)) return;
    Mll = (ElTColl.at(0)+ElTColl.at(1)).M();
    if( !(Mll>60. && Mll<120.) ) return;
  }
  else return;

  if(IsSS2l) Label="_SS"+Label;
  else       Label="_OS"+Label;

  int IdxFlipped=-1;
  float CFSF1=1., CFSF2=1.;
  vector<TString> IterStrList = {"_It1", "_It2", "_It3", "_It4", "_It5", "_It6"};//{"_It1", "_It2", "_It3", "_It4", "_It5"};
  if( (!IsDATA) ){
    int NFk=0, NFlip=0, NCv=0;
    for(unsigned int ie=0; ie<ElTColl.size(); ie++){
      Electron* El(&ElTColl.at(ie));
      int LepType = GetLeptonType_JH(ElTColl.at(ie), truthColl);
      if(LepType<0 && LepType>-5) NFk++;
      else if(LepType<-4) NCv++;
      else if(LepType>0){
        int Idx_Closest    = GenMatchedIdx(*El,truthColl); 
        int IdxType_NearEl = LepType>3? GetPrElType_InSameSCRange(Idx_Closest, truthColl, "IdxType"):Idx_Closest;
        int Idx_NearEl     = LepType>3? IdxType_NearEl/10:Idx_Closest;
        if(El->Charge()*truthColl.at(Idx_NearEl).PID()>0){
          NFlip++; IdxFlipped=ie;
          for(unsigned int it=0; it<IterStrList.size(); it++){
            CFSF1 *= GetCFRSF(*El, "App2Bin1"+IterStrList.at(it)); CFSF2 *= GetCFRSF(*El, "App2Bin2"+IterStrList.at(it));
            //printf("%s, %f %f\n", IterStrList.at(it).Data(), CFSF1, CFSF2);
          }
        }
      } 
    }
    if( !(NFk==0 && NCv==0)  ) return;
    if(   IsSS2l && NFlip==0 ) return;
  }

  vector<float> fEtaEdges   = {0., 1.5, 2.5};
  vector<float> PTEdges     = {15., 35., 50., 200.};
  vector<float> fEtaEdges1D = {0., 0.8, 1.5, 2., 2.5};
  for(unsigned int ie=0; ie<ElTColl.size(); ie++){
    float PT=ElTColl.at(ie).Pt(), fEta=fabs(ElTColl.at(ie).Eta());
    int Nbins = (fEtaEdges.size()-1)*(PTEdges.size()-1), Nbins1D = fEtaEdges1D.size()-1;
    int TmpBinIndex1=0, TmpBinIndex2=0;
    for(unsigned int ieta=0; ieta<fEtaEdges.size()-1; ieta++){
    for(unsigned int ipt=0 ; ipt<PTEdges.size()-1; ipt++){
      if( !(fEta>=fEtaEdges.at(ieta) && fEta<fEtaEdges.at(ieta+1)) ) continue;
      if( !(  PT>=PTEdges.at(ipt)    &&   PT<PTEdges.at(ipt+1)   ) ) continue;
        TmpBinIndex1 = ieta*(PTEdges.size()-1)+ipt+1;
    }}
    for(unsigned int ieta=0; ieta<fEtaEdges1D.size()-1; ieta++){
      if( !(fEta>=fEtaEdges1D.at(ieta) && fEta<fEtaEdges1D.at(ieta+1)) ) continue;
        TmpBinIndex2 = ieta+1;
    }

    if(TmpBinIndex1!=0){
      TString TmpBinIdxStr1 = TString::Itoa(TmpBinIndex1,10);
      FillHist("Mll_App2Bin1_"+TmpBinIdxStr1+Label, Mll, weight*CFSF1, 60, 60., 120.);
      if(!IsDATA){
        FillHist("NCnt_App2Bin1"+Label, TmpBinIndex1, weight*CFSF1, Nbins+1, 0., Nbins+1);
        if(IdxFlipped==(int) ie) FillHist("NCntCF_App2Bin1"+Label, TmpBinIndex1, weight*CFSF1, Nbins+1, 0., Nbins+1);
      }
    }
    if(TmpBinIndex2!=0){
      TString TmpBinIdxStr2 = TString::Itoa(TmpBinIndex2,10);
      FillHist("Mll_App2Bin2_"+TmpBinIdxStr2+Label, Mll, weight*CFSF2, 60, 60., 120.);
      if(!IsDATA){
        FillHist("NCnt_App2Bin2"+Label, TmpBinIndex2, weight*CFSF2, Nbins1D+1, 0., Nbins1D+1);
        if(IdxFlipped==(int) ie) FillHist("NCntCF_App2Bin2"+Label, TmpBinIndex2, weight*CFSF2, Nbins1D+1, 0., Nbins1D+1);
      }
    }
  }
}


void GenSigStudy::CheckMCCFClosure(vector<Muon>& MuTColl, vector<Muon>& MuLColl, vector<Muon>& MuVColl,
                                     vector<Electron>& ElTColl, vector<Electron>& ElLColl, vector<Electron>& ElVColl,
                                     vector<Jet>& JetColl, vector<Jet>& BJetColl, Particle& vMET, float weight, TString Label)
{
  int NMuT=MuTColl.size(), NElT=ElTColl.size(), NMuL=MuLColl.size(), NElL=ElLColl.size(), NMuV=MuVColl.size(), NElV=ElVColl.size();
  bool IsSS2l=false, IsOnZ=false;
  double Mll=-1., PT1=-1., Eta1=999., PT2=-1., Eta2=999., dRll=-1.;
  if( FakeRun      and weight==0.  ) return; 
  if( !( (NElT==2  and NMuT==0)  ) ) return;
  if( !(NMuT==NMuL and NElT==NElL) ) return;
  if( !(NMuT==NMuV and NElT==NElV) ) return;
  if(NElT==2){
    if( ElTColl.at(0).Charge()==ElTColl.at(1).Charge()  ) IsSS2l=true;
    if(!(ElTColl.at(0).Pt()>25 && ElTColl.at(1).Pt()>15)) return;
    Mll  = (ElTColl.at(0)+ElTColl.at(1)).M();
    dRll = ElTColl.at(0).DeltaR(ElTColl.at(1));
    PT1 = ElTColl.at(0).Pt(), Eta1 = ElTColl.at(0).Eta();
    PT2 = ElTColl.at(1).Pt(), Eta2 = ElTColl.at(1).Eta();
  }
  else return;

  if(fabs(Mll-91.2)<15.) IsOnZ=true;

  //int IdxFlipped=-1;
  if( IsSS2l && (!IsDATA) ){
    int NFk=0, NFlip=0, NCv=0;
    for(unsigned int im=0; im<MuTColl.size(); im++){
      int LepType = GetLeptonType_JH(MuTColl.at(im), truthColl);
      if(LepType<0 && LepType>-5) NFk++;
    }
    for(unsigned int ie=0; ie<ElTColl.size(); ie++){
      int LepType = GetLeptonType_JH(ElTColl.at(ie), truthColl);
      if(LepType<0 && LepType>-5) NFk++;
      else if(LepType<-4) NCv++;
      else if(LepType>0){
        int Idx_Closest    = GenMatchedIdx(ElTColl.at(ie),truthColl); 
        int IdxType_NearEl = LepType>3? GetPrElType_InSameSCRange(Idx_Closest, truthColl, "IdxType"):Idx_Closest;
        int Idx_NearEl     = LepType>3? IdxType_NearEl/10:Idx_Closest;
        if(ElTColl.at(ie).Charge()*truthColl.at(Idx_NearEl).PID()>0){
          NFlip++;// IdxFlipped=ie; 
        }
      } 
    }
    if( !(NFk==0 && NCv==0 && NFlip>0) ) return;
  }


  float CFR1=0., CFR2=0., CFRMCDY=0.;
  //float CFR1=0., CFR2=0., CFRMCDY=0., CFRMCTT=0.;
  for(unsigned int ie=0; ie<ElTColl.size() && !IsSS2l; ie++){
    TString TypeStr=IsDATA? "Data":"MC";
    Electron* El(&ElTColl.at(ie));
    CFR1 += GetCFRSF(*El, "App2Bin1_Fin", TypeStr+"Eff");
    CFR2 += GetCFRSF(*El, "App2Bin2_Fin", TypeStr+"Eff");
    CFRMCDY += GetMCCFR(El->Pt(), fabs(El->Eta()), "h2D_PTfEta_QF_DY");
    //CFRMCTT += GetMCCFR(El->Pt(), fabs(El->Eta()), "h2D_PTfEta_QF_TT");
  }

  vector<TString> AppTagList = {"_App2Bin1", "_App2Bin2", "_CFRMCDY"};
  //vector<TString> AppTagList = {"_App2Bin1", "_App2Bin2", "_CFRMCDY", "_CFRMCTT"};
  vector<TString> MassTagList = {""}; if(IsOnZ) MassTagList.push_back("_OnZ");
  vector<float>   CFRList    = {CFR1, CFR2, CFRMCDY};
  //vector<float>   CFRList    = {CFR1, CFR2, CFRMCDY, CFRMCTT};
  TString TypeStr = IsSS2l? "_Obs":"_Exp";

  //Exp from CFR
  for(unsigned int it=0; it<AppTagList.size(); it++){
  for(unsigned int im=0; im<MassTagList.size(); im++){
    TString AppTag(AppTagList.at(it)), MassTag(MassTagList.at(im));
    float CFR = IsSS2l? 1.:CFRList.at(it);
    //printf("%d %.2e %.2e %.2e %.2e %.2e\n", it, CFR, PT1, Eta1, PT1, Eta2);

    FillHist("PTl1"+MassTag+Label+AppTag+TypeStr, PT1, weight*CFR, 30, 0., 300.); 
    FillHist("PTl2"+MassTag+Label+AppTag+TypeStr, PT2, weight*CFR, 20, 0., 200.); 
    FillHist("Etal1"+MassTag+Label+AppTag+TypeStr, Eta1, weight*CFR, 20, -5., 5.); 
    FillHist("Etal2"+MassTag+Label+AppTag+TypeStr, Eta2, weight*CFR, 20, -5., 5.); 
    FillHist("Mll"+MassTag+Label+AppTag+TypeStr, Mll, weight*CFR, 30, 0., 300.);
    FillHist("dRll"+MassTag+Label+AppTag+TypeStr, dRll, weight*CFR, 25, 0., 5.);
    FillHist("NCnt"+MassTag+Label+AppTag+TypeStr, 0., weight*CFR, 1, 0., 1.);
  }}
}


void GenSigStudy::MeasMCCFRate(vector<Muon>& MuTColl, vector<Muon>& MuLColl, vector<Muon>& MuVColl,
                                 vector<Electron>& ElTColl, vector<Electron>& ElLColl, vector<Electron>& ElVColl,
                                 vector<Jet>& JetColl, vector<Jet>& BJetColl, Particle& vMET, float weight, TString Label)
{
  if(IsDATA) return;
  vector<double> PtBinEdges   = {15., 25., 35., 50., 100., 200.};
  vector<double> EtaBinEdges  = {-2.5, -2., -1.47, -0.8, 0., 0.8, 1.47, 2., 2.5};
  vector<double> fEtaBinEdges = {0., 0.8, 1.47, 2., 2.5};

  for(unsigned int ie=0; ie<ElTColl.size(); ie++){
    Electron* El(&ElTColl.at(ie));
    bool IsFlipped=false;
    int ElType = GetLeptonType_JH(*El, truthColl);
    if(ElType<0 or ElType==3) continue;
    else{
      int Idx_Closest    = GenMatchedIdx(*El,truthColl); 
      int IdxType_NearEl = ElType>3? GetPrElType_InSameSCRange(Idx_Closest, truthColl, "IdxType"):Idx_Closest;
      int Idx_NearEl     = ElType>3? IdxType_NearEl/10:Idx_Closest;
      if(El->Charge()*truthColl.at(Idx_NearEl).PID()>0){ IsFlipped=true; }
    } 
  
    double PT = El->Pt(), Eta = El->Eta(), fEta = fabs(Eta);
    TString QLabel = IsFlipped? "_QF":"_QT";
    //float RelIsoNoEA = El->RelIso()+Rho*El->EA()/PT, RelTkIso = El->dr03TkSumPt()/PT ;
    //TString RelIsoTag = RelIsoNoEA<0.06? "_PFIsoNoEAp06":RelIsoNoEA<0.1? "_PFIsoNoEAp1": RelIsoNoEA<0.2? "_PFIsoNoEAp2":"_PRIsoNoEAgtp2";
    //TString TkIsoTag  = RelTkIso<0.06? "_RelTkIsop06":RelTkIso<0.1? "_RelTkIsop1": RelTkIso<0.2? "_RelTkIsop2":"_PRIsoNoEAgtp2";
    //vector<TString> CutTagList = {"", RelIsoTag, TkIsoTag};
    vector<TString> CutTagList = {""};
    for(unsigned int it=0; it<CutTagList.size(); it++){
      TString CutTag(CutTagList.at(it));
      FillHist("h1D_PT"+QLabel+CutTag+Label, PT, weight, PtBinEdges.size()-1, &PtBinEdges[0]);
      FillHist("h1D_Eta"+QLabel+CutTag+Label, Eta, weight, EtaBinEdges.size()-1, &EtaBinEdges[0]);
      FillHist("h2D_PTEta"+QLabel+CutTag+Label, PT, Eta, weight,
                PtBinEdges.size()-1, &PtBinEdges[0], EtaBinEdges.size()-1, &EtaBinEdges[0]);
      FillHist("h2D_PTfEta"+QLabel+CutTag+Label, PT, fEta, weight,
                PtBinEdges.size()-1, &PtBinEdges[0], fEtaBinEdges.size()-1, &fEtaBinEdges[0]);
    }
  }
}


void GenSigStudy::MeasMCPTScale(vector<Muon>& MuTColl, vector<Muon>& MuLColl, vector<Muon>& MuVColl,
                                  vector<Electron>& ElTColl, vector<Electron>& ElLColl, vector<Electron>& ElVColl,
                                  vector<Jet>& JetColl, vector<Jet>& BJetColl, Particle& vMET, float weight, TString Label)
{
  if(IsDATA) return;
  vector<double> PtBinEdges   = {15., 25., 35., 50., 100., 200.};
  vector<double> EtaBinEdges  = {-2.5, -2., -1.47, -0.8, 0., 0.8, 1.47, 2., 2.5};
  vector<double> fEtaBinEdges = {0., 0.8, 1.47, 2., 2.5};

  for(unsigned int ie=0; ie<ElTColl.size(); ie++){
    Electron* El(&ElTColl.at(ie));
    bool IsFlipped=false;
    int ElType = GetLeptonType_JH(*El, truthColl);
    double PT = El->Pt(), Eta = El->Eta(), fEta = fabs(Eta), PTGen=0., PTResponse=0.;
    if(ElType<0 or ElType==3) continue;
    else{
      int Idx_Closest    = GenMatchedIdx(*El,truthColl); 
      int IdxType_NearEl = ElType>3? GetPrElType_InSameSCRange(Idx_Closest, truthColl, "IdxType"):Idx_Closest;
      int Idx_NearEl     = ElType>3? IdxType_NearEl/10:Idx_Closest;
      int Idx_NearEl_1st = LastSelfMotherIdx(Idx_NearEl, truthColl);
      PTGen      = Idx_NearEl_1st>1? truthColl.at(Idx_NearEl_1st).Pt():0.;
      PTResponse =          PTGen>0?                          PT/PTGen:0.;
      if(El->Charge()*truthColl.at(Idx_NearEl).PID()>0){ IsFlipped=true; }
    } 
  
    TString QLabel = IsFlipped? "_QF":"_QT";
    vector<TString> NumDenList = {"_SumWPTResponse", "_SumW"};
    for(unsigned int im=0; im<NumDenList.size(); im++){
      TString NumDenTag(NumDenList.at(im));
      float ValZ = NumDenTag!="_SumW"? PTResponse*weight:weight;
      FillHist("h1D_PTGen"+QLabel+NumDenTag+Label, PTGen, ValZ, PtBinEdges.size()-1, &PtBinEdges[0]);
      FillHist("h1D_Eta"+QLabel+NumDenTag+Label, Eta, ValZ, EtaBinEdges.size()-1, &EtaBinEdges[0]);
      FillHist("h2D_PTGenEta"+QLabel+NumDenTag+Label, PTGen, Eta, ValZ,
                PtBinEdges.size()-1, &PtBinEdges[0], EtaBinEdges.size()-1, &EtaBinEdges[0]);
      FillHist("h2D_PTGenfEta"+QLabel+NumDenTag+Label, PTGen, fEta, ValZ,
                PtBinEdges.size()-1, &PtBinEdges[0], fEtaBinEdges.size()-1, &fEtaBinEdges[0]);
    }
  }
}


float GenSigStudy::GetFlipCorrPT(Electron& El, TString Tag, TString Option){

  if(!(IsDATA  && Option.Contains("Data"))) return 0.;

  bool DoScale = Option.Contains("Scale"), DoSmear = Option.Contains("Smear");
  float PT=El.Pt(), fEta=fabs(El.Eta());
  int EtaRegIndex1 = fEta<1.47? 0:1;
  int EtaRegIndex2 = fEta<0.8? 0:fEta<1.47? 1: fEta<2.? 2:3;
  int PtRegIndex1  = PT<35? 0:PT<50? 1: 2;
  int PtRegIndex2  = PT<35? 0:PT<50? 1:PT<100? 2:3;
  int BinIndex1 = EtaRegIndex1*3+PtRegIndex1+1; 
  int BinIndex2 = EtaRegIndex2+1; 
  int BinIndex3 = PtRegIndex2 +1; 

  float PTScaleCorr=0., PTResCorr=0., ReturnPT=PT, RelRes=0.;
  if(Tag.Contains("App2Bin1_")){
    int Idx = BinIndex1;
    PTScaleCorr = Idx==1? 0.978:Idx==2? 0.981:Idx==3? 0.988:Idx==4? 0.972:Idx==5? 0.985:Idx==6? 0.990:0.;
    PTResCorr   = Idx==1?  1.38:Idx==2?  1.47:Idx==3?  1.31:Idx==4?  1.15:Idx==5?  1.08:Idx==6? 0.981:0.;
    RelRes      = Idx==1? 0.0322:Idx==2? 0.0276:Idx==3? 0.0264:Idx==4? 0.0388:Idx==5? 0.0375:Idx==6? 0.0382:0.;
  }
  else if(Tag.Contains("App2Bin2_")){
    int Idx = BinIndex2;
    PTScaleCorr = 0.985;
    PTResCorr   = 1.75;
    RelRes      = Idx==1? 0.01:Idx==2? 0.0153:Idx==3? 0.0217:Idx==4? 0.0208:0.;
  }
  else if(Tag.Contains("App2Bin3_")){
    int Idx = BinIndex3;
    PTScaleCorr = Idx==1? 0.976:Idx==2? 0.985:Idx==3? 0.992:Idx==4? 0.999:0.;
    PTResCorr   = Idx==1?  1.29:Idx==2?  1.41:Idx==3?  1.32:Idx==4?  1.18:0.;
    RelRes      = Idx==1? 0.0343:Idx==2? 0.0287:Idx==3? 0.0285:Idx==4? 0.0297:0.;
  }
  PTScaleCorr = 1.-2.*(1.-PTScaleCorr);
  PTResCorr   = 1.-2.*(1.-PTResCorr);

  if(DoScale) ReturnPT = PT*PTScaleCorr;
  if(DoSmear) ReturnPT = ReturnPT*( 1.+gRandom->Gaus(0,RelRes)*sqrt(max(pow(PTResCorr,2.)-1,0.)) );

  return ReturnPT;
}


float GenSigStudy::GetCFRSF(Electron& El, TString Tag, TString Option){

  if     (IsDATA  && Option=="") return 1.;
  else if(IsDATA  && Option!="DataEff") return 0.;
  else if(!IsDATA && Option=="DataEff") return 0.;

  bool ReturnMCEff=Option.Contains("MCEff"), ReturnDataEff=Option.Contains("DataEff");
  float PT=min(El.Pt(),199.), fEta=min(fabs(El.Eta()),2.45);

  vector<float> fEtaEdges    = {0., 1.5, 2.5};
  vector<float> PTEdges      = {15., 35., 50., 200.};
  vector<float> fEtaEdges1D  = {0., 0.8, 1.5, 2., 2.5};

  int BinIndex1=0, BinIndex2=0;//, BinIndexMC=0;
  for(unsigned int ieta=0; ieta<fEtaEdges.size()-1; ieta++){
  for(unsigned int ipt=0 ; ipt<PTEdges.size()-1; ipt++){
    if( !(fEta>=fEtaEdges.at(ieta) && fEta<fEtaEdges.at(ieta+1)) ) continue;
    if( !(  PT>=PTEdges.at(ipt)    &&   PT<PTEdges.at(ipt+1)   ) ) continue;
      BinIndex1 = ieta*(PTEdges.size()-1)+ipt+1;
  }}
  for(unsigned int ieta=0; ieta<fEtaEdges1D.size()-1; ieta++){
    if( !(fEta>=fEtaEdges1D.at(ieta) && fEta<fEtaEdges1D.at(ieta+1)) ) continue;
      BinIndex2 = ieta+1;
  }

  float SF=1., MCEff=1., DataEff=1., ReturnVal=1.;
  if(Tag.Contains("App2Bin1_")){
    int Idx = BinIndex1;
    if(GetEraShort()=="2016a"){
      if(Tag.EndsWith("It1")) SF = Idx==1? 0.775609:Idx==2? 0.774063:Idx==3? 0.745159:Idx==4? 0.74864:Idx==5? 0.776881:Idx==6? 0.781969:1.;
      if(Tag.EndsWith("It2")) SF = Idx==1? 1.01206:Idx==2? 1.00422:Idx==3? 0.994629:Idx==4? 0.994307:Idx==5? 0.99996:Idx==6? 1.00471:1.;
      if(Tag.EndsWith("It3")) SF = Idx==1? 1.01145:Idx==2? 1.00336:Idx==3? 0.996687:Idx==4? 0.998538:Idx==5? 0.999571:Idx==6? 1.00165:1.;
      if(Tag.EndsWith("It4")) SF = Idx==1? 1.00999:Idx==2? 1.00244:Idx==3? 0.997049:Idx==4? 0.999518:Idx==5? 0.999723:Idx==6? 1.0005:1.;
      if(Tag.EndsWith("It5")) SF = Idx==1? 1.00868:Idx==2? 1.00163:Idx==3? 0.997338:Idx==4? 0.999864:Idx==5? 0.999858:Idx==6? 1.00012:1.;
      if(Tag.EndsWith("It6")) SF = Idx==1? 1.00756:Idx==2? 1.001  :Idx==3? 0.997521:Idx==4? 0.999976:Idx==5? 0.99996:Idx==6? 0.999991:1.;
      if(Tag.EndsWith("It7")) SF = Idx==1? 1.00635:Idx==2? 1.00057:Idx==3? 0.986847:Idx==4? 0.999981:Idx==5? 0.999955:Idx==6? 0.999942:1.;
      if(Tag.EndsWith("Fin")){
        SF = Idx==1? 0.770188:Idx==2? 0.813516:Idx==3? 0.771032:Idx==4? 0.712556:Idx==5? 0.75322:Idx==6? 0.791322:1.;
        DataEff = Idx==1? 0.000125861:Idx==2? 0.00015171:Idx==3? 0.000169858:Idx==4? 0.00207889:Idx==5? 0.00255606:Idx==6? 0.00337988:1.;
        MCEff = Idx==1? 0.000163416:Idx==2? 0.000186487:Idx==3? 0.000220299:Idx==4? 0.00291751:Idx==5? 0.00339351:Idx==6? 0.00427117:1.;
      }
    }
    else if(GetEraShort()=="2016b"){
      if(Tag.EndsWith("It1")) SF = Idx==1? 0.821416:Idx==2? 0.831932:Idx==3? 0.89228:Idx==4? 0.806955:Idx==5? 0.859091:Idx==6? 0.832816:1.;
      if(Tag.EndsWith("It2")) SF = Idx==1? 0.987547:Idx==2? 0.990379:Idx==3? 1.05212:Idx==4? 0.994371:Idx==5? 1.00279:Idx==6? 0.997317:1.;
      if(Tag.EndsWith("It3")) SF = Idx==1? 0.988828:Idx==2? 0.992663:Idx==3? 1.03069:Idx==4? 0.998864:Idx==5? 1.00041:Idx==6? 0.999416:1.;
      if(Tag.EndsWith("It4")) SF = Idx==1? 0.989498:Idx==2? 0.994795:Idx==3? 1.02581:Idx==4? 0.999526:Idx==5? 1.00011:Idx==6? 1.00003:1.;
      if(Tag.EndsWith("It5")) SF = Idx==1? 0.99021 :Idx==2? 0.996268:Idx==3? 1.01705:Idx==4? 0.999536:Idx==5? 1.00006:Idx==6? 1.00009:1.;
      if(Tag.EndsWith("It6")) SF = Idx==1? 0.988109:Idx==2? 0.997374:Idx==3? 1.01142:Idx==4? 0.999741:Idx==5? 1.00005:Idx==6? 1.00021:1.;
      if(Tag.EndsWith("It7")) SF = Idx==1? 0.992103:Idx==2? 0.998285:Idx==3? 1.00793:Idx==4? 0.999749:Idx==5? 1.00004:Idx==6? 1.00025:1.;
      if(Tag.EndsWith("Fin")){
        SF = Idx==1? 0.748377:Idx==2? 0.822857:Idx==3? 0.983595:Idx==4? 0.79469:Idx==5? 0.869773:Idx==6? 0.829995:1.;
        DataEff = Idx==1? 0.000123377:Idx==2? 0.000145494:Idx==3? 0.000211887:Idx==4? 0.00224042:Idx==5? 0.00276965:Idx==6? 0.00328515:1.;
        MCEff = Idx==1? 0.000164859:Idx==2? 0.000176816:Idx==3? 0.000215421:Idx==4? 0.00281924:Idx==5? 0.00318434:Idx==6? 0.00395804:1.;
      }
    }
    else if(DataYear==2017){
      if(Tag.EndsWith("It1")) SF = Idx==1? 1.31546:Idx==2? 1.34459:Idx==3? 1.42202:Idx==4? 1.31019:Idx==5? 1.31198:Idx==6? 1.26319:1.;
      if(Tag.EndsWith("It2")) SF = Idx==1? 0.990088:Idx==2? 1.01596:Idx==3? 1.0535:Idx==4? 1.00293:Idx==5? 1.00132:Idx==6? 0.98922:1.;
      if(Tag.EndsWith("It3")) SF = Idx==1? 1.00466:Idx==2? 1.00875:Idx==3? 1.03195:Idx==4? 1.00139:Idx==5? 1.00026:Idx==6? 0.996263:1.;
      if(Tag.EndsWith("It4")) SF = Idx==1? 1.00248:Idx==2? 1.00462:Idx==3? 1.0182:Idx==4? 1.00009:Idx==5? 0.997225:Idx==6? 0.998542:1.;
      if(Tag.EndsWith("It5")) SF = Idx==1? 1.00781:Idx==2? 1.00366:Idx==3? 1.01089:Idx==4? 0.999896:Idx==5? 1.00244:Idx==6? 0.999949:1.;
      if(Tag.EndsWith("It6")) SF = Idx==1? 1.00554:Idx==2? 1.00102:Idx==3? 1.00557:Idx==4? 0.999745:Idx==5? 0.99719:Idx==6? 0.999462:1.;
      if(Tag.EndsWith("It7")) SF = Idx==1? 0.999939:Idx==2? 1.00159:Idx==3? 1.00337:Idx==4? 0.999888:Idx==5? 1.0026:Idx==6? 1.00028:1.;
      if(Tag.EndsWith("Fin")){
        SF = Idx==1? 1.2696:Idx==2? 1.36965:Idx==3? 1.52389:Idx==4? 1.37131:Idx==5? 1.31699:Idx==6? 1.2204:1.;
        DataEff = Idx==1? 6.65722e-05:Idx==2? 8.34845e-05:Idx==3? 0.000117936:Idx==4? 0.00133884:Idx==5? 0.00140659:Idx==6? 0.00173507:1.;
        MCEff = Idx==1? 5.24355e-05:Idx==2? 6.0953e-05:Idx==3? 7.73914e-05:Idx==4? 0.000976318:Idx==5? 0.00106803:Idx==6? 0.00142172:1.;
      }
    }
    else if(DataYear==2018){
      if(Tag.EndsWith("It1")) SF = Idx==1? 1.29882:Idx==2? 1.28704:Idx==3? 1.34991:Idx==4? 1.28662 :Idx==5? 1.25111 :Idx==6? 1.29814:1.;
      if(Tag.EndsWith("It2")) SF = Idx==1? 1.0129 :Idx==2? 1.0102 :Idx==3? 1.0345 :Idx==4? 0.998252:Idx==5? 0.996831:Idx==6? 1.00719:1.;
      if(Tag.EndsWith("It3")) SF = Idx==1? 1.00976:Idx==2? 1.00722:Idx==3? 1.02089:Idx==4? 0.998148:Idx==5? 0.998852:Idx==6? 1.00245:1.;
      if(Tag.EndsWith("It4")) SF = Idx==1? 1.00756:Idx==2? 1.005:Idx==3? 1.01265:Idx==4? 0.998951:Idx==5? 0.999457:Idx==6? 1.00089:1.;
      if(Tag.EndsWith("It5")) SF = Idx==1? 1.00669:Idx==2? 1.00425:Idx==3? 1.0074:Idx==4? 0.999437:Idx==5? 0.99971:Idx==6? 1.00032:1.;
      if(Tag.EndsWith("It6")) SF = Idx==1? 1.00557:Idx==2? 1.0018:Idx==3? 1.00407:Idx==4? 0.999685:Idx==5? 0.999805:Idx==6? 1.0001:1.;
      if(Tag.EndsWith("It7")) SF = Idx==1? 1.00427:Idx==2? 1.00118:Idx==3? 1.00215:Idx==4? 0.999808:Idx==5? 0.999892:Idx==6? 1.00003:1.;
      if(Tag.EndsWith("Fin")){
        SF = Idx==1? 1.46065:Idx==2? 1.36472:Idx==3? 1.38385:Idx==4? 1.30511:Idx==5? 1.27019:Idx==6? 1.36434:1.;
        DataEff = Idx==1? 8.256e-05:Idx==2? 8.34791e-05:Idx==3? 0.000107939:Idx==4? 0.00125831:Idx==5? 0.00139244:Idx==6? 0.00190927:1.;
        MCEff = Idx==1? 5.65228e-05:Idx==2? 6.11694e-05:Idx==3? 7.79988e-05:Idx==4? 0.00096414:Idx==5? 0.00109625:Idx==6? 0.0013994:1.;
      }
    }
  } 
  else if(Tag.Contains("App2Bin2_")){
    int Idx = BinIndex2;
    if(GetEraShort()=="2016a"){
      if(Tag.EndsWith("It1")) SF = Idx==1? 0.750319:Idx==2? 0.796936:Idx==3? 0.7364:Idx==4? 0.819356:1.;
      if(Tag.EndsWith("It2")) SF = Idx==1? 0.975959:Idx==2? 1.01854:Idx==3? 0.984197:Idx==4? 1.01592:1.;
      if(Tag.EndsWith("It3")) SF = Idx==1? 0.976943:Idx==2? 1.01171:Idx==3? 0.994717:Idx==4? 1.00419:1.;
      if(Tag.EndsWith("It4")) SF = Idx==1? 0.97774:Idx==2? 1.00757:Idx==3? 0.998226:Idx==4? 1.00104:1.;
      if(Tag.EndsWith("It5")) SF = Idx==1? 0.978517:Idx==2? 1.00492:Idx==3? 0.999373:Idx==4? 1.00028:1.;
      if(Tag.EndsWith("It6")) SF = Idx==1? 0.979391:Idx==2? 1.00322:Idx==3? 0.999751:Idx==4? 1.00003:1.;
      if(Tag.EndsWith("It7")) SF = Idx==1? 0.980398:Idx==2? 1.00217:Idx==3? 0.999901:Idx==4? 1.00002:1.;
      if(Tag.EndsWith("Fin")){
        SF = Idx==1? 0.655387:Idx==2? 0.842453:Idx==3? 0.714889:Idx==4? 0.804131:1.;
        DataEff = Idx==1? 2.6199e-05:Idx==2? 0.000344799:Idx==3? 0.00230424:Idx==4? 0.00288139:1.;
        MCEff = Idx==1? 3.99749e-05:Idx==2? 0.00040928:Idx==3? 0.00322321:Idx==4? 0.00358324:1.;
      }
    }
    else if(GetEraShort()=="2016b"){
      if(Tag.EndsWith("It1")) SF = Idx==1? 0.821062:Idx==2? 0.854276:Idx==3? 0.841132:Idx==4? 0.838997:1.;
      if(Tag.EndsWith("It2")) SF = Idx==1? 0.975925:Idx==2? 1.01022:Idx==3? 0.99995:Idx==4? 0.99911:1.;
      if(Tag.EndsWith("It3")) SF = Idx==1? 0.977137:Idx==2? 1.0066:Idx==3? 0.999947:Idx==4? 0.99958:1.;
      if(Tag.EndsWith("It4")) SF = Idx==1? 0.978144:Idx==2? 1.00436:Idx==3? 0.999885:Idx==4? 0.99979:1.;
      if(Tag.EndsWith("It5")) SF = Idx==1? 0.979403:Idx==2? 1.00295:Idx==3? 0.999991:Idx==4? 0.99989:1.;
      if(Tag.EndsWith("It6")) SF = Idx==1? 0.980386:Idx==2? 1.00212:Idx==3? 0.999995:Idx==4? 0.99996:1.;
      if(Tag.EndsWith("It7")) SF = Idx==1? 0.981706:Idx==2? 1.00159:Idx==3? 1.00001:Idx==4? 0.999967:1.;
      if(Tag.EndsWith("Fin")){
        SF = Idx==1? 0.619954:Idx==2? 0.896209:Idx==3? 0.843693:Idx==4? 0.846716:1.;
        DataEff = Idx==1? 2.77502e-05:Idx==2? 0.000355046:Idx==3? 0.0026395:Idx==4? 0.00274673:1.;
        MCEff = Idx==1? 4.47616e-05:Idx==2? 0.000396165:Idx==3? 0.00312851:Idx==4? 0.00324398:1.;
      }
    }
    else if(DataYear==2017){
      if(Tag.EndsWith("It1")) SF = Idx==1? 1.3573:Idx==2? 1.33212:Idx==3? 1.33763:Idx==4? 1.26674:1.;
      if(Tag.EndsWith("It2")) SF = Idx==1? 1.03055:Idx==2? 1.01519:Idx==3? 1.00959:Idx==4? 0.99173:1.;
      if(Tag.EndsWith("It3")) SF = Idx==1? 1.02256:Idx==2? 1.00035:Idx==3? 1.00275:Idx==4? 0.999193:1.;
      if(Tag.EndsWith("It4")) SF = Idx==1? 1.01851:Idx==2? 1.00759:Idx==3? 1.00054:Idx==4? 0.997919:1.;
      if(Tag.EndsWith("It5")) SF = Idx==1? 1.01519:Idx==2? 1.00477:Idx==3? 1.00012:Idx==4? 1.00111:1.;
      if(Tag.EndsWith("It6")) SF = Idx==1? 1.01202:Idx==2? 1.00224:Idx==3? 0.999604:Idx==4? 0.999981:1.;
      if(Tag.EndsWith("It7")) SF = Idx==1? 1.0102:Idx==2? 1.00117:Idx==3? 0.999779:Idx==4? 0.999931:1.;
      if(Tag.EndsWith("Fin")){
        SF = Idx==1? 1.24704:Idx==2? 1.36859:Idx==3? 1.36859:Idx==4? 1.28726:1.;
        DataEff = Idx==1? 2.57751e-05:Idx==2? 0.000171696:Idx==3? 0.00117306:Idx==4? 0.00186744:1.;
        MCEff = Idx==1? 2.0669e-05:Idx==2? 0.000125455:Idx==3? 0.000857131:Idx==4? 0.0014507:1.;
      }
    }
    else if(DataYear==2018){
      if(Tag.EndsWith("It1")) SF = Idx==1? 1.28468:Idx==2? 1.3082:Idx==3? 1.30601:Idx==4? 1.2365:1.;
      if(Tag.EndsWith("It2")) SF = Idx==1? 1.00359:Idx==2? 1.0206:Idx==3? 1.01071:Idx==4? 0.993675:1.;
      if(Tag.EndsWith("It3")) SF = Idx==1? 0.998165:Idx==2? 1.01212:Idx==3? 1.00297:Idx==4? 0.9978:1.;
      if(Tag.EndsWith("It4")) SF = Idx==1? 0.996209:Idx==2? 1.00759:Idx==3? 1.00076:Idx==4? 0.999219:1.;
      if(Tag.EndsWith("It5")) SF = Idx==1? 0.995682:Idx==2? 1.00486:Idx==3? 1.00014:Idx==4? 0.999708:1.;
      if(Tag.EndsWith("It6")) SF = Idx==1? 0.995179:Idx==2? 1.00314:Idx==3? 0.999968:Idx==4? 0.999866:1.;
      if(Tag.EndsWith("It7")) SF = Idx==1? 0.995276:Idx==2? 1.00212:Idx==3? 0.999952:Idx==4? 0.999937:1.;
      if(Tag.EndsWith("Fin")){
        SF = Idx==1? 1.37469:Idx==2? 1.39657:Idx==3? 1.35169:Idx==4? 1.24908:1.;
        DataEff = Idx==1? 2.57045e-05:Idx==2? 0.000183513:Idx==3? 0.00114237:Idx==4? 0.00183787:1.;
        MCEff = Idx==1? 1.86983e-05:Idx==2? 0.000131403:Idx==3? 0.000845138:Idx==4? 0.00147138:1.;
      }
    }
  }

  if     (ReturnMCEff  ) ReturnVal = MCEff;
  else if(ReturnDataEff) ReturnVal = DataEff;
  else                   ReturnVal = SF; 

  return ReturnVal;
}


float GenSigStudy::GetMCCFR(float VarX, float VarY, TString Key){
return 1.;

}




GenSigStudy::GenSigStudy(){


}


GenSigStudy::~GenSigStudy(){


}

