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
include src/Chapter_12/Sinewave/CMakeFiles/sinewave.dir/depend.make

# Include the progress variables for this target.
include src/Chapter_12/Sinewave/CMakeFiles/sinewave.dir/progress.make

# Include the compile flags for this target's objects.
include src/Chapter_12/Sinewave/CMakeFiles/sinewave.dir/flags.make

src/Chapter_12/Sinewave/CMakeFiles/sinewave.dir/sinewave.cpp.o: src/Chapter_12/Sinewave/CMakeFiles/sinewave.dir/flags.make
src/Chapter_12/Sinewave/CMakeFiles/sinewave.dir/sinewave.cpp.o: /home/ankdesh/LearnTry/opencl/hetereogenous-opencl-book/opencl-book-samples/src/Chapter_12/Sinewave/sinewave.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/ankdesh/LearnTry/opencl/hetereogenous-opencl-book/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object src/Chapter_12/Sinewave/CMakeFiles/sinewave.dir/sinewave.cpp.o"
	cd /home/ankdesh/LearnTry/opencl/hetereogenous-opencl-book/build/src/Chapter_12/Sinewave && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/sinewave.dir/sinewave.cpp.o -c /home/ankdesh/LearnTry/opencl/hetereogenous-opencl-book/opencl-book-samples/src/Chapter_12/Sinewave/sinewave.cpp

src/Chapter_12/Sinewave/CMakeFiles/sinewave.dir/sinewave.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sinewave.dir/sinewave.cpp.i"
	cd /home/ankdesh/LearnTry/opencl/hetereogenous-opencl-book/build/src/Chapter_12/Sinewave && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/ankdesh/LearnTry/opencl/hetereogenous-opencl-book/opencl-book-samples/src/Chapter_12/Sinewave/sinewave.cpp > CMakeFiles/sinewave.dir/sinewave.cpp.i

src/Chapter_12/Sinewave/CMakeFiles/sinewave.dir/sinewave.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sinewave.dir/sinewave.cpp.s"
	cd /home/ankdesh/LearnTry/opencl/hetereogenous-opencl-book/build/src/Chapter_12/Sinewave && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/ankdesh/LearnTry/opencl/hetereogenous-opencl-book/opencl-book-samples/src/Chapter_12/Sinewave/sinewave.cpp -o CMakeFiles/sinewave.dir/sinewave.cpp.s

src/Chapter_12/Sinewave/CMakeFiles/sinewave.dir/sinewave.cpp.o.requires:
.PHONY : src/Chapter_12/Sinewave/CMakeFiles/sinewave.dir/sinewave.cpp.o.requires

src/Chapter_12/Sinewave/CMakeFiles/sinewave.dir/sinewave.cpp.o.provides: src/Chapter_12/Sinewave/CMakeFiles/sinewave.dir/sinewave.cpp.o.requires
	$(MAKE) -f src/Chapter_12/Sinewave/CMakeFiles/sinewave.dir/build.make src/Chapter_12/Sinewave/CMakeFiles/sinewave.dir/sinewave.cpp.o.provides.build
.PHONY : src/Chapter_12/Sinewave/CMakeFiles/sinewave.dir/sinewave.cpp.o.provides

src/Chapter_12/Sinewave/CMakeFiles/sinewave.dir/sinewave.cpp.o.provides.build: src/Chapter_12/Sinewave/CMakeFiles/sinewave.dir/sinewave.cpp.o

# Object files for target sinewave
sinewave_OBJECTS = \
"CMakeFiles/sinewave.dir/sinewave.cpp.o"

# External object files for target sinewave
sinewave_EXTERNAL_OBJECTS =

src/Chapter_12/Sinewave/sinewave: src/Chapter_12/Sinewave/CMakeFiles/sinewave.dir/sinewave.cpp.o
src/Chapter_12/Sinewave/sinewave: src/Chapter_12/Sinewave/CMakeFiles/sinewave.dir/build.make
src/Chapter_12/Sinewave/sinewave: /usr/lib/x86_64-linux-gnu/libOpenCL.so
src/Chapter_12/Sinewave/sinewave: src/Chapter_12/Sinewave/CMakeFiles/sinewave.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable sinewave"
	cd /home/ankdesh/LearnTry/opencl/hetereogenous-opencl-book/build/src/Chapter_12/Sinewave && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/sinewave.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/Chapter_12/Sinewave/CMakeFiles/sinewave.dir/build: src/Chapter_12/Sinewave/sinewave
.PHONY : src/Chapter_12/Sinewave/CMakeFiles/sinewave.dir/build

src/Chapter_12/Sinewave/CMakeFiles/sinewave.dir/requires: src/Chapter_12/Sinewave/CMakeFiles/sinewave.dir/sinewave.cpp.o.requires
.PHONY : src/Chapter_12/Sinewave/CMakeFiles/sinewave.dir/requires

src/Chapter_12/Sinewave/CMakeFiles/sinewave.dir/clean:
	cd /home/ankdesh/LearnTry/opencl/hetereogenous-opencl-book/build/src/Chapter_12/Sinewave && $(CMAKE_COMMAND) -P CMakeFiles/sinewave.dir/cmake_clean.cmake
.PHONY : src/Chapter_12/Sinewave/CMakeFiles/sinewave.dir/clean

src/Chapter_12/Sinewave/CMakeFiles/sinewave.dir/depend:
	cd /home/ankdesh/LearnTry/opencl/hetereogenous-opencl-book/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ankdesh/LearnTry/opencl/hetereogenous-opencl-book/opencl-book-samples /home/ankdesh/LearnTry/opencl/hetereogenous-opencl-book/opencl-book-samples/src/Chapter_12/Sinewave /home/ankdesh/LearnTry/opencl/hetereogenous-opencl-book/build /home/ankdesh/LearnTry/opencl/hetereogenous-opencl-book/build/src/Chapter_12/Sinewave /home/ankdesh/LearnTry/opencl/hetereogenous-opencl-book/build/src/Chapter_12/Sinewave/CMakeFiles/sinewave.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/Chapter_12/Sinewave/CMakeFiles/sinewave.dir/depend

