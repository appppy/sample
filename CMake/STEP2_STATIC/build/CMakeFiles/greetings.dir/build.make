# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


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
CMAKE_SOURCE_DIR = /home/adachi/share/home/appy/documents/Sample/CMake/STEP2_STATIC

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/adachi/share/home/appy/documents/Sample/CMake/STEP2_STATIC/build

# Include any dependencies generated for this target.
include CMakeFiles/greetings.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/greetings.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/greetings.dir/flags.make

CMakeFiles/greetings.dir/hello.cpp.o: CMakeFiles/greetings.dir/flags.make
CMakeFiles/greetings.dir/hello.cpp.o: ../hello.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/adachi/share/home/appy/documents/Sample/CMake/STEP2_STATIC/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/greetings.dir/hello.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/greetings.dir/hello.cpp.o -c /home/adachi/share/home/appy/documents/Sample/CMake/STEP2_STATIC/hello.cpp

CMakeFiles/greetings.dir/hello.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/greetings.dir/hello.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/adachi/share/home/appy/documents/Sample/CMake/STEP2_STATIC/hello.cpp > CMakeFiles/greetings.dir/hello.cpp.i

CMakeFiles/greetings.dir/hello.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/greetings.dir/hello.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/adachi/share/home/appy/documents/Sample/CMake/STEP2_STATIC/hello.cpp -o CMakeFiles/greetings.dir/hello.cpp.s

CMakeFiles/greetings.dir/hello.cpp.o.requires:

.PHONY : CMakeFiles/greetings.dir/hello.cpp.o.requires

CMakeFiles/greetings.dir/hello.cpp.o.provides: CMakeFiles/greetings.dir/hello.cpp.o.requires
	$(MAKE) -f CMakeFiles/greetings.dir/build.make CMakeFiles/greetings.dir/hello.cpp.o.provides.build
.PHONY : CMakeFiles/greetings.dir/hello.cpp.o.provides

CMakeFiles/greetings.dir/hello.cpp.o.provides.build: CMakeFiles/greetings.dir/hello.cpp.o


CMakeFiles/greetings.dir/good_morning.cpp.o: CMakeFiles/greetings.dir/flags.make
CMakeFiles/greetings.dir/good_morning.cpp.o: ../good_morning.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/adachi/share/home/appy/documents/Sample/CMake/STEP2_STATIC/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/greetings.dir/good_morning.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/greetings.dir/good_morning.cpp.o -c /home/adachi/share/home/appy/documents/Sample/CMake/STEP2_STATIC/good_morning.cpp

CMakeFiles/greetings.dir/good_morning.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/greetings.dir/good_morning.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/adachi/share/home/appy/documents/Sample/CMake/STEP2_STATIC/good_morning.cpp > CMakeFiles/greetings.dir/good_morning.cpp.i

CMakeFiles/greetings.dir/good_morning.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/greetings.dir/good_morning.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/adachi/share/home/appy/documents/Sample/CMake/STEP2_STATIC/good_morning.cpp -o CMakeFiles/greetings.dir/good_morning.cpp.s

CMakeFiles/greetings.dir/good_morning.cpp.o.requires:

.PHONY : CMakeFiles/greetings.dir/good_morning.cpp.o.requires

CMakeFiles/greetings.dir/good_morning.cpp.o.provides: CMakeFiles/greetings.dir/good_morning.cpp.o.requires
	$(MAKE) -f CMakeFiles/greetings.dir/build.make CMakeFiles/greetings.dir/good_morning.cpp.o.provides.build
.PHONY : CMakeFiles/greetings.dir/good_morning.cpp.o.provides

CMakeFiles/greetings.dir/good_morning.cpp.o.provides.build: CMakeFiles/greetings.dir/good_morning.cpp.o


# Object files for target greetings
greetings_OBJECTS = \
"CMakeFiles/greetings.dir/hello.cpp.o" \
"CMakeFiles/greetings.dir/good_morning.cpp.o"

# External object files for target greetings
greetings_EXTERNAL_OBJECTS =

libgreetings.a: CMakeFiles/greetings.dir/hello.cpp.o
libgreetings.a: CMakeFiles/greetings.dir/good_morning.cpp.o
libgreetings.a: CMakeFiles/greetings.dir/build.make
libgreetings.a: CMakeFiles/greetings.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/adachi/share/home/appy/documents/Sample/CMake/STEP2_STATIC/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX static library libgreetings.a"
	$(CMAKE_COMMAND) -P CMakeFiles/greetings.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/greetings.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/greetings.dir/build: libgreetings.a

.PHONY : CMakeFiles/greetings.dir/build

CMakeFiles/greetings.dir/requires: CMakeFiles/greetings.dir/hello.cpp.o.requires
CMakeFiles/greetings.dir/requires: CMakeFiles/greetings.dir/good_morning.cpp.o.requires

.PHONY : CMakeFiles/greetings.dir/requires

CMakeFiles/greetings.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/greetings.dir/cmake_clean.cmake
.PHONY : CMakeFiles/greetings.dir/clean

CMakeFiles/greetings.dir/depend:
	cd /home/adachi/share/home/appy/documents/Sample/CMake/STEP2_STATIC/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/adachi/share/home/appy/documents/Sample/CMake/STEP2_STATIC /home/adachi/share/home/appy/documents/Sample/CMake/STEP2_STATIC /home/adachi/share/home/appy/documents/Sample/CMake/STEP2_STATIC/build /home/adachi/share/home/appy/documents/Sample/CMake/STEP2_STATIC/build /home/adachi/share/home/appy/documents/Sample/CMake/STEP2_STATIC/build/CMakeFiles/greetings.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/greetings.dir/depend

