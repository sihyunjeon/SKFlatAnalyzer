#include "SkimTree_SingleLepton.h"

void SkimTree_SingleLepton::initializeAnalyzer(){

  outfile->cd();
  cout << "[SkimTree_SingleLepton::initializeAnalyzer()] gDirectory = " << gDirectory->GetName() << endl;
  newtree = fChain->CloneTree(0);

 
  if(!IsDATA){
    newtree->SetBranchStatus("gen_*",0);
    newtree->SetBranchStatus("LHE_*",0);
    newtree->SetBranchStatus("gen_weight",1); // for MCweight()
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
    cout << "[SkimTree_SingleLepton::initializeAnalyzer] DataYear is wrong : " << DataYear << endl;
  }

  cout << "[SkimTree_SingleLepton::initializeAnalyzer] triggers to skim = " << endl;
  for(unsigned int i=0; i<triggers.size(); i++){
    cout << "[SkimTree_SingleLepton::initializeAnalyzer]   " << triggers.at(i) << endl;
  }

}

void SkimTree_SingleLepton::executeEvent(){

    //==== Skim 1 ) Triggers
    Event ev;
    ev.SetTrigger(*HLT_TriggerName);
    if(! (ev.PassTrigger(triggers)) ) return;

    //==== Skim 4) Only fill in the survived events
    newtree->Fill();

}

void SkimTree_SingleLepton::executeEventFromParameter(AnalyzerParameter param){

}

SkimTree_SingleLepton::SkimTree_SingleLepton(){

  newtree = NULL;

}

SkimTree_SingleLepton::~SkimTree_SingleLepton(){

}

void SkimTree_SingleLepton::WriteHist(){

  outfile->mkdir("recoTree");
  outfile->cd("recoTree");
  newtree->Write();
  outfile->cd();

}


