CC = clang

SRC  = test0.c test1.c
OBJ  = $(SRC:.c=.o)
NAME  = $(SRC:.c=)
BIN = build

all: build run

run:
	for i in {0..1} ; do	\
  		echo $$i th program;			\
	    ./$(BIN)/test$$i ;	\
	done

build: $(BIN) $(NAME)

clean:
	rm $(BIN)/* $(OBJ)

%: %.c
	$(CC) -Wall -ldebug -lSDL2 $< -o $(BIN)/$@

$(BIN):
	mkdir -p $(BIN)