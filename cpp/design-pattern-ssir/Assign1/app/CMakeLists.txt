link_directories (${PROJECT_BINARY_DIR}/lib) 
add_executable(dirApp test1.cpp)
target_link_libraries (dirApp libDir)