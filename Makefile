CC     ?= gcc
CFLAGS ?= -I. -std=c99 -Wall -Wextra -Wpedantic

EXAMPLES := \
	examples/assert \
	examples/test \
	examples/cli

TESTS := \
	tests/exam

.PHONY: all examples tests clean

all: examples tests

examples: $(EXAMPLES)

tests: $(TESTS)

examples/%: examples/%.c exam.h
	$(CC) $(CFLAGS) -o $@ $<

tests/%: tests/%.c exam.h
	$(CC) $(CFLAGS) -o $@ $<

clean:
	$(RM) $(EXAMPLES) $(TESTS)

