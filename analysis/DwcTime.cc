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
// #include "list.h"

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


  TTree* aTree = new TTree("data", "data");

  float _dwc_1_R_fast, _dwc_1_L_fast, _dwc_2_R_fast, _dwc_2_L_fast;
  float _dwc_1_U_fast, _dwc_1_D_fast, _dwc_2_U_fast, _dwc_2_D_fast;


  float _dwc_1_R_wave0p1, _dwc_1_L_wave0p1, _dwc_2_R_wave0p1, _dwc_2_L_wave0p1, _dwc_1_R_vsFast0p1, _dwc_1_L_vsFast0p1, _dwc_2_R_vsFast0p1, _dwc_2_L_vsFast0p1;
  float _dwc_1_R_wave0p2, _dwc_1_L_wave0p2, _dwc_2_R_wave0p2, _dwc_2_L_wave0p2, _dwc_1_R_vsFast0p2, _dwc_1_L_vsFast0p2, _dwc_2_R_vsFast0p2, _dwc_2_L_vsFast0p2;
  float _dwc_1_R_wave0p3, _dwc_1_L_wave0p3, _dwc_2_R_wave0p3, _dwc_2_L_wave0p3, _dwc_1_R_vsFast0p3, _dwc_1_L_vsFast0p3, _dwc_2_R_vsFast0p3, _dwc_2_L_vsFast0p3;
  float _dwc_1_R_wave0p4, _dwc_1_L_wave0p4, _dwc_2_R_wave0p4, _dwc_2_L_wave0p4, _dwc_1_R_vsFast0p4, _dwc_1_L_vsFast0p4, _dwc_2_R_vsFast0p4, _dwc_2_L_vsFast0p4;
  float _dwc_1_R_wave0p5, _dwc_1_L_wave0p5, _dwc_2_R_wave0p5, _dwc_2_L_wave0p5, _dwc_1_R_vsFast0p5, _dwc_1_L_vsFast0p5, _dwc_2_R_vsFast0p5, _dwc_2_L_vsFast0p5;
  float _dwc_1_R_wave0p6, _dwc_1_L_wave0p6, _dwc_2_R_wave0p6, _dwc_2_L_wave0p6, _dwc_1_R_vsFast0p6, _dwc_1_L_vsFast0p6, _dwc_2_R_vsFast0p6, _dwc_2_L_vsFast0p6;
  float _dwc_1_R_wave0p7, _dwc_1_L_wave0p7, _dwc_2_R_wave0p7, _dwc_2_L_wave0p7, _dwc_1_R_vsFast0p7, _dwc_1_L_vsFast0p7, _dwc_2_R_vsFast0p7, _dwc_2_L_vsFast0p7;
  float _dwc_1_R_wave0p8, _dwc_1_L_wave0p8, _dwc_2_R_wave0p8, _dwc_2_L_wave0p8, _dwc_1_R_vsFast0p8, _dwc_1_L_vsFast0p8, _dwc_2_R_vsFast0p8, _dwc_2_L_vsFast0p8;
  float _dwc_1_R_wave0p9, _dwc_1_L_wave0p9, _dwc_2_R_wave0p9, _dwc_2_L_wave0p9, _dwc_1_R_vsFast0p9, _dwc_1_L_vsFast0p9, _dwc_2_R_vsFast0p9, _dwc_2_L_vsFast0p9;
  float _dwc_1_R_wave1p0, _dwc_1_L_wave1p0, _dwc_2_R_wave1p0, _dwc_2_L_wave1p0, _dwc_1_R_vsFast1p0, _dwc_1_L_vsFast1p0, _dwc_2_R_vsFast1p0, _dwc_2_L_vsFast1p0;

  float _dwc_1_U_wave0p1, _dwc_1_D_wave0p1, _dwc_2_U_wave0p1, _dwc_2_D_wave0p1, _dwc_1_U_vsFast0p1, _dwc_1_D_vsFast0p1, _dwc_2_U_vsFast0p1, _dwc_2_D_vsFast0p1;
  float _dwc_1_U_wave0p2, _dwc_1_D_wave0p2, _dwc_2_U_wave0p2, _dwc_2_D_wave0p2, _dwc_1_U_vsFast0p2, _dwc_1_D_vsFast0p2, _dwc_2_U_vsFast0p2, _dwc_2_D_vsFast0p2;
  float _dwc_1_U_wave0p3, _dwc_1_D_wave0p3, _dwc_2_U_wave0p3, _dwc_2_D_wave0p3, _dwc_1_U_vsFast0p3, _dwc_1_D_vsFast0p3, _dwc_2_U_vsFast0p3, _dwc_2_D_vsFast0p3;
  float _dwc_1_U_wave0p4, _dwc_1_D_wave0p4, _dwc_2_U_wave0p4, _dwc_2_D_wave0p4, _dwc_1_U_vsFast0p4, _dwc_1_D_vsFast0p4, _dwc_2_U_vsFast0p4, _dwc_2_D_vsFast0p4;
  float _dwc_1_U_wave0p5, _dwc_1_D_wave0p5, _dwc_2_U_wave0p5, _dwc_2_D_wave0p5, _dwc_1_U_vsFast0p5, _dwc_1_D_vsFast0p5, _dwc_2_U_vsFast0p5, _dwc_2_D_vsFast0p5;
  float _dwc_1_U_wave0p6, _dwc_1_D_wave0p6, _dwc_2_U_wave0p6, _dwc_2_D_wave0p6, _dwc_1_U_vsFast0p6, _dwc_1_D_vsFast0p6, _dwc_2_U_vsFast0p6, _dwc_2_D_vsFast0p6;
  float _dwc_1_U_wave0p7, _dwc_1_D_wave0p7, _dwc_2_U_wave0p7, _dwc_2_D_wave0p7, _dwc_1_U_vsFast0p7, _dwc_1_D_vsFast0p7, _dwc_2_U_vsFast0p7, _dwc_2_D_vsFast0p7;
  float _dwc_1_U_wave0p8, _dwc_1_D_wave0p8, _dwc_2_U_wave0p8, _dwc_2_D_wave0p8, _dwc_1_U_vsFast0p8, _dwc_1_D_vsFast0p8, _dwc_2_U_vsFast0p8, _dwc_2_D_vsFast0p8;
  float _dwc_1_U_wave0p9, _dwc_1_D_wave0p9, _dwc_2_U_wave0p9, _dwc_2_D_wave0p9, _dwc_1_U_vsFast0p9, _dwc_1_D_vsFast0p9, _dwc_2_U_vsFast0p9, _dwc_2_D_vsFast0p9;
  float _dwc_1_U_wave1p0, _dwc_1_D_wave1p0, _dwc_2_U_wave1p0, _dwc_2_D_wave1p0, _dwc_1_U_vsFast1p0, _dwc_1_D_vsFast1p0, _dwc_2_U_vsFast1p0, _dwc_2_D_vsFast1p0;

  aTree->Branch("dwc_1_R_fast", &_dwc_1_R_fast);
  aTree->Branch("dwc_1_L_fast", &_dwc_1_L_fast);
  aTree->Branch("dwc_2_R_fast", &_dwc_2_R_fast);
  aTree->Branch("dwc_2_L_fast", &_dwc_2_L_fast);
  aTree->Branch("dwc_1_U_fast", &_dwc_1_U_fast);
  aTree->Branch("dwc_1_D_fast", &_dwc_1_D_fast);
  aTree->Branch("dwc_2_U_fast", &_dwc_2_U_fast);
  aTree->Branch("dwc_2_D_fast", &_dwc_2_D_fast);

  aTree->Branch("dwc_1_R_wave0p1", &_dwc_1_R_wave0p1);
  aTree->Branch("dwc_1_L_wave0p1", &_dwc_1_L_wave0p1);
  aTree->Branch("dwc_2_R_wave0p1", &_dwc_2_R_wave0p1);
  aTree->Branch("dwc_2_L_wave0p1", &_dwc_2_L_wave0p1);
  aTree->Branch("dwc_1_R_vsFast0p1", &_dwc_1_R_vsFast0p1);
  aTree->Branch("dwc_1_L_vsFast0p1", &_dwc_1_L_vsFast0p1);
  aTree->Branch("dwc_2_R_vsFast0p1", &_dwc_2_R_vsFast0p1);
  aTree->Branch("dwc_2_L_vsFast0p1", &_dwc_2_L_vsFast0p1);

  aTree->Branch("dwc_1_R_wave0p2", &_dwc_1_R_wave0p2);
  aTree->Branch("dwc_1_L_wave0p2", &_dwc_1_L_wave0p2);
  aTree->Branch("dwc_2_R_wave0p2", &_dwc_2_R_wave0p2);
  aTree->Branch("dwc_2_L_wave0p2", &_dwc_2_L_wave0p2);
  aTree->Branch("dwc_1_R_vsFast0p2", &_dwc_1_R_vsFast0p2);
  aTree->Branch("dwc_1_L_vsFast0p2", &_dwc_1_L_vsFast0p2);
  aTree->Branch("dwc_2_R_vsFast0p2", &_dwc_2_R_vsFast0p2);
  aTree->Branch("dwc_2_L_vsFast0p2", &_dwc_2_L_vsFast0p2);

  aTree->Branch("dwc_1_R_wave0p3", &_dwc_1_R_wave0p3);
  aTree->Branch("dwc_1_L_wave0p3", &_dwc_1_L_wave0p3);
  aTree->Branch("dwc_2_R_wave0p3", &_dwc_2_R_wave0p3);
  aTree->Branch("dwc_2_L_wave0p3", &_dwc_2_L_wave0p3);
  aTree->Branch("dwc_1_R_vsFast0p3", &_dwc_1_R_vsFast0p3);
  aTree->Branch("dwc_1_L_vsFast0p3", &_dwc_1_L_vsFast0p3);
  aTree->Branch("dwc_2_R_vsFast0p3", &_dwc_2_R_vsFast0p3);
  aTree->Branch("dwc_2_L_vsFast0p3", &_dwc_2_L_vsFast0p3);

  aTree->Branch("dwc_1_R_wave0p4", &_dwc_1_R_wave0p4);
  aTree->Branch("dwc_1_L_wave0p4", &_dwc_1_L_wave0p4);
  aTree->Branch("dwc_2_R_wave0p4", &_dwc_2_R_wave0p4);
  aTree->Branch("dwc_2_L_wave0p4", &_dwc_2_L_wave0p4);
  aTree->Branch("dwc_1_R_vsFast0p4", &_dwc_1_R_vsFast0p4);
  aTree->Branch("dwc_1_L_vsFast0p4", &_dwc_1_L_vsFast0p4);
  aTree->Branch("dwc_2_R_vsFast0p4", &_dwc_2_R_vsFast0p4);
  aTree->Branch("dwc_2_L_vsFast0p4", &_dwc_2_L_vsFast0p4);

  aTree->Branch("dwc_1_R_wave0p5", &_dwc_1_R_wave0p5);
  aTree->Branch("dwc_1_L_wave0p5", &_dwc_1_L_wave0p5);
  aTree->Branch("dwc_2_R_wave0p5", &_dwc_2_R_wave0p5);
  aTree->Branch("dwc_2_L_wave0p5", &_dwc_2_L_wave0p5);
  aTree->Branch("dwc_1_R_vsFast0p5", &_dwc_1_R_vsFast0p5);
  aTree->Branch("dwc_1_L_vsFast0p5", &_dwc_1_L_vsFast0p5);
  aTree->Branch("dwc_2_R_vsFast0p5", &_dwc_2_R_vsFast0p5);
  aTree->Branch("dwc_2_L_vsFast0p5", &_dwc_2_L_vsFast0p5);

  aTree->Branch("dwc_1_R_wave0p6", &_dwc_1_R_wave0p6);
  aTree->Branch("dwc_1_L_wave0p6", &_dwc_1_L_wave0p6);
  aTree->Branch("dwc_2_R_wave0p6", &_dwc_2_R_wave0p6);
  aTree->Branch("dwc_2_L_wave0p6", &_dwc_2_L_wave0p6);
  aTree->Branch("dwc_1_R_vsFast0p6", &_dwc_1_R_vsFast0p6);
  aTree->Branch("dwc_1_L_vsFast0p6", &_dwc_1_L_vsFast0p6);
  aTree->Branch("dwc_2_R_vsFast0p6", &_dwc_2_R_vsFast0p6);
  aTree->Branch("dwc_2_L_vsFast0p6", &_dwc_2_L_vsFast0p6);

  aTree->Branch("dwc_1_R_wave0p7", &_dwc_1_R_wave0p7);
  aTree->Branch("dwc_1_L_wave0p7", &_dwc_1_L_wave0p7);
  aTree->Branch("dwc_2_R_wave0p7", &_dwc_2_R_wave0p7);
  aTree->Branch("dwc_2_L_wave0p7", &_dwc_2_L_wave0p7);
  aTree->Branch("dwc_1_R_vsFast0p7", &_dwc_1_R_vsFast0p7);
  aTree->Branch("dwc_1_L_vsFast0p7", &_dwc_1_L_vsFast0p7);
  aTree->Branch("dwc_2_R_vsFast0p7", &_dwc_2_R_vsFast0p7);
  aTree->Branch("dwc_2_L_vsFast0p7", &_dwc_2_L_vsFast0p7);

  aTree->Branch("dwc_1_R_wave0p8", &_dwc_1_R_wave0p8);
  aTree->Branch("dwc_1_L_wave0p8", &_dwc_1_L_wave0p8);
  aTree->Branch("dwc_2_R_wave0p8", &_dwc_2_R_wave0p8);
  aTree->Branch("dwc_2_L_wave0p8", &_dwc_2_L_wave0p8);
  aTree->Branch("dwc_1_R_vsFast0p8", &_dwc_1_R_vsFast0p8);
  aTree->Branch("dwc_1_L_vsFast0p8", &_dwc_1_L_vsFast0p8);
  aTree->Branch("dwc_2_R_vsFast0p8", &_dwc_2_R_vsFast0p8);
  aTree->Branch("dwc_2_L_vsFast0p8", &_dwc_2_L_vsFast0p8);

  aTree->Branch("dwc_1_R_wave0p9", &_dwc_1_R_wave0p9);
  aTree->Branch("dwc_1_L_wave0p9", &_dwc_1_L_wave0p9);
  aTree->Branch("dwc_2_R_wave0p9", &_dwc_2_R_wave0p9);
  aTree->Branch("dwc_2_L_wave0p9", &_dwc_2_L_wave0p9);
  aTree->Branch("dwc_1_R_vsFast0p9", &_dwc_1_R_vsFast0p9);
  aTree->Branch("dwc_1_L_vsFast0p9", &_dwc_1_L_vsFast0p9);
  aTree->Branch("dwc_2_R_vsFast0p9", &_dwc_2_R_vsFast0p9);
  aTree->Branch("dwc_2_L_vsFast0p9", &_dwc_2_L_vsFast0p9);

  aTree->Branch("dwc_1_R_wave1p0", &_dwc_1_R_wave1p0);
  aTree->Branch("dwc_1_L_wave1p0", &_dwc_1_L_wave1p0);
  aTree->Branch("dwc_2_R_wave1p0", &_dwc_2_R_wave1p0);
  aTree->Branch("dwc_2_L_wave1p0", &_dwc_2_L_wave1p0);
  aTree->Branch("dwc_1_R_vsFast1p0", &_dwc_1_R_vsFast1p0);
  aTree->Branch("dwc_1_L_vsFast1p0", &_dwc_1_L_vsFast1p0);
  aTree->Branch("dwc_2_R_vsFast1p0", &_dwc_2_R_vsFast1p0);
  aTree->Branch("dwc_2_L_vsFast1p0", &_dwc_2_L_vsFast1p0);

  aTree->Branch("dwc_1_U_wave0p1", &_dwc_1_U_wave0p1);
  aTree->Branch("dwc_1_D_wave0p1", &_dwc_1_D_wave0p1);
  aTree->Branch("dwc_2_U_wave0p1", &_dwc_2_U_wave0p1);
  aTree->Branch("dwc_2_D_wave0p1", &_dwc_2_D_wave0p1);
  aTree->Branch("dwc_1_U_vsFast0p1", &_dwc_1_U_vsFast0p1);
  aTree->Branch("dwc_1_D_vsFast0p1", &_dwc_1_D_vsFast0p1);
  aTree->Branch("dwc_2_U_vsFast0p1", &_dwc_2_U_vsFast0p1);
  aTree->Branch("dwc_2_D_vsFast0p1", &_dwc_2_D_vsFast0p1);

  aTree->Branch("dwc_1_U_wave0p2", &_dwc_1_U_wave0p2);
  aTree->Branch("dwc_1_D_wave0p2", &_dwc_1_D_wave0p2);
  aTree->Branch("dwc_2_U_wave0p2", &_dwc_2_U_wave0p2);
  aTree->Branch("dwc_2_D_wave0p2", &_dwc_2_D_wave0p2);
  aTree->Branch("dwc_1_U_vsFast0p2", &_dwc_1_U_vsFast0p2);
  aTree->Branch("dwc_1_D_vsFast0p2", &_dwc_1_D_vsFast0p2);
  aTree->Branch("dwc_2_U_vsFast0p2", &_dwc_2_U_vsFast0p2);
  aTree->Branch("dwc_2_D_vsFast0p2", &_dwc_2_D_vsFast0p2);

  aTree->Branch("dwc_1_U_wave0p3", &_dwc_1_U_wave0p3);
  aTree->Branch("dwc_1_D_wave0p3", &_dwc_1_D_wave0p3);
  aTree->Branch("dwc_2_U_wave0p3", &_dwc_2_U_wave0p3);
  aTree->Branch("dwc_2_D_wave0p3", &_dwc_2_D_wave0p3);
  aTree->Branch("dwc_1_U_vsFast0p3", &_dwc_1_U_vsFast0p3);
  aTree->Branch("dwc_1_D_vsFast0p3", &_dwc_1_D_vsFast0p3);
  aTree->Branch("dwc_2_U_vsFast0p3", &_dwc_2_U_vsFast0p3);
  aTree->Branch("dwc_2_D_vsFast0p3", &_dwc_2_D_vsFast0p3);

  aTree->Branch("dwc_1_U_wave0p4", &_dwc_1_U_wave0p4);
  aTree->Branch("dwc_1_D_wave0p4", &_dwc_1_D_wave0p4);
  aTree->Branch("dwc_2_U_wave0p4", &_dwc_2_U_wave0p4);
  aTree->Branch("dwc_2_D_wave0p4", &_dwc_2_D_wave0p4);
  aTree->Branch("dwc_1_U_vsFast0p4", &_dwc_1_U_vsFast0p4);
  aTree->Branch("dwc_1_D_vsFast0p4", &_dwc_1_D_vsFast0p4);
  aTree->Branch("dwc_2_U_vsFast0p4", &_dwc_2_U_vsFast0p4);
  aTree->Branch("dwc_2_D_vsFast0p4", &_dwc_2_D_vsFast0p4);

  aTree->Branch("dwc_1_U_wave0p5", &_dwc_1_U_wave0p5);
  aTree->Branch("dwc_1_D_wave0p5", &_dwc_1_D_wave0p5);
  aTree->Branch("dwc_2_U_wave0p5", &_dwc_2_U_wave0p5);
  aTree->Branch("dwc_2_D_wave0p5", &_dwc_2_D_wave0p5);
  aTree->Branch("dwc_1_U_vsFast0p5", &_dwc_1_U_vsFast0p5);
  aTree->Branch("dwc_1_D_vsFast0p5", &_dwc_1_D_vsFast0p5);
  aTree->Branch("dwc_2_U_vsFast0p5", &_dwc_2_U_vsFast0p5);
  aTree->Branch("dwc_2_D_vsFast0p5", &_dwc_2_D_vsFast0p5);

  aTree->Branch("dwc_1_U_wave0p6", &_dwc_1_U_wave0p6);
  aTree->Branch("dwc_1_D_wave0p6", &_dwc_1_D_wave0p6);
  aTree->Branch("dwc_2_U_wave0p6", &_dwc_2_U_wave0p6);
  aTree->Branch("dwc_2_D_wave0p6", &_dwc_2_D_wave0p6);
  aTree->Branch("dwc_1_U_vsFast0p6", &_dwc_1_U_vsFast0p6);
  aTree->Branch("dwc_1_D_vsFast0p6", &_dwc_1_D_vsFast0p6);
  aTree->Branch("dwc_2_U_vsFast0p6", &_dwc_2_U_vsFast0p6);
  aTree->Branch("dwc_2_D_vsFast0p6", &_dwc_2_D_vsFast0p6);

  aTree->Branch("dwc_1_U_wave0p7", &_dwc_1_U_wave0p7);
  aTree->Branch("dwc_1_D_wave0p7", &_dwc_1_D_wave0p7);
  aTree->Branch("dwc_2_U_wave0p7", &_dwc_2_U_wave0p7);
  aTree->Branch("dwc_2_D_wave0p7", &_dwc_2_D_wave0p7);
  aTree->Branch("dwc_1_U_vsFast0p7", &_dwc_1_U_vsFast0p7);
  aTree->Branch("dwc_1_D_vsFast0p7", &_dwc_1_D_vsFast0p7);
  aTree->Branch("dwc_2_U_vsFast0p7", &_dwc_2_U_vsFast0p7);
  aTree->Branch("dwc_2_D_vsFast0p7", &_dwc_2_D_vsFast0p7);

  aTree->Branch("dwc_1_U_wave0p8", &_dwc_1_U_wave0p8);
  aTree->Branch("dwc_1_D_wave0p8", &_dwc_1_D_wave0p8);
  aTree->Branch("dwc_2_U_wave0p8", &_dwc_2_U_wave0p8);
  aTree->Branch("dwc_2_D_wave0p8", &_dwc_2_D_wave0p8);
  aTree->Branch("dwc_1_U_vsFast0p8", &_dwc_1_U_vsFast0p8);
  aTree->Branch("dwc_1_D_vsFast0p8", &_dwc_1_D_vsFast0p8);
  aTree->Branch("dwc_2_U_vsFast0p8", &_dwc_2_U_vsFast0p8);
  aTree->Branch("dwc_2_D_vsFast0p8", &_dwc_2_D_vsFast0p8);

  aTree->Branch("dwc_1_U_wave0p9", &_dwc_1_U_wave0p9);
  aTree->Branch("dwc_1_D_wave0p9", &_dwc_1_D_wave0p9);
  aTree->Branch("dwc_2_U_wave0p9", &_dwc_2_U_wave0p9);
  aTree->Branch("dwc_2_D_wave0p9", &_dwc_2_D_wave0p9);
  aTree->Branch("dwc_1_U_vsFast0p9", &_dwc_1_U_vsFast0p9);
  aTree->Branch("dwc_1_D_vsFast0p9", &_dwc_1_D_vsFast0p9);
  aTree->Branch("dwc_2_U_vsFast0p9", &_dwc_2_U_vsFast0p9);
  aTree->Branch("dwc_2_D_vsFast0p9", &_dwc_2_D_vsFast0p9);

  aTree->Branch("dwc_1_U_wave1p0", &_dwc_1_U_wave1p0);
  aTree->Branch("dwc_1_D_wave1p0", &_dwc_1_D_wave1p0);
  aTree->Branch("dwc_2_U_wave1p0", &_dwc_2_U_wave1p0);
  aTree->Branch("dwc_2_D_wave1p0", &_dwc_2_D_wave1p0);
  aTree->Branch("dwc_1_U_vsFast1p0", &_dwc_1_U_vsFast1p0);
  aTree->Branch("dwc_1_D_vsFast1p0", &_dwc_1_D_vsFast1p0);
  aTree->Branch("dwc_2_U_vsFast1p0", &_dwc_2_U_vsFast1p0);
  aTree->Branch("dwc_2_D_vsFast1p0", &_dwc_2_D_vsFast1p0);

  gStyle->SetOptFit(1);

  int runNum = std::stoi(argv[1]);
  TBload<TBwaveform>* wave_loader = new TBload<TBwaveform>(runNum);
  TBload<TBfastmode>* fast_loader = new TBload<TBfastmode>(runNum);

  int maxEvents = std::stoi(argv[2]); 

  std::string pedPath = "dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/khwang/Aug2022TB/RunInfo/pedestal/mean/Run" + std::to_string(runNum) + "_pedestalHist_mean.root";

  TButility utility = TButility();
  utility.loading("dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/khwang/Aug2022TB/RunInfo/mapping/mapping_Aug2022TB.root");
  utility.loadped(pedPath);

  DWCset<TBwaveform>* dwcWaveSet0p1 = new DWCset<TBwaveform>(runNum, dwc_calib, 0.1);
  DWCset<TBwaveform>* dwcWaveSet0p2 = new DWCset<TBwaveform>(runNum, dwc_calib, 0.2);
  DWCset<TBwaveform>* dwcWaveSet0p3 = new DWCset<TBwaveform>(runNum, dwc_calib, 0.3);
  DWCset<TBwaveform>* dwcWaveSet0p4 = new DWCset<TBwaveform>(runNum, dwc_calib, 0.4);
  DWCset<TBwaveform>* dwcWaveSet0p5 = new DWCset<TBwaveform>(runNum, dwc_calib, 0.5);
  DWCset<TBwaveform>* dwcWaveSet0p6 = new DWCset<TBwaveform>(runNum, dwc_calib, 0.6);
  DWCset<TBwaveform>* dwcWaveSet0p7 = new DWCset<TBwaveform>(runNum, dwc_calib, 0.7);
  DWCset<TBwaveform>* dwcWaveSet0p8 = new DWCset<TBwaveform>(runNum, dwc_calib, 0.8);
  DWCset<TBwaveform>* dwcWaveSet0p9 = new DWCset<TBwaveform>(runNum, dwc_calib, 0.9);
  DWCset<TBwaveform>* dwcWaveSet1p0 = new DWCset<TBwaveform>(runNum, dwc_calib, 1.);

  DWCset<TBfastmode>* dwcFastSet = new DWCset<TBfastmode>(runNum, dwc_calib, 0.);

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

  int waveMaxEvt = wave_loader->getEntries();
  int fastMaxEvt = fast_loader->getEntries();

  if ( maxEvents == -1 )
    maxEvents = wave_loader->getEntries();

  if ( maxEvents > wave_loader->getEntries() )
    throw std::runtime_error("Events number is larger than entries !");

  std::chrono::time_point time_begin = std::chrono::system_clock::now(); //delete
  printf("\n");

  TFile* treeFile = new TFile((TString)("/u/user/kyhwang/DRC/Aug2022TB/dev_230307/dual-readout_TB/analysis/DWC_time/root/DWC_Run" + std::to_string(runNum) + "_RunInfo.root"), "RECREATE");




  wave_loader->loading();
  auto aWaveEvt = wave_loader->getEvent();

  for ( int ievt = 0; ievt < fastMaxEvt; ievt++ ) {

    if ( ievt > 0 && ievt % 8 == 0 ) {
      std::chrono::duration time_taken = std::chrono::system_clock::now() - time_begin; //delete
      float percent_done = 1. * ievt / (float)maxEvents;
      std::chrono::duration time_left = time_taken * ( 1 / percent_done - 1 );
      std::chrono::minutes minutes_left = std::chrono::duration_cast<std::chrono::minutes>(time_left);
      std::chrono::seconds seconds_left = std::chrono::duration_cast<std::chrono::seconds>(time_left - minutes_left);
      std::cout << "\r\033[F"<< " " << ievt << " events  "<< minutes_left.count() << ":";
      printf("%02d left   %.1f%%            \n",int(seconds_left.count()),percent_done*100);
    }

    fast_loader->loading();
    auto aFastEvt = fast_loader->getEvent();

    if ( !(aWaveEvt->tcb() == aFastEvt->tcb() ) )
      continue;

    std::vector<TBfastmode> setFastDWC1;
    for ( int i = 0; i < dwc1.size(); i++ )
      setFastDWC1.push_back(aFastEvt->data(dwc1.at(i)));

    std::vector<TBfastmode> setFastDWC2;
    for ( int i = 0; i < dwc2.size(); i++ )
      setFastDWC2.push_back(aFastEvt->data(dwc2.at(i)));

    std::vector<TBwaveform> setWaveDWC1;
    for ( int i = 0; i < dwc1.size(); i++ )
      setWaveDWC1.push_back(aWaveEvt->data(dwc1.at(i)));

    std::vector<TBwaveform> setWaveDWC2;
    for ( int i = 0; i < dwc2.size(); i++ )
      setWaveDWC2.push_back(aWaveEvt->data(dwc2.at(i)));

    dwcFastSet->SetDWC(setFastDWC1, setFastDWC2, dwc_ped);     auto dwcFastPos    = dwcFastSet->GetTimeVec();
    dwcWaveSet0p1->SetDWC(setWaveDWC1, setWaveDWC2, dwc_ped);  auto dwcWavePos0p1 = dwcWaveSet0p1->GetTimeVec();
    dwcWaveSet0p2->SetDWC(setWaveDWC1, setWaveDWC2, dwc_ped);  auto dwcWavePos0p2 = dwcWaveSet0p2->GetTimeVec();
    dwcWaveSet0p3->SetDWC(setWaveDWC1, setWaveDWC2, dwc_ped);  auto dwcWavePos0p3 = dwcWaveSet0p3->GetTimeVec();
    dwcWaveSet0p4->SetDWC(setWaveDWC1, setWaveDWC2, dwc_ped);  auto dwcWavePos0p4 = dwcWaveSet0p4->GetTimeVec();
    dwcWaveSet0p5->SetDWC(setWaveDWC1, setWaveDWC2, dwc_ped);  auto dwcWavePos0p5 = dwcWaveSet0p5->GetTimeVec();
    dwcWaveSet0p6->SetDWC(setWaveDWC1, setWaveDWC2, dwc_ped);  auto dwcWavePos0p6 = dwcWaveSet0p6->GetTimeVec();
    dwcWaveSet0p7->SetDWC(setWaveDWC1, setWaveDWC2, dwc_ped);  auto dwcWavePos0p7 = dwcWaveSet0p7->GetTimeVec();
    dwcWaveSet0p8->SetDWC(setWaveDWC1, setWaveDWC2, dwc_ped);  auto dwcWavePos0p8 = dwcWaveSet0p8->GetTimeVec();
    dwcWaveSet0p9->SetDWC(setWaveDWC1, setWaveDWC2, dwc_ped);  auto dwcWavePos0p9 = dwcWaveSet0p9->GetTimeVec();
    dwcWaveSet1p0->SetDWC(setWaveDWC1, setWaveDWC2, dwc_ped);  auto dwcWavePos1p0 = dwcWaveSet1p0->GetTimeVec();

    _dwc_1_R_fast = dwcFastPos.at(0);
    _dwc_1_L_fast = dwcFastPos.at(1);
    _dwc_1_U_fast = dwcFastPos.at(2);
    _dwc_1_D_fast = dwcFastPos.at(3);
    _dwc_2_R_fast = dwcFastPos.at(4);
    _dwc_2_L_fast = dwcFastPos.at(5);
    _dwc_2_U_fast = dwcFastPos.at(6);
    _dwc_2_D_fast = dwcFastPos.at(7);

    _dwc_1_R_wave0p1 = dwcWavePos0p1.at(0);
    _dwc_1_L_wave0p1 = dwcWavePos0p1.at(1);
    _dwc_1_U_wave0p1 = dwcWavePos0p1.at(2);
    _dwc_1_D_wave0p1 = dwcWavePos0p1.at(3);
    _dwc_2_R_wave0p1 = dwcWavePos0p1.at(4);
    _dwc_2_L_wave0p1 = dwcWavePos0p1.at(5);
    _dwc_2_U_wave0p1 = dwcWavePos0p1.at(6);
    _dwc_2_D_wave0p1 = dwcWavePos0p1.at(7);

    _dwc_1_R_vsFast0p1 = _dwc_1_R_fast - _dwc_1_R_wave0p1; 
    _dwc_1_L_vsFast0p1 = _dwc_1_L_fast - _dwc_1_L_wave0p1; 
    _dwc_1_U_vsFast0p1 = _dwc_1_U_fast - _dwc_1_U_wave0p1; 
    _dwc_1_D_vsFast0p1 = _dwc_1_D_fast - _dwc_1_D_wave0p1; 
    _dwc_2_R_vsFast0p1 = _dwc_2_R_fast - _dwc_2_R_wave0p1; 
    _dwc_2_L_vsFast0p1 = _dwc_2_L_fast - _dwc_2_L_wave0p1; 
    _dwc_2_U_vsFast0p1 = _dwc_2_U_fast - _dwc_2_U_wave0p1; 
    _dwc_2_D_vsFast0p1 = _dwc_2_D_fast - _dwc_2_D_wave0p1; 

    _dwc_1_R_wave0p2 = dwcWavePos0p2.at(0);
    _dwc_1_L_wave0p2 = dwcWavePos0p2.at(1);
    _dwc_1_U_wave0p2 = dwcWavePos0p2.at(2);
    _dwc_1_D_wave0p2 = dwcWavePos0p2.at(3);
    _dwc_2_R_wave0p2 = dwcWavePos0p2.at(4);
    _dwc_2_L_wave0p2 = dwcWavePos0p2.at(5);
    _dwc_2_U_wave0p2 = dwcWavePos0p2.at(6);
    _dwc_2_D_wave0p2 = dwcWavePos0p2.at(7);

    _dwc_1_R_vsFast0p2 = _dwc_1_R_fast - _dwc_1_R_wave0p2;
    _dwc_1_L_vsFast0p2 = _dwc_1_L_fast - _dwc_1_L_wave0p2;
    _dwc_1_U_vsFast0p2 = _dwc_1_U_fast - _dwc_1_U_wave0p2;
    _dwc_1_D_vsFast0p2 = _dwc_1_D_fast - _dwc_1_D_wave0p2;
    _dwc_2_R_vsFast0p2 = _dwc_2_R_fast - _dwc_2_R_wave0p2;
    _dwc_2_L_vsFast0p2 = _dwc_2_L_fast - _dwc_2_L_wave0p2;
    _dwc_2_U_vsFast0p2 = _dwc_2_U_fast - _dwc_2_U_wave0p2;
    _dwc_2_D_vsFast0p2 = _dwc_2_D_fast - _dwc_2_D_wave0p2;

    _dwc_1_R_wave0p3 = dwcWavePos0p3.at(0);
    _dwc_1_L_wave0p3 = dwcWavePos0p3.at(1);
    _dwc_1_U_wave0p3 = dwcWavePos0p3.at(2);
    _dwc_1_D_wave0p3 = dwcWavePos0p3.at(3);
    _dwc_2_R_wave0p3 = dwcWavePos0p3.at(4);
    _dwc_2_L_wave0p3 = dwcWavePos0p3.at(5);
    _dwc_2_U_wave0p3 = dwcWavePos0p3.at(6);
    _dwc_2_D_wave0p3 = dwcWavePos0p3.at(7);

    _dwc_1_R_vsFast0p3 = _dwc_1_R_fast - _dwc_1_R_wave0p3;
    _dwc_1_L_vsFast0p3 = _dwc_1_L_fast - _dwc_1_L_wave0p3;
    _dwc_1_U_vsFast0p3 = _dwc_1_U_fast - _dwc_1_U_wave0p3;
    _dwc_1_D_vsFast0p3 = _dwc_1_D_fast - _dwc_1_D_wave0p3;
    _dwc_2_R_vsFast0p3 = _dwc_2_R_fast - _dwc_2_R_wave0p3;
    _dwc_2_L_vsFast0p3 = _dwc_2_L_fast - _dwc_2_L_wave0p3;
    _dwc_2_U_vsFast0p3 = _dwc_2_U_fast - _dwc_2_U_wave0p3;
    _dwc_2_D_vsFast0p3 = _dwc_2_D_fast - _dwc_2_D_wave0p3;

    _dwc_1_R_wave0p4 = dwcWavePos0p4.at(0);
    _dwc_1_L_wave0p4 = dwcWavePos0p4.at(1);
    _dwc_1_U_wave0p4 = dwcWavePos0p4.at(2);
    _dwc_1_D_wave0p4 = dwcWavePos0p4.at(3);
    _dwc_2_R_wave0p4 = dwcWavePos0p4.at(4);
    _dwc_2_L_wave0p4 = dwcWavePos0p4.at(5);
    _dwc_2_U_wave0p4 = dwcWavePos0p4.at(6);
    _dwc_2_D_wave0p4 = dwcWavePos0p4.at(7);

    _dwc_1_R_vsFast0p4 = _dwc_1_R_fast - _dwc_1_R_wave0p4;
    _dwc_1_L_vsFast0p4 = _dwc_1_L_fast - _dwc_1_L_wave0p4;
    _dwc_1_U_vsFast0p4 = _dwc_1_U_fast - _dwc_1_U_wave0p4;
    _dwc_1_D_vsFast0p4 = _dwc_1_D_fast - _dwc_1_D_wave0p4;
    _dwc_2_R_vsFast0p4 = _dwc_2_R_fast - _dwc_2_R_wave0p4;
    _dwc_2_L_vsFast0p4 = _dwc_2_L_fast - _dwc_2_L_wave0p4;
    _dwc_2_U_vsFast0p4 = _dwc_2_U_fast - _dwc_2_U_wave0p4;
    _dwc_2_D_vsFast0p4 = _dwc_2_D_fast - _dwc_2_D_wave0p4;

    _dwc_1_R_wave0p5 = dwcWavePos0p5.at(0);
    _dwc_1_L_wave0p5 = dwcWavePos0p5.at(1);
    _dwc_1_U_wave0p5 = dwcWavePos0p5.at(2);
    _dwc_1_D_wave0p5 = dwcWavePos0p5.at(3);
    _dwc_2_R_wave0p5 = dwcWavePos0p5.at(4);
    _dwc_2_L_wave0p5 = dwcWavePos0p5.at(5);
    _dwc_2_U_wave0p5 = dwcWavePos0p5.at(6);
    _dwc_2_D_wave0p5 = dwcWavePos0p5.at(7);

    _dwc_1_R_vsFast0p5 = _dwc_1_R_fast - _dwc_1_R_wave0p5;
    _dwc_1_L_vsFast0p5 = _dwc_1_L_fast - _dwc_1_L_wave0p5;
    _dwc_1_U_vsFast0p5 = _dwc_1_U_fast - _dwc_1_U_wave0p5;
    _dwc_1_D_vsFast0p5 = _dwc_1_D_fast - _dwc_1_D_wave0p5;
    _dwc_2_R_vsFast0p5 = _dwc_2_R_fast - _dwc_2_R_wave0p5;
    _dwc_2_L_vsFast0p5 = _dwc_2_L_fast - _dwc_2_L_wave0p5;
    _dwc_2_U_vsFast0p5 = _dwc_2_U_fast - _dwc_2_U_wave0p5;
    _dwc_2_D_vsFast0p5 = _dwc_2_D_fast - _dwc_2_D_wave0p5;

    _dwc_1_R_wave0p6 = dwcWavePos0p6.at(0);
    _dwc_1_L_wave0p6 = dwcWavePos0p6.at(1);
    _dwc_1_U_wave0p6 = dwcWavePos0p6.at(2);
    _dwc_1_D_wave0p6 = dwcWavePos0p6.at(3);
    _dwc_2_R_wave0p6 = dwcWavePos0p6.at(4);
    _dwc_2_L_wave0p6 = dwcWavePos0p6.at(5);
    _dwc_2_U_wave0p6 = dwcWavePos0p6.at(6);
    _dwc_2_D_wave0p6 = dwcWavePos0p6.at(7);

    _dwc_1_R_vsFast0p6 = _dwc_1_R_fast - _dwc_1_R_wave0p6;
    _dwc_1_L_vsFast0p6 = _dwc_1_L_fast - _dwc_1_L_wave0p6;
    _dwc_1_U_vsFast0p6 = _dwc_1_U_fast - _dwc_1_U_wave0p6;
    _dwc_1_D_vsFast0p6 = _dwc_1_D_fast - _dwc_1_D_wave0p6;
    _dwc_2_R_vsFast0p6 = _dwc_2_R_fast - _dwc_2_R_wave0p6;
    _dwc_2_L_vsFast0p6 = _dwc_2_L_fast - _dwc_2_L_wave0p6;
    _dwc_2_U_vsFast0p6 = _dwc_2_U_fast - _dwc_2_U_wave0p6;
    _dwc_2_D_vsFast0p6 = _dwc_2_D_fast - _dwc_2_D_wave0p6;

    _dwc_1_R_wave0p7 = dwcWavePos0p7.at(0);
    _dwc_1_L_wave0p7 = dwcWavePos0p7.at(1);
    _dwc_1_U_wave0p7 = dwcWavePos0p7.at(2);
    _dwc_1_D_wave0p7 = dwcWavePos0p7.at(3);
    _dwc_2_R_wave0p7 = dwcWavePos0p7.at(4);
    _dwc_2_L_wave0p7 = dwcWavePos0p7.at(5);
    _dwc_2_U_wave0p7 = dwcWavePos0p7.at(6);
    _dwc_2_D_wave0p7 = dwcWavePos0p7.at(7);

    _dwc_1_R_vsFast0p7 = _dwc_1_R_fast - _dwc_1_R_wave0p7;
    _dwc_1_L_vsFast0p7 = _dwc_1_L_fast - _dwc_1_L_wave0p7;
    _dwc_1_U_vsFast0p7 = _dwc_1_U_fast - _dwc_1_U_wave0p7;
    _dwc_1_D_vsFast0p7 = _dwc_1_D_fast - _dwc_1_D_wave0p7;
    _dwc_2_R_vsFast0p7 = _dwc_2_R_fast - _dwc_2_R_wave0p7;
    _dwc_2_L_vsFast0p7 = _dwc_2_L_fast - _dwc_2_L_wave0p7;
    _dwc_2_U_vsFast0p7 = _dwc_2_U_fast - _dwc_2_U_wave0p7;
    _dwc_2_D_vsFast0p7 = _dwc_2_D_fast - _dwc_2_D_wave0p7;

    _dwc_1_R_wave0p8 = dwcWavePos0p8.at(0);
    _dwc_1_L_wave0p8 = dwcWavePos0p8.at(1);
    _dwc_1_U_wave0p8 = dwcWavePos0p8.at(2);
    _dwc_1_D_wave0p8 = dwcWavePos0p8.at(3);
    _dwc_2_R_wave0p8 = dwcWavePos0p8.at(4);
    _dwc_2_L_wave0p8 = dwcWavePos0p8.at(5);
    _dwc_2_U_wave0p8 = dwcWavePos0p8.at(6);
    _dwc_2_D_wave0p8 = dwcWavePos0p8.at(7);

    _dwc_1_R_vsFast0p8 = _dwc_1_R_fast - _dwc_1_R_wave0p8;
    _dwc_1_L_vsFast0p8 = _dwc_1_L_fast - _dwc_1_L_wave0p8;
    _dwc_1_U_vsFast0p8 = _dwc_1_U_fast - _dwc_1_U_wave0p8;
    _dwc_1_D_vsFast0p8 = _dwc_1_D_fast - _dwc_1_D_wave0p8;
    _dwc_2_R_vsFast0p8 = _dwc_2_R_fast - _dwc_2_R_wave0p8;
    _dwc_2_L_vsFast0p8 = _dwc_2_L_fast - _dwc_2_L_wave0p8;
    _dwc_2_U_vsFast0p8 = _dwc_2_U_fast - _dwc_2_U_wave0p8;
    _dwc_2_D_vsFast0p8 = _dwc_2_D_fast - _dwc_2_D_wave0p8;

    _dwc_1_R_wave0p9 = dwcWavePos0p9.at(0);
    _dwc_1_L_wave0p9 = dwcWavePos0p9.at(1);
    _dwc_1_U_wave0p9 = dwcWavePos0p9.at(2);
    _dwc_1_D_wave0p9 = dwcWavePos0p9.at(3);
    _dwc_2_R_wave0p9 = dwcWavePos0p9.at(4);
    _dwc_2_L_wave0p9 = dwcWavePos0p9.at(5);
    _dwc_2_U_wave0p9 = dwcWavePos0p9.at(6);
    _dwc_2_D_wave0p9 = dwcWavePos0p9.at(7);

    _dwc_1_R_vsFast0p9 = _dwc_1_R_fast - _dwc_1_R_wave0p9;
    _dwc_1_L_vsFast0p9 = _dwc_1_L_fast - _dwc_1_L_wave0p9;
    _dwc_1_U_vsFast0p9 = _dwc_1_U_fast - _dwc_1_U_wave0p9;
    _dwc_1_D_vsFast0p9 = _dwc_1_D_fast - _dwc_1_D_wave0p9;
    _dwc_2_R_vsFast0p9 = _dwc_2_R_fast - _dwc_2_R_wave0p9;
    _dwc_2_L_vsFast0p9 = _dwc_2_L_fast - _dwc_2_L_wave0p9;
    _dwc_2_U_vsFast0p9 = _dwc_2_U_fast - _dwc_2_U_wave0p9;
    _dwc_2_D_vsFast0p9 = _dwc_2_D_fast - _dwc_2_D_wave0p9;

    _dwc_1_R_wave1p0 = dwcWavePos1p0.at(0);
    _dwc_1_L_wave1p0 = dwcWavePos1p0.at(1);
    _dwc_1_U_wave1p0 = dwcWavePos1p0.at(2);
    _dwc_1_D_wave1p0 = dwcWavePos1p0.at(3);
    _dwc_2_R_wave1p0 = dwcWavePos1p0.at(4);
    _dwc_2_L_wave1p0 = dwcWavePos1p0.at(5);
    _dwc_2_U_wave1p0 = dwcWavePos1p0.at(6);
    _dwc_2_D_wave1p0 = dwcWavePos1p0.at(7);

    _dwc_1_R_vsFast1p0 = _dwc_1_R_fast - _dwc_1_R_wave1p0;
    _dwc_1_L_vsFast1p0 = _dwc_1_L_fast - _dwc_1_L_wave1p0;
    _dwc_1_U_vsFast1p0 = _dwc_1_U_fast - _dwc_1_U_wave1p0;
    _dwc_1_D_vsFast1p0 = _dwc_1_D_fast - _dwc_1_D_wave1p0;
    _dwc_2_R_vsFast1p0 = _dwc_2_R_fast - _dwc_2_R_wave1p0;
    _dwc_2_L_vsFast1p0 = _dwc_2_L_fast - _dwc_2_L_wave1p0;
    _dwc_2_U_vsFast1p0 = _dwc_2_U_fast - _dwc_2_U_wave1p0;
    _dwc_2_D_vsFast1p0 = _dwc_2_D_fast - _dwc_2_D_wave1p0;


    aTree->Fill();

    if ( aWaveEvt->tcb() > maxEvents )
      break;

    wave_loader->loading();
    aWaveEvt = wave_loader->getEvent();

  }
  wave_loader->close();
  fast_loader->close();

  treeFile->cd();
  aTree->Write();
  treeFile->Close();

  return 0;
}
