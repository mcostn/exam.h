CC := gcc
CFLAGS := -I. -std=c89 -Wall -Wextra -Wpedantic

examples:
	$(CC) $(CFLAGS) -o examples/assert examples/assert.c
	$(CC) $(CFLAGS) -o examples/test examples/test.c

clean:
	rm examples/assert examples/test

.PHONY: examples clean
