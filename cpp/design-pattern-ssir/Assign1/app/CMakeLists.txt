link_directories (${PROJECT_BINARY_DIR}/lib) 
add_executable(dirApp dirApp.cpp)
target_link_libraries (dirApp libDir)
set(CMAKE_BUILD_TYPE Debug)