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

dragon_constr.o: dragon_constr.cpp.o

.PHONY : dragon_constr.o

# target to build an object file
dragon_constr.cpp.o:
	$(MAKE) -f CMakeFiles/DI_RPG.dir/build.make CMakeFiles/DI_RPG.dir/dragon_constr.cpp.o
.PHONY : dragon_constr.cpp.o

dragon_constr.i: dragon_constr.cpp.i

.PHONY : dragon_constr.i

# target to preprocess a source file
dragon_constr.cpp.i:
	$(MAKE) -f CMakeFiles/DI_RPG.dir/build.make CMakeFiles/DI_RPG.dir/dragon_constr.cpp.i
.PHONY : dragon_constr.cpp.i

dragon_constr.s: dragon_constr.cpp.s

.PHONY : dragon_constr.s

# target to generate assembly for a file
dragon_constr.cpp.s:
	$(MAKE) -f CMakeFiles/DI_RPG.dir/build.make CMakeFiles/DI_RPG.dir/dragon_constr.cpp.s
.PHONY : dragon_constr.cpp.s

exoskeleton_constr.o: exoskeleton_constr.cpp.o

.PHONY : exoskeleton_constr.o

# target to build an object file
exoskeleton_constr.cpp.o:
	$(MAKE) -f CMakeFiles/DI_RPG.dir/build.make CMakeFiles/DI_RPG.dir/exoskeleton_constr.cpp.o
.PHONY : exoskeleton_constr.cpp.o

exoskeleton_constr.i: exoskeleton_constr.cpp.i

.PHONY : exoskeleton_constr.i

# target to preprocess a source file
exoskeleton_constr.cpp.i:
	$(MAKE) -f CMakeFiles/DI_RPG.dir/build.make CMakeFiles/DI_RPG.dir/exoskeleton_constr.cpp.i
.PHONY : exoskeleton_constr.cpp.i

exoskeleton_constr.s: exoskeleton_constr.cpp.s

.PHONY : exoskeleton_constr.s

# target to generate assembly for a file
exoskeleton_constr.cpp.s:
	$(MAKE) -f CMakeFiles/DI_RPG.dir/build.make CMakeFiles/DI_RPG.dir/exoskeleton_constr.cpp.s
.PHONY : exoskeleton_constr.cpp.s

hero_constr.o: hero_constr.cpp.o

.PHONY : hero_constr.o

# target to build an object file
hero_constr.cpp.o:
	$(MAKE) -f CMakeFiles/DI_RPG.dir/build.make CMakeFiles/DI_RPG.dir/hero_constr.cpp.o
.PHONY : hero_constr.cpp.o

hero_constr.i: hero_constr.cpp.i

.PHONY : hero_constr.i

# target to preprocess a source file
hero_constr.cpp.i:
	$(MAKE) -f CMakeFiles/DI_RPG.dir/build.make CMakeFiles/DI_RPG.dir/hero_constr.cpp.i
.PHONY : hero_constr.cpp.i

hero_constr.s: hero_constr.cpp.s

.PHONY : hero_constr.s

# target to generate assembly for a file
hero_constr.cpp.s:
	$(MAKE) -f CMakeFiles/DI_RPG.dir/build.make CMakeFiles/DI_RPG.dir/hero_constr.cpp.s
.PHONY : hero_constr.cpp.s

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

living_constr.o: living_constr.cpp.o

.PHONY : living_constr.o

# target to build an object file
living_constr.cpp.o:
	$(MAKE) -f CMakeFiles/DI_RPG.dir/build.make CMakeFiles/DI_RPG.dir/living_constr.cpp.o
.PHONY : living_constr.cpp.o

living_constr.i: living_constr.cpp.i

.PHONY : living_constr.i

# target to preprocess a source file
living_constr.cpp.i:
	$(MAKE) -f CMakeFiles/DI_RPG.dir/build.make CMakeFiles/DI_RPG.dir/living_constr.cpp.i
.PHONY : living_constr.cpp.i

living_constr.s: living_constr.cpp.s

.PHONY : living_constr.s

# target to generate assembly for a file
living_constr.cpp.s:
	$(MAKE) -f CMakeFiles/DI_RPG.dir/build.make CMakeFiles/DI_RPG.dir/living_constr.cpp.s
.PHONY : living_constr.cpp.s

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

monster_constr.o: monster_constr.cpp.o

.PHONY : monster_constr.o

# target to build an object file
monster_constr.cpp.o:
	$(MAKE) -f CMakeFiles/DI_RPG.dir/build.make CMakeFiles/DI_RPG.dir/monster_constr.cpp.o
.PHONY : monster_constr.cpp.o

monster_constr.i: monster_constr.cpp.i

.PHONY : monster_constr.i

# target to preprocess a source file
monster_constr.cpp.i:
	$(MAKE) -f CMakeFiles/DI_RPG.dir/build.make CMakeFiles/DI_RPG.dir/monster_constr.cpp.i
.PHONY : monster_constr.cpp.i

monster_constr.s: monster_constr.cpp.s

.PHONY : monster_constr.s

# target to generate assembly for a file
monster_constr.cpp.s:
	$(MAKE) -f CMakeFiles/DI_RPG.dir/build.make CMakeFiles/DI_RPG.dir/monster_constr.cpp.s
.PHONY : monster_constr.cpp.s

paladin_constr.o: paladin_constr.cpp.o

.PHONY : paladin_constr.o

# target to build an object file
paladin_constr.cpp.o:
	$(MAKE) -f CMakeFiles/DI_RPG.dir/build.make CMakeFiles/DI_RPG.dir/paladin_constr.cpp.o
.PHONY : paladin_constr.cpp.o

paladin_constr.i: paladin_constr.cpp.i

.PHONY : paladin_constr.i

# target to preprocess a source file
paladin_constr.cpp.i:
	$(MAKE) -f CMakeFiles/DI_RPG.dir/build.make CMakeFiles/DI_RPG.dir/paladin_constr.cpp.i
.PHONY : paladin_constr.cpp.i

paladin_constr.s: paladin_constr.cpp.s

.PHONY : paladin_constr.s

# target to generate assembly for a file
paladin_constr.cpp.s:
	$(MAKE) -f CMakeFiles/DI_RPG.dir/build.make CMakeFiles/DI_RPG.dir/paladin_constr.cpp.s
.PHONY : paladin_constr.cpp.s

sorcerer_constr.o: sorcerer_constr.cpp.o

.PHONY : sorcerer_constr.o

# target to build an object file
sorcerer_constr.cpp.o:
	$(MAKE) -f CMakeFiles/DI_RPG.dir/build.make CMakeFiles/DI_RPG.dir/sorcerer_constr.cpp.o
.PHONY : sorcerer_constr.cpp.o

sorcerer_constr.i: sorcerer_constr.cpp.i

.PHONY : sorcerer_constr.i

# target to preprocess a source file
sorcerer_constr.cpp.i:
	$(MAKE) -f CMakeFiles/DI_RPG.dir/build.make CMakeFiles/DI_RPG.dir/sorcerer_constr.cpp.i
.PHONY : sorcerer_constr.cpp.i

sorcerer_constr.s: sorcerer_constr.cpp.s

.PHONY : sorcerer_constr.s

# target to generate assembly for a file
sorcerer_constr.cpp.s:
	$(MAKE) -f CMakeFiles/DI_RPG.dir/build.make CMakeFiles/DI_RPG.dir/sorcerer_constr.cpp.s
.PHONY : sorcerer_constr.cpp.s

spirit_constr.o: spirit_constr.cpp.o

.PHONY : spirit_constr.o

# target to build an object file
spirit_constr.cpp.o:
	$(MAKE) -f CMakeFiles/DI_RPG.dir/build.make CMakeFiles/DI_RPG.dir/spirit_constr.cpp.o
.PHONY : spirit_constr.cpp.o

spirit_constr.i: spirit_constr.cpp.i

.PHONY : spirit_constr.i

# target to preprocess a source file
spirit_constr.cpp.i:
	$(MAKE) -f CMakeFiles/DI_RPG.dir/build.make CMakeFiles/DI_RPG.dir/spirit_constr.cpp.i
.PHONY : spirit_constr.cpp.i

spirit_constr.s: spirit_constr.cpp.s

.PHONY : spirit_constr.s

# target to generate assembly for a file
spirit_constr.cpp.s:
	$(MAKE) -f CMakeFiles/DI_RPG.dir/build.make CMakeFiles/DI_RPG.dir/spirit_constr.cpp.s
.PHONY : spirit_constr.cpp.s

warrior_constr.o: warrior_constr.cpp.o

.PHONY : warrior_constr.o

# target to build an object file
warrior_constr.cpp.o:
	$(MAKE) -f CMakeFiles/DI_RPG.dir/build.make CMakeFiles/DI_RPG.dir/warrior_constr.cpp.o
.PHONY : warrior_constr.cpp.o

warrior_constr.i: warrior_constr.cpp.i

.PHONY : warrior_constr.i

# target to preprocess a source file
warrior_constr.cpp.i:
	$(MAKE) -f CMakeFiles/DI_RPG.dir/build.make CMakeFiles/DI_RPG.dir/warrior_constr.cpp.i
.PHONY : warrior_constr.cpp.i

warrior_constr.s: warrior_constr.cpp.s

.PHONY : warrior_constr.s

# target to generate assembly for a file
warrior_constr.cpp.s:
	$(MAKE) -f CMakeFiles/DI_RPG.dir/build.make CMakeFiles/DI_RPG.dir/warrior_constr.cpp.s
.PHONY : warrior_constr.cpp.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... rebuild_cache"
	@echo "... edit_cache"
	@echo "... DI_RPG"
	@echo "... dragon_constr.o"
	@echo "... dragon_constr.i"
	@echo "... dragon_constr.s"
	@echo "... exoskeleton_constr.o"
	@echo "... exoskeleton_constr.i"
	@echo "... exoskeleton_constr.s"
	@echo "... hero_constr.o"
	@echo "... hero_constr.i"
	@echo "... hero_constr.s"
	@echo "... item.o"
	@echo "... item.i"
	@echo "... item.s"
	@echo "... living_constr.o"
	@echo "... living_constr.i"
	@echo "... living_constr.s"
	@echo "... main.o"
	@echo "... main.i"
	@echo "... main.s"
	@echo "... monster_constr.o"
	@echo "... monster_constr.i"
	@echo "... monster_constr.s"
	@echo "... paladin_constr.o"
	@echo "... paladin_constr.i"
	@echo "... paladin_constr.s"
	@echo "... sorcerer_constr.o"
	@echo "... sorcerer_constr.i"
	@echo "... sorcerer_constr.s"
	@echo "... spirit_constr.o"
	@echo "... spirit_constr.i"
	@echo "... spirit_constr.s"
	@echo "... warrior_constr.o"
	@echo "... warrior_constr.i"
	@echo "... warrior_constr.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

