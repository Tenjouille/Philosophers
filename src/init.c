/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbourdea <tbourdea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 11:22:45 by tbourdea          #+#    #+#             */
/*   Updated: 2023/09/11 17:04:59 by tbourdea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	ft_init_threads(t_data *data)
{
	long	i;

	i = 0;
	while (i < data->philo_nb)
	{
		if (pthread_create(&data->philos[i].tid, NULL, &routine,
				(void *) &data->philos[i]))
			return (write(2, "pthread_create FAILURE\n", 23), 1);
		i += 2;
	}
	ft_usleep(1, data);
	i = 1;
	while (i < data->philo_nb)
	{
		if (pthread_create(&data->philos[i].tid, NULL, &routine,
				(void *) &data->philos[i]))
			return (write(2, "pthread_create FAILURE\n", 23), 1);
		i += 2;
	}
	return (0);
}

int	ft_malloc_init(t_data *data)
{
	data->philos = malloc(sizeof(t_philo) * data->philo_nb);
	if (!data->philos)
		return (write (2, "malloc FAILURE\n", 15), 1);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->philo_nb);
	if (!data->forks)
		return (write (2, "malloc FAILURE\n", 15), 1);
	return (0);
}

int	ft_init_philos(t_data *data)
{
	long	i;

	i = 0;
	while (i < data->philo_nb)
	{
		data->philos[i].data = data;
		data->philos[i].id = i + 1;
		data->philos[i].eat_count = 0;
		data->philos[i].time_to_die = get_time() + data->death_timer;
		data->philos[i].philo_nb = data->philo_nb;
		data->philos[i].meals_nb = data->meals_nb;
		data->philos[i].death_timer = data->death_timer;
		data->philos[i].eat_timer = data->eat_timer;
		data->philos[i].sleep_timer = data->sleep_timer;
		data->philos[i].start_timer = data->start_timer;
		i++;
	}
	return (0);
}

int	ft_init_forks(t_data *data)
{
	long	i;

	i = -1;
	while (++i < data->philo_nb)
		if (pthread_mutex_init(&data->forks[i], NULL))
			return (write (2, "Mutex init FAILURE\n", 19), 1);
	i = 0;
	while (i < data->philo_nb - 1)
	{
		data->philos[i].r_fork = &data->forks[i];
		data->philos[i].l_fork = &data->forks[i + 1];
		i++;
	}
	data->philos[i].r_fork = &data->forks[i];
	data->philos[i].l_fork = &data->forks[0];
	return (0);
}

int	ft_init_data(int ac, char **av, t_data *data)
{
	data->philo_nb = ft_atol(av[1]);
	if (ac == 6)
	{
		data->meals_nb = ft_atol(av[5]);
		if (data->meals_nb < 0)
			return (-1);
	}
	else
		data->meals_nb = -1;
	data->death_timer = ft_atol(av[2]);
	data->eat_timer = ft_atol(av[3]);
	data->sleep_timer = ft_atol(av[4]);
	data->start_timer = get_time();
	data->dead = 0;
	data->done = 0;
	if (data->philo_nb <= 0 || data->death_timer <= 0 || data->eat_timer <= 0
		|| data->sleep_timer <= 0)
		return (-1);
	if (pthread_mutex_init(&data->write, NULL))
		return (write (2, "Mutex init FAILURE\n", 19), 1);
	if (pthread_mutex_init(&data->death, NULL))
		return (write (2, "Mutex init FAILURE\n", 19), 1);
	if (pthread_mutex_init(&data->meal, NULL))
		return (write (2, "Mutex init FAILURE\n", 19), 1);
	return (0);
}
