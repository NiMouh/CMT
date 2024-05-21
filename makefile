# Nome do compilador
CXX = g++

# Flags de compilação
CXXFLAGS = -Wall -Wextra -std=c++17

# Diretório onde estão os ficheiros da biblioteca
LIB_DIR = lib

# Arquivos de origem
SRC = main.cpp $(LIB_DIR)/lib.cpp

# Arquivos objeto
OBJ = main.o $(LIB_DIR)/lib.o

# Nome do executável
EXEC = program

# Regra padrão para construir tudo
all: $(EXEC)

# Regra para construir o executável
$(EXEC): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Regras para compilar arquivos .cpp em .o
main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(LIB_DIR)/lib.o: $(LIB_DIR)/lib.cpp $(LIB_DIR)/lib.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Limpar os arquivos objeto e o executável
clean:
	rm -f $(OBJ) $(EXEC)

.PHONY: all clean
