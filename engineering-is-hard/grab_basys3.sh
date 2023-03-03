#!/bin/bash
cd ~/Downloads
mkdir eih_basys3_board_file
cd eih_basys3_board_file
wget https://github.com/Digilent/vivado-boards/archive/master.zip
unzip master.zip
cd vivado-boards-master/new/board_files
cp -r basys3 $1/data/boards/board_files
