CFLAGS=-ggdb3 -Wall -Werror -pedantic -std=gnu99

test-future: deck.o cards.o eval.o test-future.o future.o
	gcc -o $@ deck.o cards.o eval.o test-future.o future.o

test-input: deck.o cards.o eval.o test-input.o future.o input.o
	gcc -o $@ deck.o cards.o eval.o test-input.o future.o input.o

.PHONY: clean
clean:
	rm -rf test-input test-future *.o
