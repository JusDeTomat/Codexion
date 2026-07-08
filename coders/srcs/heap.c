/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbichet <mbichet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/02 15:58:15 by mbichet           #+#    #+#             */
/*   Updated: 2026/07/06 10:19:02 by mbichet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	cmp_req(t_req a, t_req b, char *sched)
{
	if (strcmp(sched, "fifo") == 0)
	{
		if (a.req_time != b.req_time)
			return (a.req_time < b.req_time);
		return (a.id < b.id);
	}
	if (a.deadline != b.deadline)
		return (a.deadline < b.deadline);
	if (a.req_time != b.req_time)
		return (a.req_time < b.req_time);
	return (a.id < b.id);
}

void	push_heap(t_heap *h, t_req req)
{
	int		i;
	t_req	tmp;

	h->data[h->size] = req;
	i = h->size++;
	while (i > 0 && cmp_req(h->data[i], h->data[(i - 1) / 2], h->scheduler))
	{
		tmp = h->data[i];
		h->data[i] = h->data[(i - 1) / 2];
		h->data[(i - 1) / 2] = tmp;
		i = (i - 1) / 2;
	}
}

void	heapify(t_heap *h, int i)
{
	int		s;
	int		l;
	int		r;
	t_req	tmp;

	s = i;
	l = 2 * i + 1;
	r = 2 * i + 2;
	if (l < h->size && cmp_req(h->data[l], h->data[s], h->scheduler))
		s = l;
	if (r < h->size && cmp_req(h->data[r], h->data[s], h->scheduler))
		s = r;
	if (s != i)
	{
		tmp = h->data[i];
		h->data[i] = h->data[s];
		h->data[s] = tmp;
		heapify(h, s);
	}
}

void	pop_heap(t_heap *h)
{
	if (h->size == 0)
		return ;
	h->data[0] = h->data[h->size - 1];
	h->size--;
	heapify(h, 0);
}
