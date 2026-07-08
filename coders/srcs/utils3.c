/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbichet <mbichet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/06 15:42:33 by mbichet           #+#    #+#             */
/*   Updated: 2026/07/08 13:10:46 by mbichet          ###   ########lyon.fr   */
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
