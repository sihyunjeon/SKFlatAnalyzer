#include "Jet.h"

ClassImp(Jet)

Jet::Jet() : Particle() {
  j_area=-999.;
  j_partonFlavour=-999;
  j_hadronFlavour=-999;
  j_CSVv2=-999.;
  j_DeepCSV=-999.;
  j_DeepFlavour_b=-999;
  j_DeepFlavour_bb=-999;
  j_DeepFlavour_lepb=-999;
  j_DeepFlavour_c=-999;
  j_DeepFlavour_uds=-999;
  j_DeepFlavour_g=-999;
  j_CvsL=-999.;
  j_CvsB=-999.;
  j_DeepCvsL=-999.;
  j_DeepCvsB=-999.;
  j_chargedHadronEnergyFraction=-999.;
  j_neutralHadronEnergyFraction=-999.;
  j_neutralEmEnergyFraction=-999.;
  j_chargedEmEnergyFraction=-999.;
  j_muonEnergyFraction=-999.;
  j_chargedMultiplicity=-999;
  j_neutralMultiplicity=-999;
  j_PileupJetId=-999.;
  j_En_up=1.;
  j_En_down=1.;
  j_Res  = 1.;
  j_Res_up = 1.;
  j_Res_down = 1.;
  j_PxUnSmeared=-999.;
  j_PyUnSmeared=-999.;
  j_tightJetID=false;
  j_tightLepVetoJetID=false;
}

Jet::~Jet(){

}

void Jet::SetArea(double area){
  j_area = area;
}
void Jet::SetGenFlavours(double pf, double hf){
  j_partonFlavour = pf;
  j_hadronFlavour = hf;
}
void Jet::SetTaggerResults(std::vector<double> ds){
  j_CSVv2             = ds.at(0);
  j_DeepCSV           = ds.at(1);
  j_DeepCvsL          = ds.at(2);
  j_DeepCvsB          = ds.at(3);
  j_DeepFlavour_b     = ds.at(4);
  j_DeepFlavour_bb    = ds.at(5);
  j_DeepFlavour_lepb  = ds.at(6);
  j_DeepFlavour_c     = ds.at(7);
  j_DeepFlavour_uds   = ds.at(8);
  j_DeepFlavour_g     = ds.at(9);
  j_CvsL              = ds.at(10);
  j_CvsB              = ds.at(11);
}
void Jet::SetEnergyFractions(double cH, double nH, double nEM, double cEM, double muE){
  j_chargedHadronEnergyFraction = cH;
  j_neutralHadronEnergyFraction = nH;
  j_neutralEmEnergyFraction = nEM;
  j_chargedEmEnergyFraction = cEM;
  j_muonEnergyFraction = muE;
}
void Jet::SetMultiplicities(double cM, double nM){
  j_chargedMultiplicity = cM;
  j_neutralMultiplicity = nM;
}
void Jet::SetPileupJetId(double v){
  j_PileupJetId = v;
}

void Jet::SetEnShift(double en_up, double en_down){
  j_En_up = en_up;
  j_En_down = en_down;
}

void Jet::SetPxUnSmeared(double px){
  j_PxUnSmeared=px;
}

void Jet::SetPyUnSmeared(double py){
  j_PyUnSmeared=py;
}

void Jet::SetRes(double res){
  j_Res = res;
}

void Jet::SetResShift(double res_up, double res_down){
  j_Res_up = res_up;
  j_Res_down = res_down;
}

void Jet::SetTightJetID(double b){
  j_tightJetID = b;
}
void Jet::SetTightLepVetoJetID(double b){
  j_tightLepVetoJetID = b;
}

bool Jet::PassID(TString ID) const {

  if(ID=="tight") return Pass_tightJetID();
  if(ID=="tightLepVeto") return Pass_tightLepVetoJetID();
  if(ID=="HNTight") return Pass_HNTight();

  cout << "[Jet::PassID] No id : " << ID << endl;
  exit(ENODATA);

  return false;

}

double Jet::GetTaggerResult(JetTagging::Tagger tg) const {

  if(tg==JetTagging::CSVv2) return j_CSVv2;
  else if(tg==JetTagging::DeepCSV) return j_DeepCSV;
  else if(tg==JetTagging::DeepJet) return j_DeepFlavour_b+j_DeepFlavour_bb+j_DeepFlavour_lepb;
  else if(tg==JetTagging::DeepFlavour_b) return j_DeepFlavour_b;
  else if(tg==JetTagging::DeepFlavour_bb) return j_DeepFlavour_bb;
  else if(tg==JetTagging::DeepFlavour_lepb) return j_DeepFlavour_lepb;
  else if(tg==JetTagging::DeepFlavour_c) return j_DeepFlavour_c;
  else if(tg==JetTagging::DeepFlavour_uds) return j_DeepFlavour_uds;
  else if(tg==JetTagging::DeepFlavour_g) return j_DeepFlavour_g;
  else if(tg==JetTagging::CvsL) return j_CvsL;
  else if(tg==JetTagging::CvsB) return j_CvsB;
  else if(tg==JetTagging::DeepCvsL) return j_DeepCvsL;
  else if(tg==JetTagging::DeepCvsB) return j_DeepCvsB;
  else{
    cout << "[Jet::GetTaggerResult] ERROR; Wrong tagger : " << tg << endl;
    return -999;
  }
}

bool Jet::PassPileupMVA(TString WP, TString Era) const {

  //https://twiki.cern.ch/twiki/bin/view/CMS/PileupJetIDUL

  bool pass=false;
  
  if (Era.Contains("2016")){
    if(WP=="tight"){
      if(fabs(this->Eta()) < 2.5){
  if(this->Pt() < 10.){ pass=true;}
  else if(this->Pt() < 20.){ if(PileupJetId() > 0.71) pass=true; }
  else if(this->Pt() < 30.){ if(PileupJetId() > 0.87) pass=true; }
  else if(this->Pt() < 40.){ if(PileupJetId() > 0.94) pass=true; }
  else if(this->Pt() < 50.){ if(PileupJetId() > 0.97) pass=true; }
  else pass=true;
      }
      else if(fabs(this->Eta()) < 2.75){
  if(this->Pt() < 10.){ pass=true;}
  else if(this->Pt() < 20.){ if(PileupJetId() > -0.32) pass=true; }
  else if(this->Pt() < 30.){ if(PileupJetId() > -0.08) pass=true; }
  else if(this->Pt() < 40.){ if(PileupJetId() > 0.24) pass=true; }
  else if(this->Pt() < 50.){ if(PileupJetId() > 0.48) pass=true; }
  else pass=true;
      }
      else if(fabs(this->Eta()) < 3.0){
  if(this->Pt() < 10.){ pass=true;}
  else if(this->Pt() < 20.){ if(PileupJetId() > -0.30) pass=true; }
  else if(this->Pt() < 30.){ if(PileupJetId() > -0.16) pass=true; }
  else if(this->Pt() < 40.){ if(PileupJetId() >  0.05) pass=true; }
  else if(this->Pt() < 50.){ if(PileupJetId() >  0.26) pass=true; }
  else pass=true;
      }
      else if(fabs(this->Eta()) < 5.0){
  if(this->Pt() < 10.){ pass=true;}
  else if(this->Pt() < 20.){ if(PileupJetId() > -0.22) pass=true; }
  else if(this->Pt() < 30.){ if(PileupJetId() > -0.12) pass=true; }
  else if(this->Pt() < 40.){ if(PileupJetId() >  0.10) pass=true; }
  else if(this->Pt() < 50.){ if(PileupJetId() >  0.29) pass=true; }
  else pass=true;
      }
      else pass=true;
    }
    else if(WP=="medium"){
      if(fabs(this->Eta()) < 2.5){
  if(this->Pt() < 10.){ pass=true;}
  else if(this->Pt() < 20.){ if(PileupJetId() > 0.20) pass=true; }
  else if(this->Pt() < 30.){ if(PileupJetId() > 0.62) pass=true; }
  else if(this->Pt() < 40.){ if(PileupJetId() > 0.86) pass=true; }
  else if(this->Pt() < 50.){ if(PileupJetId() > 0.93) pass=true; }
  else pass=true;
      }
      else if(fabs(this->Eta()) < 2.75){
  if(this->Pt() < 10.){ pass=true;}
  else if(this->Pt() < 20.){ if(PileupJetId() > -0.56) pass=true; }
  else if(this->Pt() < 30.){ if(PileupJetId() > -0.39) pass=true; }
  else if(this->Pt() < 40.){ if(PileupJetId() > -0.10) pass=true; }
  else if(this->Pt() < 50.){ if(PileupJetId() >  0.19) pass=true; }
  else pass=true;
      }
      else if(fabs(this->Eta()) < 3.0){
  if(this->Pt() < 10.){ pass=true;}
  else if(this->Pt() < 20.){ if(PileupJetId() > -0.43) pass=true; }
  else if(this->Pt() < 30.){ if(PileupJetId() > -0.32) pass=true; }
  else if(this->Pt() < 40.){ if(PileupJetId() > -0.15) pass=true; }
  else if(this->Pt() < 50.){ if(PileupJetId() >  0.04) pass=true; }
  else pass=true;
      }
      else if(fabs(this->Eta()) < 5.0){
  if(this->Pt() < 10.){ pass=true;}
  else if(this->Pt() < 20.){ if(PileupJetId() > -0.38) pass=true; }
  else if(this->Pt() < 30.){ if(PileupJetId() > -0.29) pass=true; }
  else if(this->Pt() < 40.){ if(PileupJetId() > -0.08) pass=true; }
  else if(this->Pt() < 50.){ if(PileupJetId() >  0.12) pass=true; }
  else pass=true;
      }
      else pass=true;
    }
    else if(WP=="loose"){
      if(fabs(this->Eta()) < 2.5){
  if(this->Pt() < 10.){ pass=true;}
  else if(this->Pt() < 20.){ if(PileupJetId() > -0.95) pass=true; }
  else if(this->Pt() < 30.){ if(PileupJetId() > -0.90) pass=true; }
  else if(this->Pt() < 40.){ if(PileupJetId() > -0.71) pass=true; }
  else if(this->Pt() < 50.){ if(PileupJetId() > -0.42) pass=true; }
  else pass=true;
      }
      else if(fabs(this->Eta()) < 2.75){
  if(this->Pt() < 10.){ pass=true;}
  else if(this->Pt() < 20.){ if(PileupJetId() > -0.70) pass=true; }
  else if(this->Pt() < 30.){ if(PileupJetId() > -0.57) pass=true; }
  else if(this->Pt() < 40.){ if(PileupJetId() > -0.36) pass=true; }
  else if(this->Pt() < 50.){ if(PileupJetId() > -0.09) pass=true; }
  else pass=true;
      }
      else if(fabs(this->Eta()) < 3.0){
  if(this->Pt() < 10.){ pass=true;}
  else if(this->Pt() < 20.){ if(PileupJetId() > -0.52) pass=true; }
  else if(this->Pt() < 30.){ if(PileupJetId() > -0.43) pass=true; }
  else if(this->Pt() < 40.){ if(PileupJetId() > -0.29) pass=true; }
  else if(this->Pt() < 50.){ if(PileupJetId() > -0.14) pass=true; }
  else pass=true;
      }
      else if(fabs(this->Eta()) < 5.0){
  if(this->Pt() < 10.){ pass=true;}
  else if(this->Pt() < 20.){ if(PileupJetId() > -0.49) pass=true; }
  else if(this->Pt() < 30.){ if(PileupJetId() > -0.42) pass=true; }
  else if(this->Pt() < 40.){ if(PileupJetId() > -0.23) pass=true; }
  else if(this->Pt() < 50.){ if(PileupJetId() > -0.02) pass=true; }
  else pass=true;
      }
      else pass=true;
    }
    else{
      cout << "[Jet::PassPileupID] No wp : " << WP << endl;
      exit(EXIT_FAILURE);
    }
  }
  

  //2017

  else if (Era.Contains("2017")){

    if(WP=="tight"){
      if(fabs(this->Eta()) < 2.5){
        if(this->Pt() < 10.){ pass=true;}
        else if(this->Pt() < 20.){ if(PileupJetId() > 0.77) pass=true; }
        else if(this->Pt() < 30.){ if(PileupJetId() > 0.90) pass=true; }
        else if(this->Pt() < 40.){ if(PileupJetId() > 0.96) pass=true; }
        else if(this->Pt() < 50.){ if(PileupJetId() > 0.96) pass=true; }
        else pass=true;
      }
      else if(fabs(this->Eta()) < 2.75){
        if(this->Pt() < 10.){ pass=true;}
        else if(this->Pt() < 20.){ if(PileupJetId() > 0.38) pass=true; }
        else if(this->Pt() < 30.){ if(PileupJetId() > 0.60) pass=true; }
        else if(this->Pt() < 40.){ if(PileupJetId() > 0.82) pass=true; }
        else if(this->Pt() < 50.){ if(PileupJetId() > 0.92) pass=true; }
        else pass=true;
      }
      else if(fabs(this->Eta()) < 3.0){
        if(this->Pt() < 10.){ pass=true;}
        else if(this->Pt() < 20.){ if(PileupJetId() > -0.31) pass=true; }
        else if(this->Pt() < 30.){ if(PileupJetId() > -0.12) pass=true; }
        else if(this->Pt() < 40.){ if(PileupJetId() >  0.20) pass=true; }
        else if(this->Pt() < 50.){ if(PileupJetId() >  0.47) pass=true; }
        else pass=true;
      }
      else if(fabs(this->Eta()) < 5.0){
        if(this->Pt() < 10.){ pass=true;}
        else if(this->Pt() < 20.){ if(PileupJetId() > -0.21) pass=true; }
        else if(this->Pt() < 30.){ if(PileupJetId() > -0.13) pass=true; }
        else if(this->Pt() < 40.){ if(PileupJetId() >  0.09) pass=true; }
        else if(this->Pt() < 50.){ if(PileupJetId() >  0.29) pass=true; }
        else pass=true;
      }
      else pass=true;
    }
    else if(WP=="medium"){
      if(fabs(this->Eta()) < 2.5){
        if(this->Pt() < 10.){ pass=true;}
        else if(this->Pt() < 20.){ if(PileupJetId() > 0.26) pass=true; }
        else if(this->Pt() < 30.){ if(PileupJetId() > 0.68) pass=true; }
        else if(this->Pt() < 40.){ if(PileupJetId() > 0.90) pass=true; }
        else if(this->Pt() < 50.){ if(PileupJetId() > 0.96) pass=true; }
        else pass=true;
      }
      else if(fabs(this->Eta()) < 2.75){
        if(this->Pt() < 10.){ pass=true;}
        else if(this->Pt() < 20.){ if(PileupJetId() > -0.33) pass=true; }
        else if(this->Pt() < 30.){ if(PileupJetId() > -0.04) pass=true; }
        else if(this->Pt() < 40.){ if(PileupJetId() >  0.36) pass=true; }
        else if(this->Pt() < 50.){ if(PileupJetId() >  0.61) pass=true; }
        else pass=true;
      }
      else if(fabs(this->Eta()) < 3.0){
        if(this->Pt() < 10.){ pass=true;}
        else if(this->Pt() < 20.){ if(PileupJetId() > -0.54) pass=true; }
        else if(this->Pt() < 30.){ if(PileupJetId() > -0.43) pass=true; }
        else if(this->Pt() < 40.){ if(PileupJetId() > -0.16) pass=true; }
        else if(this->Pt() < 50.){ if(PileupJetId() >  0.14) pass=true; }
        else pass=true;
      }
      else if(fabs(this->Eta()) < 5.0){
        if(this->Pt() < 10.){ pass=true;}
        else if(this->Pt() < 20.){ if(PileupJetId() > -0.37) pass=true; }
        else if(this->Pt() < 30.){ if(PileupJetId() > -0.30) pass=true; }
        else if(this->Pt() < 40.){ if(PileupJetId() > -0.09) pass=true; }
        else if(this->Pt() < 50.){ if(PileupJetId() >  0.12) pass=true; }
        else pass=true;
      }
      else pass=true;
    }
    else if(WP=="loose"){
      if(fabs(this->Eta()) < 2.5){
        if(this->Pt() < 10.){ pass=true;}
        else if(this->Pt() < 20.){ if(PileupJetId() > -0.95) pass=true; }
        else if(this->Pt() < 30.){ if(PileupJetId() > -0.88) pass=true; }
        else if(this->Pt() < 40.){ if(PileupJetId() > -0.63) pass=true; }
        else if(this->Pt() < 50.){ if(PileupJetId() > -0.19) pass=true; }
        else pass=true;
      }
      else if(fabs(this->Eta()) < 2.75){
        if(this->Pt() < 10.){ pass=true;}
        else if(this->Pt() < 20.){ if(PileupJetId() > -0.72) pass=true; }
        else if(this->Pt() < 30.){ if(PileupJetId() > -0.55) pass=true; }
        else if(this->Pt() < 40.){ if(PileupJetId() > -0.18) pass=true; }
        else if(this->Pt() < 50.){ if(PileupJetId() >  0.22) pass=true; }
        else pass=true;
      }
      else if(fabs(this->Eta()) < 3.0){
        if(this->Pt() < 10.){ pass=true;}
        else if(this->Pt() < 20.){ if(PileupJetId() > -0.68) pass=true; }
        else if(this->Pt() < 30.){ if(PileupJetId() > -0.60) pass=true; }
        else if(this->Pt() < 40.){ if(PileupJetId() > -0.43) pass=true; }
        else if(this->Pt() < 50.){ if(PileupJetId() > -0.13) pass=true; }
        else pass=true;
      }
      else if(fabs(this->Eta()) < 5.0){
        if(this->Pt() < 10.){ pass=true;}
        else if(this->Pt() < 20.){ if(PileupJetId() > -0.47) pass=true; }
        else if(this->Pt() < 30.){ if(PileupJetId() > -0.43) pass=true; }
        else if(this->Pt() < 40.){ if(PileupJetId() > -0.24) pass=true; }
        else if(this->Pt() < 50.){ if(PileupJetId() > -0.03) pass=true; }
        else pass=true;
      }
      else pass=true;
    }
    else{
      cout << "[Jet::PassPileupID] No wp : " << WP << endl;
      exit(EXIT_FAILURE);
    }
  }

  //2018

  else if (Era.Contains("2018")){
    if(WP=="tight"){
      if(fabs(this->Eta()) < 2.5){
        if(this->Pt() < 10.){ pass=true;}
        else if(this->Pt() < 20.){ if(PileupJetId() > 0.77) pass=true; }
        else if(this->Pt() < 30.){ if(PileupJetId() > 0.90) pass=true; }
        else if(this->Pt() < 40.){ if(PileupJetId() > 0.96) pass=true; }
        else if(this->Pt() < 50.){ if(PileupJetId() > 0.98) pass=true; }
        else pass=true;
      }
      else if(fabs(this->Eta()) < 2.75){
        if(this->Pt() < 10.){ pass=true;}
        else if(this->Pt() < 20.){ if(PileupJetId() > 0.38) pass=true; }
        else if(this->Pt() < 30.){ if(PileupJetId() > 0.60) pass=true; }
        else if(this->Pt() < 40.){ if(PileupJetId() > 0.82) pass=true; }
        else if(this->Pt() < 50.){ if(PileupJetId() > 0.92) pass=true; }
        else pass=true;
      }
      else if(fabs(this->Eta()) < 3.0){
        if(this->Pt() < 10.){ pass=true;}
        else if(this->Pt() < 20.){ if(PileupJetId() > -0.31) pass=true; }
        else if(this->Pt() < 30.){ if(PileupJetId() > -0.12) pass=true; }
        else if(this->Pt() < 40.){ if(PileupJetId() >  0.20) pass=true; }
        else if(this->Pt() < 50.){ if(PileupJetId() >  0.47) pass=true; }
        else pass=true;
      }
      else if(fabs(this->Eta()) < 5.0){
        if(this->Pt() < 10.){ pass=true;}
        else if(this->Pt() < 20.){ if(PileupJetId() > -0.21) pass=true; }
        else if(this->Pt() < 30.){ if(PileupJetId() > -0.13) pass=true; }
        else if(this->Pt() < 40.){ if(PileupJetId() >  0.09) pass=true; }
        else if(this->Pt() < 50.){ if(PileupJetId() >  0.29) pass=true; }
        else pass=true;
      }
      else pass=true;
    }
    else if(WP=="medium"){
      if(fabs(this->Eta()) < 2.5){
        if(this->Pt() < 10.){ pass=true;}
        else if(this->Pt() < 20.){ if(PileupJetId() > 0.26) pass=true; }
        else if(this->Pt() < 30.){ if(PileupJetId() > 0.68) pass=true; }
        else if(this->Pt() < 40.){ if(PileupJetId() > 0.90) pass=true; }
        else if(this->Pt() < 50.){ if(PileupJetId() > 0.96) pass=true; }
        else pass=true;
      }
      else if(fabs(this->Eta()) < 2.75){
        if(this->Pt() < 10.){ pass=true;}
        else if(this->Pt() < 20.){ if(PileupJetId() > -0.33) pass=true; }
        else if(this->Pt() < 30.){ if(PileupJetId() > -0.04) pass=true; }
        else if(this->Pt() < 40.){ if(PileupJetId() >  0.36) pass=true; }
        else if(this->Pt() < 50.){ if(PileupJetId() >  0.61) pass=true; }
        else pass=true;
      }
      else if(fabs(this->Eta()) < 3.0){
        if(this->Pt() < 10.){ pass=true;}
        else if(this->Pt() < 20.){ if(PileupJetId() > -0.54) pass=true; }
        else if(this->Pt() < 30.){ if(PileupJetId() > -0.43) pass=true; }
        else if(this->Pt() < 40.){ if(PileupJetId() > -0.16) pass=true; }
        else if(this->Pt() < 50.){ if(PileupJetId() >  0.14) pass=true; }
        else pass=true;
      }
      else if(fabs(this->Eta()) < 5.0){
        if(this->Pt() < 10.){ pass=true;}
        else if(this->Pt() < 20.){ if(PileupJetId() > -0.37) pass=true; }
        else if(this->Pt() < 30.){ if(PileupJetId() > -0.30) pass=true; }
        else if(this->Pt() < 40.){ if(PileupJetId() > -0.09) pass=true; }
        else if(this->Pt() < 50.){ if(PileupJetId() >  0.12) pass=true; }
        else pass=true;
      }
      else pass=true;
    }
    else if(WP=="loose"){
      if(fabs(this->Eta()) < 2.5){
        if(this->Pt() < 10.){ pass=true;}
        else if(this->Pt() < 20.){ if(PileupJetId() > -0.95) pass=true; }
        else if(this->Pt() < 30.){ if(PileupJetId() > -0.88) pass=true; }
        else if(this->Pt() < 40.){ if(PileupJetId() > -0.63) pass=true; }
        else if(this->Pt() < 50.){ if(PileupJetId() > -0.19) pass=true; }
        else pass=true;
      }
      else if(fabs(this->Eta()) < 2.75){
        if(this->Pt() < 10.){ pass=true;}
        else if(this->Pt() < 20.){ if(PileupJetId() > -0.72) pass=true; }
        else if(this->Pt() < 30.){ if(PileupJetId() > -0.55) pass=true; }
        else if(this->Pt() < 40.){ if(PileupJetId() > -0.18) pass=true; }
        else if(this->Pt() < 50.){ if(PileupJetId() >  0.22) pass=true; }
        else pass=true;
      }
      else if(fabs(this->Eta()) < 3.0){
        if(this->Pt() < 10.){ pass=true;}
        else if(this->Pt() < 20.){ if(PileupJetId() > -0.68) pass=true; }
        else if(this->Pt() < 30.){ if(PileupJetId() > -0.60) pass=true; }
        else if(this->Pt() < 40.){ if(PileupJetId() > -0.43) pass=true; }
        else if(this->Pt() < 50.){ if(PileupJetId() > -0.13) pass=true; }
        else pass=true;
      }
      else if(fabs(this->Eta()) < 5.0){
        if(this->Pt() < 10.){ pass=true;}
        else if(this->Pt() < 20.){ if(PileupJetId() > -0.47) pass=true; }
        else if(this->Pt() < 30.){ if(PileupJetId() > -0.43) pass=true; }
        else if(this->Pt() < 40.){ if(PileupJetId() > -0.24) pass=true; }
        else if(this->Pt() < 50.){ if(PileupJetId() > -0.03) pass=true; }
        else pass=true;
      }
      else pass=true;
    }
    else{
      cout << "[Jet::PassPileupID] No wp : " << WP << endl;
      exit(EXIT_FAILURE);
    }
  }
  
  return pass;
}

bool Jet::Pass_HNTight() const {
  if(!Pass_tightJetID()) return false;
  //if(!PassPileupMVA("loose")) return false;

  return true;
}

