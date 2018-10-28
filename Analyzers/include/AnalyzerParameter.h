#ifndef AnalyzerParameter_h
#define AnalyzerParameter_h

#include "TString.h"

class AnalyzerParameter{

public:

  TString Name;

  bool MCCorrrectionIgnoreNoHist;

  TString Electron_Tight_ID, Electron_Loose_ID, Electron_Veto_ID;
  TString Electron_ID_SF_Key;
  TString Electron_FR_ID, Electron_FR_Key;
  TString Electron_CF_ID, Electron_CF_Key;
  double Electron_Tight_RelIso, Electron_Loose_RelIso, Electron_Veto_RelIso;
  bool Electron_UseMini, Electron_UsePtCone;
  double Electron_MinPt;

  TString Muon_Tight_ID, Muon_Loose_ID, Muon_Veto_ID;
  TString Muon_ID_SF_Key, Muon_ISO_SF_Key, Muon_Trigger_SF_Key;
  TString Muon_FR_ID, Muon_FR_Key;
  TString Muon_CF_ID, Muon_CF_Key;
  double Muon_Tight_RelIso, Muon_Loose_RelIso, Muon_Veto_RelIso;
  bool Muon_UseMini, Muon_UsePtCone, Muon_UseTuneP;
  double Muon_MinPt;

  TString Jet_ID, FatJet_ID;

  void Clear();

  AnalyzerParameter();
  ~AnalyzerParameter();

};

#endif