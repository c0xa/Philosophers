/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblink <tblink@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/07 13:58:39 by tblink            #+#    #+#             */
/*   Updated: 2021/08/07 13:58:40 by tblink           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# define MAXPHILO 200

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_value
{
	int			number_of_philosophers;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			number_of_times_to_eat;
}				t_value;

typedef struct s_philo
{
	int			state;
	int			time_to_die;
	int			left_fork;
	int			right_fork;
	int			eating_count;
}				t_philo;

typedef struct s_data
{
	int				is_alive;
	t_value			*value;
	t_philo			philos[MAXPHILO];
	pthread_mutex_t	forks[MAXPHILO];
	pthread_mutex_t	ph_mtx[MAXPHILO];
	struct timeval	start_time;
	pthread_mutex_t	id_mtx;
	pthread_mutex_t	sim_mtx;
}				t_data;

typedef struct s_data_info
{
	t_data	*data;
	int		id;
}				t_data_info;

int				ft_atoi(const char *string);
void			createThread(void);
int				initial_main(t_data *data);
void			print_time(t_data *data, int id, char *message);
int				simulation(t_data *data, int i);
void			ft_set_timeout(int sec);
void			do_next_action(t_data *data, int id);
int				ate_count_of_times(t_data *data);
void			eat(t_data *data, int id);
void			destroy_mtx(pthread_mutex_t *mtx_arr, int len, int i);
void			error_create_thread(t_data *data);
void			*case_die(t_data *data, int id, int i);
#endif