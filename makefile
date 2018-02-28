CC = gcc -std=c99
CFLAGS = -g -fno-omit-frame-pointer -Wall -Wextra

.PHONY: all
all: rundfa
rundfa: rundfa.o dfaType.o table-hash.o
	$(CC) $(CFLAGS) -o $@ dfaType.o rundfa.o table-hash.o

rundfa.o: rundfa.c rundfa.h
	$(CC) $(CFLAGS) -c rundfa.c

dfaType.o: dfaType.c dfaType.h
	$(CC) $(CFLAGS) -c dfaType.c

table-hash.o: table-hash.c table.h
	$(CC) $(CFLAGS) -c table-hash.c

.PHONY: clean
clean:
	rm -fv *.o rundfa
