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

void ScaleFactor(TString id, TString EtaRegion, TString METcut, TString fit, int Syst = 0, TString SaveAs = "n"){ // BB, BE, EE

  TString X = ""; //energy shift
  if(id=="HEID") X = "1.3%";
  else if(id=="HNTightV1") X = "1.0%";
  else if(id=="HNTight2016") X = "1.2%";
  
  int MllLeft = 50; if(Syst==3) MllLeft = 80; else if(Syst==4) MllLeft = 70;
  int MllRight = 150; if(Syst==3) MllRight = 100; else if(Syst==4) MllRight = 110;
  int NBin = 50; if(Syst==5) NBin = 25; else if(Syst==6) NBin = 35;
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
  TString filename = "/data6/Users/jihkim/SKFlatOutput/Run2Legacy_v4/CFSF_test/2016/ScaleFactor__/DATA/CFSF_test_DoubleEG.root";
  TFile* f1 = new TFile(filename);
  
  TString samplename = filename(filename.Last('_')+1,filename.Length());
  samplename.ReplaceAll(".root","");
  
  gSystem->Exec("mkdir -p "+samplename);
  
  TH1D* h0 = (TH1D*)f1->Get(id+RunSyst[Syst]+"/ScaleFactor/"+EtaRegion+"_ZMass_SS_MET"+METcut);
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
  for (int i=10; i<NBin+10; i++) { //JH : NOTE select bin m(ll) = 50 GeV correctly!
    y_1.push_back(h1->GetBinContent(i+1));
    ey_1.push_back(h1->GetBinError(i+1));
    y_2.push_back(h0->GetBinContent(i+1));
    ey_2.push_back(h0->GetBinError(i+1));
    y_3.push_back(h0->GetBinContent(i+1)/h1->GetBinContent(i+1));
    ey_3.push_back(y_3[i]*(sqrt(pow(h1->GetBinError(i+1)/h1->GetBinContent(i+1),2)+pow(h0->GetBinError(i+1)/h0->GetBinContent(i+1),2)))); //y_3 : OS / SS before fittinh (no use)
  }
 
  // create a TF1 with the range from MllLeft to MllRight and free parameters
  TF1 *fitFcn_SS, *fitFcn_OS;
  TF1 *signalFcn_SS, *signalFcn_OS, *signalFcn_OS_alt;
  TF1 *bkgFcn_SS, *bkgFcn_OS;
  int NtotPar, NsigPar, NbkgPar;
  if(fit.Contains("BW")||fit.Contains("gaus")) NsigPar = 3;
  if(fit.Contains("pol1")||fit.Contains("expo")) NbkgPar = 2;
  else if(fit.Contains("pol3")) NbkgPar = 4;
  NtotPar = NsigPar + NbkgPar;

  // Draw SS and OS fitting //
 
   // SS canvas
  TCanvas* c1_SS = new TCanvas("c1_SS","ZMass : SS2l ("+EtaRegion+")",100,100,900,800);
  
  TGraphErrors* gr_SS = new TGraphErrors(x_2.size(),&x_2[0],&y_2[0],&ex_2[0],&ey_2[0]);
  //TGraphErrors* gr_SS = new TGraphErrors(x_1.size(),&x_1[0],&y_1[0],&ex_1[0],&ey_1[0]);
  gr_SS->SetMarkerStyle(20);
  //gr_SS->SetMarkerSize(0.8);
  //gr_SS->SetMarkerColor(kMagenta+2);
  gr_SS->SetLineColor(15);
  gr_SS->SetTitle("ZMass : SS2l ("+EtaRegion+") "+RunSyst[Syst](6,10000));
  gr_SS->GetXaxis()->SetRangeUser(MllLeft,MllRight);
  //gr_SS->SetMinimum(0.);
  gr_SS->Draw("ZAP"); // Z : do not draw small horizontal/vertical lines the end of the error bars
  //gr_SS->GetXaxis()->SetLabelSize(0.01);
  gr_SS->GetXaxis()->SetTitle("m(ee) (GeV)");
  //gr_SS->GetXaxis()->SetTitleOffset(1.6);
  //gr_SS->GetXaxis()->SetTickLength(0.05);
  //gr_SS->GetYaxis()->SetLabelSize(0.05);
  
  ////////////////////// SS fitting //////////////////////////////
  if(fit=="BW_pol1"){
    fitFcn_SS = new TF1("fitFcn_SS",BW_pol1,MllLeft,MllRight,NtotPar);
    if(EtaRegion=="BB") fitFcn_SS->SetParameters(80,2.5,90,0,0.1); //optimized - chi2/ndf : 634.783/25, SF : 106.8%
    else if(EtaRegion=="EE"){
      fitFcn_SS->SetParameters(40,2.5,90,0,1);
      fitFcn_SS->SetParLimits(3,20,200); //FIXME
    }

    signalFcn_SS = new TF1("signalFcn_SS",BW,MllLeft,MllRight,NsigPar);
    signalFcn_SS->SetLineColor(kMagenta-6);
    bkgFcn_SS = new TF1("bkgFcn_SS",pol1,MllLeft,MllRight,NbkgPar);
    bkgFcn_SS->SetLineColor(kBlue);
  }
  else if(fit=="BW_pol3"){
    fitFcn_SS = new TF1("fitFcn_SS",BW_pol3,MllLeft,MllRight,NtotPar);
    if(EtaRegion=="BB") fitFcn_SS->SetParameters(312,7.,-90,-20,0.9,0.,0.); //optimized - chi2/ndf : 584.981/23, SF : 108.55%
    else if(EtaRegion=="EE") fitFcn_SS->SetParameters(3012.7,2.,-90,-439.,48.,40.,550.); //FIXME
    else if(EtaRegion=="BE") fitFcn_SS->SetParameters(412.7,7.,-90,11.,-0.7,0.,0.); //FIXME
    
    signalFcn_SS = new TF1("signalFcn_SS",BW,MllLeft,MllRight,NsigPar);
    signalFcn_SS->SetLineColor(kMagenta-6);
    bkgFcn_SS = new TF1("bkgFcn_SS",pol3,MllLeft,MllRight,NbkgPar);
    bkgFcn_SS->SetLineColor(kBlue);
  }
  else if(fit=="BW_expo"){
    fitFcn_SS = new TF1("fitFcn_SS",BW_expo,MllLeft,MllRight,NtotPar);
    if(EtaRegion=="BB") fitFcn_SS->SetParameters(312,7.,-90,2,-0.9); //optimized - chi2/ndf : 633.434/25, SF : 108.67% XXX <--- The best chi2
    else if(EtaRegion=="EE") fitFcn_SS->SetParameters(312.7,2.,-90,4.,-2.); //optimized(?) - chi2/ndf : 9360.52/25, SF : 118.59%
    else if(EtaRegion=="BE") fitFcn_SS->SetParameters(112.7,0.4,-90,11.,-0.9); //FIXME
    
    signalFcn_SS = new TF1("signalFcn_SS",BW,MllLeft,MllRight,NsigPar);
    signalFcn_SS->SetLineColor(kMagenta-6);
    bkgFcn_SS = new TF1("bkgFcn_SS",expo,MllLeft,MllRight,NbkgPar);
    bkgFcn_SS->SetLineColor(kBlue);
  }
  else if(fit=="gaus_pol1"){
    fitFcn_SS = new TF1("fitFcn_SS",gaus_pol1,MllLeft,MllRight,NtotPar);
    if(EtaRegion=="BB") fitFcn_SS->SetParameters(80,2.5,90,0,0.1); //FIXME
    else if(EtaRegion=="EE") fitFcn_SS->SetParameters(40,2.5,90,0,1); //FIXME
    else if(EtaRegion=="BE") fitFcn_SS->SetParameters(40,2.5,90,0,1); //FIXME
    
    signalFcn_SS = new TF1("signalFcn_SS",gaus,MllLeft,MllRight,NsigPar);
    signalFcn_SS->SetLineColor(kMagenta-6);
    bkgFcn_SS = new TF1("bkgFcn_SS",pol1,MllLeft,MllRight,NbkgPar);
    bkgFcn_SS->SetLineColor(kBlue);
  }
  else if(fit=="gaus_pol3"){
    fitFcn_SS = new TF1("fitFcn_SS",gaus_pol3,MllLeft,MllRight,NtotPar);
    if(EtaRegion=="BB") fitFcn_SS->SetParameters(480,90,3,-40,0.9,0.,0.); //optimized - chi2/ndf : 602.101/23, SF : 68.16%
    else if(EtaRegion=="EE") fitFcn_SS->SetParameters(480,90,3,-40,0.9,0.,0.); //optimized - chi2/ndf : 3959.76/23, SF : 83.3%
    else if(EtaRegion=="BE") fitFcn_SS->SetParameters(480,90,3,-40,0.9,0.,0.); //optimized - chi2/ndf : 8160.63/23, SF : 93.38% || chi2/ndf : same, SF : 96.35% - 60% SF at BB gives the better result..
    
    signalFcn_SS = new TF1("signalFcn_SS",gaus,MllLeft,MllRight,NsigPar);
    signalFcn_SS->SetLineColor(kMagenta-6);
    bkgFcn_SS = new TF1("bkgFcn_SS",pol3,MllLeft,MllRight,NbkgPar);
    bkgFcn_SS->SetLineColor(kBlue);
  }
  else if(fit=="gaus_expo"){
    fitFcn_SS = new TF1("fitFcn_SS",gaus_expo,MllLeft,MllRight,NtotPar);
    if(EtaRegion=="BB") fitFcn_SS->SetParameters(480,90,3,2,-0.9); //FIXME
    else if(EtaRegion=="EE") fitFcn_SS->SetParameters(480,90,3,4,-0.9); //FIXME chi2/ndf : 7158.70/25, SF : 90.55%
    else if(EtaRegion=="BE") fitFcn_SS->SetParameters(480,90,3,4,-0.9); //FIXME
    
    signalFcn_SS = new TF1("signalFcn_SS",gaus,MllLeft,MllRight,NsigPar);
    signalFcn_SS->SetLineColor(kMagenta-6);
    bkgFcn_SS = new TF1("bkgFcn_SS",expo,MllLeft,MllRight,NbkgPar);
    bkgFcn_SS->SetLineColor(kBlue);
  }
  
  fitFcn_SS->SetNpx(1500);
  fitFcn_SS->SetLineColor(kRed);
  gr_SS->Fit(fitFcn_SS,"IWR");
  
  // writes the fit results into the par array
  Double_t par_SS[NtotPar];
  fitFcn_SS->GetParameters(par_SS);
  signalFcn_SS->SetParameters(par_SS);
  bkgFcn_SS->SetParameters(&par_SS[NsigPar]);
  
  bkgFcn_SS->Draw("same");
  
  // get needed strings to put in the textbox //
  double Chisquare_SS = fitFcn_SS->GetChisquare();
  TString Chisquare_SS_t = Form("%f",Chisquare_SS);
  Chisquare_SS_t = Chisquare_SS_t(0,7);
  int ndf_SS = fitFcn_SS->GetNDF();
  TString ndf_SS_t = Form("%d",ndf_SS);
  int SS2l_obs = h0->Integral(26,35); //JH NOTE look carefully the range
  TString SS2l_obs_t = Form("%d",SS2l_obs);
  double SS2l_bkg = bkgFcn_SS->Integral(80,100)/(2.*err); //JH : histo integral just counts the entry, but function integral calculates the area, so must be divided by the bin width. NOTE Integral range
  TString SS2l_bkg_t = Form("%f",SS2l_bkg);
  SS2l_bkg_t = SS2l_bkg_t(0,7);
  double SS2l = signalFcn_SS->Integral(80,100)/(2.*err); // NOTE Beware to the integral range
  TString SS2l_t = Form("%f",SS2l);
  SS2l_t = SS2l_t(0,7);
  //int OS2l = h1->Integral(26,35); //JH NOTE Select bin of 80 GeV < m(ll) < 100 GeV correctly!
  //TString OS2l_t = Form("%d",OS2l);
  //double SF = SS2l/OS2l;
  //TString SF_t = Form("%f",SF);
  //SF_t = SF_t(0,7);
  
  // draw the textbox
  TPaveText *pt_SS = new TPaveText(0.65,0.75,0.9,0.9,"NDC");
  pt_SS->SetShadowColor(0);
  pt_SS->SetFillColor(0);
  pt_SS->AddText("Chisqaure/ndf : "+Chisquare_SS_t+"/"+ndf_SS_t);
  pt_SS->AddText("SS_observed : "+SS2l_obs_t);
  pt_SS->AddText("SS_signal : "+SS2l_t);
  pt_SS->AddText("SS_background : "+SS2l_bkg_t);
  pt_SS->Draw();
 

  // OS canvas
  TCanvas* c1_OS = new TCanvas("c1_OS","ZMass : OS2l ("+EtaRegion+")",1000,100,900,800);
  
  TGraphErrors* gr_OS = new TGraphErrors(x_1.size(),&x_1[0],&y_1[0],&ex_1[0],&ey_1[0]);
  gr_OS->SetMarkerStyle(20);
  //gr_OS->SetMarkerSize(0.8);
  //gr_OS->SetMarkerColor(kMagenta+2);
  gr_OS->SetLineColor(15);
  gr_OS->SetTitle("ZMass : OS2l ("+EtaRegion+") "+RunSyst[Syst](6,10000));
  gr_OS->GetXaxis()->SetRangeUser(MllLeft,MllRight);
  //gr_OS->SetMinimum(0.);
  gr_OS->Draw("ZAP"); // Z : do not draw small horizontal/vertical lines the end of the error bars
  //gr_OS->GetXaxis()->SetLabelSize(0.01);
  gr_OS->GetXaxis()->SetTitle("m(ee) (GeV)");
  //gr_OS->GetXaxis()->SetTitleOffset(1.6);
  //gr_OS->GetXaxis()->SetTickLength(0.05);
  //gr_OS->GetYaxis()->SetLabelSize(0.05);

  ////////////////////// OS fitting //////////////////////////////
  if(fit=="BW_pol1"){
    fitFcn_OS = new TF1("fitFcn_OS",BW_pol1,MllLeft,MllRight,NtotPar);
    if(EtaRegion=="BB") fitFcn_OS->SetParameters(80,2.5,90,0,0.1); //optimized - chi2/ndf : 634.783/25, SF : 106.8%
    else if(EtaRegion=="EE"){
      fitFcn_OS->SetParameters(40,2.5,90,0,1);
      fitFcn_OS->SetParLimits(3,20,200); //FIXME
    }

    signalFcn_OS = new TF1("signalFcn_OS",BW,MllLeft,MllRight,NsigPar);
    signalFcn_OS->SetLineColor(kGreen+1);
    bkgFcn_OS = new TF1("bkgFcn_OS",pol1,MllLeft,MllRight,NbkgPar);
    bkgFcn_OS->SetLineColor(kBlue);
  }
  else if(fit=="BW_pol3"){
    fitFcn_OS = new TF1("fitFcn_OS",BW_pol3,MllLeft,MllRight,NtotPar);
    if(EtaRegion=="BB") fitFcn_OS->SetParameters(312,7.,-90,-20,0.9,0.,0.); //optimized - chi2/ndf : 584.981/23, SF : 108.55%
    else if(EtaRegion=="EE") fitFcn_OS->SetParameters(3012.7,2.,-90,-439.,48.,40.,550.); //FIXME
    else if(EtaRegion=="BE") fitFcn_OS->SetParameters(412.7,7.,-90,11.,-0.7,0.,0.); //FIXME
    
    signalFcn_OS = new TF1("signalFcn_OS",BW,MllLeft,MllRight,NsigPar);
    signalFcn_OS->SetLineColor(kGreen+1);
    bkgFcn_OS = new TF1("bkgFcn_OS",pol3,MllLeft,MllRight,NbkgPar);
    bkgFcn_OS->SetLineColor(kBlue);
  }
  else if(fit=="BW_expo"){
    fitFcn_OS = new TF1("fitFcn_OS",BW_expo,MllLeft,MllRight,NtotPar);
    if(EtaRegion=="BB") fitFcn_OS->SetParameters(312,7.,-90,2,-0.9); //optimized - chi2/ndf : 633.434/25, SF : 108.67% XXX <--- The best chi2
    else if(EtaRegion=="EE") fitFcn_OS->SetParameters(312.7,2.,-90,4.,-2.); //optimized(?) - chi2/ndf : 9360.52/25, SF : 118.59%
    else if(EtaRegion=="BE") fitFcn_OS->SetParameters(112.7,0.4,-90,11.,-0.9); //FIXME
    
    signalFcn_OS = new TF1("signalFcn_OS",BW,MllLeft,MllRight,NsigPar);
    signalFcn_OS->SetLineColor(kGreen+1);
    bkgFcn_OS = new TF1("bkgFcn_OS",expo,MllLeft,MllRight,NbkgPar);
    bkgFcn_OS->SetLineColor(kBlue);
  }
  else if(fit=="gaus_pol1"){
    fitFcn_OS = new TF1("fitFcn_OS",gaus_pol1,MllLeft,MllRight,NtotPar);
    if(EtaRegion=="BB") fitFcn_OS->SetParameters(80,2.5,90,0,0.1); //FIXME
    else if(EtaRegion=="EE") fitFcn_OS->SetParameters(40,2.5,90,0,1); //FIXME
    else if(EtaRegion=="BE") fitFcn_OS->SetParameters(40,2.5,90,0,1); //FIXME
    
    signalFcn_OS = new TF1("signalFcn_OS",gaus,MllLeft,MllRight,NsigPar);
    signalFcn_OS->SetLineColor(kGreen+1);
    bkgFcn_OS = new TF1("bkgFcn_OS",pol1,MllLeft,MllRight,NbkgPar);
    bkgFcn_OS->SetLineColor(kBlue);
  }
  else if(fit=="gaus_pol3"){
    fitFcn_OS = new TF1("fitFcn_OS",gaus_pol3,MllLeft,MllRight,NtotPar);
    if(EtaRegion=="BB") fitFcn_OS->SetParameters(480,90,3,-40,0.9,0.,0.); //optimized - chi2/ndf : 602.101/23, SF : 68.16%
    else if(EtaRegion=="EE") fitFcn_OS->SetParameters(480,90,3,-40,0.9,0.,0.); //optimized - chi2/ndf : 3959.76/23, SF : 83.3%
    else if(EtaRegion=="BE") fitFcn_OS->SetParameters(480,90,3,-40,0.9,0.,0.); //optimized - chi2/ndf : 8160.63/23, SF : 93.38% || chi2/ndf : same, SF : 96.35% - 60% SF at BB gives the better result..
    
    signalFcn_OS = new TF1("signalFcn_OS",gaus,MllLeft,MllRight,NsigPar);
    signalFcn_OS->SetLineColor(kGreen+1);
    bkgFcn_OS = new TF1("bkgFcn_OS",pol3,MllLeft,MllRight,NbkgPar);
    bkgFcn_OS->SetLineColor(kBlue);
  }
  else if(fit=="gaus_expo"){
    fitFcn_OS = new TF1("fitFcn_OS",gaus_expo,MllLeft,MllRight,NtotPar);
    if(EtaRegion=="BB") fitFcn_OS->SetParameters(480,90,3,2,-0.9); //FIXME
    else if(EtaRegion=="EE") fitFcn_OS->SetParameters(480,90,3,4,-0.9); //FIXME chi2/ndf : 7158.70/25, SF : 90.55%
    else if(EtaRegion=="BE") fitFcn_OS->SetParameters(480,90,3,4,-0.9); //FIXME
    
    signalFcn_OS = new TF1("signalFcn_OS",gaus,MllLeft,MllRight,NsigPar);
    signalFcn_OS->SetLineColor(kGreen+1);
    bkgFcn_OS = new TF1("bkgFcn_OS",expo,MllLeft,MllRight,NbkgPar);
    bkgFcn_OS->SetLineColor(kBlue);
  }
  
  fitFcn_OS->SetNpx(1500);
  fitFcn_OS->SetLineColor(kRed);
  gr_OS->Fit(fitFcn_OS,"IWR0");
  
  // writes the fit results into the par array
  Double_t par_OS[NtotPar];
  fitFcn_OS->GetParameters(par_OS);
  signalFcn_OS->SetParameters(par_OS);
  bkgFcn_OS->SetParameters(&par_OS[NsigPar]);

  // If bkg < 0, then just omit the bkg fit.
  if(bkgFcn_OS->Integral(MllLeft,MllRight) < 0){
    fitFcn_OS = signalFcn_OS;
    fitFcn_OS->SetLineColor(kGreen+1);
    gr_OS->Fit(fitFcn_OS,"IWR0");
    fitFcn_OS->Draw("same");
  }
  else{
    fitFcn_OS->Draw("same");
    bkgFcn_OS->Draw("same");
  }
 
  // get needed strings to put in the textbox //
  double Chisquare_OS = fitFcn_OS->GetChisquare();
  TString Chisquare_OS_t = Form("%f",Chisquare_OS);
  Chisquare_OS_t = Chisquare_OS_t(0,7);
  int ndf_OS = fitFcn_OS->GetNDF();
  TString ndf_OS_t = Form("%d",ndf_OS);
  int OS2l_obs = h1->Integral(26,35); //JH NOTE look carefully the range
  TString OS2l_obs_t = Form("%d",OS2l_obs);
  double OS2l_bkg = bkgFcn_OS->Integral(80,100)/(2.*err); //JH : histo integral just counts the entry, but function integral calculates the area, so must be divided by the bin width. NOTE Beware to the integral range
  TString OS2l_bkg_t = Form("%f",OS2l_bkg);
  OS2l_bkg_t = OS2l_bkg_t(0,7);
  double OS2l = signalFcn_OS->Integral(80,100)/(2.*err);
  TString OS2l_t = Form("%f",OS2l);
  OS2l_t = OS2l_t(0,7);
  double SF = SS2l/OS2l;
  TString SF_t = Form("%f",SF);
  SF_t = SF_t(0,7);
  
  // draw the textbox
  TPaveText *pt_OS = new TPaveText(0.65,0.75,0.9,0.9,"NDC");
  pt_OS->SetShadowColor(0);
  pt_OS->SetFillColor(0);
  pt_OS->AddText("Chisqaure/ndf : "+Chisquare_OS_t+"/"+ndf_OS_t);
  pt_OS->AddText("OS_observed : "+OS2l_obs_t);
  pt_OS->AddText("OS_signal : "+OS2l_t);
  if(!(bkgFcn_OS->Integral(MllLeft,MllRight) < 0)) pt_OS->AddText("OS_background : "+OS2l_bkg_t);
  pt_OS->Draw();

  
  // Draw the comparison plots //
  
  TCanvas* c2 = new TCanvas("c2","ZMass : OS_CFweighted vs SS ("+EtaRegion+")",1000,100,900,800);
  c2->Divide(1,2);
  
  c2->cd(1);
  
  gPad->SetPad(0,0.35,1,1);
  gPad->SetTopMargin(0.08);
  gPad->SetBottomMargin(0.02);
 
  // gr1 : OS before fitting //  
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

  signalFcn_OS->SetNpx(1500);
  signalFcn_OS->Draw("same");

  // gr2 : SS before fitting //  
  TGraphErrors* gr2 = new TGraphErrors(x_2.size(),&x_2[0],&y_2[0],&ex_2[0],&ey_2[0]);
  gr2->SetMarkerStyle(20);
  gr2->SetMarkerColor(kMagenta+2);
  gr2->SetLineColor(15);
  gr2->Draw("ZP SAME"); 
  
  signalFcn_SS->SetNpx(1500);
  signalFcn_SS->Draw("same");
  
  // draw legend
  TLegend* legend = new TLegend(0.15,0.6,0.4,0.8);
  legend->AddEntry(gr1,"OS_CFweighted_"+X,"lp");
  legend->AddEntry(signalFcn_OS,"OS_signalFit","l");
  legend->AddEntry(gr2,"SS_observed","lp");
  legend->AddEntry(signalFcn_SS,"SS_signalFit","l");
  legend->Draw();
  
  // draw textbox
  TPaveText *pt2 = new TPaveText(0.62,0.77,0.9,0.92,"NDC");
  pt2->SetShadowColor(0);
  pt2->SetFillColor(0);
  pt2->AddText("SS_observed : "+SS2l_obs_t);
  pt2->AddText("OS_predicted : "+OS2l_obs_t);
  pt2->AddText("SS_signalFit : "+SS2l_t);
  pt2->AddText("OS_signalFit : "+OS2l_t);
  pt2->AddText("SF : "+SF_t);
  pt2->Draw();
  
  
  
  c2->cd(2);
  
  gPad->SetPad(0,0,1,0.35);
  gPad->SetTopMargin(0.05);
  gPad->SetBottomMargin(0.15);
  
  /* ratio plot for SS(signal) vs OS(signal) */
  
  vector<double> x_4;
  for (int i=0; i<NBin; i++) {
    x_4.push_back(MllLeft+(2*i+1)*(err));
  }
  vector<double> y_4;
  for (int i=0; i<NBin; i++) {
    //y_4.push_back(signalFcn_SS->Eval(x_4[i])/h1->GetBinContent(10+i+1)); //JH : NOTE
    y_4.push_back(signalFcn_SS->Eval(x_4[i])/signalFcn_OS->Eval(x_4[i])); //JH 
  }

  // gr3 : SS after fitting / OS before fitting //
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
  gr3->GetYaxis()->SetTitle("#scale[2.2]{SS(signalFit) / OS(signalFit)}"); //JH
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
  
    c1_SS->SaveAs(samplename+"/"+id+"_SS2lFit_"+EtaRegion+"_MET"+METcut+"_"+RunSyst[Syst](6,10000)+".png");
    c2->SaveAs(samplename+"/"+id+"_ScaleFactor_"+EtaRegion+"_MET"+METcut+"_"+RunSyst[Syst](6,10000)+".png");
  
  }


}

void SaveAll(){

  map<int,TString> m1;
  m1[0] = "HEID";
  m1[1] = "HNTight2016";
  map<int,TString> m2;
  m2[0] = "BB";
  m2[1] = "EE";
  map<int,TString> m3;
  m3[0] = "0";
  m3[1] = "50";

  for (int i=0; i<2; i++){
    for (int j=0; j<2; j++){
      for (int k=0; k<2; k++){
        for (int l=0; l<7; l++){
          ScaleFactor(m1[i],m2[j],m3[k],"",l,"y");
        }
      }
    }
  }

}
