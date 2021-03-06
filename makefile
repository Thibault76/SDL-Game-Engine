# project
VERSION = 0.1.0

# compiler
CXX = gcc
LIBSFLAGS = -lmingw32 -lSDL2main -lSDL2 -lSDL2_mixer
CFLAGS =
DEFINES =
INCLUDE = include/

# directories
BIN = out
SRC = src
OBJ = .obj
LIB = libs
OUT = engine

# source files
SRCS = $(wildcard $(SRC)/*.c) $(wildcard $(SRC)/**/*.c) $(wildcard $(SRC)/**/**/*.c)
OBJS := $(patsubst %.c, $(OBJ)/%.o, $(notdir $(SRCS)))

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
	$(CXX) $(OBJ)/*.o -I $(INCLUDE) -L $(LIB) -o $(BIN)\$(OUT) $(CFLAGS) $(DEFINES) $(LIBSFLAGS)

$(OBJ)/%.o : $(SRC)/%.c
	$(CXX) -o $@ -c $< -I $(INCLUDE) -L $(LIB) $(DEFINES) $(CFLAGS) -L $(LIB) $(LIBSFLAGS)

$(OBJ)/%.o : $(SRC)/*/%.c
	$(CXX) -o $@ -c $< -I $(INCLUDE) -L $(LIB) $(DEFINES) $(CFLAGS) -L $(LIB) $(LIBSFLAGS)

$(OBJ)/%.o : $(SRC)/*/*/%.c
	$(CXX) -o $@ -c $< -I $(INCLUDE) -L $(LIB) $(DEFINES) $(CFLAGS) -L $(LIB) $(LIBSFLAGS)


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