double background(double *x, double *par){
  return par[0] + par[1]*x[0] + par[2]*x[0]*x[0] + par[3]*x[0]*x[0]*x[0];
}

double background_tmp(double *x, double *par){ //SH asked
  return par[0] + par[1]*x[0];
}

double gaussianPeak(double *x, double *par){
  return par[0]*exp(-0.5*pow((x[0]-par[1])/par[2],2));
}

double fitFunction(double *x, double *par){
  return background(x,par) + gaussianPeak(x,&par[4]);
}

double fitFunction_tmp(double *x, double *par){
  return background_tmp(x,par) + gaussianPeak(x,&par[2]);
}

void ScaleFactor(TString EtaRegion){ // BB, BE, EE

TFile* f1 = new TFile("/data6/Users/jihkim/SKFlatOutput/Run2Legacy_v3/ChargeFlip/2016/ChargeFlipHE__/DATA/ChargeFlip_DoubleEG_total_DYTTLLCF.root");
TH1D* h0 = (TH1D*)f1->Get("ScaleFactor/"+EtaRegion+"_ZMass_SS");
TH1D* h1 = (TH1D*)f1->Get("ScaleFactor/"+EtaRegion+"_ZMass_OS_CFSFweighted_shifted_1.4%");

//if((EtaRegion == "BB")||(EtaRegion == "EE")){
//TH1D* h1 = (TH1D*)f1->Get("ScaleFactor/"+EtaRegion+"_ZMass_OS_CFSFweighted_shifted_1.4%");
//}
//else if(EtaRegion == "BE"){
//TH1D* h1 = (TH1D*)f1->Get("ScaleFactor/"+EtaRegion+"_ZMass_OS_CFSFweighted_shifted_1.4%");
//} FIXME

vector<double> x_1, ex_1, x_2, ex_2, x_3, ex_3;
for (int i=0; i<40; i++) {
  x_1.push_back(70+(2*i+1)*(0.5)); ex_1.push_back(0.5); 
  x_2.push_back(70+(2*i+1)*(0.5)); ex_2.push_back(0.5); 
  x_3.push_back(70+(2*i+1)*(0.5)); ex_3.push_back(0.5); 
}
vector<double> y_1, ey_1, y_2, ey_2, y_3, ey_3;
for (int i=0; i<40; i++) {
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
gr->SetMarkerStyle(20);
//gr->SetMarkerSize(0.8);
//gr->SetMarkerColor(kMagenta+2);
gr->SetLineColor(15);
gr->SetTitle("ZMass : SS2l ("+EtaRegion+")");
gr->GetXaxis()->SetRangeUser(70,110);
//gr->SetMinimum(0.);
gr->Draw("ZAP"); // Z : do not draw small horizontal/vertical lines the end of the error bars
//gr->GetXaxis()->SetLabelSize(0.01);
gr->GetXaxis()->SetTitle("m(ee) (GeV)");
//gr->GetXaxis()->SetTitleOffset(1.6);
//gr->GetXaxis()->SetTickLength(0.05);
//gr->GetYaxis()->SetLabelSize(0.05);

////////////////////// original fitting //////////////////////////////


// create a TF1 with the range from 70 to 110 and 7 parameters
TF1 *fitFcn = new TF1("fitFcn",fitFunction,70,110,7);
fitFcn->SetNpx(500);
//fitFcn->SetLineWidth(4);
fitFcn->SetLineColor(kRed);

//fitFcn->SetParameters(0,0,0,0,100,90,0.5); // Parameters to get SF for BB, EE
fitFcn->SetParameters(0,0,0,0,80,90,0.5); // Parameters to get SF for BE
gr->Fit("fitFcn","V+","ep");


// improve the picture:
TF1 *backFcn = new TF1("backFcn",background,70,110,4);
//backFcn->SetLineColor(kRed);
backFcn->SetLineColor(kBlue);
TF1 *signalFcn = new TF1("signalFcn",gaussianPeak,70,110,3);
signalFcn->SetLineColor(kMagenta-6);
signalFcn->SetNpx(500);
Double_t par[7];

// writes the fit results into the par array
fitFcn->GetParameters(par);

backFcn->SetParameters(par);
backFcn->Draw("same");

signalFcn->SetParameters(&par[4]);
//signalFcn->Draw("same");

// draw the legend
//TLegend *legend_fit=new TLegend(0.6,0.65,0.88,0.85);
//legend_fit->SetTextFont(72);
//legend_fit->SetTextSize(0.04);
//legend_fit->AddEntry(gr,"Data","lpe");
//legend_fit->AddEntry(backFcn,"Background fit","l");
//legend_fit->AddEntry(signalFcn,"Signal fit","l");
//legend_fit->AddEntry(fitFcn,"Global Fit","l");
//legend_fit->Draw();


///////////////////////////// tmp fitting /////////////////////////////

//// create a TF1 with the range from 70 to 110 and 5 parameters
//TF1 *fitFcn_tmp = new TF1("fitFcn_tmp",fitFunction_tmp,70,110,5);
//fitFcn_tmp->SetNpx(500);
////fitFcn_tmp->SetLineWidth(4);
//fitFcn_tmp->SetLineColor(kRed);
//
//fitFcn_tmp->SetParameters(0,0,70,90,0.5); 
//gr->Fit("fitFcn_tmp","V+","ep");
//
//// improve the picture:
//TF1 *backFcn_tmp = new TF1("backFcn_tmp",background_tmp,70,110,4);
////backFcn->SetLineColor(kRed);
//backFcn_tmp->SetLineColor(kBlue);
//TF1 *signalFcn = new TF1("signalFcn",gaussianPeak,70,110,3);
//signalFcn->SetLineColor(kMagenta-6);
//signalFcn->SetNpx(500);
//Double_t par[5];
//
//// writes the fit results into the par array
//fitFcn_tmp->GetParameters(par);
//
//backFcn_tmp->SetParameters(par);
//backFcn_tmp->Draw("same");
//
//signalFcn->SetParameters(&par[2]);
////signalFcn->Draw("same");


////////////////////////////////////////////////////////////////////////



// Draw the comparison plots //

TCanvas* c2 = new TCanvas("c2","ZMass : OS_CFSFweighted vs SS ("+EtaRegion+")",1000,100,900,800);
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
gr1->SetTitle("ZMass : OS_CFSFweighted_1.4% vs SS ("+EtaRegion+")");
//gr1->GetXaxis()->SetRangeUser(70,110);
//gr1->SetMinimum(0.);
gr1->Draw("ZAP"); // Z : do not draw small horizontal/vertical lines the end of the error bars
gr1->GetXaxis()->SetTickLength(0.025);
gr1->GetXaxis()->SetLabelSize(0);
gr1->GetYaxis()->SetLabelSize(0.025);

TGraphErrors* gr2 = new TGraphErrors(x_2.size(),&x_2[0],&y_2[0],&ex_2[0],&ey_2[0]);
gr2->SetMarkerStyle(20);
gr2->SetMarkerColor(kMagenta+2);
gr2->SetLineColor(15);
gr2->Draw("ZP SAME"); 

signalFcn->Draw("same");

TLegend* legend = new TLegend(0.15,0.6,0.4,0.8);
legend->AddEntry(gr1,"OS_CFSFweighted_1.4%","lp");
legend->AddEntry(gr2,"SS","lp");
legend->AddEntry(signalFcn,"SS_signalFit","l");
legend->Draw();


c2->cd(2);

gPad->SetPad(0,0,1,0.35);
gPad->SetTopMargin(0.05);
gPad->SetBottomMargin(0.15);

// Just ratio plot

TGraphErrors* gr3 = new TGraphErrors(x_3.size(),&x_3[0],&y_3[0],&ex_3[0],&ey_3[0]);
gr3->SetMarkerStyle(20);
gr3->SetMarkerColor(kBlue-4);
gr3->SetMarkerSize(0.8);
gr3->SetTitle("");
gr3->Draw("ZAP");
gr3->GetXaxis()->SetLabelSize(0.06);
gr3->GetXaxis()->SetTitle("#scale[2.2]{m(ee) (GeV)}");
gr3->GetXaxis()->SetTitleOffset(1.6);
gr3->GetXaxis()->SetTickLength(0.05);
gr3->GetYaxis()->SetLabelSize(0.05);
gr3->GetYaxis()->SetTitle("#scale[2.2]{SS(observed) / OS}"); // TODO SS(signal) / OS would be more informative
gr3->GetYaxis()->SetTitleOffset(0.8);
gr3->GetYaxis()->SetRangeUser(0,2);
gPad->SetGridx();
gPad->SetGridy();

TLine* LineAtOne = new TLine(gr3->GetXaxis()->GetXmin(),1,gr3->GetXaxis()->GetXmax(),1);
LineAtOne->SetLineStyle(kDashed);
LineAtOne->SetLineWidth(2);
LineAtOne->SetLineColor(2);
LineAtOne->Draw();



//TCanvas* c3 = new TCanvas("c3","ZMass : OS_CFSFweighted vs SS ("+EtaRegion+")",1000,100,900,800);
//
//TGraph* gr4 = new TGraph(40);
//TGraphSmooth* gs1 = new TGraphSmooth();
//gr4 = gs1->Approx(gr1);
//gr4->Draw("ALP");
//
//cout << gr4->Integral() << endl;

double SS2l, OS2l;
SS2l = signalFcn->Integral(70,110);
OS2l = h1->Integral();


//cout << "SS2l: " << gr2->Integral() << endl;
//cout << "OS2l_CF_shifted_1.4%: " << gr1->Integral() << endl;
//cout << "SF: " << gr2->Integral()/gr1->Integral() << endl;
cout << "SS2l_signal: " << SS2l << endl;
cout << "OS2l_CF_shifted_1.4%: " << OS2l << endl;
cout << "SF: " << SS2l/OS2l << endl;
cout << "SS2l(hist) - SS2l(fit) = " << h0->Integral()-signalFcn->Integral(70,110)-backFcn->Integral(70,110) << endl;
//cout << "SS2l(hist) - SS2l(fit) = " << h0->Integral()-signalFcn->Integral(70,110)-backFcn_tmp->Integral(70,110) << endl; // tmp fitting

}

