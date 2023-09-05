/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbourdea <tbourdea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 15:53:30 by tbourdea          #+#    #+#             */
/*   Updated: 2023/09/05 19:02:24 by tbourdea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <pthread.h>
# include <unistd.h>
# include <stdint.h>
# include <sys/time.h>
# include "ft_printf.h"

typedef struct s_philo
{
	struct s_data	*data;
	pthread_t		t1;
	int				id;
	int				eat_count;
	int				status;
	int				eating;
	int				time_to_die;
	pthread_mutex_t	lock;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
}					t_philo;

typedef struct s_data
{
	pthread_t		*thread_id;
	int				philo_nb;
	int				meals_nb;
	int				death;
	int				done;
	t_philo			*philos;
	int				death_timer;	
	int				eat_timer;
	int				sleep_timer;
	int				start_timer;
	pthread_mutex_t	*forks;
	pthread_mutex_t	lock;
	pthread_mutex_t	write;
}					t_data; 
/*		philosphers_utils		*/
int		ft_init_param(int ac, char **av, t_data *data);
void	ft_init_philos(t_data *data);
void	ft_init_forks(t_data *data);
void	ft_write(int time, int philo, char *msg, pthread_mutex_t *write_mutex);
int		get_time(void);
int		ft_usleep(int time);
int		ft_timer(int start);
/*		parsing.c		*/
int		ft_atoi(char *str);
/*		philosophers.c		*/
void	*routine(void *arg);
/*		actions.c		*/
void	take_forks(t_philo *philo);
void	drop_forks(t_philo *philo);

#endif