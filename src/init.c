/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbourdea <tbourdea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 11:22:45 by tbourdea          #+#    #+#             */
/*   Updated: 2023/09/08 11:04:25 by tbourdea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	ft_malloc(t_data *data)
{
	data->thread_id = malloc(sizeof(pthread_t) * data->philo_nb);
	if (!data->thread_id)
		return (write (2, "malloc FAILURE\n", 15), 1);
	data->philos = malloc(sizeof(t_philo) * data->philo_nb);
	if (!data->philos)
		return (write (2, "malloc FAILURE\n", 15), 1);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->philo_nb);
	if (!data->forks)
		return (write (2, "malloc FAILURE\n", 15), 1);
	return (0);
}

void	ft_init_philos(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_nb)
	{
		data->philos[i].data = data;
		data->philos[i].id = i + 1;
		data->philos[i].eat_count = 0;
		data->philos[i].time_to_die = get_time() + data->death_timer;
		data->philos[i].status = 0;
		data->philos[i].eating = 0;
		pthread_mutex_init(&data->philos[i].lock, NULL);
		i++;
	}
}

void	ft_init_forks(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->philo_nb)
		pthread_mutex_init(&data->forks[i], NULL);
	i = 0;
	while (i < data->philo_nb - 1)
	{
		data->philos[i].r_fork = &data->forks[i];
		data->philos[i].l_fork = &data->forks[i + 1];
		i++;
	}
	data->philos[i].r_fork = &data->forks[i];
	data->philos[i].l_fork = &data->forks[0];
}

int	ft_init_param(int ac, char **av, t_data *data)
{
	data->philo_nb = ft_atoi(av[1]);
	if (ac == 6)
		data->meals_nb = ft_atoi(av[5]);
	else
		data->meals_nb = -1;
	data->death_timer = ft_atoi(av[2]);
	data->eat_timer = ft_atoi(av[3]);
	data->sleep_timer = ft_atoi(av[4]);
	data->dead = 0;
	data->done = 0;
	if (ft_malloc(data))
		return (1);
	pthread_mutex_init(&data->write, NULL);
	pthread_mutex_init(&data->lock, NULL);
	ft_init_philos(data);
	ft_init_forks(data);
	return (0);
}
