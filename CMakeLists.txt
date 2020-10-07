cmake_minimum_required(VERSION 3.5)

project(praes LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Widgets REQUIRED)
find_package(KF5TextEditor)

add_executable(praes
    main.cpp
    mainwindow.cpp
    mainwindow.ui
    textfinder.qrc
    frame.cpp
    textfield.cpp
    box.cpp
    parser.cpp
    painter.cpp
    paintdocument.cpp
    property.cpp
    drawtext.cpp
    formatetext.cpp
    picture.cpp
)


target_link_libraries(praes PRIVATE Qt5::Widgets KF5::TextEditor)
