cmake_minimum_required(VERSION 3.21)

project(opus_project)

enable_language(CXX C ASM)

set(LIB_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR}/opus_lib/include/opus ${CMAKE_CURRENT_SOURCE_DIR}/opus_interface)
set(LIB_OPUS ${CMAKE_CURRENT_SOURCE_DIR}/opus_lib/lib/libopus.so)

add_executable(target main.c ${CMAKE_CURRENT_SOURCE_DIR}/opus_interface/opus_interface.c)

target_link_libraries(target ${LIB_OPUS})
target_link_libraries(target m)
target_include_directories(target PUBLIC ${LIB_INCLUDE})