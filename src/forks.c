/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annamarianunes <annamarianunes@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 19:34:50 by annamarianu       #+#    #+#             */
/*   Updated: 2024/05/18 19:34:51 by annamarianu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "philosophers.h"

t_fork	*create_forks(int number_of_forks)
{
	int		i;
	t_fork	*forks;

	i = 0;
	forks = malloc(sizeof(t_fork) * number_of_forks);
	if (forks == NULL)
		return (malloc_error());
	while (i < number_of_forks)
	{
		forks[i].available = YES;
		pthread_mutex_init(&(forks[i].lock), NULL);
		i++;
	}
	return (forks);
}

int	has_fork(t_fork *fork)
{
	int	available;

	pthread_mutex_lock(&(fork->lock));
	available = fork->available;
	pthread_mutex_unlock(&(fork->lock));
	return (available);
}

void	philo_takes_forks(int nbr, long long starting_time, t_args *philo)
{
	long long	time;

	if (nbr % 2)
	{
		pthread_mutex_lock(&(philo->left_fork->lock));
		pthread_mutex_lock(&(philo->right_fork->lock));
	}
	else
	{
		pthread_mutex_lock(&(philo->right_fork->lock));
		pthread_mutex_lock(&(philo->left_fork->lock));
	}
	philo->left_fork->available = NO;
	philo->right_fork->available = NO;
	time = time_now() - starting_time;
	print_action(time, nbr, "has taken a fork", philo->data);
	time = time_now() - starting_time;
	print_action(time, nbr, "has taken a fork", philo->data);
}

void	philo_drops_forks(t_args *philo)
{
	philo->left_fork->available = YES;
	philo->right_fork->available = YES;
	pthread_mutex_unlock(&(philo->left_fork->lock));
	pthread_mutex_unlock(&(philo->right_fork->lock));
}
