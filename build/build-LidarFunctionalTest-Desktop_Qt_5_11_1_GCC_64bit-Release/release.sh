#!/bin/sh

exe="LidarFunctionalTest"
des="/home/mango/myQT/build-LidarFunctionalTest-Desktop_Qt_5_11_1_GCC_64bit-Release/ldd"

deplist=$(ldd $exe | awk  '{if (match($3,"/")){ printf("%s "),$3 } }')
cp $deplist $des
