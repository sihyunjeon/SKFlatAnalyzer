void Chi2Test(){

  //TString filename = "/data6/Users/jihkim/SKFlatOutput/Run2Legacy_v4/ChargeFlip/2016/ClosureTest__/ChargeFlip_DYJets.root";
  TString filename = "/data6/Users/jihkim/SKFlatOutput/Run2Legacy_v4/ChargeFlip/2016/ClosureTest__/ChargeFlip_All.root";
  //TString filename = "/data6/Users/jihkim/SKFlatOutput/Run2Legacy_v4/ChargeFlip/2016/ClosureTest__/ChargeFlip_DYonly.root";
  TFile* f1 = new TFile(filename);
  
  TString samplename = filename(filename.Last('/')+12,filename.Length());
  samplename.ReplaceAll(".root","");
  
  vector<TString> User_ID;
  //User_ID.push_back("HNTight2016");
  //User_ID.push_back("HEID");
  User_ID.push_back("HNTightV1");
  
  for(unsigned int i=0; i<User_ID.size(); i++){
  
    //TH1D* h0 = (TH1D*)f1->Get(User_ID.at(i)+"/ClosureTest/ZMass_SS");
    TH1D* h0 = (TH1D*)f1->Get(User_ID.at(i)+"/ClosureTest/ZMass_prmpt_SS");
  
    // Chi2Test //
  
    TString s = User_ID.at(i)+"/ClosureTest/ZMass_OS_CFweighted_shifted_";
  
    cout << "!!User_ID : " << User_ID.at(i) << "!!" << endl;
  
    for(int i=0; i<50; i++){
      TH1D* h_test = (TH1D*)f1->Get(s+TString::Itoa((i+1),10));
      cout << "Energy shifted " << (i+1)*0.1 << "%:" << endl;
      h0->Chi2Test(h_test,"UW P");
    }
  
    cout << "// Chi2Test ended //" << endl;
    cout << endl;
  
  }

}
