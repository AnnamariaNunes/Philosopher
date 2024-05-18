/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annamarianunes <annamarianunes@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 19:34:30 by annamarianu       #+#    #+#             */
/*   Updated: 2024/05/18 19:34:31 by annamarianu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "philosophers.h"

static void	set_philo_forks(t_args *args, t_fork *forks, int index,
	int nbr_of_philos)
{
	args->right_fork = &forks[index];
	if (nbr_of_philos == 1)
		args->left_fork = NULL;
	else if (index == 0)
		args->left_fork = &forks[nbr_of_philos - 1];
	else
		args->left_fork = &forks[index - 1];
}

t_args	*create_args(t_data *data, t_fork *forks)
{
	t_args	*args;
	int		i;

	args = malloc(sizeof(t_args) * data->nbr_of_philos);
	if (args == NULL)
		return (malloc_error());
	i = 0;
	while (i < data->nbr_of_philos)
	{
		args[i].nbr = i + 1;
		args[i].data = data;
		args[i].must_eat = data->nbr_of_times_must_eat;
		set_philo_forks(&args[i], forks, i, data->nbr_of_philos);
		if (data->order[0][i] == 1)
			args[i].next_eat = 0;
		else if (data->order[0][i] == 0 && data->order[1][i] == 1)
			args[i].next_eat = data->time.eating;
		else
			args[i].next_eat = 2 * data->time.eating;
		args[i].iteration = args[i].next_eat / data->time.eating;
		pthread_mutex_init(&(args[i].lock_philo), NULL);
		i++;
	}
	return (args);
}
