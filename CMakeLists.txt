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
    src/core/boxes/arrowbox.cpp
    src/core/boxes/box.cpp
    src/core/boxes/boxgeometry.cpp
    src/core/boxes/cachemanager.cpp
    src/core/boxes/equationcachemanager.cpp
    src/core/boxes/linebox.cpp
    src/core/boxes/markdowntextbox.cpp
    src/core/boxes/imagebox.cpp
    src/core/boxes/textbox.cpp
    src/core/boxes/plaintextbox.cpp
    src/core/configboxes.cpp
    src/core/frame.cpp
    src/core/main.cpp
    src/core/pdfcreator.cpp
    src/ui/mainwindow.cpp
    src/ui/mainwindow.ui
    src/core/framepainter.cpp
    src/core/parser.cpp
    src/core/presentation.cpp
    src/core/template.cpp
    src/core/tokenizer.cpp
    src/core/transformboxundo.cpp
    src/core/markdownformatvisitor.cpp
    src/antlr/generated/markdownParser.cpp
    src/antlr/generated/markdownListener.cpp
    src/antlr/generated/markdownLexer.cpp
    src/antlr/generated/markdownBaseListener.cpp
    src/files.qrc
    src/ui/boxtransformation.cpp
    src/ui/framelistdelegate.cpp
    src/ui/framelistmodel.cpp
    src/ui/framewidget.cpp
)

add_executable(testtokenizer
    src/core/testtokenizer.cpp
    src/core/tokenizer.cpp)
add_test(NAME testtokenizer COMMAND testtokenizer)

target_link_libraries(praes PRIVATE Qt5::Widgets KF5::TextEditor)
target_link_libraries(praes PRIVATE Qt5::PrintSupport)
target_link_libraries(praes PRIVATE Qt5::Svg)
target_link_libraries(testtokenizer PRIVATE Qt5::Test)
target_link_libraries(praes PRIVATE antlr4-runtime)

target_include_directories(praes PRIVATE src/ui/ src/core/ src/core/boxes/ src/core/antlr src/antlr/generated)
target_include_directories(praes SYSTEM PRIVATE /usr/include/antlr4-runtime)
target_include_directories(testtokenizer PRIVATE src/ui/ src/core/ src/core/boxes/)

target_compile_definitions(praes PRIVATE -DQT_NO_KEYWORDS)
