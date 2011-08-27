all:
	rm run
	gcc -g -lpthread parser.c -o run
