cmake_minimum_required(VERSION 2.8)
project (dir)

SET( CMAKE_CXX_FLAGS -std=c++11 )
include_directories("${PROJECT_SOURCE_DIR}/include")

add_subdirectory (src)
add_subdirectory (app)