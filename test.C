R__LOAD_LIBRARY(/cvmfs/cms.cern.ch/slc7_amd64_gcc900/external/lhapdf/6.2.3/lib/libLHAPDF.so)

void test(TString era, TString isdata, TString stream){ // test("2016preVFP","data","DM")

  //Fake m;
  //SSWW m;
  //Signal m;
  Control m;

  m.SetTreeName("recoTree/SKFlat");

  m.LogEvery = 1000;
  if(isdata == "data"){
    m.IsDATA = true;
    if(stream == "SM") m.DataStream = "SingleMuon";
    else if(stream == "DM") m.DataStream = "DoubleMuon";
    else if(era != "2018"){
      if(stream == "SE") m.DataStream = "SingleElectron";
      else if(stream == "DE") m.DataStream = "DoubleEG";
    }
    else if(stream == "SE"||stream == "DE") m.DataStream = "EGamma";
    else exit(EXIT_FAILURE);
  }
  else if(isdata == "mc") m.IsDATA = false;
  m.SetEra(era);
  m.Userflags = {
    //"FR", //Fake
    //"Norm", //Fake
    //"RunFake", //SSWW, Signal, Control
    //"FR_ex", //Signal, Control
    //"jcln_inv", //SSWW
    //"fatjet_veto", //SSWW
  };
  if(era=="2016preVFP" && isdata=="data" && stream=="DM"){
    m.AddFile("/gv0/DATA/SKFlat/Run2UltraLegacy_v2/2016preVFP/DATA_SkimTree_Dilepton/DoubleMuon/periodB_ver2/2021_09_02_200740/SKFlatNtuple_2016preVFP_DATA_15.root");
    m.AddFile("/gv0/DATA/SKFlat/Run2UltraLegacy_v2/2016preVFP/DATA_SkimTree_Dilepton/DoubleMuon/periodB_ver2/2021_09_02_200740/SKFlatNtuple_2016preVFP_DATA_16.root");
    m.AddFile("/gv0/DATA/SKFlat/Run2UltraLegacy_v2/2016preVFP/DATA_SkimTree_Dilepton/DoubleMuon/periodB_ver2/2021_09_02_200740/SKFlatNtuple_2016preVFP_DATA_17.root");
    m.AddFile("/gv0/DATA/SKFlat/Run2UltraLegacy_v2/2016preVFP/DATA_SkimTree_Dilepton/DoubleMuon/periodB_ver2/2021_09_02_200740/SKFlatNtuple_2016preVFP_DATA_18.root");
    m.AddFile("/gv0/DATA/SKFlat/Run2UltraLegacy_v2/2016preVFP/DATA_SkimTree_Dilepton/DoubleMuon/periodB_ver2/2021_09_02_200740/SKFlatNtuple_2016preVFP_DATA_19.root");
    m.AddFile("/gv0/DATA/SKFlat/Run2UltraLegacy_v2/2016preVFP/DATA_SkimTree_Dilepton/DoubleMuon/periodB_ver2/2021_09_02_200740/SKFlatNtuple_2016preVFP_DATA_20.root");
    m.AddFile("/gv0/DATA/SKFlat/Run2UltraLegacy_v2/2016preVFP/DATA_SkimTree_Dilepton/DoubleMuon/periodB_ver2/2021_09_02_200740/SKFlatNtuple_2016preVFP_DATA_21.root");
    m.AddFile("/gv0/DATA/SKFlat/Run2UltraLegacy_v2/2016preVFP/DATA_SkimTree_Dilepton/DoubleMuon/periodB_ver2/2021_09_02_200740/SKFlatNtuple_2016preVFP_DATA_22.root");
    m.AddFile("/gv0/DATA/SKFlat/Run2UltraLegacy_v2/2016preVFP/DATA_SkimTree_Dilepton/DoubleMuon/periodB_ver2/2021_09_02_200740/SKFlatNtuple_2016preVFP_DATA_23.root");
    m.AddFile("/gv0/DATA/SKFlat/Run2UltraLegacy_v2/2016preVFP/DATA_SkimTree_Dilepton/DoubleMuon/periodB_ver2/2021_09_02_200740/SKFlatNtuple_2016preVFP_DATA_24.root");
    m.AddFile("/gv0/DATA/SKFlat/Run2UltraLegacy_v2/2016preVFP/DATA_SkimTree_Dilepton/DoubleMuon/periodB_ver2/2021_09_02_200740/SKFlatNtuple_2016preVFP_DATA_25.root");
    m.AddFile("/gv0/DATA/SKFlat/Run2UltraLegacy_v2/2016preVFP/DATA_SkimTree_Dilepton/DoubleMuon/periodB_ver2/2021_09_02_200740/SKFlatNtuple_2016preVFP_DATA_26.root");
    m.AddFile("/gv0/DATA/SKFlat/Run2UltraLegacy_v2/2016preVFP/DATA_SkimTree_Dilepton/DoubleMuon/periodB_ver2/2021_09_02_200740/SKFlatNtuple_2016preVFP_DATA_27.root");
    m.AddFile("/gv0/DATA/SKFlat/Run2UltraLegacy_v2/2016preVFP/DATA_SkimTree_Dilepton/DoubleMuon/periodB_ver2/2021_09_02_200740/SKFlatNtuple_2016preVFP_DATA_28.root");
    m.AddFile("/gv0/DATA/SKFlat/Run2UltraLegacy_v2/2016preVFP/DATA_SkimTree_Dilepton/DoubleMuon/periodB_ver2/2021_09_02_200740/SKFlatNtuple_2016preVFP_DATA_29.root");
    m.AddFile("/gv0/DATA/SKFlat/Run2UltraLegacy_v2/2016preVFP/DATA_SkimTree_Dilepton/DoubleMuon/periodB_ver2/2021_09_02_200740/SKFlatNtuple_2016preVFP_DATA_30.root");
    m.AddFile("/gv0/DATA/SKFlat/Run2UltraLegacy_v2/2016preVFP/DATA_SkimTree_Dilepton/DoubleMuon/periodB_ver2/2021_09_02_200740/SKFlatNtuple_2016preVFP_DATA_31.root");
    m.AddFile("/gv0/DATA/SKFlat/Run2UltraLegacy_v2/2016preVFP/DATA_SkimTree_Dilepton/DoubleMuon/periodB_ver2/2021_09_02_200740/SKFlatNtuple_2016preVFP_DATA_32.root");
  }
  else if(era=="2016preVFP" && isdata=="mc" && stream=="DY"){
    m.AddFile("/gv0/DATA/SKFlat/Run2UltraLegacy_v2/2016preVFP/MC/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/210915_033646/0000/SKFlatNtuple_2016preVFP_MC_1.root");
    //m.AddFile("/gv0/DATA/SKFlat/Run2UltraLegacy_v2/2016preVFP/MC/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/210915_033646/0000/SKFlatNtuple_2016preVFP_MC_2.root");
    //m.AddFile("/gv0/DATA/SKFlat/Run2UltraLegacy_v2/2016preVFP/MC/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/210915_033646/0000/SKFlatNtuple_2016preVFP_MC_3.root");
    //m.AddFile("/gv0/DATA/SKFlat/Run2UltraLegacy_v2/2016preVFP/MC/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/210915_033646/0000/SKFlatNtuple_2016preVFP_MC_4.root");
    //m.AddFile("/gv0/DATA/SKFlat/Run2UltraLegacy_v2/2016preVFP/MC/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/210915_033646/0000/SKFlatNtuple_2016preVFP_MC_5.root");
    //m.AddFile("/gv0/DATA/SKFlat/Run2UltraLegacy_v2/2016preVFP/MC/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/210915_033646/0000/SKFlatNtuple_2016preVFP_MC_6.root");
  }
  else if(era=="2016preVFP" && isdata=="mc" && stream=="SSWWTypeI_SF_M1500"){
    m.AddFile("/gv0/DATA/SKFlat/Run2UltraLegacy_v2/2016preVFP/MC/SSWWTypeI_NLO_SF_M1500/211126_002710/0000/SKFlatNtuple_2016preVFP_MC_1.root");
    //m.AddFile("/gv0/DATA/SKFlat/Run2UltraLegacy_v2/2016preVFP/MC/SSWWTypeI_NLO_SF_M1500/211126_002710/0000/SKFlatNtuple_2016preVFP_MC_2.root");
    //m.AddFile("/gv0/DATA/SKFlat/Run2UltraLegacy_v2/2016preVFP/MC/SSWWTypeI_NLO_SF_M1500/211126_002710/0000/SKFlatNtuple_2016preVFP_MC_3.root");
    //m.AddFile("/gv0/DATA/SKFlat/Run2UltraLegacy_v2/2016preVFP/MC/SSWWTypeI_NLO_SF_M1500/211126_002710/0000/SKFlatNtuple_2016preVFP_MC_4.root");
    //m.AddFile("/gv0/DATA/SKFlat/Run2UltraLegacy_v2/2016preVFP/MC/SSWWTypeI_NLO_SF_M1500/211126_002710/0000/SKFlatNtuple_2016preVFP_MC_5.root");
    //m.AddFile("/gv0/DATA/SKFlat/Run2UltraLegacy_v2/2016preVFP/MC/SSWWTypeI_NLO_SF_M1500/211126_002710/0000/SKFlatNtuple_2016preVFP_MC_6.root");
  }
	else if(era=="2017" && isdata=="data" && stream=="DM"){
    //m.AddFile("/gv0/DATA/SKFlat/Run2UltraLegacy_v2/2017/DATA/DoubleMuon/periodB/210806_002721/0000/SKFlatNtuple_2017_DATA_1.root"); // for Fake.C
    m.AddFile("/gv0/DATA/SKFlat/Run2UltraLegacy_v2/2017/DATA_SkimTree_Dilepton/DoubleMuon/periodB/2021_08_30_162016/SKFlatNtuple_2017_DATA_0.root");
  }
  else if(era=="2017" && isdata=="mc" && stream=="DY"){
    m.AddFile("/gv0/DATA/SKFlat/Run2UltraLegacy_v2/2017/MC/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/210915_034020/0000/SKFlatNtuple_2017_MC_1.root");
    //m.AddFile("/gv0/DATA/SKFlat/Run2UltraLegacy_v2/2017/MC/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/210915_034020/0000/SKFlatNtuple_2017_MC_2.root");
    //m.AddFile("/gv0/DATA/SKFlat/Run2UltraLegacy_v2/2017/MC/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/210915_034020/0000/SKFlatNtuple_2017_MC_3.root");
    //m.AddFile("/gv0/DATA/SKFlat/Run2UltraLegacy_v2/2017/MC/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/210915_034020/0000/SKFlatNtuple_2017_MC_4.root");
    //m.AddFile("/gv0/DATA/SKFlat/Run2UltraLegacy_v2/2017/MC/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/210915_034020/0000/SKFlatNtuple_2017_MC_5.root");
  }
	else if(era=="2018" && isdata=="data" && stream=="DM"){
    m.AddFile("/gv0/DATA/SKFlat/Run2UltraLegacy_v2/2018/DATA_SkimTree_Dilepton/DoubleMuon/periodB/2021_08_30_141017/SKFlatNtuple_2018_DATA_0.root");
  }
  m.SetOutfilePath("hists_"+era+"_"+isdata+"_"+stream+".root");
  m.Init();
  m.initializeAnalyzer();
  m.initializeAnalyzerTools();
  m.SwitchToTempDir();
  m.Loop();

  m.WriteHist();

}
