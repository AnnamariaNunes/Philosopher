/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_libft.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annamarianunes <annamarianunes@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 19:35:23 by annamarianu       #+#    #+#             */
/*   Updated: 2024/05/18 19:35:24 by annamarianu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "philosophers.h"

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

static int	return_not_int(int sign)
{
	if (sign == 1)
		return (-1);
	else
		return (0);
}

int	ft_atoi(const char *nptr)
{
	unsigned long long	n;
	int					i;
	int					sign;

	i = 0;
	sign = 1;
	n = 0;
	while (nptr[i] == ' ' || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '-')
		sign = -1;
	if (nptr[i] == '+' || nptr[i] == '-')
		i++;
	while (ft_isdigit(nptr[i]))
	{
		n = n * 10 + (nptr[i] - 48);
		i++;
	}
	if (n > 9223372036854775807)
		return (return_not_int(sign));
	return (n * sign);
}

long int	ft_atol(const char *nptr)
{
	unsigned long long	n;
	int					i;
	int					sign;

	i = 0;
	sign = 1;
	n = 0;
	while (nptr[i] == ' ' || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '-')
		sign = -1;
	if (nptr[i] == '+' || nptr[i] == '-')
		i++;
	while (ft_isdigit(nptr[i]))
	{
		n = n * 10 + (nptr[i] - 48);
		i++;
	}
	if (n > 9223372036854775807)
		return (return_not_int(sign));
	return (n * sign);
}
