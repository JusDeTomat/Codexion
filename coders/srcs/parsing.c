/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbichet <mbichet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/02 15:59:00 by mbichet           #+#    #+#             */
/*   Updated: 2026/07/10 16:31:51 by mbichet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	parsing(int ac, char **av, t_data *data)
{
	int	i;

	i = 0;
	if (ac != 9)
		return (0);
	while (++i < ac - 1)
	{
		if (((1 <= i && i <= 7) && !is_nuber(av[i]))
			|| atoi(av[i]) <= 0 || strlen(av[i]) >= 11)
			return (2);
	}
	if (i == 8 && strcmp(av[i], "fifo") && strcmp(av[i], "edf"))
		return (2);
	data->nb_coders = atoi(av[1]);
	data->time_burn = atoi(av[2]);
	data->time_comp = atoi(av[3]);
	data->time_debug = atoi(av[4]);
	data->time_refac = atoi(av[5]);
	data->nb_comp = atoi(av[6]);
	data->dongle_cooldown = atoi(av[7]);
	data->scheduler = av[8];
	return (1);
}

int	parsing_error(int ac, char **av, t_data *data)
{
	int	res;

	res = parsing(ac, av, data);
	if (res == 1)
		return (1);
	else if (res == 0)
		printf("you need exatly 8 argument and you have %d \n", ac - 1);
	else if (res == 2)
		printf("the parmeter type paternal: '(strictly positive int) * 7 \
(fifo or edf(str)) ' be careful overflow\n");
	return (0);
}
