PROJECT_NAME := nauka
files := main.c
CFLAGS := -Wall -Werror -Wpedantic -g -Os

MAKEFLAGS += -rR

all: $(PROJECT_NAME)

$(PROJECT_NAME): FORCE
	gcc $(files) -o nauka $(CFLAGS)

run: $(PROJECT_NAME)
	clear
	./$(PROJECT_NAME)

FORCE: ;
