#!/bin/bash

# Might need:
# sudo pip3 uninstall numpy

/usr/bin/ruby -e "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install)"
echo | "\n"
brew install python3
python3 -V
sudo python3 get-pip.py
curl 'https://bootstrap.pypa.io/get-pip.py' > get-pip.py && sudo python get-pip.py
pip3 -V
sudo pip3 install --upgrade --ignore-installed --install-option '--install-data=/usr/local' numpy
sudo pip3 install --ignore-install six
sudo easy_install --upgrade pip
sudo easy_install mpmath
sudo pip3 install networkx
sudo easy_install nose
sudo easy_install tornado
sudo pip3 install tensorflow
sudo pip3 install --ignore-install keras
Python3 Keras_Example.py