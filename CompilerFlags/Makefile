# this we will discus about variable and flags
# note: variables can only be string
# note: single or double quotes for variable names or value have no meaning to Make, it alway treat as string

# VARIABLE_TEST = 1

# CC: Program for compiling C programs; default gcc
# CXX: Program fro compiling C++ programs; default g++
# CFLAGS: Extra flags to give to the C compiler
# CXXFLAGS: Extra flags to give to the C++ compiler
# CPPFLAGS: Extra flags to give to the C preprocessor
# LDFLAGS: Extra flags to give to the linker


DEBUG = 1
EXECUTABLE_NAME = main

CXX_STANDARD = c++17
CXX_WARNINGS = -Wall -Wextra -Wpedantic
CXX = g++
CXXFLAGS = $(CXX_WARNINGS) -std=$(CXX_STANDARD)
LDFLAGS =

ifeq ($(DEBUG), 1)
CXXFLAGS += -g -O0
else
CXXFLAGS += -O3
endif

COMPILER_CALL = $(CXX) $(CXXFLAGS)

build: my_lib.o main.o
	$(COMPILER_CALL) main.o my_lib.o $(LDFLAGS) -o $(EXECUTABLE_NAME)

main.o:
	$(COMPILER_CALL) -c main.c -o main.o

my_lib.o:
	$(COMPILER_CALL) -c my_lib.c -o my_lib.o

execute:
	./main

clean:
	rm -f *.o
	rm -f main

#default debug mode auto active, so to disable debug mode we can use command "make build DEBUG=0"