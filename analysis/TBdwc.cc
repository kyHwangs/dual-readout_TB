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

  AuxFactory<TBwaveform>* auxFac = new AuxFactory<TBwaveform>(runNum, 2.5);
  DWCset<TBwaveform>* dwcSet = new DWCset<TBwaveform>(runNum, dwc_calib, 1.);

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

  std::vector<float> dwc_ped = {3646.5, 3622.5, 3632.5, 3633.5, 3614.5, 3587.5, 3618.5, 3617.5};

  if ( maxEvents == -1 )
    maxEvents = loader->getEntries();

  if ( maxEvents > loader->getEntries() )
    throw std::runtime_error("Events number is larger than entries !");

  std::chrono::time_point time_begin = std::chrono::system_clock::now(); //delete
  printf("\n");

  // TFile* treeFile = new TFile((TString)("/u/user/kyhwang/scratch/WorkSpace/DRC/Aug2022TB/dev_230307/dual-readout_TB/analysis/DWC_le_20/root/DWC_Run" + std::to_string(runNum) + "_RunInfo.root"), "RECREATE");

  // TTree* aTree = new TTree("data", "data");

  // float _dwc_1_x, _dwc_1_y, _dwc_2_x, _dwc_2_y;

  // aTree->Branch("dwc_1_x", &_dwc_1_x);
  // aTree->Branch("dwc_1_y", &_dwc_1_y);
  // aTree->Branch("dwc_2_x", &_dwc_2_x);
  // aTree->Branch("dwc_2_y", &_dwc_2_y);

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

    std::vector<TBwaveform> setDWC1;
    for ( int i = 0; i < dwc1.size(); i++ )
      setDWC1.push_back(anEvt->data(dwc1.at(i)));

    std::vector<TBwaveform> setDWC2;
    for ( int i = 0; i < dwc2.size(); i++ )
      setDWC2.push_back(anEvt->data(dwc2.at(i)));

    dwcSet->SetDWC(setDWC1, setDWC2, dwc_ped);
    auto dwc_pos = dwcSet->GetPosition();

    // _dwc_1_x = dwc_pos.at(0);
    // _dwc_1_y = dwc_pos.at(1);
    // _dwc_2_x = dwc_pos.at(2);
    // _dwc_2_y = dwc_pos.at(3);

    // aTree->Fill();
  }
  // loader->close();

  // treeFile->cd();
  // aTree->Write();
  // treeFile->Close();

  return 0;
}
