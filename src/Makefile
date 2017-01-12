EXEC=ex_projet2
SRC=$(wildcard *.c) $(wildcard */*.c)
OBJ=$(SRC:.c=.o)

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

main.o: parser.h

%.o: %.c FORCE
	$(CC) -o $@ -c $< $(CFLAGS)

.PHONY: clean

clall: clean

clean:
	-rm *.o

test:
	echo “Tests OK”
