void ClosureTest_All(){

//TString filename = "/data6/Users/jihkim/SKFlatOutput/Run2Legacy_v4/ChargeFlip/2016/ClosureTest__/ChargeFlip_DYJets.root";
TString filename = "/data6/Users/jihkim/SKFlatOutput/Run2Legacy_v4/ChargeFlip/2016/ClosureTest__/ChargeFlip_All.root";
TFile* f1 = new TFile(filename);

TString samplename = filename(filename.Last('/')+12,filename.Length());
samplename.ReplaceAll(".root","");

gSystem->Exec("mkdir "+samplename);

TString User_ID = "HNTightV1";

//TH1D* h0 = (TH1D*)f1->Get(User_ID+"/ClosureTest/ZMass_SS");
TH1D* h0 = (TH1D*)f1->Get(User_ID+"/ClosureTest/ZMass_prmpt_SS");

// 1.0% //

TH1D* h1 = (TH1D*)f1->Get(User_ID+"/ClosureTest/ZMass_OS_CFweighted_shifted_10");

vector<double> x_1, ex_1, x_2, ex_2, x_3, ex_3;
for (int i=0; i<30; i++) {
  x_1.push_back(75+(2*i+1)*(0.5)); ex_1.push_back(0.5); 
  x_2.push_back(75+(2*i+1)*(0.5)); ex_2.push_back(0.5); 
  x_3.push_back(75+(2*i+1)*(0.5)); ex_3.push_back(0.5); 
}
vector<double> y_1, ey_1, y_2, ey_2, y_3, ey_3, ey_3_syst;
for (int i=0; i<30; i++) {
  y_1.push_back(h1->GetBinContent(i+1));
  ey_1.push_back(h1->GetBinError(i+1));
  y_2.push_back(h0->GetBinContent(i+1));
  ey_2.push_back(h0->GetBinError(i+1));
  y_3.push_back(h0->GetBinContent(i+1)/h1->GetBinContent(i+1));
  ey_3.push_back(y_3[i]*(sqrt(pow(h1->GetBinError(i+1)/h1->GetBinContent(i+1),2)+pow(h0->GetBinError(i+1)/h0->GetBinContent(i+1),2))));
  ey_3_syst.push_back(ey_3[i]+0.01);
}

// Draw the plots //

TCanvas* c1 = new TCanvas("c1","ZMass : OS_CFweighted_1.0% vs SS",1000,100,900,800);
c1->Divide(1,2);

c1->cd(1);

gPad->SetPad(0,0.35,1,1);
gPad->SetTopMargin(0.08);
gPad->SetBottomMargin(0.02);

TGraphErrors* gr1 = new TGraphErrors(x_1.size(),&x_1[0],&y_1[0],&ex_1[0],&ey_1[0]);
gr1->SetFillColor(20);
gr1->SetTitle("ZMass : OS_CFweighted_1.0% vs SS");
//gr1->GetXaxis()->SetRangeUser(70,110);
//gr1->SetMinimum(0.);
gr1->Draw("AB2"); // Z : do not draw small horizontal/vertical lines the end of the error bars
gr1->GetXaxis()->SetTickLength(0.025);
gr1->GetXaxis()->SetLabelSize(0);
gr1->GetYaxis()->SetLabelSize(0.025);

TGraphErrors* gr2 = new TGraphErrors(x_2.size(),&x_2[0],&y_2[0],&ex_2[0],&ey_2[0]);
gr2->SetMarkerStyle(20);
//gr2->SetMarkerColor(kMagenta+2);
//gr2->SetLineColor(15);
gr2->Draw("ZP SAME"); 

TLegend* legend = new TLegend(0.15,0.6,0.4,0.7);
legend->AddEntry(gr2,"observed","lp");
legend->AddEntry(gr1,"predicted","f");
legend->Draw();


c1->cd(2);

gPad->SetPad(0,0,1,0.35);
gPad->SetTopMargin(0.05);
gPad->SetBottomMargin(0.15);

// Just ratio plot

TGraphErrors* gr3 = new TGraphErrors(x_3.size(),&x_3[0],&y_3[0],&ex_3[0],&ey_3_syst[0]);
gr3->SetTitle("");
gr3->SetFillColor(17);
gr3->Draw("A2");
gr3->GetXaxis()->SetLabelSize(0.06);
gr3->GetXaxis()->SetTitle("#scale[2.2]{m(ee) (GeV)}");
gr3->GetXaxis()->SetTitleOffset(1.6);
gr3->GetXaxis()->SetTickLength(0.05);
gr3->GetYaxis()->SetLabelSize(0.05);
gr3->GetYaxis()->SetTitle("#scale[2.2]{obs. / pred.}");
gr3->GetYaxis()->SetTitleOffset(0.8);
gr3->GetYaxis()->SetRangeUser(0,2);

TGraphErrors* gr4 = new TGraphErrors(x_3.size(),&x_3[0],&y_3[0],&ex_3[0],&ey_3[0]);
gr4->SetMarkerStyle(20);
gr4->SetMarkerColor(kBlue-4);
gr4->SetMarkerSize(0.8);
gr4->Draw("ZP SAME");

gPad->SetGridx();
gPad->SetGridy();


TLine* LineAtOne = new TLine(gr3->GetXaxis()->GetXmin(),1,gr3->GetXaxis()->GetXmax(),1);
LineAtOne->SetLineStyle(kDashed);
LineAtOne->SetLineWidth(2);
LineAtOne->SetLineColor(2);
LineAtOne->Draw();


cout << "N(SS) : " << h0->Integral() << endl;
cout << "N(OS_CFweighted_shifted_1.0%) : " << h1->Integral() << endl;
cout << "SS/OS ratio : " << h0->Integral()/h1->Integral() << " +- " << (h0->Integral()/h1->Integral()) * sqrt(1./h0->Integral() + 1./h1->Integral()) << endl;


//c1->cd(3);
//
//gPad->SetPad(0,0,1,0.2);
//gPad->SetTopMargin(0.05);
//gPad->SetBottomMargin(0.15);
//
//int n = h0->GetNbinsX();
//double res[n], x[n];
//h0->Chi2Test(h1,"UW",res);
//for(int i=0;i<n;i++) x[i]=h0->GetBinLowEdge(1)+h0->GetBinWidth(1)/2.+i*h0->GetBinWidth(1);
//TGraph *resgr = new TGraph(n,x,res);
//resgr->GetXaxis()->SetRangeUser(70,110);
//resgr->SetMarkerStyle(20);
//resgr->SetMarkerColor(2);
//resgr->SetTitle("");
//resgr->Draw("APL");
//resgr->GetXaxis()->SetLabelSize(0.06);
//resgr->GetXaxis()->SetTitle("#scale[2.2]{m(ee) (GeV)}");
//resgr->GetXaxis()->SetTitleOffset(1.6);
//resgr->GetXaxis()->SetTickLength(0.05);
//resgr->GetYaxis()->SetLabelSize(0.05);
//resgr->GetYaxis()->SetTitle("#scale[1.8]{Normalized #chi^{2} Residuals}");
//resgr->GetYaxis()->SetTitleOffset(0.6);
//
//TCanvas* c10 = new TCanvas("c10","QQ plot",1100,10,500,500);
//
//TF1 *f = new TF1("f","TMath::Gaus(x,0,1)",-10,10);
//TGraphQQ *qqplot = new TGraphQQ(n,res,f);
//qqplot->SetMarkerStyle(20);
//qqplot->SetMarkerColor(4);
//qqplot->SetMarkerSize(.9);
//qqplot->SetTitle("Q-Q plot of Normalized Residuals");
//qqplot->Draw("AP");

TH1D* H1 = (TH1D*)f1->Get(User_ID+"/ClosureTest/ZMass_prmpt_OS_CFweighted");

vector<double> X_1, EX_1, X_2, EX_2, X_3, EX_3;
for (int i=0; i<30; i++) {
  X_1.push_back(75+(2*i+1)*(0.5)); EX_1.push_back(0.5); 
  X_2.push_back(75+(2*i+1)*(0.5)); EX_2.push_back(0.5); 
  X_3.push_back(75+(2*i+1)*(0.5)); EX_3.push_back(0.5); 
}
vector<double> Y_1, EY_1, Y_2, EY_2, Y_3, EY_3;
for (int i=0; i<30; i++) {
  Y_1.push_back(H1->GetBinContent(i+1));
  EY_1.push_back(H1->GetBinError(i+1));
  Y_2.push_back(h0->GetBinContent(i+1));
  EY_2.push_back(h0->GetBinError(i+1));
  Y_3.push_back(h0->GetBinContent(i+1)/H1->GetBinContent(i+1));
  EY_3.push_back(Y_3[i]*(sqrt(pow(H1->GetBinError(i+1)/H1->GetBinContent(i+1),2)+pow(h0->GetBinError(i+1)/h0->GetBinContent(i+1),2))));
}

// Draw the plots //

TCanvas* c2 = new TCanvas("c2","ZMass : OS_CFweighted vs SS",100,100,900,800);
c2->Divide(1,2);

c2->cd(1);

gPad->SetPad(0,0.35,1,1);
gPad->SetTopMargin(0.08);
gPad->SetBottomMargin(0.02);

TGraphErrors* GR1 = new TGraphErrors(X_1.size(),&X_1[0],&Y_1[0],&EX_1[0],&EY_1[0]);
GR1->SetFillColor(20);
GR1->SetTitle("ZMass : OS_CFweighted vs SS");
//GR1->GetXaxis()->SetRangeUser(70,110);
//GR1->SetMinimum(0.);
GR1->Draw("AB2"); // Z : do not draw small horizontal/vertical lines the end of the error bars
GR1->GetXaxis()->SetTickLength(0.025);
GR1->GetXaxis()->SetLabelSize(0);
GR1->GetYaxis()->SetLabelSize(0.025);

TGraphErrors* GR2 = new TGraphErrors(X_2.size(),&X_2[0],&Y_2[0],&EX_2[0],&EY_2[0]);
GR2->SetMarkerStyle(20);
//GR2->SetMarkerColor(kMagenta+2);
GR2->Draw("ZP SAME"); 

TLegend* legend_2 = new TLegend(0.15,0.6,0.35,0.7);
legend_2->AddEntry(GR2,"observed","lp");
legend_2->AddEntry(GR1,"predicted","f");
legend_2->Draw();


c2->cd(2);

gPad->SetPad(0,0,1,0.35);
gPad->SetTopMargin(0.05);
gPad->SetBottomMargin(0.15);

// Just ratio plot

TGraphErrors* GR3 = new TGraphErrors(X_3.size(),&X_3[0],&Y_3[0],&EX_3[0],&EY_3[0]);
GR3->SetMarkerStyle(20);
GR3->SetMarkerColor(kBlue-4);
GR3->SetMarkerSize(0.8);
GR3->SetTitle("");
GR3->Draw("ZAP");
GR3->GetXaxis()->SetLabelSize(0.06);
GR3->GetXaxis()->SetTitle("#scale[2.2]{m(ee) (GeV)}");
GR3->GetXaxis()->SetTitleOffset(1.6);
GR3->GetXaxis()->SetTickLength(0.05);
GR3->GetYaxis()->SetLabelSize(0.05);
GR3->GetYaxis()->SetTitle("#scale[2.2]{obs. / pred.}");
GR3->GetYaxis()->SetTitleOffset(0.8);
GR3->GetYaxis()->SetRangeUser(0,2);
gPad->SetGridx();
gPad->SetGridy();

TLine* LineAtOne_2 = new TLine(GR3->GetXaxis()->GetXmin(),1,GR3->GetXaxis()->GetXmax(),1);
LineAtOne_2->SetLineStyle(kDashed);
LineAtOne_2->SetLineWidth(2);
LineAtOne_2->SetLineColor(2);
LineAtOne_2->Draw();

////////////////////////////////////////////////////////////////////////////////////////////////////////

//TH1D* h2 = (TH1D*)f1->Get(User_ID+"/ClosureTest/pt1_SS");
TH1D* h2 = (TH1D*)f1->Get(User_ID+"/ClosureTest/pt1_prmpt_SS");
TH1D* h3 = (TH1D*)f1->Get(User_ID+"/ClosureTest/pt1_OS_CFweighted_shifted_10");
//TH1D* h4 = (TH1D*)f1->Get(User_ID+"/ClosureTest/pt2_SS");
TH1D* h4 = (TH1D*)f1->Get(User_ID+"/ClosureTest/pt2_prmpt_SS");
TH1D* h5 = (TH1D*)f1->Get(User_ID+"/ClosureTest/pt2_OS_CFweighted_shifted_10");
//TH1D* h6 = (TH1D*)f1->Get(User_ID+"/ClosureTest/MET_SS");
TH1D* h6 = (TH1D*)f1->Get(User_ID+"/ClosureTest/MET_prmpt_SS");
TH1D* h7 = (TH1D*)f1->Get(User_ID+"/ClosureTest/MET_OS_CFweighted_shifted_10");

vector<double> pt1_SS_x, pt1_SS_ex, pt2_SS_x, pt2_SS_ex, MET_SS_x, MET_SS_ex, pt1_OS_x, pt1_OS_ex, pt2_OS_x, pt2_OS_ex, MET_OS_x, MET_OS_ex, pt1_R_x, pt1_R_ex, pt2_R_x, pt2_R_ex, MET_R_x, MET_R_ex;
for (int i=0; i<55; i++) {
  pt1_SS_x.push_back(25+(2*i+1)*(0.5)); pt1_SS_ex.push_back(0.5); 
  pt1_OS_x.push_back(25+(2*i+1)*(0.5)); pt1_OS_ex.push_back(0.5); 
  pt1_R_x.push_back(25+(2*i+1)*(0.5)); pt1_R_ex.push_back(0.5); 
  pt2_SS_x.push_back(25+(2*i+1)*(0.5)); pt2_SS_ex.push_back(0.5); 
  pt2_OS_x.push_back(25+(2*i+1)*(0.5)); pt2_OS_ex.push_back(0.5); 
  pt2_R_x.push_back(25+(2*i+1)*(0.5)); pt2_R_ex.push_back(0.5); 
}
for (int i=0; i<80; i++){
  MET_SS_x.push_back((2*i+1)*0.5); MET_SS_ex.push_back(0.5);
  MET_OS_x.push_back((2*i+1)*0.5); MET_OS_ex.push_back(0.5);
  MET_R_x.push_back((2*i+1)*0.5); MET_R_ex.push_back(0.5);
}
vector<double> pt1_SS_y, pt1_SS_ey, pt2_SS_y, pt2_SS_ey, MET_SS_y, MET_SS_ey, pt1_OS_y, pt1_OS_ey, pt2_OS_y, pt2_OS_ey, MET_OS_y, MET_OS_ey, pt1_R_y, pt1_R_ey, pt1_R_ey_syst, pt2_R_y, pt2_R_ey, pt2_R_ey_syst, MET_R_y, MET_R_ey, MET_R_ey_syst;
for (int i=0; i<55; i++) {
  pt1_SS_y.push_back(h2->GetBinContent(i+6));
  pt1_SS_ey.push_back(h2->GetBinError(i+6));
  pt1_OS_y.push_back(h3->GetBinContent(i+6));
  pt1_OS_ey.push_back(h3->GetBinError(i+6));
  pt1_R_y.push_back(h2->GetBinContent(i+6)/h3->GetBinContent(i+6));
  pt1_R_ey.push_back(pt1_R_y[i]*(sqrt(pow(h3->GetBinError(i+6)/h3->GetBinContent(i+6),2)+pow(h2->GetBinError(i+6)/h2->GetBinContent(i+6),2))));
  pt1_R_ey_syst.push_back(pt1_R_ey[i] + 0.01);

  pt2_SS_y.push_back(h4->GetBinContent(i+6));
  pt2_SS_ey.push_back(h4->GetBinError(i+6));
  pt2_OS_y.push_back(h5->GetBinContent(i+6));
  pt2_OS_ey.push_back(h5->GetBinError(i+6));
  pt2_R_y.push_back(h4->GetBinContent(i+6)/h5->GetBinContent(i+6));
  pt2_R_ey.push_back(pt2_R_y[i]*(sqrt(pow(h5->GetBinError(i+6)/h5->GetBinContent(i+6),2)+pow(h4->GetBinError(i+6)/h4->GetBinContent(i+6),2))));
  pt2_R_ey_syst.push_back(pt2_R_ey[i] + 0.01);
}
for (int i=0; i<80; i++){
  MET_SS_y.push_back(h6->GetBinContent(i+1));
  MET_SS_ey.push_back(h6->GetBinError(i+1));
  MET_OS_y.push_back(h7->GetBinContent(i+1));
  MET_OS_ey.push_back(h7->GetBinError(i+1));
  MET_R_y.push_back(h6->GetBinContent(i+1)/h7->GetBinContent(i+1));
  MET_R_ey.push_back(MET_R_y[i]*(sqrt(pow(h7->GetBinError(i+1)/h7->GetBinContent(i+1),2)+pow(h6->GetBinError(i+1)/h6->GetBinContent(i+1),2))));
  MET_R_ey_syst.push_back(MET_R_ey[i] + 0.01);
}

// pt1

TCanvas* c3 = new TCanvas("c3","pt1 : OS_shifted_1.0% vs SS",100,100,900,800);
c3->Divide(1,2);

c3->cd(1);

gPad->SetPad(0,0.35,1,1);
gPad->SetTopMargin(0.08);
gPad->SetBottomMargin(0.02);

TGraphErrors* pt1_OS = new TGraphErrors(pt1_OS_x.size(),&pt1_OS_x[0],&pt1_OS_y[0],&pt1_OS_ex[0],&pt1_OS_ey[0]);
pt1_OS->SetFillColor(20);
pt1_OS->SetTitle("pt1 : OS_CFweighted_1.0% vs SS");
pt1_OS->Draw("AB2"); 
pt1_OS->GetXaxis()->SetTickLength(0.025);
pt1_OS->GetXaxis()->SetLabelSize(0);
pt1_OS->GetYaxis()->SetLabelSize(0.025);

TGraphErrors* pt1_SS = new TGraphErrors(pt1_SS_x.size(),&pt1_SS_x[0],&pt1_SS_y[0],&pt1_SS_ex[0],&pt1_SS_ey[0]);
pt1_SS->SetMarkerStyle(20);
pt1_SS->SetLineColor(15);
pt1_SS->Draw("ZP SAME"); // Z : do not draw small horizontal/vertical lines the end of the error bars

TLegend* legend_pt1 = new TLegend(0.55,0.7,0.8,0.8);
legend_pt1->AddEntry(pt1_SS,"observed","lp");
legend_pt1->AddEntry(pt1_OS,"predicted","f");
legend_pt1->Draw();

c3->cd(2);

gPad->SetPad(0,0,1,0.35);
gPad->SetTopMargin(0.05);
gPad->SetBottomMargin(0.15);

// Just ratio plot

TGraphErrors* pt1_R_syst = new TGraphErrors(pt1_R_x.size(),&pt1_R_x[0],&pt1_R_y[0],&pt1_R_ex[0],&pt1_R_ey_syst[0]);
pt1_R_syst->SetTitle("");
pt1_R_syst->SetFillColor(17);
pt1_R_syst->Draw("A2");
pt1_R_syst->GetXaxis()->SetLabelSize(0.06);
pt1_R_syst->GetXaxis()->SetTitle("#scale[2.2]{P_{T} (GeV)}");
pt1_R_syst->GetXaxis()->SetTitleOffset(1.6);
pt1_R_syst->GetXaxis()->SetTickLength(0.05);
pt1_R_syst->GetYaxis()->SetLabelSize(0.05);
pt1_R_syst->GetYaxis()->SetTitle("#scale[2.2]{obs. / pred.}");
pt1_R_syst->GetYaxis()->SetTitleOffset(0.8);
pt1_R_syst->GetYaxis()->SetRangeUser(0.2,1.4);

TGraphErrors* pt1_R = new TGraphErrors(pt1_R_x.size(),&pt1_R_x[0],&pt1_R_y[0],&pt1_R_ex[0],&pt1_R_ey[0]);
pt1_R->SetMarkerStyle(20);
pt1_R->SetMarkerColor(kBlue-4);
pt1_R->SetMarkerSize(0.8);
pt1_R->Draw("ZP SAME");

gPad->SetGridx();
gPad->SetGridy();

TLine* LineAtOne_pt1 = new TLine(pt1_R->GetXaxis()->GetXmin(),1,pt1_R->GetXaxis()->GetXmax(),1);
LineAtOne_pt1->SetLineStyle(kDashed);
LineAtOne_pt1->SetLineWidth(2);
LineAtOne_pt1->SetLineColor(2);
LineAtOne_pt1->Draw();

// pt2

TCanvas* c4 = new TCanvas("c4","pt2 : OS_shifted_1.0% vs SS",100,100,900,800);
c4->Divide(1,2);

c4->cd(1);

gPad->SetPad(0,0.35,1,1);
gPad->SetTopMargin(0.08);
gPad->SetBottomMargin(0.02);

TGraphErrors* pt2_OS = new TGraphErrors(pt2_OS_x.size(),&pt2_OS_x[0],&pt2_OS_y[0],&pt2_OS_ex[0],&pt2_OS_ey[0]);
pt2_OS->SetFillColor(20);
pt2_OS->SetTitle("pt2 : OS_CFweighted_1.0% vs SS");
pt2_OS->Draw("AB2"); 
pt2_OS->GetXaxis()->SetTickLength(0.025);
pt2_OS->GetXaxis()->SetLabelSize(0);
pt2_OS->GetYaxis()->SetLabelSize(0.025);

TGraphErrors* pt2_SS = new TGraphErrors(pt2_SS_x.size(),&pt2_SS_x[0],&pt2_SS_y[0],&pt2_SS_ex[0],&pt2_SS_ey[0]);
pt2_SS->SetMarkerStyle(20);
pt2_SS->Draw("ZP SAME"); // Z : do not draw small horizontal/vertical lines the end of the error bars

TLegend* legend_pt2 = new TLegend(0.55,0.7,0.8,0.8);
legend_pt2->AddEntry(pt2_SS,"observed","lp");
legend_pt2->AddEntry(pt2_OS,"predicted","f");
legend_pt2->Draw();

c4->cd(2);

gPad->SetPad(0,0,1,0.35);
gPad->SetTopMargin(0.05);
gPad->SetBottomMargin(0.15);

// Just ratio plot

TGraphErrors* pt2_R_syst = new TGraphErrors(pt2_R_x.size(),&pt2_R_x[0],&pt2_R_y[0],&pt2_R_ex[0],&pt2_R_ey_syst[0]);
pt2_R_syst->SetTitle("");
pt2_R_syst->SetFillColor(17);
pt2_R_syst->Draw("A2");
pt2_R_syst->GetXaxis()->SetLabelSize(0.06);
pt2_R_syst->GetXaxis()->SetTitle("#scale[2.2]{P_{T} (GeV)}");
pt2_R_syst->GetXaxis()->SetTitleOffset(1.6);
pt2_R_syst->GetXaxis()->SetTickLength(0.05);
pt2_R_syst->GetYaxis()->SetLabelSize(0.05);
pt2_R_syst->GetYaxis()->SetTitle("#scale[2.2]{obs. / pred.}");
pt2_R_syst->GetYaxis()->SetTitleOffset(0.8);
pt2_R_syst->GetYaxis()->SetRangeUser(0.8,1.2);

TGraphErrors* pt2_R = new TGraphErrors(pt2_R_x.size(),&pt2_R_x[0],&pt2_R_y[0],&pt2_R_ex[0],&pt2_R_ey[0]);
pt2_R->SetMarkerStyle(20);
pt2_R->SetMarkerColor(kBlue-4);
pt2_R->SetMarkerSize(0.8);
pt2_R->Draw("ZP SAME");

gPad->SetGridx();
gPad->SetGridy();

TLine* LineAtOne_pt2 = new TLine(pt2_R->GetXaxis()->GetXmin(),1,pt2_R->GetXaxis()->GetXmax(),1);
LineAtOne_pt2->SetLineStyle(kDashed);
LineAtOne_pt2->SetLineWidth(2);
LineAtOne_pt2->SetLineColor(2);
LineAtOne_pt2->Draw();


// MET

TCanvas* c5 = new TCanvas("c5","MET : OS_shifted_1.0% vs SS",100,100,900,800);
c5->Divide(1,2);

c5->cd(1);

gPad->SetPad(0,0.35,1,1);
gPad->SetTopMargin(0.08);
gPad->SetBottomMargin(0.02);

TGraphErrors* MET_OS = new TGraphErrors(MET_OS_x.size(),&MET_OS_x[0],&MET_OS_y[0],&MET_OS_ex[0],&MET_OS_ey[0]);
MET_OS->SetFillColor(20);
MET_OS->SetTitle("MET : OS_CFweighted_1.0% vs SS");
MET_OS->Draw("AB2"); 
MET_OS->GetXaxis()->SetTickLength(0.025);
MET_OS->GetXaxis()->SetLabelSize(0);
MET_OS->GetYaxis()->SetLabelSize(0.025);

TGraphErrors* MET_SS = new TGraphErrors(MET_SS_x.size(),&MET_SS_x[0],&MET_SS_y[0],&MET_SS_ex[0],&MET_SS_ey[0]);
MET_SS->SetMarkerStyle(20);
MET_SS->Draw("ZP SAME"); // Z : do not draw small horizontal/vertical lines the end of the error bars

TLegend* legend_MET = new TLegend(0.55,0.7,0.8,0.8);
legend_MET->AddEntry(MET_SS,"observed","lp");
legend_MET->AddEntry(MET_OS,"predicted","f");
legend_MET->Draw();

c5->cd(2);

gPad->SetPad(0,0,1,0.35);
gPad->SetTopMargin(0.05);
gPad->SetBottomMargin(0.15);

// Just ratio plot

TGraphErrors* MET_R_syst = new TGraphErrors(MET_R_x.size(),&MET_R_x[0],&MET_R_y[0],&MET_R_ex[0],&MET_R_ey_syst[0]);
MET_R_syst->SetTitle("");
MET_R_syst->SetFillColor(17);
MET_R_syst->Draw("A2");
MET_R_syst->GetXaxis()->SetLabelSize(0.06);
MET_R_syst->GetXaxis()->SetTitle("#scale[2.2]{E^{miss}_{T} (GeV)}");
MET_R_syst->GetXaxis()->SetTitleOffset(1.6);
MET_R_syst->GetXaxis()->SetTickLength(0.05);
MET_R_syst->GetYaxis()->SetLabelSize(0.05);
MET_R_syst->GetYaxis()->SetTitle("#scale[2.2]{obs. / pred.}");
MET_R_syst->GetYaxis()->SetTitleOffset(0.8);
MET_R_syst->GetYaxis()->SetRangeUser(0.6,1.4);

TGraphErrors* MET_R = new TGraphErrors(MET_R_x.size(),&MET_R_x[0],&MET_R_y[0],&MET_R_ex[0],&MET_R_ey[0]);
MET_R->SetMarkerStyle(20);
MET_R->SetMarkerColor(kBlue-4);
MET_R->SetMarkerSize(0.8);
MET_R->Draw("ZP SAME");

gPad->SetGridx();
gPad->SetGridy();

TLine* LineAtOne_MET = new TLine(MET_R->GetXaxis()->GetXmin(),1,MET_R->GetXaxis()->GetXmax(),1);
LineAtOne_MET->SetLineStyle(kDashed);
LineAtOne_MET->SetLineWidth(2);
LineAtOne_MET->SetLineColor(2);
LineAtOne_MET->Draw();

//c1->SaveAs(samplename+"/"+User_ID+"_ZMass.pdf");
//c2->SaveAs(samplename+"/"+User_ID+"_ZMass_NoEshift.pdf");
//c3->SaveAs(samplename+"/"+User_ID+"_pt1.pdf");
//c4->SaveAs(samplename+"/"+User_ID+"_pt2.pdf");
//c5->SaveAs(samplename+"/"+User_ID+"_MET.pdf");
//
//c1->SaveAs(samplename+"/"+User_ID+"_ZMass.png");
//c2->SaveAs(samplename+"/"+User_ID+"_ZMass_NoEshift.png");
//c3->SaveAs(samplename+"/"+User_ID+"_pt1.png");
//c4->SaveAs(samplename+"/"+User_ID+"_pt2.png");
//c5->SaveAs(samplename+"/"+User_ID+"_MET.png");

}
