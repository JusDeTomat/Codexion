# include "header.h"

int	init_normal(t_data *data, t_coders *coders, long long time, int i)
{	
	coders[i].time = time;
	coders[i].id = i + 1;
	coders[i].nb_comp = data->nb_comp;
	coders[i].time_comp = data->time_comp;
	coders[i].time_burn = data->time_burn;
	coders[i].time_debug = data->time_debug;
	coders[i].time_refac = data->time_refac;
	coders[i].global_data = data;
	return (1);
}

int	init_mutex(t_coders *coders, int i, pthread_mutex_t *pm, pthread_mutex_t *ld, t_data *data)
{
	coders[i].printf_mutex = pm;
	coders[i].mutex = malloc(sizeof(pthread_mutex_t));
	if (!coders[i].mutex)
		return (0);
	coders[i].dongle_r.mutex = &ld[i];
	coders[i].dongle_l.mutex = &ld[(i + 1) % data->nb_coders];
	pthread_mutex_init(coders[i].mutex, NULL);
	return (1);
}

int	alloc_scheduling(t_data *data)
{
	data->states = malloc(sizeof(t_state) * data->nb_coders);
	data->request_time = malloc(sizeof(long long) * data->nb_coders);
	data->deadlines = malloc(sizeof(long long) * data->nb_coders);
	data->cond_vars = malloc(sizeof(pthread_cond_t) * data->nb_coders);
	if (!data->states || !data->request_time || !data->deadlines || !data->cond_vars)
		return (0);
	return (1);
}

int	init_coders_loop(t_data *data, t_coders *coders, pthread_mutex_t *pm, pthread_mutex_t *ld)
{
	int	i;

	i = -1;
	while (++i < data->nb_coders)
	{
		data->states[i] = THINKING;
		data->request_time[i] = 0;
		data->deadlines[i] = 0;
		pthread_cond_init(&data->cond_vars[i], NULL);
		init_normal(data, coders, data->start_time, i);
		if (!init_mutex(coders, i, pm, ld, data))
			return (0);
	}
	return (1);
}

int init_all(t_data *data, t_coders *coders)
{
	int				i;
	pthread_mutex_t	*lst_dongle;
	pthread_mutex_t *printf_mutex;

	data->start_time = get_current_time();
	printf_mutex = malloc(sizeof(pthread_mutex_t));
	lst_dongle = malloc(sizeof(pthread_mutex_t) * data->nb_coders);
	if (!printf_mutex || !lst_dongle || !alloc_scheduling(data))
		return (0);
	pthread_mutex_init(printf_mutex, NULL);
	i = -1;
	while (++i < data->nb_coders)
		pthread_mutex_init(&lst_dongle[i], NULL);
	pthread_mutex_init(&data->arbiter_mutex, NULL);
	return (init_coders_loop(data, coders, printf_mutex, lst_dongle));
}