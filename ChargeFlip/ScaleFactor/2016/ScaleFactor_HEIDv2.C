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

void ScaleFactor(TString EtaRegion, TString id = "HEIDv2", int Syst = 0, TString SaveAs = "n"){ // BB, BE, EE

  TString X = ""; //energy shift
  if(id=="HEIDv2") X = "1.0%";
  
  int MllLeft = 70; if(Syst==3) MllLeft = 75; else if(Syst==4) MllLeft = 65;
  int MllRight = 110; if(Syst==3) MllRight = 105; else if(Syst==4) MllRight = 115;
  int NBin = 40; if(Syst==5) NBin = 35; else if(Syst==6) NBin = 45;
  double err = 0.5; if(Syst==3||Syst==4||Syst==5||Syst==6) err = 1.*(MllRight-MllLeft)/NBin/2.; // if NBin is fixed at 40, then err changes in both Syst 3 and 4
  
  std::map<int, TString> RunSyst;
  RunSyst[0] = "";
  RunSyst[1] = "_Syst_MinPtDown";
  RunSyst[2] = "_Syst_MinPtUp";
  RunSyst[3] = "_Syst_MllRangeDown";
  RunSyst[4] = "_Syst_MllRangeUp";
  RunSyst[5] = "_Syst_NBinDown";
  RunSyst[6] = "_Syst_NBinUp";
  
  
  TString filename = "/data6/Users/jihkim/SKFlatOutput/Run2Legacy_v3/ChargeFlip_IDv2/2016/ScaleFactor__/DATA/ChargeFlip_IDv2_DoubleEG_total_DYTTLLCF.root";
  TFile* f1 = new TFile(filename);
  
  TString samplename = filename(filename.Last('_')+1,filename.Length());
  samplename.ReplaceAll(".root","");
  
  gSystem->Exec("mkdir "+samplename);
  
  TH1D* h0 = (TH1D*)f1->Get(id+RunSyst[Syst]+"/ScaleFactor/"+EtaRegion+"_ZMass_SS");
  TH1D* h1 = (TH1D*)f1->Get(id+RunSyst[Syst]+"/ScaleFactor/"+EtaRegion+"_ZMass_OS_CFweighted_shifted_"+X);
  
  vector<double> x_1, ex_1, x_2, ex_2, x_3, ex_3;
  for (int i=0; i<NBin; i++) {
    x_1.push_back(MllLeft+(2*i+1)*(err)); ex_1.push_back(err); 
    x_2.push_back(MllLeft+(2*i+1)*(err)); ex_2.push_back(err); 
    x_3.push_back(MllLeft+(2*i+1)*(err)); ex_3.push_back(err); 
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
  
  
  // create a TF1 with the range from MllLeft to MllRight and 7 parameters
  TF1 *fitFcn = new TF1("fitFcn",fitFunction,MllLeft,MllRight,7);
  fitFcn->SetNpx(500);
  //fitFcn->SetLineWidth(4);
  fitFcn->SetLineColor(kRed);
  
  fitFcn->SetParameters(0,0,0,0,50,90,1.); // Parameters to get SF for BB, EE
  gr->Fit("fitFcn","V+","ep");
  
  
  // improve the picture:
  TF1 *backFcn = new TF1("backFcn",background,MllLeft,MllRight,4);
  backFcn->SetLineColor(kBlue);
  backFcn->Draw("same");
  
  TF1 *signalFcn = new TF1("signalFcn",gaussianPeak,MllLeft,MllRight,3);
  signalFcn->SetLineColor(kMagenta-6);
  signalFcn->SetNpx(500);
  //signalFcn->Draw("same");
  
  // writes the fit results into the par array
  Double_t par[7];
  fitFcn->GetParameters(par);
  backFcn->SetParameters(par);
  signalFcn->SetParameters(&par[4]);
  
  
  /* get needed strings to put in the textbox */
  
  double Chisquare = fitFcn->GetChisquare();
  TString Chisquare_t = Form("%f",Chisquare);
  Chisquare_t = Chisquare_t(0,7);
  int ndf = fitFcn->GetNDF();
  TString ndf_t = Form("%d",ndf);
  int SS2l_obs = h0->Integral();
  TString SS2l_obs_t = Form("%d",SS2l_obs);
  double SS2l_bkg = backFcn->Integral(MllLeft,MllRight)/(2.*err);
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
  
  //legend_fit->AddEntry((TObject*)0,"Chisquare/ndf : "+Chisquare+"/"+ndf,"");
  //cout << "SS2l_signal: " << SS2l << endl;
  //cout << "OS2l_CF_shifted_"+X+": " << OS2l << endl;
  //cout << "SF: " << SS2l/OS2l << endl;
  //cout << "SS2l(hist) - SS2l(fit) = " << h0->Integral()-signalFcn->Integral(MllLeft,MllRight)-backFcn->Integral(MllLeft,MllRight) << endl;
  
  
  
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
  //gr1->GetXaxis()->SetRangeUser(MllLeft,MllRight);
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
    y_4.push_back(gaussianPeak(&x_4[i],&par[4])/h1->GetBinContent(i+1));
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
  gr3->GetYaxis()->SetLabelSize(0.05);
  gr3->GetYaxis()->SetTitle("#scale[2.2]{SS(signalFit) / OS}"); // SS(signal) / OS would be more informative than SS(observed)
  gr3->GetYaxis()->SetTitleOffset(0.8);
  gr3->GetYaxis()->SetRangeUser(0,1.3);
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

  map<int,TString> m;
  m[0] = "BB";
  m[1] = "EE";

  for (int i=0; i<2; i++){
    ScaleFactor("HEIDv2",m[i],0,"y");
  }

}
