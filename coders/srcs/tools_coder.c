/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_coder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbichet <mbichet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/02 15:58:45 by mbichet           #+#    #+#             */
/*   Updated: 2026/07/08 13:09:31 by mbichet          ###   ########lyon.fr   */
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
	while (get_current_time() - start < time && !get_stop_flag(c->data))
		usleep(10);
	return (1);
}

void	coders(t_coders *c)
{
	t_dongle	*first;
	t_dongle	*second;

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
	while (c->nb_comp > 0 && !get_stop_flag(c->data))
	{
		if (!check_dongle(first, second, c))
			break ;
		if (!refac_comp(c))
			break ;
	}
}

void	*action_coders(void *arg)
{
	t_coders	*c;

	c = (t_coders *) arg;
	if (c->id % 2 == 0)
		usleep(10);
	coders(c);
	return (NULL);
}
