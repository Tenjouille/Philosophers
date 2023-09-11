/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbourdea <tbourdea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 15:35:40 by tbourdea          #+#    #+#             */
/*   Updated: 2023/09/11 17:24:09 by tbourdea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	ft_freeall(t_data *data)
{
	long	i;

	i = 0;
	pthread_mutex_destroy(&data->death);
	pthread_mutex_destroy(&data->meal);
	pthread_mutex_destroy(&data->write);
	while (i < data->philo_nb)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	free (data->forks);
	free (data->philos);
}

int	ft_init_all(int ac, char **av, t_data *data)
{
	int	ret;

	if (ac < 5 || ac > 6)
		return (1);
	ret = ft_init_data(ac, av, data);
	if (ret == -1)
	{
		printf("Args can't be null, negatives or non numeric values\n");
		return (1);
	}
	if (ret == 1)
		return (1);
	if (ft_malloc_init(data))
		return (1);
	if (ft_init_philos(data))
		return (1);
	if (ft_init_forks(data))
		return (1);
	if (ft_init_threads(data))
		return (1);
	return (0);
}

void	*ft_one_philo(t_philo *philo)
{
	write(1, "0 1 has taken a fork\n", 21);
	usleep(philo->death_timer * 1000);
	printf ("%ld 1 died\n", philo->death_timer);
	return ((void *) 0);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *) arg;
	// if (philo->philo_nb == 1)
	// 	return (ft_one_philo(philo));
	while (!philo_dead(philo->data) && !philo_done(philo))
	{
		ft_eat(philo);
		ft_write("is thinking\n", philo);
	}
	return ((void *) 0);
}

int	main(int ac, char **av)
{
	t_data	data;
	long	i;

	i = 0;
	if (ft_init_all(ac, av, &data))
		return (1);
	if (data.philo_nb != 1)
		doctolib(&data);
	while (i < data.philo_nb)
	{
		pthread_join(data.philos[i].tid, NULL);
		i++;
	}
	ft_freeall(&data);
	return (0);
}
