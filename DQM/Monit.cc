#include <iostream>
#include <stdexcept>
#include <filesystem>

#include "TBevt.h"
#include "TButility.h"
#include "TBmonit.h"

#include <TChain.h>
#include <TFile.h>
#include <TTree.h>
#include <TH1D.h>

// g++ -I/Users/drc_daq/scratch/TBAnalysisTool/dual-readout_TB/install/include -L/Users/drc_daq/scratch/TBAnalysisTool/dual-readout_TB/install/lib /Users/drc_daq/scratch/TBAnalysisTool/dual-readout_TB/install/lib/drcTB.so `root-config --cflags --libs` Monit.cc -o Monit
// g++ -I/Users/drc_daq/scratch/TBAnalysisTool/dual-readout_TB/install/include -L/Users/drc_daq/scratch/TBAnalysisTool/dual-readout_TB/install/lib /Users/drc_daq/scratch/TBAnalysisTool/dual-readout_TB/install/lib/drcTB.so `root-config --cflags --libs` Monit.cc -o Monit

int main(int argc, char** argv) {

	std::string aRunNum = argv[1];
	std::string aPedNum = argv[2];
	std::string aFileNum = argv[3];
	double DistMaxADC = std::stod(argv[4]);
	double DistBinADC = std::stod(argv[5]);

  std::string directory_name = "./MonitPlot/Run"+aRunNum;
  std::string output = directory_name+"/Run"+aRunNum+"_File"+aFileNum+".root";

  if (std::filesystem::create_directory(directory_name) ) {
    std::cout << " [INFO ] Monitoring : " << directory_name << " created." << std::endl;
  } else {
    std::cout << " [ERROR] Monitoring : " << directory_name << " failed to create!" << std::endl;
  }

  std::vector<std::string> FastFiles = {
    "/Users/drc_daq/scratch/Aug2022TB/SSD/SSD_Run_"+aRunNum+"/Run_"+aRunNum+"_Fast/Run_"+aRunNum+"_Fast_MID_1/Run_"+aRunNum+"_Fast_MID_1_FILE_"+aFileNum+".dat",
    "/Users/drc_daq/scratch/Aug2022TB/SSD/SSD_Run_"+aRunNum+"/Run_"+aRunNum+"_Fast/Run_"+aRunNum+"_Fast_MID_2/Run_"+aRunNum+"_Fast_MID_2_FILE_"+aFileNum+".dat",
    "/Users/drc_daq/scratch/Aug2022TB/SSD/SSD_Run_"+aRunNum+"/Run_"+aRunNum+"_Fast/Run_"+aRunNum+"_Fast_MID_3/Run_"+aRunNum+"_Fast_MID_3_FILE_"+aFileNum+".dat",
    "/Users/drc_daq/scratch/Aug2022TB/SSD/SSD_Run_"+aRunNum+"/Run_"+aRunNum+"_Fast/Run_"+aRunNum+"_Fast_MID_4/Run_"+aRunNum+"_Fast_MID_4_FILE_"+aFileNum+".dat",
    "/Users/drc_daq/scratch/Aug2022TB/SSD/SSD_Run_"+aRunNum+"/Run_"+aRunNum+"_Fast/Run_"+aRunNum+"_Fast_MID_5/Run_"+aRunNum+"_Fast_MID_5_FILE_"+aFileNum+".dat",
    "/Users/drc_daq/scratch/Aug2022TB/SSD/SSD_Run_"+aRunNum+"/Run_"+aRunNum+"_Fast/Run_"+aRunNum+"_Fast_MID_6/Run_"+aRunNum+"_Fast_MID_6_FILE_"+aFileNum+".dat",
    "/Users/drc_daq/scratch/Aug2022TB/SSD/SSD_Run_"+aRunNum+"/Run_"+aRunNum+"_Fast/Run_"+aRunNum+"_Fast_MID_7/Run_"+aRunNum+"_Fast_MID_7_FILE_"+aFileNum+".dat",
    "/Users/drc_daq/scratch/Aug2022TB/SSD/SSD_Run_"+aRunNum+"/Run_"+aRunNum+"_Fast/Run_"+aRunNum+"_Fast_MID_8/Run_"+aRunNum+"_Fast_MID_8_FILE_"+aFileNum+".dat",
    "/Users/drc_daq/scratch/Aug2022TB/SSD/SSD_Run_"+aRunNum+"/Run_"+aRunNum+"_Fast/Run_"+aRunNum+"_Fast_MID_9/Run_"+aRunNum+"_Fast_MID_9_FILE_"+aFileNum+".dat",
    "/Users/drc_daq/scratch/Aug2022TB/SSD/SSD_Run_"+aRunNum+"/Run_"+aRunNum+"_Fast/Run_"+aRunNum+"_Fast_MID_10/Run_"+aRunNum+"_Fast_MID_10_FILE_"+aFileNum+".dat",
    "/Users/drc_daq/scratch/Aug2022TB/SSD/SSD_Run_"+aRunNum+"/Run_"+aRunNum+"_Fast/Run_"+aRunNum+"_Fast_MID_11/Run_"+aRunNum+"_Fast_MID_11_FILE_"+aFileNum+".dat",
    "/Users/drc_daq/scratch/Aug2022TB/SSD/SSD_Run_"+aRunNum+"/Run_"+aRunNum+"_Fast/Run_"+aRunNum+"_Fast_MID_12/Run_"+aRunNum+"_Fast_MID_12_FILE_"+aFileNum+".dat",
    "/Users/drc_daq/scratch/Aug2022TB/SSD/SSD_Run_"+aRunNum+"/Run_"+aRunNum+"_Fast/Run_"+aRunNum+"_Fast_MID_13/Run_"+aRunNum+"_Fast_MID_13_FILE_"+aFileNum+".dat",
    "/Users/drc_daq/scratch/Aug2022TB/SSD/SSD_Run_"+aRunNum+"/Run_"+aRunNum+"_Fast/Run_"+aRunNum+"_Fast_MID_14/Run_"+aRunNum+"_Fast_MID_14_FILE_"+aFileNum+".dat",
    "/Users/drc_daq/scratch/Aug2022TB/SSD/SSD_Run_"+aRunNum+"/Run_"+aRunNum+"_Fast/Run_"+aRunNum+"_Fast_MID_15/Run_"+aRunNum+"_Fast_MID_15_FILE_"+aFileNum+".dat"
  };

	std::vector<std::string> WaveFiles = {
    "/Users/drc_daq/scratch/Aug2022TB/SSD/SSD_Run_"+aRunNum+"/Run_"+aRunNum+"_Wave/Run_"+aRunNum+"_Wave_MID_1/Run_"+aRunNum+"_Wave_MID_1_FILE_"+aFileNum+".dat",
    "/Users/drc_daq/scratch/Aug2022TB/SSD/SSD_Run_"+aRunNum+"/Run_"+aRunNum+"_Wave/Run_"+aRunNum+"_Wave_MID_2/Run_"+aRunNum+"_Wave_MID_2_FILE_"+aFileNum+".dat",
    "/Users/drc_daq/scratch/Aug2022TB/SSD/SSD_Run_"+aRunNum+"/Run_"+aRunNum+"_Wave/Run_"+aRunNum+"_Wave_MID_3/Run_"+aRunNum+"_Wave_MID_3_FILE_"+aFileNum+".dat",
    "/Users/drc_daq/scratch/Aug2022TB/SSD/SSD_Run_"+aRunNum+"/Run_"+aRunNum+"_Wave/Run_"+aRunNum+"_Wave_MID_4/Run_"+aRunNum+"_Wave_MID_4_FILE_"+aFileNum+".dat",
    "/Users/drc_daq/scratch/Aug2022TB/SSD/SSD_Run_"+aRunNum+"/Run_"+aRunNum+"_Wave/Run_"+aRunNum+"_Wave_MID_5/Run_"+aRunNum+"_Wave_MID_5_FILE_"+aFileNum+".dat",
    "/Users/drc_daq/scratch/Aug2022TB/SSD/SSD_Run_"+aRunNum+"/Run_"+aRunNum+"_Wave/Run_"+aRunNum+"_Wave_MID_6/Run_"+aRunNum+"_Wave_MID_6_FILE_"+aFileNum+".dat",
    "/Users/drc_daq/scratch/Aug2022TB/SSD/SSD_Run_"+aRunNum+"/Run_"+aRunNum+"_Wave/Run_"+aRunNum+"_Wave_MID_7/Run_"+aRunNum+"_Wave_MID_7_FILE_"+aFileNum+".dat",
    "/Users/drc_daq/scratch/Aug2022TB/SSD/SSD_Run_"+aRunNum+"/Run_"+aRunNum+"_Wave/Run_"+aRunNum+"_Wave_MID_8/Run_"+aRunNum+"_Wave_MID_8_FILE_"+aFileNum+".dat",
    "/Users/drc_daq/scratch/Aug2022TB/SSD/SSD_Run_"+aRunNum+"/Run_"+aRunNum+"_Wave/Run_"+aRunNum+"_Wave_MID_9/Run_"+aRunNum+"_Wave_MID_9_FILE_"+aFileNum+".dat",
    "/Users/drc_daq/scratch/Aug2022TB/SSD/SSD_Run_"+aRunNum+"/Run_"+aRunNum+"_Wave/Run_"+aRunNum+"_Wave_MID_10/Run_"+aRunNum+"_Wave_MID_10_FILE_"+aFileNum+".dat",
    "/Users/drc_daq/scratch/Aug2022TB/SSD/SSD_Run_"+aRunNum+"/Run_"+aRunNum+"_Wave/Run_"+aRunNum+"_Wave_MID_11/Run_"+aRunNum+"_Wave_MID_11_FILE_"+aFileNum+".dat",
    "/Users/drc_daq/scratch/Aug2022TB/SSD/SSD_Run_"+aRunNum+"/Run_"+aRunNum+"_Wave/Run_"+aRunNum+"_Wave_MID_12/Run_"+aRunNum+"_Wave_MID_12_FILE_"+aFileNum+".dat",
    "/Users/drc_daq/scratch/Aug2022TB/SSD/SSD_Run_"+aRunNum+"/Run_"+aRunNum+"_Wave/Run_"+aRunNum+"_Wave_MID_13/Run_"+aRunNum+"_Wave_MID_13_FILE_"+aFileNum+".dat",
    "/Users/drc_daq/scratch/Aug2022TB/SSD/SSD_Run_"+aRunNum+"/Run_"+aRunNum+"_Wave/Run_"+aRunNum+"_Wave_MID_14/Run_"+aRunNum+"_Wave_MID_14_FILE_"+aFileNum+".dat",
    "/Users/drc_daq/scratch/Aug2022TB/SSD/SSD_Run_"+aRunNum+"/Run_"+aRunNum+"_Wave/Run_"+aRunNum+"_Wave_MID_15/Run_"+aRunNum+"_Wave_MID_15_FILE_"+aFileNum+".dat"
  };
 
  TBmonit monit = TBmonit(FastFiles, WaveFiles, output);
  monit.setPedestalPath("ped_"+aPedNum+".csv");
  monit.setMappingPath("mapping_data_MCPPMT_positiveSignal.csv");
  monit.SetADCmax(DistMaxADC);
  monit.SetADCbin(DistBinADC);
  monit.SetOutputName(output);

  std::cout << " [INFO ] Monitoring : start monitoring process." << std::endl;

  monit.MonitPlots();

  std::cout << " [INFO ] Monitoring : monitoring process is done." << std::endl;


	return 0;
}