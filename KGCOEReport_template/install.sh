#!/bin/bash
# Simple install script for standard install of texlive on ubuntu

INSTALL_DIR_NAME=KGCOEReport_template
TEXMF_PATH=$HOME/texmf/tex/latex
INSTALL_DIR=$TEXMF_PATH/$INSTALL_DIR_NAME
FILES_TO_COPY="KGCOEReport.cls imgs/RIT_Report.png"

if [[ ! -e $INSTALL_DIR ]]; then
  echo Install directory doesent exist creating it...
  mkdir $INSTALL_DIR
fi

for FILE in $FILES_TO_COPY; do
  echo Copying over $FILE to $INSTALL_DIR
  cp $FILE $INSTALL_DIR
done  
