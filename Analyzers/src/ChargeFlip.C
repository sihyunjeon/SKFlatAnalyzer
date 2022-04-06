#include "ChargeFlip.h" 

ChargeFlip::ChargeFlip(){

}

void ChargeFlip::initializeAnalyzer(){

  if(DataYear==2016){
    EleVetoIDs = {
      "ISRVeto",
    };
    EleIDs = { 
      //"HEEP_dZ_CF",
      "HNTightV1",
      //"HNMVATight",
    }; // PassID() in Electron.C
    EleIDSFKeys = {
      "",
    }; // histmap.txt
    EleTriggerName = "HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v"; // script/PDandTriggers/2016/DoubleEG.txt
    lep0ptcut = 25.;
    lep1ptcut = 15.;
  }
  else if(DataYear==2017){
    EleVetoIDs = {
      "ISRVeto",
    };
    EleIDs = {
      //"HEEP_dZ_CF",
      "HNTightV1",
      //"HNMVATight",
    };
    EleIDSFKeys = {
      "",
    };
    EleTriggerName = "HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_v";
    lep0ptcut = 25.;
    lep1ptcut = 15.;
  }
  else if(DataYear==2018){
    EleVetoIDs = {
      "ISRVeto",
    };
    EleIDs = {
      //"HEEP2018_dZ_CF",
      "HNTightV1",
      //"HNMVATight",
    };
    EleIDSFKeys = {
      "",
    };
    //EleTriggerName = "HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v";
    EleTriggerName = "HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_v"; //JH : would this affect the result?
    lep0ptcut = 25.;
    lep1ptcut = 15.;
  }

  std::vector<JetTagging::Parameters> jtps;
  jtps.push_back( JetTagging::Parameters(JetTagging::DeepCSV, JetTagging::Medium, JetTagging::incl, JetTagging::comb) );
  mcCorr->SetJetTaggingParameters(jtps);
}

ChargeFlip::~ChargeFlip(){

}

void ChargeFlip::executeEvent(Long64_t Nentry){

  AllEles = GetAllElectrons();
  AllMuons = GetAllMuons();
  AllJets = GetAllJets();

  AnalyzerParameter param;

  for(unsigned int i=0; i<EleIDs.size(); i++){

    TString EleID = EleIDs.at(i);
    //TString EleIDSFKey = EleIDSFKeys.at(i);
  
    param.Clear();
  
    //param.CFsyst_ = AnalyzerParameter::CF_Central;
  
    param.Name = EleID;

    param.Electron_Tight_ID = EleID;

    param.Electron_Veto_ID = EleVetoIDs.at(i);
 
    if(HasFlag("250")){
      param.Electron_Tight_ID = EleID+"_250";
    }
    else if(HasFlag("200")){
      param.Electron_Tight_ID = EleID+"_200";
    } // To check 3charge cut
  
    executeEventFromParameter(param, Nentry);
  
    //if(HasFlag("RunSyst")){
  
    //  for(int i=1; i<AnalyzerParameter::N_CFSyst; i++){
  
    //  param.CFsyst_ = AnalyzerParameter::CFSyst(i);
    //  param.Name = EleID+"_"+"Syst_"+param.GetCFSystType();
    //  executeEventFromParameter(param, Nentry);
  
    //  }

    //}

  }

}

void ChargeFlip::executeEventFromParameter(AnalyzerParameter param, Long64_t Nentry){

  Event ev = GetEvent();

  MllLeft = 60;
  MllRight = 120;
  MinPt = 25;
  NBin = 30; //initialize syst. parameters

  //if(param.CFsyst_ == AnalyzerParameter::CF_Central){
  //
  //}
  //else if(param.CFsyst_ == AnalyzerParameter::MllRangeUp){
  //  MllLeft = 55;
  //  MllRight = 125;
  //  //NBin = 40;
  //}
  //else if(param.CFsyst_ == AnalyzerParameter::MllRangeDown){
  //  MllLeft = 65;
  //  MllRight = 115;
  //  //NBin = 20;
  //}
  //else if(param.CFsyst_ == AnalyzerParameter::MinPtUp){
  //  MinPt = 28;
  //}
  //else if(param.CFsyst_ == AnalyzerParameter::MinPtDown){
  //  MinPt = 22;
  //}
  //else if(param.CFsyst_ == AnalyzerParameter::NBinUp){
  //  NBin = 35;
  //}
  //else if(param.CFsyst_ == AnalyzerParameter::NBinDown){
  //  NBin = 25;
  //}
  //else{
  //  cout << "[ExampleRun::executeEventFromParameter] Wrong syst" << endl;
  //  exit(EXIT_FAILURE);
  //}

  vector<Electron> eles;
  vector<Electron> eles_veto;
  vector<Muon> muons;
  vector<Muon> muons_veto;
  vector<Jet> jets;
  vector<Jet> jets_nolepveto;

  if(!IsDATA){

    // CF ID selection //

    if(param.Electron_Tight_ID.Contains("HEEP")) eles = SelectElectrons(AllEles, param.Electron_Tight_ID, 50., 2.5);
    else eles = SelectElectrons(AllEles, param.Electron_Tight_ID, 25., 2.5);
    std::sort(eles.begin(), eles.end(), PtComparing);

    vector<Gen> gens = GetGens();
    vector<Electron> eles_prmpt = ElectronPromptOnlyChargeFlip(eles, gens); // Get prompt electrons except conversions
    
    if(HasFlag("CFrate")){

      // Measure CF rate using MC //

      for(unsigned int i=0; i<eles.size(); i++){
        Gen truth_lep = GetGenMatchedLepton(eles.at(i), gens);
        if(GetLeptonType(eles.at(i), gens)<=0 || GetLeptonType(eles.at(i), gens)>=4) continue; // conversion veto
        if(truth_lep.PID() == 0) continue; 
    
        int truth_lep_Charge;
        if(truth_lep.PID() == 11) truth_lep_Charge = -1;
        else if(truth_lep.PID() == -11) truth_lep_Charge = 1;
      
        //Measure with original method (many 1/pt bins, 3 eta bins)
        if(abs(eles.at(i).scEta())<0.8){
          FillHist(param.Name+"/CFrate/EtaRegion1_Denom", 1./eles.at(i).Pt(), 1., 40, 0., 0.04);
          if(truth_lep_Charge*eles.at(i).Charge()<0){
            //cout << "!!EtaRegion1!! truth lepton charge : " << truth_lep_Charge << ", reco lepton charge : " << eles.at(i).Charge() << endl;
            FillHist(param.Name+"/CFrate/EtaRegion1_Num", 1./eles.at(i).Pt(), 1., 40, 0., 0.04);
            //// SH's ask //
            //if(eles.size() == 2&&i == 0){
            //FillHist(param.Name+"/CFrate/EtaRegion1_IsLeading", 1, 1, 2, 0, 2);
            //}
            //else if(eles.size() == 2&&i == 1){
            //FillHist(param.Name+"/CFrate/EtaRegion1_IsLeading", 0, 1, 2, 0, 2);
            //}
          }
        }
        else if(0.8<=abs(eles.at(i).scEta())&&abs(eles.at(i).scEta())<1.4442){
          FillHist(param.Name+"/CFrate/EtaRegion2_Denom", 1./eles.at(i).Pt(), 1., 40, 0., 0.04);
          if(truth_lep_Charge*eles.at(i).Charge()<0){
            //cout << "!!EtaRegion2!! truth lepton charge : " << truth_lep_Charge << ", reco lepton charge : " << eles.at(i).Charge() << endl;
            FillHist(param.Name+"/CFrate/EtaRegion2_Num", 1./eles.at(i).Pt(), 1., 40, 0., 0.04);
            //// SH's ask //
            //if(eles.size() == 2&&i == 0){
            //FillHist(param.Name+"/CFrate/EtaRegion2_IsLeading", 1, 1, 2, 0, 2);
            //}
            //else if(eles.size() == 2&&i == 1){
            //FillHist(param.Name+"/CFrate/EtaRegion2_IsLeading", 0, 1, 2, 0, 2);
            //}
          }
        }
        else if(1.556<=abs(eles.at(i).scEta())&&abs(eles.at(i).scEta())<2.5){
          FillHist(param.Name+"/CFrate/EtaRegion3_Denom", 1./eles.at(i).Pt(), 1., 40, 0., 0.04);
          if(truth_lep_Charge*eles.at(i).Charge()<0){
            //cout << "!!EtaRegion3!! truth lepton charge : " << truth_lep_Charge << ", reco lepton charge : " << eles.at(i).Charge() << endl;
            FillHist(param.Name+"/CFrate/EtaRegion3_Num", 1./eles.at(i).Pt(), 1., 40, 0., 0.04);
            //// SH's ask //
            //if(eles.size() == 2&&i == 0){
            //FillHist(param.Name+"/CFrate/EtaRegion3_IsLeading", 1, 1, 2, 0, 2);
            //}
            //else if(eles.size() == 2&&i == 1){
            //FillHist(param.Name+"/CFrate/EtaRegion3_IsLeading", 0, 1, 2, 0, 2);
            //}
          }
        }

        //Measure with eta bins
        
        FillHist(param.Name+"/CFrate_Eta/Denom", eles.at(i).scEta(), 1., 50, -2.5, 2.5);
        FillHist(param.Name+"/CFrate_IP/Denom", eles.at(i).dXY(), 1., 200, -0.1, 0.1);
        FillHist(param.Name+"/CFrate_2D/Denom", 1./eles.at(i).Pt(), eles.at(i).scEta(), 1., 40, 0., 0.04, 50, -2.5, 2.5);
        if(truth_lep_Charge*eles.at(i).Charge()<0){
          //cout << "!!EtaRegion3!! truth lepton charge : " << truth_lep_Charge << ", reco lepton charge : " << eles.at(i).Charge() << endl;
          FillHist(param.Name+"/CFrate_Eta/Num", eles.at(i).scEta(), 1., 50, -2.5, 2.5);
          FillHist(param.Name+"/CFrate_IP/Num", eles.at(i).dXY(), 1., 200, -0.1, 0.1);
          FillHist(param.Name+"/CFrate_2D/Num", 1./eles.at(i).Pt(), eles.at(i).scEta(), 1., 40, 0., 0.04, 50, -2.5, 2.5);
        }

      }
    }

    //if(HasFlag("CFrateValidation")){ // to answer Unki's ask to see how CFrate vary with different dR matching

    //  // Select events with only two tight same-sign electrons //
    //  if(eles.size()==2&&eles.at(0).Charge()*eles.at(1).Charge()>0){

    //    for(int i=0; i<4; i++){

    //      double dR = (i+1)*0.1;

    //      Gen truth_lep1 = GetGenMatchedLepton(eles.at(0), gens, dR);
    //      Gen truth_lep2 = GetGenMatchedLepton(eles.at(1), gens, dR);

    //      FillHist(param.Name+"/CFrateValidation/Total", dR, 1, 4, 0.1, 0.5);
    //      if(abs(truth_lep1.PID())==11&&abs(truth_lep2.PID())==11) FillHist(param.Name+"/CFrateValidation/Matched", dR, 1, 4, 0.1, 0.5);
    //      else if(truth_lep1.PID()==0||truth_lep2.PID()==0) FillHist(param.Name+"/CFrateValidation/Missed", dR, 1, 4, 0.1, 0.5);

    //    }

    //  }
    //}

    if(HasFlag("ClosureTest")){

      // MC Closure test start //
     
      if(!PassMETFilter()) return;
      Particle METv = ev.GetMETVector();

      //if(eles.size() == 2){
  
      //  double weight = GetCFweight(eles, param.Electron_Tight_ID);
  
      //  Particle ZCand = eles.at(0)+eles.at(1);
  
      //  if(75.<=ZCand.M()&&ZCand.M()<105.){
      //    if(eles.at(0).Charge()*eles.at(1).Charge()<0){
      //      FillHist(param.Name+"/ClosureTest/ZMass_OS_CFweighted", ZCand.M(), weight, 30, 75., 105.);
      //    }
      //    else{
      //      FillHist(param.Name+"/ClosureTest/ZMass_SS", ZCand.M(), 1., 30, 75., 105.);
      //      FillHist(param.Name+"/ClosureTest/pt1_SS", eles.at(0).Pt(), 1., 70, 20., 90.);
      //      FillHist(param.Name+"/ClosureTest/pt2_SS", eles.at(1).Pt(), 1., 70, 20., 90.);
      //      FillHist(param.Name+"/ClosureTest/MET_SS", METv.Pt(), 1., 100, 0., 100.);
      //    }
      //  }
      //}
  
      // Now require only prompt electrons in SS events //

      if(eles_prmpt.size() == 2){

        double weight_prmpt = GetCFweight(eles_prmpt, param.Electron_Tight_ID, false, 0.);

        Particle ZCand_prmpt = eles_prmpt.at(0)+eles_prmpt.at(1);

        if(75.<=ZCand_prmpt.M()&&ZCand_prmpt.M()<105.){
          if(eles_prmpt.at(0).Charge()*eles_prmpt.at(1).Charge()<0){
            FillHist(param.Name+"/ClosureTest/ZMass_prmpt_OS_CFweighted", ZCand_prmpt.M(), weight_prmpt, 30, 75., 105.);
          }
          else{
            FillHist(param.Name+"/ClosureTest/ZMass_prmpt_SS", ZCand_prmpt.M(), 1., 30, 75., 105.);
            FillHist(param.Name+"/ClosureTest/pt1_prmpt_SS", eles_prmpt.at(0).Pt(), 1., 70, 20., 90.);
            FillHist(param.Name+"/ClosureTest/pt2_prmpt_SS", eles_prmpt.at(1).Pt(), 1., 70, 20., 90.);
            FillHist(param.Name+"/ClosureTest/MET_prmpt_SS", METv.Pt(), 1., 100, 0., 100.);
          }
        }
      }
  
      //
  
      // There's disagreement between OS_CFweighted and SS(where NO requirement on its promptness?). //
      // Now, Let's shift the electrons' energy //
      
      if(eles_prmpt.size() != 2) return;
  
      Particle ZCand = eles_prmpt.at(0)+eles_prmpt.at(1);
      Particle ZCand_tmp;
      Particle METv_tmp;
      double weight_tmp;
  
      for(int i=0;i<50;i++){
        vector<Electron> eles_tmp = eles_prmpt; // copy the vector
        for(int j=0;j<2;j++){
          eles_tmp.at(j).SetE(eles_tmp.at(j).E()*(1-0.001*(i+1)));
          eles_tmp.at(j).SetPtEtaPhiE(eles_tmp.at(j).E() * TMath::Sin(eles_tmp.at(j).Theta()), eles_tmp.at(j).Eta(), eles_tmp.at(j).Phi(), eles_tmp.at(j).E());
        }
  
        ZCand_tmp = eles_tmp.at(0) + eles_tmp.at(1);
        METv_tmp.SetPxPyPzE(METv.Px()+ZCand.Px()-ZCand_tmp.Px(),METv.Py()+ZCand.Py()-ZCand_tmp.Py(),0,METv.E()+ZCand.E()-ZCand_tmp.E());
        weight_tmp = GetCFweight(eles_tmp, param.Electron_Tight_ID, false, 0.);
  
        if(! (75.<=ZCand_tmp.M()&&ZCand_tmp.M()<105.) ) continue;
  
        if(eles_prmpt.at(0).Charge()*eles_prmpt.at(1).Charge()<0){
          FillHist(param.Name+"/ClosureTest/ZMass_OS_CFweighted_shifted_"+TString::Itoa(i+1,10), ZCand_tmp.M(), weight_tmp, 30, 75., 105.);
          FillHist(param.Name+"/ClosureTest/pt1_OS_CFweighted_shifted_"+TString::Itoa(i+1,10), eles_tmp.at(0).Pt(), weight_tmp, 70, 20., 90.);
          FillHist(param.Name+"/ClosureTest/pt2_OS_CFweighted_shifted_"+TString::Itoa(i+1,10), eles_tmp.at(1).Pt(), weight_tmp, 70, 20., 90.);
          FillHist(param.Name+"/ClosureTest/MET_OS_CFweighted_shifted_"+TString::Itoa(i+1,10), METv_tmp.Pt(), weight_tmp, 100, 0., 100.);
        }
      }

    }

    if(HasFlag("HalfSampleTest")){

      // Start the Half Sample Test : Even -> observed, Odd -> predicted //

      // Call the needed particles //

      if(!PassMETFilter()) return;
      Particle METv = ev.GetMETVector();
 
      muons = SelectMuons(AllMuons, "HNTightV1", 10., 2.4); // to calculate HT
      muons_veto = SelectMuons(AllMuons, "ISRVeto", 5., 2.4);
      eles_veto = SelectElectrons(AllEles, "ISRVeto", 10., 2.5);
      jets_nolepveto = SelectJetsPileupMVA(SelectJets(AllJets, "HNTight", 20., 2.7), "loose");
      jets = JetsVetoLeptonInside(jets_nolepveto, eles_veto, muons_veto);

      // Calculate the needed variables //

      double MET = METv.Pt(); //MET

      double LT = 0;
      for(unsigned int i=0; i<eles.size(); i++){
        LT += eles.at(i).Pt();
      } 
      for(unsigned int i=0; i<muons.size(); i++){
        LT += muons.at(i).Pt();
      }  //LT

      if(muons.size()==0&&eles.size()==0) FillHist(param.Name+"/HalfSampleTest/lepton_size_PassID", 0, 1, 7, 0, 7);
      else if(muons.size()==0&&eles.size()==1) FillHist(param.Name+"/HalfSampleTest/lepton_size_PassID", 1, 1, 7, 0, 7);
      else if(muons.size()==0&&eles.size()==2) FillHist(param.Name+"/HalfSampleTest/lepton_size_PassID", 2, 1, 7, 0, 7);
      else if(muons.size()==1&&eles.size()==0) FillHist(param.Name+"/HalfSampleTest/lepton_size_PassID", 3, 1, 7, 0, 7);
      else if(muons.size()==2&&eles.size()==0) FillHist(param.Name+"/HalfSampleTest/lepton_size_PassID", 4, 1, 7, 0, 7);
      else if(muons.size()==1&&eles.size()==1) FillHist(param.Name+"/HalfSampleTest/lepton_size_PassID", 5, 1, 7, 0, 7);
      else if(muons.size()>0&&eles.size()>0) FillHist(param.Name+"/HalfSampleTest/lepton_size_PassID", 6, 1, 7, 0, 7); //To check number of leptons

      int fake_ele = 0;
      for(unsigned int i=0; i<eles.size(); i++){
        Gen truth_lep = GetGenMatchedLepton(eles.at(i), gens);
        if(truth_lep.PID() == 0) fake_ele++;
      }
      if(fake_ele==0){
        if(muons.size()==0&&eles.size()==0) FillHist(param.Name+"/HalfSampleTest/lepton_size_PassID_NoFakeEles", 0, 1, 7, 0, 7);
        else if(muons.size()==0&&eles.size()==1) FillHist(param.Name+"/HalfSampleTest/lepton_size_PassID_NoFakeEles", 1, 1, 7, 0, 7);
        else if(muons.size()==0&&eles.size()==2) FillHist(param.Name+"/HalfSampleTest/lepton_size_PassID_NoFakeEles", 2, 1, 7, 0, 7);
        else if(muons.size()==1&&eles.size()==0) FillHist(param.Name+"/HalfSampleTest/lepton_size_PassID_NoFakeEles", 3, 1, 7, 0, 7);
        else if(muons.size()==2&&eles.size()==0) FillHist(param.Name+"/HalfSampleTest/lepton_size_PassID_NoFakeEles", 4, 1, 7, 0, 7);
        else if(muons.size()==1&&eles.size()==1) FillHist(param.Name+"/HalfSampleTest/lepton_size_PassID_NoFakeEles", 5, 1, 7, 0, 7);
        else if(muons.size()>0&&eles.size()>0) FillHist(param.Name+"/HalfSampleTest/lepton_size_PassID_NoFakeEles", 6, 1, 7, 0, 7); 
      } //To check number of leptons

      double HT = 0;
      for(unsigned int i=0; i<jets.size(); i++){
        HT += jets.at(i).Pt();
      } //HT

      double ST = MET + LT + HT; //
      double METsquaredOverST = pow(MET,2)/ST; //

      if(Nentry%2==0){ //Even : measure CFrate with pT, eta as before

        for(unsigned int i=0; i<eles.size(); i++){
          Gen truth_lep = GetGenMatchedLepton(eles.at(i), gens);
          if(GetLeptonType(eles.at(i), gens)<=0 || GetLeptonType(eles.at(i), gens)>=4) continue; // conversion veto
          if(truth_lep.PID() == 0) continue;
      
          int truth_lep_Charge;
          if(truth_lep.PID() == 11) truth_lep_Charge = -1;
          else if(truth_lep.PID() == -11) truth_lep_Charge = 1;
        
          if(abs(eles.at(i).scEta())<0.8){
            FillHist(param.Name+"/HalfSampleTest/Even/EtaRegion1_Denom", 1/eles.at(i).Pt(), 1., 40, 0., 0.04);
            if(truth_lep_Charge*eles.at(i).Charge()<0){
              //cout << "!!EtaRegion1!! truth lepton charge : " << truth_lep_Charge << ", reco lepton charge : " << eles.at(i).Charge() << endl;
              FillHist(param.Name+"/HalfSampleTest/Even/EtaRegion1_Num", 1/eles.at(i).Pt(), 1., 40, 0., 0.04);
            }
          }
          else if(0.8<=abs(eles.at(i).scEta())&&abs(eles.at(i).scEta())<1.4442){
            FillHist(param.Name+"/HalfSampleTest/Even/EtaRegion2_Denom", 1/eles.at(i).Pt(), 1., 40, 0., 0.04);
            if(truth_lep_Charge*eles.at(i).Charge()<0){
              //cout << "!!EtaRegion2!! truth lepton charge : " << truth_lep_Charge << ", reco lepton charge : " << eles.at(i).Charge() << endl;
              FillHist(param.Name+"/HalfSampleTest/Even/EtaRegion2_Num", 1/eles.at(i).Pt(), 1., 40, 0., 0.04);
            }
          }
          else if(1.556<=abs(eles.at(i).scEta())&&abs(eles.at(i).scEta())<2.5){
            FillHist(param.Name+"/HalfSampleTest/Even/EtaRegion3_Denom", 1/eles.at(i).Pt(), 1., 40, 0., 0.04);
            if(truth_lep_Charge*eles.at(i).Charge()<0){
              //cout << "!!EtaRegion3!! truth lepton charge : " << truth_lep_Charge << ", reco lepton charge : " << eles.at(i).Charge() << endl;
              FillHist(param.Name+"/HalfSampleTest/Even/EtaRegion3_Num", 1/eles.at(i).Pt(), 1., 40, 0., 0.04);
            }
          }
        }

      }

      if(Nentry%2==1){ //Odd : measure CFrate with MET, METsquaredOverST. Also apply the weight from the Even set

        for(unsigned int i=0; i<eles.size(); i++){
          Gen truth_lep = GetGenMatchedLepton(eles.at(i), gens);
          if(GetLeptonType(eles.at(i), gens)<=0 || GetLeptonType(eles.at(i), gens)>=4) continue; // conversion veto
          if(truth_lep.PID() == 0) continue;
      
          int truth_lep_Charge;
          if(truth_lep.PID() == 11) truth_lep_Charge = -1;
          else if(truth_lep.PID() == -11) truth_lep_Charge = 1;

          if(abs(eles.at(i).scEta())<0.8){
            FillHist(param.Name+"/HalfSampleTest/Odd/EtaRegion1_Denom", 1/eles.at(i).Pt(), 1., 40, 0., 0.04);
            if(truth_lep_Charge*eles.at(i).Charge()<0){
              //cout << "!!EtaRegion1!! truth lepton charge : " << truth_lep_Charge << ", reco lepton charge : " << eles.at(i).Charge() << endl;
              FillHist(param.Name+"/HalfSampleTest/Odd/EtaRegion1_Num", 1/eles.at(i).Pt(), 1., 40, 0., 0.04);
            }
          }
          else if(0.8<=abs(eles.at(i).scEta())&&abs(eles.at(i).scEta())<1.4442){
            FillHist(param.Name+"/HalfSampleTest/Odd/EtaRegion2_Denom", 1/eles.at(i).Pt(), 1., 40, 0., 0.04);
            if(truth_lep_Charge*eles.at(i).Charge()<0){
              //cout << "!!EtaRegion2!! truth lepton charge : " << truth_lep_Charge << ", reco lepton charge : " << eles.at(i).Charge() << endl;
              FillHist(param.Name+"/HalfSampleTest/Odd/EtaRegion2_Num", 1/eles.at(i).Pt(), 1., 40, 0., 0.04);
            }
          }
          else if(1.556<=abs(eles.at(i).scEta())&&abs(eles.at(i).scEta())<2.5){
            FillHist(param.Name+"/HalfSampleTest/Odd/EtaRegion3_Denom", 1/eles.at(i).Pt(), 1., 40, 0., 0.04);
            if(truth_lep_Charge*eles.at(i).Charge()<0){
              //cout << "!!EtaRegion3!! truth lepton charge : " << truth_lep_Charge << ", reco lepton charge : " << eles.at(i).Charge() << endl;
              FillHist(param.Name+"/HalfSampleTest/Odd/EtaRegion3_Num", 1/eles.at(i).Pt(), 1., 40, 0., 0.04);
            }
          }
        
          FillHist(param.Name+"/HalfSampleTest/Odd/MET_Denom", MET, 1., 100, 0., 100.);
          FillHist(param.Name+"/HalfSampleTest/Odd/METsquaredOverST_Denom", METsquaredOverST, 1., 50, 0., 50.);
          if(truth_lep_Charge*eles.at(i).Charge()<0){
            cout << "truth lepton charge : " << truth_lep_Charge << ", reco lepton charge : " << eles.at(i).Charge() << endl;
            FillHist(param.Name+"/HalfSampleTest/Odd/MET_Num", MET, 1., 100, 0., 100.);
            FillHist(param.Name+"/HalfSampleTest/Odd/METsquaredOverST_Num", METsquaredOverST, 1., 50, 0., 50.);
          }

          double weight = GetHalfSampleWeight(eles.at(i), param.Electron_Tight_ID);

          if(abs(eles.at(i).scEta())<0.8){
            FillHist(param.Name+"/HalfSampleTest/Odd/EtaRegion1_weight", 1/eles.at(i).Pt(), weight, 40, 0., 0.04);
          }
          else if(0.8<=abs(eles.at(i).scEta())&&abs(eles.at(i).scEta())<1.4442){
            FillHist(param.Name+"/HalfSampleTest/Odd/EtaRegion2_weight", 1/eles.at(i).Pt(), weight, 40, 0., 0.04);
          }
          else if(1.556<=abs(eles.at(i).scEta())&&abs(eles.at(i).scEta())<2.5){
            FillHist(param.Name+"/HalfSampleTest/Odd/EtaRegion3_weight", 1/eles.at(i).Pt(), weight, 40, 0., 0.04);
          }

          FillHist(param.Name+"/HalfSampleTest/Odd/MET_weight", MET, weight, 100, 0., 100.);
          FillHist(param.Name+"/HalfSampleTest/Odd/METsquaredOverST_weight", METsquaredOverST, weight, 50, 0., 50.);

        }

      }

    }

  }

  // Scale Factor measurement //

  else{ //if IsDATA;
    
    /*
    if(HasFlag("ScaleFactor_Old")){

      if(!PassMETFilter()) return;
      if(! (ev.PassTrigger(EleTriggerName) )) return;
      
      Particle METv = ev.GetMETVector();
  
      // CF SF ID selection //
  
      eles = SelectElectrons(AllEles, param.Electron_Tight_ID, MinPt, 2.5);

      std::sort(eles.begin(), eles.end(), PtComparing);
  
      if(eles.size() != 2) return;
      //if(eles.at(0).Pt()<lep0ptcut||eles.at(1).Pt()<lep1ptcut) return; //No need already pt min = 25
  
      Particle ZCand = eles.at(0)+eles.at(1);
      if(! (MllLeft<=ZCand.M()&&ZCand.M()<MllRight) ) return;
  
      // BB
      if(abs(eles.at(0).scEta())<1.4442&&abs(eles.at(1).scEta())<1.4442){
  
        if(eles.at(0).Charge()*eles.at(1).Charge()>0){
          FillHist(param.Name+"/ScaleFactor/BB_ZMass_SS", ZCand.M(), 1., NBin, MllLeft, MllRight);
        }
  
      }
  
      // BE
      if((abs(eles.at(0).scEta())<1.4442&&abs(eles.at(1).scEta())>=1.556)||(abs(eles.at(0).scEta())>=1.556&&abs(eles.at(1).scEta())<1.4442)){
  
        if(eles.at(0).Charge()*eles.at(1).Charge()>0){
          FillHist(param.Name+"/ScaleFactor/BE_ZMass_SS", ZCand.M(), 1., NBin, MllLeft, MllRight);
        }
  
      }
  
      // EE
      if(abs(eles.at(0).scEta())>=1.556&&abs(eles.at(1).scEta())>=1.556){
  
        if(eles.at(0).Charge()*eles.at(1).Charge()>0){
          FillHist(param.Name+"/ScaleFactor/EE_ZMass_SS", ZCand.M(), 1., NBin, MllLeft, MllRight);
        }
  
      }
  
      // Now let's shift the electrons' energy X% //
      
      vector<Electron> eles_shifted = eles; // copy the vector
      double X;
      if(DataYear==2016){
        if(param.Electron_Tight_ID=="HNTightV1") X = 1.0;
      }
      else if(DataYear==2017){
        if(param.Electron_Tight_ID=="HNTightV1") X = 1.0;
      }
      else if(DataYear==2018){
        if(param.Electron_Tight_ID=="HNTightV1") X = 0.8;
      }
      TString X_string = Form("%f",X);
      X_string = X_string(0,3)+"%";
      
      for(int j=0;j<2;j++){
        eles_shifted.at(j).SetE(eles_shifted.at(j).E()*(1-X/100));
        eles_shifted.at(j).SetPtEtaPhiE(eles_shifted.at(j).E() * TMath::Sin(eles_shifted.at(j).Theta()), eles_shifted.at(j).Eta(), eles_shifted.at(j).Phi(), eles_shifted.at(j).E());
      }
  
      Particle ZCand_shifted = eles_shifted.at(0) + eles_shifted.at(1);
      double weight_shifted = GetCFweight(eles_shifted, param.Electron_Tight_ID, false, 0.);
      double weight_shifted_SF_BWexpo_BWexpo = 0.;
      double weight_shifted_SF_BWexpo_gauspol3 = 0.;
      double weight_shifted_SF_gauspol3_BWexpo = 0.;
      double weight_shifted_SF_gauspol3_gauspol3 = 0.;
      if(DataYear==2016){
        weight_shifted_SF_BWexpo_gauspol3 = GetCFweight(eles_shifted, param.Electron_Tight_ID, true, "BW_expo", "gaus_pol3");
        weight_shifted_SF_gauspol3_gauspol3 = GetCFweight(eles_shifted, param.Electron_Tight_ID, true, "gaus_pol3", "gaus_pol3");
      }
      if(DataYear==2017){
        weight_shifted_SF_BWexpo_BWexpo = GetCFweight(eles_shifted, param.Electron_Tight_ID, true, "BW_expo", "BW_expo");
        weight_shifted_SF_BWexpo_gauspol3 = GetCFweight(eles_shifted, param.Electron_Tight_ID, true, "BW_expo", "gaus_pol3");
        weight_shifted_SF_gauspol3_BWexpo = GetCFweight(eles_shifted, param.Electron_Tight_ID, true, "gaus_pol3", "BW_expo");
        weight_shifted_SF_gauspol3_gauspol3 = GetCFweight(eles_shifted, param.Electron_Tight_ID, true, "gaus_pol3", "gaus_pol3");
      }
      if(DataYear==2018){
        weight_shifted_SF_gauspol3_gauspol3 = GetCFweight(eles_shifted, param.Electron_Tight_ID, true, "gaus_pol3", "gaus_pol3");
      }
  
      Particle METv_shifted;
      METv_shifted.SetPxPyPzE(METv.Px()+ZCand.Px()-ZCand_shifted.Px(),METv.Py()+ZCand.Py()-ZCand_shifted.Py(),0,METv.E()+ZCand.E()-ZCand_shifted.E());
  
      if(MllLeft<=ZCand_shifted.M()&&ZCand_shifted.M()<MllRight){
        if(eles.at(0).Charge()*eles.at(1).Charge()<0){
  
          // BB
          if(abs(eles_shifted.at(0).scEta())<1.4442&&abs(eles_shifted.at(1).scEta())<1.4442){
            FillHist(param.Name+"/ScaleFactor/BB_ZMass_OS_CFweighted_shifted_"+X_string, ZCand_shifted.M(), weight_shifted, NBin, MllLeft, MllRight);
            //FillHist(param.Name+"/ScaleFactor/BB_ZMass_OS_CFSFweighted_shifted_"+X_string, ZCand_shifted.M(), weight_shifted_SF, NBin, MllLeft, MllRight);
          }
      
          // BE
          if((abs(eles_shifted.at(0).scEta())<1.4442&&abs(eles_shifted.at(1).scEta())>=1.556)||(abs(eles_shifted.at(0).scEta())>=1.556&&abs(eles_shifted.at(1).scEta())<1.4442)){
            if(DataYear==2016){
              FillHist(param.Name+"/ScaleFactor/BE_ZMass_OS_CFSF_BWexpo_gauspol3_weighted_shifted_"+X_string, ZCand_shifted.M(), weight_shifted_SF_BWexpo_gauspol3, NBin, MllLeft, MllRight);
              FillHist(param.Name+"/ScaleFactor/BE_ZMass_OS_CFSF_gauspol3_gauspol3_weighted_shifted_"+X_string, ZCand_shifted.M(), weight_shifted_SF_gauspol3_gauspol3, NBin, MllLeft, MllRight);
            }
            else if(DataYear==2017){
              FillHist(param.Name+"/ScaleFactor/BE_ZMass_OS_CFSF_BWexpo_BWexpo_weighted_shifted_"+X_string, ZCand_shifted.M(), weight_shifted_SF_BWexpo_BWexpo, NBin, MllLeft, MllRight);
              FillHist(param.Name+"/ScaleFactor/BE_ZMass_OS_CFSF_BWexpo_gauspol3_weighted_shifted_"+X_string, ZCand_shifted.M(), weight_shifted_SF_BWexpo_gauspol3, NBin, MllLeft, MllRight);
              FillHist(param.Name+"/ScaleFactor/BE_ZMass_OS_CFSF_gauspol3_BWexpo_weighted_shifted_"+X_string, ZCand_shifted.M(), weight_shifted_SF_gauspol3_BWexpo, NBin, MllLeft, MllRight);
              FillHist(param.Name+"/ScaleFactor/BE_ZMass_OS_CFSF_gauspol3_gauspol3_weighted_shifted_"+X_string, ZCand_shifted.M(), weight_shifted_SF_gauspol3_gauspol3, NBin, MllLeft, MllRight);
            }
            if(DataYear==2018){
              FillHist(param.Name+"/ScaleFactor/BE_ZMass_OS_CFSF_gauspol3_gauspol3_weighted_shifted_"+X_string, ZCand_shifted.M(), weight_shifted_SF_gauspol3_gauspol3, NBin, MllLeft, MllRight);
            }
          }
      
          // EE
          if(abs(eles_shifted.at(0).scEta())>=1.556&&abs(eles_shifted.at(1).scEta())>=1.556){
            FillHist(param.Name+"/ScaleFactor/EE_ZMass_OS_CFweighted_shifted_"+X_string, ZCand_shifted.M(), weight_shifted, NBin, MllLeft, MllRight);
            //FillHist(param.Name+"/ScaleFactor/EE_ZMass_OS_CFSFweighted_shifted_"+X_string, ZCand_shifted.M(), weight_shifted_SF, NBin, MllLeft, MllRight);
          }
          
        }
      }
    }
    */

    if(HasFlag("ScaleFactor")){

      if(!PassMETFilter()) return;
      if(! (ev.PassTrigger(EleTriggerName) )) return;

      Particle METv = ev.GetMETVector();

      // CF SF ID selection //

      eles = SelectElectrons(AllEles, param.Electron_Tight_ID, MinPt, 2.5);
      eles_veto = SelectElectrons(AllEles, param.Electron_Veto_ID, MinPt, 2.5);
      vector<Jet> jets_nolepveto = SelectJets(AllJets, "HNTight", 20., 2.7); //JH : to reject bjets

      std::sort(eles.begin(), eles.end(), PtComparing);
      std::sort(eles_veto.begin(), eles_veto.end(), PtComparing);
      int ele_veto_size = eles_veto.size() - eles.size();

      std::sort(jets_nolepveto.begin(), jets_nolepveto.end(), PtComparing);
      int Nbjet_loose = 0, Nbjet_medium = 0;
      JetTagging::Parameters jtp_DeepCSV_Medium = JetTagging::Parameters(JetTagging::DeepCSV, JetTagging::Medium, JetTagging::incl, JetTagging::comb);
      for(unsigned int ij=0; ij<jets_nolepveto.size(); ij++){
        if(mcCorr->IsBTagged_2a(jtp_DeepCSV_Medium, jets_nolepveto.at(ij))) Nbjet_medium++; //JH : count Nbjet. NOTE : AN says they used CVSv2 and medium WP.
      }

      if(eles.size() != 2) return;
      if(HasFlag("HEM")){
        if( eles.at(0).isHEM()||eles.at(1).isHEM() ) return;
      }
      //if(eles.at(0).Pt()<lep0ptcut||eles.at(1).Pt()<lep1ptcut) return; //No need already pt min = 25

      double MCweight = 1.; // JH : test how DY distribution change with MC weight
      if(!IsDATA && MCSample.Contains("DYJets")){
        MCweight *= ev.MCweight();
        vector<Gen> gens = GetGens();
        for(unsigned int i=0; i<eles.size(); i++){
          if(GetLeptonType(eles.at(i), gens)<=0 || GetLeptonType(eles.at(i), gens)>=4) return; // JH : To extract MC template
        }
      }

      Particle ZCand = eles.at(0)+eles.at(1);
      if(! (MllLeft<=ZCand.M()&&ZCand.M()<MllRight) ) return;

      // BB
      if(abs(eles.at(0).scEta())<1.4442&&abs(eles.at(1).scEta())<1.4442){
        if(eles.at(0).Charge()*eles.at(1).Charge()>0){
          FillHist(param.Name+"/ScaleFactor/BB_ZMass_SS", ZCand.M(), MCweight, NBin, MllLeft, MllRight);
        }
        if(eles.at(0).Charge()*eles.at(1).Charge()<0){
          FillHist(param.Name+"/ScaleFactor/BB_ZMass_OS", ZCand.M(), MCweight, NBin, MllLeft, MllRight);
        } //JH : if you want to check OS distribution before applying the CF weight
      }
      // BE
      if((abs(eles.at(0).scEta())<1.4442&&abs(eles.at(1).scEta())>=1.556)||(abs(eles.at(0).scEta())>=1.556&&abs(eles.at(1).scEta())<1.4442)){
        if(eles.at(0).Charge()*eles.at(1).Charge()>0){
          FillHist(param.Name+"/ScaleFactor/BE_ZMass_SS", ZCand.M(), MCweight, NBin, MllLeft, MllRight);
        }
        if(eles.at(0).Charge()*eles.at(1).Charge()<0){
          FillHist(param.Name+"/ScaleFactor/BE_ZMass_OS", ZCand.M(), MCweight, NBin, MllLeft, MllRight);
        }
      }
      // EE
      if(abs(eles.at(0).scEta())>=1.556&&abs(eles.at(1).scEta())>=1.556){
        if(eles.at(0).Charge()*eles.at(1).Charge()>0){
          FillHist(param.Name+"/ScaleFactor/EE_ZMass_SS", ZCand.M(), MCweight, NBin, MllLeft, MllRight);
        }
        if(eles.at(0).Charge()*eles.at(1).Charge()<0){
          FillHist(param.Name+"/ScaleFactor/EE_ZMass_OS", ZCand.M(), MCweight, NBin, MllLeft, MllRight);
        }
      }

      /*
      if(METv.Pt() < 50){
        // BB
        if(abs(eles.at(0).scEta())<1.4442&&abs(eles.at(1).scEta())<1.4442){
          if(eles.at(0).Charge()*eles.at(1).Charge()>0){
            FillHist(param.Name+"/ScaleFactor/BB_ZMass_SS_MET50", ZCand.M(), MCweight, NBin, MllLeft, MllRight);
          }
          if(eles.at(0).Charge()*eles.at(1).Charge()<0){
            FillHist(param.Name+"/ScaleFactor/BB_ZMass_OS_MET50", ZCand.M(), MCweight, NBin, MllLeft, MllRight);
          }
        }
        // BE
        if((abs(eles.at(0).scEta())<1.4442&&abs(eles.at(1).scEta())>=1.556)||(abs(eles.at(0).scEta())>=1.556&&abs(eles.at(1).scEta())<1.4442)){
          if(eles.at(0).Charge()*eles.at(1).Charge()>0){
            FillHist(param.Name+"/ScaleFactor/BE_ZMass_SS_MET50", ZCand.M(), MCweight, NBin, MllLeft, MllRight);
          }
          if(eles.at(0).Charge()*eles.at(1).Charge()<0){
            FillHist(param.Name+"/ScaleFactor/BE_ZMass_OS_MET50", ZCand.M(), MCweight, NBin, MllLeft, MllRight);
          }
        }
        // EE
        if(abs(eles.at(0).scEta())>=1.556&&abs(eles.at(1).scEta())>=1.556){
          if(eles.at(0).Charge()*eles.at(1).Charge()>0){
            FillHist(param.Name+"/ScaleFactor/EE_ZMass_SS_MET50", ZCand.M(), MCweight, NBin, MllLeft, MllRight);
          }
          if(eles.at(0).Charge()*eles.at(1).Charge()<0){
            FillHist(param.Name+"/ScaleFactor/EE_ZMass_OS_MET50", ZCand.M(), MCweight, NBin, MllLeft, MllRight);
          }
        }
      }

      if(nPV < 40){
        // BB
        if(abs(eles.at(0).scEta())<1.4442&&abs(eles.at(1).scEta())<1.4442){
          if(eles.at(0).Charge()*eles.at(1).Charge()>0){
            FillHist(param.Name+"/ScaleFactor/BB_ZMass_SS_nPV40", ZCand.M(), MCweight, NBin, MllLeft, MllRight);
          }
          if(eles.at(0).Charge()*eles.at(1).Charge()<0){
            FillHist(param.Name+"/ScaleFactor/BB_ZMass_OS_nPV40", ZCand.M(), MCweight, NBin, MllLeft, MllRight);
          }
        }
        // BE
        if((abs(eles.at(0).scEta())<1.4442&&abs(eles.at(1).scEta())>=1.556)||(abs(eles.at(0).scEta())>=1.556&&abs(eles.at(1).scEta())<1.4442)){
          if(eles.at(0).Charge()*eles.at(1).Charge()>0){
            FillHist(param.Name+"/ScaleFactor/BE_ZMass_SS_nPV40", ZCand.M(), MCweight, NBin, MllLeft, MllRight);
          }
          if(eles.at(0).Charge()*eles.at(1).Charge()<0){
            FillHist(param.Name+"/ScaleFactor/BE_ZMass_OS_nPV40", ZCand.M(), MCweight, NBin, MllLeft, MllRight);
          }
        }
        // EE
        if(abs(eles.at(0).scEta())>=1.556&&abs(eles.at(1).scEta())>=1.556){
          if(eles.at(0).Charge()*eles.at(1).Charge()>0){
            FillHist(param.Name+"/ScaleFactor/EE_ZMass_SS_nPV40", ZCand.M(), MCweight, NBin, MllLeft, MllRight);
          }
          if(eles.at(0).Charge()*eles.at(1).Charge()<0){
            FillHist(param.Name+"/ScaleFactor/EE_ZMass_OS_nPV40", ZCand.M(), MCweight, NBin, MllLeft, MllRight);
          }
        }
      }

      if(METv.Pt() < 50 && nPV < 40){
        // BB
        if(abs(eles.at(0).scEta())<1.4442&&abs(eles.at(1).scEta())<1.4442){
          if(eles.at(0).Charge()*eles.at(1).Charge()>0){
            FillHist(param.Name+"/ScaleFactor/BB_ZMass_SS_MET50_nPV40", ZCand.M(), MCweight, NBin, MllLeft, MllRight);
          }
          if(eles.at(0).Charge()*eles.at(1).Charge()<0){
            FillHist(param.Name+"/ScaleFactor/BB_ZMass_OS_MET50_nPV40", ZCand.M(), MCweight, NBin, MllLeft, MllRight);
          }
        }
        // BE
        if((abs(eles.at(0).scEta())<1.4442&&abs(eles.at(1).scEta())>=1.556)||(abs(eles.at(0).scEta())>=1.556&&abs(eles.at(1).scEta())<1.4442)){
          if(eles.at(0).Charge()*eles.at(1).Charge()>0){
            FillHist(param.Name+"/ScaleFactor/BE_ZMass_SS_MET50_nPV40", ZCand.M(), MCweight, NBin, MllLeft, MllRight);
          }
          if(eles.at(0).Charge()*eles.at(1).Charge()<0){
            FillHist(param.Name+"/ScaleFactor/BE_ZMass_OS_MET50_nPV40", ZCand.M(), MCweight, NBin, MllLeft, MllRight);
          }
        }
        // EE
        if(abs(eles.at(0).scEta())>=1.556&&abs(eles.at(1).scEta())>=1.556){
          if(eles.at(0).Charge()*eles.at(1).Charge()>0){
            FillHist(param.Name+"/ScaleFactor/EE_ZMass_SS_MET50_nPV40", ZCand.M(), MCweight, NBin, MllLeft, MllRight);
          }
          if(eles.at(0).Charge()*eles.at(1).Charge()<0){
            FillHist(param.Name+"/ScaleFactor/EE_ZMass_OS_MET50_nPV40", ZCand.M(), MCweight, NBin, MllLeft, MllRight);
          }
        }
      }

      if(ele_veto_size == 0){
        // BB
        if(abs(eles.at(0).scEta())<1.4442&&abs(eles.at(1).scEta())<1.4442){
          if(eles.at(0).Charge()*eles.at(1).Charge()>0){
            FillHist(param.Name+"/ScaleFactor/BB_ZMass_SS_l3veto", ZCand.M(), MCweight, NBin, MllLeft, MllRight);
          }
          if(eles.at(0).Charge()*eles.at(1).Charge()<0){
            FillHist(param.Name+"/ScaleFactor/BB_ZMass_OS_l3veto", ZCand.M(), MCweight, NBin, MllLeft, MllRight);
          }
        }
        // BE
        if((abs(eles.at(0).scEta())<1.4442&&abs(eles.at(1).scEta())>=1.556)||(abs(eles.at(0).scEta())>=1.556&&abs(eles.at(1).scEta())<1.4442)){
          if(eles.at(0).Charge()*eles.at(1).Charge()>0){
            FillHist(param.Name+"/ScaleFactor/BE_ZMass_SS_l3veto", ZCand.M(), MCweight, NBin, MllLeft, MllRight);
          }
          if(eles.at(0).Charge()*eles.at(1).Charge()<0){
            FillHist(param.Name+"/ScaleFactor/BE_ZMass_OS_l3veto", ZCand.M(), MCweight, NBin, MllLeft, MllRight);
          }
        }
        // EE
        if(abs(eles.at(0).scEta())>=1.556&&abs(eles.at(1).scEta())>=1.556){
          if(eles.at(0).Charge()*eles.at(1).Charge()>0){
            FillHist(param.Name+"/ScaleFactor/EE_ZMass_SS_l3veto", ZCand.M(), MCweight, NBin, MllLeft, MllRight);
          }
          if(eles.at(0).Charge()*eles.at(1).Charge()<0){
            FillHist(param.Name+"/ScaleFactor/EE_ZMass_OS_l3veto", ZCand.M(), MCweight, NBin, MllLeft, MllRight);
          }
        }
      }

      if(Nbjet_medium == 0){
        // BB
        if(abs(eles.at(0).scEta())<1.4442&&abs(eles.at(1).scEta())<1.4442){
          if(eles.at(0).Charge()*eles.at(1).Charge()>0){
            FillHist(param.Name+"/ScaleFactor/BB_ZMass_SS_bveto", ZCand.M(), MCweight, NBin, MllLeft, MllRight);
          }
          if(eles.at(0).Charge()*eles.at(1).Charge()<0){
            FillHist(param.Name+"/ScaleFactor/BB_ZMass_OS_bveto", ZCand.M(), MCweight, NBin, MllLeft, MllRight);
          }
        }
        // BE
        if((abs(eles.at(0).scEta())<1.4442&&abs(eles.at(1).scEta())>=1.556)||(abs(eles.at(0).scEta())>=1.556&&abs(eles.at(1).scEta())<1.4442)){
          if(eles.at(0).Charge()*eles.at(1).Charge()>0){
            FillHist(param.Name+"/ScaleFactor/BE_ZMass_SS_bveto", ZCand.M(), MCweight, NBin, MllLeft, MllRight);
          }
          if(eles.at(0).Charge()*eles.at(1).Charge()<0){
            FillHist(param.Name+"/ScaleFactor/BE_ZMass_OS_bveto", ZCand.M(), MCweight, NBin, MllLeft, MllRight);
          }
        }
        // EE
        if(abs(eles.at(0).scEta())>=1.556&&abs(eles.at(1).scEta())>=1.556){
          if(eles.at(0).Charge()*eles.at(1).Charge()>0){
            FillHist(param.Name+"/ScaleFactor/EE_ZMass_SS_bveto", ZCand.M(), MCweight, NBin, MllLeft, MllRight);
          }
          if(eles.at(0).Charge()*eles.at(1).Charge()<0){
            FillHist(param.Name+"/ScaleFactor/EE_ZMass_OS_bveto", ZCand.M(), MCweight, NBin, MllLeft, MllRight);
          }
        }
      }
      */

      // Now let's shift the electrons' energy by X% //

      vector<Electron> eles_shifted = eles; // copy the vector
      double X;
      if(DataYear==2016){
        if(param.Electron_Tight_ID=="HNTightV1") X = 1.0;
      }
      else if(DataYear==2017){
        if(param.Electron_Tight_ID=="HNTightV1") X = 1.0;
      }
      else if(DataYear==2018){
        if(param.Electron_Tight_ID=="HNTightV1") X = 0.8;
      }
      TString X_string = Form("%f",X);
      X_string = X_string(0,3)+"%";

      for(int j=0;j<2;j++){
        eles_shifted.at(j).SetE(eles_shifted.at(j).E()*(1-X/100));
        eles_shifted.at(j).SetPtEtaPhiE(eles_shifted.at(j).E() * TMath::Sin(eles_shifted.at(j).Theta()), eles_shifted.at(j).Eta(), eles_shifted.at(j).Phi(), eles_shifted.at(j).E());
      }

      Particle ZCand_shifted = eles_shifted.at(0) + eles_shifted.at(1);
      double weight_shifted = GetCFweight(eles_shifted, param.Electron_Tight_ID, false, 0.);
      double weight_shifted_SF = GetCFweight(eles_shifted, param.Electron_Tight_ID, true, 0.);
      weight_shifted *= MCweight;
      weight_shifted_SF *= MCweight;

      Particle METv_shifted;
      METv_shifted.SetPxPyPzE(METv.Px()+ZCand.Px()-ZCand_shifted.Px(),METv.Py()+ZCand.Py()-ZCand_shifted.Py(),0,METv.E()+ZCand.E()-ZCand_shifted.E());

      if(MllLeft<=ZCand_shifted.M()&&ZCand_shifted.M()<MllRight){
        if(eles.at(0).Charge()*eles.at(1).Charge()<0){

          // BB
          if(abs(eles_shifted.at(0).scEta())<1.4442&&abs(eles_shifted.at(1).scEta())<1.4442){
            FillHist(param.Name+"/ScaleFactor/BB_ZMass_OS_CFweighted_shifted_"+X_string, ZCand_shifted.M(), weight_shifted, NBin, MllLeft, MllRight);
            //FillHist(param.Name+"/ScaleFactor/BB_ZMass_OS_CFSFweighted_shifted_"+X_string, ZCand_shifted.M(), weight_shifted_SF, NBin, MllLeft, MllRight);
          }

          // BE
          if((abs(eles_shifted.at(0).scEta())<1.4442&&abs(eles_shifted.at(1).scEta())>=1.556)||(abs(eles_shifted.at(0).scEta())>=1.556&&abs(eles_shifted.at(1).scEta())<1.4442)){
            FillHist(param.Name+"/ScaleFactor/BE_ZMass_OS_CFweighted_shifted_"+X_string, ZCand_shifted.M(), weight_shifted, NBin, MllLeft, MllRight);
            FillHist(param.Name+"/ScaleFactor/BE_ZMass_OS_CFSFweighted_shifted_"+X_string, ZCand_shifted.M(), weight_shifted_SF, NBin, MllLeft, MllRight);
          }

          // EE
          if(abs(eles_shifted.at(0).scEta())>=1.556&&abs(eles_shifted.at(1).scEta())>=1.556){
            FillHist(param.Name+"/ScaleFactor/EE_ZMass_OS_CFweighted_shifted_"+X_string, ZCand_shifted.M(), weight_shifted, NBin, MllLeft, MllRight);
            //FillHist(param.Name+"/ScaleFactor/EE_ZMass_OS_CFSFweighted_shifted_"+X_string, ZCand_shifted.M(), weight_shifted_SF, NBin, MllLeft, MllRight);
          }

        }
      }
    }
  }
}
