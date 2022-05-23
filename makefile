# project
VERSION = 0.1.0

# compiler
CXX = gcc
LIBSFLAGS = -lmingw32
CFLAGS =
DEFINES =
INCLUDE = include/

# directories
BIN = out
SRC = src
OBJ = .obj
LIB = libs
OUT = libEngine

# tests
TEST_BIN = test/out
TEST_SRC = test
TEST_OBJ = test/.obj
TEST_LIB = $(BIN)
TEST_OUT = test.exe

# source files
SRCS = $(wildcard $(SRC)/*.c) $(wildcard $(SRC)/**/*.c) $(wildcard $(SRC)/**/**/*.c)
OBJS := $(patsubst %.c, $(OBJ)/%.o, $(notdir $(SRCS)))

TEST_SRCS = $(wildcard $(TEST_SRC)/*.c) $(wildcard $(TEST_SRC)/**/*.c) $(wildcard $(TEST_SRC)/**/**/*.c)
TEST_OBJS := $(patsubst %.c, $(TEST_OBJ)/%.o, $(notdir $(TEST_SRCS)))

all: $(OUT)

release: CFLAGS = -Wall -O2 -D NDEBUG
release: clean
release: $(OUT)

dbg: CFLAGS = -g3
dbg: all

dbgRebuild: CFLAGS = -g3
dbgRebuild: rebuild

rebuild: clean
rebuild: $(OUT)

test: $(TEST_OUT)

clean:
	@del $(OBJ)\*.o

$(OUT) : $(OBJS)
	ar rcs $(BIN)/$(OUT).a $(OBJ)/*.o

$(OBJ)/%.o : $(SRC)/%.c
	$(CXX) -o $@ -c $< -I $(INCLUDE) -L $(LIB) $(DEFINES) $(CFLAGS)

$(OBJ)/%.o : $(SRC)/*/%.c
	$(CXX) -o $@ -c $< -I $(INCLUDE) -L $(LIB) $(DEFINES) $(CFLAGS)

$(OBJ)/%.o : $(SRC)/*/*/%.c
	$(CXX) -o $@ -c $< -I $(INCLUDE) -L $(LIB) $(DEFINES) $(CFLAGS)


$(TEST_OUT) : $(TEST_OBJS)
	ar rcs $(TEST_BIN)/$(TEST_OUT).a $(TEST_OBJ)/*.o

$(TEST_OBJ)/%.o : $(TEST_SRC)/%.c
	$(CXX) -o $@ -c $< -I $(INCLUDE) -L $(TEST_LIB) $(DEFINES) $(CFLAGS)

$(TEST_OBJ)/%.o : $(TEST_SRC)/*/%.c
	$(CXX) -o $@ -c $< -I $(INCLUDE) -L $(TEST_LIB) $(DEFINES) $(CFLAGS)

$(TEST_OBJ)/%.o : $(TEST_SRC)/*/*/%.c
	$(CXX) -o $@ -c $< -I $(INCLUDE) -L $(TEST_LIB) $(DEFINES) $(CFLAGS)

info:
	@echo -----------------------------------------------------
	@echo info :                
	@echo 	compiler                     : $(CXX)
	@echo 	compiler standart version    : $(STD_VERSION)
	@echo 	flags                        : $(CFLAGS)
	@echo 	defines                      : $(DEFINES)
	@echo 	lib name                     : $(DLL)
	@echo 	libs directory               : $(LIB)
	@echo 	binary directory             : $(BIN)
	@echo 	source code directory        : $(SRC)
	@echo 	compiled object directory    : $(OBJ)
	@echo 	include directory            : $(INCLUDE)
	@echo -----------------------------------------------------