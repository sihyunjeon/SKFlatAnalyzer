#!/bin/bash

### test job ###
#python python/SKFlat.py -a SSWW -e 2016a -i DoubleMuon:B_ver2 -n 50 --skim SkimTree_Dilepton --userflags jcln_inv,fatjet_veto --batchname auto &
#python python/SKFlat.py -a SSWW -e 2016a -i SSWWTypeI_NLO_SF_M1500 -n 50 --userflags jcln_inv,fatjet_veto --batchname auto &


### Test (investigation of key variables in each steps in event selection) ###
#! data !#
#python python/SKFlat.py -a Test -e 2016a -l submitList/2016a_DoubleMuon.txt -n 50 --userflags RunFake --batchname auto &
#python python/SKFlat.py -a Test -e 2016b -l submitList/2016b_DoubleMuon_FtoG.txt -n 50 --userflags RunFake --batchname auto &
#python python/SKFlat.py -a Test -e 2016b -l submitList/2016b_DoubleMuon_H.txt -n 50 --userflags RunFake,PeriodH --batchname auto &

#! SM backgrounds !#
#python python/SKFlat.py -a Test -e 2016a -l submitList/Signal_2016_HNMultiLep.txt -n 80 --batchname auto &
#python python/SKFlat.py -a Test -e 2016b -l submitList/Signal_2016_HNMultiLep.txt -n 80 --batchname auto &

#! signals #!
#python python/SKFlat.py -a Test -e 2016a -l submitList/signals_Mproxy.txt -n 80 --batchname auto &
#python python/SKFlat.py -a Test -e 2016b -l submitList/signals_Mproxy.txt -n 80 --batchname auto &


### SSWW selections (CR, SR) ###
#! 2016a !#
#python python/SKFlat.py -a SSWW -e 2016a -l submitList/2016a_DoubleMuon.txt -n 50 --skim SkimTree_Dilepton --userflags jcln_inv,fatjet_veto --batchname auto &
#python python/SKFlat.py -a SSWW -e 2016a -l submitList/2016a_DoubleMuon.txt -n 50 --skim SkimTree_Dilepton --userflags jcln_inv,fatjet_veto,RunFake --batchname auto &
#python python/SKFlat.py -a SSWW -e 2016a -l submitList/SSWW_2016_HNMultiLep.txt -n 50 --skim SkimTree_HNMultiLep --userflags jcln_inv,fatjet_veto --batchname auto &
#python python/SKFlat.py -a SSWW -e 2016a -l submitList/signals.txt -n 50 --userflags jcln_inv,fatjet_veto --batchname auto &
#python python/SKFlat.py -a SSWW -e 2016a -l submitList/signals_M1500.txt -n 50 --userflags jcln_inv,fatjet_veto --batchname auto &
#python python/SKFlat.py -a SSWW -e 2016a -l submitList/signals_Mproxy.txt -n 50 --userflags jcln_inv,fatjet_veto --batchname auto &
#python python/SKFlat.py -a SSWW -e 2016a -l submitList/signals_test.txt -n 50 --userflags jcln_inv,fatjet_veto --batchname auto &

#python python/SKFlat.py -a SSWW -e 2016a -l submitList/2016a_DoubleMuon.txt -n 50 --skim SkimTree_Dilepton --userflags jcln_inv,fatjet_veto,CentralJet --batchname auto &
#python python/SKFlat.py -a SSWW -e 2016a -l submitList/2016a_DoubleMuon.txt -n 50 --skim SkimTree_Dilepton --userflags jcln_inv,fatjet_veto,CentralJet,RunFake --batchname auto &
#python python/SKFlat.py -a SSWW -e 2016a -l submitList/SSWW_2016_HNMultiLep.txt -n 50 --skim SkimTree_HNMultiLep --userflags jcln_inv,fatjet_veto,CentralJet --batchname auto &
#python python/SKFlat.py -a SSWW -e 2016a -l submitList/signals_test.txt -n 50 --userflags jcln_inv,fatjet_veto,CentralJet --batchname auto &

#python python/SKFlat.py -a SSWW -e 2016a -l submitList/2016a_DoubleMuon.txt -n 50 --skim SkimTree_Dilepton --userflags jcln_inv,fatjet_veto,CentralJet,Pass_VBF --batchname auto &
#python python/SKFlat.py -a SSWW -e 2016a -l submitList/2016a_DoubleMuon.txt -n 50 --skim SkimTree_Dilepton --userflags jcln_inv,fatjet_veto,CentralJet,Pass_VBF,RunFake --batchname auto &
#python python/SKFlat.py -a SSWW -e 2016a -l submitList/SSWW_2016_HNMultiLep.txt -n 50 --skim SkimTree_HNMultiLep --userflags jcln_inv,fatjet_veto,CentralJet,Pass_VBF --batchname auto &
#python python/SKFlat.py -a SSWW -e 2016a -l submitList/signals_test.txt -n 50 --userflags jcln_inv,fatjet_veto,CentralJet,Pass_VBF --batchname auto &

python python/SKFlat.py -a SSWW -e 2016a -l submitList/2016a_DoubleMuon.txt -n 50 --skim SkimTree_Dilepton --userflags jcln_inv,fatjet_veto,CentralJet,Pass_VBF,Pt10 --batchname auto &
python python/SKFlat.py -a SSWW -e 2016a -l submitList/2016a_DoubleMuon.txt -n 50 --skim SkimTree_Dilepton --userflags jcln_inv,fatjet_veto,CentralJet,Pass_VBF,Pt10,RunFake --batchname auto &
python python/SKFlat.py -a SSWW -e 2016a -l submitList/SSWW_2016_HNMultiLep.txt -n 50 --skim SkimTree_HNMultiLep --userflags jcln_inv,fatjet_veto,CentralJet,Pass_VBF,Pt10 --batchname auto &
#python python/SKFlat.py -a SSWW -e 2016a -l submitList/signals_test.txt -n 50 --userflags jcln_inv,fatjet_veto,CentralJet,Pass_VBF,Pt10 --batchname auto &

#python python/SKFlat.py -a SSWW -e 2016a -l submitList/2016a_DoubleMuon.txt -n 50 --skim SkimTree_Dilepton --userflags jcln_inv,fatjet_veto,TightEleVeto --batchname auto &
#python python/SKFlat.py -a SSWW -e 2016a -l submitList/2016a_DoubleMuon.txt -n 50 --skim SkimTree_Dilepton --userflags jcln_inv,fatjet_veto,TightEleVeto,RunFake --batchname auto &
#python python/SKFlat.py -a SSWW -e 2016a -l submitList/SSWW_2016_HNMultiLep.txt -n 50 --skim SkimTree_HNMultiLep --userflags jcln_inv,fatjet_veto,TightEleVeto --batchname auto &
#python python/SKFlat.py -a SSWW -e 2016a -l submitList/signals_test.txt -n 50 --userflags jcln_inv,fatjet_veto,TightEleVeto --batchname auto &


#! 2016b !#
#python python/SKFlat.py -a SSWW -e 2016b -l submitList/2016b_DoubleMuon_FtoG.txt -n 50 --skim SkimTree_Dilepton --userflags jcln_inv,fatjet_veto --batchname auto &
#python python/SKFlat.py -a SSWW -e 2016b -l submitList/2016b_DoubleMuon_H.txt -n 50 --skim SkimTree_Dilepton --userflags jcln_inv,fatjet_veto,PeriodH --batchname auto &
#python python/SKFlat.py -a SSWW -e 2016b -l submitList/2016b_DoubleMuon_FtoG.txt -n 50 --skim SkimTree_Dilepton --userflags jcln_inv,fatjet_veto,RunFake --batchname auto &
#python python/SKFlat.py -a SSWW -e 2016b -l submitList/2016b_DoubleMuon_H.txt -n 50 --skim SkimTree_Dilepton --userflags jcln_inv,fatjet_veto,RunFake,PeriodH --batchname auto &
#python python/SKFlat.py -a SSWW -e 2016b -l submitList/SSWW_2016_HNMultiLep.txt -n 50 --skim SkimTree_HNMultiLep --userflags jcln_inv,fatjet_veto --batchname auto &
#python python/SKFlat.py -a SSWW -e 2016b -l submitList/signals.txt -n 50 --userflags jcln_inv,fatjet_veto --batchname auto &
#python python/SKFlat.py -a SSWW -e 2016b -l submitList/signals_M1500.txt -n 50 --userflags jcln_inv,fatjet_veto --batchname auto &
#python python/SKFlat.py -a SSWW -e 2016b -l submitList/signals_Mproxy.txt -n 50 --userflags jcln_inv,fatjet_veto --batchname auto &
#python python/SKFlat.py -a SSWW -e 2016b -l submitList/signals_test.txt -n 50 --userflags jcln_inv,fatjet_veto --batchname auto &

#python python/SKFlat.py -a SSWW -e 2016b -l submitList/2016b_DoubleMuon_FtoG.txt -n 50 --skim SkimTree_Dilepton --userflags jcln_inv,fatjet_veto,CentralJet --batchname auto &
#python python/SKFlat.py -a SSWW -e 2016b -l submitList/2016b_DoubleMuon_H.txt -n 50 --skim SkimTree_Dilepton --userflags jcln_inv,fatjet_veto,CentralJet,PeriodH --batchname auto &
#python python/SKFlat.py -a SSWW -e 2016b -l submitList/2016b_DoubleMuon_FtoG.txt -n 50 --skim SkimTree_Dilepton --userflags jcln_inv,fatjet_veto,CentralJet,RunFake --batchname auto &
#python python/SKFlat.py -a SSWW -e 2016b -l submitList/2016b_DoubleMuon_H.txt -n 50 --skim SkimTree_Dilepton --userflags jcln_inv,fatjet_veto,CentralJet,RunFake,PeriodH --batchname auto &
#python python/SKFlat.py -a SSWW -e 2016b -l submitList/SSWW_2016_HNMultiLep.txt -n 50 --skim SkimTree_HNMultiLep --userflags jcln_inv,fatjet_veto,CentralJet --batchname auto &
#python python/SKFlat.py -a SSWW -e 2016b -l submitList/signals_test.txt -n 50 --userflags jcln_inv,fatjet_veto,CentralJet --batchname auto &

#python python/SKFlat.py -a SSWW -e 2016b -l submitList/2016b_DoubleMuon_FtoG.txt -n 50 --skim SkimTree_Dilepton --userflags jcln_inv,fatjet_veto,CentralJet,Pass_VBF --batchname auto &
#python python/SKFlat.py -a SSWW -e 2016b -l submitList/2016b_DoubleMuon_H.txt -n 50 --skim SkimTree_Dilepton --userflags jcln_inv,fatjet_veto,CentralJet,Pass_VBF,PeriodH --batchname auto &
#python python/SKFlat.py -a SSWW -e 2016b -l submitList/2016b_DoubleMuon_FtoG.txt -n 50 --skim SkimTree_Dilepton --userflags jcln_inv,fatjet_veto,CentralJet,Pass_VBF,RunFake --batchname auto &
#python python/SKFlat.py -a SSWW -e 2016b -l submitList/2016b_DoubleMuon_H.txt -n 50 --skim SkimTree_Dilepton --userflags jcln_inv,fatjet_veto,CentralJet,Pass_VBF,RunFake,PeriodH --batchname auto &
#python python/SKFlat.py -a SSWW -e 2016b -l submitList/SSWW_2016_HNMultiLep.txt -n 50 --skim SkimTree_HNMultiLep --userflags jcln_inv,fatjet_veto,CentralJet,Pass_VBF --batchname auto &
#python python/SKFlat.py -a SSWW -e 2016b -l submitList/signals_test.txt -n 50 --userflags jcln_inv,fatjet_veto,CentralJet,Pass_VBF --batchname auto &

python python/SKFlat.py -a SSWW -e 2016b -l submitList/2016b_DoubleMuon_FtoG.txt -n 50 --skim SkimTree_Dilepton --userflags jcln_inv,fatjet_veto,CentralJet,Pass_VBF,Pt10 --batchname auto &
python python/SKFlat.py -a SSWW -e 2016b -l submitList/2016b_DoubleMuon_H.txt -n 50 --skim SkimTree_Dilepton --userflags jcln_inv,fatjet_veto,CentralJet,Pass_VBF,Pt10,PeriodH --batchname auto &
python python/SKFlat.py -a SSWW -e 2016b -l submitList/2016b_DoubleMuon_FtoG.txt -n 50 --skim SkimTree_Dilepton --userflags jcln_inv,fatjet_veto,CentralJet,Pass_VBF,Pt10,RunFake --batchname auto &
python python/SKFlat.py -a SSWW -e 2016b -l submitList/2016b_DoubleMuon_H.txt -n 50 --skim SkimTree_Dilepton --userflags jcln_inv,fatjet_veto,CentralJet,Pass_VBF,Pt10,RunFake,PeriodH --batchname auto &
python python/SKFlat.py -a SSWW -e 2016b -l submitList/SSWW_2016_HNMultiLep.txt -n 50 --skim SkimTree_HNMultiLep --userflags jcln_inv,fatjet_veto,CentralJet,Pass_VBF,Pt10 --batchname auto &
#python python/SKFlat.py -a SSWW -e 2016b -l submitList/signals_test.txt -n 50 --userflags jcln_inv,fatjet_veto,CentralJet,Pass_VBF,Pt10 --batchname auto &

#python python/SKFlat.py -a SSWW -e 2016b -l submitList/2016b_DoubleMuon_FtoG.txt -n 50 --skim SkimTree_Dilepton --userflags jcln_inv,fatjet_veto,TightEleVeto --batchname auto &
#python python/SKFlat.py -a SSWW -e 2016b -l submitList/2016b_DoubleMuon_H.txt -n 50 --skim SkimTree_Dilepton --userflags jcln_inv,fatjet_veto,TightEleVeto,PeriodH --batchname auto &
#python python/SKFlat.py -a SSWW -e 2016b -l submitList/2016b_DoubleMuon_FtoG.txt -n 50 --skim SkimTree_Dilepton --userflags jcln_inv,fatjet_veto,TightEleVeto,RunFake --batchname auto &
#python python/SKFlat.py -a SSWW -e 2016b -l submitList/2016b_DoubleMuon_H.txt -n 50 --skim SkimTree_Dilepton --userflags jcln_inv,fatjet_veto,TightEleVeto,RunFake,PeriodH --batchname auto &
#python python/SKFlat.py -a SSWW -e 2016b -l submitList/SSWW_2016_HNMultiLep.txt -n 50 --skim SkimTree_HNMultiLep --userflags jcln_inv,fatjet_veto,TightEleVeto --batchname auto &
#python python/SKFlat.py -a SSWW -e 2016b -l submitList/signals_test.txt -n 50 --userflags jcln_inv,fatjet_veto,TightEleVeto --batchname auto &



#! 2017 !#
#python python/SKFlat.py -a SSWW -e 2017 -l submitList/2017_DoubleMuon.txt -n 50 --skim SkimTree_Dilepton --userflags jcln_inv,fatjet_veto --batchname auto &
#python python/SKFlat.py -a SSWW -e 2017 -l submitList/2017_DoubleMuon.txt -n 50 --skim SkimTree_Dilepton --userflags jcln_inv,fatjet_veto,RunFake --batchname auto &
#python python/SKFlat.py -a SSWW -e 2017 -l submitList/SSWW_2017_HNMultiLep.txt -n 50 --skim SkimTree_HNMultiLep --userflags jcln_inv,fatjet_veto --batchname auto &
#python python/SKFlat.py -a SSWW -e 2017 -l submitList/signals.txt -n 50 --userflags jcln_inv,fatjet_veto --batchname auto &
#python python/SKFlat.py -a SSWW -e 2017 -l submitList/signals_Mproxy.txt -n 50 --userflags jcln_inv,fatjet_veto --batchname auto &

#! 2018 !#
#python python/SKFlat.py -a SSWW -e 2018 -l submitList/2018_DoubleMuon.txt -n 50 --skim SkimTree_Dilepton --userflags jcln_inv,fatjet_veto --batchname auto &
#python python/SKFlat.py -a SSWW -e 2018 -l submitList/2018_DoubleMuon.txt -n 50 --skim SkimTree_Dilepton --userflags jcln_inv,fatjet_veto,RunFake --batchname auto &
#python python/SKFlat.py -a SSWW -e 2018 -l submitList/SSWW_2018_HNMultiLep.txt -n 50 --skim SkimTree_HNMultiLep --userflags jcln_inv,fatjet_veto --batchname auto &
#python python/SKFlat.py -a SSWW -e 2018 -l submitList/signals.txt -n 50 --userflags jcln_inv,fatjet_veto --batchname auto &
#python python/SKFlat.py -a SSWW -e 2018 -l submitList/signals_Mproxy.txt -n 50 --userflags jcln_inv,fatjet_veto --batchname auto &



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
#python python/SKFlat.py -a Control -e 2016a -l submitList/Control_2016_HNMultiLep.txt -n 80 --batchname auto &
#python python/SKFlat.py -a Control -e 2016b -l submitList/Control_2016_HNMultiLep.txt -n 80 --batchname auto &
#JH : Don't use HNMultiLep skim if to see DY, TT CR

##!! 2017 !!##
#python python/SKFlat.py -a Control -e 2017 -l submitList/2017_DoubleMuon.txt -n 50 --skim SkimTree_Dilepton --batchname auto &
#python python/SKFlat.py -a Control -e 2017 -l submitList/2017_DoubleMuon.txt -n 50 --skim SkimTree_Dilepton --userflags RunFake --batchname auto &
#python python/SKFlat.py -a Control -e 2017 -l submitList/Control_2017_HNMultiLep.txt -n 80 --batchname auto &
#JH : Don't use HNMultiLep skim if to see DY, TT CR

##!! 2018 !!##
#python python/SKFlat.py -a Control -e 2018 -l submitList/2018_DoubleMuon.txt -n 50 --skim SkimTree_Dilepton --batchname auto &
#python python/SKFlat.py -a Control -e 2018 -l submitList/2018_DoubleMuon.txt -n 50 --skim SkimTree_Dilepton --userflags RunFake --batchname auto &
#python python/SKFlat.py -a Control -e 2018 -l submitList/Control_2018_HNMultiLep.txt -n 80 --batchname auto &
#JH : Don't use HNMultiLep skim if to see DY, TT CR



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
