#include "philo.h"

static void initial_philo(t_philo *philo, t_value *value)
{
	int i;
	int count_philo;

	i = 0;
	count_philo = value->number_of_philosophers;
	printf("count filo = %d", count_philo);
	while (i < count_philo) {
		philo[i].state = 0;
		philo[i].time_to_die = value->time_to_die;
		philo[i].left_fork = i;
		philo[i].right_fork = (i + 1) % count_philo;
		philo[i].eating_count = 0;
		i++;
	}
}

static void destroy_mtx_arr(pthread_mutex_t *mtx_arr, int size)
{
	int i;

	i = 0;
	while (i < size)
		pthread_mutex_destroy(&mtx_arr[i++]);
}

static int initial_mutex(t_data *data)
{
	int i;
	int count_philo;

	i = 0;
	count_philo = data->value->number_of_philosophers;
	while (i < count_philo) 
	{
		if ((pthread_mutex_init(&data->ph_mtx[i], NULL)) != 0)
		{
			destroy_mtx_arr(data->ph_mtx, i);
			destroy_mtx_arr(data->forks, i - 1);
			pthread_mutex_destroy(&data->id_mtx);
			pthread_mutex_destroy(&data->sim_mtx);
			return (-1);
		}
		if ((pthread_mutex_init(&data->forks[i++], NULL)) != 0)
		{
			destroy_mtx_arr(data->ph_mtx, i);
			destroy_mtx_arr(data->forks, i - 1);
			pthread_mutex_destroy(&data->id_mtx);
			pthread_mutex_destroy(&data->sim_mtx);
			return (-1);
		}
	}
	return (0);
}

int initial_main(t_data *data)
{
	initial_philo(data->philos, data->value);
	if (initial_mutex(data) == -1) {
		printf("Initial mutex failed\n");
		return (-1);
	}
	return (0);
}