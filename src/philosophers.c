/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbourdea <tbourdea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 15:35:40 by tbourdea          #+#    #+#             */
/*   Updated: 2023/09/05 19:07:48 by tbourdea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

// int	get_random(int max)
// {
// 	double	val;

// 	val = (double) max * rand();
// 	val /= (RAND_MAX + 1.0);
// 	return ((int)val);
// }

// void	*fn_store(void* arg)
// {
// 	t_store*	store;
	
// 	store = (t_store*) arg;
// 	while (1)
// 	{
// 		if (store->stock <= 0)
// 		{
// 			store->stock += 20;
// 			printf ("Remplissage du stock de %d articles\n", store->stock);
// 		}
// 	}
// 	return (NULL);
// 	// (void) arg;
// 	// sleep (1);
// 	// printf("Thread num %lu\n", pthread_self());
// 	// return (NULL);
// }

// void	*fn_clients(void* arg)
// {
// 	t_store*	store;
// 	int			val;

// 	store = (t_store*) arg;
// 	while (1)
// 	{
// 		val = get_random(6);
// 		sleep(get_random(5));
// 		store->stock -= val;
// 		printf("Client %d prend %d du stock, reste %d en stock\n", store->client_id, val, store->stock);
// 	}
// 	return (NULL);
// }

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

// int	ft_init(int philo_nb)
// {
// 	int		i;
// 	t_philo	philo;
	
// 	while (i < philo_nb)
// 	{
// 		pthread_mutex_init(&philo.l_fork, NULL);
// 		pthread_create(&philo.t1, NULL, &routine, (void*)&philo);
		
// 		i++;
// 	}
// }

void	*routine(void *arg)
{
	// int		i;
	t_philo	*philo;

	philo = (t_philo*)arg;
	// philo.l_fork = data->forks[philo.id];
	// if (philo.id == 1)
	// 	philo.r_fork = data->forks[data->philo_nb];
	// else
	// 	philo.r_fork = data->forks[philo.id - 1];
	if (ft_timer(philo->data->start_timer) < philo->data->eat_timer && philo->id % 2 == 0)
		take_forks(philo);
	while (philo->eat_count != philo->data->meals_nb)
	{
		if (philo->eating)
			ft_write(ft_timer(philo->data->start_timer),philo->id, "is eating\n", &philo->data->write);
		ft_usleep(philo->data->eat_timer);
		philo->eat_count++;
		// if (drop_forks(philo))
		// 	return (NULL);
		ft_write(ft_timer(philo->data->start_timer),philo->id, "is sleeping\n", &philo->data->write);
		ft_usleep(philo->data->sleep_timer);
		ft_write(ft_timer(philo->data->start_timer),philo->id, "is thinking\n", &philo->data->write);
		pthread_mutex_lock(&philo->data->write);
		printf("%d ate %d of %d meals\n",philo->id, philo->eat_count, philo->data->meals_nb);
		pthread_mutex_unlock(&philo->data->write);
	}
	return (NULL);
}

// void	*monitor(void *arg)
// {
// 	t_data	*data;

// 	data = (t_data*)arg;
// 	while (data->philos->status)
// 	{
		
// 	}
// }

int	main(int ac, char **av)
{
	t_data	data;
	t_philo	*philos;
	int		i;

	i = 0;
	philos = NULL;
	data.philos = philos;
	// if (parsing(ac, av))
	// 	return (1);
	ft_init_param(ac, av, &data); 
	data.start_timer = get_time();
	i = 0;
	pthread_mutex_init(&data.lock, NULL);
	while (i < ft_atoi(av[1]))
	{
		pthread_create(&data.thread_id[i], NULL, &routine, (void*)&data.philos[i]);
		i++;
	}
	// pthread_create(&data.thread_id[i], NULL, &monitor, (void*)&data);
	// pthread_join(data.thread_id[data.philo_nb - 1], NULL);
	ft_usleep(10000);
	pthread_mutex_destroy(&data.write);
	return (0);
}
	// pthread_t	thread;

	// thread = pthread_self();
	// pthread_create(&thread, NULL, display_thread_id, NULL);
	// pthread_cancel(thread);
	// pthread_exit (NULL);
	// pthread_join(thread, NULL);
	// printf("Thread parent num %lu\n", pthread_self());