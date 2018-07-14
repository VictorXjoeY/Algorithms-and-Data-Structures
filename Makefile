# Victor Forbes - 9293394

all:
	gcc src/*.c -I includes -o main -g -Wall
run:
	./main
debug:
	valgrind -v --track-origins=yes --leak-check=full --show-leak-kinds=all ./main
