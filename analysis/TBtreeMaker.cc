#include <stdexcept>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <chrono>
#include <cmath>
#include <vector>
#include <numeric>
#include <functional>

#include "TBevt.h"
#include "TButility.h"
#include "TBload.h"
#include "TBhist.h"
#include "TBauxfactory.h"
#include "TBdwc.h"

#include "functions.cc"

#include "TROOT.h"
#include "TStyle.h"
#include <TChain.h>
#include <TFile.h>
#include <TTree.h>
#include <TF1.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TCanvas.h>



int main(int argc, char** argv) {

  gStyle->SetOptFit(1);

  int runNum = std::stoi(argv[1]);
  TBload<TBwaveform>* loader = new TBload<TBwaveform>(runNum);

  int maxEvents = std::stoi(argv[2]); 

  std::string pedPath = "dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/khwang/Aug2022TB/RunInfo/pedestal/mean/Run" + std::to_string(runNum) + "_pedestalHist_mean.root";

  TButility utility = TButility();
  utility.loading("dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/khwang/Aug2022TB/RunInfo/mapping/mapping_Aug2022TB.root");
  utility.loadped(pedPath);

  std::vector<float> dwc_offset{-3.119, 3.207, -5.535, 10.48};

  AuxFactory<TBwaveform>* auxFac = new AuxFactory<TBwaveform>(runNum, 2.5);
  DWCset<TBwaveform>* dwcSet = new DWCset<TBwaveform>(runNum, dwc_calib, 1.);
  dwcSet->SetOffset(dwc_offset);

  auxFac->print();
  dwcSet->print();

  TBcid pscid = utility.getcid(TBdetector::detid::preshower);
  TBcid mucid = utility.getcid(TBdetector::detid::muon);

  std::vector<TBcid> dwc1;
  dwc1.push_back(TBcid(1,17));
  dwc1.push_back(TBcid(1,19));
  dwc1.push_back(TBcid(1,21));
  dwc1.push_back(TBcid(1,23));

  std::vector<TBcid> dwc2;
  dwc2.push_back(TBcid(1,25));
  dwc2.push_back(TBcid(1,27));
  dwc2.push_back(TBcid(1,29));
  dwc2.push_back(TBcid(1,31));

  std::vector<TBcid> M1TC;
  M1TC.push_back(utility.getcid(TBdetector::detid::PMT, 1, 1, true));
  M1TC.push_back(utility.getcid(TBdetector::detid::PMT, 1, 2, true));
  M1TC.push_back(utility.getcid(TBdetector::detid::PMT, 1, 3, true));
  M1TC.push_back(utility.getcid(TBdetector::detid::PMT, 1, 4, true));

  std::vector<TBcid> M1TS;
  M1TS.push_back(utility.getcid(TBdetector::detid::PMT, 1, 1, false));
  M1TS.push_back(utility.getcid(TBdetector::detid::PMT, 1, 2, false));
  M1TS.push_back(utility.getcid(TBdetector::detid::PMT, 1, 3, false));
  M1TS.push_back(utility.getcid(TBdetector::detid::PMT, 1, 4, false));


  TFile* treeFile = new TFile((TString)("/u/user/kyhwang/DRC/Aug2022TB/dev_230307/dual-readout_TB/analysis/Tree/TreeRun" + std::to_string(runNum) + "_RunInfo.root"), "RECREATE");

  TTree* aTree = new TTree("data", "data");

  float _dwc_1_x, _dwc_1_y, _dwc_2_x, _dwc_2_y;
  float _muADC, _psADC;
  float _m1t1c, _m1t2c, _m1t3c, _m1t4c;
  float _m1t1s, _m1t2s, _m1t3s, _m1t4s;

  aTree->Branch("dwc_1_x", &_dwc_1_x);
  aTree->Branch("dwc_1_y", &_dwc_1_y);
  aTree->Branch("dwc_2_x", &_dwc_2_x);
  aTree->Branch("dwc_2_y", &_dwc_2_y);

  aTree->Branch("muADC", &_muADC);
  aTree->Branch("psADC", &_psADC);

  aTree->Branch("m1t1c", &_m1t1c);
  aTree->Branch("m1t2c", &_m1t2c);
  aTree->Branch("m1t3c", &_m1t3c);
  aTree->Branch("m1t4c", &_m1t4c);
  
  aTree->Branch("m1t1s", &_m1t1s);
  aTree->Branch("m1t2s", &_m1t2s);
  aTree->Branch("m1t3s", &_m1t3s);
  aTree->Branch("m1t4s", &_m1t4s);

  if ( maxEvents == -1 )
    maxEvents = loader->getEntries();

  if ( maxEvents > loader->getEntries() )
    throw std::runtime_error("Events number is larger than entries !");

  std::chrono::time_point time_begin = std::chrono::system_clock::now(); //delete
  printf("\n");

  float selEvent = 0;
  for ( int ievt = 0; ievt < maxEvents; ievt++ ) {

    if ( ievt > 0 && ievt % 8 == 0 ) {
      std::chrono::duration time_taken = std::chrono::system_clock::now() - time_begin; //delete
      float percent_done = 1. * ievt / (float)maxEvents;
      std::chrono::duration time_left = time_taken * ( 1 / percent_done - 1 );
      std::chrono::minutes minutes_left = std::chrono::duration_cast<std::chrono::minutes>(time_left);
      std::chrono::seconds seconds_left = std::chrono::duration_cast<std::chrono::seconds>(time_left - minutes_left);
      std::cout << "\r\033[F"<< " " << ievt << " events  "<< minutes_left.count() << ":";
      printf("%02d left   %.1f%%            \n",int(seconds_left.count()),percent_done*100);
    }

    loader->loading();
    auto anEvt = loader->getEvent();

    TBwaveform adata_ps = anEvt->data(pscid);
    TBwaveform adata_mu = anEvt->data(mucid);

    std::vector<TBwaveform> setDWC1;
    for ( int i = 0; i < dwc1.size(); i++ )
      setDWC1.push_back(anEvt->data(dwc1.at(i)));

    std::vector<TBwaveform> setDWC2;
    for ( int i = 0; i < dwc2.size(); i++ )
      setDWC2.push_back(anEvt->data(dwc2.at(i)));

    std::vector<TBwaveform> M1TC_data;
    std::vector<TBwaveform> M1TS_data;
    for ( int i = 0; i < M1TC.size(); i++ ) {
      M1TC_data.push_back(anEvt->data(M1TC.at(i)));
      M1TS_data.push_back(anEvt->data(M1TS.at(i)));
    }

    dwcSet->SetDWC(setDWC1, setDWC2);
    auto dwc_pos = dwcSet->GetAlignedPosition();

    auto psWave_ped = adata_ps.pedcorrectedWaveform(utility.retrievePed(pscid));
    auto muWave_ped = adata_mu.pedcorrectedWaveform(utility.retrievePed(mucid));

    auto moduleM1T1Cwave_ped = M1TC_data.at(0).pedcorrectedWaveform(utility.retrievePed(M1TC.at(0)));
    auto moduleM1T1Swave_ped = M1TS_data.at(0).pedcorrectedWaveform(utility.retrievePed(M1TS.at(0)));

    auto moduleM1T2Cwave_ped = M1TC_data.at(1).pedcorrectedWaveform(utility.retrievePed(M1TC.at(1)));
    auto moduleM1T2Swave_ped = M1TS_data.at(1).pedcorrectedWaveform(utility.retrievePed(M1TS.at(1)));

    auto moduleM1T3Cwave_ped = M1TC_data.at(2).pedcorrectedWaveform(utility.retrievePed(M1TC.at(2)));
    auto moduleM1T3Swave_ped = M1TS_data.at(2).pedcorrectedWaveform(utility.retrievePed(M1TS.at(2)));
    
    auto moduleM1T4Cwave_ped = M1TC_data.at(3).pedcorrectedWaveform(utility.retrievePed(M1TC.at(3)));
    auto moduleM1T4Swave_ped = M1TS_data.at(3).pedcorrectedWaveform(utility.retrievePed(M1TS.at(3)));


    _muADC = std::accumulate(psWave_ped.begin() + 240, psWave_ped.begin() + 240 + 140, 0.);
    _psADC = std::accumulate(muWave_ped.begin() + 820, muWave_ped.begin() + 820 + 130, 0.);

    _m1t1c = std::accumulate(moduleM1T1Cwave_ped.begin() + 120, moduleM1T1Cwave_ped.begin() + 120 + 80, 0.);
    _m1t1s = std::accumulate(moduleM1T1Swave_ped.begin() + 110, moduleM1T1Swave_ped.begin() + 110 + 110, 0.);

    _m1t2c = std::accumulate(moduleM1T2Cwave_ped.begin() + 130, moduleM1T2Cwave_ped.begin() + 130 + 80, 0.);
    _m1t2s = std::accumulate(moduleM1T2Swave_ped.begin() + 110, moduleM1T2Swave_ped.begin() + 110 + 130, 0.);

    _m1t3c = std::accumulate(moduleM1T3Cwave_ped.begin() + 115, moduleM1T3Cwave_ped.begin() + 115 + 60, 0.);
    _m1t3s = std::accumulate(moduleM1T3Swave_ped.begin() + 110, moduleM1T3Swave_ped.begin() + 110 + 110, 0.);

    _m1t4c = std::accumulate(moduleM1T4Cwave_ped.begin() + 130, moduleM1T4Cwave_ped.begin() + 130 + 70, 0.);
    _m1t4s = std::accumulate(moduleM1T4Swave_ped.begin() + 120, moduleM1T4Swave_ped.begin() + 120 + 110, 0.);

    _dwc_1_x = dwc_pos.at(0);
    _dwc_1_y = dwc_pos.at(1);
    _dwc_2_x = dwc_pos.at(2);
    _dwc_2_y = dwc_pos.at(3);

    // _muADC = muADC;
    // _psADC = psADC;

    // _m1t1c = moduleM1T1Cadc;
    // _m1t2c = moduleM1T2Cadc;
    // _m1t3c = moduleM1T3Cadc;
    // _m1t4c = moduleM1T4Cadc; 

    // _m1t1s = moduleM1T1Sadc;
    // _m1t2s = moduleM1T2Sadc;
    // _m1t3s = moduleM1T3Sadc;
    // _m1t4s = moduleM1T4Sadc;

    aTree->Fill();


  }
  loader->close();

  treeFile->cd();
  aTree->Write();
  treeFile->Close();

  return 0;
}
