files := main.c
CFLAGS := -Wall -Werror -Wpedantic

all:
	gcc -g $(files) -o nauka $(CFLAGS)
