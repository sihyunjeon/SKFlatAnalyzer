{
TString filename = "/data6/Users/jihkim/SKFlatOutput/Run2Legacy_v4/ChargeFlip/2016/CFrate__/ChargeFlip_All.root";
//TString filename = "/data6/Users/jihkim/SKFlatOutput/Run2Legacy_v4/ChargeFlip/2016/CFrate__/ChargeFlip_DYJets_MG.root";
//TString filename = "/data6/Users/jihkim/SKFlatOutput/Run2Legacy_v4/ChargeFlip/2016/CFrate__/ChargeFlip_SkimTree_Dilepton_DYJets.root";
//TString filename = "/data6/Users/jihkim/SKFlatOutput/Run2Legacy_v4/ChargeFlip/2016/CFrate__/ChargeFlip_SkimTree_Dilepton_TTLL_powheg.root";
//TString filename = "/data6/Users/jihkim/SKFlatOutput/Run2Legacy_v4/ChargeFlip/2016/CFrate__/ChargeFlip_TTLJ_powheg.root";
//TString filename = "/data6/Users/jihkim/SKFlatOutput/Run2Legacy_v4/ChargeFlip/2016/CFrate__/ChargeFlip_SkimTree_Dilepton_DYJets_M.root";
//TString filename = "/data6/Users/jihkim/SKFlatOutput/Run2Legacy_v4/ChargeFlip/2016/CFrate__/ChargeFlip_SkimTree_Dilepton_DYJets_Pt.root";
//TString filename = "/data6/Users/jihkim/SKFlatOutput/Run2Legacy_v4/ChargeFlip/2016/CFrate__/ChargeFlip_DYJets_MG_HT.root";
TFile* f1 = new TFile(filename);

TString samplename = filename(filename.Last('/')+12,filename.Length());
samplename.ReplaceAll(".root","");

//gSystem->Exec("mkdir -p "+samplename);

vector<TString> User_ID;
//User_ID.push_back("HEEP_dZ_CF");
//User_ID.push_back("HNMVATight");
User_ID.push_back("HNTightV1");

for(unsigned int i=0; i<User_ID.size(); i++){

  TH1D* h1 = (TH1D*)f1->Get(User_ID.at(i)+"/CFrate_Eta/Denom");
  TH1D* h2 = (TH1D*)f1->Get(User_ID.at(i)+"/CFrate_Eta/Num");
  
  // Let's use vector instead of array, to remove zero bins and nan bins //
  
  vector<double> X_1, EX_1;
  for (int i=0; i<50; i++) {
    X_1.push_back(-2.5+(2*i+1)*(2.5/50.)); EX_1.push_back(2.5/50.); 
  }
  vector<double> Y_1, EY_1;
  for (int i=0; i<50; i++) {
    Y_1.push_back(h2->GetBinContent(i+1)/h1->GetBinContent(i+1));
    EY_1.push_back(Y_1[i]*(sqrt(pow(h2->GetBinError(i+1)/h2->GetBinContent(i+1),2)+pow(h1->GetBinError(i+1)/h1->GetBinContent(i+1),2))));
  }
  
  for (int i=0; i<X_1.size();) {
    if ( (Y_1.at(i) == 0) || (isnan(Y_1.at(i)) != 0) ) {
      X_1.erase(X_1.begin()+i);
      EX_1.erase(EX_1.begin()+i);
      Y_1.erase(Y_1.begin()+i);
      EY_1.erase(EY_1.begin()+i);
    }
    else i++;
  }
  
  
  // Draw the plots //
  
  //TCanvas* c1 = new TCanvas("c1","ChargeFlip_Eta ("+User_ID.at(i)+")",200,200,900,800);
  TCanvas* c1 = new TCanvas("c1","ChargeFlip_Eta",200,200,900,800);
  
  c1->cd();
  //c1->SetLogy();
  
  TGraphErrors* gr1 = new TGraphErrors(X_1.size(),&X_1[0],&Y_1[0],&EX_1[0],&EY_1[0]);
  gr1->SetMarkerStyle(20);
  //gr1->SetMarkerSize(0.8);
  //gr1->SetMarkerColor(kMagenta+2);
  gr1->SetLineColor(15);
  gr1->SetTitle("ChargeFlip_#eta");
  gr1->SetMinimum(0.);
  gr1->Draw("ZAP"); //Z : do not draw small horizontal/vertical lines the end of the error bars
  gr1->GetXaxis()->SetRangeUser(-2.5,2.5);
  gr1->GetXaxis()->SetTitle("#eta");
  gr1->GetXaxis()->SetTickLength(0.025);
  gr1->GetXaxis()->SetLabelSize(0.025);
  gr1->GetYaxis()->SetLabelSize(0.025);
  
  
  //c1->SaveAs("All_250/"+samplename+"_"+User_ID.at(i)+"_NoFit_EtaRegion1.png");

  //c1->SaveAs(samplename+"/"+User_ID.at(i)+"_NoFit_EtaRegion1.png");

  //c1->SaveAs(samplename+"/"+User_ID.at(i)+"_NoFit_EtaRegion1_logY.png");

}

}
