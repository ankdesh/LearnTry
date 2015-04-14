# Install script for directory: /home/ankdesh/LearnTry/opencl/hetereogenous-opencl-book/opencl-book-samples/src

# Set the install prefix
IF(NOT DEFINED CMAKE_INSTALL_PREFIX)
  SET(CMAKE_INSTALL_PREFIX "/usr/local")
ENDIF(NOT DEFINED CMAKE_INSTALL_PREFIX)
STRING(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
IF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  IF(BUILD_TYPE)
    STRING(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  ELSE(BUILD_TYPE)
    SET(CMAKE_INSTALL_CONFIG_NAME "")
  ENDIF(BUILD_TYPE)
  MESSAGE(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
ENDIF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)

# Set the component getting installed.
IF(NOT CMAKE_INSTALL_COMPONENT)
  IF(COMPONENT)
    MESSAGE(STATUS "Install component: \"${COMPONENT}\"")
    SET(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  ELSE(COMPONENT)
    SET(CMAKE_INSTALL_COMPONENT)
  ENDIF(COMPONENT)
ENDIF(NOT CMAKE_INSTALL_COMPONENT)

# Install shared libraries without execute permission?
IF(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  SET(CMAKE_INSTALL_SO_NO_EXE "1")
ENDIF(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)

IF(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  INCLUDE("/home/ankdesh/LearnTry/opencl/hetereogenous-opencl-book/build/src/Chapter_2/HelloWorld/cmake_install.cmake")
  INCLUDE("/home/ankdesh/LearnTry/opencl/hetereogenous-opencl-book/build/src/Chapter_3/OpenCLInfo/cmake_install.cmake")
  INCLUDE("/home/ankdesh/LearnTry/opencl/hetereogenous-opencl-book/build/src/Chapter_3/OpenCLConvolution/cmake_install.cmake")
  INCLUDE("/home/ankdesh/LearnTry/opencl/hetereogenous-opencl-book/build/src/Chapter_6/HelloBinaryWorld/cmake_install.cmake")
  INCLUDE("/home/ankdesh/LearnTry/opencl/hetereogenous-opencl-book/build/src/Chapter_7/SimpleBufferSubBuffer/cmake_install.cmake")
  INCLUDE("/home/ankdesh/LearnTry/opencl/hetereogenous-opencl-book/build/src/Chapter_8/ImageFilter2D/cmake_install.cmake")
  INCLUDE("/home/ankdesh/LearnTry/opencl/hetereogenous-opencl-book/build/src/Chapter_12/VectorAdd/cmake_install.cmake")
  INCLUDE("/home/ankdesh/LearnTry/opencl/hetereogenous-opencl-book/build/src/Chapter_14/histogram/cmake_install.cmake")
  INCLUDE("/home/ankdesh/LearnTry/opencl/hetereogenous-opencl-book/build/src/Chapter_16/Dijkstra/cmake_install.cmake")
  INCLUDE("/home/ankdesh/LearnTry/opencl/hetereogenous-opencl-book/build/src/Chapter_22/cmake_install.cmake")
  INCLUDE("/home/ankdesh/LearnTry/opencl/hetereogenous-opencl-book/build/src/Chapter_12/Sinewave/cmake_install.cmake")

ENDIF(NOT CMAKE_INSTALL_LOCAL_ONLY)

