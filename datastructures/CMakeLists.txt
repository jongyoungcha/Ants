cmake_minimum_required (VERSION 3.0)
set(CMAKE_CXX_FLAGS "-fPIC --shared")
project (ants)
include_directories(./)

file(GLOB SOURCES
    ./*.h
    ./*.c
)

add_library(ants_datas SHARED ${SOURCES})
