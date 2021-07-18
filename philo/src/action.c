#include "philo.h" 

void			*philo_routine(t_data *data)
{
	t_data_info	philo_info;
	static int		id = 1;
	int				local_id;

	pthread_mutex_lock(&data->id_mtx);
	if (id > data->value->number_of_philosophers)
	{
		id = data->value->number_of_philosophers
			- (data->value->number_of_philosophers % 2);
	}
	local_id = id;
	if (id % 2 == 0)
	{
		data->philos[id - 1].state = SLEEPING;
		id -= 2;
	}
	else
		id += 2;
	philo_info.data = data;
	philo_info.id = local_id;
	act(data, philo_info);
	return (NULL);
}


int				start_simulation(t_data *data, int i)
{
	pthread_t		thread_id[MAXPHILO];

	while (i < data->value->number_of_philosophers)
	{
		if ((pthread_create(&thread_id[i], NULL, &philo_routine, (void*)&data)) != 0)
		{
			print_error(0, "System error");
			data->is_alive = 0;
			while (i-- >= 0)
				pthread_join(thread_id[i], NULL);
			pthread_join(thread_id[data->value->number_of_philosophers], NULL);
			free(thread_id);
		}
		i++;
	}
	i = 0;
	while (i < data->value->number_of_philosophers)
		pthread_join(thread_id[i++], NULL);
		free(thread_id);
	return (0);
}