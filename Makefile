PROJECT_NAME := nauka
files := main.c
CFLAGS := -Wall -Werror -Wpedantic -g -Os

MAKEFLAGS += -rR

all: $(PROJECT_NAME)

$(PROJECT_NAME):
	gcc $(files) -o nauka $(CFLAGS)

run: $(PROJECT_NAME)
	./$(PROJECT_NAME)
