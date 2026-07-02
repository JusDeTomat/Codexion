NAME			= codexion
CFLAGS			= -Wall -Wextra -Werror -pthread
INCLUDE			= -Iincludes
OBJ_DIR			= obj
C_FILES			= srcs/dongle.c \
				  srcs/utils.c \
				  srcs/parsing.c \
				  srcs/free_all.c \
				  srcs/heap.c \
				  srcs/init.c \
				  srcs/main.c \
				  srcs/monitor.c \
				  srcs/tools_coder.c \


O_FILES			= $(patsubst %.c,$(OBJ_DIR)/%.o,$(C_FILES))

D_FILES			= $(O_FILES:.o=.d)

all: $(OBJ_DIR) $(NAME)


$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(NAME): $(O_FILES)
	$(CC) $(INCLUDE) $(CFLAGS) $^ -o $@

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(INCLUDE) $(CFLAGS) -MMD -MP -c $< -o $@

clean:
	$(RM) -rf $(OBJ_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all re clean fclean

-include $(D_FILES)