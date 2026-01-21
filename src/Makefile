CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c11
TEST_LINK_FLAGS = $(shell pkg-config --cflags --libs check) --coverage -lm

SRC_DIR = s21_decimal
OBJ_DIR = obj
INC_DIR = .

SOURCES = $(wildcard $(SRC_DIR)/*.c)
HEADERS = $(wildcard $(INC_DIR)/*.h)
OBJECTS = $(SOURCES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
LIBRARY = s21_decimal.a

TEST_DIR = s21_decimal_test
TEST_SOURCES = $(wildcard $(TEST_DIR)/*.c)
TEST_OBJECTS = $(TEST_SOURCES:$(TEST_DIR)/%.c=$(OBJ_DIR)/test_%.o)
TEST_BINARY = s21_test

CFLAGS_COV = $(CFLAGS) --coverage
OBJECTS_COV = $(SOURCES:$(SRC_DIR)/%.c=$(OBJ_DIR)/cov_%.o)

.PHONY: all clean rebuild format_check format test run_test gcov_report

all: $(LIBRARY)

$(LIBRARY): $(OBJECTS) $(HEADERS)
	ar rcs $@ $(OBJECTS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS) | $(OBJ_DIR)
	$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $@

test: $(TEST_BINARY)

$(TEST_BINARY): $(LIBRARY) $(TEST_OBJECTS)
	$(CC) $(CFLAGS) -I$(INC_DIR) $(TEST_OBJECTS) $(LIBRARY) $(TEST_LINK_FLAGS) -o $@

$(OBJ_DIR)/test_%.o: $(TEST_DIR)/%.c $(HEADERS) | $(OBJ_DIR)
	$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

run_test: test
	./$(TEST_BINARY)

gcov_report: $(OBJECTS_COV) $(TEST_OBJECTS)
	$(CC) $(CFLAGS_COV) -I$(INC_DIR) $(OBJECTS_COV) $(TEST_OBJECTS) $(TEST_LINK_FLAGS) -o s21_test_cov
	./s21_test_cov
	mkdir -p coverage_report
	lcov --capture --directory . --output-file coverage_report/coverage.info
	genhtml coverage_report/coverage.info --output-directory coverage_report

$(OBJ_DIR)/cov_%.o: $(SRC_DIR)/%.c $(HEADERS) | $(OBJ_DIR)
	$(CC) $(CFLAGS_COV) -I$(INC_DIR) -c $< -o $@

clean:
	rm -rf $(LIBRARY) $(OBJ_DIR) $(TEST_BINARY) coverage_report s21_test_cov

rebuild: clean all

format_check:
	clang-format -n --style=file:../materials/linters/.clang-format $(INC_DIR)/*.h
	clang-format -n --style=file:../materials/linters/.clang-format $(SRC_DIR)/*.c

format:
	clang-format -i --style=file:../materials/linters/.clang-format $(INC_DIR)/*.h
	clang-format -i --style=file:../materials/linters/.clang-format $(SRC_DIR)/*.c

