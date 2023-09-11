/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbourdea <tbourdea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 15:53:30 by tbourdea          #+#    #+#             */
/*   Updated: 2023/09/11 17:29:02 by tbourdea         ###   ########.fr       */
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

typedef struct s_philo
{
	struct s_data	*data;
	pthread_t		tid;
	int				id;
	long			philo_nb;
	long			meals_nb;
	long			death_timer;
	long			eat_timer;
	long			sleep_timer;
	long			start_timer;
	long			eat_count;
	long			time_to_die;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
}					t_philo;

typedef struct s_data
{
	long			philo_nb;
	long			meals_nb;
	int				done;
	int				dead;
	t_philo			*philos;
	long			death_timer;	
	long			eat_timer;
	long			sleep_timer;
	long			start_timer;
	pthread_mutex_t	*forks;
	pthread_mutex_t	death;
	pthread_mutex_t	write;
	pthread_mutex_t	meal;
}					t_data; 
/*		philosphers_utils		*/
long	ft_atol(char *str);
int		ft_strcmp(char *s1, char *s2);
long	get_time(void);
long	ft_usleep(long time, t_data *data);
int		ft_time_from(long start);
/*		check.c		*/
int		ft_scanner(long i, t_data *data);
void	doctolib(t_data *data);
int		done_eating(t_data *data);
int		philo_done(t_philo *philo);
int		philo_dead(t_data *data);
/*		actions.c		*/
void	take_forks(t_philo *philo);
void	drop_forks(t_philo *philo);
void	ft_eat(t_philo *philo);
void	ft_write(char *msg, t_philo *philo);
/*		init.c		*/
int		ft_init_threads(t_data *data);
int		ft_malloc_init(t_data *data);
int		ft_init_philos(t_data *data);
int		ft_init_forks(t_data *data);
int		ft_init_data(int ac, char **av, t_data *data);
/*		philosophers.c		*/
void	ft_freeall(t_data *data);
int		ft_init_all(int ac, char **av, t_data *data);
void	*ft_one_philo(t_philo *philo);
void	*routine(void *arg);

#endif