#ifndef HEADER_H
# define HEADER_H

# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef enum e_bool {
	FALSE,
	TRUE
} bool;

typedef enum e_state {
	THINKING,
	HUNGRY,
	COMPILING
} t_state;

typedef struct s_data {
	int				nb_coders;
	int				time_burn;
	int				time_comp;
	int				time_debug;
	int				time_refac;
	int				nb_comp;
	int				dongle_cooldown;
	char 			*scheduler;
	pthread_mutex_t	arbiter_mutex;
	t_state			*states;
	long long		*request_time;
	long long		*deadlines;
	pthread_cond_t	*cond_vars;
	long long		start_time;
} t_data;

typedef struct s_dongle
{
	pthread_mutex_t *mutex;
	bool 			available;
} t_dongle;

typedef struct s_coders {
	int				id;
	long long		time;
	int				nb_comp;
	int				time_burn;
	int				time_comp;
	int				time_debug;
	int				time_refac;
	pthread_mutex_t *printf_mutex;
	pthread_mutex_t *mutex;
	t_dongle 		dongle_r;
	t_dongle 		dongle_l;
	t_data			*global_data;
} t_coders;

int			is_nuber(char *str);
int			parsing_error(int ac, char **av, t_data *data);
int			parsing(int ac, char **av, t_data *data);
int			init_all(t_data *data, t_coders *coders);
int			free_all(t_coders *coders, t_data *data);
void		*action_coders(void *arg);
int			mprintf(pthread_mutex_t *mutex, char * str, long long time, int id);
long long	get_current_time(void);
int			alloc_scheduling(t_data *data);
int			init_coders_loop(t_data *d, t_coders *c, pthread_mutex_t *p, pthread_mutex_t *l);
int			check_fifo_edf(t_coders *coder, t_data *data, int l, int r);
void		free_dongles_and_printf(t_coders *coders, t_data *data);

#endif