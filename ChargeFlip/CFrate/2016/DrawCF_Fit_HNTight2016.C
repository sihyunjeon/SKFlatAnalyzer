{
TString filename = "/data6/Users/jihkim/SKFlatOutput/Run2Legacy_v3/ChargeFlip/2016/CFrate__/ChargeFlip_DYJets_TTLL.root";
TFile* f1 = new TFile(filename);

TString samplename = filename(filename.Last('/')+12,filename.Length());
samplename.ReplaceAll(".root","");

gSystem->Exec("mkdir "+samplename);

vector<TString> User_ID;
User_ID.push_back("HNTight2016");
//User_ID.push_back("HEID");

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
  TCanvas* c2 = new TCanvas("c2","ChargeFlip_EtaRegion1 ("+User_ID.at(i)+")",250,150,900,800);
  TCanvas* c3 = new TCanvas("c3","ChargeFlip_EtaRegion1 ("+User_ID.at(i)+")",300,100,900,800);
  
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
  
  
  // Define fit function and range //
  
  TF1 *gr1_fit1 = new TF1("gr1_fit1","pol1",0,0.0075);
  TF1 *gr1_fit2 = new TF1("gr1_fit2","pol1",0.0075,0.0155);
  TF1 *gr1_fit3 = new TF1("gr1_fit3","pol1",0.0155,0.041);
  
  gr1_fit1->SetLineWidth(3);
  gr1_fit2->SetLineWidth(3);
  gr1_fit3->SetLineWidth(3);
  
  gr1_fit1->SetLineColor(4);
  gr1_fit2->SetLineColor(4);
  gr1_fit3->SetLineColor(4);
  
  cout << "//////////////////// Now fitting on EtaRegion1 ... ////////////////////" << endl;
 
  // Draw fitting and its uncertainties //
  
  gr1->Fit(gr1_fit1,"R");
  
  //TGraphErrors *gr1_fit1_err = new TGraphErrors(16);
  //for(int i=0; i<16; i++) gr1_fit1_err->SetPoint(i,0.0005*i,0);
  //(TVirtualFitter::GetFitter())->GetConfidenceIntervals(gr1_fit1_err);
  //gr1_fit1_err->SetFillColor(4);
  //gr1_fit1_err->SetFillStyle(3001);
  //gr1_fit1_err->Draw("3 same");
  
  gr1->Fit(gr1_fit2,"R+");

  //TGraphErrors *gr1_fit2_err = new TGraphErrors(17);
  //for(int i=0; i<17; i++) gr1_fit2_err->SetPoint(i,0.0075+0.0005*i,0);
  //(TVirtualFitter::GetFitter())->GetConfidenceIntervals(gr1_fit2_err);
  //gr1_fit2_err->SetFillColor(4);
  //gr1_fit2_err->SetFillStyle(3001);
  //gr1_fit2_err->Draw("3 same");
  
  gr1->Fit(gr1_fit3,"R+");

  //TGraphErrors *gr1_fit3_err = new TGraphErrors(51);
  //for(int i=0; i<51; i++) gr1_fit3_err->SetPoint(i,0.0155+0.0005*i,0);
  //(TVirtualFitter::GetFitter())->GetConfidenceIntervals(gr1_fit3_err);
  //gr1_fit3_err->SetFillColor(4);
  //gr1_fit3_err->SetFillStyle(3001);
  //gr1_fit3_err->Draw("3 same");
 
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
  
  
  
  TF1 *gr2_fit1 = new TF1("gr2_fit1","pol1",0,0.0055);
  TF1 *gr2_fit2 = new TF1("gr2_fit2","pol1",0.0055,0.0155);
  TF1 *gr2_fit3 = new TF1("gr2_fit3","pol1",0.0155,0.04);
  
  gr2_fit1->SetLineWidth(3);
  gr2_fit2->SetLineWidth(3);
  gr2_fit3->SetLineWidth(3);
  
  gr2_fit1->SetLineColor(4);
  gr2_fit2->SetLineColor(4);
  gr2_fit3->SetLineColor(4);
  
  cout << endl << "//////////////////// Now fitting on EtaRegion2 ... ////////////////////" << endl;
  
  gr2->Fit(gr2_fit1,"R");
  
  //TGraphErrors *gr2_fit1_err = new TGraphErrors(12);
  //for(int i=0; i<12; i++) gr2_fit1_err->SetPoint(i,0.0005*i,0);
  //(TVirtualFitter::GetFitter())->GetConfidenceIntervals(gr2_fit1_err);
  //gr2_fit1_err->SetFillColor(4);
  //gr2_fit1_err->SetFillStyle(3001);
  //gr2_fit1_err->Draw("3 same");
  
  gr2->Fit(gr2_fit2,"R+");

  //TGraphErrors *gr2_fit2_err = new TGraphErrors(21);
  //for(int i=0; i<21; i++) gr2_fit2_err->SetPoint(i,0.0055+0.0005*i,0);
  //(TVirtualFitter::GetFitter())->GetConfidenceIntervals(gr2_fit2_err);
  //gr2_fit2_err->SetFillColor(4);
  //gr2_fit2_err->SetFillStyle(3001);
  //gr2_fit2_err->Draw("3 same");
  
  gr2->Fit(gr2_fit3,"R+");

  //TGraphErrors *gr2_fit3_err = new TGraphErrors(54);
  //for(int i=0; i<54; i++) gr2_fit3_err->SetPoint(i,0.0155+0.0005*i,0);
  //(TVirtualFitter::GetFitter())->GetConfidenceIntervals(gr2_fit3_err);
  //gr2_fit3_err->SetFillColor(4);
  //gr2_fit3_err->SetFillStyle(3001);
  //gr2_fit3_err->Draw("3 same");
  

  
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
  
  
  TF1 *gr3_fit1 = new TF1("gr3_fit1","pol1",0,0.010);
  TF1 *gr3_fit2 = new TF1("gr3_fit2","pol1",0.010,0.019);
  TF1 *gr3_fit3 = new TF1("gr3_fit3","pol1",0.019,0.04);
  
  gr3_fit1->SetLineWidth(3);
  gr3_fit2->SetLineWidth(3);
  gr3_fit3->SetLineWidth(3);
  
  gr3_fit1->SetLineColor(4);
  gr3_fit2->SetLineColor(4);
  gr3_fit3->SetLineColor(4);
  
  cout << endl << "//////////////////// Now fitting on EtaRegion3 ... ////////////////////" << endl;
  
  gr3->Fit(gr3_fit1,"R");
  
  //TGraphErrors *gr3_fit1_err = new TGraphErrors(11);
  //for(int i=0; i<11; i++) gr3_fit1_err->SetPoint(i,0.001*i,0);
  //(TVirtualFitter::GetFitter())->GetConfidenceIntervals(gr3_fit1_err);
  //gr3_fit1_err->SetFillColor(4);
  //gr3_fit1_err->SetFillStyle(3001);
  //gr3_fit1_err->Draw("3 same");
  
  gr3->Fit(gr3_fit2,"R+");

  //TGraphErrors *gr3_fit2_err = new TGraphErrors(10);
  //for(int i=0; i<10; i++) gr3_fit2_err->SetPoint(i,0.01+0.001*i,0);
  //(TVirtualFitter::GetFitter())->GetConfidenceIntervals(gr3_fit2_err);
  //gr3_fit2_err->SetFillColor(4);
  //gr3_fit2_err->SetFillStyle(3001);
  //gr3_fit2_err->Draw("3 same");
  
  gr3->Fit(gr3_fit3,"R+");

  //TGraphErrors *gr3_fit3_err = new TGraphErrors(23);
  //for(int i=0; i<23; i++) gr3_fit3_err->SetPoint(i,0.019+0.001*i,0);
  //(TVirtualFitter::GetFitter())->GetConfidenceIntervals(gr3_fit3_err);
  //gr3_fit3_err->SetFillColor(4);
  //gr3_fit3_err->SetFillStyle(3001);
  //gr3_fit3_err->Draw("3 same");
  
  

  //c1->SaveAs(samplename+"/"+User_ID.at(i)+"_Fit_EtaRegion1.pdf");
  //c2->SaveAs(samplename+"/"+User_ID.at(i)+"_Fit_EtaRegion2.pdf");
  //c3->SaveAs(samplename+"/"+User_ID.at(i)+"_Fit_EtaRegion3.pdf");

  //c1->SaveAs(samplename+"/"+User_ID.at(i)+"_Fit_EtaRegion1.png");
  //c2->SaveAs(samplename+"/"+User_ID.at(i)+"_Fit_EtaRegion2.png");
  //c3->SaveAs(samplename+"/"+User_ID.at(i)+"_Fit_EtaRegion3.png");

  //c1->SaveAs(samplename+"/"+User_ID.at(i)+"_FitErrorBand_EtaRegion1.pdf");
  //c2->SaveAs(samplename+"/"+User_ID.at(i)+"_FitErrorBand_EtaRegion2.pdf");
  //c3->SaveAs(samplename+"/"+User_ID.at(i)+"_FitErrorBand_EtaRegion3.pdf");

  //c1->SaveAs(samplename+"/"+User_ID.at(i)+"_FitErrorBand_EtaRegion1.png");
  //c2->SaveAs(samplename+"/"+User_ID.at(i)+"_FitErrorBand_EtaRegion2.png");
  //c3->SaveAs(samplename+"/"+User_ID.at(i)+"_FitErrorBand_EtaRegion3.png");

}

}
