{
TString filename = "/data6/Users/jihkim/SKFlatOutput/Run2Legacy_v4/ChargeFlip/2016/CFrate__/ChargeFlip_All.root";
TFile* f1 = new TFile(filename);

TString samplename = filename(filename.Last('/')+12,filename.Length());
samplename.ReplaceAll(".root","");

//gSystem->Exec("mkdir "+samplename);

vector<TString> User_ID;
//User_ID.push_back("HEEP_dZ_CF");
User_ID.push_back("HNTightV1");
//User_ID.push_back("HNMVATight");

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
    X_1.push_back((2*i+1)*(0.0005)); EX_1.push_back(0); 
    X_2.push_back((2*i+1)*(0.0005)); EX_2.push_back(0);
    X_3.push_back((2*i+1)*(0.0005)); EX_3.push_back(0);
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
  if(User_ID[i].Contains("HEEP")) gr1->GetXaxis()->SetRangeUser(0.,0.02);
  else gr1->GetXaxis()->SetRangeUser(0.,0.04);
  gr1->GetXaxis()->SetTitle("#scale[0.8]{1/p_{T} (GeV^{-1})}");
  gr1->GetXaxis()->SetTickLength(0.025);
  gr1->GetXaxis()->SetLabelSize(0.025);
  gr1->GetYaxis()->SetLabelSize(0.025);
  
  
  // Define fit function and range //
  
  //TF1 *gr1_fit1 = new TF1("gr1_fit1","[0]/(x+[1])+[2]",0.001,0.04);
  TF1 *gr1_fit1 = new TF1("gr1_fit1","expo",0.,0.003);
  TF1 *gr1_fit2 = new TF1("gr1_fit2","[0]/(x+[1])+[2]",0.003,0.015);
  TF1 *gr1_fit3 = new TF1("gr1_fit3","pol1",0.015,0.04);
  
  gr1_fit1->SetLineWidth(3);
  gr1_fit2->SetLineWidth(3);
  gr1_fit3->SetLineWidth(3);
  
  gr1_fit1->SetLineColor(kRed);
  gr1_fit2->SetLineColor(kGreen);
  gr1_fit3->SetLineColor(kBlue);
  
  cout << "//////////////////// Now fitting on EtaRegion1 ... ////////////////////" << endl;
 
  // Draw fitting and its uncertainties //
  
  gr1->Fit(gr1_fit1,"R");
  
  //TGraphErrors *gr1_fit1_err = new TGraphErrors(4);
  //for(int i=0; i<4; i++) gr1_fit1_err->SetPoint(i,0.001*i,0);
  //(TVirtualFitter::GetFitter())->GetConfidenceIntervals(gr1_fit1_err);
  //gr1_fit1_err->SetFillColor(4);
  //gr1_fit1_err->SetFillStyle(3001);
  //gr1_fit1_err->Draw("3 same");
  
  gr1->Fit(gr1_fit2,"R+");

  //TGraphErrors *gr1_fit2_err = new TGraphErrors(13);
  //for(int i=0; i<13; i++) gr1_fit2_err->SetPoint(i,0.003+0.001*i,0);
  //(TVirtualFitter::GetFitter())->GetConfidenceIntervals(gr1_fit2_err);
  //gr1_fit2_err->SetFillColor(4);
  //gr1_fit2_err->SetFillStyle(3001);
  //gr1_fit2_err->Draw("3 same");
  
  gr1->Fit(gr1_fit3,"R+");

  //TGraphErrors *gr1_fit3_err = new TGraphErrors(26);
  //for(int i=0; i<26; i++) gr1_fit3_err->SetPoint(i,0.015+0.001*i,0);
  //(TVirtualFitter::GetFitter())->GetConfidenceIntervals(gr1_fit3_err);
  //gr1_fit3_err->SetFillColor(4);
  //gr1_fit3_err->SetFillStyle(3001);
  //gr1_fit3_err->Draw("3 same");

  TLegend* gr1_legend = new TLegend(0.75,0.8,0.9,0.9);
  gr1_legend->AddEntry(gr1_fit1,"high pt","l");
  gr1_legend->AddEntry(gr1_fit2,"medium pt","l");
  gr1_legend->AddEntry(gr1_fit3,"low pt","l");
  gr1_legend->Draw();

/*	
  double Chisquare1 = gr1_fit1->GetChisquare();
  TString Chisquare1_t = Form("%f",Chisquare1);
  Chisquare1_t = Chisquare1_t(0,7);
  int ndf1 = gr1_fit1->GetNDF();
  TString ndf1_t = Form("%d",ndf1);
  double par1[3];
  gr1_fit1->GetParameters(par1);
  TString par1_0 = Form("%.10f",par1[0]);
  TString par1_1 = Form("%.10f",par1[1]);
  if(!par1_1.Contains("-")) par1_1 = "+"+par1_1;
  TString par1_2 = Form("%.10f",par1[2]);
  double rate1 = par1[0]/(0.001+par1[1])+par1[2];
  TString rate1_t = Form("%.10f",rate1);

  // draw the textbox
  TPaveText *pt1 = new TPaveText(0.55,0.8,0.9,0.9,"NDC");
  pt1->SetShadowColor(0);
  pt1->SetFillColor(0);
  pt1->AddText("#chi^{2}/ndf : "+Chisquare1_t+"/"+ndf1_t);
  pt1->AddText("Fit func : #frac{"+par1_0+"}{x"+par1_1+"}+"+par1_2);
  if(!User_ID[i].Contains("V1")) pt1->AddText("CF rate at 1000GeV : "+rate1_t);
  pt1->Draw();
*/


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
  if(User_ID[i].Contains("HEEP")) gr2->GetXaxis()->SetRangeUser(0.,0.02);
  else gr2->GetXaxis()->SetRangeUser(0.,0.04);
  gr2->GetXaxis()->SetTitle("#scale[0.8]{1/p_{T} (GeV^{-1})}");
  gr2->GetXaxis()->SetTickLength(0.025);
  gr2->GetXaxis()->SetLabelSize(0.025);
  gr2->GetYaxis()->SetLabelSize(0.025);
  
  
  
  //TF1 *gr2_fit1 = new TF1("gr2_fit1","[0]/(x+[1])+[2]",0.,0.003);
  TF1 *gr2_fit1 = new TF1("gr2_fit1","expo",0.,0.003);
  TF1 *gr2_fit2 = new TF1("gr2_fit2","[0]/(x+[1])+[2]",0.003,0.015);
  TF1 *gr2_fit3 = new TF1("gr2_fit3","pol1",0.015,0.04);
  
  gr2_fit1->SetLineWidth(3);
  gr2_fit2->SetLineWidth(3);
  gr2_fit3->SetLineWidth(3);
  
  gr2_fit1->SetLineColor(kRed);
  gr2_fit2->SetLineColor(kGreen);
  gr2_fit3->SetLineColor(kBlue);
  
  cout << endl << "//////////////////// Now fitting on EtaRegion2 ... ////////////////////" << endl;
  
  gr2->Fit(gr2_fit1,"R");
  
  //TGraphErrors *gr2_fit1_err = new TGraphErrors(4);
  //for(int i=0; i<4; i++) gr2_fit1_err->SetPoint(i,0.001*i,0);
  //(TVirtualFitter::GetFitter())->GetConfidenceIntervals(gr2_fit1_err);
  //gr2_fit1_err->SetFillColor(4);
  //gr2_fit1_err->SetFillStyle(3001);
  //gr2_fit1_err->Draw("3 same");
  
  gr2->Fit(gr2_fit2,"R+");

  //TGraphErrors *gr2_fit2_err = new TGraphErrors(13);
  //for(int i=0; i<13; i++) gr2_fit2_err->SetPoint(i,0.003+0.001*i,0);
  //(TVirtualFitter::GetFitter())->GetConfidenceIntervals(gr2_fit2_err);
  //gr2_fit2_err->SetFillColor(4);
  //gr2_fit2_err->SetFillStyle(3001);
  //gr2_fit2_err->Draw("3 same");
  
  gr2->Fit(gr2_fit3,"R+");

  //TGraphErrors *gr2_fit3_err = new TGraphErrors(26);
  //for(int i=0; i<26; i++) gr2_fit3_err->SetPoint(i,0.015+0.001*i,0);
  //(TVirtualFitter::GetFitter())->GetConfidenceIntervals(gr2_fit3_err);
  //gr2_fit3_err->SetFillColor(4);
  //gr2_fit3_err->SetFillStyle(3001);
  //gr2_fit3_err->Draw("3 same");

  TLegend* gr2_legend = new TLegend(0.75,0.8,0.9,0.9);
  gr2_legend->AddEntry(gr2_fit1,"high pt","l");
  gr2_legend->AddEntry(gr2_fit2,"medium pt","l");
  gr2_legend->AddEntry(gr2_fit3,"low pt","l");
  gr2_legend->Draw();
  
/*

  double Chisquare2 = gr2_fit1->GetChisquare();
  TString Chisquare2_t = Form("%f",Chisquare2);
  Chisquare2_t = Chisquare2_t(0,7);
  int ndf2 = gr2_fit1->GetNDF();
  TString ndf2_t = Form("%d",ndf2);
  double par2[3];
  gr2_fit1->GetParameters(par2);
  TString par2_0 = Form("%.10f",par2[0]);
  TString par2_1 = Form("%.10f",par2[1]);
  if(!par2_1.Contains("-")) par2_1 = "+"+par2_1;
  TString par2_2 = Form("%.10f",par2[2]);
  double rate2 = par2[0]/(0.001+par2[1])+par2[2];
  TString rate2_t = Form("%.10f",rate2);

  // draw the textbox
  TPaveText *pt2 = new TPaveText(0.55,0.8,0.9,0.9,"NDC");
  pt2->SetShadowColor(0);
  pt2->SetFillColor(0);
  pt2->AddText("#chi^{2}/ndf : "+Chisquare2_t+"/"+ndf2_t);
  pt2->AddText("Fit func : #frac{"+par2_0+"}{x"+par2_1+"}+"+par2_2);
  pt2->AddText("CF rate at 1000GeV : "+rate2_t);
  pt2->Draw();

*/

  
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
  if(User_ID[i].Contains("HEEP")) gr3->GetXaxis()->SetRangeUser(0.,0.02);
  else gr3->GetXaxis()->SetRangeUser(0.,0.04);
  gr3->GetXaxis()->SetTitle("#scale[0.8]{1/p_{T} (GeV^{-1})}");
  gr3->GetXaxis()->SetTickLength(0.025);
  gr3->GetXaxis()->SetLabelSize(0.025);
  gr3->GetYaxis()->SetLabelSize(0.025);
  
  
  TF1 *gr3_fit1 = new TF1("gr3_fit1","[0]/(x+[1])+[2]",0.,0.04);
  //TF1 *gr3_fit1 = new TF1("gr3_fit1","expo",0.,0.002);
  //TF1 *gr3_fit2 = new TF1("gr3_fit2","[0]/(x+[1])+[2]",0.002,0.015);
  //TF1 *gr3_fit3 = new TF1("gr3_fit3","pol1",0.015,0.04);
  
  gr3_fit1->SetLineWidth(3);
  //gr3_fit2->SetLineWidth(3);
  //gr3_fit3->SetLineWidth(3);
  
  gr3_fit1->SetLineColor(kRed);
  //gr3_fit2->SetLineColor(kGreen);
  //gr3_fit3->SetLineColor(kBlue);
  
  cout << endl << "//////////////////// Now fitting on EtaRegion3 ... ////////////////////" << endl;
  
  gr3->Fit(gr3_fit1,"R");
  
  //TGraphErrors *gr3_fit1_err = new TGraphErrors(5);
  //for(int i=0; i<5; i++) gr3_fit1_err->SetPoint(i,0.001*i,0);
  //(TVirtualFitter::GetFitter())->GetConfidenceIntervals(gr3_fit1_err);
  //gr3_fit1_err->SetFillColor(4);
  //gr3_fit1_err->SetFillStyle(3001);
  //gr3_fit1_err->Draw("3 same");
  
  //gr3->Fit(gr3_fit2,"R+");

  //TGraphErrors *gr3_fit2_err = new TGraphErrors(13);
  //for(int i=0; i<13; i++) gr3_fit2_err->SetPoint(i,0.003+0.001*i,0);
  //(TVirtualFitter::GetFitter())->GetConfidenceIntervals(gr3_fit2_err);
  //gr3_fit2_err->SetFillColor(4);
  //gr3_fit2_err->SetFillStyle(3001);
  //gr3_fit2_err->Draw("3 same");
  
  //gr3->Fit(gr3_fit3,"R+");

  //TGraphErrors *gr3_fit3_err = new TGraphErrors(26);
  //for(int i=0; i<26; i++) gr3_fit3_err->SetPoint(i,0.015+0.001*i,0);
  //(TVirtualFitter::GetFitter())->GetConfidenceIntervals(gr3_fit3_err);
  //gr3_fit3_err->SetFillColor(4);
  //gr3_fit3_err->SetFillStyle(3001);
  //gr3_fit3_err->Draw("3 same");
  
  double Chisquare3 = gr3_fit1->GetChisquare();
  TString Chisquare3_t = Form("%f",Chisquare3);
  Chisquare3_t = Chisquare3_t(0,7);
  int ndf3 = gr3_fit1->GetNDF();
  TString ndf3_t = Form("%d",ndf3);
  double par3[3];
  gr3_fit1->GetParameters(par3);
  TString par3_0 = Form("%.10f",par3[0]);
  TString par3_1 = Form("%.10f",par3[1]);
  if(!par3_1.Contains("-")) par3_1 = "+"+par3_1;
  TString par3_2 = Form("%.10f",par3[2]);
  double rate3 = par3[0]/(0.+par3[1])+par3[2];
  TString rate3_t = Form("%.10f",rate3);

  // draw the textbox
  TPaveText *pt3 = new TPaveText(0.55,0.8,0.9,0.9,"NDC");
  pt3->SetShadowColor(0);
  pt3->SetFillColor(0);
  pt3->AddText("#chi^{2}/ndf : "+Chisquare3_t+"/"+ndf3_t);
  pt3->AddText("Fit func : #frac{"+par3_0+"}{x"+par3_1+"}+"+par3_2);
  pt3->AddText("CF rate at inf GeV : "+rate3_t);
  pt3->Draw();


  //c1->SaveAs(samplename+"/"+User_ID.at(i)+"_Fit_EtaRegion1.pdf");
  //c2->SaveAs(samplename+"/"+User_ID.at(i)+"_Fit_EtaRegion2.pdf");
  //c3->SaveAs(samplename+"/"+User_ID.at(i)+"_Fit_EtaRegion3.pdf");

  //c1->SaveAs(samplename+"/"+User_ID.at(i)+"_Fit_EtaRegion1.png");
  //c2->SaveAs(samplename+"/"+User_ID.at(i)+"_Fit_EtaRegion2.png");
  //c3->SaveAs(samplename+"/"+User_ID.at(i)+"_Fit_EtaRegion3.png");

  c1->SaveAs("Fit_Test3_EtaRegion1.png");
  //c2->SaveAs("Fit_EtaRegion2.png");
  //c3->SaveAs("Fit_EtaRegion3.png");

  //c1->SaveAs(samplename+"/"+User_ID.at(i)+"_FitErrorBand_EtaRegion1.pdf");
  //c2->SaveAs(samplename+"/"+User_ID.at(i)+"_FitErrorBand_EtaRegion2.pdf");
  //c3->SaveAs(samplename+"/"+User_ID.at(i)+"_FitErrorBand_EtaRegion3.pdf");

  //c1->SaveAs(samplename+"/"+User_ID.at(i)+"_FitErrorBand_EtaRegion1.png");
  //c2->SaveAs(samplename+"/"+User_ID.at(i)+"_FitErrorBand_EtaRegion2.png");
  //c3->SaveAs(samplename+"/"+User_ID.at(i)+"_FitErrorBand_EtaRegion3.png");

}

}
