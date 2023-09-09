/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbourdea <tbourdea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 15:35:40 by tbourdea          #+#    #+#             */
/*   Updated: 2023/09/09 13:39:51 by tbourdea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	ft_parsing(int ac, char **av)
{
	if (ac < 5 || ac > 6)
	{
		write(2, "Error ! The differents argument are :\n", 38);
		write(2, "\t1.\tNumber of philosophers\n\t2.\tTime to die\n", 43);
		write(2, "\t3.\tTime to eat\n\t4.\tTime to sleep\n\t(5.\t", 39);
		write(2, "Number of times each philosophers must eat)\n\n", 45);
		write(2, "Please retry with the good number of argument.", 46);
		return (1);
	}
	if (ft_atoi(av[1]) <= 0 || ft_atoi(av[2]) <= 0 || ft_atoi(av[3]) <= 0
		|| ft_atoi(av[4]) <= 0)
		return (write (2, "Error ! Arguments must be bigger than 0.\n", 41),1);
	if (ac == 6 && ft_atoi(av[5]) < 0)
		return (1);
	return (0);
}

void	doctolib(t_data *data)
{
	while (!philo_dead(data))
	{
		if (get_time() >= philo->time_to_die && !philo->eating)
		{
			ft_write(ft_time_from(philo->start_timer), "died\n", philo);
			philo->data->dead = 1;
		}
	}
	return (NULL);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo*)arg;
	while (!philo->data->dead)
	{
		ft_eat(philo);
		ft_write(ft_time_from(philo->data->start_timer), "is thinking\n", philo);
	}
	return ((void*)0);
}

int	main(int ac, char **av)
{
	t_data	data;
	int		i;

	i = 0;
	// if (parsing(ac, av))
	// 	return (1);
	if (ft_init_all(ac, av, &data))
		return (1);
	while (i < data.philo_nb)
	{
		pthread_join(data.philos[i].thread_id, NULL);
		i++;
	}
	while (!doctolib(&data))
		continue;
	return (0);
}
