/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbichet <mbichet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/02 15:59:14 by mbichet           #+#    #+#             */
/*   Updated: 2026/07/08 14:29:58 by mbichet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_req
{
	int			id;
	long long	req_time;
	long long	deadline;
}	t_req;

typedef struct s_heap
{
	t_req	data[250];
	int		size;
	char	*scheduler;
}	t_heap;

typedef struct s_dongle
{
	pthread_mutex_t	mutex;
	pthread_cond_t	cond;
	int				available;
	long long		last_release;
	t_heap			heap;
}	t_dongle;

typedef struct s_data
{
	int				nb_coders;
	int				time_burn;
	int				time_comp;
	int				time_debug;
	int				time_refac;
	int				nb_comp;
	int				dongle_cooldown;
	char			*scheduler;
	long long		start_time;
	int				stop_flag;
	int				error;
	pthread_mutex_t	printf_mutex;
	pthread_mutex_t	state_mutex;
	t_dongle		*dongles;
}	t_data;

typedef struct s_coders
{
	int				id;
	long long		last_compile_start;
	pthread_mutex_t	coder_mutex;
	int				nb_comp;
	int				finished;
	t_dongle		*dongle_l;
	t_dongle		*dongle_r;
	t_data			*data;
}	t_coders;

long long	get_current_time(void);
void		choose_first(t_dongle *first, t_dongle *second, t_coders *c);
int			mprintf(t_data *data, char *str, int id);
int			get_stop_flag(t_data *data);
void		set_stop_flag(t_data *data, int val);
int			get_error(t_data *data);
void		set_error(t_data *data, int val);
long long	get_last_compile_start(t_coders *c);
void		set_last_compile_start(t_coders *c, long long val);
int			get_finished(t_coders *c);
void		set_finished(t_coders *c, int val);
int			parsing_error(int ac, char **av, t_data *data);
int			is_nuber(char *str);
void		push_heap(t_heap *h, t_req req);
void		pop_heap(t_heap *h);
int			ask_dongle(t_dongle *d, t_coders *c);
void		drop_dongle(t_dongle *d);
int			init_all(t_data *data, t_coders **coders);
int			free_all(t_coders *coders, t_data *data);
void		*action_coders(void *arg);
void		*monitor(void *arg);
int			check_dongle(t_dongle *first, t_dongle *second, t_coders *c);
int			refac_comp(t_coders *c);
int			wait_for_action(t_coders *c, int mode);
int			init_theard(t_data *data, t_coders **coders,
				pthread_t *monitor_th, pthread_t **th);

#endif