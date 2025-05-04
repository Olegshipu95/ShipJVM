# Компилятор
CC = gcc

# Базовые флаги компиляции
CFLAGS = -std=c11 -Wall -Wextra -Werror -fstack-protector-strong
LDFLAGS = 

# Флаги для разных сборок
RELEASE_FLAGS = -O2 -DNDEBUG -flto
DEBUG_FLAGS = -g3 -O0 -DDEBUG -fno-omit-frame-pointer
SANITIZE_FLAGS = -fsanitize=address,undefined,leak \
                 -fsanitize=float-divide-by-zero \
                 -fsanitize=null \
                 -fsanitize=alignment \
                 -fsanitize=bounds \
                 -fsanitize=enum \
                 -fsanitize=object-size
THREAD_SANITIZER_FLAGS = -fsanitize=thread
MEMORY_SANITIZER_FLAGS = -fsanitize=memory -fPIE -pie

# Имена исполняемых файлов
TARGET = jvm
DEBUG_TARGET = jvm_debug
SANITIZE_TARGET = jvm_sanitize
TSAN_TARGET = jvm_tsan
MSAN_TARGET = jvm_msan

# Папки проекта
SRC_DIR ?= ./src

INCLUDE_DIRS ?= ./include ./include/classfile ./include/runtime ./include/util ./include/bytecode ./include/classloader ./include/runtime

BUILD_DIR ?= ./build

# Добавляем пути к include в CFLAGS
CFLAGS += $(addprefix -I,$(INCLUDE_DIRS))

# Автоматический поиск исходных файлов во всех поддиректориях src
SOURCES = $(shell find $(SRC_DIR) -name '*.c')
OBJECTS = $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SOURCES))
DEBUG_OBJECTS = $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%_debug.o,$(SOURCES))
SANITIZE_OBJECTS = $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%_sanitize.o,$(SOURCES))
TSAN_OBJECTS = $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%_tsan.o,$(SOURCES))
MSAN_OBJECTS = $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%_msan.o,$(SOURCES))

# Создаем папку build и поддиректории если их нет
$(shell mkdir -p $(BUILD_DIR))
$(foreach src,$(SOURCES), \
    $(eval src_dir := $(dir $(patsubst $(SRC_DIR)/%,$(BUILD_DIR)/%,$(src)))) \
    $(shell mkdir -p $(src_dir)))

# Правило по умолчанию - сборка релиза
all: release

# Релизная сборка
release: CFLAGS += $(RELEASE_FLAGS)
release: LDFLAGS += -flto
release: $(TARGET)

# Отладочная сборка
debug: CFLAGS += $(DEBUG_FLAGS)
debug: $(DEBUG_TARGET)

# Основная сборка с санитайзерами
sanitize: CFLAGS += $(DEBUG_FLAGS) $(SANITIZE_FLAGS)
sanitize: LDFLAGS += $(SANITIZE_FLAGS)
sanitize: $(SANITIZE_TARGET)

# Сборка с ThreadSanitizer
tsan: CFLAGS += $(DEBUG_FLAGS) $(THREAD_SANITIZER_FLAGS)
tsan: LDFLAGS += $(THREAD_SANITIZER_FLAGS)
tsan: $(TSAN_TARGET)

# Сборка с MemorySanitizer
msan: CFLAGS += $(DEBUG_FLAGS) $(MEMORY_SANITIZER_FLAGS)
msan: LDFLAGS += $(MEMORY_SANITIZER_FLAGS)
msan: $(MSAN_TARGET)

# Линковка всех версий
$(TARGET): $(OBJECTS)
	$(CC) $(LDFLAGS) $^ -o $@

$(DEBUG_TARGET): $(DEBUG_OBJECTS)
	$(CC) $(LDFLAGS) $^ -o $@

$(SANITIZE_TARGET): $(SANITIZE_OBJECTS)
	$(CC) $(LDFLAGS) $^ -o $@

$(TSAN_TARGET): $(TSAN_OBJECTS)
	$(CC) $(LDFLAGS) $^ -o $@

$(MSAN_TARGET): $(MSAN_OBJECTS)
	$(CC) $(LDFLAGS) $^ -o $@

# Компиляция объектных файлов
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%_debug.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%_sanitize.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%_tsan.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%_msan.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Утилиты для запуска
run: release
	./$(TARGET)

run_debug: debug
	./$(DEBUG_TARGET)

run_sanitize: sanitize
	ASAN_OPTIONS=detect_leaks=1 ./$(SANITIZE_TARGET)

run_tsan: tsan
	TSAN_OPTIONS=second_deadlock_stack=1 ./$(TSAN_TARGET)

run_msan: msan
	MSAN_OPTIONS=poison_in_dtor=1 ./$(MSAN_TARGET)

# Анализ покрытия кода
coverage: CFLAGS += -fprofile-arcs -ftest-coverage
coverage: LDFLAGS += -lgcov
coverage: clean
	$(MAKE) debug
	./$(DEBUG_TARGET)
	gcov -r $(SOURCES)

# Статический анализ
analyze:
	scan-build --use-cc=$(CC) $(MAKE) debug

# Очистка
clean:
	rm -rf $(BUILD_DIR) $(TARGET) $(DEBUG_TARGET) $(SANITIZE_TARGET) \
        $(TSAN_TARGET) $(MSAN_TARGET) *.gcov *.gcda *.gcno

# Установка зависимостей
deps:
	sudo apt-get install -y \
		gcc \
		valgrind \
		clang-tools \
		llvm \
		lcov

# Форматирование кода с помощью clang-format
format:
	find . -type f \( -name "*.c" -o -name "*.h" \) \
		-exec clang-format -i --style=GNU {} \;

.PHONY: all release debug sanitize tsan msan \
        run run_debug run_sanitize run_tsan run_msan \
        coverage analyze clean deps format
