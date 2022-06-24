CC = clang

SRC  = $(shell find src -name "*.c")
OBJ  = $(SRC:.c=.o)
BIN = build

all: build

run:
	$(CC) test.c -o test -ldebug -Isrc
	./test

build: $(OBJ)
	$(CC) -fPIC -rdynamic -shared -Lstatic -o $(BIN)/libdebug.so $(OBJ)

clean:
	rm $(BIN)/* $(OBJ) test libdebug.so

%.o: %.c
	$(CC) -ggdb -o $@ -c $< $(CCFLAGS)
