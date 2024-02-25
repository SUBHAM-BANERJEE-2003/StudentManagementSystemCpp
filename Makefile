CC = clang++
CFLAGS = -c -Wall

output: main.o
	$(CC) main.o -o main -lmysqlclient

main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp

run: output
	./main

clean:
	rm -f *.o main
