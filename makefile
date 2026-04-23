CC=g++
CFLAGS=-std=c++17
INCLUDECADMIUM=-I $(CADMIUM)

bin_folder := $(shell mkdir -p bin)
build_folder := $(shell mkdir -p build)
results_folder := $(shell mkdir -p simulation_results)

all: tests freight_elevator_system

build/main_ecall_test.o: test/main_ecall_test.cpp
	$(CC) -g -c $(CFLAGS) $(INCLUDECADMIUM) test/main_ecall_test.cpp -o build/main_ecall_test.o

build/main_econtrol_test.o: test/main_econtrol_test.cpp
	$(CC) -g -c $(CFLAGS) $(INCLUDECADMIUM) test/main_econtrol_test.cpp -o build/main_econtrol_test.o

build/main_evehicle_test.o: test/main_evehicle_test.cpp
	$(CC) -g -c $(CFLAGS) $(INCLUDECADMIUM) test/main_evehicle_test.cpp -o build/main_evehicle_test.o

build/main_elevator_test.o: test/main_elevator_test.cpp
	$(CC) -g -c $(CFLAGS) $(INCLUDECADMIUM) test/main_elevator_test.cpp -o build/main_elevator_test.o

build/main.o: top_model/main.cpp
	$(CC) -g -c $(CFLAGS) $(INCLUDECADMIUM) top_model/main.cpp -o build/main.o

tests: build/main_ecall_test.o build/main_econtrol_test.o build/main_evehicle_test.o build/main_elevator_test.o
	$(CC) -g -o bin/ECALL_TEST build/main_ecall_test.o
	$(CC) -g -o bin/ECONTROL_TEST build/main_econtrol_test.o
	$(CC) -g -o bin/EVEHICLE_TEST build/main_evehicle_test.o
	$(CC) -g -o bin/ELEVATOR_TEST build/main_elevator_test.o

freight_elevator_system: build/main.o
	$(CC) -g -o bin/FREIGHT_ELEVATOR_TEST build/main.o

clean:
	rm -f bin/* build/*

