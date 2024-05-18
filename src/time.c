/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annamarianunes <annamarianunes@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 19:35:13 by annamarianu       #+#    #+#             */
/*   Updated: 2024/05/18 19:35:14 by annamarianu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "philosophers.h"

long long	time_now(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

long long	get_delta_time(long long start)
{
	return (time_now() - start);
}

void	time_wait(int time_to_wait, long long start)
{
	long long	delta_time;

	usleep(time_to_wait * 0.9 * 1000);
	delta_time = time_now() - start;
	while (delta_time < time_to_wait)
	{
		usleep(100);
		delta_time = time_now() - start;
	}
}

void	time_wait2(int time_to_wait, long long start)
{
	long long	delta_time;

	delta_time = time_now() - start;
	if (time_to_wait - delta_time > 2)
	{
		usleep((time_to_wait - delta_time) * 1000 * 0.9);
		delta_time = time_now() - start;
	}
	while (delta_time < time_to_wait)
	{
		usleep(100);
		delta_time = time_now() - start;
	}
}
