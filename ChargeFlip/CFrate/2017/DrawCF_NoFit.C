{
TString filename = "/data6/Users/jihkim/SKFlatOutput/Run2Legacy_v4/ChargeFlip/2017/CFrate__/ChargeFlip_All.root";
TFile* f1 = new TFile(filename);

TString samplename = filename(filename.Last('/')+12,filename.Length());
samplename.ReplaceAll(".root","");

gSystem->Exec("mkdir "+samplename);

vector<TString> User_ID;
//User_ID.push_back("HNTight2016");
//User_ID.push_back("HEID");
User_ID.push_back("HNTightV1");

for(unsigned int i=0; i<User_ID.size(); i++){

  TH1D* h1 = (TH1D*)f1->Get(User_ID.at(i)+"/CFrate/EtaRegion1_Denom");
  TH1D* h2 = (TH1D*)f1->Get(User_ID.at(i)+"/CFrate/EtaRegion1_Num");
  TH1D* h3 = (TH1D*)f1->Get(User_ID.at(i)+"/CFrate/EtaRegion2_Denom");
  TH1D* h4 = (TH1D*)f1->Get(User_ID.at(i)+"/CFrate/EtaRegion2_Num");
  TH1D* h5 = (TH1D*)f1->Get(User_ID.at(i)+"/CFrate/EtaRegion3_Denom");
  TH1D* h6 = (TH1D*)f1->Get(User_ID.at(i)+"/CFrate/EtaRegion3_Num");
  
  // Let's use vector instead of array, to remove zero bins and nan bins //
  
  vector<double> X_1, EX_1, X_2, EX_2, X_3, EX_3;
  for (int i=0; i<40; i++) {
    X_1.push_back((2*i+1)*(0.04/80.)); EX_1.push_back(0.04/80.); 
    X_2.push_back((2*i+1)*(0.04/80.)); EX_2.push_back(0.04/80.);
    X_3.push_back((2*i+1)*(0.04/80.)); EX_3.push_back(0.04/80.);
  }
  vector<double> Y_1, EY_1, Y_2, EY_2, Y_3, EY_3;
  for (int i=0; i<40; i++) {
    Y_1.push_back(h2->GetBinContent(i+1)/h1->GetBinContent(i+1));
    EY_1.push_back(Y_1[i]*(sqrt(pow(h2->GetBinError(i+1)/h2->GetBinContent(i+1),2)+pow(h1->GetBinError(i+1)/h1->GetBinContent(i+1),2))));
    Y_2.push_back(h4->GetBinContent(i+1)/h3->GetBinContent(i+1));
    EY_2.push_back(Y_2[i]*(sqrt(pow(h4->GetBinError(i+1)/h4->GetBinContent(i+1),2)+pow(h3->GetBinError(i+1)/h3->GetBinContent(i+1),2))));
    Y_3.push_back(h6->GetBinContent(i+1)/h5->GetBinContent(i+1));
    EY_3.push_back(Y_3[i]*(sqrt(pow(h6->GetBinError(i+1)/h6->GetBinContent(i+1),2)+pow(h5->GetBinError(i+1)/h5->GetBinContent(i+1),2))));
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
  for (int i=0; i<X_2.size();) {
    if ( (Y_2.at(i) == 0) || (isnan(Y_2.at(i)) != 0) ) {
      X_2.erase(X_2.begin()+i);
      EX_2.erase(EX_2.begin()+i);
      Y_2.erase(Y_2.begin()+i);
      EY_2.erase(EY_2.begin()+i);
    }
    else i++;
  }
  for (int i=0; i<X_3.size();) {
    if ( (Y_3.at(i) == 0) || (isnan(Y_3.at(i)) != 0) ) {
      X_3.erase(X_3.begin()+i);
      EX_3.erase(EX_3.begin()+i);
      Y_3.erase(Y_3.begin()+i);
      EY_3.erase(EY_3.begin()+i);
    }
    else i++;
  }
  
  
  // Draw the plots //
  
  TCanvas* c1 = new TCanvas("c1","ChargeFlip_EtaRegion1 ("+User_ID.at(i)+")",200,200,900,800);
  TCanvas* c2 = new TCanvas("c2","ChargeFlip_EtaRegion2 ("+User_ID.at(i)+")",250,150,900,800);
  TCanvas* c3 = new TCanvas("c3","ChargeFlip_EtaRegion3 ("+User_ID.at(i)+")",300,100,900,800);
  
  c1->cd();
  
  TGraphErrors* gr1 = new TGraphErrors(X_1.size(),&X_1[0],&Y_1[0],&EX_1[0],&EY_1[0]);
  gr1->SetMarkerStyle(20);
  //gr1->SetMarkerSize(0.8);
  //gr1->SetMarkerColor(kMagenta+2);
  gr1->SetLineColor(15);
  gr1->SetTitle("ChargeFlip_|#eta|<0.8 ("+User_ID.at(i)+")");
  gr1->SetMinimum(0.);
  gr1->Draw("ZAP"); //Z : do not draw small horizontal/vertical lines the end of the error bars
  gr1->GetXaxis()->SetRangeUser(0.,0.04);
  gr1->GetXaxis()->SetTitle("#scale[0.8]{1/p_{T} (GeV^{-1})}");
  gr1->GetXaxis()->SetTickLength(0.025);
  gr1->GetXaxis()->SetLabelSize(0.025);
  gr1->GetYaxis()->SetLabelSize(0.025);
  
  
  // Done and repeat for EtaRegion2, 3 //
  
  c2->cd();
  
  TGraphErrors* gr2 = new TGraphErrors(X_2.size(),&X_2[0],&Y_2[0],&EX_2[0],&EY_2[0]);
  gr2->SetMarkerStyle(20);
  //gr2->SetMarkerSize(0.8);
  //gr2->SetMarkerColor(kMagenta+2);
  //gr2->SetMarkerColor(kBlue-4);
  gr2->SetLineColor(15);
  gr2->SetTitle("ChargeFlip_0.8#leq|#eta|<1.4442 ("+User_ID.at(i)+")");
  gr2->SetMinimum(0.);
  gr2->Draw("ZAP");
  gr2->GetXaxis()->SetRangeUser(0.,0.04);
  gr2->GetXaxis()->SetTitle("#scale[0.8]{1/p_{T} (GeV^{-1})}");
  gr2->GetXaxis()->SetTickLength(0.025);
  gr2->GetXaxis()->SetLabelSize(0.025);
  gr2->GetYaxis()->SetLabelSize(0.025);
  
  
  
  c3->cd();
  
  TGraphErrors* gr3 = new TGraphErrors(X_3.size(),&X_3[0],&Y_3[0],&EX_3[0],&EY_3[0]);
  gr3->SetMarkerStyle(20);
  //gr3->SetMarkerSize(0.8);
  //gr3->SetMarkerColor(kMagenta+2);
  //gr3->SetMarkerColor(kGreen+3);
  gr3->SetLineColor(15);
  gr3->SetTitle("ChargeFlip_1.556#leq|#eta|<2.5 ("+User_ID.at(i)+")");
  gr3->SetMinimum(0.);
  gr3->Draw("ZAP");
  gr3->GetXaxis()->SetRangeUser(0.,0.04);
  gr3->GetXaxis()->SetTitle("#scale[0.8]{1/p_{T} (GeV^{-1})}");
  gr3->GetXaxis()->SetTickLength(0.025);
  gr3->GetXaxis()->SetLabelSize(0.025);
  gr3->GetYaxis()->SetLabelSize(0.025);
  
  
  //c1->SaveAs(samplename+"/"+User_ID.at(i)+"_NoFit_EtaRegion1.pdf");
  //c2->SaveAs(samplename+"/"+User_ID.at(i)+"_NoFit_EtaRegion2.pdf");
  //c3->SaveAs(samplename+"/"+User_ID.at(i)+"_NoFit_EtaRegion3.pdf");

  c1->SaveAs(samplename+"/"+User_ID.at(i)+"_NoFit_EtaRegion1.png");
  c2->SaveAs(samplename+"/"+User_ID.at(i)+"_NoFit_EtaRegion2.png");
  c3->SaveAs(samplename+"/"+User_ID.at(i)+"_NoFit_EtaRegion3.png");

}

}
