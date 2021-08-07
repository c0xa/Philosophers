/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblink <tblink@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/07 13:58:37 by tblink            #+#    #+#             */
/*   Updated: 2021/08/07 13:58:38 by tblink           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *string)
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
		return (-1);
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

void	destroy_mtx(pthread_mutex_t *mtx_arr, int len, int i)
{
	while (i < len)
	{
		pthread_mutex_destroy(&mtx_arr[i]);
		i++;
	}
	free(mtx_arr);
}

void	error_create_thread(t_data *data)
{
	printf("System error\n");
	pthread_mutex_unlock(&data->id_mtx);
	data->is_alive = 0;
	return ;
}

void	*case_die(t_data *data, int id, int i)
{
	print_time(data, id, "died");
	data->is_alive = 0;
	while (i <= data->value->number_of_philosophers)
		pthread_mutex_unlock(&data->forks[i++]);
	pthread_mutex_unlock(&data->ph_mtx[id - 1]);
	return (NULL);
}
