CC = gcc
CFLAGS = -Wall -Wextra -pthread -Iinclude -g

test_runner: src/allocator.c tests/main.c
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -f test_runner
