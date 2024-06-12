# Diretório de origem dos arquivos .c
SRC_DIR = .

# Nome do executável final
TARGET = main.out
TEST_TARGET = $(SRC_DIR)/tests/run_tests.out

# Todos os arquivos .c exceto o que queremos ignorar
SRC_FILES = $(SRC_DIR)/*.c
TEST_SRC_FILES = $(filter-out $(SRC_DIR)/main.c, $(wildcard $(SRC_DIR)/*.c)) $(SRC_DIR)/tests/*.c


# Compilador e flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c11

# Regras de compilação
all: $(TARGET)

test: $(TEST_TARGET)

$(TARGET):
	$(CC) -DVERBOSE $(SRC_FILES) $(CFLAGS) -o $@ $^

$(TEST_TARGET): 
	$(CC) $(TEST_SRC_FILES) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) $(TEST_TARGET)

.PHONY: all test clean

