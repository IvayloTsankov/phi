#!/bin/bash

git --version

is_git=$?

# Install git if missing
if [ $is_git -ne 0 ]
then
    echo "Installing git..."
    sudo apt-get install -y git
fi

mkdir -p third_party
cd third_party


# get libs
git clone https://github.com/IvayloTsankov/slog

#get png++
mkdir -p temp
cd temp
wget "http://download.savannah.gnu.org/releases/pngpp/png++-0.2.9.tar.gz"
tar -zxf png++-0.2.9.tar.gz
cd *
make
make install PREFIX=../
cd ..
mv include/png++ ../
cd ..
rm -rf temp

# Install package config tool needed by Makefile
pkg-config --version

is_pkg=$?
if [ $is_pkg -ne 0 ]
then
    echo "Installing pkg-config..."
    sudo apt-get install -y pkg-config
fi



# create folder for images
cd ..
mkdir -p images
