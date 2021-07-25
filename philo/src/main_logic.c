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

// static void			watcher_routine(t_data_info *data_info)
// {
// 	t_data	*data;
// 	int		id;
// 	int		i;

// 	data = data_info->data;
// 	id = data_info->id;
// 	while (data->is_alive)
// 	{
// 		pthread_mutex_lock(&data->ph_mtx[id - 1]);
// 		(data->philos[id - 1].time_to_die)--;
// 		if (data->philos[id - 1].time_to_die == 0)
// 		{
// 			print_time(data, id, "died");
// 			data->is_alive = 0;
// 			i = 0;
// 			while (i <= data->value->number_of_philosophers)
// 				pthread_mutex_unlock(&data->forks[i++]);
// 			pthread_mutex_unlock(&data->ph_mtx[id - 1]);
// 			return (NULL);
// 		}
// 		pthread_mutex_unlock(&data->ph_mtx[id - 1]);
// 		ft_set_timeout(1000);
// 	}
// }

// static void			act(t_data *data, t_data_info *data_info)
// {
// 	pthread_t		tid;

// 	if (pthread_create(&tid, NULL, watcher_routine, data_info) != 0)
// 	{
// 		print_error(0, "System error happened");
// 		pthread_mutex_unlock(&data->id_mtx);
// 		data->is_alive = 0;
// 		return ;
// 	}
// 	pthread_mutex_unlock(&data->id_mtx);
// 	while (data->is_alive)
// 		do_next_action(data, data_info->id);
// 	pthread_join(tid, NULL);
// }

// void			*philo_routine(t_data *data)
// {
// 	t_data_info	philo_info;
// 	int		id = 1;
// 	int		local_id;

// 	pthread_mutex_lock(&data->id_mtx);
// 	if (id > data->value->number_of_philosophers)
// 	{
// 		id = data->value->number_of_philosophers
// 			- (data->value->number_of_philosophers % 2);
// 	}
// 	local_id = id;
// 	if (id % 2 == 0)
// 	{
// 		data->philos[id - 1].state = 3;
// 		id -= 2;
// 	}
// 	else
// 		id += 2;
// 	philo_info.data = data;
// 	philo_info.id = local_id;
// 	act(data, &philo_info);
// 	return (NULL);
// }


// int				start_simulation(t_data *data, int i)
// {
// 	pthread_t		thread_id[MAXPHILO];

// 	while (i < data->value->number_of_philosophers)
// 	{
// 		if ((pthread_create(&thread_id[i], NULL, philo_routine, &data) != 0))
// 		{
// 			print_error(0, "System error");
// 			data->is_alive = 0;
// 			while (i-- >= 0)
// 				pthread_join(thread_id[i], NULL);
// 			pthread_join(thread_id[data->value->number_of_philosophers], NULL);
// 			free(thread_id);
// 		}
// 		i++;
// 	}
// 	i = 0;
// 	while (i < data->value->number_of_philosophers)
// 		pthread_join(thread_id[i++], NULL);
// 		free(thread_id);
// 	return (0);
// }