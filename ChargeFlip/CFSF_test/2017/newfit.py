import ROOT as rt
rt.gROOT.LoadMacro('./histFitter.C+')
#rt.gROOT.LoadMacro('./RooCBExGaussShape.cc+')
#rt.gROOT.LoadMacro('./RooCMSShape.cc+')
from ROOT import tnpFitter
import time
import os

channels = ["BB","EE","BE"]

for channel in channels:

  #fileName = "DYJets_MG_All"
  fileName = "DYJets_All"
  os.system("mkdir -p "+fileName)
  fileTruth  = rt.TFile("CFSF_test_"+fileName+".root",'read')

  funcs = [
      "Gaussian::sigResPass(x,meanOS,sigmaOS)",
      "Gaussian::sigResFail(x,meanSS,sigmaSS)",
      "RooCMSShape::bkgPass(x, acmsOS, betaOS, gammaOS, peakOS)",
      "RooCMSShape::bkgFail(x, acmsSS, betaSS, gammaSS, peakSS)",
      ]

  if fileTruth.GetName() == "CFSF_test_DYJets_All.root" and channel == "BB":
    pars = [
        "meanOS[-0.0,-5.0,5.0]","sigmaOS[0.9,0.5,5.0]",
        "meanSS[-0.0,-5.0,5.0]","sigmaSS[0.9,0.5,5.0]",
        "acmsOS[60.,50.,80.]","betaOS[0.05,0.01,0.08]","gammaOS[0.1, -2, 2]","peakOS[90.0]",
        "acmsSS[60.,50.,80.]","betaSS[0.05,0.01,0.08]","gammaSS[0.1, 0.05, 2]","peakSS[90.0]",
        ]
  elif fileTruth.GetName() == "CFSF_test_DYJets_MG_All.root" and channel == "BB":
    pars = [
        "meanOS[-0.0,-5.0,5.0]","sigmaOS[0.9,0.5,5.0]",
        "meanSS[-0.0,-5.0,5.0]","sigmaSS[0.9,0.5,5.0]",
        "acmsOS[60.,50.,80.]","betaOS[0.05,0.01,0.08]","gammaOS[0.1, -2, 2]","peakOS[90.0]",
        "acmsSS[60.,50.,80.]","betaSS[0.05,0.01,0.08]","gammaSS[0.1, 0.05, 2]","peakSS[90.0]",
        ]
  elif fileTruth.GetName() == "CFSF_test_DYJets_All.root" and channel == "BE":
    pars = [
        "meanOS[-0.0,-5.0,5.0]","sigmaOS[0.9,0.5,5.0]",
        "meanSS[-0.0,-5.0,5.0]","sigmaSS[0.9,0.5,5.0]",
        "acmsOS[60.,50.,80.]","betaOS[0.05,0.01,0.08]","gammaOS[0.1, -2, 2]","peakOS[90.0]",
        "acmsSS[60.,50.,80.]","betaSS[0.05,0.01,0.08]","gammaSS[0.1, -2, 2]","peakSS[90.0,80.0,110.0]", # This gives 93.04% agreement
        #"acmsSS[60.,50.,80.]","betaSS[0.01,0.,2.0]","gammaSS[2.0, 0.15, 5.0]","peakSS[90.0,80.0,110.0]", # This gives 98.8% agreement; sllllightly better to describe the peak
        ]
  elif fileTruth.GetName() == "CFSF_test_DYJets_MG_All.root" and channel == "BE":
    pars = [
        "meanOS[-0.0,-5.0,5.0]","sigmaOS[0.9,0.5,5.0]",
        "meanSS[-0.0,-5.0,5.0]","sigmaSS[0.9,0.5,5.0]",
        "acmsOS[60.,50.,80.]","betaOS[0.05,0.01,0.08]","gammaOS[0.1, -2, 2]","peakOS[90.0]",
        #"acmsSS[60.,50.,80.]","betaSS[0.05,0.01,0.08]","gammaSS[0.1, -2, 2]","peakSS[90.0]", # default : 92.73%
        "acmsSS[60.,50.,80.]","betaSS[0.05,0.01,0.08]","gammaSS[0.1, -2, 2]","peakSS[90.0,80.0,110.0]", # This gives 92.69% agreement
        #"acmsSS[60.,50.,80.]","betaSS[0.01,0.,2.0]","gammaSS[2.0, 0.1, 5.0]","peakSS[90.0,80.0,110.0]", # This gives 94.12% agreement
        #"acmsSS[60.,50.,80.]","betaSS[0.01,0.,2.0]","gammaSS[2.0, 0.15, 5.0]","peakSS[90.0,80.0,110.0]", # This gives 101.51% agreement; better to describe the peak
        ]
  else:
    pars = [
        "meanOS[-0.0,-5.0,5.0]","sigmaOS[0.9,0.5,5.0]",
        "meanSS[-0.0,-5.0,5.0]","sigmaSS[0.9,0.5,5.0]",
        "acmsOS[60.,50.,80.]","betaOS[0.05,0.01,0.08]","gammaOS[0.1, -2, 2]","peakOS[90.0]",
        "acmsSS[60.,50.,80.]","betaSS[0.05,0.01,0.08]","gammaSS[0.1, -2, 2]","peakSS[90.0]",
        ]
  
  this_workspace = []
  this_workspace.extend(pars)
  this_workspace.extend(funcs)
  
  infile = rt.TFile("CFSF_test_DoubleEG.root", "read")
  if channel == "BE":
    hOS = infile.Get("HNTightV1/ScaleFactor/"+channel+"_ZMass_OS_CFSFweighted_shifted_1.0%")
  else:
    hOS = infile.Get("HNTightV1/ScaleFactor/"+channel+"_ZMass_OS_CFweighted_shifted_1.0%")
  hSS = infile.Get("HNTightV1/ScaleFactor/"+channel+"_ZMass_SS_MET0")
  fitter = tnpFitter( hOS, hSS, fileName, "myhist_"+channel )
  infile.Close()
  
  fitter.useMinos()
  rootfile = rt.TFile("newfit_"+fileName+".root",'update')
  fitter.setOutputFile( rootfile )
  
  if channel == "BE":
    histZLineShapeOS = fileTruth.Get("HNTightV1/ScaleFactor/"+channel+"_ZMass_OS_CFSFweighted_shifted_1.0%")
  else:
    histZLineShapeOS = fileTruth.Get("HNTightV1/ScaleFactor/"+channel+"_ZMass_OS_CFweighted_shifted_1.0%")
  histZLineShapeSS = fileTruth.Get("HNTightV1/ScaleFactor/"+channel+"_ZMass_SS_MET0")
  fitter.setZLineShapes(histZLineShapeOS,histZLineShapeSS)
  
  fileTruth.Close()
  
  workspace = rt.vector("string")()
  for i in this_workspace:
    workspace.push_back(i)
  fitter.setWorkspace( workspace )
  
  title = "mytitle_"+channel
  fitter.fits(False,title)
  print "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
  rootfile.Close()

print "BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB"
