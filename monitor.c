#include "header.h"

int	check_death(t_coders *c, t_data *data, int i)
{
	long long	now;

	now = get_current_time();
	if (!c[i].finished && now - c[i].last_compile_start >= data->time_burn)
	{
		data->stop_flag = 1;
		mprintf(data, "burned out\n", c[i].id);
		return (1);
	}
	return (0);
}

void	*monitor_routine(void *arg)
{
	t_coders	*c;
	t_data		*d;
	int			i;
	int			done;

	c = (t_coders *)arg;
	d = c[0].data;
	while (!d->stop_flag)
	{
		i = -1;
		done = 1;
		while (++i < d->nb_coders)
		{
			if (!c[i].finished)
				done = 0;
			if (check_death(c, d, i))
				break ;
		}
		if (done || d->stop_flag)
			break ;
		i = -1;
		while (++i < d->nb_coders)
		{
			pthread_mutex_lock(&d->dongles[i].mutex);
			pthread_cond_broadcast(&d->dongles[i].cond);
			pthread_mutex_unlock(&d->dongles[i].mutex);
		}
		usleep(1000);
	}
	return (NULL);
}