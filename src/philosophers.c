/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annamarianunes <annamarianunes@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 19:35:05 by annamarianu       #+#    #+#             */
/*   Updated: 2024/05/18 19:35:06 by annamarianu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "philosophers.h"

static pthread_t	*create_one_philo(pthread_t *philo, t_args *args);
static void			*pthread_error(pthread_t *philos, int philo_nbr);

pthread_t	*create_philos(int nbr_of_philos, t_args *args)
{
	long long		starting_time;
	pthread_t		*philos;
	int				i;

	philos = NULL;
	philos = malloc(sizeof(pthread_t) * nbr_of_philos);
	if (philos == NULL)
		return (malloc_error());
	if (nbr_of_philos == 1)
		return (create_one_philo(philos, args));
	i = 0;
	starting_time = time_now();
	args->data->starting_time = starting_time;
	while (i < nbr_of_philos)
	{
		args[i].last_eat = starting_time;
		if (pthread_create(&philos[i], NULL, &routine, (void *)&args[i]) != 0)
			return (pthread_error(philos, args[i].nbr));
		i++;
	}
	return (philos);
}

void	join_philos(pthread_t *philos, int nbr_of_philos)
{
	int	i;

	i = 0;
	while (i < nbr_of_philos)
	{
		if (pthread_join(philos[i], NULL) != 0)
			printf("Error join philo %i thread.\n", i + 1);
		i++;
	}
}

static pthread_t	*create_one_philo(pthread_t *philo, t_args *args)
{
	args->data->starting_time = time_now();
	args->last_eat = args->data->starting_time;
	if (pthread_create(philo, NULL, &only_one_philo_routine, (void *)args) != 0)
		pthread_error(philo, args->nbr);
	return (philo);
}

static void	*pthread_error(pthread_t *philos, int philo_nbr)
{
	int	i;

	printf("Error creating philo %i thread.\n", philo_nbr);
	i = 0;
	while (i < philo_nbr)
	{
		pthread_detach(philos[i]);
		i++;
	}
	free (philos);
	return (NULL);
}
