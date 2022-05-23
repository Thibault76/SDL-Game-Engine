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

test: test/test.exe

test/test.exe : test/%.c
	gcc test/*.c -I$(INCLUDE) -o test/test.exe -L $(BIN)/ -lEngine -lmingw32

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