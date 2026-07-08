/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbichet <mbichet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/06 10:22:55 by mbichet           #+#    #+#             */
/*   Updated: 2026/07/06 16:23:56 by mbichet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	choose_first(t_dongle *first, t_dongle *second, t_coders *c)
{
	if (c->id % 2 == 0)
	{
		first = c->dongle_r;
		second = c->dongle_l;
	}
	else
	{
		first = c->dongle_l;
		second = c->dongle_r;
	}
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
