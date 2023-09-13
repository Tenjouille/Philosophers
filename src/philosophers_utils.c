/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbourdea <tbourdea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 13:56:41 by tbourdea          #+#    #+#             */
/*   Updated: 2023/09/11 17:34:06 by tbourdea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

long	ft_atol(char *str)
{
	int		i;
	long	res;

	i = 0;
	res = 0;
	if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + str[i] - '0';
		i++;
	}
	if (str[i])
		return (-1);
	return (res);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0')
		i++;
	return (s1[i] - s2[i]);
}

long	get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		return (write(2, "gettimeofday() FAILURE !\n", 25), 1);
	return (((long)tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

long	ft_usleep(long time, t_data *data)
{
	long	start;

	start = 0;
	while (start < time && !philo_dead(data))
	{
		usleep(10000);
		start += 10;
	}
	return (0);
}

long	ft_time_from(long start)
{
	return (get_time() - start);
}
