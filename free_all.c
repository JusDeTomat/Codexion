#include "header.h"

int	free_all(t_coders *coders, t_data *data)
{
	int i;

	i = -1;
	while (++i < data->nb_coders - 1)
	{
		free(coders[i].mutex);
		//free(coders->dongle_r.mutex);
	}
	free(coders[i + 1].mutex);
	free(coders->printf_mutex);
	free(coders);
	free(data);
	return (1);
}
