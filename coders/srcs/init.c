/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbichet <mbichet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/02 15:59:07 by mbichet           #+#    #+#             */
/*   Updated: 2026/07/06 10:19:15 by mbichet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	init_dongles(t_data *data)
{
	int	i;

	data->dongles = malloc(sizeof(t_dongle) * data->nb_coders);
	if (!data->dongles)
		return (0);
	i = -1;
	while (++i < data->nb_coders)
	{
		pthread_mutex_init(&data->dongles[i].mutex, NULL);
		pthread_cond_init(&data->dongles[i].cond, NULL);
		data->dongles[i].available = 1;
		data->dongles[i].last_release = 0;
		data->dongles[i].heap.size = 0;
		data->dongles[i].heap.scheduler = data->scheduler;
	}
	return (1);
}

int	init_coders(t_data *data, t_coders *coders)
{
	int	i;

	i = -1;
	while (++i < data->nb_coders)
	{
		coders[i].id = i + 1;
		coders[i].last_compile_start = data->start_time;
		pthread_mutex_init(&coders[i].coder_mutex, NULL);
		coders[i].nb_comp = data->nb_comp;
		coders[i].finished = (data->nb_comp == 0);
		coders[i].dongle_l = &data->dongles[i];
		coders[i].dongle_r = &data->dongles[(i + 1) % data->nb_coders];
		coders[i].data = data;
	}
	return (1);
}

int	init_all(t_data *data, t_coders **coders)
{
	data->start_time = get_current_time();
	data->stop_flag = 0;
	pthread_mutex_init(&data->printf_mutex, NULL);
	pthread_mutex_init(&data->state_mutex, NULL);
	if (!init_dongles(data))
		return (0);
	*coders = malloc(sizeof(t_coders) * data->nb_coders);
	if (!*coders)
		return (0);
	return (init_coders(data, *coders));
}
