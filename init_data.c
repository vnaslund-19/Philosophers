/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnaslund <vnaslund@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 19:14:56 by vnaslund          #+#    #+#             */
/*   Updated: 2023/11/21 14:55:58 by vnaslund         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_data(t_data *data)
{
	data->end_simulation = false;
	data->running_threads = 0;
	data->all_threads_ready = false;
	init_forks(data);
	init_philos(data);
	pthread_mutex_init(&data->mutex, NULL);
	pthread_mutex_init(&data->write_lock, NULL);
	data->mem_allocated = true;
}

void	init_forks(t_data *data)
{
	int	i;

	data->forks = malloc(sizeof(t_fork) * data->nbr_of_philos);
	if (!data->forks)
		exit_handler("Malloc error", data);
	i = -1;
	while (++i < data->nbr_of_philos)
	{
		data->forks[i] = malloc(sizeof(t_fork));
		if (!data->forks[i])
			exit_handler("Malloc error", data);
	}
	data->forks[i] = NULL;
	i = -1;
	while (++i < data->nbr_of_philos)
	{
		pthread_mutex_init(&data->forks[i]->fork, NULL);
		data->forks[i]->fork_id = i + 1;
	}
}

void	init_philos(t_data *data)
{
	int	i;

	data->philos = malloc(sizeof(t_philo) * data->nbr_of_philos);
	if (!data->philos)
		exit_handler("Malloc error", data);
	i = -1;
	while (++i < data->nbr_of_philos)
	{
		data->philos[i] = malloc(sizeof(t_philo));
		if (!data->philos[i])
			exit_handler("Malloc error", data);
		data->philos[i]->id = i + 1;
		data->philos[i]->nbr_of_meals = 0;
		data->philos[i]->last_meal_time = 0;
		data->philos[i]->full = false;
		data->philos[i]->data = data;
		pthread_mutex_init(&data->philos[i]->mutex, NULL);
		assign_forks(data->philos[i], data->forks);
	}
	data->philos[i] = NULL;
}

void	assign_forks(t_philo *philo, t_fork **forks)
{
	if (philo->id % 2 == 0)
	{
		philo->first_fork = forks[philo->id - 1];
		philo->second_fork = forks[philo->id - 2];
	}
	else
	{
		if (philo->id == 1)
			philo->first_fork = forks[philo->data->nbr_of_philos - 1];
		else
			philo->first_fork = forks[philo->id - 2];
		philo->second_fork = forks[philo->id - 1];
	}
}
