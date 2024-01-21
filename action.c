/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnaslund <vnaslund@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 16:14:53 by vnaslund          #+#    #+#             */
/*   Updated: 2023/11/21 16:15:04 by vnaslund         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->first_fork->fork);
	print_take_fork(philo);
	pthread_mutex_lock(&philo->second_fork->fork);
	print_take_fork(philo);
	print_eating(philo);
	ft_usleep(philo->data->time_to_eat, philo->data);
	set_long(&philo->mutex, &philo->last_meal_time, ft_gettime(philo->data));
	increase_long(&philo->mutex, &philo->nbr_of_meals);
	if (philo->data->meal_limit > 0
		&& philo->nbr_of_meals == philo->data->meal_limit)
		set_bool(&philo->mutex, &philo->full, true);
	pthread_mutex_unlock(&philo->first_fork->fork);
	pthread_mutex_unlock(&philo->second_fork->fork);
}

void	philo_think(t_philo *philo)
{
	long	time_to_think;

	print_thinking(philo);
	if (philo->data->nbr_of_philos % 2 == 0)
		return ;
	else
	{
		time_to_think = philo->data->time_to_eat * 2
			- philo->data->time_to_sleep;
		if (time_to_think < 1)
			return ;
		ft_usleep(time_to_think * 0.6, philo->data);
	}
}

void	philo_sleep(t_philo *philo)
{
	print_sleeping(philo);
	ft_usleep(philo->data->time_to_sleep, philo->data);
}
