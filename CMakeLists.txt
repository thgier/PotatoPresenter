cmake_minimum_required(VERSION 3.5)

project(praes LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Widgets REQUIRED)
find_package(KF5TextEditor)
find_package(Qt5PrintSupport REQUIRED)
find_package(Qt5Svg REQUIRED)
find_package(Qt5Test REQUIRED)

enable_testing(true)

add_executable(praes
    main.cpp
    mainwindow.cpp
    mainwindow.ui
    files.qrc
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
    configboxes.cpp
    layout.cpp
    equationcachemanager.cpp
    imagecachemanager.cpp
    framelistmodel.cpp
    framelistdelegate.cpp
    presentation.cpp
    tokenizer.cpp
    boxgeometry.cpp
    boxtransformation.cpp
    arrowbox.cpp
    template.cpp
)

add_executable(testtokenizer
    testtokenizer.cpp
    tokenizer.cpp)
add_test(NAME testtokenizer COMMAND testtokenizer)

target_link_libraries(praes PRIVATE Qt5::Widgets KF5::TextEditor)
target_link_libraries(praes PRIVATE Qt5::PrintSupport)
target_link_libraries(praes PRIVATE Qt5::Svg)
target_link_libraries(testtokenizer PRIVATE Qt5::Test)
