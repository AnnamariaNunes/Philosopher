/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annamarianunes <annamarianunes@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 19:34:23 by annamarianu       #+#    #+#             */
/*   Updated: 2024/05/18 20:24:59 by annamarianu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "philosophers.h"

static void	update_must_eat(t_args *philo)
{
	if (philo->must_eat > 0)
	{
		philo->must_eat--;
		if (philo->must_eat == 0)
			set_simulation(philo->data);
	}
}

void	philo_eats(int nbr, int time_eating, t_args *philo)
{
	long long	delta_time;
	long long	eating_start;

	philo_takes_forks(nbr, philo->data->starting_time, philo);
	pthread_mutex_lock(&(philo->lock_philo));
	eating_start = time_now();
	delta_time = eating_start - philo->data->starting_time;
	print_action(delta_time, nbr, "\033[1;33m is eating", philo->data);
	philo->last_eat = eating_start;
	pthread_mutex_unlock(&(philo->lock_philo));
	time_wait(time_eating, eating_start);
	philo_drops_forks(philo);
	update_must_eat(philo);
}

void	philo_sleeps(int philo, int time_spleeping, long long starting_time,
			t_data *data)
{
	long long	delta_time;
	long long	sleeping_start;

	sleeping_start = time_now();
	delta_time = sleeping_start - starting_time;
	print_action(delta_time, philo, "\033[1;34m is sleeping", data);
	time_wait(time_spleeping, sleeping_start);
}

void	philo_thinks(int philo, long long starting_time, t_data *data)
{
	long long		delta_time;

	delta_time = get_delta_time(starting_time);
	print_action(delta_time, philo, "\033[1;35m is thinking", data);
	usleep(100);
}
