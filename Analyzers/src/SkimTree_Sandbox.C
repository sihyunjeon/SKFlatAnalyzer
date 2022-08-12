#include "SkimTree_Sandbox.h"

void SkimTree_Sandbox::initializeAnalyzer(){

  outfile->cd();
  cout << "[SkimTree_Sandbox::initializeAnalyzer()] gDirectory = " << gDirectory->GetName() << endl;
  newtree = fChain->CloneTree(0);

  /*
  if(!IsDATA){
    newtree->SetBranchStatus("gen_*",0);
    newtree->SetBranchStatus("LHE_*",0);
    newtree->SetBranchStatus("gen_weight",1); // for MCweight()
  }*/

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
    cout << "[SkimTree_Sandbox::initializeAnalyzer] DataYear is wrong : " << DataYear << endl;
  }

  cout << "[SkimTree_Sandbox::initializeAnalyzer] triggers to skim = " << endl;
  for(unsigned int i=0; i<triggers.size(); i++){
    cout << "[SkimTree_Sandbox::initializeAnalyzer]   " << triggers.at(i) << endl;
  }

  LeptonPtCut = 35.;
  AK4JetPtCut = 20.;
  AK8JetPtCut = 150.;

}

void SkimTree_Sandbox::executeEvent(){

    //==== Skim 1 ) Triggers
    Event ev;
    ev.SetTrigger(*HLT_TriggerName);
    if(! (ev.PassTrigger(triggers)) ) return;

    //==== Skim 2) Leptons
    vector<Muon> muons = GetMuons("NOCUT", LeptonPtCut, 2.4);
    vector<Electron> electrons = GetElectrons("NOCUT", LeptonPtCut, 2.5);
    vector<Muon> tunep_muons = UseTunePMuon( GetAllMuons() );
    int n_tunep_muons = 0;
    for(unsigned int i=0; i<tunep_muons.size(); i++){
        if( tunep_muons.at(i).Pt() > LeptonPtCut ) n_tunep_muons++;
    }

    int n_muons = muons.size();
    int n_electrons = electrons.size();
    if (n_tunep_muons + n_muons + n_electrons == 0) return;

    //==== Skim 4) Only fill in the survived events
    newtree->Fill();

}

void SkimTree_Sandbox::executeEventFromParameter(AnalyzerParameter param){

}

SkimTree_Sandbox::SkimTree_Sandbox(){

  newtree = NULL;

}

SkimTree_Sandbox::~SkimTree_Sandbox(){

}

void SkimTree_Sandbox::WriteHist(){

  outfile->mkdir("recoTree");
  outfile->cd("recoTree");
  newtree->Write();
  outfile->cd();

}


