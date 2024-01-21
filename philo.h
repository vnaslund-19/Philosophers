/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnaslund <vnaslund@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 15:00:28 by vnaslund          #+#    #+#             */
/*   Updated: 2023/11/21 16:13:06 by vnaslund         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <pthread.h>
# include <limits.h>
# include <stdbool.h>

typedef struct s_philo	t_philo;
typedef struct s_fork	t_fork;

typedef struct s_data
{
	long				nbr_of_philos;
	long				time_to_die;
	long				time_to_eat;
	long				time_to_sleep;
	long				meal_limit;
	long				sim_start_time;
	bool				end_simulation;
	t_fork				**forks;
	t_philo				**philos;
	pthread_mutex_t		mutex;
	pthread_mutex_t		write_lock;
	pthread_t			monitor;
	long				running_threads;
	bool				all_threads_ready;
	bool				mem_allocated;
}				t_data;

typedef struct s_fork
{
	pthread_mutex_t	fork;
	int				fork_id;
}				t_fork;

typedef struct s_philo
{
	int					id;
	long				nbr_of_meals;
	bool				full;
	long				last_meal_time;
	t_fork				*first_fork;
	t_fork				*second_fork;
	pthread_t			thread_id;
	pthread_mutex_t		mutex;
	t_data				*data;
}				t_philo;

void	ft_parse_input(int argc, char **argv, t_data *data);
int		philo_syntax_error(char *str);
long	ft_atoi_long(const char *str);

void	init_data(t_data *data);
void	init_forks(t_data *data);
void	init_philos(t_data *data);
void	assign_forks(t_philo *philo, t_fork **forks);

// Micro seconds
void	ft_setstart(t_data *data);
long	ft_gettime(t_data *data);
void	ft_usleep(long sleep_time, t_data *data);
void	synch_threads(t_data *data);
void	prep_by_desync(t_philo *philo);

void	set_bool(pthread_mutex_t *mutex, bool *dst, bool value);
void	set_long(pthread_mutex_t *mutex, long *dst, long value);
bool	get_bool(pthread_mutex_t *mutex, bool *value);
long	get_long(pthread_mutex_t *mutex, long *value);
void	increase_long(pthread_mutex_t *mutex, long *value);
bool	simulation_finished(t_data *data);

void	print_take_fork(t_philo *philo);
void	print_eating(t_philo *philo);
void	print_sleeping(t_philo *philo);
void	print_thinking(t_philo *philo);
void	print_died(t_philo *philo);

void	start_dinner(t_data *data);
void	*dinner_simulation(void *param);
void	*one_philo_sim(void *param);

void	*monitor_thread(void *param);
bool	philo_died(t_philo *philo);

void	philo_eat(t_philo *philo);
void	philo_think(t_philo *philo);
void	philo_sleep(t_philo *philo);

void	clean_data(t_data *data);
void	exit_handler(char *str, t_data *data);

// shit
bool	all_threads_running(pthread_mutex_t *mutex, long *threads, long philos);

#endif
