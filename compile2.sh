#!usr/bin/sh

cd build
cmake .
cmake --build .
mv sample_openMP ..
cd ..

