# CMAKE generated file: DO NOT EDIT!
# Generated by "NMake Makefiles" Generator, CMake Version 3.19

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


.SUFFIXES: .hpux_make_needs_suffix_list


# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE
NULL=nul
!ENDIF
SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = C:\Users\mbaratella\AppData\Local\JetBrains\Toolbox\apps\CLion\ch-0\211.7142.21\bin\cmake\win\bin\cmake.exe

# The command to remove a file.
RM = C:\Users\mbaratella\AppData\Local\JetBrains\Toolbox\apps\CLion\ch-0\211.7142.21\bin\cmake\win\bin\cmake.exe -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Bara\Unive\PageRank

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Bara\Unive\PageRank\cmake-build-release

# Include any dependencies generated for this target.
include CMakeFiles\PageRank.dir\depend.make

# Include the progress variables for this target.
include CMakeFiles\PageRank.dir\progress.make

# Include the compile flags for this target's objects.
include CMakeFiles\PageRank.dir\flags.make

CMakeFiles\PageRank.dir\main.cpp.obj: CMakeFiles\PageRank.dir\flags.make
CMakeFiles\PageRank.dir\main.cpp.obj: ..\main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Bara\Unive\PageRank\cmake-build-release\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/PageRank.dir/main.cpp.obj"
	C:\PROGRA~2\MICROS~4\2019\COMMUN~1\VC\Tools\MSVC\1426~1.288\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoCMakeFiles\PageRank.dir\main.cpp.obj /FdCMakeFiles\PageRank.dir\ /FS -c C:\Bara\Unive\PageRank\main.cpp
<<

CMakeFiles\PageRank.dir\main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/PageRank.dir/main.cpp.i"
	C:\PROGRA~2\MICROS~4\2019\COMMUN~1\VC\Tools\MSVC\1426~1.288\bin\Hostx86\x86\cl.exe > CMakeFiles\PageRank.dir\main.cpp.i @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Bara\Unive\PageRank\main.cpp
<<

CMakeFiles\PageRank.dir\main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/PageRank.dir/main.cpp.s"
	C:\PROGRA~2\MICROS~4\2019\COMMUN~1\VC\Tools\MSVC\1426~1.288\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoNUL /FAs /FaCMakeFiles\PageRank.dir\main.cpp.s /c C:\Bara\Unive\PageRank\main.cpp
<<

# Object files for target PageRank
PageRank_OBJECTS = \
"CMakeFiles\PageRank.dir\main.cpp.obj"

# External object files for target PageRank
PageRank_EXTERNAL_OBJECTS =

PageRank.exe: CMakeFiles\PageRank.dir\main.cpp.obj
PageRank.exe: CMakeFiles\PageRank.dir\build.make
PageRank.exe: CMakeFiles\PageRank.dir\objects1.rsp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Bara\Unive\PageRank\cmake-build-release\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable PageRank.exe"
	C:\Users\mbaratella\AppData\Local\JetBrains\Toolbox\apps\CLion\ch-0\211.7142.21\bin\cmake\win\bin\cmake.exe -E vs_link_exe --intdir=CMakeFiles\PageRank.dir --rc=C:\PROGRA~2\WI3CF2~1\10\bin\100183~1.0\x86\rc.exe --mt=C:\PROGRA~2\WI3CF2~1\10\bin\100183~1.0\x86\mt.exe --manifests -- C:\PROGRA~2\MICROS~4\2019\COMMUN~1\VC\Tools\MSVC\1426~1.288\bin\Hostx86\x86\link.exe /nologo @CMakeFiles\PageRank.dir\objects1.rsp @<<
 /out:PageRank.exe /implib:PageRank.lib /pdb:C:\Bara\Unive\PageRank\cmake-build-release\PageRank.pdb /version:0.0 /machine:X86 /INCREMENTAL:NO /subsystem:console  kernel32.lib user32.lib gdi32.lib winspool.lib shell32.lib ole32.lib oleaut32.lib uuid.lib comdlg32.lib advapi32.lib 
<<

# Rule to build all files generated by this target.
CMakeFiles\PageRank.dir\build: PageRank.exe

.PHONY : CMakeFiles\PageRank.dir\build

CMakeFiles\PageRank.dir\clean:
	$(CMAKE_COMMAND) -P CMakeFiles\PageRank.dir\cmake_clean.cmake
.PHONY : CMakeFiles\PageRank.dir\clean

CMakeFiles\PageRank.dir\depend:
	$(CMAKE_COMMAND) -E cmake_depends "NMake Makefiles" C:\Bara\Unive\PageRank C:\Bara\Unive\PageRank C:\Bara\Unive\PageRank\cmake-build-release C:\Bara\Unive\PageRank\cmake-build-release C:\Bara\Unive\PageRank\cmake-build-release\CMakeFiles\PageRank.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles\PageRank.dir\depend
