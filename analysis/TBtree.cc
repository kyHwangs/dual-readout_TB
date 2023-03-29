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

  int m1t1c_start_ref = 125;
  int m1t1c_end_ref = 217;

  int m1t1s_start_ref = 120;
  int m1t1s_end_ref = 243;

  int m1t2c_start_ref = 133;
  int m1t2c_end_ref = 228;

  int m1t2s_start_ref = 128;
  int m1t2s_end_ref = 245;

  int m1t3c_start_ref = 117;
  int m1t3c_end_ref = 180;

  int m1t3s_start_ref = 117;
  int m1t3s_end_ref = 220;

  int m1t4c_start_ref = 128;
  int m1t4c_end_ref = 226;

  int m1t4s_start_ref = 125;
  int m1t4s_end_ref = 248;

  std::vector<int> m1t1c_start;
  std::vector<int> m1t1c_end  ; // 여기까지
  std::vector<int> m1t1s_start;
  std::vector<int> m1t1s_end  ;

  std::vector<int> m1t2c_start;
  std::vector<int> m1t2c_end  ;
  std::vector<int> m1t2s_start;
  std::vector<int> m1t2s_end  ;

  std::vector<int> m1t3c_start;
  std::vector<int> m1t3c_end  ;
  std::vector<int> m1t3s_start;
  std::vector<int> m1t3s_end  ;

  std::vector<int> m1t4c_start;
  std::vector<int> m1t4c_end  ;
  std::vector<int> m1t4s_start;
  std::vector<int> m1t4s_end  ;

  for ( int i = 0; i < 9; i++ ) {
    m1t1c_start.push_back(m1t1c_start_ref - 10 + 2 * i);
    m1t1c_end.push_back(m1t1c_end_ref - 10 + 2 * i);

    m1t1s_start.push_back(m1t1s_start_ref - 10 + 2 * i);
    m1t1s_end.push_back(m1t1s_end_ref - 10 + 2 * i);

    m1t2c_start.push_back(m1t2c_start_ref - 10 + 2 * i);
    m1t2c_end.push_back(m1t2c_end_ref - 10 + 2 * i);

    m1t2s_start.push_back(m1t2s_start_ref - 10 + 2 * i);
    m1t2s_end.push_back(m1t2s_end_ref - 10 + 2 * i);

    m1t3c_start.push_back(m1t3c_start_ref - 10 + 2 * i);
    m1t3c_end.push_back(m1t3c_end_ref - 10 + 2 * i);

    m1t3s_start.push_back(m1t3s_start_ref - 10 + 2 * i);
    m1t3s_end.push_back(m1t3s_end_ref - 10 + 2 * i);

    m1t4c_start.push_back(m1t4c_start_ref - 10 + 2 * i);
    m1t4c_end.push_back(m1t4c_end_ref - 10 + 2 * i);

    m1t4s_start.push_back(m1t4s_start_ref - 10 + 2 * i);
    m1t4s_end.push_back(m1t4s_end_ref - 10 + 2 * i);
  }

  std::vector<std::pair<int, int>> cerenIntT1;
  std::vector<std::pair<int, int>> cerenIntT2;
  std::vector<std::pair<int, int>> cerenIntT3;
  std::vector<std::pair<int, int>> cerenIntT4;

  std::vector<std::pair<int, int>> scintIntT1;
  std::vector<std::pair<int, int>> scintIntT2;
  std::vector<std::pair<int, int>> scintIntT3;
  std::vector<std::pair<int, int>> scintIntT4;

  std::vector<TString> nameVecCT1;
  std::vector<TString> nameVecCT2;
  std::vector<TString> nameVecCT3;
  std::vector<TString> nameVecCT4;

  std::vector<TString> nameVecST1;
  std::vector<TString> nameVecST2;
  std::vector<TString> nameVecST3;
  std::vector<TString> nameVecST4;

  std::vector<TBhist*> moduleM1T1C;
  std::vector<TBhist*> moduleM1T2C;
  std::vector<TBhist*> moduleM1T3C;
  std::vector<TBhist*> moduleM1T4C;

  std::vector<TBhist*> moduleM1T1S;
  std::vector<TBhist*> moduleM1T2S;
  std::vector<TBhist*> moduleM1T3S;
  std::vector<TBhist*> moduleM1T4S;

  std::vector<TH1F*> moduleM1T1C_zoom;
  std::vector<TH1F*> moduleM1T2C_zoom;
  std::vector<TH1F*> moduleM1T3C_zoom;
  std::vector<TH1F*> moduleM1T4C_zoom;

  std::vector<TH1F*> moduleM1T1S_zoom;
  std::vector<TH1F*> moduleM1T2S_zoom;
  std::vector<TH1F*> moduleM1T3S_zoom;
  std::vector<TH1F*> moduleM1T4S_zoom;

  for (int i = 0; i < m1t2c_start.size(); i++) {
    for (int j = 0; j < m1t2c_end.size(); j++) {
      cerenIntT1.push_back(std::make_pair(m1t1c_start.at(i), m1t1c_end.at(j)));
      cerenIntT2.push_back(std::make_pair(m1t2c_start.at(i), m1t2c_end.at(j)));
      cerenIntT3.push_back(std::make_pair(m1t3c_start.at(i), m1t3c_end.at(j)));
      cerenIntT4.push_back(std::make_pair(m1t4c_start.at(i), m1t4c_end.at(j)));

      scintIntT1.push_back(std::make_pair(m1t1s_start.at(i), m1t1s_end.at(j)));
      scintIntT2.push_back(std::make_pair(m1t2s_start.at(i), m1t2s_end.at(j)));
      scintIntT3.push_back(std::make_pair(m1t3s_start.at(i), m1t3s_end.at(j)));
      scintIntT4.push_back(std::make_pair(m1t4s_start.at(i), m1t4s_end.at(j)));

      nameVecCT1.push_back("C_"+std::to_string(m1t1c_start.at(i)) + "to" + std::to_string(m1t1c_end.at(j)));
      nameVecCT2.push_back("C_"+std::to_string(m1t2c_start.at(i)) + "to" + std::to_string(m1t2c_end.at(j)));
      nameVecCT3.push_back("C_"+std::to_string(m1t3c_start.at(i)) + "to" + std::to_string(m1t3c_end.at(j)));
      nameVecCT4.push_back("C_"+std::to_string(m1t4c_start.at(i)) + "to" + std::to_string(m1t4c_end.at(j)));

      nameVecST1.push_back("S_"+std::to_string(m1t1s_start.at(i)) + "to" + std::to_string(m1t1s_end.at(j)));
      nameVecST2.push_back("S_"+std::to_string(m1t2s_start.at(i)) + "to" + std::to_string(m1t2s_end.at(j)));
      nameVecST3.push_back("S_"+std::to_string(m1t3s_start.at(i)) + "to" + std::to_string(m1t3s_end.at(j)));
      nameVecST4.push_back("S_"+std::to_string(m1t4s_start.at(i)) + "to" + std::to_string(m1t4s_end.at(j)));

      moduleM1T1C.push_back(new TBhist((TString)"T1_"+nameVecCT1.at(i*m1t1c_end.size() + j), "int. ADC", "events", 1100, -5000., 50000.));
      moduleM1T2C.push_back(new TBhist((TString)"T2_"+nameVecCT2.at(i*m1t2c_end.size() + j), "int. ADC", "events", 1100, -5000., 50000.));
      moduleM1T3C.push_back(new TBhist((TString)"T3_"+nameVecCT3.at(i*m1t3c_end.size() + j), "int. ADC", "events", 1100, -5000., 50000.));
      moduleM1T4C.push_back(new TBhist((TString)"T4_"+nameVecCT4.at(i*m1t4c_end.size() + j), "int. ADC", "events", 1100, -5000., 50000.));

      moduleM1T1S.push_back(new TBhist((TString)"T1_"+nameVecST1.at(i*m1t1c_end.size() + j), "int. ADC", "events", 1100, -5000., 50000.));
      moduleM1T2S.push_back(new TBhist((TString)"T2_"+nameVecST2.at(i*m1t2c_end.size() + j), "int. ADC", "events", 1100, -5000., 50000.));
      moduleM1T3S.push_back(new TBhist((TString)"T3_"+nameVecST3.at(i*m1t3c_end.size() + j), "int. ADC", "events", 1100, -5000., 50000.));
      moduleM1T4S.push_back(new TBhist((TString)"T4_"+nameVecST4.at(i*m1t4c_end.size() + j), "int. ADC", "events", 1100, -5000., 50000.));

      moduleM1T1C_zoom.push_back(new TH1F((TString)"T1_"+nameVecCT1.at(i*m1t1c_end.size() + j) + (TString)"_zoom", ";int. ADC;events", 200, 6000., 14000.));
      moduleM1T2C_zoom.push_back(new TH1F((TString)"T2_"+nameVecCT2.at(i*m1t2c_end.size() + j) + (TString)"_zoom", ";int. ADC;events", 200, 5000., 14000.));
      moduleM1T3C_zoom.push_back(new TH1F((TString)"T3_"+nameVecCT3.at(i*m1t3c_end.size() + j) + (TString)"_zoom", ";int. ADC;events", 200, 4000., 12000.));
      moduleM1T4C_zoom.push_back(new TH1F((TString)"T4_"+nameVecCT4.at(i*m1t4c_end.size() + j) + (TString)"_zoom", ";int. ADC;events", 200, 5000., 14000.));

      moduleM1T1S_zoom.push_back(new TH1F((TString)"T1_"+nameVecST1.at(i*m1t1c_end.size() + j) + (TString)"_zoom", ";int. ADC;events", 200, 9000., 23000.));
      moduleM1T2S_zoom.push_back(new TH1F((TString)"T2_"+nameVecST2.at(i*m1t2c_end.size() + j) + (TString)"_zoom", ";int. ADC;events", 200, 10000., 21000.));
      moduleM1T3S_zoom.push_back(new TH1F((TString)"T3_"+nameVecST3.at(i*m1t3c_end.size() + j) + (TString)"_zoom", ";int. ADC;events", 200, 8000. , 18000.));
      moduleM1T4S_zoom.push_back(new TH1F((TString)"T4_"+nameVecST4.at(i*m1t4c_end.size() + j) + (TString)"_zoom", ";int. ADC;events", 200, 10700., 20300.));
    }
  }



  // TFile* treeFile = new TFile((TString)("/u/user/kyhwang/DRC/Aug2022TB/dev_230307/dual-readout_TB/analysis/Tree/TreeRun" + std::to_string(runNum) + "_RunInfo.root"), "RECREATE");

  // TTree* aTree = new TTree("data", "data");

  float _dwc_1_x, _dwc_1_y, _dwc_2_x, _dwc_2_y;
  float _muADC, _psADC;
  float _m1t1c, _m1t2c, _m1t3c, _m1t4c;
  float _m1t1s, _m1t2s, _m1t3s, _m1t4s;

  // aTree->Branch("dwc_1_x", &_dwc_1_x);
  // aTree->Branch("dwc_1_y", &_dwc_1_y);
  // aTree->Branch("dwc_2_x", &_dwc_2_x);
  // aTree->Branch("dwc_2_y", &_dwc_2_y);

  // aTree->Branch("muADC", &_muADC);
  // aTree->Branch("psADC", &_psADC);

  // aTree->Branch("m1t1c", &_m1t1c);
  // aTree->Branch("m1t2c", &_m1t2c);
  // aTree->Branch("m1t3c", &_m1t3c);
  // aTree->Branch("m1t4c", &_m1t4c);
  
  // aTree->Branch("m1t1s", &_m1t1s);
  // aTree->Branch("m1t2s", &_m1t2s);
  // aTree->Branch("m1t3s", &_m1t3s);
  // aTree->Branch("m1t4s", &_m1t4s);

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

    if ( !dwcSet->inAlign(1.5) )
      continue;

    float psADC = 0;
    float muADC = 0;
    float moduleM1T1Cadc = 0;
    float moduleM1T1Sadc = 0;
    float moduleM1T2Cadc = 0;
    float moduleM1T2Sadc = 0;
    float moduleM1T3Cadc = 0;
    float moduleM1T3Sadc = 0;
    float moduleM1T4Cadc = 0;
    float moduleM1T4Sadc = 0;

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

    psADC = std::accumulate(psWave_ped.begin() + 240, psWave_ped.begin() + 240 + 140, 0.);
    muADC = std::accumulate(muWave_ped.begin() + 820, muWave_ped.begin() + 820 + 130, 0.);

    if ( !(muADC < 2000.) )
      continue;

    if ( !(psADC > 80000.) )
      continue;


    for ( int t = 0; t < 81; t++ ) {

      moduleM1T1C.at(t)->Fill(std::accumulate(moduleM1T1Cwave_ped.begin() + cerenIntT1.at(t).first, moduleM1T1Cwave_ped.begin() + cerenIntT1.at(t).second, 0.));
      moduleM1T2C.at(t)->Fill(std::accumulate(moduleM1T2Cwave_ped.begin() + cerenIntT2.at(t).first, moduleM1T2Cwave_ped.begin() + cerenIntT2.at(t).second, 0.));
      moduleM1T3C.at(t)->Fill(std::accumulate(moduleM1T3Cwave_ped.begin() + cerenIntT3.at(t).first, moduleM1T3Cwave_ped.begin() + cerenIntT3.at(t).second, 0.));
      moduleM1T4C.at(t)->Fill(std::accumulate(moduleM1T4Cwave_ped.begin() + cerenIntT4.at(t).first, moduleM1T4Cwave_ped.begin() + cerenIntT4.at(t).second, 0.));

      moduleM1T1S.at(t)->Fill(std::accumulate(moduleM1T1Swave_ped.begin() + scintIntT1.at(t).first, moduleM1T1Swave_ped.begin() + scintIntT1.at(t).second, 0.));
      moduleM1T2S.at(t)->Fill(std::accumulate(moduleM1T2Swave_ped.begin() + scintIntT2.at(t).first, moduleM1T2Swave_ped.begin() + scintIntT2.at(t).second, 0.));
      moduleM1T3S.at(t)->Fill(std::accumulate(moduleM1T3Swave_ped.begin() + scintIntT3.at(t).first, moduleM1T3Swave_ped.begin() + scintIntT3.at(t).second, 0.));
      moduleM1T4S.at(t)->Fill(std::accumulate(moduleM1T4Swave_ped.begin() + scintIntT4.at(t).first, moduleM1T4Swave_ped.begin() + scintIntT4.at(t).second, 0.));

      moduleM1T1C_zoom.at(t)->Fill(std::accumulate(moduleM1T1Cwave_ped.begin() + cerenIntT1.at(t).first, moduleM1T1Cwave_ped.begin() + cerenIntT1.at(t).second, 0.));
      moduleM1T2C_zoom.at(t)->Fill(std::accumulate(moduleM1T2Cwave_ped.begin() + cerenIntT2.at(t).first, moduleM1T2Cwave_ped.begin() + cerenIntT2.at(t).second, 0.));
      moduleM1T3C_zoom.at(t)->Fill(std::accumulate(moduleM1T3Cwave_ped.begin() + cerenIntT3.at(t).first, moduleM1T3Cwave_ped.begin() + cerenIntT3.at(t).second, 0.));
      moduleM1T4C_zoom.at(t)->Fill(std::accumulate(moduleM1T4Cwave_ped.begin() + cerenIntT4.at(t).first, moduleM1T4Cwave_ped.begin() + cerenIntT4.at(t).second, 0.));

      moduleM1T1S_zoom.at(t)->Fill(std::accumulate(moduleM1T1Swave_ped.begin() + scintIntT1.at(t).first, moduleM1T1Swave_ped.begin() + scintIntT1.at(t).second, 0.));
      moduleM1T2S_zoom.at(t)->Fill(std::accumulate(moduleM1T2Swave_ped.begin() + scintIntT2.at(t).first, moduleM1T2Swave_ped.begin() + scintIntT2.at(t).second, 0.));
      moduleM1T3S_zoom.at(t)->Fill(std::accumulate(moduleM1T3Swave_ped.begin() + scintIntT3.at(t).first, moduleM1T3Swave_ped.begin() + scintIntT3.at(t).second, 0.));
      moduleM1T4S_zoom.at(t)->Fill(std::accumulate(moduleM1T4Swave_ped.begin() + scintIntT4.at(t).first, moduleM1T4Swave_ped.begin() + scintIntT4.at(t).second, 0.));

    }

    // moduleM1T1Cadc = std::accumulate(moduleM1T1Cwave_ped.begin() + 120, moduleM1T1Cwave_ped.begin() + 120 + 100, 0.);
    // moduleM1T1Sadc = std::accumulate(moduleM1T1Swave_ped.begin() + 120, moduleM1T1Swave_ped.begin() + 120 + 110, 0.);

    // moduleM1T2Cadc = std::accumulate(moduleM1T2Cwave_ped.begin() + 120, moduleM1T2Cwave_ped.begin() + 120 + 100, 0.);
    // moduleM1T2Sadc = std::accumulate(moduleM1T2Swave_ped.begin() + 120, moduleM1T2Swave_ped.begin() + 120 + 110, 0.);

    // moduleM1T3Cadc = std::accumulate(moduleM1T3Cwave_ped.begin() + 120, moduleM1T3Cwave_ped.begin() + 120 + 100, 0.);
    // moduleM1T3Sadc = std::accumulate(moduleM1T3Swave_ped.begin() + 120, moduleM1T3Swave_ped.begin() + 120 + 110, 0.);

    // moduleM1T4Cadc = std::accumulate(moduleM1T4Cwave_ped.begin() + 120, moduleM1T4Cwave_ped.begin() + 120 + 100, 0.);
    // moduleM1T4Sadc = std::accumulate(moduleM1T4Swave_ped.begin() + 120, moduleM1T4Swave_ped.begin() + 120 + 110, 0.);

    // _dwc_1_x = dwc_pos.at(0);
    // _dwc_1_y = dwc_pos.at(1);
    // _dwc_2_x = dwc_pos.at(2);
    // _dwc_2_y = dwc_pos.at(3);

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

    // aTree->Fill();


  }
  loader->close();

  // treeFile->cd();
  // aTree->Write();
  // treeFile->Close();

  TCanvas* c = new TCanvas("", "");


  if (runNum == 702) {

    for ( int i = 0; i < 81; i++ ) {
      c->cd();

      moduleM1T1C.at(i)->getHist()->Draw();
      c->SaveAs("/u/user/kyhwang/DRC/Aug2022TB/dev_230307/dual-readout_TB/analysis/AvgTime/230321_pngs/T1/"+(TString)moduleM1T1C.at(i)->getHist()->GetName()+".png");
      moduleM1T1S.at(i)->getHist()->Draw();
      c->SaveAs("/u/user/kyhwang/DRC/Aug2022TB/dev_230307/dual-readout_TB/analysis/AvgTime/230321_pngs/T1/"+(TString)moduleM1T1S.at(i)->getHist()->GetName()+".png");
      moduleM1T1C_zoom.at(i)->Draw();
      c->SaveAs("/u/user/kyhwang/DRC/Aug2022TB/dev_230307/dual-readout_TB/analysis/AvgTime/230321_pngs/T1/Zoom"+(TString)moduleM1T1C_zoom.at(i)->GetName()+".png");
      moduleM1T1S_zoom.at(i)->Draw();
      c->SaveAs("/u/user/kyhwang/DRC/Aug2022TB/dev_230307/dual-readout_TB/analysis/AvgTime/230321_pngs/T1/Zoom"+(TString)moduleM1T1S_zoom.at(i)->GetName()+".png");
    }
  }

  if (runNum == 624) {

    for ( int i = 0; i < 81; i++ ) {
      c->cd();

      moduleM1T2C.at(i)->getHist()->Draw();
      c->SaveAs("/u/user/kyhwang/DRC/Aug2022TB/dev_230307/dual-readout_TB/analysis/AvgTime/230321_pngs/T2/"+(TString)moduleM1T2C.at(i)->getHist()->GetName()+".png");
      moduleM1T2S.at(i)->getHist()->Draw();
      c->SaveAs("/u/user/kyhwang/DRC/Aug2022TB/dev_230307/dual-readout_TB/analysis/AvgTime/230321_pngs/T2/"+(TString)moduleM1T2S.at(i)->getHist()->GetName()+".png");
      moduleM1T2C_zoom.at(i)->Draw();
      c->SaveAs("/u/user/kyhwang/DRC/Aug2022TB/dev_230307/dual-readout_TB/analysis/AvgTime/230321_pngs/T2/Zoom"+(TString)moduleM1T2C_zoom.at(i)->GetName()+".png");
      moduleM1T2S_zoom.at(i)->Draw();
      c->SaveAs("/u/user/kyhwang/DRC/Aug2022TB/dev_230307/dual-readout_TB/analysis/AvgTime/230321_pngs/T2/Zoom"+(TString)moduleM1T2S_zoom.at(i)->GetName()+".png");
    }
  }

  if (runNum == 700) {

    for ( int i = 0; i < 81; i++ ) {
      c->cd();

      moduleM1T3C.at(i)->getHist()->Draw();
      c->SaveAs("/u/user/kyhwang/DRC/Aug2022TB/dev_230307/dual-readout_TB/analysis/AvgTime/230321_pngs/T3/"+(TString)moduleM1T3C.at(i)->getHist()->GetName()+".png");
      moduleM1T3S.at(i)->getHist()->Draw();
      c->SaveAs("/u/user/kyhwang/DRC/Aug2022TB/dev_230307/dual-readout_TB/analysis/AvgTime/230321_pngs/T3/"+(TString)moduleM1T3S.at(i)->getHist()->GetName()+".png");
      moduleM1T3C_zoom.at(i)->Draw();
      c->SaveAs("/u/user/kyhwang/DRC/Aug2022TB/dev_230307/dual-readout_TB/analysis/AvgTime/230321_pngs/T3/Zoom"+(TString)moduleM1T3C_zoom.at(i)->GetName()+".png");
      moduleM1T3S_zoom.at(i)->Draw();
      c->SaveAs("/u/user/kyhwang/DRC/Aug2022TB/dev_230307/dual-readout_TB/analysis/AvgTime/230321_pngs/T3/Zoom"+(TString)moduleM1T3S_zoom.at(i)->GetName()+".png");
    }
  }

  if (runNum == 704) {

    for ( int i = 0; i < 81; i++ ) {
      c->cd();

      moduleM1T4C.at(i)->getHist()->Draw();
      c->SaveAs("/u/user/kyhwang/DRC/Aug2022TB/dev_230307/dual-readout_TB/analysis/AvgTime/230321_pngs/T4/"+(TString)moduleM1T4C.at(i)->getHist()->GetName()+".png");
      moduleM1T4S.at(i)->getHist()->Draw();
      c->SaveAs("/u/user/kyhwang/DRC/Aug2022TB/dev_230307/dual-readout_TB/analysis/AvgTime/230321_pngs/T4/"+(TString)moduleM1T4S.at(i)->getHist()->GetName()+".png");
      moduleM1T4C_zoom.at(i)->Draw();
      c->SaveAs("/u/user/kyhwang/DRC/Aug2022TB/dev_230307/dual-readout_TB/analysis/AvgTime/230321_pngs/T4/Zoom"+(TString)moduleM1T4C_zoom.at(i)->GetName()+".png");
      moduleM1T4S_zoom.at(i)->Draw();
      c->SaveAs("/u/user/kyhwang/DRC/Aug2022TB/dev_230307/dual-readout_TB/analysis/AvgTime/230321_pngs/T4/Zoom"+(TString)moduleM1T4S_zoom.at(i)->GetName()+".png");
    }
  }

  TFile* outputFile = new TFile((TString)("/u/user/kyhwang/DRC/Aug2022TB/dev_230307/dual-readout_TB/analysis/AvgTime/TreeRun" + std::to_string(runNum) + "_RunInfo.root"), "RECREATE");
  outputFile->cd();

  double stdDevInt = 0;
  double resInt = 0;

  double stdDevRef = 0;
  double resRef = 0;

  std::vector<TBhist*> plotCcollection;
  std::vector<TBhist*> plotScollection;
  std::vector<TH1F*> plotCcollectionZoom;
  std::vector<TH1F*> plotScollectionZoom;

  if (runNum == 702) {
    plotCcollection = moduleM1T1C;
    plotScollection = moduleM1T1S;
    plotCcollectionZoom = moduleM1T1C_zoom;
    plotScollectionZoom = moduleM1T1S_zoom;
  }

  if (runNum == 624) {
    plotCcollection = moduleM1T2C;
    plotScollection = moduleM1T2S;
    plotCcollectionZoom = moduleM1T2C_zoom;
    plotScollectionZoom = moduleM1T2S_zoom;
  }

  if (runNum == 700) {
    plotCcollection = moduleM1T3C;
    plotScollection = moduleM1T3S;
    plotCcollectionZoom = moduleM1T3C_zoom;
    plotScollectionZoom = moduleM1T3S_zoom;
  }

  if (runNum == 704) {
    plotCcollection = moduleM1T4C;
    plotScollection = moduleM1T4S;
    plotCcollectionZoom = moduleM1T4C_zoom;
    plotScollectionZoom = moduleM1T4S_zoom;
  }


  for ( int t = 0; t < 81; t++ ) {
    plotCcollection.at(t)->getHist()->Write();
    plotScollection.at(t)->getHist()->Write();
    plotCcollectionZoom.at(t)->Write();
    plotScollectionZoom.at(t)->Write();
  }


  stdDevInt = 0;
  resInt = 0;
  stdDevRef = plotCcollectionZoom.at(0)->GetStdDev();
  resRef = plotCcollectionZoom.at(0)->GetStdDev() / plotCcollectionZoom.at(0)->GetMean();

  for ( int i = 0; i < 81; i++ ) {
    std::cout << plotCcollectionZoom.at(i)->GetName() << " " << plotCcollectionZoom.at(i)->GetStdDev() << " " << plotCcollectionZoom.at(i)->GetStdDev() / plotCcollectionZoom.at(i)->GetMean() << std::endl;

    if ( stdDevRef > plotCcollectionZoom.at(i)->GetStdDev() ) {
      stdDevRef = plotCcollectionZoom.at(i)->GetStdDev();
      stdDevInt = i;
    }

    if ( resRef > plotCcollectionZoom.at(i)->GetStdDev() / plotCcollectionZoom.at(i)->GetMean() ) {
      resRef = plotCcollectionZoom.at(i)->GetStdDev() / plotCcollectionZoom.at(i)->GetMean();
      resInt = i;
    }
  }
  std::cout << " " << std::endl;
  std::cout << " C : Std dev - " << plotCcollectionZoom.at(stdDevInt)->GetName() << " | Res - " << plotCcollectionZoom.at(resInt)->GetName() << std::endl;


  stdDevInt = 0;
  resInt = 0;
  stdDevRef = plotScollectionZoom.at(0)->GetStdDev();
  resRef = plotScollectionZoom.at(0)->GetStdDev() / plotScollectionZoom.at(0)->GetMean();

  std::cout << " " << std::endl;
  for ( int i = 0; i < 81; i++ ) {
    std::cout << plotScollectionZoom.at(i)->GetName() << " " << plotScollectionZoom.at(i)->GetStdDev() << " " << plotScollectionZoom.at(i)->GetStdDev() / plotScollectionZoom.at(i)->GetMean() << std::endl;

    if ( stdDevRef > plotScollectionZoom.at(i)->GetStdDev() ) {
      stdDevRef = plotScollectionZoom.at(i)->GetStdDev();
      stdDevInt = i;
    }

    if ( resRef > plotScollectionZoom.at(i)->GetStdDev() / plotScollectionZoom.at(i)->GetMean() ) {
      resRef = plotScollectionZoom.at(i)->GetStdDev() / plotScollectionZoom.at(i)->GetMean();
      resInt = i;
    }
  }
  std::cout << " " << std::endl;
  std::cout << " S : Std dev - " << plotScollectionZoom.at(stdDevInt)->GetName() << " | Res - " << plotScollectionZoom.at(resInt)->GetName() << std::endl;
  
  outputFile->Close();

  return 0;
}
