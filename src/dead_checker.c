/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dead_checker.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annamarianunes <annamarianunes@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 19:34:43 by annamarianu       #+#    #+#             */
/*   Updated: 2024/05/18 20:08:48 by annamarianu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "philosophers.h"

static void	philo_dies(int philo, long long starting_time, t_data *data)
{
	long long		delta_time;

	delta_time = get_delta_time(starting_time);
	pthread_mutex_lock(&(data->lock_print));
	printf("%-5lld %i %s\n", delta_time, philo, "\033[0;31m died");
	pthread_mutex_unlock(&(data->lock_print));
}

void	simulation_monitoring(t_args *philos, t_data *data)
{
	int			i;
	long long	delta;

	while (simulation(data) != STOP)
	{
		i = 0;
		while (i < data->nbr_of_philos)
		{
			if (simulation(data) == STOP)
				break ;
			pthread_mutex_lock(&(philos[i].lock_philo));
			delta = time_now() - philos[i].last_eat;
			if (delta >= data->time.to_die)
			{
				pthread_mutex_lock(&(data->lock_data));
				data->simulation = STOP;
				pthread_mutex_unlock(&(data->lock_data));
				usleep(100);
				philo_dies(i + 1, data->starting_time, data);
			}
			pthread_mutex_unlock(&(philos[i].lock_philo));
			i++;
		}
		usleep(100);
	}
}
