CXX      = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -I./include --coverage
LDFLAGS  = --coverage

BUILD_DIR = build

SRC_OBJS = $(BUILD_DIR)/Alarme.o \
           $(BUILD_DIR)/Parametro.o \
           $(BUILD_DIR)/Equipamento.o \
           $(BUILD_DIR)/Conjunto.o \
           $(BUILD_DIR)/LinhaDeProducao.o \
           $(BUILD_DIR)/Log.o \
           $(BUILD_DIR)/Usuario.o \
           $(BUILD_DIR)/Sistema.o

TEST_OBJS = $(BUILD_DIR)/test_main.o \
            $(BUILD_DIR)/test_Alarme.o \
            $(BUILD_DIR)/test_Parametro.o \
            $(BUILD_DIR)/test_Equipamento.o \
            $(BUILD_DIR)/test_Conjunto.o \
            $(BUILD_DIR)/test_LinhaDeProducao.o \
            $(BUILD_DIR)/test_Log.o \
            $(BUILD_DIR)/test_Usuario.o \
            $(BUILD_DIR)/test_Sistema.o

TEST_BIN = $(BUILD_DIR)/test_runner

.PHONY: all test clean

all: $(TEST_BIN)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/%.o: src/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(BUILD_DIR)/%.o: tests/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -I./tests -c -o $@ $<

$(TEST_BIN): $(SRC_OBJS) $(TEST_OBJS)
	$(CXX) $(LDFLAGS) -o $@ $^

test: $(TEST_BIN)
	-$(TEST_BIN)
	python -m gcovr -r . --object-directory=$(BUILD_DIR) \
	    --exclude='tests/.*' \
	    --exclude='include/doctest\.h' \
	    --txt
	python -m gcovr -r . --object-directory=$(BUILD_DIR) \
	    --exclude='tests/.*' \
	    --exclude='include/doctest\.h' \
	    --html --html-details \
	    -o $(BUILD_DIR)/coverage.html

clean:
	powershell -Command "Remove-Item -Recurse -Force -ErrorAction SilentlyContinue '$(BUILD_DIR)'"
