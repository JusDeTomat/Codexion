/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbichet <mbichet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/02 15:58:33 by mbichet           #+#    #+#             */
/*   Updated: 2026/07/08 14:18:47 by mbichet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	check_death(t_coders *c, t_data *data, int i)
{
	long long	now;

	now = get_current_time();
	if (!get_finished(&c[i])
		&& now - get_last_compile_start(&c[i]) >= data->time_burn)
	{
		set_stop_flag(data, 1);
		mprintf(data, "burned out\n", c[i].id);
		return (1);
	}
	return (0);
}

void	check_coder(t_data *d)
{
	int	i;

	i = -1;
	while (++i < d->nb_coders)
	{
		pthread_mutex_lock(&d->dongles[i].mutex);
		pthread_cond_broadcast(&d->dongles[i].cond);
		pthread_mutex_unlock(&d->dongles[i].mutex);
	}
}

void	*monitor(void *arg)
{
	t_coders	*c;
	t_data		*d;
	int			i;
	int			done;

	c = (t_coders *) arg;
	d = c[0].data;
	while (!get_stop_flag(d))
	{
		usleep(100);
		i = -1;
		done = 1;
		while (++i < d->nb_coders)
		{
			if (!get_finished(&c[i]))
				done = 0;
			if (check_death(c, d, i))
				break ;
		}
		check_coder(d);
		if (done || get_stop_flag(d))
			break ;
	}
	check_coder(d);
	return (NULL);
}
