/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbichet <mbichet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/02 16:32:44 by mbichet           #+#    #+#             */
/*   Updated: 2026/07/10 16:31:06 by mbichet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	start_simulation(t_data *data, t_coders **coders, pthread_t **th)
{
	pthread_t	monitor_th;
	int			a;
	long long	now;

	monitor_th = 0;
	if (!init_all(data, coders))
		return (1);
	*th = malloc(sizeof(pthread_t) * data->nb_coders);
	if (!*th)
		return (1);
	now = get_current_time();
	data->start_time = now;
	a = -1;
	while (++a < data->nb_coders)
		(*coders)[a].last_compile_start = now;
	if (!init_theard(data, coders, &monitor_th, th))
		return (0);
	a = -1;
	while (++a < data->nb_coders)
		pthread_join((*th)[a], NULL);
	pthread_join(monitor_th, NULL);
	return (0);
}

int	main(int ac, char **av)
{
	t_data		data;
	t_coders	*coders;
	pthread_t	*th;

	coders = NULL;
	th = NULL;
	if (!parsing_error(ac, av, &data))
		return (1);
	start_simulation(&data, &coders, &th);
	free_all(coders, &data);
	free(th);
	return (0);
}
