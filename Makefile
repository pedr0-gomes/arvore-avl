CC     = gcc
CFLAGS = -Wall -Wextra

%.exe: %.c avl.c
	$(CC) $(CFLAGS) -o $@ $< avl.c

.PHONY: clean
clean:
	del *.exe