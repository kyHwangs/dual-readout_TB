#include <iostream>
#include <stdexcept>
#include <filesystem>

#include "TBevt.h"
#include "TButility.h"
#include "TBmonit.h"
#include "TBplot.h"

#include <TChain.h>
#include <TCanvas.h>
#include <TFile.h>
#include <TTree.h>
#include <TH1D.h>
#include <TH2D.h>

// g++ -I/Users/drc_daq/scratch/TBAnalysisTool/dual-readout_TB/install/include -L/Users/drc_daq/scratch/TBAnalysisTool/dual-readout_TB/install/lib /Users/drc_daq/scratch/TBAnalysisTool/dual-readout_TB/install/lib/drcTB.so `root-config --cflags --libs` plotting.cc -o plotting


int main(int argc, char** argv) {

	TCanvas* c = new TCanvas("c", "c", 500, 500);

	std::string PlotFile = argv[1];

  TFile* plotRootFile = new TFile(PlotFile.c_str(), "READ");

  std::vector<TH2D*> WaveHitMap__;
  std::vector<TH1D*> WaveADCDist__;
  std::vector<TH1D*> WaveWaveform__;
  std::vector<TH2D*> FastHitMap__;
  std::vector<TH1D*> FastADCDist__;

  std::cout << "loading hitmap" << std::endl;
  plotRootFile->cd();
  gDirectory->cd("WaveHitMap");
  for( int i = 0; i < 27; i++) {
  	TH2D* tmpHist;
  	plotRootFile->GetObject((TString)("HitMapAccuWave0"+std::to_string(i)), tmpHist);
  	WaveHitMap__.push_back(tmpHist);
  }
  std::cout << "loading adc" << std::endl;
  plotRootFile->cd();
  gDirectory->cd("WaveADCDist");
  for( int i = 0; i < 26; i++) WaveADCDist__.push_back((TH1D*)plotRootFile->Get((TString)("disMapAccuWave1"+std::to_string(i))));

  std::cout << "loading wave" << std::endl;
  plotRootFile->cd();
  gDirectory->cd("WaveWaveform");
  for( int i = 0; i < 26; i++) WaveWaveform__.push_back((TH1D*)plotRootFile->Get((TString)("wavMapAccuWave2"+std::to_string(i))));

  std::cout << "loading hit" << std::endl;
  plotRootFile->cd();
  gDirectory->cd("FastHitMap");
  for( int i = 0; i < 27; i++) FastHitMap__.push_back((TH2D*)plotRootFile->Get((TString)("HitMapAccuFast0"+std::to_string(i))));

  std::cout << "loading adc" << std::endl;
  plotRootFile->cd();
  gDirectory->cd("FastADCDist");
  for( int i = 0; i < 26; i++) FastADCDist__.push_back((TH1D*)plotRootFile->Get((TString)("disMapAccuFast1"+std::to_string(i))));

  // c->cd(); 
	std::cout << WaveHitMap__.at(6)->GetMean() << std::endl;

  auto HitMapAccuWave = new TBplot(1000, 1000, "HitMapAccuWave", TBplotbase::kind::hitmap, WaveHitMap__);
	auto disMapAccuWave = new TBplot(1000, 500, "disMapAccuWave", TBplotbase::kind::distribution, WaveADCDist__);
	auto wavMapWave = new TBplot(1000, 500, "wavMapWave", TBplotbase::kind::waveform, WaveWaveform__);

	auto disMapAccuFast = new TBplot(1000, 500, "disMapAccuFast", TBplotbase::kind::distribution, FastHitMap__);
  auto HitMapAccuFast = new TBplot(1000, 1000, "HitMapAccuFast", TBplotbase::kind::hitmap, FastADCDist__);

  // disMapAccuWave->Draw();

  // c->cd(); disMapAccuWave->aPlot1D(1)->Draw("Hist");





	return 0;
}