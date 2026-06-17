#include "header.h"

void	demander_dongle(t_dongle *d, t_coders *c)
{
	t_req		req;
	long long	now;

	req.id = c->id;
	req.req_time = get_current_time();
	req.deadline = c->last_compile_start + c->data->time_burn;
	pthread_mutex_lock(&d->mutex);
	push_heap(&d->heap, req);
	while (!c->data->stop_flag)
	{
		now = get_current_time();
		if (d->available && now - d->last_release >= c->data->dongle_cooldown)
		{
			if (d->heap.size > 0 && d->heap.data[0].id == c->id)
			{
				pop_heap(&d->heap);
				d->available = 0;
				break ;
			}
		}
		pthread_cond_wait(&d->cond, &d->mutex);
	}
	pthread_mutex_unlock(&d->mutex);
}

void	relacher_dongle(t_dongle *d)
{
	pthread_mutex_lock(&d->mutex);
	d->available = 1;
	d->last_release = get_current_time();
	pthread_cond_broadcast(&d->cond);
	pthread_mutex_unlock(&d->mutex);
}