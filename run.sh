!#/bin/bash

# building 
cmake -S . -B build

# move to build repository
cd build

    ########
make

# run 
./Tetris_NH

#go back 
cd ..