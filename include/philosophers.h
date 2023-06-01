/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbourdea <tbourdea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 15:53:30 by tbourdea          #+#    #+#             */
/*   Updated: 2023/06/01 15:32:31 by tbourdea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <pthread.h>
# include <unistd.h>

typedef struct s_philo
{
	pthread_t		thread_id;
	int				id;
	int				eat_count;
	int				status;
	int				eating;
	int				death_timer;
	pthread_mutex_t	lock;
	pthread_mutex_t	right_fork;
	pthread_mutex_t	left_fork;
}					t_philo;

typedef struct s_data
{
	pthread_t		thread_id;
	int				philo_num;
	int				meals_nb;
	int				death;
	int				done;
	t_philo			*philo;
	int				death_timer;	
	int				eat_timer;
	int				sleep_timer;
	int				start_timer;
	pthread_mutex_t	*forks;
	pthread_mutex_t	lock;
	pthread_mutex_t	write;
}					t_data; 

#endif