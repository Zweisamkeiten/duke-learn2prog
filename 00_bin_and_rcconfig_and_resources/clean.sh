#!/bin/bash
fd -d 1 --hidden '[^(match5)(poker)(subseq)(power)(clean.sh)(rot_matrix)]' --exec rm -rf
mv ~/t/home-archive.zip .
unzip home-archive.zip
