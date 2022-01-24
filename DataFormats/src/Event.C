#include "Event.h"

ClassImp(Event)

Event::Event(){
  j_MCweight = 1.;
  j_nPV = -999;
  j_DataYear = -999;
  j_DataEra = "";
}

Event::~Event(){

}

void Event::SetMCweight(double genw){
  if(genw>0) j_MCweight=1.;
  else j_MCweight=-1.;
}

void Event::SetnPV(double n){
  j_nPV = n;
}

void Event::SetTrigger(vector<string> HLT_TriggerName){
  j_HLT_TriggerName = HLT_TriggerName;
}

bool Event::PassTrigger(TString trig){
  std::vector<TString> tmp_vec;
  tmp_vec.push_back(trig);
  return PassTrigger(tmp_vec);
}

bool Event::PassTrigger(std::vector<TString> trigs){

  for(unsigned int i=0; i<trigs.size(); i++){
    TString this_check_trig = trigs.at(i);

    //cout << this_check_trig << endl;
    for(unsigned int j=0; j<j_HLT_TriggerName.size(); j++){

      //cout << j_HLT_TriggerName.at(j) << endl;
      if( j_HLT_TriggerName.at(j).find(this_check_trig)!=std::string::npos ){
        return true;
      }
    }

  }
  return false;
}

double Event::GetTriggerLumi(TString trig){
  if(j_DataEra=="2016preVFP"){
    if(trig=="Full") return 19517.523849863;
    else if(trig=="HLT_Mu3_PFJet40_v") return 3.911703648;
    else if(trig=="HLT_Mu8_v") return 3.319291722;
    else if(trig=="HLT_Mu17_v") return 259.029439505;
    else if(trig=="HLT_Mu20_v") return 109.124528366;
    else if(trig=="HLT_Mu27_v") return 149.654826484;
    else if(trig=="HLT_Mu50_v") return 19517.523849863;
    else if(trig=="HLT_Mu55_v") return 19517.523849863;
    else if(trig=="HLT_DoublePhoton60_v") return 19517.523849863;
    else if(trig=="HLT_DoublePhoton85_v") return 19517.523849863;
    else if(trig=="HLT_Photon50_v") return 18.734556169;
    else if(trig=="HLT_Photon75_v") return 83.007650452;
    else if(trig=="HLT_Photon90_v") return 163.439249664;
    else if(trig=="HLT_Photon120_v") return 338.327429849;
    else if(trig=="HLT_Photon175_v") return 19517.523849863;
    else if(trig=="HLT_IsoMu24_v") return 19517.523849863;
    else if(trig=="HLT_IsoMu27_v") return 19517.523849863;
    else if(trig=="HLT_Ele8_CaloIdL_TrackIdL_IsoVL_PFJet30_v") return 4.127188014;
    else if(trig=="HLT_Ele12_CaloIdL_TrackIdL_IsoVL_PFJet30_v") return 11.033890219;
    else if(trig=="HLT_Ele17_CaloIdL_TrackIdL_IsoVL_PFJet30_v") return 52.443756312; // JH : from https://indico.cern.ch/event/1100580/contributions/4630237/attachments/2366544/4041115/HN_20211216.pdf . Mu17, Mu8 leg from John's branch.
    else if(trig=="HLT_Ele23_CaloIdL_TrackIdL_IsoVL_PFJet30_v") return 52.790026620;
    else if(trig=="HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v") return 19517.523849863;
    else if(trig=="HLT_Mu17_TrkIsoVVL_v") return 192.1246;
    else if(trig=="HLT_Mu8_TrkIsoVVL_v") return 6.58539;
  }else if(j_DataEra=="2016postVFP"){
    if(trig=="Full") return 16812.151722482;
    else if(trig=="HLT_Mu3_PFJet40_v") return 3.580526616;
    else if(trig=="HLT_Mu8_v") return 0.659286323;
    else if(trig=="HLT_Mu17_v") return 26.872793405;
    else if(trig=="HLT_Mu20_v") return 32.291949992;
    else if(trig=="HLT_Mu27_v") return 103.565936026;
    else if(trig=="HLT_Mu50_v") return 16812.151722482;
    else if(trig=="HLT_Mu55_v") return 16812.151722482;
    else if(trig=="HLT_DoublePhoton60_v") return 16812.151722482;
    else if(trig=="HLT_DoublePhoton85_v") return 16812.151722482;
    else if(trig=="HLT_Photon50_v") return 12.643834933;
    else if(trig=="HLT_Photon75_v") return 53.053657641;
    else if(trig=="HLT_Photon90_v") return 103.565936026;
    else if(trig=="HLT_Photon120_v") return 204.590057915;
    else if(trig=="HLT_Photon175_v") return 16812.151722482;
    else if(trig=="HLT_IsoMu24_v") return 16812.151722482;
    else if(trig=="HLT_IsoMu27_v") return 16812.151722482;
    else if(trig=="HLT_Ele8_CaloIdL_TrackIdL_IsoVL_PFJet30_v") return 2.938006053;
    else if(trig=="HLT_Ele12_CaloIdL_TrackIdL_IsoVL_PFJet30_v") return 3.980060594;
    else if(trig=="HLT_Ele17_CaloIdL_TrackIdL_IsoVL_PFJet30_v") return 6.834870773;
    else if(trig=="HLT_Ele23_CaloIdL_TrackIdL_IsoVL_PFJet30_v") return 10.699483420;
    else if(trig=="HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v") return 16812.151722482;
    else if(trig=="HLT_Mu17_TrkIsoVVL_v") return 26.87279;
    else if(trig=="HLT_Mu8_TrkIsoVVL_v") return 1.29683;
  }else if(j_DataEra=="2017"){
    if(trig=="Full") return 41477.877400009;
    else if(trig=="HLT_Mu3_PFJet40_v") return 4.607782551;
    else if(trig=="HLT_Mu8_v"){
      return 2.602078443;
      //FIXME what is norm?? (JS's code)
      //==== 180829 Norm Checked : sf = 1.41036
      //==== 181206 Norm Checked : sf = 1.33461
      //return 2.605;;
      //return 2.605*1.33461;
    }
    else if(trig=="HLT_Mu17_v") return 70.005238765;
    else if(trig=="HLT_Mu19_v") return 46.204786104;
    else if(trig=="HLT_Mu20_v") return 575.585018236;
    else if(trig=="HLT_Mu27_v") return 184.843129035;
    else if(trig=="HLT_Mu50_v") return 41477.877400009;
    else if(trig=="HLT_Mu55_v") return 27121.940558082;
    else if(trig=="HLT_DoublePhoton70_v") return 41477.877400009;
    else if(trig=="HLT_DoublePhoton85_v") return 41477.877400009;
    else if(trig=="HLT_Photon25_v") return 1.339434797;
    else if(trig=="HLT_Photon33_v") return 14.319591410;
    else if(trig=="HLT_Photon50_v") return 22.182993392;
    else if(trig=="HLT_Photon75_v") return 101.406554985;
    else if(trig=="HLT_Photon90_v") return 122.130341981;
    else if(trig=="HLT_Photon120_v") return 490.132351457;
    else if(trig=="HLT_Photon150_v") return 689.862207927;
    else if(trig=="HLT_Photon175_v") return 1245.403311711;
    else if(trig=="HLT_Photon200_v") return 41477.877400009;
    else if(trig=="HLT_IsoMu24_v") return 37997.004705584;
    else if(trig=="HLT_IsoMu27_v") return 41477.877400009;
    else if(trig=="HLT_IsoMu30_v") return 27121.940558082;
    else if(trig=="HLT_Ele8_CaloIdL_TrackIdL_IsoVL_PFJet30_v") return 3.970041451;
    else if(trig=="HLT_Ele12_CaloIdL_TrackIdL_IsoVL_PFJet30_v") return 27.683553584;
    else if(trig=="HLT_Ele15_CaloIdL_TrackIdL_IsoVL_PFJet30_v") return 0.000600725;
    else if(trig=="HLT_Ele23_CaloIdL_TrackIdL_IsoVL_PFJet30_v") return 43.453223350;
    else if(trig=="HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v") return 7455.394595245;
    else if(trig=="HLT_Mu17_TrkIsoVVL_v") return 65.8989;
    else if(trig=="HLT_Mu8_TrkIsoVVL_v") return 2.89970;
    else if(trig=="HLT_Mu19_TrkIsoVVL_Mu9_TrkIsoVVL_DZ_v") return 2613.476499000;
    else if(trig=="HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8_v") return 41477.877400009;
    else if(trig=="HLT_Mu19_TrkIsoVVL_Mu9_TrkIsoVVL_DZ_Mass8_v") return 27121.940558082;
    else if(trig=="HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8_v") return 36674.511073834;
    else if(trig=="HLT_Mu19_TrkIsoVVL_Mu9_TrkIsoVVL_DZ_Mass3p8_v") return 27121.940558082;
  }else if(j_DataEra=="2018"){
    if(trig=="Full") return 59827.879502925;
    else if(trig=="HLT_Mu3_PFJet40_v") return 2.704239929;
    else if(trig=="HLT_Mu8_v") return 8.566603827;
    else if(trig=="HLT_Mu17_v") return 45.852032056;
    else if(trig=="HLT_Mu19_v") return 45.852032056;
    else if(trig=="HLT_Mu20_v") return 55.360539057;
    else if(trig=="HLT_Mu27_v") return 125.967123844;
    else if(trig=="HLT_Mu50_v") return 59827.879502925;
    else if(trig=="HLT_Mu55_v") return 59827.879502925;
    else if(trig=="HLT_DoublePhoton70_v") return 59827.879502925;
    else if(trig=="HLT_DoublePhoton85_v") return 59827.879502925;
    else if(trig=="HLT_Photon33_v") return 2.349799925;
    else if(trig=="HLT_Photon50_v") return 12.960071823;
    else if(trig=="HLT_Photon75_v") return 117.946263489;
    else if(trig=="HLT_Photon90_v") return 117.622232475;
    else if(trig=="HLT_Photon120_v") return 470.863308303;
    else if(trig=="HLT_Photon150_v") return 478.335294777;
    else if(trig=="HLT_Photon175_v") return 952.895805882;
    else if(trig=="HLT_Photon200_v") return 59827.879502925;
    else if(trig=="HLT_IsoMu24_v") return 59819.714470919;
    else if(trig=="HLT_IsoMu27_v") return 59827.879502925;
    else if(trig=="HLT_IsoMu30_v") return 59827.879502925;
    else if(trig=="HLT_Ele8_CaloIdL_TrackIdL_IsoVL_PFJet30_v") return 6.424543223;
    else if(trig=="HLT_Ele12_CaloIdL_TrackIdL_IsoVL_PFJet30_v") return 38.917235485;
    else if(trig=="HLT_Ele15_CaloIdL_TrackIdL_IsoVL_PFJet30_v") return 0.001834965;
    else if(trig=="HLT_Ele23_CaloIdL_TrackIdL_IsoVL_PFJet30_v") return 38.973910595;
    else if(trig=="HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v") return 3008.003592622;
    else if(trig=="HLT_Mu17_TrkIsoVVL_v") return 45.852;
    else if(trig=="HLT_Mu8_TrkIsoVVL_v") return 8.58157;
    else if(trig=="HLT_Mu19_TrkIsoVVL_Mu9_TrkIsoVVL_DZ_v") return 3135.331113947;
    else if(trig=="HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8_v") return 59827.879502925;
    else if(trig=="HLT_Mu19_TrkIsoVVL_Mu9_TrkIsoVVL_DZ_Mass8_v") return 59827.879502925;
    else if(trig=="HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8_v") return 59827.879502925;
    else if(trig=="HLT_Mu19_TrkIsoVVL_Mu9_TrkIsoVVL_DZ_Mass3p8_v") return 59827.879502925;
  }

  cout << "[Event::GetTriggerLumi] Wrong trigger (DataEra=" << j_DataEra << ", trig=" << trig << ")" << endl;
  exit(ENODATA);
  return -1.;

}

bool Event::IsPDForTrigger(TString trig, TString PD){

  if(j_DataYear==2016){
    
    //https://docs.google.com/spreadsheets/d/1bII_92pCrgk20A9FMIIHsOsYYj3f-lLjsoRkP_ZNQW4/edit#gid=1113127300
    if(PD=="DoubleEG"){
      if(trig=="HLT_DoubleEle33_CaloIdL_GsfTrkIdVL_MW_v") return true;
      if(trig=="HLT_DoubleEle33_CaloIdL_MW_v") return true;
      if(trig=="HLT_DoubleEle33_CaloIdL_v") return true;
      if(trig=="HLT_DoubleEle37_Ele27_CaloIdL_GsfTrkIdVL_v") return true;
      if(trig=="HLT_DoubleEle8_CaloIdM_TrackIdM_Mass8_PFHT300_v") return true;
      if(trig=="HLT_DoublePhoton60_v") return true;
      if(trig=="HLT_DoublePhoton85_v") return true;
      if(trig=="HLT_ECALHT800_v") return true;
      if(trig=="HLT_Ele10_CaloIdM_TrackIdM_CentralPFJet30_BTagCSV_p13_v") return true;
      if(trig=="HLT_Ele12_CaloIdL_TrackIdL_IsoVL_PFJet30_v") return true;
      if(trig=="HLT_Ele12_CaloIdL_TrackIdL_IsoVL_v") return true;
      if(trig=="HLT_Ele12_CaloIdM_TrackIdM_PFJet30_v") return true;
      if(trig=="HLT_Ele16_Ele12_Ele8_CaloIdL_TrackIdL_v") return true;
      if(trig=="HLT_Ele17_CaloIdL_GsfTrkIdVL_v") return true;
      if(trig=="HLT_Ele17_CaloIdL_TrackIdL_IsoVL_PFJet30_v") return true;
      if(trig=="HLT_Ele17_CaloIdL_TrackIdL_IsoVL_v") return true;
      if(trig=="HLT_Ele17_CaloIdM_TrackIdM_PFJet30_v") return true;
      if(trig=="HLT_Ele17_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v") return true;
      if(trig=="HLT_Ele17_Ele12_CaloIdL_TrackIdL_IsoVL_v") return true;
      if(trig=="HLT_Ele23_CaloIdL_TrackIdL_IsoVL_PFJet30_v") return true;
      if(trig=="HLT_Ele23_CaloIdL_TrackIdL_IsoVL_v") return true;
      if(trig=="HLT_Ele23_CaloIdM_TrackIdM_PFJet30_v") return true;
      if(trig=="HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_L1JetTauSeeded_v") return true;
      if(trig=="HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v") return true;
      if(trig=="HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_v") return true;
      if(trig=="HLT_Ele27_HighEta_Ele20_Mass55_v") return true;
      if(trig=="HLT_Ele8_CaloIdL_TrackIdL_IsoVL_PFJet30_v") return true;
      if(trig=="HLT_Ele8_CaloIdM_TrackIdM_PFJet30_v") return true;}
    else   if(PD=="SingleElectron"){
      if(trig=="HLT_Ele105_CaloIdVT_GsfTrkIdT_v") return true;
      if(trig=="HLT_Ele115_CaloIdVT_GsfTrkIdT_v") return true;
      if(trig=="HLT_Ele145_CaloIdVT_GsfTrkIdT_v") return true;
      if(trig=="HLT_Ele15_IsoVVVL_BTagCSV_p067_PFHT400_v") return true;
      if(trig=="HLT_Ele15_IsoVVVL_PFHT400_PFMET50_v") return true;
      if(trig=="HLT_Ele15_IsoVVVL_PFHT400_v") return true;
      if(trig=="HLT_Ele15_IsoVVVL_PFHT600_v") return true;
      if(trig=="HLT_Ele200_CaloIdVT_GsfTrkIdT_v") return true;
      if(trig=="HLT_Ele20_eta2p1_WPLoose_Gsf_LooseIsoPFTau28_v") return true;
      if(trig=="HLT_Ele22_eta2p1_WPLoose_Gsf_LooseIsoPFTau29_v") return true;
      if(trig=="HLT_Ele22_eta2p1_WPLoose_Gsf_v") return true;
      if(trig=="HLT_Ele24_eta2p1_WPLoose_Gsf_LooseIsoPFTau30_v") return true;
      if(trig=="HLT_Ele250_CaloIdVT_GsfTrkIdT_v") return true;
      if(trig=="HLT_Ele25_WPTight_Gsf_v") return true;
      if(trig=="HLT_Ele25_eta2p1_WPTight_Gsf_v") return true;
      if(trig=="HLT_Ele27_WPLoose_Gsf_WHbbBoost_v") return true;
      if(trig=="HLT_Ele27_WPTight_Gsf_L1JetTauSeeded_v") return true;
      if(trig=="HLT_Ele27_WPTight_Gsf_v") return true;
      if(trig=="HLT_Ele27_eta2p1_WPLoose_Gsf_HT200_v") return true;
      if(trig=="HLT_Ele27_eta2p1_WPLoose_Gsf_v") return true;
      if(trig=="HLT_Ele27_eta2p1_WPTight_Gsf_v") return true;
      if(trig=="HLT_Ele300_CaloIdVT_GsfTrkIdT_v") return true;
      if(trig=="HLT_Ele30_WPTight_Gsf_v") return true;
      if(trig=="HLT_Ele30_eta2p1_WPTight_Gsf_v") return true;
      if(trig=="HLT_Ele32_WPTight_Gsf_v") return true;
      if(trig=="HLT_Ele32_eta2p1_WPTight_Gsf_v") return true;
      if(trig=="HLT_Ele36_eta2p1_WPLoose_Gsf_LooseIsoPFTau20_SingleL1_v") return true;
      if(trig=="HLT_Ele45_CaloIdVT_GsfTrkIdT_PFJet200_PFJet50_v") return true;
      if(trig=="HLT_Ele50_CaloIdVT_GsfTrkIdT_PFJet165_v") return true;
      if(trig=="HLT_Ele50_IsoVVVL_PFHT400_v") return true;
    }
    else   if(PD=="SinglePhoton"){
      if(trig=="HLT_Photon120_R9Id90_HE10_Iso40_EBOnly_PFMET40_v") return true;
      if(trig=="HLT_Photon120_R9Id90_HE10_Iso40_EBOnly_VBF_v") return true;
      if(trig=="HLT_Photon120_R9Id90_HE10_IsoM_v") return true;
      if(trig=="HLT_Photon120_v") return true;
      if(trig=="HLT_Photon135_PFMET100_v") return true;
      if(trig=="HLT_Photon165_HE10_v") return true;
      if(trig=="HLT_Photon165_R9Id90_HE10_IsoM_v") return true;
      if(trig=="HLT_Photon175_v") return true;
      if(trig=="HLT_Photon22_R9Id90_HE10_Iso40_EBOnly_PFMET40_v") return true;
      if(trig=="HLT_Photon22_R9Id90_HE10_Iso40_EBOnly_VBF_v") return true;
      if(trig=="HLT_Photon22_R9Id90_HE10_IsoM_v") return true;
      if(trig=="HLT_Photon22_v") return true;
      if(trig=="HLT_Photon250_NoHE_v") return true;
      if(trig=="HLT_Photon300_NoHE_v") return true;
      if(trig=="HLT_Photon30_R9Id90_HE10_IsoM_v") return true;
      if(trig=="HLT_Photon30_v") return true;
      if(trig=="HLT_Photon36_R9Id90_HE10_Iso40_EBOnly_PFMET40_v") return true;
      if(trig=="HLT_Photon36_R9Id90_HE10_Iso40_EBOnly_VBF_v") return true;
      if(trig=="HLT_Photon36_R9Id90_HE10_IsoM_v") return true;
      if(trig=="HLT_Photon36_v") return true;
      if(trig=="HLT_Photon500_v") return true;
      if(trig=="HLT_Photon50_R9Id90_HE10_Iso40_EBOnly_PFMET40_v") return true;
      if(trig=="HLT_Photon50_R9Id90_HE10_Iso40_EBOnly_VBF_v") return true;
      if(trig=="HLT_Photon50_R9Id90_HE10_IsoM_v") return true;
      if(trig=="HLT_Photon50_v") return true;
      if(trig=="HLT_Photon600_v") return true;
      if(trig=="HLT_Photon75_R9Id90_HE10_Iso40_EBOnly_PFMET40_v") return true;
      if(trig=="HLT_Photon75_R9Id90_HE10_Iso40_EBOnly_VBF_v") return true;
      if(trig=="HLT_Photon75_R9Id90_HE10_IsoM_v") return true;
      if(trig=="HLT_Photon75_v") return true;
      if(trig=="HLT_Photon90_CaloIdL_PFHT600_v") return true;
      if(trig=="HLT_Photon90_R9Id90_HE10_Iso40_EBOnly_PFMET40_v") return true;
      if(trig=="HLT_Photon90_R9Id90_HE10_Iso40_EBOnly_VBF_v") return true;
      if(trig=="HLT_Photon90_R9Id90_HE10_IsoM_v") return true;
      if(trig=="HLT_Photon90_v") return true;
    }
    
    else   if(PD=="DoubleMuon"){
      if(trig=="HLT_DoubleMu0_v") return true;
      if(trig=="HLT_DoubleMu18NoFiltersNoVtx_v") return true;
      if(trig=="HLT_DoubleMu23NoFiltersNoVtxDisplaced_v") return true;
      if(trig=="HLT_DoubleMu28NoFiltersNoVtxDisplaced_v") return true;
      if(trig=="HLT_DoubleMu33NoFiltersNoVtx_v") return true;
      if(trig=="HLT_DoubleMu38NoFiltersNoVtx_v") return true;
      if(trig=="HLT_DoubleMu8_Mass8_PFHT300_v") return true;
      if(trig=="HLT_L2DoubleMu23_NoVertex_v") return true;
      if(trig=="HLT_L2DoubleMu28_NoVertex_2Cha_Angle2p5_Mass10_v") return true;
      if(trig=="HLT_L2DoubleMu38_NoVertex_2Cha_Angle2p5_Mass10_v") return true;
      if(trig=="HLT_Mu10_CentralPFJet30_BTagCSV_p13_v") return true;
      if(trig=="HLT_Mu17_Mu8_DZ_v") return true;
      if(trig=="HLT_Mu17_Mu8_SameSign_DZ_v") return true;
      if(trig=="HLT_Mu17_Mu8_SameSign_v") return true;
      if(trig=="HLT_Mu17_Mu8_v") return true;
      if(trig=="HLT_Mu17_TkMu8_DZ_v") return true;
      if(trig=="HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v") return true;
      if(trig=="HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_v") return true;
      if(trig=="HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v") return true;
      if(trig=="HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_v") return true;
      if(trig=="HLT_Mu17_TrkIsoVVL_v") return true;
      if(trig=="HLT_Mu17_v") return true;
      if(trig=="HLT_Mu20_Mu10_DZ_v") return true;
      if(trig=="HLT_Mu20_Mu10_SameSign_DZ_v") return true;
      if(trig=="HLT_Mu20_Mu10_SameSign_v") return true;
      if(trig=="HLT_Mu20_Mu10_v") return true;
      if(trig=="HLT_Mu27_TkMu8_v") return true;
      if(trig=="HLT_Mu30_TkMu11_v") return true;
      if(trig=="HLT_Mu3_PFJet40_v") return true;
      if(trig=="HLT_Mu40_TkMu11_v") return true;
      if(trig=="HLT_Mu8_TrkIsoVVL_v") return true;
      if(trig=="HLT_Mu8_v") return true;
      if(trig=="HLT_TkMu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v") return true;
      if(trig=="HLT_TkMu17_TrkIsoVVL_TkMu8_TrkIsoVVL_v") return true;
      if(trig=="HLT_TripleMu_12_10_5_v") return true;
      if(trig=="HLT_TripleMu_5_3_3_DZ_Mass3p8_v") return true;
      if(trig=="HLT_TrkMu15_DoubleTrkMu5NoFiltersNoVtx_v") return true;
      if(trig=="HLT_TrkMu17_DoubleTrkMu8NoFiltersNoVtx_v") return true;
    }
    else   if(PD=="MuonEG"){
      if(trig=="HLT_DiMu9_Ele9_CaloIdL_TrackIdL_v") return true;
      if(trig=="HLT_Mu12_Photon25_CaloIdL_L1ISO_v") return true;
      if(trig=="HLT_Mu12_Photon25_CaloIdL_L1OR_v") return true;
      if(trig=="HLT_Mu12_Photon25_CaloIdL_v") return true;
      if(trig=="HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_v") return true;
      if(trig=="HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_v") return true;
      if(trig=="HLT_Mu17_Photon30_CaloIdL_L1ISO_v") return true;
      if(trig=="HLT_Mu17_Photon35_CaloIdL_L1ISO_v") return true;
      if(trig=="HLT_Mu17_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v") return true;
      if(trig=="HLT_Mu23NoFiltersNoVtx_Photon23_CaloIdL_v") return true;
      if(trig=="HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v") return true;
      if(trig=="HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v") return true;
      if(trig=="HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL_DZ_v") return true;
      if(trig=="HLT_Mu27_Ele37_CaloIdL_GsfTrkIdVL_v") return true;
      if(trig=="HLT_Mu28NoFiltersNoVtxDisplaced_Photon28_CaloIdL_v") return true;
      if(trig=="HLT_Mu33NoFiltersNoVtxDisplaced_Photon33_CaloIdL_v") return true;
      if(trig=="HLT_Mu33_Ele33_CaloIdL_GsfTrkIdVL_v") return true;
      if(trig=="HLT_Mu37_Ele27_CaloIdL_GsfTrkIdVL_v") return true;
      if(trig=="HLT_Mu38NoFiltersNoVtx_Photon38_CaloIdL_v") return true;
      if(trig=="HLT_Mu42NoFiltersNoVtx_Photon42_CaloIdL_v") return true;
      if(trig=="HLT_Mu8_DiEle12_CaloIdL_TrackIdL_v") return true;
      if(trig=="HLT_Mu8_Ele8_CaloIdM_TrackIdM_Mass8_PFHT300_v") return true;
      if(trig=="HLT_Mu8_TrkIsoVVL_Ele17_CaloIdL_TrackIdL_IsoVL_v") return true;
      if(trig=="HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_v") return true;
      
    }
    
    else   if(PD=="SingleMuon"){
      if(trig=="HLT_DoubleIsoMu17_eta2p1_noDzCut_v") return true;
      if(trig=="HLT_IsoMu16_eta2p1_MET30_LooseIsoPFTau50_Trk30_eta2p1_v") return true;
      if(trig=="HLT_IsoMu16_eta2p1_MET30_v") return true;
      if(trig=="HLT_IsoMu19_eta2p1_LooseIsoPFTau20_SingleL1_v") return true;
      if(trig=="HLT_IsoMu19_eta2p1_LooseIsoPFTau20_v") return true;
      if(trig=="HLT_IsoMu19_eta2p1_MediumIsoPFTau32_Trk1_eta2p1_Reg_v") return true;
      if(trig=="HLT_IsoMu20_v") return true;
      if(trig=="HLT_IsoMu21_eta2p1_LooseIsoPFTau20_SingleL1_v") return true;
      if(trig=="HLT_IsoMu21_eta2p1_LooseIsoPFTau50_Trk30_eta2p1_SingleL1_v") return true;
      if(trig=="HLT_IsoMu21_eta2p1_MediumIsoPFTau32_Trk1_eta2p1_Reg_v") return true;
      if(trig=="HLT_IsoMu22_eta2p1_v") return true;
      if(trig=="HLT_IsoMu22_v") return true;
      if(trig=="HLT_IsoMu24_eta2p1_v") return true;
      if(trig=="HLT_IsoMu24_v") return true;
      if(trig=="HLT_IsoMu27_v") return true;
      if(trig=="HLT_IsoTkMu20_v") return true;
      if(trig=="HLT_IsoTkMu22_eta2p1_v") return true;
      if(trig=="HLT_IsoTkMu22_v") return true;
      if(trig=="HLT_IsoTkMu24_eta2p1_v") return true;
      if(trig=="HLT_IsoTkMu24_v") return true;
      if(trig=="HLT_IsoTkMu27_v") return true;
      if(trig=="HLT_L1SingleMu18_v") return true;
      if(trig=="HLT_L2Mu10_v") return true;
      if(trig=="HLT_Mu10_TrkIsoVVL_DiPFJet40_DEta3p5_MJJ750_HTT350_PFMETNoMu60_v") return true;
      if(trig=="HLT_Mu15_IsoVVVL_BTagCSV_p067_PFHT400_v") return true;
      if(trig=="HLT_Mu15_IsoVVVL_PFHT400_PFMET50_v") return true;
      if(trig=="HLT_Mu15_IsoVVVL_PFHT400_v") return true;
      if(trig=="HLT_Mu15_IsoVVVL_PFHT600_v") return true;
      if(trig=="HLT_Mu20_v") return true;
      if(trig=="HLT_Mu24_eta2p1_v") return true;
      if(trig=="HLT_Mu27_v") return true;
      if(trig=="HLT_Mu28NoFiltersNoVtx_CentralCaloJet40_v") return true;
      if(trig=="HLT_Mu28NoFiltersNoVtx_DisplacedJet40_Loose_v") return true;
      if(trig=="HLT_Mu300_v") return true;
      if(trig=="HLT_Mu30_eta2p1_PFJet150_PFJet50_v") return true;
      if(trig=="HLT_Mu350_v") return true;
      if(trig=="HLT_Mu38NoFiltersNoVtxDisplaced_DisplacedJet60_Loose_v") return true;
      if(trig=="HLT_Mu38NoFiltersNoVtxDisplaced_DisplacedJet60_Tight_v") return true;
      if(trig=="HLT_Mu38NoFiltersNoVtx_DisplacedJet60_Loose_v") return true;
      if(trig=="HLT_Mu40_eta2p1_PFJet200_PFJet50_v") return true;
      if(trig=="HLT_Mu45_eta2p1_v") return true;
      if(trig=="HLT_Mu50_IsoVVVL_PFHT400_v") return true;
      if(trig=="HLT_Mu50_v") return true;
      if(trig=="HLT_Mu55_v") return true;
      if(trig=="HLT_Mu8_TrkIsoVVL_DiPFJet40_DEta3p5_MJJ750_HTT300_PFMETNoMu60_v") return true;
      if(trig=="HLT_TkMu17_v") return true;
      if(trig=="HLT_TkMu20_v") return true;
      if(trig=="HLT_TkMu24_eta2p1_v") return true;
      if(trig=="HLT_TkMu27_v") return true;
      if(trig=="HLT_TkMu50_v") return true;
    }
    return false;
  }
  else if(j_DataYear==2017){

    //https://docs.google.com/spreadsheets/d/1SqSKATiHcZdSB-t7rMb0SRSUL4Ot1jr2TExjnMrDUpA/edit#gid=0
    if(PD=="DoubleEG"){

      if(trig=="HLT_DiEle27_WPTightCaloOnly_L1DoubleEG_v")  return true;
      if(trig=="HLT_DiSC30_18_EIso_AND_HE_Mass70_v")  return true;
      if(trig=="HLT_Diphoton30EB_18EB_R9Id_OR_IsoCaloId_AND_HE_R9Id_NoPixelVeto_Mass55_v")  return true;
      if(trig=="HLT_Diphoton30EB_18EB_R9Id_OR_IsoCaloId_AND_HE_R9Id_PixelVeto_Mass55_v")  return true;
      if(trig=="HLT_Diphoton30PV_18PV_R9Id_AND_IsoCaloId_AND_HE_R9Id_NoPixelVeto_Mass55_v")  return true;
      if(trig=="HLT_Diphoton30PV_18PV_R9Id_AND_IsoCaloId_AND_HE_R9Id_PixelVeto_Mass55_v")  return true;
      if(trig=="HLT_Diphoton30_18_PVrealAND_R9Id_AND_IsoCaloId_AND_HE_R9Id_NoPixelVeto_Mass55_v")  return true;
      if(trig=="HLT_Diphoton30_18_PVrealAND_R9Id_AND_IsoCaloId_AND_HE_R9Id_PixelVeto_Mass55_v")  return true;
      if(trig=="HLT_Diphoton30_22_R9Id_OR_IsoCaloId_AND_HE_R9Id_Mass90_v")  return true;
      if(trig=="HLT_Diphoton30_22_R9Id_OR_IsoCaloId_AND_HE_R9Id_Mass95_v")  return true;
      if(trig=="HLT_DoubleEle25_CaloIdL_MW_v")  return true;
      if(trig=="HLT_DoubleEle27_CaloIdL_MW_v")  return true;
      if(trig=="HLT_DoubleEle33_CaloIdL_MW_v")  return true;
      if(trig=="HLT_DoubleEle8_CaloIdM_TrackIdM_Mass8_DZ_PFHT350_v")  return true;
      if(trig=="HLT_DoubleEle8_CaloIdM_TrackIdM_Mass8_PFHT350_v")  return true;
      if(trig=="HLT_DoublePhoton33_CaloIdL_v")  return true;
      if(trig=="HLT_DoublePhoton70_v")  return true;
      if(trig=="HLT_DoublePhoton85_v")  return true;
      if(trig=="HLT_ECALHT800_v")  return true;
      if(trig=="HLT_Ele15_Ele8_CaloIdL_TrackIdL_IsoVL_v")  return true;
      if(trig=="HLT_Ele16_Ele12_Ele8_CaloIdL_TrackIdL_v")  return true;
      if(trig=="HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v")  return true;
      if(trig=="HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_v")  return true;
      if(trig=="HLT_Ele27_Ele37_CaloIdL_MW_v")  return true;
      if(trig=="HLT_Ele28_HighEta_SC20_Mass55_v")  return true;
      if(trig=="HLT_TriplePhoton_20_20_20_CaloIdLV2_R9IdVL_v")  return true;
      if(trig=="HLT_TriplePhoton_20_20_20_CaloIdLV2_v")  return true;
      if(trig=="HLT_TriplePhoton_30_30_10_CaloIdLV2_R9IdVL_v")  return true;
      if(trig=="HLT_TriplePhoton_30_30_10_CaloIdLV2_v")  return true;
      if(trig=="HLT_TriplePhoton_35_35_5_CaloIdLV2_R9IdVL_v")  return true;
    }
    
    if(PD=="SingleElectron"){
      if(trig=="HLT_Ele115_CaloIdVT_GsfTrkIdT_v")  return true;
      if(trig=="HLT_Ele12_CaloIdL_TrackIdL_IsoVL_PFJet30_v")  return true;
      if(trig=="HLT_Ele135_CaloIdVT_GsfTrkIdT_v")  return true;
      if(trig=="HLT_Ele145_CaloIdVT_GsfTrkIdT_v")  return true;
      if(trig=="HLT_Ele15_CaloIdL_TrackIdL_IsoVL_PFJet30_v")  return true;
      if(trig=="HLT_Ele15_IsoVVVL_PFHT450_CaloBTagCSV_4p5_v")  return true;
      if(trig=="HLT_Ele15_IsoVVVL_PFHT450_PFMET50_v")  return true;
      if(trig=="HLT_Ele15_IsoVVVL_PFHT450_v")  return true;
      if(trig=="HLT_Ele15_IsoVVVL_PFHT600_v")  return true;
      if(trig=="HLT_Ele15_WPLoose_Gsf_v")  return true;
      if(trig=="HLT_Ele17_CaloIdM_TrackIdM_PFJet30_v")  return true;
      if(trig=="HLT_Ele17_WPLoose_Gsf_v")  return true;
      if(trig=="HLT_Ele200_CaloIdVT_GsfTrkIdT_v")  return true;
      if(trig=="HLT_Ele20_WPLoose_Gsf_v")  return true;
      if(trig=="HLT_Ele20_WPTight_Gsf_v")  return true;
      if(trig=="HLT_Ele20_eta2p1_WPLoose_Gsf_v")  return true;
      if(trig=="HLT_Ele23_CaloIdL_TrackIdL_IsoVL_PFJet30_v")  return true;
      if(trig=="HLT_Ele23_CaloIdM_TrackIdM_PFJet30_v")  return true;
      if(trig=="HLT_Ele24_eta2p1_WPTight_Gsf_LooseChargedIsoPFTau30_eta2p1_CrossL1_v")  return true;
      if(trig=="HLT_Ele24_eta2p1_WPTight_Gsf_LooseChargedIsoPFTau30_eta2p1_TightID_CrossL1_v")  return true;
      if(trig=="HLT_Ele24_eta2p1_WPTight_Gsf_MediumChargedIsoPFTau30_eta2p1_CrossL1_v")  return true;
      if(trig=="HLT_Ele24_eta2p1_WPTight_Gsf_MediumChargedIsoPFTau30_eta2p1_TightID_CrossL1_v")  return true;
      if(trig=="HLT_Ele24_eta2p1_WPTight_Gsf_TightChargedIsoPFTau30_eta2p1_CrossL1_v")  return true;
      if(trig=="HLT_Ele24_eta2p1_WPTight_Gsf_TightChargedIsoPFTau30_eta2p1_TightID_CrossL1_v")  return true;
      if(trig=="HLT_Ele250_CaloIdVT_GsfTrkIdT_v")  return true;
      if(trig=="HLT_Ele27_WPTight_Gsf_v")  return true;
      if(trig=="HLT_Ele28_eta2p1_WPTight_Gsf_HT150_v")  return true;
      if(trig=="HLT_Ele300_CaloIdVT_GsfTrkIdT_v")  return true;
      if(trig=="HLT_Ele30_eta2p1_WPTight_Gsf_CentralPFJet35_EleCleaned_v")  return true;
      if(trig=="HLT_Ele32_WPTight_Gsf_L1DoubleEG_v")  return true;
      if(trig=="HLT_Ele32_WPTight_Gsf_v")  return true;
      if(trig=="HLT_Ele35_WPTight_Gsf_L1EGMT_v")  return true;
      if(trig=="HLT_Ele35_WPTight_Gsf_v")  return true;
      if(trig=="HLT_Ele38_WPTight_Gsf_v")  return true;
      if(trig=="HLT_Ele40_WPTight_Gsf_v")  return true;
      if(trig=="HLT_Ele50_CaloIdVT_GsfTrkIdT_PFJet165_v")  return true;
      if(trig=="HLT_Ele50_IsoVVVL_PFHT450_v")  return true;
      if(trig=="HLT_Ele8_CaloIdL_TrackIdL_IsoVL_PFJet30_v")  return true;
      if(trig=="HLT_Ele8_CaloIdM_TrackIdM_PFJet30_v")  return true;
    }
    if(PD=="SinglePhoton"){
      if(trig=="HLT_Photon120_R9Id90_HE10_IsoM_v")  return true;
      if(trig=="HLT_Photon120_v")  return true;
      if(trig=="HLT_Photon150_v")  return true;
      if(trig=="HLT_Photon165_R9Id90_HE10_IsoM_v")  return true;
      if(trig=="HLT_Photon175_v")  return true;
      if(trig=="HLT_Photon200_v")  return true;
      if(trig=="HLT_Photon20_HoverELoose_v")  return true;
      if(trig=="HLT_Photon20_v")  return true;
      if(trig=="HLT_Photon25_v")  return true;
      if(trig=="HLT_Photon300_NoHE_v")  return true;
      if(trig=="HLT_Photon30_HoverELoose_v")  return true;
      if(trig=="HLT_Photon33_v")  return true;
      if(trig=="HLT_Photon40_HoverELoose_v")  return true;
      if(trig=="HLT_Photon50_HoverELoose_v")  return true;
      if(trig=="HLT_Photon50_R9Id90_HE10_IsoM_EBOnly_PFJetsMJJ300DEta3_PFMET50_v")  return true;
      if(trig=="HLT_Photon50_R9Id90_HE10_IsoM_v")  return true;
      if(trig=="HLT_Photon50_v")  return true;
      if(trig=="HLT_Photon60_HoverELoose_v")  return true;
      if(trig=="HLT_Photon60_R9Id90_CaloIdL_IsoL_DisplacedIdL_PFHT350MinPFJet15_v")  return true;
      if(trig=="HLT_Photon60_R9Id90_CaloIdL_IsoL_DisplacedIdL_v")  return true;
      if(trig=="HLT_Photon60_R9Id90_CaloIdL_IsoL_v")  return true;
      if(trig=="HLT_Photon75_R9Id90_HE10_IsoM_EBOnly_PFJetsMJJ300DEta3_v")  return true;
      if(trig=="HLT_Photon75_R9Id90_HE10_IsoM_EBOnly_PFJetsMJJ600DEta3_v")  return true;
      if(trig=="HLT_Photon75_R9Id90_HE10_IsoM_v")  return true;
      if(trig=="HLT_Photon75_v")  return true;
      if(trig=="HLT_Photon90_R9Id90_HE10_IsoM_v")  return true;
      if(trig=="HLT_Photon90_v")  return true;
    }
    if(PD=="DoubleMuon"){
      if(trig=="HLT_DoubleL2Mu50_v")  return true;
      if(trig=="HLT_DoubleMu3_DCA_PFMET50_PFMHT60_v")  return true;
      if(trig=="HLT_DoubleMu3_DZ_PFMET50_PFMHT60_v")  return true;
      if(trig=="HLT_DoubleMu3_DZ_PFMET70_PFMHT70_v")  return true;
      if(trig=="HLT_DoubleMu3_DZ_PFMET90_PFMHT90_v")  return true;
      if(trig=="HLT_DoubleMu43NoFiltersNoVtx_v")  return true;
      if(trig=="HLT_DoubleMu48NoFiltersNoVtx_v")  return true;
      if(trig=="HLT_DoubleMu4_Mass8_DZ_PFHT350_v")  return true;
      if(trig=="HLT_DoubleMu8_Mass8_PFHT350_v")  return true;
      if(trig=="HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8_v")  return true;
      if(trig=="HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8_v")  return true;
      if(trig=="HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v")  return true;
      if(trig=="HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_v")  return true;
      if(trig=="HLT_Mu17_TrkIsoVVL_v")  return true;
      if(trig=="HLT_Mu17_v")  return true;
      if(trig=="HLT_Mu18_Mu9_DZ_v")  return true;
      if(trig=="HLT_Mu18_Mu9_SameSign_DZ_v")  return true;
      if(trig=="HLT_Mu18_Mu9_SameSign_v")  return true;
      if(trig=="HLT_Mu18_Mu9_v")  return true;
      if(trig=="HLT_Mu19_TrkIsoVVL_Mu9_TrkIsoVVL_DZ_Mass3p8_v")  return true;
      if(trig=="HLT_Mu19_TrkIsoVVL_Mu9_TrkIsoVVL_DZ_Mass8_v")  return true;
      if(trig=="HLT_Mu19_TrkIsoVVL_Mu9_TrkIsoVVL_DZ_v")  return true;
      if(trig=="HLT_Mu19_TrkIsoVVL_Mu9_TrkIsoVVL_v")  return true;
      if(trig=="HLT_Mu19_TrkIsoVVL_v")  return true;
      if(trig=="HLT_Mu19_v")  return true;
      if(trig=="HLT_Mu20_Mu10_DZ_v")  return true;
      if(trig=="HLT_Mu20_Mu10_SameSign_DZ_v")  return true;
      if(trig=="HLT_Mu20_Mu10_SameSign_v")  return true;
      if(trig=="HLT_Mu20_Mu10_v")  return true;
      if(trig=="HLT_Mu23_Mu12_DZ_v")  return true;
      if(trig=="HLT_Mu23_Mu12_SameSign_DZ_v")  return true;
      if(trig=="HLT_Mu23_Mu12_SameSign_v")  return true;
      if(trig=="HLT_Mu23_Mu12_v")  return true;
      if(trig=="HLT_Mu37_TkMu27_v")  return true;
      if(trig=="HLT_Mu8_TrkIsoVVL_v")  return true;
      if(trig=="HLT_Mu8_v")  return true;
      if(trig=="HLT_TripleMu_10_5_5_DZ_v")  return true;
      if(trig=="HLT_TripleMu_12_10_5_v")  return true;
      if(trig=="HLT_TripleMu_5_3_3_Mass3p8to60_DCA_v")  return true;
      if(trig=="HLT_TripleMu_5_3_3_Mass3p8to60_DZ_v")  return true;
      if(trig=="HLT_TrkMu12_DoubleTrkMu5NoFiltersNoVtx_v")  return true;
      if(trig=="HLT_TrkMu16_DoubleTrkMu6NoFiltersNoVtx_v")  return true;
      if(trig=="HLT_TrkMu17_DoubleTrkMu8NoFiltersNoVtx_v")  return true;
    }
    
    if(PD=="MuonEG"){
      if(trig=="HLT_DiMu9_Ele9_CaloIdL_TrackIdL_DZ_v")  return true;
      if(trig=="HLT_DiMu9_Ele9_CaloIdL_TrackIdL_v")  return true;
      if(trig=="HLT_DoubleMu20_7_Mass0to30_L1_DM4EG_v")  return true;
      if(trig=="HLT_DoubleMu20_7_Mass0to30_L1_DM4_v")  return true;
      if(trig=="HLT_DoubleMu20_7_Mass0to30_Photon23_v")  return true;
      if(trig=="HLT_Mu12_DoublePhoton20_v")  return true;
      if(trig=="HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_v")  return true;
      if(trig=="HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_v")  return true;
      if(trig=="HLT_Mu17_Photon30_IsoCaloId_v")  return true;
      if(trig=="HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v")  return true;
      if(trig=="HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v")  return true;
      if(trig=="HLT_Mu27_Ele37_CaloIdL_MW_v")  return true;
      if(trig=="HLT_Mu37_Ele27_CaloIdL_MW_v")  return true;
      if(trig=="HLT_Mu43NoFiltersNoVtx_Photon43_CaloIdL_v")  return true;
      if(trig=="HLT_Mu48NoFiltersNoVtx_Photon48_CaloIdL_v")  return true;
      if(trig=="HLT_Mu8_DiEle12_CaloIdL_TrackIdL_DZ_v")  return true;
      if(trig=="HLT_Mu8_DiEle12_CaloIdL_TrackIdL_v")  return true;
      if(trig=="HLT_Mu8_Ele8_CaloIdM_TrackIdM_Mass8_PFHT350_DZ_v")  return true;
      if(trig=="HLT_Mu8_Ele8_CaloIdM_TrackIdM_Mass8_PFHT350_v")  return true;
      if(trig=="HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_v")  return true;
      if(trig=="HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_v")  return true;
    }
    if(PD=="SingleMuon"){
      if(trig=="HLT_IsoMu20_eta2p1_LooseChargedIsoPFTau27_eta2p1_CrossL1_v")  return true;
      if(trig=="HLT_IsoMu20_eta2p1_LooseChargedIsoPFTau27_eta2p1_TightID_CrossL1_v")  return true;
      if(trig=="HLT_IsoMu20_eta2p1_MediumChargedIsoPFTau27_eta2p1_CrossL1_v")  return true;
      if(trig=="HLT_IsoMu20_eta2p1_MediumChargedIsoPFTau27_eta2p1_TightID_CrossL1_v")  return true;
      if(trig=="HLT_IsoMu20_eta2p1_TightChargedIsoPFTau27_eta2p1_CrossL1_v")  return true;
      if(trig=="HLT_IsoMu20_eta2p1_TightChargedIsoPFTau27_eta2p1_TightID_CrossL1_v")  return true;
      if(trig=="HLT_IsoMu20_v")  return true;
      if(trig=="HLT_IsoMu24_eta2p1_LooseChargedIsoPFTau20_SingleL1_v")  return true;
      if(trig=="HLT_IsoMu24_eta2p1_LooseChargedIsoPFTau20_TightID_SingleL1_v")  return true;
      if(trig=="HLT_IsoMu24_eta2p1_LooseChargedIsoPFTau35_Trk1_TightID_eta2p1_Reg_CrossL1_v")  return true;
      if(trig=="HLT_IsoMu24_eta2p1_LooseChargedIsoPFTau35_Trk1_eta2p1_Reg_CrossL1_v")  return true;
      if(trig=="HLT_IsoMu24_eta2p1_MediumChargedIsoPFTau20_SingleL1_v")  return true;
      if(trig=="HLT_IsoMu24_eta2p1_MediumChargedIsoPFTau20_TightID_SingleL1_v")  return true;
      if(trig=="HLT_IsoMu24_eta2p1_MediumChargedIsoPFTau35_Trk1_TightID_eta2p1_Reg_CrossL1_v")  return true;
      if(trig=="HLT_IsoMu24_eta2p1_MediumChargedIsoPFTau35_Trk1_eta2p1_Reg_CrossL1_v")  return true;
      if(trig=="HLT_IsoMu24_eta2p1_TightChargedIsoPFTau20_SingleL1_v")  return true;
      if(trig=="HLT_IsoMu24_eta2p1_TightChargedIsoPFTau20_TightID_SingleL1_v")  return true;
      if(trig=="HLT_IsoMu24_eta2p1_TightChargedIsoPFTau35_Trk1_TightID_eta2p1_Reg_CrossL1_v")  return true;
      if(trig=="HLT_IsoMu24_eta2p1_TightChargedIsoPFTau35_Trk1_eta2p1_Reg_CrossL1_v")  return true;
      if(trig=="HLT_IsoMu24_eta2p1_v")  return true;
      if(trig=="HLT_IsoMu24_v")  return true;
      if(trig=="HLT_IsoMu27_v")  return true;
      if(trig=="HLT_IsoMu30_v")  return true;
      if(trig=="HLT_L1SingleMu18_v")  return true;
      if(trig=="HLT_L1SingleMu25_v")  return true;
      if(trig=="HLT_L1_DoubleJet30_Mass_Min400_Mu10_v")  return true;
      if(trig=="HLT_L2Mu10_v")  return true;
      if(trig=="HLT_L2Mu50_v")  return true;
      if(trig=="HLT_Mu10_TrkIsoVVL_DiPFJet40_DEta3p5_MJJ750_HTT350_PFMETNoMu60_v")  return true;
      if(trig=="HLT_Mu12_v")  return true;
      if(trig=="HLT_Mu15_IsoVVVL_PFHT450_CaloBTagCSV_4p5_v")  return true;
      if(trig=="HLT_Mu15_IsoVVVL_PFHT450_PFMET50_v")  return true;
      if(trig=="HLT_Mu15_IsoVVVL_PFHT450_v")  return true;
      if(trig=="HLT_Mu15_IsoVVVL_PFHT600_v")  return true;
      if(trig=="HLT_Mu15_v")  return true;
      if(trig=="HLT_Mu20_v")  return true;
      if(trig=="HLT_Mu27_v")  return true;
      if(trig=="HLT_Mu3_PFJet40_v")  return true;
      if(trig=="HLT_Mu50_IsoVVVL_PFHT450_v")  return true;
      if(trig=="HLT_Mu50_v")  return true;
      if(trig=="HLT_Mu55_v")  return true;
      if(trig=="HLT_Mu8_TrkIsoVVL_DiPFJet40_DEta3p5_MJJ750_HTT300_PFMETNoMu60_v")  return true;
      if(trig=="HLT_OldMu100_v")  return true;
      if(trig=="HLT_TkMu100_v")  return true;
    }
    return false;
  }
  else if(j_DataYear==2018){
    //https://docs.google.com/spreadsheets/d/1D_og1_J6Hp4uALUg-R4Hkq3CF0VN6IK5komHPHv5R-o/edit#gid=585230569

    if(PD=="SingleMuon"){    
      if(trig=="HLT_IsoMu20_eta2p1_LooseChargedIsoPFTauHPS27_eta2p1_CrossL1_v") return true;
      if(trig=="HLT_IsoMu20_eta2p1_LooseChargedIsoPFTauHPS27_eta2p1_TightID_CrossL1_v") return true;
      if(trig=="HLT_IsoMu20_eta2p1_MediumChargedIsoPFTauHPS27_eta2p1_CrossL1_v") return true;
      if(trig=="HLT_IsoMu20_eta2p1_MediumChargedIsoPFTauHPS27_eta2p1_TightID_CrossL1_v") return true;
      if(trig=="HLT_IsoMu20_eta2p1_TightChargedIsoPFTauHPS27_eta2p1_CrossL1_v") return true;
      if(trig=="HLT_IsoMu20_eta2p1_TightChargedIsoPFTauHPS27_eta2p1_TightID_CrossL1_v") return true;
      if(trig=="HLT_IsoMu20_v") return true;
      if(trig=="HLT_IsoMu24_TwoProngs35_v") return true;
      if(trig=="HLT_IsoMu24_eta2p1_v") return true;
      if(trig=="HLT_IsoMu24_v") return true;
      if(trig=="HLT_IsoMu27_v") return true;
      if(trig=="HLT_IsoMu30_v") return true;
      if(trig=="HLT_L1SingleMu18_v") return true;
      if(trig=="HLT_L1SingleMu25_v") return true;
      if(trig=="HLT_L2Mu10_v") return true;
      if(trig=="HLT_L2Mu50_v") return true;
      if(trig=="HLT_Mu10_TrkIsoVVL_DiPFJet40_DEta3p5_MJJ750_HTT350_PFMETNoMu60_v") return true;
      if(trig=="HLT_Mu12_v") return true;
      if(trig=="HLT_Mu15_IsoVVVL_PFHT450_CaloBTagDeepCSV_4p5_v") return true;
      if(trig=="HLT_Mu15_IsoVVVL_PFHT450_PFMET50_v") return true;
      if(trig=="HLT_Mu15_IsoVVVL_PFHT450_v") return true;
      if(trig=="HLT_Mu15_IsoVVVL_PFHT600_v") return true;
      if(trig=="HLT_Mu15_v") return true;
      if(trig=="HLT_Mu20_v") return true;
      if(trig=="HLT_Mu27_v") return true;
      if(trig=="HLT_Mu3_PFJet40_v") return true;
      if(trig=="HLT_Mu3er1p5_PFJet100er2p5_PFMET100_PFMHT100_IDTight_v") return true;
      if(trig=="HLT_Mu3er1p5_PFJet100er2p5_PFMET70_PFMHT70_IDTight_v") return true;
      if(trig=="HLT_Mu3er1p5_PFJet100er2p5_PFMET80_PFMHT80_IDTight_v") return true;
      if(trig=="HLT_Mu3er1p5_PFJet100er2p5_PFMET90_PFMHT90_IDTight_v") return true;
      if(trig=="HLT_Mu3er1p5_PFJet100er2p5_PFMETNoMu100_PFMHTNoMu100_IDTight_v") return true;
      if(trig=="HLT_Mu3er1p5_PFJet100er2p5_PFMETNoMu70_PFMHTNoMu70_IDTight_v") return true;
      if(trig=="HLT_Mu3er1p5_PFJet100er2p5_PFMETNoMu80_PFMHTNoMu80_IDTight_v") return true;
      if(trig=="HLT_Mu3er1p5_PFJet100er2p5_PFMETNoMu90_PFMHTNoMu90_IDTight_v") return true;
      if(trig=="HLT_Mu4_TrkIsoVVL_DiPFJet90_40_DEta3p5_MJJ750_HTT300_PFMETNoMu60_v") return true;
      if(trig=="HLT_Mu50_IsoVVVL_PFHT450_v") return true;
      if(trig=="HLT_Mu50_v") return true;
      if(trig=="HLT_Mu55_v") return true;
      if(trig=="HLT_Mu8_TrkIsoVVL_DiPFJet40_DEta3p5_MJJ750_HTT300_PFMETNoMu60_v") return true;
      if(trig=="HLT_OldMu100_v") return true;
      if(trig=="HLT_TkMu100_v") return true;
    }
    if(PD=="EGamma"){
      
      if(trig=="HLT_DiEle27_WPTightCaloOnly_L1DoubleEG_v") return true;
      if(trig=="HLT_DiSC30_18_EIso_AND_HE_Mass70_v") return true;
      if(trig=="HLT_Diphoton30PV_18PV_R9Id_AND_IsoCaloId_AND_HE_R9Id_NoPixelVeto_Mass55_v") return true;
      if(trig=="HLT_Diphoton30PV_18PV_R9Id_AND_IsoCaloId_AND_HE_R9Id_PixelVeto_Mass55_v") return true;
      if(trig=="HLT_Diphoton30_18_R9IdL_AND_HE_AND_IsoCaloId_NoPixelVeto_Mass55_v") return true;
      if(trig=="HLT_Diphoton30_18_R9IdL_AND_HE_AND_IsoCaloId_NoPixelVeto_v") return true;
      if(trig=="HLT_Diphoton30_22_R9Id_OR_IsoCaloId_AND_HE_R9Id_Mass90_v") return true;
      if(trig=="HLT_Diphoton30_22_R9Id_OR_IsoCaloId_AND_HE_R9Id_Mass95_v") return true;
      if(trig=="HLT_DoubleEle25_CaloIdL_MW_v") return true;
      if(trig=="HLT_DoubleEle27_CaloIdL_MW_v") return true;
      if(trig=="HLT_DoubleEle33_CaloIdL_MW_v") return true;
      if(trig=="HLT_DoubleEle8_CaloIdM_TrackIdM_Mass8_DZ_PFHT350_v") return true;
      if(trig=="HLT_DoubleEle8_CaloIdM_TrackIdM_Mass8_PFHT350_v") return true;
      if(trig=="HLT_DoublePhoton33_CaloIdL_v") return true;
      if(trig=="HLT_DoublePhoton70_v") return true;
      if(trig=="HLT_DoublePhoton85_v") return true;
      if(trig=="HLT_ECALHT800_v") return true;
      if(trig=="HLT_Ele115_CaloIdVT_GsfTrkIdT_v") return true;
      if(trig=="HLT_Ele12_CaloIdL_TrackIdL_IsoVL_PFJet30_v") return true;
      if(trig=="HLT_Ele135_CaloIdVT_GsfTrkIdT_v") return true;
      if(trig=="HLT_Ele145_CaloIdVT_GsfTrkIdT_v") return true;
      if(trig=="HLT_Ele15_CaloIdL_TrackIdL_IsoVL_PFJet30_v") return true;
      if(trig=="HLT_Ele15_Ele8_CaloIdL_TrackIdL_IsoVL_v") return true;
      if(trig=="HLT_Ele15_IsoVVVL_PFHT450_CaloBTagDeepCSV_4p5_v") return true;
      if(trig=="HLT_Ele15_IsoVVVL_PFHT450_PFMET50_v") return true;
      if(trig=="HLT_Ele15_IsoVVVL_PFHT450_v") return true;
      if(trig=="HLT_Ele15_IsoVVVL_PFHT600_v") return true;
      if(trig=="HLT_Ele15_WPLoose_Gsf_v") return true;
      if(trig=="HLT_Ele16_Ele12_Ele8_CaloIdL_TrackIdL_v") return true;
      if(trig=="HLT_Ele17_CaloIdM_TrackIdM_PFJet30_v") return true;
      if(trig=="HLT_Ele17_WPLoose_Gsf_v") return true;
      if(trig=="HLT_Ele200_CaloIdVT_GsfTrkIdT_v") return true;
      if(trig=="HLT_Ele20_WPLoose_Gsf_v") return true;
      if(trig=="HLT_Ele20_WPTight_Gsf_v") return true;
      if(trig=="HLT_Ele20_eta2p1_WPLoose_Gsf_v") return true;
      if(trig=="HLT_Ele23_CaloIdL_TrackIdL_IsoVL_PFJet30_v") return true;
      if(trig=="HLT_Ele23_CaloIdM_TrackIdM_PFJet30_v") return true;
      if(trig=="HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v") return true;
      if(trig=="HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_v") return true;
      if(trig=="HLT_Ele24_eta2p1_WPTight_Gsf_LooseChargedIsoPFTauHPS30_eta2p1_CrossL1_v") return true;
      if(trig=="HLT_Ele24_eta2p1_WPTight_Gsf_LooseChargedIsoPFTauHPS30_eta2p1_TightID_CrossL1_v") return true;
      if(trig=="HLT_Ele24_eta2p1_WPTight_Gsf_MediumChargedIsoPFTauHPS30_eta2p1_CrossL1_v") return true;
      if(trig=="HLT_Ele24_eta2p1_WPTight_Gsf_MediumChargedIsoPFTauHPS30_eta2p1_TightID_CrossL1_v") return true;
      if(trig=="HLT_Ele24_eta2p1_WPTight_Gsf_TightChargedIsoPFTauHPS30_eta2p1_CrossL1_v") return true;
      if(trig=="HLT_Ele24_eta2p1_WPTight_Gsf_TightChargedIsoPFTauHPS30_eta2p1_TightID_CrossL1_v") return true;
      if(trig=="HLT_Ele250_CaloIdVT_GsfTrkIdT_v") return true;
      if(trig=="HLT_Ele27_Ele37_CaloIdL_MW_v") return true;
      if(trig=="HLT_Ele27_WPTight_Gsf_v") return true;
      if(trig=="HLT_Ele28_HighEta_SC20_Mass55_v") return true;
      if(trig=="HLT_Ele28_WPTight_Gsf_v") return true;
      if(trig=="HLT_Ele28_eta2p1_WPTight_Gsf_HT150_v") return true;
      if(trig=="HLT_Ele300_CaloIdVT_GsfTrkIdT_v") return true;
      if(trig=="HLT_Ele30_WPTight_Gsf_v") return true;
      if(trig=="HLT_Ele30_eta2p1_WPTight_Gsf_CentralPFJet35_EleCleaned_v") return true;
      if(trig=="HLT_Ele32_WPTight_Gsf_L1DoubleEG_v") return true;
      if(trig=="HLT_Ele32_WPTight_Gsf_v") return true;
      if(trig=="HLT_Ele35_WPTight_Gsf_L1EGMT_v") return true;
      if(trig=="HLT_Ele35_WPTight_Gsf_v") return true;
      if(trig=="HLT_Ele38_WPTight_Gsf_v") return true;
      if(trig=="HLT_Ele40_WPTight_Gsf_v") return true;
      if(trig=="HLT_Ele50_CaloIdVT_GsfTrkIdT_PFJet165_v") return true;
      if(trig=="HLT_Ele50_IsoVVVL_PFHT450_v") return true;
      if(trig=="HLT_Ele8_CaloIdL_TrackIdL_IsoVL_PFJet30_v") return true;
      if(trig=="HLT_Ele8_CaloIdM_TrackIdM_PFJet30_v") return true;
      if(trig=="HLT_Photon100EBHE10_v") return true;
      if(trig=="HLT_Photon100EB_TightID_TightIso_v") return true;
      if(trig=="HLT_Photon100EEHE10_v") return true;
      if(trig=="HLT_Photon100EE_TightID_TightIso_v") return true;
      if(trig=="HLT_Photon110EB_TightID_TightIso_v") return true;
      if(trig=="HLT_Photon120EB_TightID_TightIso_v") return true;
      if(trig=="HLT_Photon120_R9Id90_HE10_IsoM_v") return true;
      if(trig=="HLT_Photon120_v") return true;
      if(trig=="HLT_Photon150_v") return true;
      if(trig=="HLT_Photon165_R9Id90_HE10_IsoM_v") return true;
      if(trig=="HLT_Photon175_v") return true;
      if(trig=="HLT_Photon200_v") return true;
      if(trig=="HLT_Photon20_HoverELoose_v") return true;
      if(trig=="HLT_Photon20_v") return true;
      if(trig=="HLT_Photon300_NoHE_v") return true;
      if(trig=="HLT_Photon30_HoverELoose_v") return true;
      if(trig=="HLT_Photon33_v") return true;
      if(trig=="HLT_Photon50_R9Id90_HE10_IsoM_EBOnly_PFJetsMJJ300DEta3_PFMET50_v") return true;
      if(trig=="HLT_Photon50_R9Id90_HE10_IsoM_v") return true;
      if(trig=="HLT_Photon50_v") return true;
      if(trig=="HLT_Photon60_R9Id90_CaloIdL_IsoL_DisplacedIdL_PFHT350MinPFJet15_v") return true;
      if(trig=="HLT_Photon60_R9Id90_CaloIdL_IsoL_DisplacedIdL_v") return true;
      if(trig=="HLT_Photon60_R9Id90_CaloIdL_IsoL_v") return true;
      if(trig=="HLT_Photon75_R9Id90_HE10_IsoM_EBOnly_CaloMJJ300_PFJetsMJJ400DEta3_v") return true;
      if(trig=="HLT_Photon75_R9Id90_HE10_IsoM_EBOnly_CaloMJJ400_PFJetsMJJ600DEta3_v") return true;
      if(trig=="HLT_Photon75_R9Id90_HE10_IsoM_EBOnly_PFJetsMJJ300DEta3_v") return true;
      if(trig=="HLT_Photon75_R9Id90_HE10_IsoM_EBOnly_PFJetsMJJ600DEta3_v") return true;
      if(trig=="HLT_Photon75_R9Id90_HE10_IsoM_v") return true;
      if(trig=="HLT_Photon75_v") return true;
      if(trig=="HLT_Photon90_R9Id90_HE10_IsoM_v") return true;
      if(trig=="HLT_Photon90_v") return true;
      if(trig=="HLT_TriplePhoton_20_20_20_CaloIdLV2_R9IdVL_v") return true;
      if(trig=="HLT_TriplePhoton_20_20_20_CaloIdLV2_v") return true;
      if(trig=="HLT_TriplePhoton_30_30_10_CaloIdLV2_R9IdVL_v") return true;
      if(trig=="HLT_TriplePhoton_30_30_10_CaloIdLV2_v") return true;
      if(trig=="HLT_TriplePhoton_35_35_5_CaloIdLV2_R9IdVL_v") return true;
    }
    if(PD=="DoubleMuon"){
      if(trig=="HLT_DoubleL2Mu23NoVtx_2Cha_CosmicSeed_NoL2Matched_v") return true;
      if(trig=="HLT_DoubleL2Mu23NoVtx_2Cha_CosmicSeed_v") return true;
      if(trig=="HLT_DoubleL2Mu23NoVtx_2Cha_NoL2Matched_v") return true;
      if(trig=="HLT_DoubleL2Mu23NoVtx_2Cha_v") return true;
      if(trig=="HLT_DoubleL2Mu25NoVtx_2Cha_CosmicSeed_Eta2p4_v") return true;
      if(trig=="HLT_DoubleL2Mu25NoVtx_2Cha_CosmicSeed_NoL2Matched_v") return true;
      if(trig=="HLT_DoubleL2Mu25NoVtx_2Cha_CosmicSeed_v") return true;
      if(trig=="HLT_DoubleL2Mu25NoVtx_2Cha_Eta2p4_v") return true;
      if(trig=="HLT_DoubleL2Mu25NoVtx_2Cha_NoL2Matched_v") return true;
      if(trig=="HLT_DoubleL2Mu25NoVtx_2Cha_v") return true;
      if(trig=="HLT_DoubleL2Mu30NoVtx_2Cha_CosmicSeed_Eta2p4_v") return true;
      if(trig=="HLT_DoubleL2Mu30NoVtx_2Cha_Eta2p4_v") return true;
      if(trig=="HLT_DoubleL2Mu50_v") return true;
      if(trig=="HLT_DoubleMu33NoFiltersNoVtxDisplaced_v") return true;
      if(trig=="HLT_DoubleMu3_DCA_PFMET50_PFMHT60_v") return true;
      if(trig=="HLT_DoubleMu3_DZ_PFMET50_PFMHT60_v") return true;
      if(trig=="HLT_DoubleMu3_DZ_PFMET70_PFMHT70_v") return true;
      if(trig=="HLT_DoubleMu3_DZ_PFMET90_PFMHT90_v") return true;
      if(trig=="HLT_DoubleMu40NoFiltersNoVtxDisplaced_v") return true;
      if(trig=="HLT_DoubleMu43NoFiltersNoVtx_v") return true;
      if(trig=="HLT_DoubleMu48NoFiltersNoVtx_v") return true;
      if(trig=="HLT_DoubleMu4_Mass3p8_DZ_PFHT350_v") return true;
      if(trig=="HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8_v") return true;
      if(trig=="HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8_v") return true;
      if(trig=="HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v") return true;
      if(trig=="HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_v") return true;
      if(trig=="HLT_Mu17_TrkIsoVVL_v") return true;
      if(trig=="HLT_Mu17_v") return true;
      if(trig=="HLT_Mu18_Mu9_DZ_v") return true;
      if(trig=="HLT_Mu18_Mu9_SameSign_DZ_v") return true;
      if(trig=="HLT_Mu18_Mu9_SameSign_v") return true;
      if(trig=="HLT_Mu18_Mu9_v") return true;
      if(trig=="HLT_Mu19_TrkIsoVVL_Mu9_TrkIsoVVL_DZ_Mass3p8_v") return true;
      if(trig=="HLT_Mu19_TrkIsoVVL_Mu9_TrkIsoVVL_DZ_Mass8_v") return true;
      if(trig=="HLT_Mu19_TrkIsoVVL_Mu9_TrkIsoVVL_DZ_v") return true;
      if(trig=="HLT_Mu19_TrkIsoVVL_Mu9_TrkIsoVVL_v") return true;
      if(trig=="HLT_Mu19_TrkIsoVVL_v") return true;
      if(trig=="HLT_Mu19_v") return true;
      if(trig=="HLT_Mu20_Mu10_DZ_v") return true;
      if(trig=="HLT_Mu20_Mu10_SameSign_DZ_v") return true;
      if(trig=="HLT_Mu20_Mu10_SameSign_v") return true;
      if(trig=="HLT_Mu20_Mu10_v") return true;
      if(trig=="HLT_Mu23_Mu12_DZ_v") return true;
      if(trig=="HLT_Mu23_Mu12_SameSign_DZ_v") return true;
      if(trig=="HLT_Mu23_Mu12_SameSign_v") return true;
      if(trig=="HLT_Mu23_Mu12_v") return true;
      if(trig=="HLT_Mu37_TkMu27_v") return true;
      if(trig=="HLT_Mu8_TrkIsoVVL_v") return true;
      if(trig=="HLT_Mu8_v") return true;
      if(trig=="HLT_TripleMu_10_5_5_DZ_v") return true;
      if(trig=="HLT_TripleMu_12_10_5_v") return true;
      if(trig=="HLT_TripleMu_5_3_3_Mass3p8_DCA_v") return true;
      if(trig=="HLT_TripleMu_5_3_3_Mass3p8_DZ_v") return true;
      if(trig=="HLT_TrkMu12_DoubleTrkMu5NoFiltersNoVtx_v") return true;
      if(trig=="HLT_TrkMu16_DoubleTrkMu6NoFiltersNoVtx_v") return true;
      if(trig=="HLT_TrkMu17_DoubleTrkMu8NoFiltersNoVtx_v") return true;
      if(trig=="HLT_Dimuon0_LowMass_L1_TM530_v") return true;
      if(trig=="HLT_DoubleMu3_TkMu_DsTau3Mu_v") return true;
      if(trig=="HLT_DoubleMu3_Trk_Tau3mu_NoL1Mass_v") return true;
      if(trig=="HLT_DoubleMu3_Trk_Tau3mu_v") return true;
      if(trig=="HLT_DoubleMu4_LowMassNonResonantTrk_Displaced_v") return true;
      if(trig=="HLT_Tau3Mu_Mu7_Mu1_TkMu1_IsoTau15_Charge1_v") return true;
      if(trig=="HLT_Tau3Mu_Mu7_Mu1_TkMu1_IsoTau15_v") return true;
      if(trig=="HLT_Tau3Mu_Mu7_Mu1_TkMu1_Tau15_Charge1_v") return true;
      if(trig=="HLT_Tau3Mu_Mu7_Mu1_TkMu1_Tau15_v") return true;
    }
    if(PD=="MuonEG"){
      if(trig=="HLT_DiMu4_Ele9_CaloIdL_TrackIdL_DZ_Mass3p8_v") return true;
      if(trig=="HLT_DiMu9_Ele9_CaloIdL_TrackIdL_DZ_v") return true;
      if(trig=="HLT_DiMu9_Ele9_CaloIdL_TrackIdL_v") return true;
      if(trig=="HLT_DoubleMu20_7_Mass0to30_L1_DM4EG_v") return true;
      if(trig=="HLT_DoubleMu20_7_Mass0to30_L1_DM4_v") return true;
      if(trig=="HLT_DoubleMu20_7_Mass0to30_Photon23_v") return true;
      if(trig=="HLT_Mu12_DoublePhoton20_v") return true;
      if(trig=="HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_v") return true;
      if(trig=="HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_v") return true;
      if(trig=="HLT_Mu17_Photon30_IsoCaloId_v") return true;
      if(trig=="HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v") return true;
      if(trig=="HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v") return true;
      if(trig=="HLT_Mu27_Ele37_CaloIdL_MW_v") return true;
      if(trig=="HLT_Mu37_Ele27_CaloIdL_MW_v") return true;
      if(trig=="HLT_Mu38NoFiltersNoVtxDisplaced_Photon38_CaloIdL_v") return true;
      if(trig=="HLT_Mu43NoFiltersNoVtxDisplaced_Photon43_CaloIdL_v") return true;
      if(trig=="HLT_Mu43NoFiltersNoVtx_Photon43_CaloIdL_v") return true;
      if(trig=="HLT_Mu48NoFiltersNoVtx_Photon48_CaloIdL_v") return true;
      if(trig=="HLT_Mu8_DiEle12_CaloIdL_TrackIdL_DZ_v") return true;
      if(trig=="HLT_Mu8_DiEle12_CaloIdL_TrackIdL_v") return true;
      if(trig=="HLT_Mu8_Ele8_CaloIdM_TrackIdM_Mass8_PFHT350_DZ_v") return true;
      if(trig=="HLT_Mu8_Ele8_CaloIdM_TrackIdM_Mass8_PFHT350_v") return true;
      if(trig=="HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_CaloDiJet30_CaloBtagDeepCSV_1p5_v") return true;
      if(trig=="HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_CaloDiJet30_v") return true;
      if(trig=="HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_PFDiJet30_PFBtagDeepCSV_1p5_v") return true;
      if(trig=="HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_PFDiJet30_v") return true;
      if(trig=="HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_v") return true;
      if(trig=="HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_v") return true;
    }
    if(PD=="MET"){
      if(trig=="HLT_CaloMET100_HBHECleaned_v") return true;
      if(trig=="HLT_CaloMET100_NotCleaned_v") return true;
      if(trig=="HLT_CaloMET110_NotCleaned_v") return true;
      if(trig=="HLT_CaloMET250_HBHECleaned_v") return true;
      if(trig=="HLT_CaloMET250_NotCleaned_v") return true;
      if(trig=="HLT_CaloMET300_HBHECleaned_v") return true;
      if(trig=="HLT_CaloMET350_HBHECleaned_v") return true;
      if(trig=="HLT_CaloMET70_HBHECleaned_v") return true;
      if(trig=="HLT_CaloMET80_HBHECleaned_v") return true;
      if(trig=="HLT_CaloMET80_NotCleaned_v") return true;
      if(trig=="HLT_CaloMET90_HBHECleaned_v") return true;
      if(trig=="HLT_CaloMET90_NotCleaned_v") return true;
      if(trig=="HLT_CaloMHT90_v") return true;
      if(trig=="HLT_DiJet110_35_Mjj650_PFMET110_v") return true;
      if(trig=="HLT_DiJet110_35_Mjj650_PFMET120_v") return true;
      if(trig=="HLT_DiJet110_35_Mjj650_PFMET130_v") return true;
      if(trig=="HLT_L1ETMHadSeeds_v") return true;
      if(trig=="HLT_MET105_IsoTrk50_v") return true;
      if(trig=="HLT_MET120_IsoTrk50_v") return true;
      if(trig=="HLT_MonoCentralPFJet80_PFMETNoMu110_PFMHTNoMu110_IDTight_v") return true;
      if(trig=="HLT_MonoCentralPFJet80_PFMETNoMu120_PFMHTNoMu120_IDTight_v") return true;
      if(trig=="HLT_MonoCentralPFJet80_PFMETNoMu130_PFMHTNoMu130_IDTight_v") return true;
      if(trig=="HLT_MonoCentralPFJet80_PFMETNoMu140_PFMHTNoMu140_IDTight_v") return true;
      if(trig=="HLT_PFMET100_PFMHT100_IDTight_CaloBTagDeepCSV_3p1_v") return true;
      if(trig=="HLT_PFMET100_PFMHT100_IDTight_PFHT60_v") return true;
      if(trig=="HLT_PFMET110_PFMHT110_IDTight_CaloBTagDeepCSV_3p1_v") return true;
      if(trig=="HLT_PFMET110_PFMHT110_IDTight_v") return true;
      if(trig=="HLT_PFMET120_PFMHT120_IDTight_CaloBTagDeepCSV_3p1_v") return true;
      if(trig=="HLT_PFMET120_PFMHT120_IDTight_PFHT60_v") return true;
      if(trig=="HLT_PFMET120_PFMHT120_IDTight_v") return true;
      if(trig=="HLT_PFMET130_PFMHT130_IDTight_CaloBTagDeepCSV_3p1_v") return true;
      if(trig=="HLT_PFMET130_PFMHT130_IDTight_v") return true;
      if(trig=="HLT_PFMET140_PFMHT140_IDTight_CaloBTagDeepCSV_3p1_v") return true;
      if(trig=="HLT_PFMET140_PFMHT140_IDTight_v") return true;
      if(trig=="HLT_PFMET200_HBHECleaned_v") return true;
      if(trig=="HLT_PFMET200_HBHE_BeamHaloCleaned_v") return true;
      if(trig=="HLT_PFMET200_NotCleaned_v") return true;
      if(trig=="HLT_PFMET250_HBHECleaned_v") return true;
      if(trig=="HLT_PFMET300_HBHECleaned_v") return true;
      if(trig=="HLT_PFMETNoMu100_PFMHTNoMu100_IDTight_PFHT60_v") return true;
      if(trig=="HLT_PFMETNoMu110_PFMHTNoMu110_IDTight_v") return true;
      if(trig=="HLT_PFMETNoMu120_PFMHTNoMu120_IDTight_PFHT60_v") return true;
      if(trig=="HLT_PFMETNoMu120_PFMHTNoMu120_IDTight_v") return true;
      if(trig=="HLT_PFMETNoMu130_PFMHTNoMu130_IDTight_v") return true;
      if(trig=="HLT_PFMETNoMu140_PFMHTNoMu140_IDTight_v") return true;
      if(trig=="HLT_PFMETTypeOne100_PFMHT100_IDTight_PFHT60_v") return true;
      if(trig=="HLT_PFMETTypeOne110_PFMHT110_IDTight_v") return true;
      if(trig=="HLT_PFMETTypeOne120_PFMHT120_IDTight_PFHT60_v") return true;
      if(trig=="HLT_PFMETTypeOne120_PFMHT120_IDTight_v") return true;
      if(trig=="HLT_PFMETTypeOne130_PFMHT130_IDTight_v") return true;
      if(trig=="HLT_PFMETTypeOne140_PFMHT140_IDTight_v") return true;
      if(trig=="HLT_PFMETTypeOne200_HBHE_BeamHaloCleaned_v") return true;
      if(trig=="HLT_TripleJet110_35_35_Mjj650_PFMET110_v") return true;
      if(trig=="HLT_TripleJet110_35_35_Mjj650_PFMET120_v") return true;
      if(trig=="HLT_TripleJet110_35_35_Mjj650_PFMET130_v") return true;
    }
    if(PD=="JetHT"){
      if(trig=="HLT_AK8PFHT750_TrimMass50_v") return true;
      if(trig=="HLT_AK8PFHT800_TrimMass50_v") return true;
      if(trig=="HLT_AK8PFHT850_TrimMass50_v") return true;
      if(trig=="HLT_AK8PFHT900_TrimMass50_v") return true;
      if(trig=="HLT_AK8PFJet140_v") return true;
      if(trig=="HLT_AK8PFJet15_v") return true;
      if(trig=="HLT_AK8PFJet200_v") return true;
      if(trig=="HLT_AK8PFJet25_v") return true;
      if(trig=="HLT_AK8PFJet260_v") return true;
      if(trig=="HLT_AK8PFJet320_v") return true;
      if(trig=="HLT_AK8PFJet330_TrimMass30_PFAK8BTagDeepCSV_p17_v") return true;
      if(trig=="HLT_AK8PFJet330_TrimMass30_PFAK8BTagDeepCSV_p1_v") return true;
      if(trig=="HLT_AK8PFJet330_TrimMass30_PFAK8BoostedDoubleB_np2_v") return true;
      if(trig=="HLT_AK8PFJet330_TrimMass30_PFAK8BoostedDoubleB_np4_v") return true;
      if(trig=="HLT_AK8PFJet330_TrimMass30_PFAK8BoostedDoubleB_p02_v") return true;
      if(trig=="HLT_AK8PFJet360_TrimMass30_v") return true;
      if(trig=="HLT_AK8PFJet380_TrimMass30_v") return true;
      if(trig=="HLT_AK8PFJet400_TrimMass30_v") return true;
      if(trig=="HLT_AK8PFJet400_v") return true;
      if(trig=="HLT_AK8PFJet40_v") return true;
      if(trig=="HLT_AK8PFJet420_TrimMass30_v") return true;
      if(trig=="HLT_AK8PFJet450_v") return true;
      if(trig=="HLT_AK8PFJet500_v") return true;
      if(trig=="HLT_AK8PFJet550_v") return true;
      if(trig=="HLT_AK8PFJet60_v") return true;
      if(trig=="HLT_AK8PFJet80_v") return true;
      if(trig=="HLT_AK8PFJetFwd140_v") return true;
      if(trig=="HLT_AK8PFJetFwd15_v") return true;
      if(trig=="HLT_AK8PFJetFwd200_v") return true;
      if(trig=="HLT_AK8PFJetFwd25_v") return true;
      if(trig=="HLT_AK8PFJetFwd260_v") return true;
      if(trig=="HLT_AK8PFJetFwd320_v") return true;
      if(trig=="HLT_AK8PFJetFwd400_v") return true;
      if(trig=="HLT_AK8PFJetFwd40_v") return true;
      if(trig=="HLT_AK8PFJetFwd450_v") return true;
      if(trig=="HLT_AK8PFJetFwd500_v") return true;
      if(trig=="HLT_AK8PFJetFwd60_v") return true;
      if(trig=="HLT_AK8PFJetFwd80_v") return true;
      if(trig=="HLT_CaloJet500_NoJetID_v") return true;
      if(trig=="HLT_CaloJet550_NoJetID_v") return true;
      if(trig=="HLT_DiPFJetAve100_HFJEC_v") return true;
      if(trig=="HLT_DiPFJetAve140_v") return true;
      if(trig=="HLT_DiPFJetAve160_HFJEC_v") return true;
      if(trig=="HLT_DiPFJetAve200_v") return true;
      if(trig=="HLT_DiPFJetAve220_HFJEC_v") return true;
      if(trig=="HLT_DiPFJetAve260_v") return true;
      if(trig=="HLT_DiPFJetAve300_HFJEC_v") return true;
      if(trig=="HLT_DiPFJetAve320_v") return true;
      if(trig=="HLT_DiPFJetAve400_v") return true;
      if(trig=="HLT_DiPFJetAve40_v") return true;
      if(trig=="HLT_DiPFJetAve500_v") return true;
      if(trig=="HLT_DiPFJetAve60_HFJEC_v") return true;
      if(trig=="HLT_DiPFJetAve60_v") return true;
      if(trig=="HLT_DiPFJetAve80_HFJEC_v") return true;
      if(trig=="HLT_DiPFJetAve80_v") return true;
      if(trig=="HLT_DoublePFJets100_CaloBTagDeepCSV_p71_v") return true;
      if(trig=="HLT_DoublePFJets116MaxDeta1p6_DoubleCaloBTagDeepCSV_p71_v") return true;
      if(trig=="HLT_DoublePFJets128MaxDeta1p6_DoubleCaloBTagDeepCSV_p71_v") return true;
      if(trig=="HLT_DoublePFJets200_CaloBTagDeepCSV_p71_v") return true;
      if(trig=="HLT_DoublePFJets350_CaloBTagDeepCSV_p71_v") return true;
      if(trig=="HLT_DoublePFJets40_CaloBTagDeepCSV_p71_v") return true;
      if(trig=="HLT_Mu12_DoublePFJets100_CaloBTagDeepCSV_p71_v") return true;
      if(trig=="HLT_Mu12_DoublePFJets200_CaloBTagDeepCSV_p71_v") return true;
      if(trig=="HLT_Mu12_DoublePFJets350_CaloBTagDeepCSV_p71_v") return true;
      if(trig=="HLT_Mu12_DoublePFJets40MaxDeta1p6_DoubleCaloBTagDeepCSV_p71_v") return true;
      if(trig=="HLT_Mu12_DoublePFJets40_CaloBTagDeepCSV_p71_v") return true;
      if(trig=="HLT_Mu12_DoublePFJets54MaxDeta1p6_DoubleCaloBTagDeepCSV_p71_v") return true;
      if(trig=="HLT_Mu12_DoublePFJets62MaxDeta1p6_DoubleCaloBTagDeepCSV_p71_v") return true;
      if(trig=="HLT_PFHT1050_v") return true;
      if(trig=="HLT_PFHT180_v") return true;
      if(trig=="HLT_PFHT250_v") return true;
      if(trig=="HLT_PFHT330PT30_QuadPFJet_75_60_45_40_TriplePFBTagDeepCSV_4p5_v") return true;
      if(trig=="HLT_PFHT330PT30_QuadPFJet_75_60_45_40_v") return true;
      if(trig=="HLT_PFHT350MinPFJet15_v") return true;
      if(trig=="HLT_PFHT350_v") return true;
      if(trig=="HLT_PFHT370_v") return true;
      if(trig=="HLT_PFHT400_FivePFJet_100_100_60_30_30_DoublePFBTagDeepCSV_4p5_v") return true;
      if(trig=="HLT_PFHT400_FivePFJet_100_100_60_30_30_v") return true;
      if(trig=="HLT_PFHT400_FivePFJet_120_120_60_30_30_DoublePFBTagDeepCSV_4p5_v") return true;
      if(trig=="HLT_PFHT400_SixPFJet32_DoublePFBTagDeepCSV_2p94_v") return true;
      if(trig=="HLT_PFHT400_SixPFJet32_v") return true;
      if(trig=="HLT_PFHT430_v") return true;
      if(trig=="HLT_PFHT450_SixPFJet36_PFBTagDeepCSV_1p59_v") return true;
      if(trig=="HLT_PFHT450_SixPFJet36_v") return true;
      if(trig=="HLT_PFHT500_PFMET100_PFMHT100_IDTight_v") return true;
      if(trig=="HLT_PFHT500_PFMET110_PFMHT110_IDTight_v") return true;
      if(trig=="HLT_PFHT510_v") return true;
      if(trig=="HLT_PFHT590_v") return true;
      if(trig=="HLT_PFHT680_v") return true;
      if(trig=="HLT_PFHT700_PFMET85_PFMHT85_IDTight_v") return true;
      if(trig=="HLT_PFHT700_PFMET95_PFMHT95_IDTight_v") return true;
      if(trig=="HLT_PFHT780_v") return true;
      if(trig=="HLT_PFHT800_PFMET75_PFMHT75_IDTight_v") return true;
      if(trig=="HLT_PFHT800_PFMET85_PFMHT85_IDTight_v") return true;
      if(trig=="HLT_PFHT890_v") return true;
      if(trig=="HLT_PFJet140_v") return true;
      if(trig=="HLT_PFJet15_v") return true;
      if(trig=="HLT_PFJet200_v") return true;
      if(trig=="HLT_PFJet25_v") return true;
      if(trig=="HLT_PFJet260_v") return true;
      if(trig=="HLT_PFJet320_v") return true;
      if(trig=="HLT_PFJet400_v") return true;
      if(trig=="HLT_PFJet40_v") return true;
      if(trig=="HLT_PFJet450_v") return true;
      if(trig=="HLT_PFJet500_v") return true;
      if(trig=="HLT_PFJet550_v") return true;
      if(trig=="HLT_PFJet60_v") return true;
      if(trig=="HLT_PFJet80_v") return true;
      if(trig=="HLT_PFJetFwd140_v") return true;
      if(trig=="HLT_PFJetFwd15_v") return true;
      if(trig=="HLT_PFJetFwd200_v") return true;
      if(trig=="HLT_PFJetFwd25_v") return true;
      if(trig=="HLT_PFJetFwd260_v") return true;
      if(trig=="HLT_PFJetFwd320_v") return true;
      if(trig=="HLT_PFJetFwd400_v") return true;
      if(trig=="HLT_PFJetFwd40_v") return true;
      if(trig=="HLT_PFJetFwd450_v") return true;
      if(trig=="HLT_PFJetFwd500_v") return true;
      if(trig=="HLT_PFJetFwd60_v") return true;
      if(trig=="HLT_PFJetFwd80_v") return true;
      if(trig=="HLT_QuadPFJet103_88_75_15_DoublePFBTagDeepCSV_1p3_7p7__VBF1_v") return true;
      if(trig=="HLT_QuadPFJet103_88_75_15_PFBTagDeepCSV_1p3__VBF2_v") return true;
      if(trig=="HLT_QuadPFJet103_88_75_15_v") return true;
      if(trig=="HLT_QuadPFJet105_88_76_15_DoublePFBTagDeepCSV_1p3_7p7__VBF1_v") return true;
      if(trig=="HLT_QuadPFJet105_88_76_15_PFBTagDeepCSV_1p3__VBF2_v") return true;
      if(trig=="HLT_QuadPFJet105_88_76_15_v") return true;
      if(trig=="HLT_QuadPFJet111_90_80_15_DoublePFBTagDeepCSV_1p3_7p7__VBF1_v") return true;
      if(trig=="HLT_QuadPFJet111_90_80_15_PFBTagDeepCSV_1p3__VBF2_v") return true;
      if(trig=="HLT_QuadPFJet111_90_80_15_v") return true;
      if(trig=="HLT_QuadPFJet98_83_71_15_DoublePFBTagDeepCSV_1p3_7p7__VBF1_v") return true;
      if(trig=="HLT_QuadPFJet98_83_71_15_PFBTagDeepCSV_1p3__VBF2_v") return true;
      if(trig=="HLT_QuadPFJet98_83_71_15_v") return true;
      if(trig=="HLT_Rsq0p35_v") return true;
      if(trig=="HLT_Rsq0p40_v") return true;
      if(trig=="HLT_RsqMR300_Rsq0p09_MR200_4jet_v") return true;
      if(trig=="HLT_RsqMR300_Rsq0p09_MR200_v") return true;
      if(trig=="HLT_RsqMR320_Rsq0p09_MR200_4jet_v") return true;
      if(trig=="HLT_RsqMR320_Rsq0p09_MR200_v") return true;
      if(trig=="HLT_SingleJet30_Mu12_SinglePFJet40_v") return true;
    }
    return false;
  }
  else{
    cout << "[Event::IsPDForTrigger] trig = " << trig << endl;
    cout << "[Event::IsPDForTrigger] PD = " << PD << endl;
    exit(ENODATA);
    return false;
  } //JH : copied from John's branch

  //if(j_DataYear==2017){
  //  if(trig=="HLT_Mu3_PFJet40_v"){
  //    if(PD=="SingleMuon") return true;
  //    else return false;
  //  }
  //  else if(trig=="HLT_Mu8_v"){
  //    if(PD=="DoubleMuon") return true;
  //    else return false;
  //  }
  //  else if(trig=="HLT_Mu17_v"){
  //    if(PD=="DoubleMuon") return true;
  //    else return false;
  //  }
  //  else if(trig=="HLT_Mu20_v"){
  //    if(PD=="SingleMuon") return true;
  //    else return false;
  //  }
  //  else if(trig=="HLT_Mu27_v"){
  //    if(PD=="SingleMuon") return true;
  //    else return false;
  //  }
  //  else if(trig=="HLT_Mu50_v"){
  //    if(PD=="SingleMuon") return true;
  //    else return false;
  //  }
  //  else if(trig=="HLT_IsoMu24_v"){
  //    if(PD=="SingleMuon") return true;
  //    else return false;
  //  }
  //  else if(trig=="HLT_IsoMu27_v"){
  //    if(PD=="SingleMuon") return true;
  //    else return false;
  //  }
  //  else if(trig=="HLT_IsoMu30_v"){
  //    if(PD=="SingleMuon") return true;
  //    else return false;
  //  }
  //  else if(trig=="HLT_Ele8_CaloIdL_TrackIdL_IsoVL_PFJet30_v"){
  //    if(PD=="SingleElectron") return true;
  //    else return false;
  //  }
  //  else if(trig=="HLT_Ele12_CaloIdL_TrackIdL_IsoVL_PFJet30_v"){
  //    if(PD=="SingleElectron") return true;
  //    else return false;
  //  }
  //  else if(trig=="HLT_Ele15_CaloIdL_TrackIdL_IsoVL_PFJet30_v"){
  //    if(PD=="SingleElectron") return true;
  //    else return false;
  //  }
  //  else if(trig=="HLT_Ele23_CaloIdL_TrackIdL_IsoVL_PFJet30_v"){
  //    if(PD=="SingleElectron") return true;
  //    else return false;
  //  }
  //  else if(trig=="HLT_Photon25_v"){
  //    if(PD=="SinglePhoton") return true;
  //    else return false;
  //  }
  //  else if(trig=="HLT_Photon33_v"){
  //    if(PD=="SinglePhoton") return true;
  //    else return false;
  //  }
  //  else if(trig=="HLT_Photon50_v"){
  //    if(PD=="SinglePhoton") return true;
  //    else return false;
  //  }
  //  else if(trig=="HLT_Photon75_v"){
  //    if(PD=="SinglePhoton") return true;
  //    else return false;
  //  }
  //  else if(trig=="HLT_Photon90_v"){
  //    if(PD=="SinglePhoton") return true;
  //    else return false;
  //  }
  //  else if(trig=="HLT_Photon120_v"){
  //    if(PD=="SinglePhoton") return true;
  //    else return false;
  //  }
  //  else if(trig=="HLT_Photon150_v"){
  //    if(PD=="SinglePhoton") return true;
  //    else return false;
  //  }
  //  else if(trig=="HLT_Photon175_v"){
  //    if(PD=="SinglePhoton") return true;
  //    else return false;
  //  }
  //  else if(trig=="HLT_Photon200_v"){
  //    if(PD=="SinglePhoton") return true;
  //    else return false;
  //  }
  //  else{
  //    cout << "[Event::IsPDForTrigger] trig = " << trig << endl;
  //    cout << "[Event::IsPDForTrigger] PD = " << PD << endl;
  //    exit(ENODATA);
  //    return false;
  //  }
  //}

  //cout << "[Event::IsPDForTrigger] trig = " << trig << endl;
  //cout << "[Event::IsPDForTrigger] PD = " << PD << endl;
  //exit(ENODATA);
  //return false;

}

void Event::SetMET(double pt, double phi){
  j_METVector.SetPtEtaPhiE(pt, 0, phi, pt);
}

