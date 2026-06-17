# include "header.h"

int	start_simulation(t_data *data, t_coders *coders, pthread_t *th)
{
	int	a;

	if (!init_all(data, coders))
		return (1);
	a = -1;
	while (++a < data->nb_coders)
		pthread_create(&th[a], NULL, action_coders, &coders[a]);
	a = 0;
	while (a < data->nb_coders)
		pthread_join(th[a], NULL);
	return (0);
}

int	main(int ac, char **av)
{
	t_data		*data;
	t_coders	*coders;
	pthread_t	*th;
	
	data = malloc(sizeof(t_data));
	if (!parsing_error(ac, av, data))
	{
		free(data);
		return (1);
	}
	coders = malloc(sizeof(t_coders) * data->nb_coders);
	th = malloc(sizeof(pthread_t) * data->nb_coders);
	if (!coders || !th)
	{
		free(data);
		free(coders);
		free(th);
		return (1);
	}
	start_simulation(data, coders, th);
	free_all(coders, data);
	free(th);
	return (0);
}