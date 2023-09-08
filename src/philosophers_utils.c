/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbourdea <tbourdea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 13:56:41 by tbourdea          #+#    #+#             */
/*   Updated: 2023/09/08 16:23:26 by tbourdea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0')
		i++;
	return (s1[i] - s2[i]);
}

int	get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		return (write(2, "gettimeofday() FAILURE !\n", 25), 1);
	return ((int)tv.tv_sec * 1000) + (tv.tv_usec / 1000);
}

int	ft_usleep(int time)
{
	int	start;

	start = get_time();
	while (get_time() - start < time)
		usleep(1);
	return  (0);
}

int	ft_time_from(int start)
{
	return (get_time() - start);
}

void	ft_write(int time, char *msg, t_philo *philo)
{
	pthread_mutex_lock(&philo->data->write);
	if (!philo->data->dead)
	{	
		printf("%d %d %s", time, philo->id, msg);
		if (!ft_strcmp(msg, "died\n"))
			philo->data->dead = 1;
	}
	pthread_mutex_unlock(&philo->data->write);
}
