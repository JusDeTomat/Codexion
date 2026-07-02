/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   utils.c                                           :+:      :+:    :+:    */
/*                                                   +:+ +:+         +:+      */
/*   By: username <username@student.42tokyo.jp>    #+#  +:+       +#+         */
/*                                               +#+#+#+#+#+   +#+            */
/*   Created: 2026/06/30 12:57:10 by username         #+#    #+#              */
/*   Updated: 2026/06/30 12:57:10 by username        ###   ########.fr        */
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

	if (data->stop_flag && strcmp(str, "burned out\n") != 0)
		return (0);
	pthread_mutex_lock(&data->printf_mutex);
	t = get_current_time() - data->start_time;
	printf("%lld %d %s", t, id, str);
	pthread_mutex_unlock(&data->printf_mutex);
	return (0);
}
