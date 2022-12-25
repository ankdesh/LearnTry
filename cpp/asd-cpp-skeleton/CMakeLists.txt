cmake_minimum_required(VERSION 2.8)
project (AsdTestPrj)

SET( CMAKE_CXX_FLAGS -std=c++11 )
include_directories("${PROJECT_SOURCE_DIR}/include")

add_subdirectory (lib)
add_subdirectory (test)
