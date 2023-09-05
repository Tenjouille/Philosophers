/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbourdea <tbourdea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 18:30:10 by tbourdea          #+#    #+#             */
/*   Updated: 2023/09/05 19:03:58 by tbourdea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	take_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->l_fork);
	ft_write(philo->data->start_timer, philo->id, "has taken a fork", &philo->data->write);
	pthread_mutex_lock(philo->r_fork);
	ft_write(philo->data->start_timer, philo->id, "has taken a fork", &philo->data->write);
	philo->eating = 1;
}

void	drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_lock(philo->r_fork);
	ft_write(philo->data->start_timer, philo->id, "is sleeping", &philo->data->write);
	ft_usleep(philo->data->sleep_timer);
	philo->eating = 0;
}