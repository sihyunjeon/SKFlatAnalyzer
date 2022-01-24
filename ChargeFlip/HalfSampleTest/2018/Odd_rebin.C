void Odd_rebin(TString binSetting){

TString filename = "/data6/Users/jihkim/SKFlatOutput/Run2Legacy_v4/ChargeFlip/2018/HalfSampleTest__/ChargeFlip_All.root";
TFile* f1 = new TFile(filename);

TString samplename = filename(filename.Last('/')+12,filename.Length());
samplename.ReplaceAll(".root","");

gSystem->Exec("mkdir -p "+samplename);

TString User_ID = "HNTightV1";

TH1D* h0 = (TH1D*)f1->Get(User_ID+"/HalfSampleTest/Odd/MET_Denom");
TH1D* h1 = (TH1D*)f1->Get(User_ID+"/HalfSampleTest/Odd/MET_weight"); //predicted
TH1D* h2 = (TH1D*)f1->Get(User_ID+"/HalfSampleTest/Odd/MET_Num"); //measured

int rebin_1 = 20;
double syst = 0.04;

h0->Rebin(rebin_1);
h1->Rebin(rebin_1);
h2->Rebin(rebin_1);

vector<double> x_1, ex_1, x_2, ex_2, x_3, ex_3;
for (int i=0; i<100/rebin_1; i++) {
  x_1.push_back((2*i+1)*(rebin_1/2)); ex_1.push_back(rebin_1/2); 
  x_2.push_back((2*i+1)*(rebin_1/2)); ex_2.push_back(rebin_1/2); 
  x_3.push_back((2*i+1)*(rebin_1/2)); ex_3.push_back(rebin_1/2); 
}
vector<double> y_1, ey_1, y_2, ey_2, y_3, y_3_show, ey_3, ey_3_stat, ey_3_stat_show, ey_3_syst, ey_3_tot, ey_3_tot_show;
for (int i=0; i<100/rebin_1; i++) {
  y_1.push_back(h1->GetBinContent(i+1)/h0->GetBinContent(i+1));
  ey_1.push_back(y_1[i]*(sqrt(pow(h1->GetBinError(i+1)/h1->GetBinContent(i+1),2)+pow(h0->GetBinError(i+1)/h0->GetBinContent(i+1),2))));
  y_2.push_back(h2->GetBinContent(i+1)/h0->GetBinContent(i+1));
  ey_2.push_back(y_2[i]*(sqrt(pow(h2->GetBinError(i+1)/h2->GetBinContent(i+1),2)+pow(h0->GetBinError(i+1)/h0->GetBinContent(i+1),2))));
  y_3.push_back(y_2[i]/y_1[i]);
  ey_3.push_back(y_3[i]*(sqrt(pow(ey_2[i]/y_2[i],2)+pow(ey_1[i]/y_1[i],2))));

  //showing the ratio
  y_3_show.push_back(1.);
  ey_3_stat.push_back(h1->GetBinError(i+1));
  ey_3_syst.push_back(syst*h1->GetBinContent(i+1));
  ey_3_tot.push_back( sqrt(ey_3_stat[i]*ey_3_stat[i] + ey_3_syst[i]*ey_3_syst[i]) );
  ey_3_stat_show.push_back(ey_3_stat[i]/h1->GetBinContent(i+1));
  ey_3_tot_show.push_back(ey_3_tot[i]/h1->GetBinContent(i+1));
}

// Draw the plots //

TCanvas* c1 = new TCanvas("c1","HalfSampleTest : MET ("+User_ID+")",100,100,900,800);
c1->Divide(1,2);

c1->cd(1);

gPad->SetPad(0,0.35,1,1);
gPad->SetTopMargin(0.08);
gPad->SetBottomMargin(0.02);

TGraphErrors* gr1 = new TGraphErrors(x_1.size(),&x_1[0],&y_1[0],&ex_1[0],&ey_1[0]);
gr1->SetMarkerStyle(20);
//gr1->SetMarkerSize(0.8);
//gr1->SetMarkerColor(kMagenta+2);
gr1->SetLineColor(15);
//gr1->SetTitle("HalfSampleTest : MET ("+User_ID+")");
gr1->SetTitle("HalfSampleTest : MET");
//gr1->SetMinimum(0.);
gr1->Draw("ZAP"); // Z : do not draw small horizontal/vertical lines the end of the error bars
gr1->GetXaxis()->SetTickLength(0.025);
gr1->GetXaxis()->SetLabelSize(0);
gr1->GetXaxis()->SetRangeUser(0,100);
gr1->GetYaxis()->SetLabelSize(0.025);
gr1->GetYaxis()->SetRangeUser(0.,0.001);

TGraphErrors* gr2 = new TGraphErrors(x_2.size(),&x_2[0],&y_2[0],&ex_2[0],&ey_2[0]);
gr2->SetMarkerStyle(20);
gr2->SetMarkerColor(kMagenta+2);
gr2->SetLineColor(15);
gr2->Draw("ZP SAME"); 

TLegend* legend = new TLegend(0.75,0.78,0.9,0.92);
legend->AddEntry(gr1,"Predicted","lp");
legend->AddEntry(gr2,"Measured","lp");
legend->Draw();


c1->cd(2);

gPad->SetPad(0,0,1,0.35);
gPad->SetTopMargin(0.05);
gPad->SetBottomMargin(0.15);

// display errors

TGraphErrors* gr3_tot_show = new TGraphErrors(x_3.size(),&x_3[0],&y_3_show[0],&ex_3[0],&ey_3_tot_show[0]);
gr3_tot_show->SetTitle("");
gr3_tot_show->SetFillColor(7);
gr3_tot_show->Draw("A2");
gr3_tot_show->GetXaxis()->SetLabelSize(0.06);
gr3_tot_show->GetXaxis()->SetTitle("#scale[2.2]{E_{T}^{miss} (GeV)}");
gr3_tot_show->GetXaxis()->SetTitleOffset(1.6);
gr3_tot_show->GetXaxis()->SetTickLength(0.05);
gr3_tot_show->GetXaxis()->SetRangeUser(0,100);
gr3_tot_show->GetYaxis()->SetLabelSize(0.05);
gr3_tot_show->GetYaxis()->SetTitle("#scale[1.5]{#frac{Measured}{Predicted}}");
gr3_tot_show->GetYaxis()->SetTitleOffset(0.8);
gr3_tot_show->GetYaxis()->SetRangeUser(0.8,1.2);
gPad->SetGridx();
gPad->SetGridy();

TGraphErrors* gr3_stat_show = new TGraphErrors(x_3.size(),&x_3[0],&y_3_show[0],&ex_3[0],&ey_3_stat_show[0]);
gr3_stat_show->SetFillColor(5);
gr3_stat_show->Draw("2");

TGraphErrors* gr3 = new TGraphErrors(x_3.size(),&x_3[0],&y_3[0],&ex_3[0],&ey_3[0]);
gr3->SetMarkerStyle(20);
gr3->SetMarkerColor(kBlue-4);
gr3->SetMarkerSize(0.8);
gr3->Draw("ZP");

TLine* LineAtOne = new TLine(gr3->GetXaxis()->GetXmin(),1,100,1);
LineAtOne->SetLineStyle(kDashed);
LineAtOne->SetLineWidth(2);
LineAtOne->SetLineColor(2);
LineAtOne->Draw();

TLegend* legend_ratio = new TLegend(0.55,0.85,0.9,0.95);
legend_ratio->SetNColumns(2);
legend_ratio->AddEntry(gr3_stat_show,"Stat.","f");
legend_ratio->AddEntry(gr3_tot_show,"Stat.+Syst.","f");
legend_ratio->Draw();



//////////////////////////////////////////////////////////////////////////////////////////////////////

TH1D* H0 = (TH1D*)f1->Get(User_ID+"/HalfSampleTest/Odd/METsquaredOverST_Denom");
TH1D* H1 = (TH1D*)f1->Get(User_ID+"/HalfSampleTest/Odd/METsquaredOverST_weight");
TH1D* H2 = (TH1D*)f1->Get(User_ID+"/HalfSampleTest/Odd/METsquaredOverST_Num");
TH1D* H0_varBin;
TH1D* H1_varBin;
TH1D* H2_varBin;

int rebin_2 = 10;
int Nbin = 3;
double xbins[4] = {0., 10., 20., 50.};
if (binSetting == "even"){
  H0->Rebin(rebin_2);
  H1->Rebin(rebin_2);
  H2->Rebin(rebin_2);
}
else if (binSetting == "var"){
  H0_varBin = (TH1D*)H0->Rebin(Nbin,"",xbins);
  H1_varBin = (TH1D*)H1->Rebin(Nbin,"",xbins);
  H2_varBin = (TH1D*)H2->Rebin(Nbin,"",xbins);
}

vector<double> X_1, EX_1, X_2, EX_2, X_3, EX_3;
vector<double> Y_1, EY_1, Y_2, EY_2, Y_3, Y_3_show, EY_3, EY_3_stat, EY_3_stat_show, EY_3_syst, EY_3_tot, EY_3_tot_show;
if (binSetting == "even"){
  for (int i=0; i<50/rebin_2; i++) {
    X_1.push_back((2*i+1)*(rebin_2/2)); EX_1.push_back(rebin_2/2); 
    X_2.push_back((2*i+1)*(rebin_2/2)); EX_2.push_back(rebin_2/2); 
    X_3.push_back((2*i+1)*(rebin_2/2)); EX_3.push_back(rebin_2/2); 
  }
  for (int i=0; i<50/rebin_2; i++) {
    Y_1.push_back(H1->GetBinContent(i+1)/H0->GetBinContent(i+1));
    EY_1.push_back(Y_1[i]*(sqrt(pow(H1->GetBinError(i+1)/H1->GetBinContent(i+1),2)+pow(H0->GetBinError(i+1)/H0->GetBinContent(i+1),2))));
    Y_2.push_back(H2->GetBinContent(i+1)/H0->GetBinContent(i+1));
    EY_2.push_back(Y_2[i]*(sqrt(pow(H2->GetBinError(i+1)/H2->GetBinContent(i+1),2)+pow(H0->GetBinError(i+1)/H0->GetBinContent(i+1),2))));
    Y_3.push_back(Y_2[i]/Y_1[i]);
    EY_3.push_back(Y_3[i]*(sqrt(pow(EY_2[i]/Y_2[i],2)+pow(EY_1[i]/Y_1[i],2))));
  
    //showing the ratio
    Y_3_show.push_back(1.);
    EY_3_stat.push_back(H1->GetBinError(i+1));
    EY_3_syst.push_back(syst*H1->GetBinContent(i+1));
    EY_3_tot.push_back( sqrt(EY_3_stat[i]*EY_3_stat[i] + EY_3_syst[i]*EY_3_syst[i]) );
    EY_3_stat_show.push_back(EY_3_stat[i]/H1->GetBinContent(i+1));
    EY_3_tot_show.push_back(EY_3_tot[i]/H1->GetBinContent(i+1));
  }
}
else if (binSetting == "var"){
  for (int i=0; i<Nbin; i++) {
    X_1.push_back(xbins[i]+(xbins[i+1]-xbins[i])/2.); EX_1.push_back((xbins[i+1]-xbins[i])/2.); 
    X_2.push_back(xbins[i]+(xbins[i+1]-xbins[i])/2.); EX_2.push_back((xbins[i+1]-xbins[i])/2.); 
    X_3.push_back(xbins[i]+(xbins[i+1]-xbins[i])/2.); EX_3.push_back((xbins[i+1]-xbins[i])/2.); 
  }
  for (int i=0; i<Nbin; i++) {
    Y_1.push_back(H1_varBin->GetBinContent(i+1)/H0_varBin->GetBinContent(i+1));
    EY_1.push_back(Y_1[i]*(sqrt(pow(H1_varBin->GetBinError(i+1)/H1_varBin->GetBinContent(i+1),2)+pow(H0_varBin->GetBinError(i+1)/H0_varBin->GetBinContent(i+1),2))));
    Y_2.push_back(H2_varBin->GetBinContent(i+1)/H0_varBin->GetBinContent(i+1));
    EY_2.push_back(Y_2[i]*(sqrt(pow(H2_varBin->GetBinError(i+1)/H2_varBin->GetBinContent(i+1),2)+pow(H0_varBin->GetBinError(i+1)/H0_varBin->GetBinContent(i+1),2))));
    Y_3.push_back(Y_2[i]/Y_1[i]);
    EY_3.push_back(Y_3[i]*(sqrt(pow(EY_2[i]/Y_2[i],2)+pow(EY_1[i]/Y_1[i],2))));
  
    //showing the ratio
    Y_3_show.push_back(1.);
    EY_3_stat.push_back(H1_varBin->GetBinError(i+1));
    EY_3_syst.push_back(syst*H1_varBin->GetBinContent(i+1));
    EY_3_tot.push_back( sqrt(EY_3_stat[i]*EY_3_stat[i] + EY_3_syst[i]*EY_3_syst[i]) );
    EY_3_stat_show.push_back(EY_3_stat[i]/H1_varBin->GetBinContent(i+1));
    EY_3_tot_show.push_back(EY_3_tot[i]/H1_varBin->GetBinContent(i+1));
  }
}

// Draw the plots //

TCanvas* c2 = new TCanvas("c2","HalfSampleTest : MET^{2}/ST ("+User_ID+")",1000,100,900,800);
c2->Divide(1,2);

c2->cd(1);

gPad->SetPad(0,0.35,1,1);
gPad->SetTopMargin(0.08);
gPad->SetBottomMargin(0.02);

TGraphErrors* GR1 = new TGraphErrors(X_1.size(),&X_1[0],&Y_1[0],&EX_1[0],&EY_1[0]);
GR1->SetMarkerStyle(20);
//GR1->SetMarkerSize(0.8);
//GR1->SetMarkerColor(kMagenta+2);
GR1->SetLineColor(15);
//GR1->SetTitle("HalfSampleTest : MET^{2}/S_{T} ("+User_ID+")");
GR1->SetTitle("HalfSampleTest : MET^{2}/S_{T}");
//GR1->SetMinimum(0.);
GR1->Draw("ZAP"); // Z : do not draw small horizontal/vertical lines the end of the error bars
GR1->GetXaxis()->SetTickLength(0.025);
GR1->GetXaxis()->SetLabelSize(0);
GR1->GetXaxis()->SetRangeUser(0,50);
GR1->GetYaxis()->SetLabelSize(0.025);
GR1->GetYaxis()->SetRangeUser(0.,0.001);

TGraphErrors* GR2 = new TGraphErrors(X_2.size(),&X_2[0],&Y_2[0],&EX_2[0],&EY_2[0]);
GR2->SetMarkerStyle(20);
GR2->SetMarkerColor(kMagenta+2);
GR2->SetLineColor(15);
GR2->Draw("ZP SAME"); 

TLegend* legend_2 = new TLegend(0.75,0.78,0.9,0.92);
legend_2->AddEntry(GR1,"Predicted","lp");
legend_2->AddEntry(GR2,"Measured","lp");
legend_2->Draw();


c2->cd(2);

gPad->SetPad(0,0,1,0.35);
gPad->SetTopMargin(0.05);
gPad->SetBottomMargin(0.15);

// display errors

TGraphErrors* GR3_tot_show = new TGraphErrors(X_3.size(),&X_3[0],&Y_3_show[0],&EX_3[0],&EY_3_tot_show[0]);
GR3_tot_show->SetTitle("");
GR3_tot_show->SetFillColor(7);
GR3_tot_show->Draw("A2");
GR3_tot_show->GetXaxis()->SetLabelSize(0.06);
GR3_tot_show->GetXaxis()->SetTitle("#scale[2.2]{MET^{2}/S_{T} (GeV)}");
GR3_tot_show->GetXaxis()->SetTitleOffset(1.6);
GR3_tot_show->GetXaxis()->SetTickLength(0.05);
GR3_tot_show->GetXaxis()->SetRangeUser(0,50);
GR3_tot_show->GetYaxis()->SetLabelSize(0.05);
GR3_tot_show->GetYaxis()->SetTitle("#scale[1.5]{#frac{Measured}{Predicted}}");
GR3_tot_show->GetYaxis()->SetTitleOffset(0.8);
GR3_tot_show->GetYaxis()->SetRangeUser(0.8,1.2);
gPad->SetGridx();
gPad->SetGridy();

TGraphErrors* GR3_stat_show = new TGraphErrors(X_3.size(),&X_3[0],&Y_3_show[0],&EX_3[0],&EY_3_stat_show[0]);
GR3_stat_show->SetFillColor(5);
GR3_stat_show->Draw("2");

TGraphErrors* GR3 = new TGraphErrors(X_3.size(),&X_3[0],&Y_3[0],&EX_3[0],&EY_3[0]);
GR3->SetMarkerStyle(20);
GR3->SetMarkerColor(kBlue-4);
GR3->SetMarkerSize(0.8);
GR3->Draw("ZP");

TLine* LineAtOne_2 = new TLine(GR3->GetXaxis()->GetXmin(),1,50,1);
LineAtOne_2->SetLineStyle(kDashed);
LineAtOne_2->SetLineWidth(2);
LineAtOne_2->SetLineColor(2);
LineAtOne_2->Draw();

TLegend* legend_ratio_2 = new TLegend(0.55,0.85,0.9,0.95);
legend_ratio_2->SetNColumns(2);
legend_ratio_2->AddEntry(GR3_stat_show,"Stat.","f");
legend_ratio_2->AddEntry(GR3_tot_show,"Stat.+Syst.","f");
legend_ratio_2->Draw();



c1->SaveAs(samplename+"/"+User_ID+"_MET_rebin.pdf");
c1->SaveAs(samplename+"/"+User_ID+"_MET_rebin.png");

if(binSetting == "even"){
  c2->SaveAs(samplename+"/"+User_ID+"_METsquaredOverST_evenBin.pdf");
  c2->SaveAs(samplename+"/"+User_ID+"_METsquaredOverST_evenBin.png");
}
else if (binSetting == "var"){
  c2->SaveAs(samplename+"/"+User_ID+"_METsquaredOverST_varBin.pdf");
  c2->SaveAs(samplename+"/"+User_ID+"_METsquaredOverST_varBin.png");
}

}
