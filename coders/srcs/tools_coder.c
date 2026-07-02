/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_coder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbichet <mbichet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/30 12:51:49 by username          #+#    #+#             */
/*   Updated: 2026/06/30 13:19:18 by mbichet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	wait_for_action(t_coders *c, int mode)
{
	long long	time;
	long long	start;

	start = get_current_time();
	if (mode == 0)
	{
		mprintf(c->data, "is compiling\n", c->id);
		time = c->data->time_comp;
	}
	else if (mode == 1)
	{
		mprintf(c->data, "is debugging\n", c->id);
		time = c->data->time_debug;
	}
	else
	{
		mprintf(c->data, "is refactoring\n", c->id);
		time = c->data->time_refac;
	}
	while (get_current_time() - start < time && !c->data->stop_flag)
		usleep(10);
	return (1);
}

int	one_coder(t_coders *c)
{
	if (c->data->nb_coders == 1)
	{
		ask_dongle(c->dongle_l, c);
		while (!c->data->stop_flag)
			usleep(10);
		return (0);
	}
	return (1);
}

void	coders(t_coders *c)
{
	t_dongle *first;
	t_dongle *second;

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
	while (c->nb_comp > 0 && !c->data->stop_flag)
	{
		if (!ask_dongle(first, c))
			break ;
		mprintf(c->data, "has taken a dongle\n", c->id);
		if (!ask_dongle(second, c))
		{
			drop_dongle(first);
			break ;
		}
		mprintf(c->data, "has taken a dongle\n", c->id);
		c->last_compile_start = get_current_time();
		wait_for_action(c, 0);
		drop_dongle(c->dongle_r);
		drop_dongle(c->dongle_l);
		if (--c->nb_comp == 0)
		{
			c->finished = 1;
			break ;
		}
		wait_for_action(c, 1);
		wait_for_action(c, 2);
	}
}

void	*action_coders(void *arg)
{
	t_coders	*c;

	c = (t_coders *) arg;
	if (c->id % 2 == 0)
		usleep(10);
	if (!one_coder(c))
		return (NULL);
	coders(c);
	return (NULL);
}
