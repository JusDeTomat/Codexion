/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbichet <mbichet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/30 12:41:28 by username          #+#    #+#             */
/*   Updated: 2026/06/30 13:20:33 by mbichet          ###   ########lyon.fr   */
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
	pthread_mutex_t	printf_mutex;
	t_dongle		*dongles;
}	t_data;

typedef struct s_coders
{
	int			id;
	long long	last_compile_start;
	int			nb_comp;
	int			finished;
	t_dongle	*dongle_l;
	t_dongle	*dongle_r;
	t_data		*data;
}	t_coders;

long long	get_current_time(void);
int			mprintf(t_data *data, char *str, int id);
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

#endif
