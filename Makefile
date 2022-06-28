CC = clang

SRC  = $(shell find src -name "*.c")
OBJ  = $(SRC:.c=.o)
BIN = build

all: build

# run tests
run:
	$(MAKE) -C tests

build: $(OBJ)
	$(CC) -fPIC -rdynamic -shared -Lstatic -o $(BIN)/libdebug.so $(OBJ)

clean:
	rm $(BIN)/* $(OBJ) test

%.o: %.c
	$(CC) -Wall -fPIC -o $@ -c $< $(CCFLAGS)
