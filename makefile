CC=gcc
EXEC=prog
SRC=$(wildcard *.c)
OBJ=$(SRC:.c=.o)

$(EXEC): $(OBJ)
	$(CC) -lncurses -o $(EXEC) $(OBJ) -Wall -Wextra -pedantic -std=c99

%.o: %.c
	$(CC) -o $@ -c $^

clean:
	rm $(EXEC) $(OBJ)
