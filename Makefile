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

area.o: area.cpp.o

.PHONY : area.o

# target to build an object file
area.cpp.o:
	$(MAKE) -f CMakeFiles/DI_RPG.dir/build.make CMakeFiles/DI_RPG.dir/area.cpp.o
.PHONY : area.cpp.o

area.i: area.cpp.i

.PHONY : area.i

# target to preprocess a source file
area.cpp.i:
	$(MAKE) -f CMakeFiles/DI_RPG.dir/build.make CMakeFiles/DI_RPG.dir/area.cpp.i
.PHONY : area.cpp.i

area.s: area.cpp.s

.PHONY : area.s

# target to generate assembly for a file
area.cpp.s:
	$(MAKE) -f CMakeFiles/DI_RPG.dir/build.make CMakeFiles/DI_RPG.dir/area.cpp.s
.PHONY : area.cpp.s

dragon.o: dragon.cpp.o

.PHONY : dragon.o

# target to build an object file
dragon.cpp.o:
	$(MAKE) -f CMakeFiles/DI_RPG.dir/build.make CMakeFiles/DI_RPG.dir/dragon.cpp.o
.PHONY : dragon.cpp.o

dragon.i: dragon.cpp.i

.PHONY : dragon.i

# target to preprocess a source file
dragon.cpp.i:
	$(MAKE) -f CMakeFiles/DI_RPG.dir/build.make CMakeFiles/DI_RPG.dir/dragon.cpp.i
.PHONY : dragon.cpp.i

dragon.s: dragon.cpp.s

.PHONY : dragon.s

# target to generate assembly for a file
dragon.cpp.s:
	$(MAKE) -f CMakeFiles/DI_RPG.dir/build.make CMakeFiles/DI_RPG.dir/dragon.cpp.s
.PHONY : dragon.cpp.s

exoskeleton.o: exoskeleton.cpp.o

.PHONY : exoskeleton.o

# target to build an object file
exoskeleton.cpp.o:
	$(MAKE) -f CMakeFiles/DI_RPG.dir/build.make CMakeFiles/DI_RPG.dir/exoskeleton.cpp.o
.PHONY : exoskeleton.cpp.o

exoskeleton.i: exoskeleton.cpp.i

.PHONY : exoskeleton.i

# target to preprocess a source file
exoskeleton.cpp.i:
	$(MAKE) -f CMakeFiles/DI_RPG.dir/build.make CMakeFiles/DI_RPG.dir/exoskeleton.cpp.i
.PHONY : exoskeleton.cpp.i

exoskeleton.s: exoskeleton.cpp.s

.PHONY : exoskeleton.s

# target to generate assembly for a file
exoskeleton.cpp.s:
	$(MAKE) -f CMakeFiles/DI_RPG.dir/build.make CMakeFiles/DI_RPG.dir/exoskeleton.cpp.s
.PHONY : exoskeleton.cpp.s

game.o: game.cpp.o

.PHONY : game.o

# target to build an object file
game.cpp.o:
	$(MAKE) -f CMakeFiles/DI_RPG.dir/build.make CMakeFiles/DI_RPG.dir/game.cpp.o
.PHONY : game.cpp.o

game.i: game.cpp.i

.PHONY : game.i

# target to preprocess a source file
game.cpp.i:
	$(MAKE) -f CMakeFiles/DI_RPG.dir/build.make CMakeFiles/DI_RPG.dir/game.cpp.i
.PHONY : game.cpp.i

game.s: game.cpp.s

.PHONY : game.s

# target to generate assembly for a file
game.cpp.s:
	$(MAKE) -f CMakeFiles/DI_RPG.dir/build.make CMakeFiles/DI_RPG.dir/game.cpp.s
.PHONY : game.cpp.s

grid.o: grid.cpp.o

.PHONY : grid.o

# target to build an object file
grid.cpp.o:
	$(MAKE) -f CMakeFiles/DI_RPG.dir/build.make CMakeFiles/DI_RPG.dir/grid.cpp.o
.PHONY : grid.cpp.o

grid.i: grid.cpp.i

.PHONY : grid.i

# target to preprocess a source file
grid.cpp.i:
	$(MAKE) -f CMakeFiles/DI_RPG.dir/build.make CMakeFiles/DI_RPG.dir/grid.cpp.i
.PHONY : grid.cpp.i

grid.s: grid.cpp.s

.PHONY : grid.s

# target to generate assembly for a file
grid.cpp.s:
	$(MAKE) -f CMakeFiles/DI_RPG.dir/build.make CMakeFiles/DI_RPG.dir/grid.cpp.s
.PHONY : grid.cpp.s

hero.o: hero.cpp.o

.PHONY : hero.o

# target to build an object file
hero.cpp.o:
	$(MAKE) -f CMakeFiles/DI_RPG.dir/build.make CMakeFiles/DI_RPG.dir/hero.cpp.o
.PHONY : hero.cpp.o

hero.i: hero.cpp.i

.PHONY : hero.i

# target to preprocess a source file
hero.cpp.i:
	$(MAKE) -f CMakeFiles/DI_RPG.dir/build.make CMakeFiles/DI_RPG.dir/hero.cpp.i
.PHONY : hero.cpp.i

hero.s: hero.cpp.s

.PHONY : hero.s

# target to generate assembly for a file
hero.cpp.s:
	$(MAKE) -f CMakeFiles/DI_RPG.dir/build.make CMakeFiles/DI_RPG.dir/hero.cpp.s
.PHONY : hero.cpp.s

item.o: item.cpp.o

.PHONY : item.o

# target to build an object file
item.cpp.o:
	$(MAKE) -f CMakeFiles/DI_RPG.dir/build.make CMakeFiles/DI_RPG.dir/item.cpp.o
.PHONY : item.cpp.o

item.i: item.cpp.i

.PHONY : item.i

# target to preprocess a source file
item.cpp.i:
	$(MAKE) -f CMakeFiles/DI_RPG.dir/build.make CMakeFiles/DI_RPG.dir/item.cpp.i
.PHONY : item.cpp.i

item.s: item.cpp.s

.PHONY : item.s

# target to generate assembly for a file
item.cpp.s:
	$(MAKE) -f CMakeFiles/DI_RPG.dir/build.make CMakeFiles/DI_RPG.dir/item.cpp.s
.PHONY : item.cpp.s

living.o: living.cpp.o

.PHONY : living.o

# target to build an object file
living.cpp.o:
	$(MAKE) -f CMakeFiles/DI_RPG.dir/build.make CMakeFiles/DI_RPG.dir/living.cpp.o
.PHONY : living.cpp.o

living.i: living.cpp.i

.PHONY : living.i

# target to preprocess a source file
living.cpp.i:
	$(MAKE) -f CMakeFiles/DI_RPG.dir/build.make CMakeFiles/DI_RPG.dir/living.cpp.i
.PHONY : living.cpp.i

living.s: living.cpp.s

.PHONY : living.s

# target to generate assembly for a file
living.cpp.s:
	$(MAKE) -f CMakeFiles/DI_RPG.dir/build.make CMakeFiles/DI_RPG.dir/living.cpp.s
.PHONY : living.cpp.s

main.o: main.cpp.o

.PHONY : main.o

# target to build an object file
main.cpp.o:
	$(MAKE) -f CMakeFiles/DI_RPG.dir/build.make CMakeFiles/DI_RPG.dir/main.cpp.o
.PHONY : main.cpp.o

main.i: main.cpp.i

.PHONY : main.i

# target to preprocess a source file
main.cpp.i:
	$(MAKE) -f CMakeFiles/DI_RPG.dir/build.make CMakeFiles/DI_RPG.dir/main.cpp.i
.PHONY : main.cpp.i

main.s: main.cpp.s

.PHONY : main.s

# target to generate assembly for a file
main.cpp.s:
	$(MAKE) -f CMakeFiles/DI_RPG.dir/build.make CMakeFiles/DI_RPG.dir/main.cpp.s
.PHONY : main.cpp.s

monster.o: monster.cpp.o

.PHONY : monster.o

# target to build an object file
monster.cpp.o:
	$(MAKE) -f CMakeFiles/DI_RPG.dir/build.make CMakeFiles/DI_RPG.dir/monster.cpp.o
.PHONY : monster.cpp.o

monster.i: monster.cpp.i

.PHONY : monster.i

# target to preprocess a source file
monster.cpp.i:
	$(MAKE) -f CMakeFiles/DI_RPG.dir/build.make CMakeFiles/DI_RPG.dir/monster.cpp.i
.PHONY : monster.cpp.i

monster.s: monster.cpp.s

.PHONY : monster.s

# target to generate assembly for a file
monster.cpp.s:
	$(MAKE) -f CMakeFiles/DI_RPG.dir/build.make CMakeFiles/DI_RPG.dir/monster.cpp.s
.PHONY : monster.cpp.s

paladin.o: paladin.cpp.o

.PHONY : paladin.o

# target to build an object file
paladin.cpp.o:
	$(MAKE) -f CMakeFiles/DI_RPG.dir/build.make CMakeFiles/DI_RPG.dir/paladin.cpp.o
.PHONY : paladin.cpp.o

paladin.i: paladin.cpp.i

.PHONY : paladin.i

# target to preprocess a source file
paladin.cpp.i:
	$(MAKE) -f CMakeFiles/DI_RPG.dir/build.make CMakeFiles/DI_RPG.dir/paladin.cpp.i
.PHONY : paladin.cpp.i

paladin.s: paladin.cpp.s

.PHONY : paladin.s

# target to generate assembly for a file
paladin.cpp.s:
	$(MAKE) -f CMakeFiles/DI_RPG.dir/build.make CMakeFiles/DI_RPG.dir/paladin.cpp.s
.PHONY : paladin.cpp.s

sorcerer.o: sorcerer.cpp.o

.PHONY : sorcerer.o

# target to build an object file
sorcerer.cpp.o:
	$(MAKE) -f CMakeFiles/DI_RPG.dir/build.make CMakeFiles/DI_RPG.dir/sorcerer.cpp.o
.PHONY : sorcerer.cpp.o

sorcerer.i: sorcerer.cpp.i

.PHONY : sorcerer.i

# target to preprocess a source file
sorcerer.cpp.i:
	$(MAKE) -f CMakeFiles/DI_RPG.dir/build.make CMakeFiles/DI_RPG.dir/sorcerer.cpp.i
.PHONY : sorcerer.cpp.i

sorcerer.s: sorcerer.cpp.s

.PHONY : sorcerer.s

# target to generate assembly for a file
sorcerer.cpp.s:
	$(MAKE) -f CMakeFiles/DI_RPG.dir/build.make CMakeFiles/DI_RPG.dir/sorcerer.cpp.s
.PHONY : sorcerer.cpp.s

spirit.o: spirit.cpp.o

.PHONY : spirit.o

# target to build an object file
spirit.cpp.o:
	$(MAKE) -f CMakeFiles/DI_RPG.dir/build.make CMakeFiles/DI_RPG.dir/spirit.cpp.o
.PHONY : spirit.cpp.o

spirit.i: spirit.cpp.i

.PHONY : spirit.i

# target to preprocess a source file
spirit.cpp.i:
	$(MAKE) -f CMakeFiles/DI_RPG.dir/build.make CMakeFiles/DI_RPG.dir/spirit.cpp.i
.PHONY : spirit.cpp.i

spirit.s: spirit.cpp.s

.PHONY : spirit.s

# target to generate assembly for a file
spirit.cpp.s:
	$(MAKE) -f CMakeFiles/DI_RPG.dir/build.make CMakeFiles/DI_RPG.dir/spirit.cpp.s
.PHONY : spirit.cpp.s

warrior.o: warrior.cpp.o

.PHONY : warrior.o

# target to build an object file
warrior.cpp.o:
	$(MAKE) -f CMakeFiles/DI_RPG.dir/build.make CMakeFiles/DI_RPG.dir/warrior.cpp.o
.PHONY : warrior.cpp.o

warrior.i: warrior.cpp.i

.PHONY : warrior.i

# target to preprocess a source file
warrior.cpp.i:
	$(MAKE) -f CMakeFiles/DI_RPG.dir/build.make CMakeFiles/DI_RPG.dir/warrior.cpp.i
.PHONY : warrior.cpp.i

warrior.s: warrior.cpp.s

.PHONY : warrior.s

# target to generate assembly for a file
warrior.cpp.s:
	$(MAKE) -f CMakeFiles/DI_RPG.dir/build.make CMakeFiles/DI_RPG.dir/warrior.cpp.s
.PHONY : warrior.cpp.s

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

