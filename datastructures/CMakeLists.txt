cmake_minimum_required (VERSION 3.0)

set(CMAKE_CXX_FLAGS "-fPIC --shared -g")
set(CMAKE_BUILD_TYPE Debug)

project (ants)

include_directories(./)
file(GLOB SOURCES
		  ants_list.c
		  ants_map.c)

add_library(ants_datas STATIC ${SOURCES})
set_target_properties(ants_datas PROPERTIES DEBUG_POSTFIX "d")

add_executable(ants_list_test ants_list_test.c)
target_link_libraries(ants_list_test ants_datas)


