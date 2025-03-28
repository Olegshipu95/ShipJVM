# Компилятор
CC = gcc

# Флаги компиляции
CFLAGS = -I./include -std=c11 
DEBUG_FLAGS = -g -O0  # Добавляем флаги для отладки

# Имя исполняемого файла
TARGET = jvm

# Папки с исходными файлами
SRC_DIR ?= ./src
INCLUDE_DIR ?= ./include
BUILD_DIR ?= ./build

# Автоматический поиск исходных файлов
SOURCES = $(wildcard $(SRC_DIR)/*.c)
OBJECTS = $(patsubst $(SRC_DIR)/%.c, %.o, $(SOURCES))
DEBUG_OBJECTS = $(patsubst $(SRC_DIR)/%.c, %_debug.o, $(SOURCES))

# Сборка релизной версии
all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $^ -o $@

%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Сборка отладочной версии
debug: $(TARGET)_debug

$(TARGET)_debug: $(DEBUG_OBJECTS)
	$(CC) $(CFLAGS) $(DEBUG_FLAGS) $^ -o $@

%_debug.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $(DEBUG_FLAGS) -c $< -o $@

# Запуск отладки с gdb
gdb: debug
	gdb ./$(TARGET)_debug

# Очистка
clean:
	rm -f $(OBJECTS) $(DEBUG_OBJECTS) $(TARGET) $(TARGET)_debug

.PHONY: all clean debug gdb