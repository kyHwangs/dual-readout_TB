#include <iostream>
#include <stdexcept>
#include <filesystem>

#include <TChain.h>
#include <TFile.h>
#include <TTree.h>
#include <TH1D.h>

void test() {
	TFile* test = new TFile("test.root", "RECREATE");

	TH2D* hist = new TH2D("", ";;", 10, 0., 10., 10, 0., 10.);

	test->WriteObject(hist, "test/testhist");
	test->Close();
}