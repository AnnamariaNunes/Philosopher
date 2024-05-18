/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annamarianunes <annamarianunes@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 19:34:38 by annamarianu       #+#    #+#             */
/*   Updated: 2024/05/18 19:34:39 by annamarianu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "philosophers.h"

static void	fill_even_matrix_order(int **m, int size)
{
	int	i;
	int	j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			if (i % 2 == 0 && j % 2 == 0)
				m[i][j] = 1;
			else if (i % 2 == 1 && j % 2 == 1)
				m[i][j] = 1;
			else
				m[i][j] = 0;
			j++;
		}
		i++;
	}
}

static void	fill_odd_matrix_order(int **m, int size)
{
	int	i;
	int	j;

	fill_even_matrix_order(m, size);
	m[0][size - 1] = 0;
	i = 2;
	while (i < size)
	{
		j = i - 2;
		while (j >= 0)
		{
			if (i % 2 == 1 && j % 2 == 0)
				m[i][j] = 1;
			else if (i % 2 == 0 && j % 2 == 1)
				m[i][j] = 1;
			else
				m[i][j] = 0;
			j--;
		}
		i++;
	}
}

static int	**create_matrix_order(int nbr_of_philos)
{
	int	**order;
	int	i;

	order = malloc(sizeof(int *) * nbr_of_philos);
	if (order == NULL)
		return (malloc_error());
	i = 0;
	while (i < nbr_of_philos)
	{
		order[i] = malloc(sizeof(int) * nbr_of_philos);
		if (order[i] == NULL)
		{
			free(order);
			order = NULL;
			return (malloc_error());
		}
		i++;
	}
	if (nbr_of_philos == 1)
		order[0][0] = 1;
	else if (nbr_of_philos % 2 == 0)
		fill_even_matrix_order(order, nbr_of_philos);
	else
		fill_odd_matrix_order(order, nbr_of_philos);
	return (order);
}

void	fill_data(t_data *data)
{
	data->simulation = data->nbr_of_philos;
	data->order = create_matrix_order(data->nbr_of_philos);
	pthread_mutex_init(&(data->lock_print), NULL);
	pthread_mutex_init(&(data->lock_data), NULL);
}
