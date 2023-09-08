/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbourdea <tbourdea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 18:30:10 by tbourdea          #+#    #+#             */
/*   Updated: 2023/09/08 16:36:13 by tbourdea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	take_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->l_fork);
	ft_write(ft_time_from(philo->data->start_timer), "has taken a fork\n", philo);
	pthread_mutex_lock(philo->r_fork);
	ft_write(ft_time_from(philo->data->start_timer), "has taken a fork\n", philo);
}

void	drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
	ft_write(ft_time_from(philo->data->start_timer), "is sleeping\n", philo);
	ft_usleep(philo->data->sleep_timer);
}

void	ft_eat(t_philo *philo)
{
	take_forks(philo);
	pthread_mutex_lock(&philo->lock);
	philo->eating = 1;
	philo->time_to_die = get_time() + philo->data->death_timer;
	ft_write(ft_time_from(philo->data->start_timer), "is eating\n", philo);
	philo->eat_count++;
	ft_usleep(philo->data->eat_timer);
	philo->eating = 0;
	pthread_mutex_unlock(&philo->lock);
	drop_forks(philo);
}