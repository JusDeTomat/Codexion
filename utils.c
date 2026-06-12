/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbichet <mbichet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/20 08:36:00 by mbichet           #+#    #+#             */
/*   Updated: 2026/06/12 14:38:03 by mbichet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

# include "header.h"

int	is_nuber(char *str)
{
	unsigned long i;
	unsigned long j;

	i = 0;
	j = 0;
	while (i < strlen(str))
	{
		if ('0' <= str[i] && str[i] <= '9')
			j++;
		i++;		
	}
	return (i == j);
}

int mprintf(pthread_mutex_t *mutex, char * str, long long time, int id)
{
	pthread_mutex_lock(mutex);
	printf("%lld %d %s",time , id, str);
	pthread_mutex_unlock(mutex);
	return (0);
}
