void GetNorm(TString year){
  TString dataName;
  if(year=="2016") dataName = "Fake_DoubleMuon";
  else if(year=="2017"||year=="2018") dataName = "Fake_Muon";
  TFile *_file0 = TFile::Open("/data6/Users/jihkim/SKFlatOutput/Run2UltraLegacy_v2/Fake/"+year+"/FR__Norm__/DATA/"+dataName+".root");
  TFile *_file1 = TFile::Open("/data6/Users/jihkim/SKFlatOutput/Run2UltraLegacy_v2/Fake/"+year+"/FR__Norm__/Fake_DYJets.root");
  TH1D* data_Mu3_HN = (TH1D*)_file0->Get("Z_Muon/DiLep_Mass_Mu3_HN");
  TH1D* MC_Mu3_HN = (TH1D*)_file1->Get("Z_Muon/DiLep_Mass_Mu3_HN");
  cout << data_Mu3_HN->Integral()/MC_Mu3_HN->Integral() << endl;
  TH1D* data_Mu8_HN = (TH1D*)_file0->Get("Z_Muon/DiLep_Mass_Mu8_HN");
  TH1D* MC_Mu8_HN = (TH1D*)_file1->Get("Z_Muon/DiLep_Mass_Mu8_HN");
  cout << data_Mu8_HN->Integral()/MC_Mu8_HN->Integral() << endl;
  TH1D* data_Mu17_HN = (TH1D*)_file0->Get("Z_Muon/DiLep_Mass_Mu17_HN");
  TH1D* MC_Mu17_HN = (TH1D*)_file1->Get("Z_Muon/DiLep_Mass_Mu17_HN");
  cout << data_Mu17_HN->Integral()/MC_Mu17_HN->Integral() << endl;
}
