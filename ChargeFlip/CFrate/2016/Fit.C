void Fit(TString fitIB = "expo_invx", TString fitOB = "expo_invx", TString fitEC = "invx_only", TString scan = "y", TString zoom = "n", TString save = "n"){
TString filename = "/data6/Users/jihkim/SKFlatOutput/Run2Legacy_v4/ChargeFlip/2016/CFrate__/ChargeFlip_All.root";
TFile* f1 = new TFile(filename);

TString samplename = filename(filename.Last('/')+12,filename.Length());
samplename.ReplaceAll(".root","");

//gSystem->Exec("mkdir "+samplename);

vector<TString> User_ID;
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
  TCanvas* c2 = new TCanvas("c2","ChargeFlip_EtaRegion2 ("+User_ID.at(i)+")",250,150,900,800);
  TCanvas* c3 = new TCanvas("c3","ChargeFlip_EtaRegion3 ("+User_ID.at(i)+")",300,100,900,800);
  
  c1->cd();
  
  TGraphErrors* gr1 = new TGraphErrors(X_1.size(),&X_1[0],&Y_1[0],&EX_1[0],&EY_1[0]);
  gr1->SetMarkerStyle(20);
  //gr1->SetMarkerSize(0.8);
  //gr1->SetMarkerColor(kMagenta+2);
  gr1->SetLineColor(15);
  //gr1->SetTitle("ChargeFlip_|#eta|<0.8 ("+User_ID.at(i)+")");
  gr1->SetTitle("ChargeFlip_|#eta|<0.8");
  gr1->SetMinimum(0.);
  gr1->Draw("ZAP"); //Z : do not draw small horizontal/vertical lines the end of the error bars
  gr1->GetXaxis()->SetRangeUser(0.,0.04);
  gr1->GetXaxis()->SetTitle("#scale[0.8]{1/p_{T} (GeV^{-1})}");
  gr1->GetXaxis()->SetTickLength(0.025);
  gr1->GetXaxis()->SetLabelSize(0.025);
  gr1->GetYaxis()->SetLabelSize(0.025);
  if(zoom == "y") gr1->GetYaxis()->SetRangeUser(0.,0.0002);
  
  
  // Define fit function and range //
 
  vector<double> gr1_range = {0, 0.003, 0.013, 0.04};

  TF1 *gr1_fit1, *gr1_fit2, *gr1_fit3;

  if(fitIB == "pol1"){
    gr1_fit1 = new TF1("gr1_fit1","pol1",gr1_range[0],gr1_range[1]);
    gr1_fit2 = new TF1("gr1_fit2","pol1",gr1_range[1],gr1_range[2]);
  }
  else if(fitIB == "invx"){
    gr1_fit1 = new TF1("gr1_fit1","[0]/(x+[1])+[2]",gr1_range[0],gr1_range[1]);
    gr1_fit2 = new TF1("gr1_fit2","[0]/(x+[1])+[2]",gr1_range[1],gr1_range[2]);
  }
  else if(fitIB == "expo"){
    gr1_fit1 = new TF1("gr1_fit1","expo",gr1_range[0],gr1_range[1]);
    gr1_fit2 = new TF1("gr1_fit2","expo",gr1_range[1],gr1_range[2]);
  }
  else if(fitIB == "expo_invx"){
    gr1_fit1 = new TF1("gr1_fit1","expo",gr1_range[0],gr1_range[1]);
    gr1_fit2 = new TF1("gr1_fit2","[0]/(x+[1])+[2]",gr1_range[1],gr1_range[2]);
  }
  gr1_fit3 = new TF1("gr1_fit3","pol1",gr1_range[2],gr1_range[3]);
  
  gr1_fit1->SetLineWidth(2);
  gr1_fit2->SetLineWidth(2);
  gr1_fit3->SetLineWidth(2);
  
  gr1_fit1->SetLineColor(kRed);
  gr1_fit2->SetLineColor(kGreen);
  gr1_fit3->SetLineColor(kBlue);

  //gr1_fit1->SetParLimits(0,0,0.16);
  
  cout << "//////////////////// Now fitting on EtaRegion1 ... ////////////////////" << endl;
 
  // Draw fitting and its uncertainties //
  
  gr1->Fit(gr1_fit1,"R");
  
  //TGraphErrors *gr1_fit1_err = new TGraphErrors(5);
  //for(int i=0; i<5; i++) gr1_fit1_err->SetPoint(i,0.001*i,0);
  //(TVirtualFitter::GetFitter())->GetConfidenceIntervals(gr1_fit1_err);
  //gr1_fit1_err->SetFillColor(4);
  //gr1_fit1_err->SetFillStyle(3001);
  //gr1_fit1_err->Draw("3 same");
  
  gr1->Fit(gr1_fit2,"R+");

  //TGraphErrors *gr1_fit2_err = new TGraphErrors(13);
  //for(int i=0; i<13; i++) gr1_fit2_err->SetPoint(i,0.004+0.001*i,0);
  //(TVirtualFitter::GetFitter())->GetConfidenceIntervals(gr1_fit2_err);
  //gr1_fit2_err->SetFillColor(4);
  //gr1_fit2_err->SetFillStyle(3001);
  //gr1_fit2_err->Draw("3 same");
  
  gr1->Fit(gr1_fit3,"R+");

  //TGraphErrors *gr1_fit3_err = new TGraphErrors(27);
  //for(int i=0; i<27; i++) gr1_fit3_err->SetPoint(i,0.015+0.001*i,0);
  //(TVirtualFitter::GetFitter())->GetConfidenceIntervals(gr1_fit3_err);
  //gr1_fit3_err->SetFillColor(4);
  //gr1_fit3_err->SetFillStyle(3001);
  //gr1_fit3_err->Draw("3 same");

  // show the chisquare over ndf
  double Chisquare1_1 = gr1_fit1->GetChisquare();
  TString Chisquare1_1_t = Form("%f",Chisquare1_1);
  Chisquare1_1_t = Chisquare1_1_t(0,7);
  int ndf1_1 = gr1_fit1->GetNDF();
  TString ndf1_1_t = Form("%d",ndf1_1);
  double Chisquare1_2 = gr1_fit2->GetChisquare();
  TString Chisquare1_2_t = Form("%f",Chisquare1_2);
  Chisquare1_2_t = Chisquare1_2_t(0,7);
  int ndf1_2 = gr1_fit2->GetNDF();
  TString ndf1_2_t = Form("%d",ndf1_2);
  double Chisquare1_3 = gr1_fit3->GetChisquare();
  TString Chisquare1_3_t = Form("%f",Chisquare1_3);
  Chisquare1_3_t = Chisquare1_3_t(0,7);
  int ndf1_3 = gr1_fit3->GetNDF();
  TString ndf1_3_t = Form("%d",ndf1_3);

  TLegend* gr1_legend = new TLegend(0.65,0.7,0.9,0.9);
  gr1_legend->AddEntry(gr1_fit1,"high pt","l");
  //gr1_legend->AddEntry((TObject*)0,"#chi^{2}/ndf : "+Chisquare1_1_t+"/"+ndf1_1_t,"");
  gr1_legend->AddEntry(gr1_fit2,"medium pt","l");
  //gr1_legend->AddEntry((TObject*)0,"#chi^{2}/ndf : "+Chisquare1_2_t+"/"+ndf1_2_t,"");
  gr1_legend->AddEntry(gr1_fit3,"low pt","l");
  //gr1_legend->AddEntry((TObject*)0,"#chi^{2}/ndf : "+Chisquare1_3_t+"/"+ndf1_3_t,"");
  gr1_legend->Draw();


  // Done and repeat for EtaRegion2, 3 //
  
  c2->cd();
  
  TGraphErrors* gr2 = new TGraphErrors(X_2.size(),&X_2[0],&Y_2[0],&EX_2[0],&EY_2[0]);
  gr2->SetMarkerStyle(20);
  //gr2->SetMarkerSize(0.8);
  //gr2->SetMarkerColor(kMagenta+2);
  gr2->SetLineColor(15);
  //gr2->SetTitle("ChargeFlip_0.8#leq|#eta|<1.4442 ("+User_ID.at(i)+")");
  gr2->SetTitle("ChargeFlip_0.8#leq|#eta|<1.4442");
  gr2->SetMinimum(0.);
  gr2->Draw("ZAP");
  gr2->GetXaxis()->SetRangeUser(0.,0.04);
  gr2->GetXaxis()->SetTitle("#scale[0.8]{1/p_{T} (GeV^{-1})}");
  gr2->GetXaxis()->SetTickLength(0.025);
  gr2->GetXaxis()->SetLabelSize(0.025);
  gr2->GetYaxis()->SetLabelSize(0.025);
  if(zoom == "y") gr2->GetYaxis()->SetRangeUser(0.,0.004);
  
  
  vector<double> gr2_range = {0, 0.003, 0.034, 0.04};

  TF1 *gr2_fit1, *gr2_fit2, *gr2_fit3;

  if(fitOB == "pol1"){
    gr2_fit1 = new TF1("gr2_fit1","pol1",gr2_range[0],gr2_range[1]);
    gr2_fit2 = new TF1("gr2_fit2","pol1",gr2_range[1],gr2_range[2]);
  }
  else if(fitOB == "invx"){
    gr2_fit1 = new TF1("gr2_fit1","[0]/(x+[1])+[2]",gr2_range[0],gr2_range[1]);
    gr2_fit2 = new TF1("gr2_fit2","[0]/(x+[1])+[2]",gr2_range[1],gr2_range[2]);
  }
  else if(fitOB == "expo"){
    gr2_fit1 = new TF1("gr2_fit1","expo",gr2_range[0],gr2_range[1]);
    gr2_fit2 = new TF1("gr2_fit2","expo",gr2_range[1],gr2_range[2]);
  }
  else if(fitOB == "expo_invx"){
    gr2_fit1 = new TF1("gr2_fit1","expo",gr2_range[0],gr2_range[1]);
    gr2_fit2 = new TF1("gr2_fit2","[0]/(x+[1])+[2]",gr2_range[1],gr2_range[2]);
  }
  gr2_fit3 = new TF1("gr2_fit3","pol1",gr2_range[2],gr2_range[3]);
  
  gr2_fit1->SetLineWidth(2);
  gr2_fit2->SetLineWidth(2);
  gr2_fit3->SetLineWidth(2);
  
  gr2_fit1->SetLineColor(kRed);
  gr2_fit2->SetLineColor(kGreen);
  gr2_fit3->SetLineColor(kBlue);
  
  cout << endl << "//////////////////// Now fitting on EtaRegion2 ... ////////////////////" << endl;
  
  gr2->Fit(gr2_fit1,"R");
  
  //TGraphErrors *gr2_fit1_err = new TGraphErrors(12);
  //for(int i=0; i<12; i++) gr2_fit1_err->SetPoint(i,0.0005*i,0);
  //(TVirtualFitter::GetFitter())->GetConfidenceIntervals(gr2_fit1_err);
  //gr2_fit1_err->SetFillColor(4);
  //gr2_fit1_err->SetFillStyle(3001);
  //gr2_fit1_err->Draw("3 same");
  
  gr2->Fit(gr2_fit2,"R+");

  //TGraphErrors *gr2_fit2_err = new TGraphErrors(22);
  //for(int i=0; i<22; i++) gr2_fit2_err->SetPoint(i,0.005+0.0005*i,0);
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
 
  double Chisquare2_1 = gr2_fit1->GetChisquare();
  TString Chisquare2_1_t = Form("%f",Chisquare2_1);
  Chisquare2_1_t = Chisquare2_1_t(0,7);
  int ndf2_1 = gr2_fit1->GetNDF();
  TString ndf2_1_t = Form("%d",ndf2_1);
  double Chisquare2_2 = gr2_fit2->GetChisquare();
  TString Chisquare2_2_t = Form("%f",Chisquare2_2);
  Chisquare2_2_t = Chisquare2_2_t(0,7);
  int ndf2_2 = gr2_fit2->GetNDF();
  TString ndf2_2_t = Form("%d",ndf2_2);
  double Chisquare2_3 = gr2_fit3->GetChisquare();
  TString Chisquare2_3_t = Form("%f",Chisquare2_3);
  Chisquare2_3_t = Chisquare2_3_t(0,7);
  int ndf2_3 = gr2_fit3->GetNDF();
  TString ndf2_3_t = Form("%d",ndf2_3);

  TLegend* gr2_legend = new TLegend(0.65,0.7,0.9,0.9);
  gr2_legend->AddEntry(gr2_fit1,"high pt","l");
  //gr2_legend->AddEntry((TObject*)0,"#chi^{2}/ndf : "+Chisquare2_1_t+"/"+ndf2_1_t,"");
  gr2_legend->AddEntry(gr2_fit2,"medium pt","l");
  //gr2_legend->AddEntry((TObject*)0,"#chi^{2}/ndf : "+Chisquare2_2_t+"/"+ndf2_2_t,"");
  gr2_legend->AddEntry(gr2_fit3,"low pt","l");
  //gr2_legend->AddEntry((TObject*)0,"#chi^{2}/ndf : "+Chisquare2_3_t+"/"+ndf2_3_t,"");
  gr2_legend->Draw();

  
  c3->cd();
  
  TGraphErrors* gr3 = new TGraphErrors(X_3.size(),&X_3[0],&Y_3[0],&EX_3[0],&EY_3[0]);
  gr3->SetMarkerStyle(20);
  //gr3->SetMarkerSize(0.8);
  //gr3->SetMarkerColor(kMagenta+2);
  gr3->SetLineColor(15);
  //gr3->SetTitle("ChargeFlip_1.556#leq|#eta|<2.5 ("+User_ID.at(i)+")");
  gr3->SetTitle("ChargeFlip_1.556#leq|#eta|<2.5");
  gr3->SetMinimum(0.);
  gr3->Draw("ZAP");
  gr3->GetXaxis()->SetRangeUser(0.,0.04);
  gr3->GetXaxis()->SetTitle("#scale[0.8]{1/p_{T} (GeV^{-1})}");
  gr3->GetXaxis()->SetTickLength(0.025);
  gr3->GetXaxis()->SetLabelSize(0.025);
  gr3->GetYaxis()->SetLabelSize(0.025);
  if(zoom == "y") gr3->GetYaxis()->SetRangeUser(0.,0.02);
  

  vector<double> gr3_range = {0., 0.004, 0.022, 0.04};

  TF1 *gr3_fit1, *gr3_fit2, *gr3_fit3;

  if(fitEC == "invx_only"){
    gr3_fit1 = new TF1("gr3_fit1","[0]/(x+[1])+[2]",0.,0.04);
    gr3_fit1->SetLineWidth(2);
    gr3_fit1->SetLineColor(kGreen);
  }
  else{
    if(fitEC == "pol1"){
      gr3_fit1 = new TF1("gr3_fit1","pol1",gr3_range[0],gr3_range[1]);
      gr3_fit2 = new TF1("gr3_fit2","pol1",gr3_range[1],gr3_range[2]);
    }
    else if(fitEC == "invx"){
      gr3_fit1 = new TF1("gr3_fit1","[0]/(x+[1])+[2]",gr3_range[0],gr3_range[1]);
      gr3_fit2 = new TF1("gr3_fit2","[0]/(x+[1])+[2]",gr3_range[1],gr3_range[2]);
    }
    else if(fitEC == "expo"){
      gr3_fit1 = new TF1("gr3_fit1","expo",gr3_range[0],gr3_range[1]);
      gr3_fit2 = new TF1("gr3_fit2","expo",gr3_range[1],gr3_range[2]);
    }
    else if(fitEC == "expo_invx"){
      gr3_fit1 = new TF1("gr3_fit1","expo",gr3_range[0],gr3_range[1]);
      gr3_fit2 = new TF1("gr3_fit2","[0]/(x+[1])+[2]",gr3_range[1],gr3_range[2]);
    }
    gr3_fit3 = new TF1("gr3_fit3","pol1",gr3_range[2],gr3_range[3]);

    gr3_fit1->SetLineWidth(2);
    gr3_fit2->SetLineWidth(2);
    gr3_fit3->SetLineWidth(2);
    
    gr3_fit1->SetLineColor(kRed);
    gr3_fit2->SetLineColor(kGreen);
    gr3_fit3->SetLineColor(kBlue);
  }
  
  cout << endl << "//////////////////// Now fitting on EtaRegion3 ... ////////////////////" << endl;
  
  gr3->Fit(gr3_fit1,"R");
  
  //TGraphErrors *gr3_fit1_err = new TGraphErrors(12);
  //for(int i=0; i<12; i++) gr3_fit1_err->SetPoint(i,0.001*i,0);
  //(TVirtualFitter::GetFitter())->GetConfidenceIntervals(gr3_fit1_err);
  //gr3_fit1_err->SetFillColor(4);
  //gr3_fit1_err->SetFillStyle(3001);
  //gr3_fit1_err->Draw("3 same");
  
  //gr3->Fit(gr3_fit2,"R+");

  //TGraphErrors *gr3_fit2_err = new TGraphErrors(10);
  //for(int i=0; i<10; i++) gr3_fit2_err->SetPoint(i,0.011+0.001*i,0);
  //(TVirtualFitter::GetFitter())->GetConfidenceIntervals(gr3_fit2_err);
  //gr3_fit2_err->SetFillColor(4);
  //gr3_fit2_err->SetFillStyle(3001);
  //gr3_fit2_err->Draw("3 same");
  
  //gr3->Fit(gr3_fit3,"R+");

  //TGraphErrors *gr3_fit3_err = new TGraphErrors(22);
  //for(int i=0; i<22; i++) gr3_fit3_err->SetPoint(i,0.02+0.001*i,0);
  //(TVirtualFitter::GetFitter())->GetConfidenceIntervals(gr3_fit3_err);
  //gr3_fit3_err->SetFillColor(4);
  //gr3_fit3_err->SetFillStyle(3001);
  //gr3_fit3_err->Draw("3 same");
 
  if(fitEC.Contains("only")){
    // show the chisqaured and fit function
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
    //TPaveText *pt3 = new TPaveText(0.55,0.8,0.9,0.9,"NDC");
    //pt3->SetShadowColor(0);
    //pt3->SetFillColor(0);
    //pt3->AddText("#chi^{2}/ndf : "+Chisquare3_t+"/"+ndf3_t);
    //if(par3[2] < 0) pt3->AddText("Fit func : #frac{"+par3_0+"}{x"+par3_1+"}"+par3_2);
		//else pt3->AddText("Fit func : #frac{"+par3_0+"}{x"+par3_1+"}+"+par3_2);
    //pt3->AddText("CF rate at inf GeV : "+rate3_t);
    //pt3->Draw(); 
  }
  else{  
    TLegend* gr3_legend = new TLegend(0.75,0.8,0.9,0.9);
    gr3_legend->AddEntry(gr3_fit1,"high pt","l");
    gr3_legend->AddEntry(gr3_fit2,"medium pt","l");
    gr3_legend->AddEntry(gr3_fit3,"low pt","l");
    gr3_legend->Draw();
  }


  // Scan the best range to get smooth function

  if(scan == "y"){
    vector<TGraphErrors*> grs;
    grs.push_back(gr1);
    grs.push_back(gr2);
    grs.push_back(gr3);
    int how_many;
    if(fitEC.Contains("only")) how_many = 2;
    else how_many = 3;

    cout << "================fit optimizing...=================" << endl;

    for(int i=0; i<how_many; i++){
      cout << "//////////////////// Eta region " << i+1 << " candidates ////////////////////" << endl;

      // Test each functions at intersection
      vector<vector<double>> bndrys;
      vector<double> RelErrs, Chi2overNDFs;
      double bndry12;
      double bndry23;

      for(int j=2; j<6; j++){
        bndry12 = 0.001*j;
        map<double, double> RelErr, Chi2overNDF;
        for(int k=j+1; k<39; k++){
          bndry23 = 0.001*k;
          TF1 *fit_temp1 = new TF1("fit_temp1","expo",0.,bndry12);
          TF1 *fit_temp2 = new TF1("fit_temp2","[0]/(x+[1])+[2]",bndry12,bndry23);
          TF1 *fit_temp3 = new TF1("fit_temp3","pol1",bndry23,0.04);
          grs.at(i)->Fit(fit_temp1,"RNQ");
          grs.at(i)->Fit(fit_temp2,"RNQ+");
          grs.at(i)->Fit(fit_temp3,"RNQ+"); //JH : R -> use range. N -> no drawing. Q -> quiet.

          double par1[2];
          double par2[3];
          double par3[2];
          fit_temp1->GetParameters(par1);
          fit_temp2->GetParameters(par2);
          fit_temp3->GetParameters(par3);
          
          double chi2_1 = fit_temp1->GetChisquare();
          double chi2_2 = fit_temp2->GetChisquare();
          double chi2_3 = fit_temp3->GetChisquare();
          double ndf1 = fit_temp1->GetNDF();
          double ndf2 = fit_temp2->GetNDF();
          double ndf3 = fit_temp3->GetNDF();
          //NDF == 0 is usually not good, but justified here because the purpose of fitting here is just to get cts shape.
          if(ndf1==0) ndf1 = 1.;
          if(ndf2==0) ndf2 = 1.;
          if(ndf3==0) ndf3 = 1.;

          double highval = TMath::Exp(par1[0]+bndry12*par1[1]);
          double medval12 = par2[0]/(bndry12+par2[1])+par2[2];
          double medval23 = par2[0]/(bndry23+par2[1])+par2[2];
          double lowval = par3[0]+par3[1]*bndry23;

          RelErr[bndry12] = (highval - medval12) / ( (highval+medval12)/2. );
          RelErr[bndry23] = (medval23 - lowval) / ( (medval23+lowval)/2. );
          double RelErrTot = RelErr[bndry12] * RelErr[bndry23];
          Chi2overNDF[bndry12] = (chi2_1/ndf1) * (chi2_2/ndf2);
          Chi2overNDF[bndry23] = (chi2_2/ndf2) * (chi2_3/ndf3);
          double Chi2overNDFTot = (chi2_1/ndf1) * (chi2_2/ndf2) * (chi2_3/ndf3);

          //cout << "CFrate at " << bndry << " in medium pt : " << medval << endl;
          //cout << "CFrate at " << bndry << " in low pt : " << lowval << endl;
          if(fabs(RelErr[bndry12]) < 0.1 && fabs(RelErr[bndry23]) < 0.1){
            cout << "In fit range : [0, " << bndry12 << ", " << bndry23 << ", 0.04]" << endl;
            cout << "rel. error at " << bndry12 << " : " << 100 * RelErr[bndry12] << "%" << endl;
            cout << "rel. error at " << bndry23 << " : " << 100 * RelErr[bndry23] << "%" << endl;
            cout << "rel. error total : " << 100 * RelErrTot << "%" << endl;
            cout << "Chi2/ndf at " << bndry12 << " : " << Chi2overNDF[bndry12] << endl;
            cout << "Chi2/ndf at " << bndry23 << " : " << Chi2overNDF[bndry23] << endl;
            cout << "Chi2/ndf total : " << Chi2overNDFTot << endl;
            vector<double> bndry;
            bndry.push_back(0.);
            bndry.push_back(bndry12);
            bndry.push_back(bndry23);
            bndry.push_back(0.04);
            bndrys.push_back(bndry);
            RelErrs.push_back(RelErrTot);
            Chi2overNDFs.push_back(Chi2overNDFTot);
          }
        }
      }

      double MinRelErr = 10000.;
      double MinChi2overNDF = 10000.;
      vector<double> RelErrOptRange;
      vector<double> Chi2OptRange;
      int this_k_RelErr, this_k_Chi2;
      int bad_Chi2 = 0;
      if(bndrys.size()==0){
        cout << "Too tight Rel. error criteria... consider loosening the condition." << endl;
        return;
      }
      for(int k=0; k<bndrys.size(); k++){
        if(fabs( RelErrs[k] ) < MinRelErr){
          MinRelErr = fabs( RelErrs[k] );
          this_k_RelErr = k;
        }
        if(Chi2overNDFs[k] < MinChi2overNDF){
          MinChi2overNDF = Chi2overNDFs[k];
          this_k_Chi2 = k;
        }
        else bad_Chi2++;
      }
      if(bad_Chi2 == bndrys.size()){
        cout << "Too bad Chi2... consider other fitting functions." << endl;
        return;
      }
      RelErrOptRange = bndrys[this_k_RelErr];
      Chi2OptRange = bndrys[this_k_Chi2];
      cout << "!!!!!!!!!!!!!!!rel. error opt at [0, " << RelErrOptRange[1] << ", " << RelErrOptRange[2] << ", 0.04]" << " : " << 100 * MinRelErr << "%!!!!!!!!!!!!!!!" << endl;
      cout << ">>>>>>>>>>Chi2/ndf : " << Chi2overNDFs[this_k_RelErr] << endl;
      cout << "!!!!!!!!!!!!!!!Chi2/ndf opt at [0, " << Chi2OptRange[1] << ", " << Chi2OptRange[2] << ", 0.04]" << " : " << MinChi2overNDF <<  "!!!!!!!!!!!!!!!" << endl; //JH : the lower is the better (<1 is the best)
      cout << ">>>>>>>>rel. error : " << 100 * RelErrs[this_k_Chi2] << "%" << endl;

      vector<double> opts12 = {0.003, 0.003, 0.003}; // to check opt results by eyes
      vector<double> opts23 = {0.013, 0.034, 0.015}; // to check opt results by eyes
      TF1 *fit_opt1 = new TF1("fit_opt1","expo",0.,opts12.at(i));
      TF1 *fit_opt2 = new TF1("fit_opt2","[0]/(x+[1])+[2]",opts12.at(i),opts23.at(i));
      TF1 *fit_opt3 = new TF1("fit_opt3","pol1",opts23.at(i),0.04);
      fit_opt1->SetLineColor(kRed);
      fit_opt2->SetLineColor(kGreen);
      fit_opt3->SetLineColor(kBlue);
      grs.at(i)->Fit(fit_opt1,"R");
      grs.at(i)->Fit(fit_opt2,"R+");
      grs.at(i)->Fit(fit_opt3,"R+");

    }
/*
      // What if using just a single function
      TF1 *fit_alt = new TF1("fit_alt","[0]/(x+[1])+[2]",0.004,0.04);
      fit_alt->SetLineColor(kRed);
      grs.at(i)->Fit(fit_alt,"RQ");
      double chi2_alt = fit_alt->GetChisquare();
      double ndf_alt = fit_alt->GetNDF();
      cout << "////////////////////////////////////" << endl;
      cout << "Chi2/ndf with one fitting : " << chi2_alt/ndf_alt << endl;
*/
  }



  if(save == "y"){
    if(zoom == "y"){
      c1->SaveAs(samplename+"/Fit/"+fitIB+"_Zoom_EtaRegion1.png");
      c2->SaveAs(samplename+"/Fit/"+fitOB+"_Zoom_EtaRegion2.png");
      c3->SaveAs(samplename+"/Fit/"+fitEC+"_Zoom_EtaRegion3.png");
    }
    else{
      c1->SaveAs(samplename+"/Fit/"+fitIB+"_EtaRegion1.png");
      c2->SaveAs(samplename+"/Fit/"+fitOB+"_EtaRegion2.png");
      c3->SaveAs(samplename+"/Fit/"+fitEC+"_EtaRegion3.png");
    }
  }

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
