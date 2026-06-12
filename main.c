/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbichet <mbichet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/20 12:51:05 by mbichet           #+#    #+#             */
/*   Updated: 2026/06/10 16:06:20 by mbichet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

# include "header.h"

int	main(int ac, char **av)
{
	int			a;
	t_data		*data;
	t_coders	*coders;
	pthread_t	th[106];
	
	a = -1;
	data = malloc(sizeof(t_data));
	if (!parsing_error(ac, av, data))
	{
		free(data);
		return (1);
	}
	coders = malloc(sizeof(t_coders) * data->nb_coders);
	init_all(data, coders);
	while (++a < data->nb_coders)
		pthread_create(&th[a], NULL, action_coders, &coders[a]);
	a = 0;
	while (a < data->nb_coders)
	 	a += pthread_join(th[a], NULL);
	free_all(coders, data);
	return (0);
}
