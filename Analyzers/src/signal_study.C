#include "signal_study.h"

void signal_study::initializeAnalyzer(){

}

void signal_study::executeEvent(){

    allMuons = GetAllMuons();
    allJets = GetAllJets();
    allFatJets = puppiCorr->Correct(GetAllFatJets());

    AnalyzerParameter param;

    executeEventFromParameter(param);

}

void signal_study::executeEventFromParameter(AnalyzerParameter param){

    double weight = MCweight(true, true)/abs(MCweight(true, true));

    std::vector<Gen> gens = GetGens();

    std::vector<Particle> genjets;
    for (unsigned int i =0; i < gens.size(); i++){
        Gen gen = gens.at(i);

        int status = gen.Status();
        if (status != 23) continue;

        int pdgid = gen.PID();
        int motherid = gens.at(gen.MotherIndex()).PID();
        if (abs(pdgid) < 6){
            if (abs(motherid) == 23 || abs(motherid) == 24 || abs(motherid) == 25){
                genjets.push_back(gen);
            }
        }
    }

    if(genjets.size() == 2){
        FillHist("GenStudy_deltarjj", genjets.at(0).DeltaR(genjets.at(1)), weight, 250, 0., 5.);
        FillHist("GenStudy_nevents", 0, weight, 1, 0., 1.);
    }
    else{
        FillHist("GenStudy_not2jets", 0, weight, 1, 0., 1.);
    }


//DataFormats/src/Gen.C:  cout << "(Index, PID, Status, MotherIndex, Pt, Eta, Phi, M) = " << Index() << "\t" << PID() << "\t" << Status() << "\t" << MotheIndex() << "\t" << Pt() << "\t" << Eta() << "\t" << Phi() << "\t" << M() << endl;


    std::vector<Muon> muonsNoIso = SelectMuons(allMuons, "POGTight", 40., 2.1);
    std::vector<Muon> muons;
    for (unsigned int i=0; i < muonsNoIso.size(); i++){
        if (muonsNoIso.at(i).RelIso() < 0.15){
            muons.push_back(muonsNoIso.at(i));
        }
    }

    std::vector<Electron> null; null.clear();

    std::vector<FatJet> fatjetsNoSDMass = SelectFatJets(allFatJets, "tight", 200., 2.1);
    std::vector<FatJet> fatjets;
    for (unsigned int i=0; i < fatjetsNoSDMass.size(); i++){
        FatJet fatjet = fatjetsNoSDMass.at(i);
        if (fatjet.SDMass() > 50.0){
            fatjets.push_back(fatjet);
        }
    }
    std::sort(fatjets.begin(), fatjets.end(), PtComparing);

    std::vector<FatJet> fatjetsCleaned = FatJetsVetoLeptonInside(fatjets, null, muons, 0.4);

    std::vector<Jet> jets = SelectJets(allJets, "tightLepVeto" , 30.0, 2.4);
    std::sort(jets.begin(), jets.end(), PtComparing);

    std::vector<Jet> jetsFatJetCleaned = JetsAwayFromFatJet(jets, fatjetsCleaned, 1.2);
    std::vector<Jet> jetsLeptonCleaned = JetsVetoLeptonInside(jets, null, muons, 0.4);
    std::vector<Jet> jetsCleaned = JetsVetoLeptonInside(JetsAwayFromFatJet(jets, fatjetsCleaned, 1.2), null, muons, 0.4);

    if (muons.size() == 0) return;

    FillHist("BeforeCut_nevents", 0, weight, 1, 0., 1.);

    double recoSecBosonMass = 0.;

    if (jetsLeptonCleaned.size() >= 2){
        recoSecBosonMass = (jetsLeptonCleaned.at(0) + jetsLeptonCleaned.at(1)).M();
        FillHist("OnlyResolved_recosecbosonmass", recoSecBosonMass, weight, 200, 0., 200.);
        FillHist("OnlyResolved_nevents", 0, weight, 1, 0., 1.);
        if (recoSecBosonMass > 65. && recoSecBosonMass < 145.){
            FillHist("OnlyResolvedMassCut_recosecbosonmass", recoSecBosonMass, weight, 200, 0., 200.);
            FillHist("OnlyResolvedMassCut_nevents", 0, weight, 1, 0., 1.);
        }

    }

    if (fatjetsCleaned.size() >= 1){
        recoSecBosonMass = fatjetsCleaned.at(0).SDMass();
        FillHist("CombinedMerged_recosecbosonmass", recoSecBosonMass, weight, 200, 0., 200.);
        FillHist("CombinedMerged_nevents", 0, weight, 1, 0., 1.);
        if (recoSecBosonMass > 65. && recoSecBosonMass < 145.){
            FillHist("CombinedMergedMassCut_recosecbosonmass", recoSecBosonMass, weight, 200, 0., 200.);
            FillHist("CombinedMergedMassCut_nevents", 0, weight, 1, 0., 1.);
        }
    }
    else if (jetsCleaned.size() >= 2){
        recoSecBosonMass = (jetsCleaned.at(0) + jetsCleaned.at(1)).M();
        FillHist("CombinedResolved_recosecbosonmass", recoSecBosonMass, weight, 200, 0., 200.);
        FillHist("CombinedResolved_nevents", 0, weight, 1, 0., 1.);
        if (recoSecBosonMass > 65. && recoSecBosonMass < 145.){
            FillHist("CombinedResolvedMassCut_recosecbosonmass", recoSecBosonMass, weight, 200, 0., 200.);
            FillHist("CombinedResolvedMassCut_nevents", 0, weight, 1, 0., 1.);
        }
    }

}

signal_study::signal_study(){

}

signal_study::~signal_study(){

}


