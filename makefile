

COMPILER = gcc
OPTIONS = -Wall
PROGRAM = PA1
SRC = driver.c functions.c
ARGS = poohWComment.ppm resized.ppm negative.ppm

all: $(PROGRAM)

run: $(PROGRAM)
	./$(PROGRAM) $(ARGS) 

$(PROGRAM): $(SRC)
	$(COMPILER) $(OPTIONS) $^ -o $@ 

clean:
	rm *.out

cleanW:
	del *.exe