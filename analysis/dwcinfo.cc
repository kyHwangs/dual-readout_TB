#include <stdexcept>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <cmath>

#include "TROOT.h"
#include "TStyle.h"
#include <TChain.h>
#include <TFile.h>
#include <TTree.h>
#include <TF1.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TLatex.h>
#include <TList.h>
#include <TCanvas.h>

#include "ROOT/RDataFrame.hxx"
#include "ROOT/RVec.hxx"
#include "ROOT/RDataFrame.hxx"

using cRVecF = const ROOT::RVecF &;

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

	ROOT::EnableImplicitMT();

  TList* dwc1xCol = new TList();
  TList* dwc1yCol = new TList();
  TList* dwc2xCol = new TList();
  TList* dwc2yCol = new TList();

  TCanvas* c = new TCanvas("", "");

	for ( int run : jobCol ) {

		std::string runNum = std::to_string(run);
		std::string filePath = "./DWC_info/root/DWC_Run" + runNum + "_RunInfo.root";

		std::cout << filePath << std::endl;

		ROOT::RDataFrame df("data", filePath);

		auto h_dwc_1_X = df.Histo1D({(TString)(runNum + " DWC 1 X"), "DWC1 X pos.;mm;N_{Events}", 720, -120., 120.}, "dwc_1_x"); dwc1xCol->Add(h_dwc_1_X->Clone());
		auto h_dwc_1_Y = df.Histo1D({(TString)(runNum + " DWC 1 Y"), "DWC1 Y pos.;mm;N_{Events}", 720, -120., 120.}, "dwc_1_y"); dwc1yCol->Add(h_dwc_1_Y->Clone());
		auto h_dwc_2_X = df.Histo1D({(TString)(runNum + " DWC 2 X"), "DWC2 X pos.;mm;N_{Events}", 720, -120., 120.}, "dwc_2_x"); dwc2xCol->Add(h_dwc_2_X->Clone());
		auto h_dwc_2_Y = df.Histo1D({(TString)(runNum + " DWC 2 Y"), "DWC2 Y pos.;mm;N_{Events}", 720, -120., 120.}, "dwc_2_y"); dwc2yCol->Add(h_dwc_2_Y->Clone());


		c->cd();
		h_dwc_1_X->Draw("Hist"); c->SaveAs((TString)("./DWC_info/png/1x/DWC_Run" + runNum + "_dwc_1_x.png"));
		h_dwc_1_Y->Draw("Hist"); c->SaveAs((TString)("./DWC_info/png/1y/DWC_Run" + runNum + "_dwc_1_y.png"));
		h_dwc_2_X->Draw("Hist"); c->SaveAs((TString)("./DWC_info/png/2x/DWC_Run" + runNum + "_dwc_2_x.png"));
		h_dwc_2_Y->Draw("Hist"); c->SaveAs((TString)("./DWC_info/png/2y/DWC_Run" + runNum + "_dwc_2_y.png"));
	}

	auto all_dwc_1_x = (TH1D*)dwc1xCol->At(0)->Clone(); all_dwc_1_x->Reset(); all_dwc_1_x->Merge(dwc1xCol);
	auto all_dwc_1_y = (TH1D*)dwc1yCol->At(0)->Clone(); all_dwc_1_y->Reset(); all_dwc_1_y->Merge(dwc1yCol);
	auto all_dwc_2_x = (TH1D*)dwc2xCol->At(0)->Clone(); all_dwc_2_x->Reset(); all_dwc_2_x->Merge(dwc2xCol);
	auto all_dwc_2_y = (TH1D*)dwc2yCol->At(0)->Clone(); all_dwc_2_y->Reset(); all_dwc_2_y->Merge(dwc2yCol);

	c->cd();
	all_dwc_1_x->Draw("Hist"); c->SaveAs((TString)("./DWC_info/DWC_Run_all_dwc_1_x.png"));
	all_dwc_1_y->Draw("Hist"); c->SaveAs((TString)("./DWC_info/DWC_Run_all_dwc_1_y.png"));
	all_dwc_2_x->Draw("Hist"); c->SaveAs((TString)("./DWC_info/DWC_Run_all_dwc_2_x.png"));
	all_dwc_2_y->Draw("Hist"); c->SaveAs((TString)("./DWC_info/DWC_Run_all_dwc_2_y.png"));

	return 1;
}

