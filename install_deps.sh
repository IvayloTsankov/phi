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

git clone https://github.com/IvayloTsankov/slog


# Install package config tool needed by Makefile
pkg-config --version

is_pkg=$?
if [ $is_pkg -ne 0 ]
then
    echo "Installing pkg-config..."
    sudo apt-get install -y pkg-config
fi


# create folder for images
mkdir -p images
