cmake_minimum_required (VERSION 3.0)

set(CMAKE_CXX_FLAGS "-fPIC --shared -g")
set(CMAKE_BUILD_TYPE Debug)

project (ants)

include_directories(./)
file(GLOB SOURCES
		  ants_list.c
		  ants_map.c
		  ants_sort.c
		  ants_common.c
		  ants_lock_free_queue.c)

add_library(ants_datas STATIC ${SOURCES})
set_target_properties(ants_datas PROPERTIES DEBUG_POSTFIX "d")

add_executable(ants_list_test ants_list_test.c)
add_executable(ants_sort_test ants_sort_test.c)
add_executable(ants_map_test ants_map_test.c)
add_executable(lock_free_queue_test lock_free_queue_test.c)

target_link_libraries(ants_list_test ants_datas)
target_link_libraries(ants_sort_test ants_datas)
target_link_libraries(ants_map_test ants_datas)
target_link_libraries(lock_free_queue_test ants_datas)	
target_link_libraries(ants_map_test crypto)


