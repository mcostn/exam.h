CC := gcc
CFLAGS := -I. -std=c99 -Wall -Wextra -Wpedantic
LDFLAGS := -pthread

examples:
	$(CC) $(CFLAGS) $(LDFLAGS) -o examples/assert examples/assert.c
	$(CC) $(CFLAGS) $(LDFLAGS) -o examples/test examples/test.c
	$(CC) $(CFLAGS) $(LDFLAGS) -o examples/cli examples/cli.c

clean:
	rm examples/assert examples/test examples/cli

.PHONY: examples clean
