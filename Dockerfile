FROM ubuntu:18.04

RUN apt-get update && apt-get install -y software-properties-common && add-apt-repository ppa:ubuntu-toolchain-r/test && apt-get update && apt-get install -y gcc-11 && sudo apt install g++-11

RUN wget http://www.antlr.org/download/antlr4-cpp-runtime-4.7.2-source.zip && unzip antlr4-cpp-runtime-4.7.2-source.zip && mkdir build && cd build && cmake -DCMAKE_INSTALL_PREFIX=/usr .. && sudo make install
RUN sudo apt-get install uuid-dev pkgconf && sudo add-apt-repository ppa:beineri/opt-qt-5.15.2-bionic && sudo apt-get update && sudo apt install qt515base qt515svg qt515declarative

WORKDIR /potato
RUN mkdir /potato && git clone https://github.com/thgier/PotatoPresenter.git && mkdir build && cd build && cmake -DCMAKE_PREFIX_PATH=/opt/qt515/lib/cmake -DCMAKE_CXX_COMPILER=g++-11 .. 
RUN cd .. && ./linuxdeployqt-continuous-x86_64.AppImage potatoPresenter.desktop -qmake=/opt/qt515/bin/qmake -appimage

