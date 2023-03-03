#!/bin/bash

echo Analyze...
ghdl -a --std=08 $1.vhdl
ghdl -a --std=08 $1TB.vhdl

echo Elaborate...
ghdl -e --std=08 $1
ghdl -e --std=08 $1_tb

echo Run...
ghdl -r $1_tb --stop-time=$2ns --wave=out.ghw

 gtkwave out.ghw
