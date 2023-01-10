cmake_minimum_required(VERSION 2.8)
project (AsdTestPrj)

execute_process (
    COMMAND bash -c "pkg-config SST-12.0.0 --libs"
    OUTPUT_VARIABLE SST_LIBS
)

execute_process (
    COMMAND bash -c "pkg-config SST-12.0.0 --cflags"
    OUTPUT_VARIABLE SST_CFLAGS
)

SET( CMAKE_CXX_FLAGS ${SST_CFLAGS} -std=c++11 )
SET( CMAKE_EXE_LINKER_FLAGS -shared -fno-common ${SST_LIBS} )
include_directories("${PROJECT_SOURCE_DIR}/include")


message("Flags used for SST LIBS:  " ${SST_LIBS})
message("Flags used for SST CFLAGS:  " ${SST_CFLAGS})

add_subdirectory (src)
#add_subdirectory (test)
