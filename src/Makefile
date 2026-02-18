CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -g -I.
GCOV_FLAGS = -fprofile-arcs -ftest-coverage
LIBS = -lcheck -lsubunit -lm -lpthread -lrt

SRC_DIR = s21_decimal
HELPER_DIR = s21_helper
TEST_DIR = s21_decimal_test
BUILD_DIR = build
COV_REPORT_DIR = gcov_report

# Все .c файлы из исходников
SRC_FILES := $(wildcard $(SRC_DIR)/*.c)
HELPER_FILES := $(wildcard $(HELPER_DIR)/*.c)
LIB_SRC := $(SRC_FILES) $(HELPER_FILES)

# Объектные файлы библиотеки с gcov
LIB_OBJS := $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/$(SRC_DIR)/%.o,$(SRC_FILES))
LIB_OBJS += $(patsubst $(HELPER_DIR)/%.c,$(BUILD_DIR)/$(HELPER_DIR)/%.o,$(HELPER_FILES))

# Тестовые файлы → отдельные бинарники
TEST_SOURCES := $(wildcard $(TEST_DIR)/*.c)
TEST_BINS := $(patsubst $(TEST_DIR)/%.c,$(BUILD_DIR)/%.out,$(TEST_SOURCES))

.PHONY: all clean test gcov_report

all: test

# Создание директорий
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)/$(SRC_DIR) $(BUILD_DIR)/$(HELPER_DIR)

# Компиляция исходников библиотеки (с gcov для отчёта)
$(BUILD_DIR)/$(SRC_DIR)/%.o: $(SRC_DIR)/%.c s21_decimal.h | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(GCOV_FLAGS) -c $< -o $@

$(BUILD_DIR)/$(HELPER_DIR)/%.o: $(HELPER_DIR)/%.c s21_decimal.h | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(GCOV_FLAGS) -c $< -o $@

# Сборка каждого теста отдельно
$(BUILD_DIR)/%.out: $(TEST_DIR)/%.c $(LIB_OBJS) | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(GCOV_FLAGS) $< $(LIB_OBJS) -o $@ $(LIBS)

# Запуск всех тестов
test: $(TEST_BINS)
	@echo "Running all tests..."
	@failed=0; \
	for t in $(TEST_BINS); do \
		echo ">>> $$t"; \
		if ! $$t; then \
			failed=1; \
		fi; \
	done; \
	exit $$failed

# Генерация отчёта покрытия
gcov_report: test
	lcov --capture --directory $(BUILD_DIR) --output-file coverage.info -q
	genhtml coverage.info --output-directory $(COV_REPORT_DIR)
	@echo "Coverage report: $(COV_REPORT_DIR)/index.html"

# Очистка
clean:
	rm -rf $(BUILD_DIR) coverage.info $(COV_REPORT_DIR)