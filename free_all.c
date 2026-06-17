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