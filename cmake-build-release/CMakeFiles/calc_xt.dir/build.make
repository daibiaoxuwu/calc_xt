# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.15

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "D:\prog\JetBrains\CLion 2019.2\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "D:\prog\JetBrains\CLion 2019.2\bin\cmake\win\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = D:\prog10\Desktop\mahjong_old\calc_xt

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = D:\prog10\Desktop\mahjong_old\calc_xt\cmake-build-release

# Include any dependencies generated for this target.
include CMakeFiles/calc_xt.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/calc_xt.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/calc_xt.dir/flags.make

CMakeFiles/calc_xt.dir/main.cpp.obj: CMakeFiles/calc_xt.dir/flags.make
CMakeFiles/calc_xt.dir/main.cpp.obj: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\prog10\Desktop\mahjong_old\calc_xt\cmake-build-release\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/calc_xt.dir/main.cpp.obj"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\G__~1.EXE  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\calc_xt.dir\main.cpp.obj -c D:\prog10\Desktop\mahjong_old\calc_xt\main.cpp

CMakeFiles/calc_xt.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/calc_xt.dir/main.cpp.i"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\prog10\Desktop\mahjong_old\calc_xt\main.cpp > CMakeFiles\calc_xt.dir\main.cpp.i

CMakeFiles/calc_xt.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/calc_xt.dir/main.cpp.s"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\prog10\Desktop\mahjong_old\calc_xt\main.cpp -o CMakeFiles\calc_xt.dir\main.cpp.s

# Object files for target calc_xt
calc_xt_OBJECTS = \
"CMakeFiles/calc_xt.dir/main.cpp.obj"

# External object files for target calc_xt
calc_xt_EXTERNAL_OBJECTS =

calc_xt.exe: CMakeFiles/calc_xt.dir/main.cpp.obj
calc_xt.exe: CMakeFiles/calc_xt.dir/build.make
calc_xt.exe: CMakeFiles/calc_xt.dir/linklibs.rsp
calc_xt.exe: CMakeFiles/calc_xt.dir/objects1.rsp
calc_xt.exe: CMakeFiles/calc_xt.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=D:\prog10\Desktop\mahjong_old\calc_xt\cmake-build-release\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable calc_xt.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\calc_xt.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/calc_xt.dir/build: calc_xt.exe

.PHONY : CMakeFiles/calc_xt.dir/build

CMakeFiles/calc_xt.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\calc_xt.dir\cmake_clean.cmake
.PHONY : CMakeFiles/calc_xt.dir/clean

CMakeFiles/calc_xt.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" D:\prog10\Desktop\mahjong_old\calc_xt D:\prog10\Desktop\mahjong_old\calc_xt D:\prog10\Desktop\mahjong_old\calc_xt\cmake-build-release D:\prog10\Desktop\mahjong_old\calc_xt\cmake-build-release D:\prog10\Desktop\mahjong_old\calc_xt\cmake-build-release\CMakeFiles\calc_xt.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/calc_xt.dir/depend

