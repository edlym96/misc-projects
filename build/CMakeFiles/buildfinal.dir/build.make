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
CMAKE_SOURCE_DIR = /homes/eyl215/MailPunk

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /homes/eyl215/MailPunk/build

# Utility rule file for buildfinal.

# Include the progress variables for this target.
include CMakeFiles/buildfinal.dir/progress.make

CMakeFiles/buildfinal: CMakeFiles/buildfinal-complete


CMakeFiles/buildfinal-complete: buildfinal-prefix/src/buildfinal-stamp/buildfinal-install
CMakeFiles/buildfinal-complete: buildfinal-prefix/src/buildfinal-stamp/buildfinal-mkdir
CMakeFiles/buildfinal-complete: buildfinal-prefix/src/buildfinal-stamp/buildfinal-download
CMakeFiles/buildfinal-complete: buildfinal-prefix/src/buildfinal-stamp/buildfinal-update
CMakeFiles/buildfinal-complete: buildfinal-prefix/src/buildfinal-stamp/buildfinal-patch
CMakeFiles/buildfinal-complete: buildfinal-prefix/src/buildfinal-stamp/buildfinal-configure
CMakeFiles/buildfinal-complete: buildfinal-prefix/src/buildfinal-stamp/buildfinal-build
CMakeFiles/buildfinal-complete: buildfinal-prefix/src/buildfinal-stamp/buildfinal-install
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/homes/eyl215/MailPunk/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Completed 'buildfinal'"
	/usr/bin/cmake -E make_directory /homes/eyl215/MailPunk/build/CMakeFiles
	/usr/bin/cmake -E touch /homes/eyl215/MailPunk/build/CMakeFiles/buildfinal-complete
	/usr/bin/cmake -E touch /homes/eyl215/MailPunk/build/buildfinal-prefix/src/buildfinal-stamp/buildfinal-done

buildfinal-prefix/src/buildfinal-stamp/buildfinal-install: buildfinal-prefix/src/buildfinal-stamp/buildfinal-build
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/homes/eyl215/MailPunk/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Performing install step for 'buildfinal'"
	cd /homes/eyl215/MailPunk/build/buildfinal-prefix/src/buildfinal && $(MAKE) install
	cd /homes/eyl215/MailPunk/build/buildfinal-prefix/src/buildfinal && /usr/bin/cmake -E touch /homes/eyl215/MailPunk/build/buildfinal-prefix/src/buildfinal-stamp/buildfinal-install

buildfinal-prefix/src/buildfinal-stamp/buildfinal-mkdir:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/homes/eyl215/MailPunk/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Creating directories for 'buildfinal'"
	/usr/bin/cmake -E make_directory /homes/eyl215/MailPunk/build/buildfinal-prefix/src/buildfinal
	/usr/bin/cmake -E make_directory /homes/eyl215/MailPunk/build/buildfinal-prefix/src/buildfinal
	/usr/bin/cmake -E make_directory /homes/eyl215/MailPunk/build/buildfinal-prefix
	/usr/bin/cmake -E make_directory /homes/eyl215/MailPunk/build/buildfinal-prefix/tmp
	/usr/bin/cmake -E make_directory /homes/eyl215/MailPunk/build/buildfinal-prefix/src/buildfinal-stamp
	/usr/bin/cmake -E make_directory /homes/eyl215/MailPunk/build/buildfinal-prefix/src
	/usr/bin/cmake -E touch /homes/eyl215/MailPunk/build/buildfinal-prefix/src/buildfinal-stamp/buildfinal-mkdir

buildfinal-prefix/src/buildfinal-stamp/buildfinal-download: buildfinal-prefix/src/buildfinal-stamp/buildfinal-urlinfo.txt
buildfinal-prefix/src/buildfinal-stamp/buildfinal-download: buildfinal-prefix/src/buildfinal-stamp/buildfinal-mkdir
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/homes/eyl215/MailPunk/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Performing download step (download, verify and extract) for 'buildfinal'"
	cd /homes/eyl215/MailPunk/build/buildfinal-prefix/src && /usr/bin/cmake -P /homes/eyl215/MailPunk/build/buildfinal-prefix/src/buildfinal-stamp/download-buildfinal.cmake
	cd /homes/eyl215/MailPunk/build/buildfinal-prefix/src && /usr/bin/cmake -P /homes/eyl215/MailPunk/build/buildfinal-prefix/src/buildfinal-stamp/verify-buildfinal.cmake
	cd /homes/eyl215/MailPunk/build/buildfinal-prefix/src && /usr/bin/cmake -P /homes/eyl215/MailPunk/build/buildfinal-prefix/src/buildfinal-stamp/extract-buildfinal.cmake
	cd /homes/eyl215/MailPunk/build/buildfinal-prefix/src && /usr/bin/cmake -E touch /homes/eyl215/MailPunk/build/buildfinal-prefix/src/buildfinal-stamp/buildfinal-download

buildfinal-prefix/src/buildfinal-stamp/buildfinal-update: buildfinal-prefix/src/buildfinal-stamp/buildfinal-download
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/homes/eyl215/MailPunk/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "No update step for 'buildfinal'"
	/usr/bin/cmake -E echo_append
	/usr/bin/cmake -E touch /homes/eyl215/MailPunk/build/buildfinal-prefix/src/buildfinal-stamp/buildfinal-update

buildfinal-prefix/src/buildfinal-stamp/buildfinal-patch: buildfinal-prefix/src/buildfinal-stamp/buildfinal-download
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/homes/eyl215/MailPunk/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Performing patch step for 'buildfinal'"
	cd /homes/eyl215/MailPunk/build/buildfinal-prefix/src/buildfinal && ./autogen.sh
	cd /homes/eyl215/MailPunk/build/buildfinal-prefix/src/buildfinal && /usr/bin/cmake -E touch /homes/eyl215/MailPunk/build/buildfinal-prefix/src/buildfinal-stamp/buildfinal-patch

buildfinal-prefix/src/buildfinal-stamp/buildfinal-configure: buildfinal-prefix/tmp/buildfinal-cfgcmd.txt
buildfinal-prefix/src/buildfinal-stamp/buildfinal-configure: buildfinal-prefix/src/buildfinal-stamp/buildfinal-update
buildfinal-prefix/src/buildfinal-stamp/buildfinal-configure: buildfinal-prefix/src/buildfinal-stamp/buildfinal-patch
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/homes/eyl215/MailPunk/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Performing configure step for 'buildfinal'"
	cd /homes/eyl215/MailPunk/build/buildfinal-prefix/src/buildfinal && ./configure --prefix /homes/eyl215/MailPunk/build/deps
	cd /homes/eyl215/MailPunk/build/buildfinal-prefix/src/buildfinal && /usr/bin/cmake -E touch /homes/eyl215/MailPunk/build/buildfinal-prefix/src/buildfinal-stamp/buildfinal-configure

buildfinal-prefix/src/buildfinal-stamp/buildfinal-build: buildfinal-prefix/src/buildfinal-stamp/buildfinal-configure
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/homes/eyl215/MailPunk/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Performing build step for 'buildfinal'"
	cd /homes/eyl215/MailPunk/build/buildfinal-prefix/src/buildfinal && make
	cd /homes/eyl215/MailPunk/build/buildfinal-prefix/src/buildfinal && /usr/bin/cmake -E touch /homes/eyl215/MailPunk/build/buildfinal-prefix/src/buildfinal-stamp/buildfinal-build

buildfinal: CMakeFiles/buildfinal
buildfinal: CMakeFiles/buildfinal-complete
buildfinal: buildfinal-prefix/src/buildfinal-stamp/buildfinal-install
buildfinal: buildfinal-prefix/src/buildfinal-stamp/buildfinal-mkdir
buildfinal: buildfinal-prefix/src/buildfinal-stamp/buildfinal-download
buildfinal: buildfinal-prefix/src/buildfinal-stamp/buildfinal-update
buildfinal: buildfinal-prefix/src/buildfinal-stamp/buildfinal-patch
buildfinal: buildfinal-prefix/src/buildfinal-stamp/buildfinal-configure
buildfinal: buildfinal-prefix/src/buildfinal-stamp/buildfinal-build
buildfinal: CMakeFiles/buildfinal.dir/build.make

.PHONY : buildfinal

# Rule to build all files generated by this target.
CMakeFiles/buildfinal.dir/build: buildfinal

.PHONY : CMakeFiles/buildfinal.dir/build

CMakeFiles/buildfinal.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/buildfinal.dir/cmake_clean.cmake
.PHONY : CMakeFiles/buildfinal.dir/clean

CMakeFiles/buildfinal.dir/depend:
	cd /homes/eyl215/MailPunk/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /homes/eyl215/MailPunk /homes/eyl215/MailPunk /homes/eyl215/MailPunk/build /homes/eyl215/MailPunk/build /homes/eyl215/MailPunk/build/CMakeFiles/buildfinal.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/buildfinal.dir/depend

