all: main.c
	clang -Wall -Wextra -pedantic -o main main.c

clean:
	rm -f main
