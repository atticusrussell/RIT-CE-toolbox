#!/bin/bash

#AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAHHHHHHHHH!!!!!!!!!
app=$1
install-peerdeps $app || npm i $app
