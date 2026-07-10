/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbichet <mbichet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/02 15:58:54 by mbichet           #+#    #+#             */
/*   Updated: 2026/07/10 16:28:37 by mbichet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	is_nuber(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if ('0' <= str[i] && str[i] <= '9')
			j++;
		i++;
	}
	return (i == j);
}

long long	get_current_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((long long) tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

int	mprintf(t_data *data, char *str, int id)
{
	long long	t;

	if (get_stop_flag(data) && strcmp(str, "burned out\n") != 0)
		return (0);
	pthread_mutex_lock(&data->printf_mutex);
	t = get_current_time() - data->start_time;
	printf("%lld %d %s", t, id, str);
	pthread_mutex_unlock(&data->printf_mutex);
	return (0);
}

int	get_stop_flag(t_data *data)
{
	int	val;

	pthread_mutex_lock(&data->state_mutex);
	val = data->stop_flag;
	pthread_mutex_unlock(&data->state_mutex);
	return (val);
}

void	set_stop_flag(t_data *data, int val)
{
	pthread_mutex_lock(&data->state_mutex);
	data->stop_flag = val;
	pthread_mutex_unlock(&data->state_mutex);
}
