.RECIPEPREFIX := >
SHELL := /bin/sh
.SHELLFLAGS := -c
.SILENT:

EXEEXT :=
BUILD_ENV_PREFIX :=
COPY_FILE := cp -f
REMOVE_DIRS := rm -rf
MAKE_DIR := mkdir -p
RUNTIME_DLL_TARGETS :=

ifeq ($(OS),Windows_NT)
SHELL := cmd.exe
.SHELLFLAGS := /c
EXEEXT := .exe
COPY_FILE := copy /y
REMOVE_DIRS := rmdir /s /q
MAKE_DIR := mkdir

ifneq ("$(wildcard C:/msys64/ucrt64/bin/g++.exe)","")
CC := C:/msys64/ucrt64/bin/g++.exe
TOOLCHAIN_BIN := C:/msys64/ucrt64/bin
else ifneq ("$(wildcard C:/msys64/mingw64/bin/g++.exe)","")
CC := C:/msys64/mingw64/bin/g++.exe
TOOLCHAIN_BIN := C:/msys64/mingw64/bin
else ifneq ("$(wildcard C:/msys64/clang64/bin/g++.exe)","")
CC := C:/msys64/clang64/bin/g++.exe
TOOLCHAIN_BIN := C:/msys64/clang64/bin
endif

ifneq ("$(TOOLCHAIN_BIN)","")
TOOLCHAIN_BIN_WIN := $(subst /,\,$(TOOLCHAIN_BIN))
BUILD_ENV_PREFIX := set "PATH=$(TOOLCHAIN_BIN);%PATH%" &&
RUNTIME_DLL_TARGETS := bin/libgcc_s_seh-1.dll bin/libstdc++-6.dll bin/libwinpthread-1.dll
endif
endif

CC ?= g++
CFLAGS := -std=c++17

CADMIUM_DIR ?= ../cadmium_v2
ifeq ("$(wildcard $(CADMIUM_DIR)/include)","")
ifeq ("$(wildcard ../cadmium/include)","")
$(error Could not find Cadmium headers. Clone cadmium_v2 beside this repo, or run 'make CADMIUM_DIR=/path/to/cadmium_v2')
else
CADMIUM_DIR := ../cadmium
endif
endif

INCLUDECADMIUM := -I $(CADMIUM_DIR)/include

ifneq ("$(wildcard ../DESTimes/include)","")
INCLUDEDESTIMES := -I ../DESTimes/include
else ifneq ("$(wildcard ../../DESTimes/include)","")
INCLUDEDESTIMES := -I ../../DESTimes/include
else
INCLUDEDESTIMES :=
endif

INCLUDELOCAL := -I ./atomics -I ./data_structures -I ./top_model

TOP_MODEL_EXE := bin/freight_elevator_top$(EXEEXT)
TEST_EXES := \
	bin/ecall_test$(EXEEXT) \
	bin/econtrol_test$(EXEEXT) \
	bin/evehicle_test$(EXEEXT) \
	bin/elevator_test$(EXEEXT)

DATA_OBJ := build/messages.o

all: simulator tests

simulator: | bin simulation_results
simulator: $(TOP_MODEL_EXE) $(RUNTIME_DLL_TARGETS)

tests: | bin simulation_results
tests: $(TEST_EXES) $(RUNTIME_DLL_TARGETS)

$(TOP_MODEL_EXE): | bin
$(TOP_MODEL_EXE): $(DATA_OBJ) build/main_top.o
>$(BUILD_ENV_PREFIX) $(CC) $(CFLAGS) $(INCLUDECADMIUM) $(INCLUDEDESTIMES) $(INCLUDELOCAL) -o $@ $^

build/main_top.o: | build
build/main_top.o: top_model/main.cpp \
	data_structures/messages.hpp \
	top_model/experiment.hpp top_model/freight_elevator_top.hpp top_model/elevator_coupled.hpp \
	atomics/ecall.hpp atomics/econtrol.hpp atomics/evehicle.hpp
>$(BUILD_ENV_PREFIX) $(CC) $(CFLAGS) $(INCLUDECADMIUM) $(INCLUDEDESTIMES) $(INCLUDELOCAL) -c $< -o $@

bin/ecall_test$(EXEEXT): | bin
bin/ecall_test$(EXEEXT): $(DATA_OBJ) build/main_ecall_test.o
>$(BUILD_ENV_PREFIX) $(CC) $(CFLAGS) $(INCLUDECADMIUM) $(INCLUDEDESTIMES) $(INCLUDELOCAL) -o $@ $^

build/main_ecall_test.o: | build
build/main_ecall_test.o: test/main_ecall_test.cpp \
	data_structures/messages.hpp atomics/ecall.hpp
>$(BUILD_ENV_PREFIX) $(CC) $(CFLAGS) $(INCLUDECADMIUM) $(INCLUDEDESTIMES) $(INCLUDELOCAL) -c $< -o $@

bin/econtrol_test$(EXEEXT): | bin
bin/econtrol_test$(EXEEXT): $(DATA_OBJ) build/main_econtrol_test.o
>$(BUILD_ENV_PREFIX) $(CC) $(CFLAGS) $(INCLUDECADMIUM) $(INCLUDEDESTIMES) $(INCLUDELOCAL) -o $@ $^

build/main_econtrol_test.o: | build
build/main_econtrol_test.o: test/main_econtrol_test.cpp \
	data_structures/messages.hpp atomics/econtrol.hpp
>$(BUILD_ENV_PREFIX) $(CC) $(CFLAGS) $(INCLUDECADMIUM) $(INCLUDEDESTIMES) $(INCLUDELOCAL) -c $< -o $@

bin/evehicle_test$(EXEEXT): | bin
bin/evehicle_test$(EXEEXT): $(DATA_OBJ) build/main_evehicle_test.o
>$(BUILD_ENV_PREFIX) $(CC) $(CFLAGS) $(INCLUDECADMIUM) $(INCLUDEDESTIMES) $(INCLUDELOCAL) -o $@ $^

build/main_evehicle_test.o: | build
build/main_evehicle_test.o: test/main_evehicle_test.cpp \
	data_structures/messages.hpp atomics/evehicle.hpp
>$(BUILD_ENV_PREFIX) $(CC) $(CFLAGS) $(INCLUDECADMIUM) $(INCLUDEDESTIMES) $(INCLUDELOCAL) -c $< -o $@

bin/elevator_test$(EXEEXT): | bin
bin/elevator_test$(EXEEXT): $(DATA_OBJ) build/main_elevator_test.o
>$(BUILD_ENV_PREFIX) $(CC) $(CFLAGS) $(INCLUDECADMIUM) $(INCLUDEDESTIMES) $(INCLUDELOCAL) -o $@ $^

build/main_elevator_test.o: | build
build/main_elevator_test.o: test/main_elevator_test.cpp \
	data_structures/messages.hpp top_model/elevator_coupled.hpp \
	atomics/econtrol.hpp atomics/evehicle.hpp
>$(BUILD_ENV_PREFIX) $(CC) $(CFLAGS) $(INCLUDECADMIUM) $(INCLUDEDESTIMES) $(INCLUDELOCAL) -c $< -o $@

build/messages.o: | build
build/messages.o: data_structures/messages.cpp data_structures/messages.hpp
>$(BUILD_ENV_PREFIX) $(CC) $(CFLAGS) $(INCLUDECADMIUM) $(INCLUDEDESTIMES) $(INCLUDELOCAL) -c $< -o $@

bin/libgcc_s_seh-1.dll: $(TOOLCHAIN_BIN)/libgcc_s_seh-1.dll | bin
>$(BUILD_ENV_PREFIX) $(COPY_FILE) "$(TOOLCHAIN_BIN_WIN)\libgcc_s_seh-1.dll" "$@" >nul

bin/libstdc++-6.dll: $(TOOLCHAIN_BIN)/libstdc++-6.dll | bin
>$(BUILD_ENV_PREFIX) $(COPY_FILE) "$(TOOLCHAIN_BIN_WIN)\libstdc++-6.dll" "$@" >nul

bin/libwinpthread-1.dll: $(TOOLCHAIN_BIN)/libwinpthread-1.dll | bin
>$(BUILD_ENV_PREFIX) $(COPY_FILE) "$(TOOLCHAIN_BIN_WIN)\libwinpthread-1.dll" "$@" >nul

bin build simulation_results:
ifeq ($(OS),Windows_NT)
>if not exist $@ $(MAKE_DIR) $@
else
>$(MAKE_DIR) "$@"
endif

clean:
ifeq ($(OS),Windows_NT)
>if exist bin $(REMOVE_DIRS) bin
>if exist build $(REMOVE_DIRS) build
>if exist simulation_results $(REMOVE_DIRS) simulation_results
else
>$(REMOVE_DIRS) bin build simulation_results
endif
