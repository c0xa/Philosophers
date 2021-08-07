/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_eat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblink <tblink@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/07 13:58:23 by tblink            #+#    #+#             */
/*   Updated: 2021/08/07 13:58:24 by tblink           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	case_one_philo(t_data *data, int min_fork)
{
	pthread_mutex_unlock(&data->forks[min_fork]);
	while (data->is_alive)
		;
	return ;
}

static void	do_eat(t_data *data, int id, int min_fork, int max_fork)
{
	pthread_mutex_lock(&data->forks[min_fork]);
	print_time(data, id, "has taken a fork");
	if (data->value->number_of_philosophers == 1)
	{
		case_one_philo(data, min_fork);
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

int	ate_count_of_times(t_data *data)
{
	int	i;
	int	eating_count;
	int	number_of_times_to_eat;

	i = 0;
	while (i < data->value->number_of_philosophers)
	{
		eating_count = data->philos[i].eating_count;
		number_of_times_to_eat = data->value->number_of_times_to_eat;
		if (eating_count < number_of_times_to_eat)
			return (0);
		i++;
	}
	return (1);
}

void	philo_full(t_data *data)
{
	if (ate_count_of_times(data))
	{
		print_time(data, -1, "all philosophers are full");
		data->is_alive = 0;
	}
}

void	eat(t_data *data, int id)
{
	int	min_fork;
	int	max_fork;

	if (data->philos[id - 1].left_fork > data->philos[id - 1].right_fork)
	{
		min_fork = data->philos[id - 1].right_fork;
		max_fork = data->philos[id - 1].left_fork;
	}
	else
	{
		min_fork = data->philos[id - 1].left_fork;
		max_fork = data->philos[id - 1].right_fork;
	}
	do_eat(data, id, min_fork, max_fork);
	if (data->value->number_of_times_to_eat != -1)
		philo_full(data);
	pthread_mutex_unlock(&data->forks[min_fork]);
	pthread_mutex_unlock(&data->forks[max_fork]);
}
