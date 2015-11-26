# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list

# Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/ankdesh/LearnTry/opencl/hetereogenous-opencl-book/opencl-book-samples

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ankdesh/LearnTry/opencl/hetereogenous-opencl-book/build

# Include any dependencies generated for this target.
include src/Chapter_3/OpenCLConvolution/CMakeFiles/OpenCLConvolutionChap3.dir/depend.make

# Include the progress variables for this target.
include src/Chapter_3/OpenCLConvolution/CMakeFiles/OpenCLConvolutionChap3.dir/progress.make

# Include the compile flags for this target's objects.
include src/Chapter_3/OpenCLConvolution/CMakeFiles/OpenCLConvolutionChap3.dir/flags.make

src/Chapter_3/OpenCLConvolution/CMakeFiles/OpenCLConvolutionChap3.dir/Convolution.cpp.o: src/Chapter_3/OpenCLConvolution/CMakeFiles/OpenCLConvolutionChap3.dir/flags.make
src/Chapter_3/OpenCLConvolution/CMakeFiles/OpenCLConvolutionChap3.dir/Convolution.cpp.o: /home/ankdesh/LearnTry/opencl/hetereogenous-opencl-book/opencl-book-samples/src/Chapter_3/OpenCLConvolution/Convolution.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/ankdesh/LearnTry/opencl/hetereogenous-opencl-book/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object src/Chapter_3/OpenCLConvolution/CMakeFiles/OpenCLConvolutionChap3.dir/Convolution.cpp.o"
	cd /home/ankdesh/LearnTry/opencl/hetereogenous-opencl-book/build/src/Chapter_3/OpenCLConvolution && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/OpenCLConvolutionChap3.dir/Convolution.cpp.o -c /home/ankdesh/LearnTry/opencl/hetereogenous-opencl-book/opencl-book-samples/src/Chapter_3/OpenCLConvolution/Convolution.cpp

src/Chapter_3/OpenCLConvolution/CMakeFiles/OpenCLConvolutionChap3.dir/Convolution.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/OpenCLConvolutionChap3.dir/Convolution.cpp.i"
	cd /home/ankdesh/LearnTry/opencl/hetereogenous-opencl-book/build/src/Chapter_3/OpenCLConvolution && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/ankdesh/LearnTry/opencl/hetereogenous-opencl-book/opencl-book-samples/src/Chapter_3/OpenCLConvolution/Convolution.cpp > CMakeFiles/OpenCLConvolutionChap3.dir/Convolution.cpp.i

src/Chapter_3/OpenCLConvolution/CMakeFiles/OpenCLConvolutionChap3.dir/Convolution.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/OpenCLConvolutionChap3.dir/Convolution.cpp.s"
	cd /home/ankdesh/LearnTry/opencl/hetereogenous-opencl-book/build/src/Chapter_3/OpenCLConvolution && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/ankdesh/LearnTry/opencl/hetereogenous-opencl-book/opencl-book-samples/src/Chapter_3/OpenCLConvolution/Convolution.cpp -o CMakeFiles/OpenCLConvolutionChap3.dir/Convolution.cpp.s

src/Chapter_3/OpenCLConvolution/CMakeFiles/OpenCLConvolutionChap3.dir/Convolution.cpp.o.requires:
.PHONY : src/Chapter_3/OpenCLConvolution/CMakeFiles/OpenCLConvolutionChap3.dir/Convolution.cpp.o.requires

src/Chapter_3/OpenCLConvolution/CMakeFiles/OpenCLConvolutionChap3.dir/Convolution.cpp.o.provides: src/Chapter_3/OpenCLConvolution/CMakeFiles/OpenCLConvolutionChap3.dir/Convolution.cpp.o.requires
	$(MAKE) -f src/Chapter_3/OpenCLConvolution/CMakeFiles/OpenCLConvolutionChap3.dir/build.make src/Chapter_3/OpenCLConvolution/CMakeFiles/OpenCLConvolutionChap3.dir/Convolution.cpp.o.provides.build
.PHONY : src/Chapter_3/OpenCLConvolution/CMakeFiles/OpenCLConvolutionChap3.dir/Convolution.cpp.o.provides

src/Chapter_3/OpenCLConvolution/CMakeFiles/OpenCLConvolutionChap3.dir/Convolution.cpp.o.provides.build: src/Chapter_3/OpenCLConvolution/CMakeFiles/OpenCLConvolutionChap3.dir/Convolution.cpp.o

# Object files for target OpenCLConvolutionChap3
OpenCLConvolutionChap3_OBJECTS = \
"CMakeFiles/OpenCLConvolutionChap3.dir/Convolution.cpp.o"

# External object files for target OpenCLConvolutionChap3
OpenCLConvolutionChap3_EXTERNAL_OBJECTS =

src/Chapter_3/OpenCLConvolution/OpenCLConvolutionChap3: src/Chapter_3/OpenCLConvolution/CMakeFiles/OpenCLConvolutionChap3.dir/Convolution.cpp.o
src/Chapter_3/OpenCLConvolution/OpenCLConvolutionChap3: src/Chapter_3/OpenCLConvolution/CMakeFiles/OpenCLConvolutionChap3.dir/build.make
src/Chapter_3/OpenCLConvolution/OpenCLConvolutionChap3: /usr/lib/x86_64-linux-gnu/libOpenCL.so
src/Chapter_3/OpenCLConvolution/OpenCLConvolutionChap3: src/Chapter_3/OpenCLConvolution/CMakeFiles/OpenCLConvolutionChap3.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable OpenCLConvolutionChap3"
	cd /home/ankdesh/LearnTry/opencl/hetereogenous-opencl-book/build/src/Chapter_3/OpenCLConvolution && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/OpenCLConvolutionChap3.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/Chapter_3/OpenCLConvolution/CMakeFiles/OpenCLConvolutionChap3.dir/build: src/Chapter_3/OpenCLConvolution/OpenCLConvolutionChap3
.PHONY : src/Chapter_3/OpenCLConvolution/CMakeFiles/OpenCLConvolutionChap3.dir/build

src/Chapter_3/OpenCLConvolution/CMakeFiles/OpenCLConvolutionChap3.dir/requires: src/Chapter_3/OpenCLConvolution/CMakeFiles/OpenCLConvolutionChap3.dir/Convolution.cpp.o.requires
.PHONY : src/Chapter_3/OpenCLConvolution/CMakeFiles/OpenCLConvolutionChap3.dir/requires

src/Chapter_3/OpenCLConvolution/CMakeFiles/OpenCLConvolutionChap3.dir/clean:
	cd /home/ankdesh/LearnTry/opencl/hetereogenous-opencl-book/build/src/Chapter_3/OpenCLConvolution && $(CMAKE_COMMAND) -P CMakeFiles/OpenCLConvolutionChap3.dir/cmake_clean.cmake
.PHONY : src/Chapter_3/OpenCLConvolution/CMakeFiles/OpenCLConvolutionChap3.dir/clean

src/Chapter_3/OpenCLConvolution/CMakeFiles/OpenCLConvolutionChap3.dir/depend:
	cd /home/ankdesh/LearnTry/opencl/hetereogenous-opencl-book/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ankdesh/LearnTry/opencl/hetereogenous-opencl-book/opencl-book-samples /home/ankdesh/LearnTry/opencl/hetereogenous-opencl-book/opencl-book-samples/src/Chapter_3/OpenCLConvolution /home/ankdesh/LearnTry/opencl/hetereogenous-opencl-book/build /home/ankdesh/LearnTry/opencl/hetereogenous-opencl-book/build/src/Chapter_3/OpenCLConvolution /home/ankdesh/LearnTry/opencl/hetereogenous-opencl-book/build/src/Chapter_3/OpenCLConvolution/CMakeFiles/OpenCLConvolutionChap3.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/Chapter_3/OpenCLConvolution/CMakeFiles/OpenCLConvolutionChap3.dir/depend
