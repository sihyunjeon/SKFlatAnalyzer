#include "SkimTree_boohft_calib.h"

void SkimTree_boohft_calib::initializeAnalyzer(){

  outfile->cd();
  cout << "[SkimTree_boohft_calib::initializeAnalyzer()] gDirectory = " << gDirectory->GetName() << endl;
  newtree = fChain->CloneTree(0);

  if( !MCSample.Contains("TT") ){
    if(!IsDATA){
      newtree->SetBranchStatus("gen_*",0);
      newtree->SetBranchStatus("LHE_*",0);
//      newtree->SetBranchStatus("gen_weight",1); // for MCweight()
    }
  }

  triggers.clear();

  if(DataYear==2016){
    triggers = {
      "HLT_IsoMu24_v",
      "HLT_Mu50_v",
      "HLT_TkMu50_v",
      "HLT_Ele27_WPTight_Gsf_v",
      "HLT_Photon175_v",
      "HLT_Ele115_CaloIdVT_GsfTrkIdT_v",
    };
  }
  else if(DataYear==2017){
    triggers = {
      "HLT_IsoMu27_v",
      "HLT_Mu50_v",
      "HLT_OldMu100_v",
      "HLT_TkMu100_v",
      "HLT_Ele35_WPTight_Gsf_v",
      "HLT_Photon200_v",
      "HLT_Ele115_CaloIdVT_GsfTrkIdT_v",
    };
  }
  else if(DataYear==2018){
    triggers = {
      "HLT_IsoMu24_v",
      "HLT_Mu50_v",
      "HLT_OldMu100_v",
      "HLT_TkMu100_v",
      "HLT_Ele32_WPTight_Gsf_v",
      "HLT_Photon200_v",
      "HLT_Ele115_CaloIdVT_GsfTrkIdT_v",
    };
  }
  else{
    cout << "[SkimTree_boohft_calib::initializeAnalyzer] DataYear is wrong : " << DataYear << endl;
  }

  cout << "[SkimTree_boohft_calib::initializeAnalyzer] triggers to skim = " << endl;
  for(unsigned int i=0; i<triggers.size(); i++){
    cout << "[SkimTree_boohft_calib::initializeAnalyzer]   " << triggers.at(i) << endl;
  }

}

void SkimTree_boohft_calib::executeEvent(){

    vector<FatJet> allFatJets = puppiCorr->Correct(GetAllFatJets());

    //==== Skim 1 ) Triggers
    Event ev;
    ev.SetTrigger(*HLT_TriggerName);
    if(! (ev.PassTrigger(triggers)) ) return;

    //==== Skim 2) Leptons
    std::vector<Muon> muonsLooseNoIso = SelectMuons(GetAllMuons(), "POGMedium", 30., 2.4);
    std::vector<Muon> muonsLoose;
    for (unsigned int i=0 ; i < muonsLooseNoIso.size(); i++){
        Muon lepton = muonsLooseNoIso.at(i);
        if (lepton.RelIso() < 0.60){
            muonsLoose.push_back(lepton);
        }
    }

    std::vector<Electron> electronsLoose = SelectElectrons(GetAllElectrons(), "passMVAID_iso_WP90", 30., 2.5, true);

    std::vector<FatJet> fatjetsNoSDMass = SelectFatJets(puppiCorr->Correct(GetAllFatJets()), "tight", 200, 2.4);
    std::vector<FatJet> fatjets;
    for (unsigned int i=0; i < fatjetsNoSDMass.size(); i++){
        FatJet fatjet = fatjetsNoSDMass.at(i);
        if (fatjet.SDMass() > 50.0){
            fatjets.push_back(fatjet);
        }
    }
    fatjets = FatJetsVetoLeptonInside(fatjets, electronsLoose, muonsLoose, 0.4);

    if (fatjets.size() != 1) return;

    //==== Skim 4) Only fill in the survived events
    newtree->Fill();

}

void SkimTree_boohft_calib::executeEventFromParameter(AnalyzerParameter param){

}

SkimTree_boohft_calib::SkimTree_boohft_calib(){

  newtree = NULL;

}

SkimTree_boohft_calib::~SkimTree_boohft_calib(){

}

void SkimTree_boohft_calib::WriteHist(){

  outfile->mkdir("recoTree");
  outfile->cd("recoTree");
  newtree->Write();
  outfile->cd();

}


