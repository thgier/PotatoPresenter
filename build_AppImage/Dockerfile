FROM ubuntu:18.04

RUN apt-get update && apt-get install -y software-properties-common && add-apt-repository ppa:ubuntu-toolchain-r/test && apt-get update && apt-get install -y gcc-11 && apt-get install -y g++-11

RUN apt-get -y install uuid-dev pkgconf && add-apt-repository ppa:beineri/opt-qt-5.15.2-bionic && apt-get -y update && apt-get install -y qt515base qt515svg qt515declarative

RUN apt-get install -y libkf5texteditor-dev libkf5syntaxhighlighting-dev

RUN apt-get install -y gpg wget && wget -O - https://apt.kitware.com/keys/kitware-archive-latest.asc 2>/dev/null | gpg --dearmor - | tee /etc/apt/trusted.gpg.d/kitware.gpg >/dev/null && apt-add-repository 'deb https://apt.kitware.com/ubuntu/ bionic main' && apt-get update && apt-get install -y cmake

WORKDIR /antlr4
RUN apt-get install -y unzip && wget http://www.antlr.org/download/antlr4-cpp-runtime-4.7.2-source.zip && unzip antlr4-cpp-runtime-4.7.2-source.zip && mkdir build && cd build && cmake -DCMAKE_INSTALL_PREFIX=/usr -DCMAKE_CXX_COMPILER=g++-11 -DCMAKE_CXX_FLAGS="-static-libstdc++ -static-libgcc" ..  && make -j2 install 

WORKDIR /linuxdeployqt
RUN wget https://github.com/probonopd/linuxdeployqt/releases/download/continuous/linuxdeployqt-continuous-x86_64.AppImage && chmod a+x linuxdeployqt-continuous-x86_64.AppImage && sed '0,/AI\x02/{s|AI\x02|\x00\x00\x00|}' -i linuxdeployqt-continuous-x86_64.AppImage

RUN apt-get install -y git gettext fuse

