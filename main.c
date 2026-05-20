/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbichet <mbichet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/20 12:51:05 by mbichet           #+#    #+#             */
/*   Updated: 2026/05/20 12:53:12 by mbichet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

# include "header.h"

int	main(int ac, char **av)
{
	int	a;
	Data *data;
	
	data = malloc(sizeof(Data));
	if (parsing_error(ac, av, data))
		return (0);
	return (0);
}
