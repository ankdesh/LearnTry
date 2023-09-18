link_directories (${PROJECT_BINARY_DIR}/lib) 

add_executable(test1 unittest_abc.cpp)
target_link_libraries (test1 tempLib) 

