#include "philo.h"

int		ft_atoi(const char *string)
{
	unsigned long int	n;

	n = 0;
	while (*string == ' ' || *string == '\t' || *string == '\n'
		|| *string == '\v' || *string == '\f' || *string == '\r')
		string++;
	if (*string == '+')
	{
		string++;
	}
	while (*string >= '0' && *string <= '9')
	{
		if (n >= 9223372036854775807)
			return (-1);
		n = n * 10 + *(string++) - '0';
	}
	if (*string)
		return -1;
	return ((int)n);
}

void	print_time(t_data *data, int id, char *message)
{
	uintmax_t		timestamp;
	struct timeval	current_time;

	pthread_mutex_lock(&data->sim_mtx);
	if (data->is_alive == 0)
	{
		pthread_mutex_unlock(&data->sim_mtx);
		return ;
	}
	gettimeofday(&current_time, NULL);
	timestamp = (uintmax_t)((current_time.tv_sec - data->start_time.tv_sec)
			* 1000
			+ (current_time.tv_usec - data->start_time.tv_usec)
			/ 1000);
	if (id == -1)
		printf("%ju %s\n", timestamp, message);
	else
		printf("%ju %d %s\n", timestamp, id, message);
	pthread_mutex_unlock(&data->sim_mtx);
}