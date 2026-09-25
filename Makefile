CC     ?= gcc
CFLAGS ?= -I. -std=c99 -Wall -Wextra -Wpedantic

EXAMPLES := \
	examples/01_basic \
	examples/02_cli \
	examples/03_manual \
	examples/04_callbacks \
	examples/05_long_names

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

