#=================================================

#DECLARAÇÕES

#diretórios
SRC_DIR = src
LIB_DIR = $(SRC_DIR)/lib

#executavel
TARGET = $(SRC_DIR)/hello

#arquivo_fonte
SRC = $(SRC_DIR)/main.c
LIB_SRC = $(LIB_DIR)/bib.c

#objetos
LIB_OBJ = $(LIB_DIR)/bib.o
LIB_A = $(LIB_DIR)/libbib.a

#compilador
CC = gcc

#flags de compilação
CFLAGS = -Wall -g -I$(LIB_DIR)

#bibliotecas a mais
LIBS = -L$(LIB_DIR) -lbib

#=================================================

#TAGS

all: $(TARGET)

#regra para compilar o executável a partir do arquivo fonte
$(TARGET): $(LIB_A) $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC) $(LIBS)

#regra para compilar a biblioteca estática
$(LIB_A): $(LIB_OBJ)
	ar rcs $(LIB_A) $(LIB_OBJ)

#regra para compilar o arquivo objeto da biblioteca
$(LIB_OBJ): $(LIB_SRC) $(LIB_DIR)/bib.h
	$(CC) $(CFLAGS) -c $(LIB_SRC) -o $(LIB_OBJ)

#=================================================

#REGRAS ESPECIAIS

#executa o arquivo executável
check: $(TARGET)
	./$(TARGET)

#limpa os arquivos feitos
clean:
	rm -f $(TARGET) $(LIB_DIR)/*.o $(LIB_DIR)/*.a


#=================================================
