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
find_package(KF5SyntaxHighlighting)
find_package(Qt5PrintSupport REQUIRED)
find_package(Qt5Svg REQUIRED)
find_package(Qt5Test REQUIRED)

enable_testing(true)

add_executable(praes
    src/antlr/markdown/generated/markdownBaseListener.cpp
    src/antlr/markdown/generated/markdownLexer.cpp
    src/antlr/markdown/generated/markdownListener.cpp
    src/antlr/markdown/generated/markdownParser.cpp
    src/antlr/potato/generated/potatoBaseListener.cpp
    src/antlr/potato/generated/potatoLexer.cpp
    src/antlr/potato/generated/potatoListener.cpp
    src/antlr/potato/generated/potatoParser.cpp
    src/core/boxes/arrowbox.cpp
    src/core/boxes/box.cpp
    src/core/boxes/codebox.cpp
    src/core/boxes/imagebox.cpp
    src/core/boxes/linebox.cpp
    src/core/boxes/markdowntextbox.cpp
    src/core/boxes/plaintextbox.cpp
    src/core/boxes/textbox.cpp
    src/core/boxgeometry.cpp
    src/core/cachemanager.cpp
    src/core/codehighlighter.cpp
    src/core/configboxes.cpp
    src/core/equationcachemanager.cpp
    src/core/slide.cpp
    src/core/sliderenderer.cpp
    src/core/main.cpp
    src/core/markdownformatvisitor.cpp
    src/core/parser.cpp
    src/core/pdfcreator.cpp
    src/core/potatoformatvisitor.cpp
    src/core/presentation.cpp
    src/core/template.cpp
    src/core/tokenizer.cpp
    src/core/transformboxundo.cpp
    src/files.qrc
    src/ui/boxtransformation.cpp
    src/ui/slidelistdelegate.cpp
    src/ui/slidelistmodel.cpp
    src/ui/slidewidget.cpp
    src/ui/mainwindow.cpp
    src/ui/mainwindow.ui
    src/ui/snapping.cpp
    src/ui/templatelistdelegate.cpp
    src/ui/templatelistmodel.cpp
    src/ui/utils.cpp
)

add_executable(testtokenizer
    src/core/testtokenizer.cpp
    src/core/tokenizer.cpp)
add_test(NAME testtokenizer COMMAND testtokenizer)

add_executable(grammartest
    src/core/grammartest.cpp
    src/antlr/potato/generated/potatoBaseListener.cpp
    src/antlr/potato/generated/potatoLexer.cpp
    src/antlr/potato/generated/potatoListener.cpp
    src/antlr/potato/generated/potatoParser.cpp)
add_test(NAME grammartest COMMAND grammartest)

target_link_libraries(praes PRIVATE Qt5::Widgets KF5::TextEditor KF5::SyntaxHighlighting)
target_link_libraries(praes PRIVATE Qt5::PrintSupport)
target_link_libraries(praes PRIVATE Qt5::Svg)
target_link_libraries(praes PRIVATE antlr4-runtime)
target_link_libraries(testtokenizer PRIVATE Qt5::Test)
target_link_libraries(grammartest PRIVATE Qt5::Test)
target_link_libraries(grammartest PRIVATE antlr4-runtime)

target_include_directories(praes PRIVATE src/ui/ src/core/ src/core/boxes/ src/core/antlr src/antlr/markdown/generated src/antlr/potato/generated)
target_include_directories(praes SYSTEM PRIVATE /usr/include/antlr4-runtime)
target_include_directories(testtokenizer PRIVATE src/ui/ src/core/ src/core/boxes/)
target_include_directories(grammartest PRIVATE src/antlr/potato/generated/ src/core/antlr)
target_include_directories(grammartest SYSTEM PRIVATE /usr/include/antlr4-runtime)

target_compile_definitions(praes PRIVATE -DQT_NO_KEYWORDS)
target_compile_definitions(grammartest PRIVATE -DQT_NO_KEYWORDS)
