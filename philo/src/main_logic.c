/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_logic.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblink <tblink@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/07 13:58:32 by tblink            #+#    #+#             */
/*   Updated: 2021/08/07 13:58:33 by tblink           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h" 

void	ft_set_timeout(int sec)
{
	struct timeval	start_time;
	struct timeval	iteration_time;
	int				sleep_time;

	gettimeofday(&start_time, NULL);
	while (1)
	{
		usleep(5);
		gettimeofday(&iteration_time, NULL);
		sleep_time = ((iteration_time.tv_sec - start_time.tv_sec) * 1000000)
			+ (iteration_time.tv_usec - start_time.tv_usec);
		if (sleep_time >= sec)
			break ;
	}
}

static void	*observer(void *arg)
{
	t_data_info	*data_info;
	t_data		*data;
	int			id;

	data_info = (t_data_info *)arg;
	data = data_info->data;
	id = data_info->id;
	while (data->is_alive)
	{
		pthread_mutex_lock(&data->ph_mtx[id - 1]);
		(data->philos[id - 1].time_to_die)--;
		if (data->philos[id - 1].time_to_die == 0)
			return (case_die(data, id, 0));
		pthread_mutex_unlock(&data->ph_mtx[id - 1]);
		ft_set_timeout(1000);
	}
	return (NULL);
}

static void	act(t_data *data, t_data_info *data_info)
{
	pthread_t		tid;

	if (pthread_create(&tid, NULL, &observer, data_info) != 0)
		return (error_create_thread(data));
	pthread_mutex_unlock(&data->id_mtx);
	while (data->is_alive)
		do_next_action(data, data_info->id);
	pthread_join(tid, NULL);
}

static void	*philo_actions(void *data_box)
{
	t_data		*data;
	t_data_info	info;
	static int	next_id = 1;
	int			philo_id;

	data = (t_data *)data_box;
	pthread_mutex_lock(&data->id_mtx);
	if (next_id > data->value->number_of_philosophers)
		next_id = data->value->number_of_philosophers
			- (data->value->number_of_philosophers % 2);
	philo_id = next_id;
	if (next_id % 2 == 0)
	{
		data->philos[next_id - 1].state = 3;
		next_id -= 2;
	}
	else
		next_id += 2;
	info.data = data;
	info.id = philo_id;
	act(data, &info);
	return (NULL);
}

int	simulation(t_data *data, int i)
{
	pthread_t		thread_id[MAXPHILO];

	while (i < data->value->number_of_philosophers)
	{
		if ((pthread_create(&thread_id[i], NULL, &philo_actions, data) != 0))
		{
			printf("System error\n");
			data->is_alive = 0;
			while (i-- >= 0)
				pthread_join(thread_id[i], NULL);
			return (1);
		}
		i++;
	}
	i = 0;
	while (i < data->value->number_of_philosophers)
		pthread_join(thread_id[i++], NULL);
	return (0);
}
