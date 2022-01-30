void checkEntry(){
  string fileline;
  ifstream in("fileList_checkEntry.txt");

  // Line loop
  while(getline(in, fileline)){
    std::istringstream is(fileline);
    TString this_line = fileline;
    if(this_line==""){
      cout << endl;
      continue;
    }
    if(this_line.Contains("#")) continue;
    TString process, region, hist, bin, skim;
    is >> process;
    is >> region;
    is >> hist;
    is >> bin;
    int bin_int = bin.Atoi();
    is >> skim;

    TFile *f_MC;
    TH1D *h_MC;

    if(skim.Sizeof() == 1) f_MC = new TFile("SSWW_"+process+".root");
    else f_MC = new TFile("SSWW_SkimTree_"+skim+"_"+process+".root");

    h_MC = (TH1D*)f_MC->Get(region+"/"+hist);
    double Nevent;
    if(h_MC) Nevent = h_MC->GetBinContent(bin_int);
    else Nevent = 0.;
    
    cout << "===============================================" << endl;
    cout << "process : " << process << endl;
    //cout << "skim : " << skim << endl;
    cout << "region : " << region << endl;
    cout << "Nevent in " << bin << "th bin : " << Nevent << endl;
  }

}


void checkEntry(TString region){

  cout << "===============================================" << endl;
  cout << "<region : " << region << ">" << endl << endl;
  string fileline;
  ifstream in("fileList_checkEntry2.txt");
  map<TString, int> map_bin;
  map_bin["SR/M1500_1"]    = 17;
  map_bin["SR_inv"]        = 16;
  map_bin["btag"]          = 14;
  map_bin["WZ"]            = 17;
  map_bin["WZb"]           = 17;
  map_bin["highSR1"]       = 13;
  map_bin["highSR1/M1500"] = 14;
  map_bin["highSR2"]       = 11;
  map_bin["highSR2/M1500"] = 12;

  // Line loop
  while(getline(in, fileline)){
    std::istringstream is(fileline);
    TString this_line = fileline;
    if(this_line==""){
      cout << endl;
      continue;
    }
    if(this_line.Contains("#")) continue;
    TString process;
    is >> process;

    TFile *f_MC;
    TH1D *h_MC;
    f_MC = new TFile("SSWW_SkimTree_HNMultiLep_"+process+".root");
    h_MC = (TH1D*)f_MC->Get(region+"/Number_Events_HN");
    double Nevent;
    if(h_MC) Nevent = h_MC->GetBinContent(map_bin[region]);
    else Nevent = 0.;
    
    cout << process << " : " << Nevent << endl;
  }
  cout << "===============================================" << endl;

}
