#!/bin/bash

set -xe

mkdir /potato
mkdir /install
cd /potato

git clone https://github.com/thgier/PotatoPresenter.git

cd PotatoPresenter

git checkout $1

mkdir build
cd build

cmake -DCMAKE_PREFIX_PATH=/opt/qt515/lib/cmake -DCMAKE_CXX_COMPILER=g++-11 -DCMAKE_CXX_FLAGS="-static-libstdc++ -static-libgcc" -DCMAKE_INSTALL_PREFIX=/install/usr ..

make -j$(nproc) install

/linuxdeployqt/linuxdeployqt-continuous-x86_64.AppImage --appimage-extract-and-run /install/usr/share/applications/potatoPresenter.desktop -qmake=/opt/qt515/bin/qmake -appimage
mv *.AppImage /potatoPresenter.AppImage
