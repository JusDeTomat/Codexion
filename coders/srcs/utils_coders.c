/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbichet <mbichet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/06 10:22:55 by mbichet           #+#    #+#             */
/*   Updated: 2026/07/10 11:02:40 by mbichet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	refac_comp(t_coders *c)
{
	set_last_compile_start(c, get_current_time());
	wait_for_action(c, 0);
	drop_dongle(c->dongle_r);
	drop_dongle(c->dongle_l);
	if (--c->nb_comp == 0)
	{
		set_finished(c, 1);
		return (0);
	}
	wait_for_action(c, 1);
	wait_for_action(c, 2);
	return (1);
}

long long	get_last_compile_start(t_coders *c)
{
	long long	val;

	pthread_mutex_lock(&c->coder_mutex);
	val = c->last_compile_start;
	pthread_mutex_unlock(&c->coder_mutex);
	return (val);
}

void	set_last_compile_start(t_coders *c, long long val)
{
	pthread_mutex_lock(&c->coder_mutex);
	c->last_compile_start = val;
	pthread_mutex_unlock(&c->coder_mutex);
}

int	get_finished(t_coders *c)
{
	int	val;

	pthread_mutex_lock(&c->coder_mutex);
	val = c->finished;
	pthread_mutex_unlock(&c->coder_mutex);
	return (val);
}

void	set_finished(t_coders *c, int val)
{
	pthread_mutex_lock(&c->coder_mutex);
	c->finished = val;
	pthread_mutex_unlock(&c->coder_mutex);
}
