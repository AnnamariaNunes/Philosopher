/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annamarianunes <annamarianunes@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 19:34:34 by annamarianu       #+#    #+#             */
/*   Updated: 2024/05/18 19:34:35 by annamarianu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "philosophers.h"

void	clean_variables(t_data *data, t_fork *forks, t_args *args,
	pthread_t *philos)
{
	int	i;

	i = 0;
	while (i < data->nbr_of_philos)
	{
		free(data->order[i]);
		pthread_mutex_destroy(&(args[i].lock_philo));
		pthread_mutex_destroy(&(forks[i].lock));
		i++;
	}
	pthread_mutex_destroy(&(data->lock_print));
	pthread_mutex_destroy(&(data->lock_data));
	free(args);
	free(forks);
	if (philos != NULL)
		free(philos);
	free(data->order);
}

static void	clean_data(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nbr_of_philos)
	{
		free(data->order[i]);
		i++;
	}
	pthread_mutex_destroy(&(data->lock_print));
	pthread_mutex_destroy(&(data->lock_data));
	free(data->order);
}

static void	clean_forks(t_fork	*forks, int nbr_of_philos)
{
	int	i;

	i = 0;
	while (i < nbr_of_philos)
	{
		pthread_mutex_destroy(&(forks[i].lock));
		i++;
	}
	free(forks);
}

static void	clean_args(t_args	*args, int nbr_of_philos)
{
	int	i;

	i = 0;
	while (i < nbr_of_philos)
	{
		pthread_mutex_destroy(&(args[i].lock_philo));
		i++;
	}
	free(args);
}

int	handle_error(int error, t_data *data, t_fork *forks, t_args *args)
{
	clean_data(data);
	if (error > 2)
		clean_forks(forks, data->nbr_of_philos);
	if (error > 3)
		clean_args(args, data->nbr_of_philos);
	return (error);
}
