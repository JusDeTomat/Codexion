/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbichet <mbichet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/10 11:04:11 by mbichet           #+#    #+#             */
/*   Updated: 2026/07/10 11:04:22 by mbichet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	get_error(t_data *data)
{
	int	val;

	pthread_mutex_lock(&data->state_mutex);
	val = data->error;
	pthread_mutex_unlock(&data->state_mutex);
	return (val);
}

void	set_error(t_data *data, int val)
{
	pthread_mutex_lock(&data->state_mutex);
	data->error = val;
	pthread_mutex_unlock(&data->state_mutex);
}
