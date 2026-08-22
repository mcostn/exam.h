CC := gcc
CFLAGS := -I. -std=c89 -Wall -Wextra -Wpedantic

examples:
	$(CC) $(CFLAGS) -o examples/assert examples/assert.c

clean:
	rm examples/assert

.PHONY: examples clean
