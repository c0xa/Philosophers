#include "philo.h"

void	do_eat(t_data *data, int id, int min_fork, int max_fork)
{
	pthread_mutex_lock(&data->forks[min_fork]);
	print_time(data, id, "has taken a fork");
	if (data->value->number_of_philosophers == 1)
	{
		pthread_mutex_unlock(&data->forks[min_fork]);
		while (data->is_alive)
			;
		return ;
	}
	pthread_mutex_lock(&data->forks[max_fork]);
	print_time(data, id, "has taken a fork");
	pthread_mutex_lock(&data->ph_mtx[id - 1]);
	data->philos[id - 1].time_to_die = data->value->time_to_die;
	pthread_mutex_unlock(&data->ph_mtx[id - 1]);
	print_time(data, id, "is eating");
	ft_set_timeout(data->value->time_to_eat * 1000);
	(data->philos[id - 1].eating_count)++;
}

void	try_to_eat(t_data *data, int id)
{
	int	min_fork;
	int	max_fork;

	if (data->philos[id - 1].left_fork > data->philos[id - 1].right_fork) {
		min_fork =  data->philos[id - 1].right_fork;
		max_fork = data->philos[id - 1].left_fork;
	}
	else {
		min_fork =  data->philos[id - 1].left_fork;
		max_fork = data->philos[id - 1].right_fork;
	}
	do_eat(data, id, min_fork, max_fork);
	if (data->value->number_of_times_to_eat != -1
			&& ate_count_of_times(data))
	{
		print_time(data, -1, "all philosophers are full");
		data->is_alive = 0;
	}
	pthread_mutex_unlock(&data->forks[min_fork]);
	pthread_mutex_unlock(&data->forks[max_fork]);
}

void	do_next_action(t_data *data, int id)
{
	if (data->philos[id - 1].state == 1)
	{
		data->philos[id - 1].state = 2;
		try_to_eat(data, id);
	}
	else if (data->philos[id - 1].state == 2)
	{
		data->philos[id - 1].state = 3;
		print_time(data, id, "is sleeping");
		ft_set_timeout(data->value->time_to_sleep * 1000);
	}
	else if (data->philos[id - 1].state == 3)
	{
		data->philos[id - 1].state = 1;
		print_time(data, id, "is thinking");
	}
}