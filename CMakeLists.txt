cmake_minimum_required(VERSION 3.22)


project(QmlOpenAuto LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake_modules/")
set(QT_QML_OUTPUT_DIRECTORY  ${CMAKE_BINARY_DIR})

find_package(Qt6 6.2 COMPONENTS Quick REQUIRED)
find_package(libusb-1.0 REQUIRED)
qt_add_library(QmlOpenAuto STATIC)

qt_add_qml_module(QmlOpenAuto
    URI QmlOpenAuto
    VERSION 1.0
    SOURCES
    openautoconnector.h
    openautoconnector.cpp
    openautodevice.h
    openautodevice.cpp
)
target_compile_definitions(QmlOpenAuto
    PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
    
target_link_libraries(QmlOpenAuto PRIVATE Qt6::Quick aasdk libusb)

target_include_directories(QmlOpenAuto PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

qt_add_executable(TestApp test/main.cpp)
qt_add_qml_module(TestApp
    URI resources
    VERSION 1.0
    QML_FILES test/main.qml
)
target_link_libraries(TestApp PRIVATE Qt6::Quick QmlOpenAutoplugin)

