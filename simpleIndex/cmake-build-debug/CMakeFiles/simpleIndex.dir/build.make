# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.17

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Disable VCS-based implicit rules.
% : %,v


# Disable VCS-based implicit rules.
% : RCS/%


# Disable VCS-based implicit rules.
% : RCS/%,v


# Disable VCS-based implicit rules.
% : SCCS/s.%


# Disable VCS-based implicit rules.
% : s.%


.SUFFIXES: .hpux_make_needs_suffix_list


# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

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
CMAKE_COMMAND = /snap/clion/139/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /snap/clion/139/bin/cmake/linux/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/nagy/CLionProjects/bigd/simpleIndex

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/nagy/CLionProjects/bigd/simpleIndex/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/simpleIndex.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/simpleIndex.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/simpleIndex.dir/flags.make

CMakeFiles/simpleIndex.dir/src/main.C.o: CMakeFiles/simpleIndex.dir/flags.make
CMakeFiles/simpleIndex.dir/src/main.C.o: ../src/main.C
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/nagy/CLionProjects/bigd/simpleIndex/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/simpleIndex.dir/src/main.C.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/simpleIndex.dir/src/main.C.o -c /home/nagy/CLionProjects/bigd/simpleIndex/src/main.C

CMakeFiles/simpleIndex.dir/src/main.C.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/simpleIndex.dir/src/main.C.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/nagy/CLionProjects/bigd/simpleIndex/src/main.C > CMakeFiles/simpleIndex.dir/src/main.C.i

CMakeFiles/simpleIndex.dir/src/main.C.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/simpleIndex.dir/src/main.C.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/nagy/CLionProjects/bigd/simpleIndex/src/main.C -o CMakeFiles/simpleIndex.dir/src/main.C.s

CMakeFiles/simpleIndex.dir/src/mysql.C.o: CMakeFiles/simpleIndex.dir/flags.make
CMakeFiles/simpleIndex.dir/src/mysql.C.o: ../src/mysql.C
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/nagy/CLionProjects/bigd/simpleIndex/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/simpleIndex.dir/src/mysql.C.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/simpleIndex.dir/src/mysql.C.o -c /home/nagy/CLionProjects/bigd/simpleIndex/src/mysql.C

CMakeFiles/simpleIndex.dir/src/mysql.C.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/simpleIndex.dir/src/mysql.C.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/nagy/CLionProjects/bigd/simpleIndex/src/mysql.C > CMakeFiles/simpleIndex.dir/src/mysql.C.i

CMakeFiles/simpleIndex.dir/src/mysql.C.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/simpleIndex.dir/src/mysql.C.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/nagy/CLionProjects/bigd/simpleIndex/src/mysql.C -o CMakeFiles/simpleIndex.dir/src/mysql.C.s

CMakeFiles/simpleIndex.dir/src/onebar.C.o: CMakeFiles/simpleIndex.dir/flags.make
CMakeFiles/simpleIndex.dir/src/onebar.C.o: ../src/onebar.C
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/nagy/CLionProjects/bigd/simpleIndex/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/simpleIndex.dir/src/onebar.C.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/simpleIndex.dir/src/onebar.C.o -c /home/nagy/CLionProjects/bigd/simpleIndex/src/onebar.C

CMakeFiles/simpleIndex.dir/src/onebar.C.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/simpleIndex.dir/src/onebar.C.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/nagy/CLionProjects/bigd/simpleIndex/src/onebar.C > CMakeFiles/simpleIndex.dir/src/onebar.C.i

CMakeFiles/simpleIndex.dir/src/onebar.C.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/simpleIndex.dir/src/onebar.C.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/nagy/CLionProjects/bigd/simpleIndex/src/onebar.C -o CMakeFiles/simpleIndex.dir/src/onebar.C.s

CMakeFiles/simpleIndex.dir/src/symbol.C.o: CMakeFiles/simpleIndex.dir/flags.make
CMakeFiles/simpleIndex.dir/src/symbol.C.o: ../src/symbol.C
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/nagy/CLionProjects/bigd/simpleIndex/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/simpleIndex.dir/src/symbol.C.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/simpleIndex.dir/src/symbol.C.o -c /home/nagy/CLionProjects/bigd/simpleIndex/src/symbol.C

CMakeFiles/simpleIndex.dir/src/symbol.C.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/simpleIndex.dir/src/symbol.C.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/nagy/CLionProjects/bigd/simpleIndex/src/symbol.C > CMakeFiles/simpleIndex.dir/src/symbol.C.i

CMakeFiles/simpleIndex.dir/src/symbol.C.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/simpleIndex.dir/src/symbol.C.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/nagy/CLionProjects/bigd/simpleIndex/src/symbol.C -o CMakeFiles/simpleIndex.dir/src/symbol.C.s

CMakeFiles/simpleIndex.dir/src/iSax.cpp.o: CMakeFiles/simpleIndex.dir/flags.make
CMakeFiles/simpleIndex.dir/src/iSax.cpp.o: ../src/iSax.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/nagy/CLionProjects/bigd/simpleIndex/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/simpleIndex.dir/src/iSax.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/simpleIndex.dir/src/iSax.cpp.o -c /home/nagy/CLionProjects/bigd/simpleIndex/src/iSax.cpp

CMakeFiles/simpleIndex.dir/src/iSax.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/simpleIndex.dir/src/iSax.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/nagy/CLionProjects/bigd/simpleIndex/src/iSax.cpp > CMakeFiles/simpleIndex.dir/src/iSax.cpp.i

CMakeFiles/simpleIndex.dir/src/iSax.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/simpleIndex.dir/src/iSax.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/nagy/CLionProjects/bigd/simpleIndex/src/iSax.cpp -o CMakeFiles/simpleIndex.dir/src/iSax.cpp.s

CMakeFiles/simpleIndex.dir/src/EnvelopGen.cpp.o: CMakeFiles/simpleIndex.dir/flags.make
CMakeFiles/simpleIndex.dir/src/EnvelopGen.cpp.o: ../src/EnvelopGen.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/nagy/CLionProjects/bigd/simpleIndex/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/simpleIndex.dir/src/EnvelopGen.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/simpleIndex.dir/src/EnvelopGen.cpp.o -c /home/nagy/CLionProjects/bigd/simpleIndex/src/EnvelopGen.cpp

CMakeFiles/simpleIndex.dir/src/EnvelopGen.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/simpleIndex.dir/src/EnvelopGen.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/nagy/CLionProjects/bigd/simpleIndex/src/EnvelopGen.cpp > CMakeFiles/simpleIndex.dir/src/EnvelopGen.cpp.i

CMakeFiles/simpleIndex.dir/src/EnvelopGen.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/simpleIndex.dir/src/EnvelopGen.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/nagy/CLionProjects/bigd/simpleIndex/src/EnvelopGen.cpp -o CMakeFiles/simpleIndex.dir/src/EnvelopGen.cpp.s

CMakeFiles/simpleIndex.dir/src/breakpoints.cpp.o: CMakeFiles/simpleIndex.dir/flags.make
CMakeFiles/simpleIndex.dir/src/breakpoints.cpp.o: ../src/breakpoints.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/nagy/CLionProjects/bigd/simpleIndex/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/simpleIndex.dir/src/breakpoints.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/simpleIndex.dir/src/breakpoints.cpp.o -c /home/nagy/CLionProjects/bigd/simpleIndex/src/breakpoints.cpp

CMakeFiles/simpleIndex.dir/src/breakpoints.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/simpleIndex.dir/src/breakpoints.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/nagy/CLionProjects/bigd/simpleIndex/src/breakpoints.cpp > CMakeFiles/simpleIndex.dir/src/breakpoints.cpp.i

CMakeFiles/simpleIndex.dir/src/breakpoints.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/simpleIndex.dir/src/breakpoints.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/nagy/CLionProjects/bigd/simpleIndex/src/breakpoints.cpp -o CMakeFiles/simpleIndex.dir/src/breakpoints.cpp.s

CMakeFiles/simpleIndex.dir/src/binarySearchTree.cpp.o: CMakeFiles/simpleIndex.dir/flags.make
CMakeFiles/simpleIndex.dir/src/binarySearchTree.cpp.o: ../src/binarySearchTree.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/nagy/CLionProjects/bigd/simpleIndex/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/simpleIndex.dir/src/binarySearchTree.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/simpleIndex.dir/src/binarySearchTree.cpp.o -c /home/nagy/CLionProjects/bigd/simpleIndex/src/binarySearchTree.cpp

CMakeFiles/simpleIndex.dir/src/binarySearchTree.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/simpleIndex.dir/src/binarySearchTree.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/nagy/CLionProjects/bigd/simpleIndex/src/binarySearchTree.cpp > CMakeFiles/simpleIndex.dir/src/binarySearchTree.cpp.i

CMakeFiles/simpleIndex.dir/src/binarySearchTree.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/simpleIndex.dir/src/binarySearchTree.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/nagy/CLionProjects/bigd/simpleIndex/src/binarySearchTree.cpp -o CMakeFiles/simpleIndex.dir/src/binarySearchTree.cpp.s

CMakeFiles/simpleIndex.dir/src/syntheticData.cpp.o: CMakeFiles/simpleIndex.dir/flags.make
CMakeFiles/simpleIndex.dir/src/syntheticData.cpp.o: ../src/syntheticData.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/nagy/CLionProjects/bigd/simpleIndex/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/simpleIndex.dir/src/syntheticData.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/simpleIndex.dir/src/syntheticData.cpp.o -c /home/nagy/CLionProjects/bigd/simpleIndex/src/syntheticData.cpp

CMakeFiles/simpleIndex.dir/src/syntheticData.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/simpleIndex.dir/src/syntheticData.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/nagy/CLionProjects/bigd/simpleIndex/src/syntheticData.cpp > CMakeFiles/simpleIndex.dir/src/syntheticData.cpp.i

CMakeFiles/simpleIndex.dir/src/syntheticData.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/simpleIndex.dir/src/syntheticData.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/nagy/CLionProjects/bigd/simpleIndex/src/syntheticData.cpp -o CMakeFiles/simpleIndex.dir/src/syntheticData.cpp.s

# Object files for target simpleIndex
simpleIndex_OBJECTS = \
"CMakeFiles/simpleIndex.dir/src/main.C.o" \
"CMakeFiles/simpleIndex.dir/src/mysql.C.o" \
"CMakeFiles/simpleIndex.dir/src/onebar.C.o" \
"CMakeFiles/simpleIndex.dir/src/symbol.C.o" \
"CMakeFiles/simpleIndex.dir/src/iSax.cpp.o" \
"CMakeFiles/simpleIndex.dir/src/EnvelopGen.cpp.o" \
"CMakeFiles/simpleIndex.dir/src/breakpoints.cpp.o" \
"CMakeFiles/simpleIndex.dir/src/binarySearchTree.cpp.o" \
"CMakeFiles/simpleIndex.dir/src/syntheticData.cpp.o"

# External object files for target simpleIndex
simpleIndex_EXTERNAL_OBJECTS =

simpleIndex: CMakeFiles/simpleIndex.dir/src/main.C.o
simpleIndex: CMakeFiles/simpleIndex.dir/src/mysql.C.o
simpleIndex: CMakeFiles/simpleIndex.dir/src/onebar.C.o
simpleIndex: CMakeFiles/simpleIndex.dir/src/symbol.C.o
simpleIndex: CMakeFiles/simpleIndex.dir/src/iSax.cpp.o
simpleIndex: CMakeFiles/simpleIndex.dir/src/EnvelopGen.cpp.o
simpleIndex: CMakeFiles/simpleIndex.dir/src/breakpoints.cpp.o
simpleIndex: CMakeFiles/simpleIndex.dir/src/binarySearchTree.cpp.o
simpleIndex: CMakeFiles/simpleIndex.dir/src/syntheticData.cpp.o
simpleIndex: CMakeFiles/simpleIndex.dir/build.make
simpleIndex: CMakeFiles/simpleIndex.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/nagy/CLionProjects/bigd/simpleIndex/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Linking CXX executable simpleIndex"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/simpleIndex.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/simpleIndex.dir/build: simpleIndex

.PHONY : CMakeFiles/simpleIndex.dir/build

CMakeFiles/simpleIndex.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/simpleIndex.dir/cmake_clean.cmake
.PHONY : CMakeFiles/simpleIndex.dir/clean

CMakeFiles/simpleIndex.dir/depend:
	cd /home/nagy/CLionProjects/bigd/simpleIndex/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/nagy/CLionProjects/bigd/simpleIndex /home/nagy/CLionProjects/bigd/simpleIndex /home/nagy/CLionProjects/bigd/simpleIndex/cmake-build-debug /home/nagy/CLionProjects/bigd/simpleIndex/cmake-build-debug /home/nagy/CLionProjects/bigd/simpleIndex/cmake-build-debug/CMakeFiles/simpleIndex.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/simpleIndex.dir/depend
