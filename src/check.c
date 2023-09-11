/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbourdea <tbourdea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 17:31:09 by tbourdea          #+#    #+#             */
/*   Updated: 2023/09/11 16:57:10 by tbourdea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	ft_scanner(long i, t_data *data)
{
	int	res;

	res = 0;
	pthread_mutex_lock(&data->meal);
	if (get_time() >= data->philos[i].time_to_die)
	{
		ft_write("died\n", &data->philos[i]);
		pthread_mutex_lock(&data->death);
		data->dead = 1;
		pthread_mutex_unlock(&data->death);
		res = 1;
	}
	else
		res = 0;
	pthread_mutex_unlock(&data->meal);
	return (res);
}

void	doctolib(t_data *data)
{
	long	i;

	i = 0;
	while (!philo_dead(data))
	{
		while (i < data->philo_nb)
		{
			if (ft_scanner(i, data))
			{
				ft_write("died\n", &data->philos[i]);
				pthread_mutex_lock(&data->death);
				data->dead = 1;
				pthread_mutex_unlock(&data->death);
				return ;
			}
			i++;
		}
		i = 0;
		if (done_eating(data))
			break ;
	}
}

int	done_eating(t_data *data)
{
	long	i;
	long	done;

	i = 0;
	done = 0;
	while (i < data->philo_nb)
	{
		if (philo_done(&data->philos[i]))
			done++;
		i++;
	}
	if (i == done)
		return (1);
	return (0);
}

int	philo_done(t_philo *philo)
{
	int	res;

	pthread_mutex_lock(&philo->data->meal);
	if (philo->eat_count != philo->meals_nb)
		res = 0;
	else
		res = 1;
	pthread_mutex_unlock(&philo->data->meal);
	return (res);
}

int	philo_dead(t_data *data)
{
	int	res;

	pthread_mutex_lock(&data->death);
	res = data->dead;
	pthread_mutex_unlock(&data->death);
	return (res);
}
