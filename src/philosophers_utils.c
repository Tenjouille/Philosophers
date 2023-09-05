/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbourdea <tbourdea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 13:56:41 by tbourdea          #+#    #+#             */
/*   Updated: 2023/09/05 19:02:17 by tbourdea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	ft_init_param(int ac, char **av, t_data *data)
{
	int	i;

	i = 0;
	data->philo_nb = ft_atoi(av[1]);
	if (ac == 6)
		data->meals_nb = ft_atoi(av[5]);
	else
		data->meals_nb = -1;
	data->death_timer = ft_atoi(av[2]);
	data->eat_timer = ft_atoi(av[3]);
	data->sleep_timer = ft_atoi(av[4]);
	data->thread_id = malloc(sizeof(pthread_t) * ft_atoi(av[1]));
	if (!data->thread_id)
		return (write (2, "malloc FAILURE\n", 15), 1);
	data->philos = malloc(sizeof(t_philo) * ft_atoi(av[1]));
	if (pthread_mutex_init(&data->write, NULL))
		return (write(2 , "Mutex initiation FAILURE !\n", 27), 1);
	if (pthread_mutex_init(&data->lock, NULL))
		return (write(2 , "Mutex initiation FAILURE !\n", 27), 1);
	while (i < atoi(av[1]))
	{
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
	ft_init_philos(data);
	// while (i < data->philo_nb)
	// {
	// 	if (pthread_mutex_init(&data->forks[i], NULL))
	// 		return (write(2 , "Mutex initiation FAILURE !\n", 27), 1);
	// 	i++;
	// }
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
		data->philos[i].time_to_die = data->death_timer;
		data->philos[i].status = 0;
		data->philos[i].eating = 0;
		pthread_mutex_init(&data->philos[i].lock, NULL);
		ft_init_forks(data);
		i++;
	}
}

void	ft_init_forks(t_data *data)
{
	int	i;

	i = 0;
	
	while (i < data->philo_nb)
	{
		data->philos[i].r_fork = &data->forks[i - 1];
		if (data->philos[i].id == data->philo_nb)
			data->philos[i].l_fork = &data->forks[0];
		else
			data->philos[i].l_fork = &data->forks[i];
		i++;
	}
}

void	ft_write(int time, int philo_nb, char *msg, pthread_mutex_t *write_mutex)
{
	pthread_mutex_lock(write_mutex);
	ft_printf("%d %d %s", time, philo_nb, msg);
	pthread_mutex_unlock(write_mutex);
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
		usleep(time / 10);
	return  (0);
}

int	ft_timer(int start)
{
	return (get_time() - start);
}
