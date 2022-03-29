void calcSig(TString signal, TString mass){ //calcSig("SSWWTypeI_NLO_SF_M1500","M1500")
  /////////////////////////////////////MC////////////////////////////////////////////
  string fileline;
  ifstream in("fileList_calcSig.txt");
  double MC_SR = 0., MC_SR_inv = 0., MC_highSR1 = 0., MC_highSR1_opt = 0., MC_highSR1_1jet = 0., MC_highSR1_1jet_opt = 0., MC_highSR2 = 0., MC_highSR2_opt = 0., MC_SR_opt = 0.;
  double signal_SR = 0., signal_SR_inv = 0., signal_highSR1 = 0., signal_highSR1_opt = 0., signal_highSR1_1jet = 0., signal_highSR1_1jet_opt = 0., signal_highSR2 = 0., signal_highSR2_opt = 0., signal_SR_opt = 0.;
  double fake_SR = 0., fake_SR_inv = 0., fake_highSR1 = 0., fake_highSR1_opt = 0., fake_highSR1_1jet = 0., fake_highSR1_1jet_opt = 0., fake_highSR2 = 0., fake_highSR2_opt = 0., fake_SR_opt = 0.;
  // Line loop
  while(getline(in, fileline)){
    std::istringstream is(fileline);
    TString this_line = fileline;
    if(this_line.Contains("#")||this_line=="") continue;
    TString category, process, isSkim;
    is >> category;
    is >> process;
    is >> isSkim;
    //cout << "process : " << process << endl;
    //cout << "isSkim : " << isSkim << endl;

    if(category=="signal"){
      if(process!=signal) continue;
    }

    TFile *f_MC;
    TH1D *h_MC_SR, *h_MC_SR_opt, *h_MC_SR_inv, *h_MC_highSR1, *h_MC_highSR1_opt, *h_MC_highSR1_1jet, *h_MC_highSR1_1jet_opt, *h_MC_highSR2, *h_MC_highSR2_opt;
    if(isSkim=="skimmed") f_MC = new TFile("SSWW_SkimTree_HNMultiLep_"+process+".root");
    else f_MC = new TFile("SSWW_"+process+".root");
    //cout << "f_MC : " << f_MC << endl;
    h_MC_SR = (TH1D*)f_MC->Get("SR/HToverPt1_HN");
    h_MC_SR_opt = (TH1D*)f_MC->Get("SR/M1500_1/HToverPt1_HN"); //JH : FIXME M1500_1 --> opt
    h_MC_SR_inv = (TH1D*)f_MC->Get("SR_inv/HToverPt1_HN");
    h_MC_highSR1 = (TH1D*)f_MC->Get("highSR1/HToverPt1_HN");
    h_MC_highSR1_opt = (TH1D*)f_MC->Get("highSR1/"+mass+"/HToverPt1_HN");
    h_MC_highSR1_1jet = (TH1D*)f_MC->Get("highSR1_1jet/HToverPt1_HN");
    h_MC_highSR1_1jet_opt = (TH1D*)f_MC->Get("highSR1_1jet/"+mass+"/HToverPt1_HN");
    h_MC_highSR2 = (TH1D*)f_MC->Get("highSR2/HToverPt1_HN");
    h_MC_highSR2_opt = (TH1D*)f_MC->Get("highSR2/"+mass+"/HToverPt1_HN");
    int Nbin = 10; // Nbin of HToverPt1
    cout.flags(ios::left); // left align; see https://m.blog.naver.com/PostView.naver?isHttpsRedirect=true&blogId=tipsware&logNo=221115657586
    cout << "========================================================" << endl;
    cout << "!!process : " << process << "!!" << endl;
    if(h_MC_SR){
                                cout << "SR                                     : " << h_MC_SR->Integral(0,Nbin+1) << endl;
                                if(category=="MC")     MC_SR     += h_MC_SR->Integral(0,Nbin+1);
                                if(category=="signal") signal_SR += h_MC_SR->Integral(0,Nbin+1);
    }
    else                        cout << "SR                                     : NULL;" << endl;
    if(h_MC_SR_opt){
                                cout << "SR, with optimization                  : " << h_MC_SR_opt->Integral(0,Nbin+1) << endl;
                                if(category=="MC")         MC_SR_opt += h_MC_SR_opt->Integral(0,Nbin+1);
                                if(category=="signal") signal_SR_opt += h_MC_SR_opt->Integral(0,Nbin+1);
    }
    else                        {cout << "SR, with optimization                  : NULL;" << endl;}
    if(h_MC_SR_inv){
                                cout << "SR_inv                                 : " << h_MC_SR_inv->Integral(0,Nbin+1) << endl;
                                if(category=="MC")         MC_SR_inv += h_MC_SR_inv->Integral(0,Nbin+1);
                                if(category=="signal") signal_SR_inv += h_MC_SR_inv->Integral(0,Nbin+1);
    }
    else                        cout << "SR_inv                                 : NULL;" << endl;
    if(h_MC_highSR1){
                                cout << "highSR1                                : " << h_MC_highSR1->Integral(0,Nbin+1) << endl;
                                if(category=="MC")         MC_highSR1 += h_MC_highSR1->Integral(0,Nbin+1);
                                if(category=="signal") signal_highSR1 += h_MC_highSR1->Integral(0,Nbin+1);
    }
    else                        cout << "highSR1                                : NULL;" << endl;
    if(h_MC_highSR1_opt){
                                cout << "highSR1, with "; cout.width(6); cout << mass; cout << " optimization      : " << h_MC_highSR1_opt->Integral(0,Nbin+1) << endl;
                                if(category=="MC")         MC_highSR1_opt += h_MC_highSR1_opt->Integral(0,Nbin+1);
                                if(category=="signal") signal_highSR1_opt += h_MC_highSR1_opt->Integral(0,Nbin+1);
    }
    else                        {cout << "highSR1, with "; cout.width(6); cout << mass; cout << " optimization      : NULL;" << endl;}
    if(h_MC_highSR1_1jet){
                                cout << "highSR1_1jet                           : " << h_MC_highSR1_1jet->Integral(0,Nbin+1) << endl;
                                if(category=="MC")         MC_highSR1_1jet += h_MC_highSR1_1jet->Integral(0,Nbin+1);
                                if(category=="signal") signal_highSR1_1jet += h_MC_highSR1_1jet->Integral(0,Nbin+1);
    }
    else                        cout << "highSR1_1jet                           : NULL;" << endl;
    if(h_MC_highSR1_1jet_opt){
                                cout << "highSR1_1jet, with "; cout.width(6); cout << mass; cout << " optimization : " << h_MC_highSR1_1jet_opt->Integral(0,Nbin+1) << endl;
                                if(category=="MC")         MC_highSR1_1jet_opt += h_MC_highSR1_1jet_opt->Integral(0,Nbin+1);
                                if(category=="signal") signal_highSR1_1jet_opt += h_MC_highSR1_1jet_opt->Integral(0,Nbin+1);
    }
    else                        {cout << "highSR1_1jet, with "; cout.width(6); cout << mass; cout << " optimization : NULL;" << endl;}
    if(h_MC_highSR2){
                                cout << "highSR2                                : " << h_MC_highSR2->Integral(0,Nbin+1) << endl;
                                if(category=="MC")         MC_highSR2 += h_MC_highSR2->Integral(0,Nbin+1);
                                if(category=="signal") signal_highSR2 += h_MC_highSR2->Integral(0,Nbin+1);
    }
    else                        cout << "highSR2                                : NULL;" << endl;
    if(h_MC_highSR2_opt){
                                cout << "highSR2, with "; cout.width(6); cout << mass; cout << " optimization      : " << h_MC_highSR2_opt->Integral(0,Nbin+1) << endl;
                                if(category=="MC")         MC_highSR2_opt += h_MC_highSR2_opt->Integral(0,Nbin+1);
                                if(category=="signal") signal_highSR2_opt += h_MC_highSR2_opt->Integral(0,Nbin+1);
    }
    else                        {cout << "highSR2, with "; cout.width(6); cout << mass; cout << " optmization       : NULL;" << endl;}
  }
  cout << "===================================================================================================" << endl;
  cout << "total MC in SR                                    : " << MC_SR << endl;
  cout << "total MC in SR, with optimization                 : " << MC_SR_opt << endl;
  cout << "total MC in SR_inv                                : " << MC_SR_inv << endl;
  cout << "total MC in highSR1                               : " << MC_highSR1 << endl;
  cout << "total MC in highSR1, with "; cout.width(6); cout << mass; cout << " optimization     : " << MC_highSR1_opt << endl;
  cout << "total MC in highSR1_1jet                          : " << MC_highSR1_1jet << endl;
  cout << "total MC in highSR1_1jet, with "; cout.width(6); cout << mass; cout << "optimization : " << MC_highSR1_1jet_opt << endl;
  cout << "total MC in highSR2                               : " << MC_highSR2 << endl;
  cout << "total MC in highSR2, with "; cout.width(6); cout << mass; cout << "optimization      : " << MC_highSR2_opt << endl;

  /////////////////////////////////////Fake////////////////////////////////////////////
  TFile *f_Fake = new TFile("/data6/Users/jihkim/SKFlatOutput/Run2UltraLegacy_v2/SSWW/2016/jcln_inv__fatjet_veto__RunFake__/DATA/SSWW_SkimTree_Dilepton_DoubleMuon.root");
  TH1D *h_Fake_SR, *h_Fake_SR_opt, *h_Fake_SR_inv, *h_Fake_highSR1, *h_Fake_highSR1_opt, *h_Fake_highSR1_1jet, *h_Fake_highSR1_1jet_opt, *h_Fake_highSR2, *h_Fake_highSR2_opt;
  h_Fake_SR = (TH1D*)f_Fake->Get("SR/HToverPt1_HN");
  h_Fake_SR_opt = (TH1D*)f_Fake->Get("SR/M1500_1/HToverPt1_HN"); //JH : FIXME M1500 --> opt
  h_Fake_SR_inv = (TH1D*)f_Fake->Get("SR_inv/HToverPt1_HN");
  h_Fake_highSR1 = (TH1D*)f_Fake->Get("highSR1/HToverPt1_HN");
  h_Fake_highSR1_opt = (TH1D*)f_Fake->Get("highSR1/"+mass+"/HToverPt1_HN");
  h_Fake_highSR1_1jet = (TH1D*)f_Fake->Get("highSR1_1jet/HToverPt1_HN");
  h_Fake_highSR1_1jet_opt = (TH1D*)f_Fake->Get("highSR1_1jet/"+mass+"/HToverPt1_HN");
  h_Fake_highSR2 = (TH1D*)f_Fake->Get("highSR2/HToverPt1_HN");
  h_Fake_highSR2_opt = (TH1D*)f_Fake->Get("highSR2/"+mass+"/HToverPt1_HN");
  int Nbin = 10; // Nbin of HToverPt1
  cout << "===================================================================================================" << endl;
  if(h_Fake_SR){
                              cout << "fake in SR                                        : " << h_Fake_SR->Integral(0,Nbin+1) << endl;
                              fake_SR += h_Fake_SR->Integral(0,Nbin+1);
  }
  else                        cout << "fake in SR                                        : NULL;" << endl;
  if(h_Fake_SR_opt){
                              cout << "fake in SR, with optimization                     : " << h_Fake_SR_opt->Integral(0,Nbin+1) << endl;
                              fake_SR_opt += h_Fake_SR_opt->Integral(0,Nbin+1);
  }
  else                        {cout << "fake in SR, with optimization                     : NULL;" << endl;}
  if(h_Fake_SR_inv){
                              cout << "fake in SR_inv                                    : " << h_Fake_SR_inv->Integral(0,Nbin+1) << endl;
                              fake_SR_inv += h_Fake_SR_inv->Integral(0,Nbin+1);
  }
  else                        cout << "fake in SR_inv                                    : NULL;" << endl;
  if(h_Fake_highSR1){
                              cout << "fake in highSR1                                   : " << h_Fake_highSR1->Integral(0,Nbin+1) << endl;
                              fake_highSR1 += h_Fake_highSR1->Integral(0,Nbin+1);
  }
  else                        cout << "fake in highSR1                                   : NULL;" << endl;
  if(h_Fake_highSR1_opt){
                              cout << "fake in highSR1, with "; cout.width(6); cout << mass; cout << " optimization         : " << h_Fake_highSR1_opt->Integral(0,Nbin+1) << endl;
                              fake_highSR1_opt += h_Fake_highSR1_opt->Integral(0,Nbin+1);
  }
  else                        {cout << "fake in highSR1, with "; cout.width(6); cout << mass; cout << " optimization         : NULL;" << endl;}
  if(h_Fake_highSR1_1jet){
                              cout << "fake in highSR1_1jet                              : " << h_Fake_highSR1_1jet->Integral(0,Nbin+1) << endl;
                              fake_highSR1_1jet += h_Fake_highSR1_1jet->Integral(0,Nbin+1);
  }
  else                        cout << "fake in highSR1_1jet                              : NULL;" << endl;
  if(h_Fake_highSR1_1jet_opt){
                              cout << "fake in highSR1_1jet, with "; cout.width(6); cout << mass; cout << " optimization    : " << h_Fake_highSR1_1jet_opt->Integral(0,Nbin+1) << endl;
                              fake_highSR1_1jet_opt += h_Fake_highSR1_1jet_opt->Integral(0,Nbin+1);
  }
  else                        {cout << "fake in highSR1_1jet, with "; cout.width(6); cout << mass; cout << " optimization    : NULL;" << endl;}
  if(h_Fake_highSR2){
                              cout << "fake in highSR2                                   : " << h_Fake_highSR2->Integral(0,Nbin+1) << endl;
                              fake_highSR2 += h_Fake_highSR2->Integral(0,Nbin+1);
  }
  else                        cout << "fake in highSR2                                   : NULL;" << endl;
  if(h_Fake_highSR2_opt){
                              cout << "fake in highSR2, with "; cout.width(6); cout << mass; cout << " optimization         : " << h_Fake_highSR2_opt->Integral(0,Nbin+1) << endl;
                              fake_highSR2_opt += h_Fake_highSR2_opt->Integral(0,Nbin+1);
  }
  else                        {cout << "fake in highSR2, with "; cout.width(6); cout << mass; cout << " optimization         : NULL;" << endl;}

  ///////////////////////////////////signal//////////////////////////////////////////
  //if(signal.Contains("DY")||signal.Contains("VBF")){
  //  signal_SR                   *= 10000.;
  //  signal_SR_opt               *= 10000.;
  //  signal_SR_inv               *= 10000.;
  //  signal_highSR1              *= 10000.;
  //  signal_highSR1_opt          *= 10000.;
  //  signal_highSR1_1jet         *= 10000.;
  //  signal_highSR1_1jet_opt     *= 10000.;
  //  signal_highSR2              *= 10000.;
  //  signal_highSR2_opt          *= 10000.;
  //} //JH : we don't need this for UL. because the xsec in sample info were already normalized to V==1.
  cout << "===================================================================================================" << endl;
  cout << "signal " << signal << " in SR                  : ";
  cout.width(12); cout << signal_SR << "--> S/sqrt(B) = ";
  cout.width(12); cout << signal_SR/sqrt(fake_SR+MC_SR);
  cout << ", full expansion = " << sqrt( 2.*((signal_SR+fake_SR+MC_SR)*log(1+(signal_SR/(fake_SR+MC_SR))) - signal_SR) ) << endl;
  cout << "signal " << signal << " in SR_opt              : ";
  cout.width(12); cout << signal_SR_opt << "--> S/sqrt(B) = ";
  cout.width(12); cout << signal_SR_opt/sqrt(fake_SR_opt+MC_SR_opt);
  cout << ", full expansion = " << sqrt( 2.*((signal_SR_opt+fake_SR_opt+MC_SR_opt)*log(1+(signal_SR_opt/(fake_SR_opt+MC_SR_opt))) - signal_SR_opt) ) << endl;
  cout << "signal " << signal << " in SR_inv              : ";
  cout.width(12); cout << signal_SR_inv << "--> S/sqrt(B) = ";
  cout.width(12); cout << signal_SR_inv/sqrt(fake_SR_inv+MC_SR_inv);
  cout << ", full expansion = " << sqrt( 2.*((signal_SR_inv+fake_SR_inv+MC_SR_inv)*log(1+(signal_SR_inv/(fake_SR_inv+MC_SR_inv))) - signal_SR_inv) ) << endl;
  cout << "signal " << signal << " in highSR1             : ";
  cout.width(12); cout << signal_highSR1 << "--> S/sqrt(B) = ";
  cout.width(12); cout << signal_highSR1/sqrt(fake_highSR1+MC_highSR1);
  cout << ", full expansion = " << sqrt( 2.*((signal_highSR1+fake_highSR1+MC_highSR1)*log(1+(signal_highSR1/(fake_highSR1+MC_highSR1))) - signal_highSR1) ) << endl;
  cout << "signal " << signal << " in highSR1_"; cout.width(6); cout << mass; cout << "      : ";
  cout.width(12); cout << signal_highSR1_opt << "--> S/sqrt(B) = ";
  cout.width(12); cout << signal_highSR1_opt/sqrt(fake_highSR1_opt+MC_highSR1_opt);
  cout << ", full expansion = " << sqrt( 2.*((signal_highSR1_opt+fake_highSR1_opt+MC_highSR1_opt)*log(1+(signal_highSR1_opt/(fake_highSR1_opt+MC_highSR1_opt))) - signal_highSR1_opt) ) << endl;
  cout << "signal " << signal << " in highSR1_1jet        : ";
  cout.width(12); cout << signal_highSR1_1jet << "--> S/sqrt(B) = ";
  cout.width(12); cout << signal_highSR1_1jet/sqrt(fake_highSR1_1jet+MC_highSR1_1jet);
  cout << ", full expansion = " << sqrt( 2.*((signal_highSR1_1jet+fake_highSR1_1jet+MC_highSR1_1jet)*log(1+(signal_highSR1_1jet/(fake_highSR1_1jet+MC_highSR1_1jet))) - signal_highSR1_1jet) ) << endl;
  cout << "signal " << signal << " in highSR1_1jet_"; cout.width(6); cout << mass; cout << " : ";
  cout.width(12); cout << signal_highSR1_1jet_opt << "--> S/sqrt(B) = ";
  cout.width(12); cout << signal_highSR1_1jet_opt/sqrt(fake_highSR1_1jet_opt+MC_highSR1_1jet_opt);
  cout << ", full expansion = " << sqrt( 2.*((signal_highSR1_1jet_opt+fake_highSR1_1jet_opt+MC_highSR1_1jet_opt)*log(1+(signal_highSR1_1jet_opt/(fake_highSR1_1jet_opt+MC_highSR1_1jet_opt))) - signal_highSR1_1jet_opt) ) << endl;
  cout << "signal " << signal << " in highSR2             : ";
  cout.width(12); cout << signal_highSR2 << "--> S/sqrt(B) = ";
  cout.width(12); cout << signal_highSR2/sqrt(fake_highSR2+MC_highSR2);
  cout << ", full expansion = " << sqrt( 2.*((signal_highSR2+fake_highSR2+MC_highSR2)*log(1+(signal_highSR2/(fake_highSR2+MC_highSR2))) - signal_highSR2) ) << endl;
  cout << "signal " << signal << " in highSR2_"; cout.width(6); cout << mass; cout << "      : ";
  cout.width(12); cout << signal_highSR2_opt << "--> S/sqrt(B) = ";
  cout.width(12); cout << signal_highSR2_opt/sqrt(fake_highSR2_opt+MC_highSR2_opt);
  cout << ", full expansion = " << sqrt( 2.*((signal_highSR2_opt+fake_highSR2_opt+MC_highSR2_opt)*log(1+(signal_highSR2_opt/(fake_highSR2_opt+MC_highSR2_opt))) - signal_highSR2_opt) ) << endl;
}
