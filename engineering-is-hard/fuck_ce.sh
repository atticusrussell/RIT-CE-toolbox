#!/bin/bash
# Rename files so fucking mycourses will fucking take them
#example: ./fuck_ce.sh .vhd .vhd.txt

for file in *$1; do
    mv "$file" "$(basename "$file" $1)$2"
done
