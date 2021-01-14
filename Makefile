# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

# Default target executed when no arguments are given to make.
default_target: all

.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:


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
CMAKE_SOURCE_DIR = /mnt/d/uni/rpg/di.rpg

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mnt/d/uni/rpg/di.rpg

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/usr/bin/cmake -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache

.PHONY : rebuild_cache/fast

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "No interactive CMake dialog available..."
	/usr/bin/cmake -E echo No\ interactive\ CMake\ dialog\ available.
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache

.PHONY : edit_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /mnt/d/uni/rpg/di.rpg/CMakeFiles /mnt/d/uni/rpg/di.rpg/CMakeFiles/progress.marks
	$(MAKE) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /mnt/d/uni/rpg/di.rpg/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean

.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named DI_RPG

# Build rule for target.
DI_RPG: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 DI_RPG
.PHONY : DI_RPG

# fast build rule for target.
DI_RPG/fast:
	$(MAKE) -f CMakeFiles/DI_RPG.dir/build.make CMakeFiles/DI_RPG.dir/build
.PHONY : DI_RPG/fast

# target to build an object file
area.o:
	$(MAKE) -f CMakeFiles/DI_RPG.dir/build.make CMakeFiles/DI_RPG.dir/area.o
.PHONY : area.o

# target to preprocess a source file
area.i:
	$(MAKE) -f CMakeFiles/DI_RPG.dir/build.make CMakeFiles/DI_RPG.dir/area.i
.PHONY : area.i

# target to generate assembly for a file
area.s:
	$(MAKE) -f CMakeFiles/DI_RPG.dir/build.make CMakeFiles/DI_RPG.dir/area.s
.PHONY : area.s

# target to build an object file
dragon.o:
	$(MAKE) -f CMakeFiles/DI_RPG.dir/build.make CMakeFiles/DI_RPG.dir/dragon.o
.PHONY : dragon.o

# target to preprocess a source file
dragon.i:
	$(MAKE) -f CMakeFiles/DI_RPG.dir/build.make CMakeFiles/DI_RPG.dir/dragon.i
.PHONY : dragon.i

# target to generate assembly for a file
dragon.s:
	$(MAKE) -f CMakeFiles/DI_RPG.dir/build.make CMakeFiles/DI_RPG.dir/dragon.s
.PHONY : dragon.s

# target to build an object file
exoskeleton.o:
	$(MAKE) -f CMakeFiles/DI_RPG.dir/build.make CMakeFiles/DI_RPG.dir/exoskeleton.o
.PHONY : exoskeleton.o

# target to preprocess a source file
exoskeleton.i:
	$(MAKE) -f CMakeFiles/DI_RPG.dir/build.make CMakeFiles/DI_RPG.dir/exoskeleton.i
.PHONY : exoskeleton.i

# target to generate assembly for a file
exoskeleton.s:
	$(MAKE) -f CMakeFiles/DI_RPG.dir/build.make CMakeFiles/DI_RPG.dir/exoskeleton.s
.PHONY : exoskeleton.s

# target to build an object file
game.o:
	$(MAKE) -f CMakeFiles/DI_RPG.dir/build.make CMakeFiles/DI_RPG.dir/game.o
.PHONY : game.o

# target to preprocess a source file
game.i:
	$(MAKE) -f CMakeFiles/DI_RPG.dir/build.make CMakeFiles/DI_RPG.dir/game.i
.PHONY : game.i

# target to generate assembly for a file
game.s:
	$(MAKE) -f CMakeFiles/DI_RPG.dir/build.make CMakeFiles/DI_RPG.dir/game.s
.PHONY : game.s

# target to build an object file
grid.o:
	$(MAKE) -f CMakeFiles/DI_RPG.dir/build.make CMakeFiles/DI_RPG.dir/grid.o
.PHONY : grid.o

# target to preprocess a source file
grid.i:
	$(MAKE) -f CMakeFiles/DI_RPG.dir/build.make CMakeFiles/DI_RPG.dir/grid.i
.PHONY : grid.i

# target to generate assembly for a file
grid.s:
	$(MAKE) -f CMakeFiles/DI_RPG.dir/build.make CMakeFiles/DI_RPG.dir/grid.s
.PHONY : grid.s

# target to build an object file
hero.o:
	$(MAKE) -f CMakeFiles/DI_RPG.dir/build.make CMakeFiles/DI_RPG.dir/hero.o
.PHONY : hero.o

# target to preprocess a source file
hero.i:
	$(MAKE) -f CMakeFiles/DI_RPG.dir/build.make CMakeFiles/DI_RPG.dir/hero.i
.PHONY : hero.i

# target to generate assembly for a file
hero.s:
	$(MAKE) -f CMakeFiles/DI_RPG.dir/build.make CMakeFiles/DI_RPG.dir/hero.s
.PHONY : hero.s

# target to build an object file
item.o:
	$(MAKE) -f CMakeFiles/DI_RPG.dir/build.make CMakeFiles/DI_RPG.dir/item.o
.PHONY : item.o

# target to preprocess a source file
item.i:
	$(MAKE) -f CMakeFiles/DI_RPG.dir/build.make CMakeFiles/DI_RPG.dir/item.i
.PHONY : item.i

# target to generate assembly for a file
item.s:
	$(MAKE) -f CMakeFiles/DI_RPG.dir/build.make CMakeFiles/DI_RPG.dir/item.s
.PHONY : item.s

# target to build an object file
living.o:
	$(MAKE) -f CMakeFiles/DI_RPG.dir/build.make CMakeFiles/DI_RPG.dir/living.o
.PHONY : living.o

# target to preprocess a source file
living.i:
	$(MAKE) -f CMakeFiles/DI_RPG.dir/build.make CMakeFiles/DI_RPG.dir/living.i
.PHONY : living.i

# target to generate assembly for a file
living.s:
	$(MAKE) -f CMakeFiles/DI_RPG.dir/build.make CMakeFiles/DI_RPG.dir/living.s
.PHONY : living.s

# target to build an object file
main.o:
	$(MAKE) -f CMakeFiles/DI_RPG.dir/build.make CMakeFiles/DI_RPG.dir/main.o
.PHONY : main.o

# target to preprocess a source file
main.i:
	$(MAKE) -f CMakeFiles/DI_RPG.dir/build.make CMakeFiles/DI_RPG.dir/main.i
.PHONY : main.i

# target to generate assembly for a file
main.s:
	$(MAKE) -f CMakeFiles/DI_RPG.dir/build.make CMakeFiles/DI_RPG.dir/main.s
.PHONY : main.s

# target to build an object file
monster.o:
	$(MAKE) -f CMakeFiles/DI_RPG.dir/build.make CMakeFiles/DI_RPG.dir/monster.o
.PHONY : monster.o

# target to preprocess a source file
monster.i:
	$(MAKE) -f CMakeFiles/DI_RPG.dir/build.make CMakeFiles/DI_RPG.dir/monster.i
.PHONY : monster.i

# target to generate assembly for a file
monster.s:
	$(MAKE) -f CMakeFiles/DI_RPG.dir/build.make CMakeFiles/DI_RPG.dir/monster.s
.PHONY : monster.s

# target to build an object file
paladin.o:
	$(MAKE) -f CMakeFiles/DI_RPG.dir/build.make CMakeFiles/DI_RPG.dir/paladin.o
.PHONY : paladin.o

# target to preprocess a source file
paladin.i:
	$(MAKE) -f CMakeFiles/DI_RPG.dir/build.make CMakeFiles/DI_RPG.dir/paladin.i
.PHONY : paladin.i

# target to generate assembly for a file
paladin.s:
	$(MAKE) -f CMakeFiles/DI_RPG.dir/build.make CMakeFiles/DI_RPG.dir/paladin.s
.PHONY : paladin.s

# target to build an object file
sorcerer.o:
	$(MAKE) -f CMakeFiles/DI_RPG.dir/build.make CMakeFiles/DI_RPG.dir/sorcerer.o
.PHONY : sorcerer.o

# target to preprocess a source file
sorcerer.i:
	$(MAKE) -f CMakeFiles/DI_RPG.dir/build.make CMakeFiles/DI_RPG.dir/sorcerer.i
.PHONY : sorcerer.i

# target to generate assembly for a file
sorcerer.s:
	$(MAKE) -f CMakeFiles/DI_RPG.dir/build.make CMakeFiles/DI_RPG.dir/sorcerer.s
.PHONY : sorcerer.s

# target to build an object file
spirit.o:
	$(MAKE) -f CMakeFiles/DI_RPG.dir/build.make CMakeFiles/DI_RPG.dir/spirit.o
.PHONY : spirit.o

# target to preprocess a source file
spirit.i:
	$(MAKE) -f CMakeFiles/DI_RPG.dir/build.make CMakeFiles/DI_RPG.dir/spirit.i
.PHONY : spirit.i

# target to generate assembly for a file
spirit.s:
	$(MAKE) -f CMakeFiles/DI_RPG.dir/build.make CMakeFiles/DI_RPG.dir/spirit.s
.PHONY : spirit.s

# target to build an object file
warrior.o:
	$(MAKE) -f CMakeFiles/DI_RPG.dir/build.make CMakeFiles/DI_RPG.dir/warrior.o
.PHONY : warrior.o

# target to preprocess a source file
warrior.i:
	$(MAKE) -f CMakeFiles/DI_RPG.dir/build.make CMakeFiles/DI_RPG.dir/warrior.i
.PHONY : warrior.i

# target to generate assembly for a file
warrior.s:
	$(MAKE) -f CMakeFiles/DI_RPG.dir/build.make CMakeFiles/DI_RPG.dir/warrior.s
.PHONY : warrior.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... rebuild_cache"
	@echo "... edit_cache"
	@echo "... DI_RPG"
	@echo "... area.o"
	@echo "... area.i"
	@echo "... area.s"
	@echo "... dragon.o"
	@echo "... dragon.i"
	@echo "... dragon.s"
	@echo "... exoskeleton.o"
	@echo "... exoskeleton.i"
	@echo "... exoskeleton.s"
	@echo "... game.o"
	@echo "... game.i"
	@echo "... game.s"
	@echo "... grid.o"
	@echo "... grid.i"
	@echo "... grid.s"
	@echo "... hero.o"
	@echo "... hero.i"
	@echo "... hero.s"
	@echo "... item.o"
	@echo "... item.i"
	@echo "... item.s"
	@echo "... living.o"
	@echo "... living.i"
	@echo "... living.s"
	@echo "... main.o"
	@echo "... main.i"
	@echo "... main.s"
	@echo "... monster.o"
	@echo "... monster.i"
	@echo "... monster.s"
	@echo "... paladin.o"
	@echo "... paladin.i"
	@echo "... paladin.s"
	@echo "... sorcerer.o"
	@echo "... sorcerer.i"
	@echo "... sorcerer.s"
	@echo "... spirit.o"
	@echo "... spirit.i"
	@echo "... spirit.s"
	@echo "... warrior.o"
	@echo "... warrior.i"
	@echo "... warrior.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

