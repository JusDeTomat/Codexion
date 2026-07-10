/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbichet <mbichet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/06 15:42:33 by mbichet           #+#    #+#             */
/*   Updated: 2026/07/10 11:02:36 by mbichet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	check_dongle(t_dongle *first, t_dongle *second, t_coders *c)
{
	if (first == second)
		return (0);
	if (!ask_dongle(first, c))
		return (0);
	mprintf(c->data, "has taken a dongle\n", c->id);
	if (!ask_dongle(second, c))
	{
		drop_dongle(first);
		return (0);
	}
	mprintf(c->data, "has taken a dongle\n", c->id);
	return (1);
}

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
