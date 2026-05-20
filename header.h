# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <stdlib.h>

typedef struct{
	int		nb_coders;
	int		time_burn;
	int		time_comp;
	int		time_debug;
	int		time_refac;
	int		nb_comp;
	int		dongle_cooldown;
	char 	*scheduler;
} Data;

int	is_nuber(char *str);
int parsing_error(int ac, char **av, Data *data);
int	parsing(int ac, char **av, Data *data);
