/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initial.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblink <tblink@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/07 13:58:29 by tblink            #+#    #+#             */
/*   Updated: 2021/08/07 13:58:30 by tblink           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	initial_philo(t_philo *philo, t_value *value)
{
	int	i;
	int	count_philo;

	i = 0;
	count_philo = value->number_of_philosophers;
	while (i < count_philo)
	{
		philo[i].state = 2;
		philo[i].time_to_die = value->time_to_die;
		philo[i].left_fork = i;
		philo[i].right_fork = (i + 1) % count_philo;
		philo[i].eating_count = 0;
		i++;
	}
}

static int	initial_mutex(t_data *data)
{
	if ((pthread_mutex_init(&data->id_mtx, NULL)) != 0)
	{
		return (-1);
	}
	if ((pthread_mutex_init(&data->sim_mtx, NULL)) != 0)
	{
		pthread_mutex_destroy(&data->id_mtx);
		return (-1);
	}
	return (0);
}

static int	initial_mutexs(t_data *data)
{
	int	i;
	int	count_philo;

	i = 0;
	count_philo = data->value->number_of_philosophers;
	while (i < count_philo)
	{
		if ((pthread_mutex_init(&data->ph_mtx[i], NULL)) != 0)
		{
			destroy_mtx(data->ph_mtx, i, 0);
			destroy_mtx(data->forks, i - 1, 0);
			pthread_mutex_destroy(&data->id_mtx);
			pthread_mutex_destroy(&data->sim_mtx);
			return (-1);
		}
		if ((pthread_mutex_init(&data->forks[i++], NULL)) != 0)
		{
			destroy_mtx(data->ph_mtx, i, 0);
			destroy_mtx(data->forks, i - 1, 0);
			pthread_mutex_destroy(&data->id_mtx);
			pthread_mutex_destroy(&data->sim_mtx);
			return (-1);
		}
	}
	return (0);
}

int	initial_main(t_data *data)
{
	static struct timeval	time;

	data->is_alive = 1;
	initial_philo(data->philos, data->value);
	if (initial_mutexs(data) == -1)
	{
		printf("Initial mutex failed\n");
		return (-1);
	}
	if (initial_mutex(data) == -1)
	{
		printf("Initial mutex failed\n");
		return (-1);
	}
	gettimeofday(&time, NULL);
	data->start_time = time;
	return (0);
}
