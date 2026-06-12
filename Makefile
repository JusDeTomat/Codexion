CC		= cc -Wall -Wextra -Werror
SRC		= main.c \
		  parsing.c \
		  header.h \
		  free_all.c \
		  init.c \
		  utils.c \
		  tools_coder.c \

run:
	$(CC) $(SRC)
	./a.out 6 10 10 10 10 10 10 fifo

debug:
	$(CC) $(SRC)
	valgrind ./a.out 6 10 20 10 10 10 10 fifo