CXX      = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -I./include --coverage
LDFLAGS  = --coverage

BUILD_DIR = build

# Deteccao de SO: comandos diferem entre Windows e POSIX (Linux/macOS)
ifeq ($(OS),Windows_NT)
    MKDIR  = if not exist "$(BUILD_DIR)" mkdir "$(BUILD_DIR)"
    RMDIR  = if exist "$(BUILD_DIR)" rmdir /S /Q "$(BUILD_DIR)"
    PYTHON = python
else
    MKDIR  = mkdir -p $(BUILD_DIR)
    RMDIR  = rm -rf $(BUILD_DIR)
    PYTHON = python3
endif

SRC_OBJS = $(BUILD_DIR)/Alarme.o \
           $(BUILD_DIR)/Parametro.o \
           $(BUILD_DIR)/Equipamento.o \
           $(BUILD_DIR)/Motor.o \
           $(BUILD_DIR)/Sensor.o \
           $(BUILD_DIR)/Valvula.o \
           $(BUILD_DIR)/Atuador.o \
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
            $(BUILD_DIR)/test_Sistema.o \
            $(BUILD_DIR)/test_Excecoes.o

TEST_BIN = $(BUILD_DIR)/test_runner
APP_BIN  = $(BUILD_DIR)/sistema

.PHONY: all test test-bin clean app run

# Alvo default: apenas o executavel da aplicacao
app: $(APP_BIN)

# Builda tudo (app + test runner)
all: $(APP_BIN) $(TEST_BIN)

# Builda apenas o binario de testes
test-bin: $(TEST_BIN)

$(BUILD_DIR):
	$(MKDIR)

$(BUILD_DIR)/%.o: src/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(BUILD_DIR)/%.o: tests/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -I./tests -c -o $@ $<

$(TEST_BIN): $(SRC_OBJS) $(TEST_OBJS)
	$(CXX) $(LDFLAGS) -o $@ $^

$(APP_BIN): $(SRC_OBJS) $(BUILD_DIR)/main.o
	$(CXX) $(LDFLAGS) -o $@ $^

run: $(APP_BIN)
	./$(APP_BIN)

test: $(TEST_BIN)
	-$(TEST_BIN)
	$(PYTHON) -m gcovr -r . --object-directory=$(BUILD_DIR) \
	    --exclude='tests/.*' \
	    --exclude='include/doctest\.h' \
	    --exclude='src/main\.cpp' \
	    --txt
	$(PYTHON) -m gcovr -r . --object-directory=$(BUILD_DIR) \
	    --exclude='tests/.*' \
	    --exclude='include/doctest\.h' \
	    --exclude='src/main\.cpp' \
	    --html --html-details \
	    -o $(BUILD_DIR)/coverage.html

clean:
	$(RMDIR)
