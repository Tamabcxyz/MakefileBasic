# MakefileBasic

# Cpp Makefile Tutorial

## GCC/Clang Compiler Steps

### Compilation (Assembling)

- Checks the C/C++ language syntax for error
- Generates object files
- Command: g++ main.cc -c
- Produces: main.o

### Linker

- Linking all the source files together, that is all the other object codes in the project.
- Generates the executable file
- Command: g++ main.o -o main
- Produces: main.out (.exe for Windows)

### Compiler Flags (https://gcc.gnu.org/onlinedocs/gcc/Option-Summary.html)

- Debug: ```-g```
- Release: ```-O0 -O1 -O2 -O3 -Og```
- Includes: ```-I```
- Warnings: ```-Wall -Wextra -Wpedantic -Wconversion```

```
CFLAGS	Compiler flags for C (gcc, clang)
CPPFLAGS	Preprocessor flags (for #define, #include)
CXXFLAGS	Compiler flags for C++ (g++, clang++)

✅ Use CPPFLAGS for -D (defines) and -I (include paths).
✅ Use CFLAGS/CXXFLAGS for -O, -Wall, -std=c++17, etc.
✅ Use LDFLAGS for -L (library paths) and -l (linking).
```

## Makefile Commands of the Template

### Makefile Variables

Convention is naming in upper snake_case.

```make
  VARIABLE_NAME = Value
```

Variables can be called by $(VARIABLE_NAME)

```make
  $(VARIABLE_NAME)
```

### Makefile Targets

Convention is naming in snake_case or camelCase.

```make
  targetName: Dependecies
    Command
```

Targets can be called by the ```make``` command.

```bash
  make targetName
```

### Makefile Phony Target

Sometimes you want your Makefile to run commands that do not represent files, for example the "clean" target. You may potentially have a file named clean in your main directory. In such a case Make will be confused because by default the clean target would be associated with this file and Make will only run it when the file doesn't appear to be up-to-date.

```make
.PHONY: clean
clean:
  rm -rf *.o
```

In terms of Make, a phony target is simply a target that is always out-of-date, so whenever you ask make <phony_target>, it will run, independent from the state of the file system.

### Build the Executable

Create the executable in either Debug or Release mode.

```bash
  make build DEBUG=0 # Build type is debug
  make build DEBUG=1 # Build type is release
```

### Run the Executable

Run the executable in either Debug or Release mode.

```bash
  make execute DEBUG=0 # Build type is debug
  make execute DEBUG=1 # Build type is release
```

### Variables of the Makefile Template

- Debug Mode: 1 (True) or 0 (False)
- ENABLE_WARNINGS: 1 (True) or 0 (False)
- WARNINGS_AS_ERRORS: 1 (True) or 0 (False)
- CPP_STANDARD: c++11, c++14, c++17, etc.

### Important Shortcuts of the Makefile Template

- ```$@```: the file name of the target
- ```$<```: the name of the first dependency
- ```$^```: the names of all dependencies


### Using docker to build (integrate with docker)

```
cd integrate_docker
make run_docker
```

### Somethings's intriguing
- ```define```: define a function to call in makefile
```
define greet
	echo "Good morning, $(1)!"
endef

main:
	$(call greet,ABC)
```
- ```eval + call```: combining eval with call is a powerful way to generate dynamic Makefile content
```
#This will dynamically create rules for foo, bar, and baz, each depending on .c files in their respective src/ subdirectories.

define make_rule
$(1): $$(wildcard src/$(1)/*.c)
	$$(CC) $$^ -o $$@
endef

$(foreach bin,foo bar baz,$(eval $(call make_rule,$(bin))))
```
- ```strip```: remove redundant space
```
RAW :=   hello     world    
CLEAN := $(strip $(RAW))

all:
	echo '$(CLEAN)'
```
- ```findstring```: check if one string contains another
```
ifneq ($(findstring Linux,$(OS)),)
    MESSAGE := "Running on Linux"
else
    MESSAGE := "Not Linux"
endif
```
- ```addsuffix + addprefix```: 
```
# SRC => main.c util.c math.c
# OBJ => build/main.o build/util.o build/math.o
FILES := main util math
SRC := $(addsuffix .c, $(FILES))
OBJ := $(addprefix build/, $(FILES:.c=.o))
```
- ```subst```: Simple Text Replacement (text is a string literal)
```
# $(subst from,to,text)
# Replaces every occurrence of from with to in text
$(subst .c,.o,main.c util.c) → main.o util.o
```
- ```patsubst```: Pattern-Based Substitution (text is a pattern)
```
# $(patsubst pattern,replacement,text)
# Works on whitespace-separated words in text.
# pattern can include % as a wildcard.
# Replaces each word that matches the pattern.
$(patsubst %.c,%.o,build/main.c build/util.c) → main.o util.o
```

Referency link: https://github.com/Tamabcxyz/Docker_Project