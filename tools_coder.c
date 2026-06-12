/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_coder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbichet <mbichet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 15:22:40 by mbichet           #+#    #+#             */
/*   Updated: 2026/06/12 14:38:10 by mbichet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

# include "header.h"

int	get_mode(t_coders *coders, int time, int mode)
{
	long long time_now;
	struct timeval tv;

	gettimeofday(&tv, NULL);
	time_now = ((long long)tv.tv_sec * 1000 + tv.tv_usec / 1000) - coders->time;
	if (mode == 0)
	{
		mprintf(coders->printf_mutex, "is compiling\n", time_now, coders->id);
		time = coders->time_comp;
	}
	if (mode == 1)
	{
		mprintf(coders->printf_mutex, "is debugging\n", time_now, coders->id);
		time = coders->time_debug;
	}
	if (mode == 2)
	{
		mprintf(coders->printf_mutex, "is refactoring\n", time_now, coders->id);
		time = coders->time_refac;
	}
	return (time);
}

int wait_for_action(t_coders *coders, int mode)
{
	int i;
	int	time;
	
	i = 0;
	time = 0;
	time = get_mode(coders, time, mode);
	while(i < 10)
	{
		usleep((float)((time * 1000)) / 10);
		i++;
	}
	return (1);
}

void *action_coders(void *arg)
{
    t_coders *coders;
	int i;

	i = 0;
	coders = (t_coders *)arg;
	while (i < coders->nb_comp)
	{
		pthread_mutex_lock(coders->dongle_r.mutex);
		pthread_mutex_lock(coders->dongle_l.mutex);
		wait_for_action(coders, 0);
		pthread_mutex_unlock(coders->dongle_r.mutex);
		pthread_mutex_unlock(coders->dongle_l.mutex);
		wait_for_action(coders, 1);
		wait_for_action(coders, 2);
		i++;
	}
	return NULL;
}
