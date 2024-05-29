CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17
LIB_DIR = lib
DEPS = -llxc
SRC = main.cpp $(LIB_DIR)/lib.cpp
OBJ = main.o $(LIB_DIR)/lib.o
EXEC = program

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(DEPS)

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(LIB_DIR)/lib.o: $(LIB_DIR)/lib.cpp $(LIB_DIR)/lib.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(EXEC)

.PHONY: all clean