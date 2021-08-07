/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblink <tblink@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/07 13:58:26 by tblink            #+#    #+#             */
/*   Updated: 2021/08/07 13:58:27 by tblink           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	action_eat(t_data *data, int id)
{
	data->philos[id - 1].state = 2;
	eat(data, id);
}

void	action_sleep(t_data *data, int id)
{
	data->philos[id - 1].state = 3;
	print_time(data, id, "is sleeping");
	ft_set_timeout(data->value->time_to_sleep * 1000);
}

void	action_think(t_data *data, int id)
{
	data->philos[id - 1].state = 1;
	print_time(data, id, "is thinking");
}

void	do_next_action(t_data *data, int id)
{
	if (data->philos[id - 1].state == 1)
		action_eat(data, id);
	else if (data->philos[id - 1].state == 2)
		action_sleep(data, id);
	else if (data->philos[id - 1].state == 3)
		action_think(data, id);
}
