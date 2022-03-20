####################Variables####################

CC=g++
CPP_FLAGS:=--std=c++11
INCLUDE:=
DEFINES:=

FLAGS=$(CPP_FLAGS) $(INCLUDE) $(DEFINES)

SRC=$(wildcard *.cpp)
OBJ=$(subst .cpp,.o,$(SRC))

BIN=prog

#####################Targets####################

all: $(BIN)

$(BIN): $(OBJ)
	$(CC) $^ -o $@ $(FLAGS)

%.o: %.cpp
	$(CC) -c $< -o $@ $(FLAGS)

####################PHONY Targets###############

.PHONY: clean run

clean:
	rm *.o $(BIN) || true

run: $(BIN)
	./$(BIN)


