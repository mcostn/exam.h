CC := gcc
CFLAGS := -I. -std=c99 -Wall -Wextra -Wpedantic

examples:
	$(CC) $(CFLAGS) -o examples/assert examples/assert.c
	$(CC) $(CFLAGS) -o examples/test examples/test.c
	$(CC) $(CFLAGS) -o examples/cli examples/cli.c

clean:
	rm examples/assert examples/test examples/cli

.PHONY: examples clean
