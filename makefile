
COMPILER = gcc
OPTIONS = -Wall
PROGRAM := PA1
SRC = driver.c functions.c
HEADER = functions.h
ARGS = input.ppm resized.ppm negative.ppm
ifeq ($(OS),Windows_NT)
EXT = .exe
else
EXT = .out
endif
PROGRAM := $(PROGRAM)$(EXT)

all: $(PROGRAM)

run: $(PROGRAM)
	./$(PROGRAM) $(ARGS) 

$(PROGRAM): $(SRC)
	$(COMPILER) $(OPTIONS) $^ -o $@

tar:
	tar -czvf PA1.tar.gz makefile readme.txt $(SRC) $(HEADER)

ifeq ($(OS),Windows_NT)
clean:
	del *.o *.out *.exe
else
clean:
	rm -f *.o *.out *.exe
endif

