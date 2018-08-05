CC=g++
CFLAGS=-g --std=c++11

LIB= ./lib/ -lpthread

run: run.o
	$(CC) $(CFLAGS) $^ -o $@ -L$(LIB)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $^ -o $@ -L$(LIB)

clean:
	rm -f *.o run
