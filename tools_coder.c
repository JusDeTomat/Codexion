#include "header.h"

int	wait_for_action(t_coders *c, int mode)
{
	long long	time;
	long long	start;

	start = get_current_time();
	if (mode == 0)
	{
		mprintf(c->data, "is compiling\n", c->id);
		time = c->data->time_comp;
	}
	else if (mode == 1)
	{
		mprintf(c->data, "is debugging\n", c->id);
		time = c->data->time_debug;
	}
	else
	{
		mprintf(c->data, "is refactoring\n", c->id);
		time = c->data->time_refac;
	}
	while (get_current_time() - start < time && !c->data->stop_flag)
		usleep(200);
	return (1);
}

void	*action_coders(void *arg)
{
	t_coders	*c;

	c = (t_coders *)arg;
	if (c->id % 2 == 0)
		usleep(1000); /* Anti-Deadlock : les pairs attendent 1ms */
	if (c->data->nb_coders == 1)
	{
		demander_dongle(c->dongle_l, c);
		while (!c->data->stop_flag)
			usleep(1000);
		return (NULL);
	}
	while (c->nb_comp > 0 && !c->data->stop_flag)
	{
		demander_dongle(c->dongle_l, c);
		if (c->data->stop_flag) break ;
		demander_dongle(c->dongle_r, c);
		if (c->data->stop_flag) break ;
		c->last_compile_start = get_current_time();
		wait_for_action(c, 0);
		relacher_dongle(c->dongle_r);
		relacher_dongle(c->dongle_l);
		if (--c->nb_comp == 0) { c->finished = 1; break ; }
		wait_for_action(c, 1);
		wait_for_action(c, 2);
	}
	return (NULL);
}