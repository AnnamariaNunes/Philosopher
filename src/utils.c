/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annamarianunes <annamarianunes@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 19:35:28 by annamarianu       #+#    #+#             */
/*   Updated: 2024/05/18 19:35:29 by annamarianu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "philosophers.h"

void	print_action(long long time, int philo, char *action, t_data *data)
{
	if (simulation(data) == STOP)
		return ;
	pthread_mutex_lock(&(data->lock_print));
	printf("%-5lld %i %s\n", time, philo, action);
	pthread_mutex_unlock(&(data->lock_print));
}

int	simulation(t_data *data)
{
	int	simulation;

	pthread_mutex_lock(&(data->lock_data));
	simulation = data->simulation;
	pthread_mutex_unlock(&(data->lock_data));
	return (simulation);
}

void	set_simulation(t_data *data)
{
	if (simulation(data) != STOP)
	{
		pthread_mutex_lock(&(data->lock_data));
		data->simulation--;
		pthread_mutex_unlock(&(data->lock_data));
	}
}

void	*malloc_error(void)
{
	write(2, "Malloc error.\n", 15);
	return (NULL);
}
