# include "header.h"

int	get_mode(t_coders *coders, int time, int mode)
{
	long long time_now;

	time_now = get_current_time() - coders->time;
	if (mode == 0)
	{
		mprintf(coders->printf_mutex, "is compiling\n", time_now, coders->id);
		time = coders->time_comp;
	}
	else if (mode == 1)
	{
		mprintf(coders->printf_mutex, "is debugging\n", time_now, coders->id);
		time = coders->time_debug;
	}
	else if (mode == 2)
	{
		mprintf(coders->printf_mutex, "is refactoring\n", time_now, coders->id);
		time = coders->time_refac;
	}
	return (time);
}

int wait_for_action(t_coders *coders, int mode)
{
	int i;
	int	time;
	
	i = 0;
	time = get_mode(coders, 0, mode);
	while(i < 10)
	{
		usleep((float)((time * 1000)) / 10);
		i++;
	}
	return (1);
}

int check_fifo_edf(t_coders *coder, t_data *data, int l, int r)
{
	int id = coder->id - 1;

	if (strcmp(data->scheduler, "fifo") == 0)
	{
		if (data->states[l] == HUNGRY && data->request_time[l] < data->request_time[id])
			return (0);
		if (data->states[r] == HUNGRY && data->request_time[r] < data->request_time[id])
			return (0);
	}
	else if (strcmp(data->scheduler, "edf") == 0)
	{
		if (data->states[l] == HUNGRY && data->deadlines[l] < data->deadlines[id])
			return (0);
		if (data->states[r] == HUNGRY && data->deadlines[r] < data->deadlines[id])
			return (0);
	}
	return (1);
}

int can_i_compile(t_coders *coder, t_data *data)
{
	int idx = coder->id - 1;
	int left = (idx + 1) % data->nb_coders;
	int right = (idx - 1 + data->nb_coders) % data->nb_coders;

	if (data->states[left] == COMPILING || data->states[right] == COMPILING)
		return (0);
	return (check_fifo_edf(coder, data, left, right));
}

void demander_dongles(t_coders *coder, t_data *data)
{
	int idx = coder->id - 1;

	pthread_mutex_lock(&data->arbiter_mutex);
	data->states[idx] = HUNGRY;
	data->request_time[idx] = get_current_time();
	data->deadlines[idx] = data->request_time[idx] + coder->time_burn;
	while (!can_i_compile(coder, data))
		pthread_cond_wait(&data->cond_vars[idx], &data->arbiter_mutex);
	data->states[idx] = COMPILING;
	pthread_mutex_unlock(&data->arbiter_mutex);
}

void relacher_dongles(t_coders *coder, t_data *data)
{
	int idx = coder->id - 1;
	int left = (idx + 1) % data->nb_coders;
	int right = (idx - 1 + data->nb_coders) % data->nb_coders;

	pthread_mutex_lock(&data->arbiter_mutex);
	data->states[idx] = THINKING;
	pthread_cond_signal(&data->cond_vars[left]);
	pthread_cond_signal(&data->cond_vars[right]);
	pthread_mutex_unlock(&data->arbiter_mutex);
}

void *action_coders(void *arg)
{
	t_coders	*coders;
	t_data		*data;
	int			i;

	i = 0;
	coders = (t_coders *)arg;
	data = coders->global_data;
	while (i < coders->nb_comp)
	{
		demander_dongles(coders, data);
		wait_for_action(coders, 0);
		relacher_dongles(coders, data);
		wait_for_action(coders, 1);
		wait_for_action(coders, 2);
		i++;
	}
	return (NULL);
}