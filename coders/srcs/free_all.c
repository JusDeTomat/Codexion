/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbichet <mbichet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/30 12:41:14 by mbichet           #+#    #+#             */
/*   Updated: 2026/06/30 12:41:18 by mbichet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	free_all(t_coders *coders, t_data *data)
{
	int	i;

	i = -1;
	if (data->dongles)
	{
		while (++i < data->nb_coders)
		{
			pthread_mutex_destroy(&data->dongles[i].mutex);
			pthread_cond_destroy(&data->dongles[i].cond);
		}
		free(data->dongles);
	}
	pthread_mutex_destroy(&data->printf_mutex);
	free(coders);
	free(data);
	return (1);
}
