####################Variables####################

CC=g++
OTIMIZATION=-O2
CPP_FLAGS:=--std=c++11
INCLUDE:=
DEFINES:=
ASSEMBLER_FLAGS= -S -fno-asynchronous-unwind-tables

FLAGS=$(CPP_FLAGS) $(INCLUDE) $(DEFINES) $(OTIMIZATION)

SRC=$(wildcard *.cpp)
OBJ=$(subst .cpp,.o,$(SRC))
ASM=$(subst .cpp,.asm,$(SRC))

BIN=prog

#####################Targets####################

all: $(BIN)

$(BIN): $(OBJ)
	$(CC) $^ -o $@ $(FLAGS)

%.o: %.cpp
	$(CC) -c $< -o $@ $(FLAGS)

%.asm: %.cpp
	$(CC) -c $< -o $@ $(ASSEMBLER_FLAGS) $(FLAGS)

asm: $(ASM)

####################PHONY Targets###############

.PHONY: clean run

clean:
	rm *.o *.asm $(BIN) || true

run: $(BIN)
	./$(BIN)


