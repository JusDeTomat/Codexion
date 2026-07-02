/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbichet <mbichet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/30 12:46:03 by username          #+#    #+#             */
/*   Updated: 2026/06/30 16:03:54 by mbichet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	start_simulation(t_data *data, t_coders *coders, pthread_t *th)
{
	pthread_t	monitor_th;
	int			a;
	long long	now;

	if (!init_all(data, &coders))
		return (1);
	now = get_current_time();
	data->start_time = now;
	a = -1;
	while (++a < data->nb_coders)
		coders[a].last_compile_start = now;
	a = -1;
	while (++a < data->nb_coders)
		pthread_create(&th[a], NULL, action_coders, &coders[a]);
	pthread_create(&monitor_th, NULL, monitor, coders);
	a = -1;
	while (++a < data->nb_coders)
		pthread_join(th[a], NULL);
	pthread_join(monitor_th, NULL);
	free(monitor_th);
	return (0);
}

int	main(int ac, char **av)
{
	t_data		*data;
	t_coders	*coders;
	pthread_t	*th;

	data = malloc(sizeof(t_data));
	if (!parsing_error(ac, av, data))
	{
		free(data);
		return (1);
	}
	coders = malloc(sizeof(t_coders) * data->nb_coders);
	th = malloc(sizeof(pthread_t) * data->nb_coders);
	if (!coders || !th)
	{
		free(data);
		free(coders);
		free(th);
		return (1);
	}
	start_simulation(data, coders, th);
	free_all(coders, data);
	free(th);
	return (0);
}
