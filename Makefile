#Компилятор
CC = gcc

#Флаги компиляции
CFLAGS = -I./include  -std=c11

#Имя исполняемого файла
TARGET = my_program

#Папки с исходными файлами
SRC_DIR = src
INCLUDE_DIR = include

#Автоматический поиск исходных файлов
SOURCES = $(wildcard $(SRC_DIR)/*.c)
OBJECTS = $(patsubst $(SRC_DIR)/%.c, %.o, $(SOURCES))

# Сборка проекта
all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $^ -o $@

%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Очистка
clean:
	rm -f $(OBJECTS) $(TARGET)

.PHONY: all clean