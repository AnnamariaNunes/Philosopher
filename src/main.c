/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annamarianunes <annamarianunes@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 19:35:00 by annamarianu       #+#    #+#             */
/*   Updated: 2024/05/18 19:35:01 by annamarianu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "philosophers.h"

int	main(int argc, char *argv[])
{
	pthread_t	*philos;
	t_fork		*forks;
	t_args		*args;
	t_data		data;

	if (handle_input(argc, argv, &data) == FAILED)
		return (E_INVAL);
	fill_data(&data);
	forks = NULL;
	args = NULL;
	if (data.order == NULL)
		return (handle_error(1, &data, forks, args));
	forks = create_forks(data.nbr_of_philos);
	if (forks == NULL)
		return (handle_error(2, &data, forks, args));
	args = create_args(&data, forks);
	if (args == NULL)
		return (handle_error(3, &data, forks, args));
	philos = create_philos(data.nbr_of_philos, args);
	if (philos == NULL)
		return (handle_error(4, &data, forks, args));
	simulation_monitoring(args, &data);
	join_philos(philos, data.nbr_of_philos);
	clean_variables(&data, forks, args, philos);
	return (0);
}
