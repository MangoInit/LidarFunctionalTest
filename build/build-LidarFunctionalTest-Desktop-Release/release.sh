#!/bin/sh

exe="LidarFunctionalTest"
des="/home/mango/myQT/build-LidarFunctionalTest-Desktop-Release/ldd"

deplist=$(ldd $exe | awk  '{if (match($3,"/")){ printf("%s "),$3 } }')
cp $deplist $des
