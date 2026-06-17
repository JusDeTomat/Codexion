CC		= cc -Wall -Wextra -Werror -pthread
SRC		= main.c \
		  parsing.c \
		  header.h \
		  free_all.c \
		  init.c \
		  utils.c \
		  tools_coder.c \

run:
	$(CC) *.c
	./a.out 6 1000 100 100 100 10 100 fifo

debug:
	$(CC) $(SRC)
	valgrind ./a.out 6 10 20 10 10 10 10 fifo