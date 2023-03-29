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
  TBcid tccid = utility.getcid(TBdetector::detid::tail);

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


  TH1D* psAvgTime = new TH1D("psAvgTime", "", 1024, 0., 1024.); psAvgTime->Sumw2();
  TH1D* muAvgTime = new TH1D("muAvgTime", "", 1024, 0., 1024.); muAvgTime->Sumw2();
  TH1D* tcAvgTime = new TH1D("tcAvgTime", "", 1024, 0., 1024.); tcAvgTime->Sumw2();

  TH2D* psAccuTime = new TH2D("psAccuTime", "", 1024, 0., 1024., 4096, 0., 4096.); psAccuTime->Sumw2();
  TH2D* muAccuTime = new TH2D("muAccuTime", "", 1024, 0., 1024., 4096, 0., 4096.); muAccuTime->Sumw2();
  TH2D* tcAccuTime = new TH2D("tcAccuTime", "", 1024, 0., 1024., 4096, 0., 4096.); tcAccuTime->Sumw2();

  std::vector<TH1D*> moduleM1TCavgTimeStructure;
  moduleM1TCavgTimeStructure.reserve(4);
  moduleM1TCavgTimeStructure.emplace_back(new TH1D("m1t1CAvgTime", "M1T1 C avg. Time Structure;bin [0.4ns/bin];ADC", 1024, 0., 1024.)); moduleM1TCavgTimeStructure.at(0)->Sumw2();
  moduleM1TCavgTimeStructure.emplace_back(new TH1D("m1t2CAvgTime", "M1T2 C avg. Time Structure;bin [0.4ns/bin];ADC", 1024, 0., 1024.)); moduleM1TCavgTimeStructure.at(1)->Sumw2();
  moduleM1TCavgTimeStructure.emplace_back(new TH1D("m1t3CAvgTime", "M1T3 C avg. Time Structure;bin [0.4ns/bin];ADC", 1024, 0., 1024.)); moduleM1TCavgTimeStructure.at(2)->Sumw2();
  moduleM1TCavgTimeStructure.emplace_back(new TH1D("m1t4CAvgTime", "M1T4 C avg. Time Structure;bin [0.4ns/bin];ADC", 1024, 0., 1024.)); moduleM1TCavgTimeStructure.at(3)->Sumw2();

  std::vector<TH1D*> moduleM1TSavgTimeStructure;
  moduleM1TSavgTimeStructure.reserve(4);
  moduleM1TSavgTimeStructure.emplace_back(new TH1D("m1t1SAvgTime", "M1T1 S avg. Time Structure;bin [0.4ns/bin];ADC", 1024, 0., 1024.)); moduleM1TSavgTimeStructure.at(0)->Sumw2();
  moduleM1TSavgTimeStructure.emplace_back(new TH1D("m1t2SAvgTime", "M1T2 S avg. Time Structure;bin [0.4ns/bin];ADC", 1024, 0., 1024.)); moduleM1TSavgTimeStructure.at(1)->Sumw2();
  moduleM1TSavgTimeStructure.emplace_back(new TH1D("m1t3SAvgTime", "M1T3 S avg. Time Structure;bin [0.4ns/bin];ADC", 1024, 0., 1024.)); moduleM1TSavgTimeStructure.at(2)->Sumw2();
  moduleM1TSavgTimeStructure.emplace_back(new TH1D("m1t4SAvgTime", "M1T4 S avg. Time Structure;bin [0.4ns/bin];ADC", 1024, 0., 1024.)); moduleM1TSavgTimeStructure.at(3)->Sumw2();

  std::vector<TH2D*> moduleM1TCaccuTimeStructure;
  moduleM1TCaccuTimeStructure.reserve(4);
  moduleM1TCaccuTimeStructure.emplace_back(new TH2D("m1t1CAccuTime", "M1T1 C accu. Time Structure;bin [0.4ns/bin];ADC", 1024, 0., 1024., 4096, 0., 4096.)); moduleM1TCaccuTimeStructure.at(0)->Sumw2();
  moduleM1TCaccuTimeStructure.emplace_back(new TH2D("m1t2CAccuTime", "M1T2 C accu. Time Structure;bin [0.4ns/bin];ADC", 1024, 0., 1024., 4096, 0., 4096.)); moduleM1TCaccuTimeStructure.at(1)->Sumw2();
  moduleM1TCaccuTimeStructure.emplace_back(new TH2D("m1t3CAccuTime", "M1T3 C accu. Time Structure;bin [0.4ns/bin];ADC", 1024, 0., 1024., 4096, 0., 4096.)); moduleM1TCaccuTimeStructure.at(2)->Sumw2();
  moduleM1TCaccuTimeStructure.emplace_back(new TH2D("m1t4CAccuTime", "M1T4 C accu. Time Structure;bin [0.4ns/bin];ADC", 1024, 0., 1024., 4096, 0., 4096.)); moduleM1TCaccuTimeStructure.at(3)->Sumw2();

  std::vector<TH2D*> moduleM1TSaccuTimeStructure;
  moduleM1TSaccuTimeStructure.reserve(4);
  moduleM1TSaccuTimeStructure.emplace_back(new TH2D("m1t1SAccuTime", "M1T1 S accu. Time Structure;bin [0.4ns/bin];ADC", 1024, 0., 1024., 4096, 0., 4096.)); moduleM1TSaccuTimeStructure.at(0)->Sumw2();
  moduleM1TSaccuTimeStructure.emplace_back(new TH2D("m1t2SAccuTime", "M1T2 S accu. Time Structure;bin [0.4ns/bin];ADC", 1024, 0., 1024., 4096, 0., 4096.)); moduleM1TSaccuTimeStructure.at(1)->Sumw2();
  moduleM1TSaccuTimeStructure.emplace_back(new TH2D("m1t3SAccuTime", "M1T3 S accu. Time Structure;bin [0.4ns/bin];ADC", 1024, 0., 1024., 4096, 0., 4096.)); moduleM1TSaccuTimeStructure.at(2)->Sumw2();
  moduleM1TSaccuTimeStructure.emplace_back(new TH2D("m1t4SAccuTime", "M1T4 S accu. Time Structure;bin [0.4ns/bin];ADC", 1024, 0., 1024., 4096, 0., 4096.)); moduleM1TSaccuTimeStructure.at(3)->Sumw2();


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
    TBwaveform adata_tc = anEvt->data(tccid);

    std::vector<TBwaveform> setDWC1;
    for ( int i = 0; i < dwc1.size(); i++ )
      setDWC1.push_back(anEvt->data(dwc1.at(i)));

    std::vector<TBwaveform> setDWC2;
    for ( int i = 0; i < dwc2.size(); i++ )
      setDWC2.push_back(anEvt->data(dwc2.at(i)));

    // std::vector<TBwaveform> M1TC_data;
    // std::vector<TBwaveform> M1TS_data;
    // for ( int i = 0; i < M1TC.size(); i++ ) {
    //   M1TC_data.push_back(anEvt->data(M1TC.at(i)));
    //   M1TS_data.push_back(anEvt->data(M1TS.at(i)));
    // }

    dwcSet->SetDWC(setDWC1, setDWC2);
    auto dwc_pos = dwcSet->GetPosition();

    auto psWave_origin = adata_ps.waveform();
    auto muWave_origin = adata_mu.waveform();
    auto tcWave_origin = adata_tc.waveform();

    // auto moduleM1T1Cwave_origin = M1TC_data.at(0).waveform();
    // auto moduleM1T1Swave_origin = M1TS_data.at(0).waveform();

    // auto moduleM1T2Cwave_origin = M1TC_data.at(1).waveform();
    // auto moduleM1T2Swave_origin = M1TS_data.at(1).waveform();

    // auto moduleM1T3Cwave_origin = M1TC_data.at(2).waveform();
    // auto moduleM1T3Swave_origin = M1TS_data.at(2).waveform();

    // auto moduleM1T4Cwave_origin = M1TC_data.at(3).waveform();
    // auto moduleM1T4Swave_origin = M1TS_data.at(3).waveform();

    if ( !dwcSet->inAlign(1.5) ) {
    // if ( true ) {
      continue;
    }

    selEvent++;

    for ( int i = 0; i < 1024; i++ ) {
      psAccuTime->Fill(i, psWave_origin.at(i));
      muAccuTime->Fill(i, muWave_origin.at(i));
      tcAccuTime->Fill(i, tcWave_origin.at(i));

      psAvgTime->Fill(i, psWave_origin.at(i));
      muAvgTime->Fill(i, muWave_origin.at(i));
      tcAvgTime->Fill(i, tcWave_origin.at(i));

      // moduleM1TCaccuTimeStructure.at(0)->Fill(i, moduleM1T1Cwave_origin.at(i));
      // moduleM1TSaccuTimeStructure.at(0)->Fill(i, moduleM1T1Swave_origin.at(i));
      // moduleM1TCaccuTimeStructure.at(1)->Fill(i, moduleM1T2Cwave_origin.at(i));
      // moduleM1TSaccuTimeStructure.at(1)->Fill(i, moduleM1T2Swave_origin.at(i));
      // moduleM1TCaccuTimeStructure.at(2)->Fill(i, moduleM1T3Cwave_origin.at(i));
      // moduleM1TSaccuTimeStructure.at(2)->Fill(i, moduleM1T3Swave_origin.at(i));
      // moduleM1TCaccuTimeStructure.at(3)->Fill(i, moduleM1T4Cwave_origin.at(i));
      // moduleM1TSaccuTimeStructure.at(3)->Fill(i, moduleM1T4Swave_origin.at(i));

      // moduleM1TCavgTimeStructure.at(0)->Fill(i, moduleM1T1Cwave_origin.at(i));
      // moduleM1TSavgTimeStructure.at(0)->Fill(i, moduleM1T1Swave_origin.at(i));
      // moduleM1TCavgTimeStructure.at(1)->Fill(i, moduleM1T2Cwave_origin.at(i));
      // moduleM1TSavgTimeStructure.at(1)->Fill(i, moduleM1T2Swave_origin.at(i));
      // moduleM1TCavgTimeStructure.at(2)->Fill(i, moduleM1T3Cwave_origin.at(i));
      // moduleM1TSavgTimeStructure.at(2)->Fill(i, moduleM1T3Swave_origin.at(i));
      // moduleM1TCavgTimeStructure.at(3)->Fill(i, moduleM1T4Cwave_origin.at(i));
      // moduleM1TSavgTimeStructure.at(3)->Fill(i, moduleM1T4Swave_origin.at(i));
    }
  }
  loader->close();

  psAvgTime->Scale(1./selEvent);
  muAvgTime->Scale(1./selEvent);
  tcAvgTime->Scale(1./selEvent);

  // for ( int i = 0; i < 4; i++ ) {
  //   moduleM1TCavgTimeStructure.at(i)->Scale(1./selEvent);
  //   moduleM1TSavgTimeStructure.at(i)->Scale(1./selEvent);
  // }

  for ( int i = 0; i < 1024; i++ ) {
    psAvgTime->SetBinError(i+1, 1e-10);
    muAvgTime->SetBinError(i+1, 1e-10);
    tcAvgTime->SetBinError(i+1, 1e-10);
    
    // for ( int j = 0; j < 4; j++ ) {
    //   moduleM1TCavgTimeStructure.at(j)->SetBinError(i+1, 1e-10);
    //   moduleM1TSavgTimeStructure.at(j)->SetBinError(i+1, 1e-10);
    // }
  }

  TFile* rootOutput = new TFile((TString)("/u/user/kyhwang/scratch/WorkSpace/DRC/Aug2022TB/dev_230307/dual-readout_TB/analysis/AvgTime/Run" + std::to_string(runNum) + "_AuxTimeInfo.root"), "RECREATE");
  rootOutput->cd();

  psAccuTime->Write();
  muAccuTime->Write();
  tcAccuTime->Write();

  // moduleM1TCaccuTimeStructure.at(0)->Write();
  // moduleM1TCaccuTimeStructure.at(1)->Write();
  // moduleM1TCaccuTimeStructure.at(2)->Write();
  // moduleM1TCaccuTimeStructure.at(3)->Write();

  // moduleM1TSaccuTimeStructure.at(0)->Write();
  // moduleM1TSaccuTimeStructure.at(1)->Write();
  // moduleM1TSaccuTimeStructure.at(2)->Write();
  // moduleM1TSaccuTimeStructure.at(3)->Write();

  psAvgTime->Write();
  muAvgTime->Write();
  tcAvgTime->Write();

  // moduleM1TCavgTimeStructure.at(0)->Write();
  // moduleM1TCavgTimeStructure.at(1)->Write();
  // moduleM1TCavgTimeStructure.at(2)->Write();
  // moduleM1TCavgTimeStructure.at(3)->Write();

  // moduleM1TSavgTimeStructure.at(0)->Write();
  // moduleM1TSavgTimeStructure.at(1)->Write();
  // moduleM1TSavgTimeStructure.at(2)->Write();
  // moduleM1TSavgTimeStructure.at(3)->Write();


  rootOutput->Close();

  return 0;
}
