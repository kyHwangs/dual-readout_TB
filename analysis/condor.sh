#! /bin/bash

source /cvmfs/sft.cern.ch/lcg/views/LCG_102/x86_64-centos7-gcc11-opt/setup.sh

export INSTALL_DIR_PATH=/u/user/kyhwang/scratch/WorkSpace/DRC/Aug2022TB/dev_230307/dual-readout_TB/install

export X509_USER_PROXY=/u/user/$USER/proxy.cert

export LD_PRELOAD="/usr/lib64/libpdcap.so"
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$INSTALL_DIR_PATH/lib64:/usr/lib64/dcap
export PYTHONPATH=$PYTHONPATH:$INSTALL_DIR_PATH/lib64

echo "Setup complete"
echo "Will run : "

echo "$@"
eval "$@"
