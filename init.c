/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbichet <mbichet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 11:37:02 by mbichet           #+#    #+#             */
/*   Updated: 2026/06/12 14:39:04 by mbichet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

# include "header.h"

int	init_normal(t_data *data, t_coders *coders,long long time, int i)
{	
	coders[i].time = time;
	coders[i].id = i + 1;
	coders[i].nb_comp = data->nb_comp;
	coders[i].time_comp = data->time_comp;
	coders[i].time_burn = data->time_burn;
	coders[i].time_debug = data->time_debug;
	coders[i].time_refac = data->time_refac;
	coders[i].dongle_r.available = TRUE;
	coders[i].dongle_l.available = TRUE;
	return (1);
}

int	init_mutex(t_coders *coders, int i, pthread_mutex_t *printf_mutex, pthread_mutex_t	*lst_dongle, t_data *data)
{
	coders[i].printf_mutex = printf_mutex;
	coders[i].mutex = malloc(sizeof(pthread_mutex_t));
	coders[i].dongle_r.mutex = &lst_dongle[i];
    coders[i].dongle_l.mutex = &lst_dongle[(i + 1) % data->nb_coders];
	if (!coders->mutex || !coders->dongle_l.mutex || !coders->dongle_r.mutex)
		return (0);
	pthread_mutex_init(coders[i].mutex, NULL);
    pthread_mutex_init(coders[i].dongle_r.mutex, NULL);
    pthread_mutex_init(coders[i].dongle_l.mutex, NULL);
	return (1);
}

int init_all(t_data *data, t_coders *coders)
{
	int				i;
	struct timeval	tv;
	pthread_mutex_t	*lst_dongle;
	pthread_mutex_t *printf_mutex;

	i = -1;
	gettimeofday(&tv, NULL);
	printf_mutex = malloc(sizeof(pthread_mutex_t));
	lst_dongle = malloc(sizeof(pthread_mutex_t) * data->nb_coders);
	pthread_mutex_init(printf_mutex, NULL);
	if(!printf_mutex || !lst_dongle)
		return (0);
	while (++i < data->nb_coders)
	{
		init_normal(data, coders, (long long)tv.tv_sec * 1000 + tv.tv_usec / 1000, i);
		if(!init_mutex(coders, i, printf_mutex, lst_dongle, data))
			return (0);
	}
	return (1);
}
