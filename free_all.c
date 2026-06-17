#include "header.h"

void	free_dongles_and_printf(t_coders *coders, t_data *data)
{
	int i;

	if (data->nb_coders > 0)
	{
		if (coders[0].printf_mutex)
		{
			pthread_mutex_destroy(coders[0].printf_mutex);
			free(coders[0].printf_mutex);
		}
		if (coders[0].dongle_r.mutex)
		{
			i = -1;
			while (++i < data->nb_coders)
				pthread_mutex_destroy(&coders[0].dongle_r.mutex[i]);
			free(coders[0].dongle_r.mutex);
		}
	}
}

int	free_all(t_coders *coders, t_data *data)
{
	int i;

	free_dongles_and_printf(coders, data);
	i = -1;
	while (++i < data->nb_coders)
	{
		if (coders[i].mutex)
		{
			pthread_mutex_destroy(coders[i].mutex);
			free(coders[i].mutex);
		}
		pthread_cond_destroy(&data->cond_vars[i]);
	}
	pthread_mutex_destroy(&data->arbiter_mutex);
	free(data->states);
	free(data->request_time);
	free(data->deadlines);
	free(data->cond_vars);
	free(coders);
	free(data);
	return (1);
}