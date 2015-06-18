cmake_minimum_required(VERSION 2.8.12)

project("Baloo Monitor")

find_package(ECM 0.0.9 REQUIRED NO_MODULE)
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake" ${ECM_MODULE_PATH})

find_package(Qt5 REQUIRED COMPONENTS Quick Core DBus)

include(KDEInstallDirs)
include(KDECMakeSettings)
include(KDECompilerSettings)

include_directories($CMAKE_SOURCE_DIR/src)

add_subdirectory(src)
