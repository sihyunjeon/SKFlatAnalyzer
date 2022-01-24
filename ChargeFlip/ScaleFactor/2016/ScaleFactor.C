double pol3(double *x, double *par){
  return par[0] + par[1]*x[0] + par[2]*x[0]*x[0] + par[3]*x[0]*x[0]*x[0];
}

double pol1(double *x, double *par){
  return par[0] + par[1]*x[0];
}

double expo(double *x, double *par){
  return exp(par[0] + par[1]*x[0]);
}

double gaus(double *x, double *par){
  return par[0]*exp(-0.5*pow((x[0]-par[1])/par[2],2));
}

double BW(double *x, double *par){
  return par[0]*par[1]/((x[0]+par[2])*(x[0]+par[2])+(0.5*par[1])*(0.5*par[1]));
}

double gaus_pol1(double *x, double *par){
  return gaus(x,par) + pol1(x,&par[3]);
}

double gaus_pol3(double *x, double *par){
  return gaus(x,par) + pol3(x,&par[3]);
}

double gaus_expo(double *x, double *par){
  return gaus(x,par) + expo(x,&par[3]);
}

double BW_pol1(double *x, double *par){
  return BW(x,par) + pol1(x,&par[3]);
}

double BW_pol3(double *x, double *par){
  return BW(x,par) + pol3(x,&par[3]);
}

double BW_expo(double *x, double *par){
  return BW(x,par) + expo(x,&par[3]);
}

void ScaleFactor(TString id, TString EtaRegion, TString fit, int Syst = 0, TString SaveAs = "n"){ // BB, BE, EE

  TString X = ""; //energy shift
  if(id=="HEID") X = "1.3%";
  else if(id=="HNTightV1") X = "1.0%";
  else if(id=="HNTight2016") X = "1.2%";
  
  int MllLeft = 60; if(Syst==3) MllLeft = 80; else if(Syst==4) MllLeft = 70;
  int MllRight = 120; if(Syst==3) MllRight = 100; else if(Syst==4) MllRight = 110;
  int NBin = 30; if(Syst==5) NBin = 25; else if(Syst==6) NBin = 35;
  //double err = 0.5; if(Syst==3||Syst==4||Syst==5||Syst==6) err = 1.*(MllRight-MllLeft)/NBin/2.; // if NBin is fixed at 40, then err changes in both Syst 3 and 4
  double err = 1.*(MllRight-MllLeft)/NBin/2.; // if NBin is fixed at 40, then err changes in both Syst 3 and 4
  
  std::map<int, TString> RunSyst;
  RunSyst[0] = "";
  RunSyst[1] = "_Syst_MinPtDown";
  RunSyst[2] = "_Syst_MinPtUp";
  RunSyst[3] = "_Syst_MllRangeDown";
  RunSyst[4] = "_Syst_MllRangeUp";
  RunSyst[5] = "_Syst_NBinDown";
  RunSyst[6] = "_Syst_NBinUp";
  
  
  //TString filename = "/data6/Users/jihkim/SKFlatOutput/Run2Legacy_v3/ChargeFlip/2016/ScaleFactor__RunSyst__/DATA/ChargeFlip_DoubleEG_total_NBin40_DYTTLLCF.root";
  TString filename = "/data6/Users/jihkim/SKFlatOutput/Run2Legacy_v4/ChargeFlip/2016/ScaleFactor__/DATA/ChargeFlip_DoubleEG.root";
  TFile* f1 = new TFile(filename);
  
  TString samplename = filename(filename.Last('_')+1,filename.Length());
  samplename.ReplaceAll(".root","");
  
  gSystem->Exec("mkdir -p "+samplename);
  
  TH1D* h0 = (TH1D*)f1->Get(id+RunSyst[Syst]+"/ScaleFactor/"+EtaRegion+"_ZMass_SS");
  TH1D* h1;
  if(EtaRegion=="BB"||EtaRegion=="EE"){
    h1 = (TH1D*)f1->Get(id+RunSyst[Syst]+"/ScaleFactor/"+EtaRegion+"_ZMass_OS_CFweighted_shifted_"+X);
  }
  else if(EtaRegion=="BE"){
    h1 = (TH1D*)f1->Get(id+RunSyst[Syst]+"/ScaleFactor/"+EtaRegion+"_ZMass_OS_CFSF_BWexpo_gauspol3_weighted_shifted_"+X);
    //h1 = (TH1D*)f1->Get(id+RunSyst[Syst]+"/ScaleFactor/"+EtaRegion+"_ZMass_OS_CFSF_gauspol3_gauspol3_weighted_shifted_"+X);
  }
  
  vector<double> x_1, ex_1, x_2, ex_2, x_3, ex_3;
  for (int i=0; i<NBin; i++) {
    x_1.push_back(MllLeft+(2*i+1)*(err)); ex_1.push_back(0.); 
    x_2.push_back(MllLeft+(2*i+1)*(err)); ex_2.push_back(0.); 
    x_3.push_back(MllLeft+(2*i+1)*(err)); ex_3.push_back(0.); 
  }
  vector<double> y_1, ey_1, y_2, ey_2, y_3, ey_3;
  for (int i=0; i<NBin; i++) {
    y_1.push_back(h1->GetBinContent(i+1));
    ey_1.push_back(h1->GetBinError(i+1));
    y_2.push_back(h0->GetBinContent(i+1));
    ey_2.push_back(h0->GetBinError(i+1));
    y_3.push_back(h0->GetBinContent(i+1)/h1->GetBinContent(i+1));
    ey_3.push_back(y_3[i]*(sqrt(pow(h1->GetBinError(i+1)/h1->GetBinContent(i+1),2)+pow(h0->GetBinError(i+1)/h0->GetBinContent(i+1),2))));
  }
  
  // Draw SS with fitting //
  
  TCanvas* c1 = new TCanvas("c1","ZMass : SS2l ("+EtaRegion+")",100,100,900,800);
  
  TGraphErrors* gr = new TGraphErrors(x_2.size(),&x_2[0],&y_2[0],&ex_2[0],&ey_2[0]);
  //TGraphErrors* gr = new TGraphErrors(x_1.size(),&x_1[0],&y_1[0],&ex_1[0],&ey_1[0]);
  gr->SetMarkerStyle(20);
  //gr->SetMarkerSize(0.8);
  //gr->SetMarkerColor(kMagenta+2);
  gr->SetLineColor(15);
  gr->SetTitle("ZMass : SS2l ("+EtaRegion+") "+RunSyst[Syst](6,10000));
  gr->GetXaxis()->SetRangeUser(MllLeft,MllRight);
  //gr->SetMinimum(0.);
  gr->Draw("ZAP"); // Z : do not draw small horizontal/vertical lines the end of the error bars
  //gr->GetXaxis()->SetLabelSize(0.01);
  gr->GetXaxis()->SetTitle("m(ee) (GeV)");
  //gr->GetXaxis()->SetTitleOffset(1.6);
  //gr->GetXaxis()->SetTickLength(0.05);
  //gr->GetYaxis()->SetLabelSize(0.05);
  
  ////////////////////// original fitting //////////////////////////////
  
  
  // create a TF1 with the range from MllLeft to MllRight and free parameters
  TF1 *fitFcn;
  TF1 *signalFcn;
  TF1 *bkgFcn;
  int NtotPar, NsigPar, NbkgPar;
  if(fit.Contains("BW")||fit.Contains("gaus")) NsigPar = 3;
  if(fit.Contains("pol1")||fit.Contains("expo")) NbkgPar = 2;
  else if(fit.Contains("pol3")) NbkgPar = 4;
  NtotPar = NsigPar + NbkgPar;
  
  if(fit=="BW_pol1"){
    fitFcn = new TF1("fitFcn",BW_pol1,MllLeft,MllRight,NtotPar);
    if(EtaRegion=="BB") fitFcn->SetParameters(80,2.5,90,0,0.1); //optimized - chi2/ndf : 634.783/25, SF : 106.8%
    else if(EtaRegion=="EE"){
      fitFcn->SetParameters(40,2.5,90,0,1);
      fitFcn->SetParLimits(3,20,200); //FIXME
    }

    signalFcn = new TF1("signalFcn",BW,MllLeft,MllRight,NsigPar);
    signalFcn->SetLineColor(kMagenta-6);
    bkgFcn = new TF1("bkgFcn",pol1,MllLeft,MllRight,NbkgPar);
    bkgFcn->SetLineColor(kBlue);
  }
  else if(fit=="BW_pol3"){
    fitFcn = new TF1("fitFcn",BW_pol3,MllLeft,MllRight,NtotPar);
    if(EtaRegion=="BB") fitFcn->SetParameters(312,7.,-90,-20,0.9,0.,0.); //optimized - chi2/ndf : 584.981/23, SF : 108.55%
    else if(EtaRegion=="EE") fitFcn->SetParameters(32.7,2.,-90,-49.,4.,0.,50.); //FIXME
    else if(EtaRegion=="BE") fitFcn->SetParameters(412.7,7.,-90,11.,-0.7,0.,0.); //FIXME

    signalFcn = new TF1("signalFcn",BW,MllLeft,MllRight,NsigPar);
    signalFcn->SetLineColor(kMagenta-6);
    bkgFcn = new TF1("bkgFcn",pol3,MllLeft,MllRight,NbkgPar);
    bkgFcn->SetLineColor(kBlue);
  }
  else if(fit=="BW_expo"){
    fitFcn = new TF1("fitFcn",BW_expo,MllLeft,MllRight,NtotPar);
    if(EtaRegion=="BB") fitFcn->SetParameters(312,7.,-90,2,-0.9); //optimized - chi2/ndf : 633.434/25, SF : 108.67% XXX <--- The best chi2
    else if(EtaRegion=="EE") fitFcn->SetParameters(312.7,2.,-90,4.,-2.); //optimized(?) - chi2/ndf : 9360.52/25, SF : 118.59%
    else if(EtaRegion=="BE") fitFcn->SetParameters(112.7,0.4,-90,11.,-0.9); //FIXME

    signalFcn = new TF1("signalFcn",BW,MllLeft,MllRight,NsigPar);
    signalFcn->SetLineColor(kMagenta-6);
    bkgFcn = new TF1("bkgFcn",expo,MllLeft,MllRight,NbkgPar);
    bkgFcn->SetLineColor(kBlue);
  }
  if(fit=="gaus_pol1"){
    fitFcn = new TF1("fitFcn",gaus_pol1,MllLeft,MllRight,NtotPar);
    if(EtaRegion=="BB") fitFcn->SetParameters(80,2.5,90,0,0.1); //FIXME
    else if(EtaRegion=="EE") fitFcn->SetParameters(40,2.5,90,0,1); //FIXME
    else if(EtaRegion=="BE") fitFcn->SetParameters(40,2.5,90,0,1); //FIXME

    signalFcn = new TF1("signalFcn",gaus,MllLeft,MllRight,NsigPar);
    signalFcn->SetLineColor(kMagenta-6);
    bkgFcn = new TF1("bkgFcn",pol1,MllLeft,MllRight,NbkgPar);
    bkgFcn->SetLineColor(kBlue);
  }
  else if(fit=="gaus_pol3"){
    fitFcn = new TF1("fitFcn",gaus_pol3,MllLeft,MllRight,NtotPar);
    if(EtaRegion=="BB") fitFcn->SetParameters(480,90,3,-40,0.9,0.,0.); //optimized - chi2/ndf : 602.101/23, SF : 68.16%
    else if(EtaRegion=="EE") fitFcn->SetParameters(480,90,3,-40,0.9,0.,0.); //optimized - chi2/ndf : 3959.76/23, SF : 83.3%
    else if(EtaRegion=="BE") fitFcn->SetParameters(480,90,3,-40,0.9,0.,0.); //optimized - chi2/ndf : 8160.63/23, SF : 93.38% || chi2/ndf : same, SF : 96.35% - 60% SF at BB gives the better result..

    signalFcn = new TF1("signalFcn",gaus,MllLeft,MllRight,NsigPar);
    signalFcn->SetLineColor(kMagenta-6);
    bkgFcn = new TF1("bkgFcn",pol3,MllLeft,MllRight,NbkgPar);
    bkgFcn->SetLineColor(kBlue);
  }
  else if(fit=="gaus_expo"){
    fitFcn = new TF1("fitFcn",gaus_expo,MllLeft,MllRight,NtotPar);
    if(EtaRegion=="BB") fitFcn->SetParameters(480,90,3,2,-0.9); //FIXME
    else if(EtaRegion=="EE") fitFcn->SetParameters(480,90,3,4,-0.9); //FIXME chi2/ndf : 7158.70/25, SF : 90.55%
    else if(EtaRegion=="BE") fitFcn->SetParameters(480,90,3,4,-0.9); //FIXME

    signalFcn = new TF1("signalFcn",gaus,MllLeft,MllRight,NsigPar);
    signalFcn->SetLineColor(kMagenta-6);
    bkgFcn = new TF1("bkgFcn",expo,MllLeft,MllRight,NbkgPar);
    bkgFcn->SetLineColor(kBlue);
  }
  
  //fitFcn->SetNpx(500);
  fitFcn->SetLineColor(kRed);
  gr->Fit(fitFcn,"IWR");
  
  // writes the fit results into the par array
  Double_t par[NtotPar];
  fitFcn->GetParameters(par);
  signalFcn->SetParameters(par);
  bkgFcn->SetParameters(&par[NsigPar]);
  
  bkgFcn->Draw("same");
  
  /* get needed strings to put in the textbox */
  
  double Chisquare = fitFcn->GetChisquare();
  TString Chisquare_t = Form("%f",Chisquare);
  Chisquare_t = Chisquare_t(0,7);
  int ndf = fitFcn->GetNDF();
  TString ndf_t = Form("%d",ndf);
  int SS2l_obs = h0->Integral();
  TString SS2l_obs_t = Form("%d",SS2l_obs);
  double SS2l_bkg = bkgFcn->Integral(MllLeft,MllRight)/(2.*err); //JH : histo integral just counts the entry, but function integral calculates the area.
  TString SS2l_bkg_t = Form("%f",SS2l_bkg);
  SS2l_bkg_t = SS2l_bkg_t(0,7);
  double SS2l = signalFcn->Integral(MllLeft,MllRight)/(2.*err);
  TString SS2l_t = Form("%f",SS2l);
  SS2l_t = SS2l_t(0,7);
  int OS2l = h1->Integral();
  TString OS2l_t = Form("%d",OS2l);
  double SF = SS2l/OS2l;
  TString SF_t = Form("%f",SF);
  SF_t = SF_t(0,7);
  
  //
  
  // draw the textbox
  TPaveText *pt = new TPaveText(0.65,0.75,0.9,0.9,"NDC");
  pt->SetShadowColor(0);
  pt->SetFillColor(0);
  pt->AddText("Chisqaure/ndf : "+Chisquare_t+"/"+ndf_t);
  pt->AddText("SS_observed : "+SS2l_obs_t);
  pt->AddText("SS_signal : "+SS2l_t);
  pt->AddText("SS_background : "+SS2l_bkg_t);
  pt->Draw();
  
  
  // Draw the comparison plots //
  
  TCanvas* c2 = new TCanvas("c2","ZMass : OS_CFweighted vs SS ("+EtaRegion+")",1000,100,900,800);
  c2->Divide(1,2);
  
  c2->cd(1);
  
  gPad->SetPad(0,0.35,1,1);
  gPad->SetTopMargin(0.08);
  gPad->SetBottomMargin(0.02);
  
  TGraphErrors* gr1 = new TGraphErrors(x_1.size(),&x_1[0],&y_1[0],&ex_1[0],&ey_1[0]);
  gr1->SetMarkerStyle(20);
  //gr1->SetMarkerSize(0.8);
  //gr1->SetMarkerColor(kMagenta+2);
  gr1->SetLineColor(15);
  gr1->SetTitle("ZMass : OS_CFweighted_"+X+" vs SS ("+EtaRegion+") "+RunSyst[Syst](6,10000));
  //gr1->SetMinimum(0.);
  gr1->Draw("ZAP"); // Z : do not draw small horizontal/vertical lines the end of the error bars
  gr1->GetXaxis()->SetTickLength(0.025);
  gr1->GetXaxis()->SetLabelSize(0);
  gr1->GetYaxis()->SetLabelSize(0.025);
  gr1->GetXaxis()->SetRangeUser(MllLeft,MllRight);
  
  TGraphErrors* gr2 = new TGraphErrors(x_2.size(),&x_2[0],&y_2[0],&ex_2[0],&ey_2[0]);
  gr2->SetMarkerStyle(20);
  gr2->SetMarkerColor(kMagenta+2);
  gr2->SetLineColor(15);
  gr2->Draw("ZP SAME"); 
  
  signalFcn->Draw("same");
  
  // draw legend
  
  TLegend* legend = new TLegend(0.15,0.6,0.4,0.8);
  legend->AddEntry(gr1,"OS_CFweighted_"+X,"lp");
  legend->AddEntry(gr2,"SS_observed","lp");
  legend->AddEntry(signalFcn,"SS_signalFit","l");
  legend->Draw();
  
  // draw textbox
  
  TPaveText *pt2 = new TPaveText(0.62,0.77,0.9,0.92,"NDC");
  pt2->SetShadowColor(0);
  pt2->SetFillColor(0);
  pt2->AddText("SS_observed : "+SS2l_obs_t);
  pt2->AddText("SS_signalFit : "+SS2l_t);
  pt2->AddText("OS2l_CF_shifted_"+X+" : "+OS2l_t);
  pt2->AddText("SF : "+SF_t);
  pt2->Draw();
  
  
  
  c2->cd(2);
  
  gPad->SetPad(0,0,1,0.35);
  gPad->SetTopMargin(0.05);
  gPad->SetBottomMargin(0.15);
  
  /* ratio plot for SS(signal) vs OS */
  
  vector<double> x_4;
  for (int i=0; i<NBin; i++) {
    x_4.push_back(MllLeft+(2*i+1)*(err));
  }
  vector<double> y_4;
  for (int i=0; i<NBin; i++) {
    y_4.push_back(signalFcn->Eval(x_4[i])/h1->GetBinContent(i+1));
  }

  //TGraphErrors* gr3 = new TGraphErrors(x_3.size(),&x_3[0],&y_3[0],&ex_3[0],&ey_3[0]);
  TGraph* gr3 = new TGraph(x_4.size(),&x_4[0],&y_4[0]);
  gr3->SetMarkerStyle(20);
  gr3->SetMarkerColor(kBlue-4);
  gr3->SetMarkerSize(0.8);
  gr3->SetTitle("");
  gr3->Draw("ZAP");
  gr3->GetXaxis()->SetLabelSize(0.06);
  gr3->GetXaxis()->SetTitle("#scale[2.2]{m(ee) (GeV)}");
  gr3->GetXaxis()->SetTitleOffset(1.6);
  gr3->GetXaxis()->SetTickLength(0.05);
  gr3->GetXaxis()->SetRangeUser(MllLeft,MllRight);
  gr3->GetYaxis()->SetLabelSize(0.05);
  gr3->GetYaxis()->SetTitle("#scale[2.2]{SS(signalFit) / OS}"); // SS(signal) / OS would be more informative than SS(observed)
  gr3->GetYaxis()->SetTitleOffset(0.8);
  gr3->GetYaxis()->SetRangeUser(0,3);
  gPad->SetGridx();
  gPad->SetGridy();
  
  //TLine* LineAtOne = new TLine(gr3->GetXaxis()->GetXmin(),1,gr3->GetXaxis()->GetXmax(),1);
  //LineAtOne->SetLineStyle(kDashed);
  //LineAtOne->SetLineWidth(2);
  //LineAtOne->SetLineColor(2);
  //LineAtOne->Draw();
  
  TLine* LineAtSF = new TLine(gr3->GetXaxis()->GetXmin(),SF,gr3->GetXaxis()->GetXmax(),SF);
  LineAtSF->SetLineStyle(kDashed);
  LineAtSF->SetLineWidth(2);
  LineAtSF->SetLineColor(2);
  LineAtSF->Draw();
  
  TLegend* legend2 = new TLegend(0.75,0.85,0.9,0.95);
  legend2->AddEntry(LineAtSF,"scale factor","l");
  legend2->Draw();
  
  
  if(SaveAs == "y") {
  
    //c1->SaveAs(samplename+"/"+id+"_SS2lFit_"+EtaRegion+"_"+RunSyst[Syst](6,10000)+".pdf");
    //c2->SaveAs(samplename+"/"+id+"_ScaleFactor_"+EtaRegion+"_"+RunSyst[Syst](6,10000)+".pdf");
  
    c1->SaveAs(samplename+"/"+id+"_SS2lFit_"+EtaRegion+"_"+RunSyst[Syst](6,10000)+".png");
    c2->SaveAs(samplename+"/"+id+"_ScaleFactor_"+EtaRegion+"_"+RunSyst[Syst](6,10000)+".png");
  
  }


}

void SaveAll(){

  map<int,TString> m1;
  m1[0] = "HEID";
  m1[1] = "HNTight2016";
  map<int,TString> m2;
  m2[0] = "BB";
  m2[1] = "EE";

  for (int i=0; i<2; i++){
    for (int j=0; j<2; j++){
      for (int k=0; k<7; k++){
        ScaleFactor(m1[i],m2[j],"",k,"y");
      }
    }
  }

}
