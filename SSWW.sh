#!/bin/bash

### Test ###
#python python/SKFlat.py -a SSWW -e 2016a -i DoubleMuon:B_ver2 -n 50 --skim SkimTree_Dilepton --userflags jcln_inv,fatjet_veto --batchname auto &
#python python/SKFlat.py -a SSWW -e 2016a -i SSWWTypeI_NLO_SF_M1500 -n 50 --userflags jcln_inv,fatjet_veto --batchname auto &



### SSWW selections (CR, SR) ###
#! 2016a !#
#python python/SKFlat.py -a SSWW -e 2016a -l submitList/2016a_DoubleMuon.txt -n 50 --skim SkimTree_Dilepton --userflags jcln_inv,fatjet_veto --batchname auto &
#python python/SKFlat.py -a SSWW -e 2016a -l submitList/2016a_DoubleMuon.txt -n 50 --skim SkimTree_Dilepton --userflags jcln_inv,fatjet_veto,RunFake --batchname auto &
#python python/SKFlat.py -a SSWW -e 2016a -l submitList/SSWW_2016_HNMultiLep.txt -n 50 --skim SkimTree_HNMultiLep --userflags jcln_inv,fatjet_veto --batchname auto &

#! 2016b !#
#python python/SKFlat.py -a SSWW -e 2016b -l submitList/2016b_DoubleMuon_FtoG.txt -n 50 --skim SkimTree_Dilepton --userflags jcln_inv,fatjet_veto --batchname auto &
#python python/SKFlat.py -a SSWW -e 2016b -l submitList/2016b_DoubleMuon_H.txt -n 50 --skim SkimTree_Dilepton --userflags jcln_inv,fatjet_veto,PeriodH --batchname auto &
python python/SKFlat.py -a SSWW -e 2016b -l submitList/2016b_DoubleMuon_FtoG.txt -n 50 --skim SkimTree_Dilepton --userflags jcln_inv,fatjet_veto,RunFake --batchname auto &
python python/SKFlat.py -a SSWW -e 2016b -l submitList/2016b_DoubleMuon_H.txt -n 50 --skim SkimTree_Dilepton --userflags jcln_inv,fatjet_veto,RunFake,PeriodH --batchname auto &
python python/SKFlat.py -a SSWW -e 2016b -l submitList/SSWW_2016_HNMultiLep.txt -n 50 --skim SkimTree_HNMultiLep --userflags jcln_inv,fatjet_veto --batchname auto &

#! 2017 !#
python python/SKFlat.py -a SSWW -e 2017 -l submitList/2017_DoubleMuon.txt -n 50 --skim SkimTree_Dilepton --userflags jcln_inv,fatjet_veto --batchname auto &
python python/SKFlat.py -a SSWW -e 2017 -l submitList/2017_DoubleMuon.txt -n 50 --skim SkimTree_Dilepton --userflags jcln_inv,fatjet_veto,RunFake --batchname auto &
python python/SKFlat.py -a SSWW -e 2017 -l submitList/SSWW_2017_HNMultiLep.txt -n 50 --skim SkimTree_HNMultiLep --userflags jcln_inv,fatjet_veto --batchname auto &

#! 2018 !#
python python/SKFlat.py -a SSWW -e 2018 -l submitList/2018_DoubleMuon.txt -n 50 --skim SkimTree_Dilepton --userflags jcln_inv,fatjet_veto --batchname auto &
python python/SKFlat.py -a SSWW -e 2018 -l submitList/2018_DoubleMuon.txt -n 50 --skim SkimTree_Dilepton --userflags jcln_inv,fatjet_veto,RunFake --batchname auto &
python python/SKFlat.py -a SSWW -e 2018 -l submitList/SSWW_2018_HNMultiLep.txt -n 50 --skim SkimTree_HNMultiLep --userflags jcln_inv,fatjet_veto --batchname auto &



### SM Control Regions ###
##!! 2016 !!##
#! data !#
#python python/SKFlat.py -a Control -e 2016a -l submitList/2016a_DoubleMuon.txt -n 50 --skim SkimTree_Dilepton --batchname auto &
#python python/SKFlat.py -a Control -e 2016b -l submitList/2016b_DoubleMuon_FtoG.txt -n 50 --skim SkimTree_Dilepton --batchname auto &
#python python/SKFlat.py -a Control -e 2016b -l submitList/2016b_DoubleMuon_H.txt -n 50 --skim SkimTree_Dilepton --userflags PeriodH --batchname auto &
#! fake background !#
#python python/SKFlat.py -a Control -e 2016a -l submitList/2016a_DoubleMuon.txt -n 50 --skim SkimTree_Dilepton --userflags RunFake --batchname auto &
#python python/SKFlat.py -a Control -e 2016b -l submitList/2016b_DoubleMuon_FtoG.txt -n 50 --skim SkimTree_Dilepton --userflags RunFake --batchname auto &
#python python/SKFlat.py -a Control -e 2016b -l submitList/2016b_DoubleMuon_H.txt -n 50 --skim SkimTree_Dilepton --userflags RunFake,PeriodH --batchname auto &
#! SM background !#
#python python/SKFlat.py -a Control -e 2016a -l submitList/Control_2016_HNMultiLep.txt -n 80 --skim SkimTree_HNMultiLep --batchname auto &
#python python/SKFlat.py -a Control -e 2016b -l submitList/Control_2016_HNMultiLep.txt -n 80 --skim SkimTree_HNMultiLep --batchname auto &

##!! 2017 !!##
#python python/SKFlat.py -a Control -e 2017 -l submitList/2017_DoubleMuon.txt -n 50 --skim SkimTree_Dilepton --batchname auto &
#python python/SKFlat.py -a Control -e 2017 -l submitList/2017_DoubleMuon.txt -n 50 --skim SkimTree_Dilepton --userflags RunFake --batchname auto &
#python python/SKFlat.py -a Control -e 2017 -l submitList/Control_2017_HNMultiLep.txt -n 80 --batchname auto &
#JH : Don't use HNMultiLep if to see DY, TT CR

##!! 2018 !!##
#python python/SKFlat.py -a Control -e 2018 -l submitList/2018_DoubleMuon.txt -n 50 --skim SkimTree_Dilepton --batchname auto &
#python python/SKFlat.py -a Control -e 2018 -l submitList/2018_DoubleMuon.txt -n 50 --skim SkimTree_Dilepton --userflags RunFake --batchname auto &
#python python/SKFlat.py -a Control -e 2018 -l submitList/Control_2018_HNMultiLep.txt -n 80 --batchname auto &
#JH : Don't use HNMultiLep if to see DY, TT CR



### Control Regions ###

##!! 2016 !!##
#! data !#
#python python/SKFlat.py -a Signal -e 2016a -l submitList/2016a_DoubleMuon.txt -n 50 --skim SkimTree_Dilepton --batchname auto &
#python python/SKFlat.py -a Signal -e 2016b -l submitList/2016b_DoubleMuon_FtoG.txt -n 50 --skim SkimTree_Dilepton --batchname auto &
#python python/SKFlat.py -a Signal -e 2016b -l submitList/2016b_DoubleMuon_H.txt -n 50 --skim SkimTree_Dilepton --userflags PeriodH --batchname auto &

#! fake background !#
#python python/SKFlat.py -a Signal -e 2016a -l submitList/2016a_DoubleMuon.txt -n 50 --skim SkimTree_Dilepton --userflags RunFake --batchname auto &
#python python/SKFlat.py -a Signal -e 2016b -l submitList/2016b_DoubleMuon_FtoG.txt -n 50 --skim SkimTree_Dilepton --userflags RunFake --batchname auto &
#python python/SKFlat.py -a Signal -e 2016b -l submitList/2016b_DoubleMuon_H.txt -n 50 --skim SkimTree_Dilepton --userflags RunFake,PeriodH --batchname auto &

#! SM background !#
#python python/SKFlat.py -a Signal -e 2016a -l submitList/Signal_2016_HNMultiLep.txt -n 80 --skim SkimTree_HNMultiLep --batchname auto &
#python python/SKFlat.py -a Signal -e 2016b -l submitList/Signal_2016_HNMultiLep.txt -n 80 --skim SkimTree_HNMultiLep --batchname auto &

##!! 2017 !!##
#! data !#
#python python/SKFlat.py -a Signal -e 2017 -l submitList/2017_DoubleMuon.txt -n 50 --skim SkimTree_Dilepton --batchname auto &
#! fake background !#
#python python/SKFlat.py -a Signal -e 2017 -l submitList/2017_DoubleMuon.txt -n 50 --skim SkimTree_Dilepton --userflags RunFake --batchname auto &
#! SM background !#
#python python/SKFlat.py -a Signal -e 2017 -l submitList/Signal_2017_HNMultiLep.txt -n 80 --skim SkimTree_HNMultiLep --batchname auto &

##!! 2018 !!##
#! data !#
#python python/SKFlat.py -a Signal -e 2018 -l submitList/2018_DoubleMuon.txt -n 50 --skim SkimTree_Dilepton --batchname auto &
#! fake background !#
#python python/SKFlat.py -a Signal -e 2018 -l submitList/2018_DoubleMuon.txt -n 50 --skim SkimTree_Dilepton --userflags RunFake --batchname auto &
#! SM background !#
#python python/SKFlat.py -a Signal -e 2018 -l submitList/Signal_2018_HNMultiLep.txt -n 80 --skim SkimTree_HNMultiLep --batchname auto &



### Fake measurement ###
#! 2016a !#
#python python/SKFlat.py -a Fake -e 2016a -l submitList/2016a_DoubleMuon.txt --userflags FR,Norm -n 50 --batchname auto &
#python python/SKFlat.py -a Fake -e 2016a -l submitList/2016a_DoubleEG.txt --userflags FR,Norm -n 50 --batchname auto &
#python python/SKFlat.py -a Fake -e 2016a -l submitList/Fake_Norm_MC_2016.txt --userflags FR,Norm -n 50 --batchname auto &

#! 2016b !#
#python python/SKFlat.py -a Fake -e 2016b -l submitList/2016b_DoubleMuon.txt --userflags FR,Norm -n 50 --batchname auto &
#python python/SKFlat.py -a Fake -e 2016b -l submitList/2016b_DoubleEG.txt --userflags FR,Norm -n 50 --batchname auto &
#python python/SKFlat.py -a Fake -e 2016b -l submitList/Fake_Norm_MC_2016.txt --userflags FR,Norm -n 50 --batchname auto &

#! 2017 !#
#python python/SKFlat.py -a Fake -e 2017 -l submitList/2017_SingleMuon.txt --userflags FR,Norm -n 50 --batchname auto &
#python python/SKFlat.py -a Fake -e 2017 -l submitList/2017_DoubleMuon.txt --userflags FR,Norm -n 50 --batchname auto &
#python python/SKFlat.py -a Fake -e 2017 -l submitList/2017_DoubleEG.txt --userflags FR,Norm -n 50 --batchname auto &
#python python/SKFlat.py -a Fake -e 2017 -l submitList/Fake_Norm_MC_2017.txt --userflags FR,Norm -n 50 --batchname auto &

#! 2018 !#
#python python/SKFlat.py -a Fake -e 2018 -l submitList/2018_SingleMuon.txt --userflags FR,Norm -n 50 --batchname auto &
#python python/SKFlat.py -a Fake -e 2018 -l submitList/2018_DoubleMuon.txt --userflags FR,Norm -n 50 --batchname auto &
#python python/SKFlat.py -a Fake -e 2018 -l submitList/2018_DoubleEG.txt --userflags FR,Norm -n 50 --batchname auto &
#python python/SKFlat.py -a Fake -e 2018 -l submitList/Fake_Norm_MC_2018.txt --userflags FR,Norm -n 50 --batchname auto &


#######################################################################################################################################################

### Test ###
#python python/SKFlat.py -a SSWW -y 2016 -i DoubleMuon:B_ver2 -n 50 --skim SkimTree_Dilepton --batchname auto &

### CF ###
#python python/SKFlat.py -a Signal -y 2016 -l submitList/2016_DoubleEG_BtoH.txt -n 80 --skim SkimTree_Dilepton --userflags RunCF &

### Fake ###
#python python/SKFlat.py -a Signal -y 2016 -l submitList/2016_DoubleMuon_BtoG.txt -n 80 --skim SkimTree_Dilepton --userflags RunFake &
#python python/SKFlat.py -a Signal -y 2016 -l submitList/2016_DoubleEG_BtoH.txt -n 80 --skim SkimTree_Dilepton --userflags RunFake &
#python python/SKFlat.py -a Signal -y 2016 -l submitList/2016_MuonEG_BtoG.txt -n 80 --skim SkimTree_Dilepton --userflags RunFake &
#python python/SKFlat.py -a Signal_2016H -y 2016 -l submitList/2016_periodH.txt -n 80 --skim SkimTree_Dilepton --userflags RunFake &

#python python/SKFlat.py -a SSWW -y 2016 -l submitList/2016_DoubleMuon_BtoH.txt -n 50 --skim SkimTree_Dilepton --userflags RunFake --batchname auto &

#python python/SKFlat.py -a SSWW -y 2016 -l submitList/2016_DoubleMuon_BtoG.txt -n 50 --skim SkimTree_Dilepton --userflags jcln_inv,fatjet_veto,RunFake --batchname auto &
#python python/SKFlat.py -a SSWW -y 2016 -l submitList/2016_DoubleMuon_H.txt -n 50 --skim SkimTree_Dilepton --userflags jcln_inv,fatjet_veto,RunFake,PeriodH --batchname auto &

#python python/SKFlat.py -a Signal -y 2016 -l submitList/2016_DoubleMuon_BtoG.txt -n 50 --skim SkimTree_Dilepton --userflags RunFake --batchname auto &
#python python/SKFlat.py -a Signal -y 2016 -l submitList/2016_DoubleMuon_H.txt -n 50 --skim SkimTree_Dilepton --userflags RunFake,PeriodH --batchname auto &
#python python/SKFlat.py -a Signal -y 2016 -l submitList/2016_DoubleMuon_BtoG.txt -n 50 --skim SkimTree_Dilepton --userflags RunFake,FR_ex --batchname auto &
#python python/SKFlat.py -a Signal -y 2016 -l submitList/2016_DoubleMuon_H.txt -n 50 --skim SkimTree_Dilepton --userflags RunFake,PeriodH,FR_ex --batchname auto &

#python python/SKFlat.py -a Control -y 2016 -l submitList/2016_DoubleMuon_BtoG.txt -n 50 --skim SkimTree_Dilepton --userflags RunFake --batchname auto &
#python python/SKFlat.py -a Control -y 2016 -l submitList/2016_DoubleMuon_H.txt -n 50 --skim SkimTree_Dilepton --userflags RunFake,PeriodH --batchname auto &
#python python/SKFlat.py -a Control -y 2016 -l submitList/2016_DoubleMuon_BtoG.txt -n 50 --skim SkimTree_Dilepton --userflags RunFake,FR_ex --batchname auto &
#python python/SKFlat.py -a Control -y 2016 -l submitList/2016_DoubleMuon_H.txt -n 50 --skim SkimTree_Dilepton --userflags RunFake,PeriodH,FR_ex --batchname auto &

### DATA ###
#python python/SKFlat.py -a SSWW -y 2016 -l submitList/2016_DoubleMuon_BtoH.txt -n 50 --skim SkimTree_Dilepton --batchname auto &
#python python/SKFlat.py -a SSWW -y 2017 -l submitList/2017_DoubleMuon.txt -n 50 --skim SkimTree_Dilepton --batchname auto &
#python python/SKFlat.py -a SSWW -y 2018 -l submitList/2018_DoubleMuon.txt -n 50 --skim SkimTree_Dilepton --batchname auto &

#python python/SKFlat.py -a SSWW -y 2016 -l submitList/2016_DoubleMuon_BtoH.txt -n 50 --skim SkimTree_Dilepton --batchname auto &
#python python/SKFlat.py -a SSWW -y 2016 -l submitList/2016_DoubleMuon_BtoG.txt -n 50 --skim SkimTree_Dilepton --userflags jcln_inv,fatjet_veto --batchname auto &
#python python/SKFlat.py -a SSWW -y 2016 -l submitList/2016_DoubleMuon_H.txt -n 50 --skim SkimTree_Dilepton --userflags jcln_inv,fatjet_veto,PeriodH --batchname auto &

#python python/SKFlat.py -a Signal -y 2016 -l submitList/2016_DoubleMuon_BtoG.txt -n 50 --skim SkimTree_Dilepton --batchname auto &
#python python/SKFlat.py -a Signal -y 2016 -l submitList/2016_DoubleMuon_H.txt -n 50 --skim SkimTree_Dilepton --userflags PeriodH --batchname auto &

#python python/SKFlat.py -a Control -y 2016 -l submitList/2016_DoubleMuon_BtoG.txt -n 50 --skim SkimTree_Dilepton --batchname auto &
#python python/SKFlat.py -a Control -y 2016 -l submitList/2016_DoubleMuon_H.txt -n 50 --skim SkimTree_Dilepton --userflags PeriodH --batchname auto &

### MC ###
#python python/SKFlat.py -a SSWW -y 2016 -l submitList/Dilepton_SR_2016.txt -n 80 --skim SkimTree_Dilepton --userflags jcln_inv,fatjet_veto --batchname auto &
#python python/SKFlat.py -a SSWW -y 2016 -l submitList/NoSkim_SR_SSWW.txt -n 80 --userflags jcln_inv,fatjet_veto --batchname auto &

#python python/SKFlat.py -a Signal -y 2016 -l submitList/Dilepton_SR_2016.txt -n 80 --skim SkimTree_Dilepton --batchname auto &
#python python/SKFlat.py -a Signal -y 2016 -l submitList/NoSkim_SR.txt -n 80 --batchname auto &

#python python/SKFlat.py -a Control -y 2016 -l submitList/Dilepton_SM_CR_2016.txt -n 80 --skim SkimTree_Dilepton --batchname auto &
#python python/SKFlat.py -a Control -y 2016 -l submitList/NoSkim_SM_CR.txt -n 80 --batchname auto &

### signal ###
#python python/SKFlat.py -a SSWW -y 2016 -l submitList/SSWWTypeI.txt -n 50 --userflags jcln_inv,fatjet_veto --batchname auto &
#python python/SKFlat.py -a SSWW -y 2016 -i DYTypeI_SS_MuMu_M100 -n 50 --userflags jcln_inv,fatjet_veto --batchname auto &
#python python/SKFlat.py -a SSWW -y 2016 -i DYTypeI_SS_MuMu_M500 -n 50 --userflags jcln_inv,fatjet_veto --batchname auto &
#python python/SKFlat.py -a SSWW -y 2016 -i DYTypeI_SS_MuMu_M1000 -n 50 --userflags jcln_inv,fatjet_veto --batchname auto &
#python python/SKFlat.py -a SSWW -y 2016 -i DYTypeI_SS_MuMu_M1500 -n 50 --userflags jcln_inv,fatjet_veto --batchname auto &
#python python/SKFlat.py -a SSWW -y 2016 -i DYTypeI_SS_MuMu_M2000 -n 50 --userflags jcln_inv,fatjet_veto --batchname auto &
#python python/SKFlat.py -a SSWW -y 2016 -i DYTypeI_SS_MuMu_M2500 -n 50 --userflags jcln_inv,fatjet_veto --batchname auto &
#python python/SKFlat.py -a SSWW -y 2016 -i VBFTypeI_SS_MuMu_M500 -n 50 --userflags jcln_inv,fatjet_veto --batchname auto &
#python python/SKFlat.py -a SSWW -y 2016 -i VBFTypeI_SS_MuMu_M1000 -n 50 --userflags jcln_inv,fatjet_veto --batchname auto &
#python python/SKFlat.py -a SSWW -y 2016 -i VBFTypeI_SS_MuMu_M1500 -n 50 --userflags jcln_inv,fatjet_veto --batchname auto &
#python python/SKFlat.py -a SSWW -y 2016 -i VBFTypeI_SS_MuMu_M2000 -n 50 --userflags jcln_inv,fatjet_veto --batchname auto &
#python python/SKFlat.py -a SSWW -y 2016 -i VBFTypeI_SS_MuMu_M2500 -n 50 --userflags jcln_inv,fatjet_veto --batchname auto &

#python python/SKFlat.py -a Signal -y 2016 -i VBFTypeI_SS_MuMu_M1500 -n 50 --batchname auto &

#python python/SKFlat.py -a SSWW -y 2018 -l submitList/SSWWTypeI.txt -n 50 --batchname auto &
#python python/SKFlat.py -a SSWW -y 2018 -l submitList/SSWWTypeI.txt -n 50 --userflags jcln_inv --batchname auto &
#python python/SKFlat.py -a SSWW -y 2018 -l submitList/SSWWTypeI.txt -n 50 --userflags fatjet_veto --batchname auto &
#python python/SKFlat.py -a SSWW -y 2018 -l submitList/SSWWTypeI.txt -n 50 --userflags jcln_inv,fatjet_veto --batchname auto &
#python python/SKFlat.py -a SSWW -y 2018 -i DYTypeI_SS_MuMu_M1500 -n 50 --batchname auto &
#python python/SKFlat.py -a SSWW -y 2018 -i VBFTypeI_SS_MuMu_M1500 -n 50 --batchname auto &
#python python/SKFlat.py -a SSWW -y 2018 -i DYTypeI_SS_MuMu_M1500 -n 50 --userflags jcln_inv --batchname auto &
#python python/SKFlat.py -a SSWW -y 2018 -i VBFTypeI_SS_MuMu_M1500 -n 50 --userflags jcln_inv --batchname auto &
#python python/SKFlat.py -a SSWW -y 2018 -i DYTypeI_SS_MuMu_M1500 -n 50 --userflags fatjet_veto --batchname auto &
#python python/SKFlat.py -a SSWW -y 2018 -i VBFTypeI_SS_MuMu_M1500 -n 50 --userflags fatjet_veto --batchname auto &
#python python/SKFlat.py -a SSWW -y 2018 -i DYTypeI_SS_MuMu_M1500 -n 50 --userflags jcln_inv,fatjet_veto --batchname auto &
#python python/SKFlat.py -a SSWW -y 2018 -i VBFTypeI_SS_MuMu_M1500 -n 50 --userflags jcln_inv,fatjet_veto --batchname auto &

### fake measurement ###

#python python/SKFlat.py -a Fake -y 2016 -i SingleMuon:B_ver2 -n 50 --batchname auto &
#python python/SKFlat.py -a Fake -y 2016 -i SingleElectron:B_ver2 -n 50 --batchname auto &
#python python/SKFlat.py -a Fake -y 2016 -i DoubleMuon:B_ver2 -n 200 --userflags FR --batchname auto &
#python python/SKFlat.py -a Fake -y 2016 -i DoubleEG:B_ver2 -n 50 --userflags FR --batchname auto &
#python python/SKFlat.py -a Fake -y 2016 -l submitList/2016_SingleMuon_BtoH.txt -n 50 --batchname auto &
#python python/SKFlat.py -a Fake -y 2016 -l submitList/2016_SingleElectron_BtoH.txt -n 50 --batchname auto &
#python python/SKFlat.py -a Fake -y 2016 -l submitList/2016_DoubleMuon_BtoH.txt --userflags FR,Norm -n 50 --batchname auto &
#python python/SKFlat.py -a Fake -y 2016 -l submitList/2016_DoubleEG_BtoH.txt --userflags FR,Norm -n 50 --batchname auto &
#python python/SKFlat.py -a Fake -y 2016 -l submitList/Fake_Norm_MC_2016.txt --userflags FR,Norm -n 50 --batchname auto &

