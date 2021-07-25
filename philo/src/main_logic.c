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

void			*watcher_actions(void *arg)
{
	t_data_info *data_info;
	t_data	*data;
	int		id;
	int		i;

	data_info = (t_data_info*)arg;
	data = data_info->data;
	id = data_info->id;
	while (data->is_alive)
	{
		pthread_mutex_lock(&data->ph_mtx[id - 1]);
		(data->philos[id - 1].time_to_die)--;
		if (data->philos[id - 1].time_to_die == 0)
		{
			print_time(data, id, "died");
			data->is_alive = 0;
			i = 0;
			while (i <= data->value->number_of_philosophers)
				pthread_mutex_unlock(&data->forks[i++]);
			pthread_mutex_unlock(&data->ph_mtx[id - 1]);
			return (NULL);
		}
		pthread_mutex_unlock(&data->ph_mtx[id - 1]);
		ft_set_timeout(1000);
	}
	return (NULL);
}

static void		act(t_data *data, t_data_info *data_info)
{
	pthread_t		tid;

	if (pthread_create(&tid, NULL, &watcher_actions, data_info) != 0)
	{
		printf("System error\n");
		pthread_mutex_unlock(&data->id_mtx);
		data->is_alive = 0;
		return ;
	}
	pthread_mutex_unlock(&data->id_mtx);
	while (data->is_alive)
		do_next_action(data, data_info->id);
	pthread_join(tid, NULL);
}

void			*philo_actions(void *arg)
{
	t_data 			*data;
	t_data_info		info;
	static int		next_id = 1;
	int				philo_id;

	data = (t_data*)arg;
	printf("%d\n", data->value->number_of_philosophers);
	pthread_mutex_lock(&data->id_mtx);
	if (next_id > data->value->number_of_philosophers)
	{
		next_id = data->value->number_of_philosophers
			- (data->value->number_of_philosophers % 2);
	}
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
	printf("%d\n", philo_id);
	act(data, &info);
	return (NULL);
}


int				simulation(t_data *data, int i)
{
	pthread_t		thread_id[MAXPHILO];

	while (i < data->value->number_of_philosophers)
	{
		if ((pthread_create(&thread_id[i], NULL, &philo_actions, &data) != 0))
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
