# My third makefile

# Name of the project
PROJ_NAME=beale

# .c files
C_SOURCE=$(wildcard ./src/*.c)

# .h files
H_SOURCE=$(wildcard ./include/*.h)

# Object files
OBJ=$(subst .c,.o,$(subst src,objects,$(C_SOURCE)))

# Compiler and linker
CC=gcc

# Flags for compiler
CC_FLAGS=-c         \
         -W         \
         -Wall      \
				 -std=c99   \

# Command used at clean target
RM = rm -rf

# Compilation and linking
all: objFolder $(PROJ_NAME)
 
$(PROJ_NAME): $(OBJ)
	$(CC) $^ -o $@ 
 
./objects/%.o: ./src/%.c ./include/%.h
	$(CC) $< $(CC_FLAGS) -o $@
 
./objects/beale.o: ./src/beale.c $(H_SOURCE)
	$(CC) $< $(CC_FLAGS) -o $@
 
objFolder:
	@mkdir -p objects
 
clean:
	$(RM) ./objects/*.o $(PROJ_NAME) *~
 
purge: clean
	$(RM) ./objects

.PHONY: all clean