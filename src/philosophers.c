/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbourdea <tbourdea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 15:35:40 by tbourdea          #+#    #+#             */
/*   Updated: 2023/06/01 15:41:02 by tbourdea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int				count = 0;
pthread_mutex_t	lock;
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
		return (0);
	if (ft_atoi(av[1]) <= 0 || ft_atoi(av[2]) <= 0 || ft_atoi(av[3]) <= 0
		|| ft_atoi(av[4]) <= 0)
		return (0);
	if (ac == 6 && ft_atoi(av[5]) < 0)
		return (0);
}

void	*routine()
{
	int	i;

	i = 0;
	while (i < 1000000)
	{
		pthread_mutex_lock(&lock);
		count++;
		pthread_mutex_unlock(&lock);
		i++;
	}
	return (NULL);
}

int	main(void)
{
	pthread_t		tid1;
	pthread_t		tid2;

	// if (!parsing(ac, av))
	// 	return (1);
	pthread_mutex_init(&lock, NULL);
	pthread_create(&tid1, NULL, &routine, (void*)&lock);
	pthread_create(&tid2, NULL, &routine, NULL);
	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);
	pthread_mutex_destroy(&lock);
	printf("count : %d\n", count);
	return (0);
}
	// pthread_t	thread;

	// thread = pthread_self();
	// pthread_create(&thread, NULL, display_thread_id, NULL);
	// pthread_cancel(thread);
	// pthread_exit (NULL);
	// pthread_join(thread, NULL);
	// printf("Thread parent num %lu\n", pthread_self());