/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbourdea <tbourdea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 18:30:10 by tbourdea          #+#    #+#             */
/*   Updated: 2023/09/13 11:10:41 by tbourdea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->r_fork);
		ft_write("has taken a fork\n", philo);
		pthread_mutex_lock(philo->l_fork);
		ft_write("has taken a fork\n", philo);
	}
	else
	{
		pthread_mutex_lock(philo->l_fork);
		ft_write("has taken a fork\n", philo);
		pthread_mutex_lock(philo->r_fork);
		ft_write("has taken a fork\n", philo);
	}
}

void	drop_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_unlock(philo->r_fork);
	}
	else
	{
		pthread_mutex_unlock(philo->r_fork);
		pthread_mutex_unlock(philo->l_fork);
	}
	ft_write("is sleeping\n", philo);
	ft_usleep(philo->sleep_timer, philo->data);
}

void	ft_eat(t_philo *philo)
{
	take_forks(philo);
	pthread_mutex_lock(&philo->data->meal);
	philo->time_to_die = get_time() + philo->death_timer;
	philo->eat_count++;
	pthread_mutex_unlock(&philo->data->meal);
	ft_write("is eating\n", philo);
	ft_usleep(philo->eat_timer, philo->data);
	drop_forks(philo);
}

void	ft_write(char *msg, t_philo *philo)
{
	pthread_mutex_lock(&philo->data->write);
	if (!philo_dead(philo->data))
	{
		printf("%ld %d %s", ft_time_from(philo->start_timer), philo->id, msg);
		if (!ft_strcmp(msg, "died\n"))
		{
			pthread_mutex_lock(&philo->data->death);
			philo->data->dead = 1;
			pthread_mutex_unlock(&philo->data->death);
		}
	}
	pthread_mutex_unlock(&philo->data->write);
}
