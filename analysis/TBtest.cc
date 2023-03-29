#include <stdexcept>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
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

  std::ifstream in;
  int run_num;
  std::vector<int> jobCol;
  in.open("jobcollection.txt",std::ios::in);
  while (true) {
    in >> run_num;
    if (!in.good()) break;
    jobCol.push_back(run_num);
  }
  in.close();

  TFile* pedCollection = new TFile("ped.root", "RECREATE");

  TTree* pedTree = new TTree("data", "data");

  float dwc1R;
  float dwc1L;
  float dwc1U;
  float dwc1D;
  float dwc2R;
  float dwc2L;
  float dwc2U;
  float dwc2D;

  pedTree->Branch("dwc1R", &dwc1R);
  pedTree->Branch("dwc1L", &dwc1L);
  pedTree->Branch("dwc1U", &dwc1U);
  pedTree->Branch("dwc1D", &dwc1D);
  pedTree->Branch("dwc2R", &dwc2R);
  pedTree->Branch("dwc2L", &dwc2L);
  pedTree->Branch("dwc2U", &dwc2U);
  pedTree->Branch("dwc2D", &dwc2D);

  std::vector<TH1D*> pedHistCol;
  TH1D* dwc_1_r_hist = new TH1D("dwc_1_R", "", 100, 3550., 3650.);
  TH1D* dwc_1_l_hist = new TH1D("dwc_1_L", "", 100, 3550., 3650.);
  TH1D* dwc_1_u_hist = new TH1D("dwc_1_U", "", 100, 3550., 3650.);
  TH1D* dwc_1_d_hist = new TH1D("dwc_1_D", "", 100, 3550., 3650.);
  TH1D* dwc_2_r_hist = new TH1D("dwc_2_R", "", 100, 3550., 3650.);
  TH1D* dwc_2_l_hist = new TH1D("dwc_2_L", "", 100, 3550., 3650.);
  TH1D* dwc_2_u_hist = new TH1D("dwc_2_U", "", 100, 3550., 3650.);
  TH1D* dwc_2_d_hist = new TH1D("dwc_2_D", "", 100, 3550., 3650.);

  for ( int run : jobCol ) {

    DWCset<TBwaveform>* dwcSet = new DWCset<TBwaveform>(run, dwc_calib);
    dwcSet->print();

    // std::string pedPath = "dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/khwang/Aug2022TB/RunInfo/pedestal/mean/Run" + std::to_string(run) + "_pedestalHist_mean.root";
    
    // TButility utility = TButility();
    // utility.loadped(pedPath);

    // std::cout << run << " " 
    //           << utility.retrievePed(TBcid(1,17)) << " "
    //           << utility.retrievePed(TBcid(1,19)) << " "
    //           << utility.retrievePed(TBcid(1,21)) << " "
    //           << utility.retrievePed(TBcid(1,23)) << " "
    //           << utility.retrievePed(TBcid(1,25)) << " "
    //           << utility.retrievePed(TBcid(1,27)) << " "
    //           << utility.retrievePed(TBcid(1,29)) << " "
    //           << utility.retrievePed(TBcid(1,31)) << " "
    //           << std::endl;

    // dwc1R = utility.retrievePed(TBcid(1,17));
    // dwc1L = utility.retrievePed(TBcid(1,19));
    // dwc1U = utility.retrievePed(TBcid(1,21));
    // dwc1D = utility.retrievePed(TBcid(1,23));
    // dwc2R = utility.retrievePed(TBcid(1,25));
    // dwc2L = utility.retrievePed(TBcid(1,27));
    // dwc2U = utility.retrievePed(TBcid(1,29));
    // dwc2D = utility.retrievePed(TBcid(1,31));

    // dwc_1_r_hist->Fill(dwc1R);
    // dwc_1_l_hist->Fill(dwc1L);
    // dwc_1_u_hist->Fill(dwc1U);
    // dwc_1_d_hist->Fill(dwc1D);
    // dwc_2_r_hist->Fill(dwc2R);
    // dwc_2_l_hist->Fill(dwc2L);
    // dwc_2_u_hist->Fill(dwc2U);
    // dwc_2_d_hist->Fill(dwc2D);

    pedTree->Fill();

  }

  // for ( int i = 0; i < 8; i++ )  
  // std::cout << " 0 : " << dwc_1_r_hist->GetBinCenter(dwc_1_r_hist->GetMaximumBin()) << std::endl;
  // std::cout << " 1 : " << dwc_1_l_hist->GetBinCenter(dwc_1_l_hist->GetMaximumBin()) << std::endl;
  // std::cout << " 2 : " << dwc_1_u_hist->GetBinCenter(dwc_1_u_hist->GetMaximumBin()) << std::endl;
  // std::cout << " 3 : " << dwc_1_d_hist->GetBinCenter(dwc_1_d_hist->GetMaximumBin()) << std::endl;
  // std::cout << " 4 : " << dwc_2_r_hist->GetBinCenter(dwc_2_r_hist->GetMaximumBin()) << std::endl;
  // std::cout << " 5 : " << dwc_2_l_hist->GetBinCenter(dwc_2_l_hist->GetMaximumBin()) << std::endl;
  // std::cout << " 6 : " << dwc_2_u_hist->GetBinCenter(dwc_2_u_hist->GetMaximumBin()) << std::endl;
  // std::cout << " 7 : " << dwc_2_d_hist->GetBinCenter(dwc_2_d_hist->GetMaximumBin()) << std::endl;

  // pedCollection->cd();
  // pedTree->Write();
  // pedCollection->Close();


  // TCanvas* c = new TCanvas("", "");

  // c->cd();

  // pedHistCol.at(0)->Draw("Hist");
  // c->SaveAs("Ped_dwc1R.png");

  // pedHistCol.at(1)->Draw("Hist");
  // c->SaveAs("Ped_dwc1L.png");

  // pedHistCol.at(2)->Draw("Hist");
  // c->SaveAs("Ped_dwc1U.png");

  // pedHistCol.at(3)->Draw("Hist");
  // c->SaveAs("Ped_dwc1D.png");

  // pedHistCol.at(4)->Draw("Hist");
  // c->SaveAs("Ped_dwc2R.png");

  // pedHistCol.at(5)->Draw("Hist");
  // c->SaveAs("Ped_dwc2L.png");

  // pedHistCol.at(6)->Draw("Hist");
  // c->SaveAs("Ped_dwc2U.png");

  // pedHistCol.at(7)->Draw("Hist");
  // c->SaveAs("Ped_dwc2D.png");

  return 0;
}
