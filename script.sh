#! /bin/bash

cat in.txt
rm -rf ./build
mkdir build
cp ./in.txt ./build
cd build
cmake ..
make -j2
./freq in.txt out.txt
cat out.txt