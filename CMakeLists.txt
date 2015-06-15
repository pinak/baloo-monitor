cmake_minimum_required(VERSION 2.8.12)

project("Baloo Monitor")

find_package(Qt5 COMPONENTS Quick Core DBus)
include_directories($CMAKE_SOURCE_DIR/src)

set(CMAKE_AUTOMOC ON)

add_subdirectory(src)
