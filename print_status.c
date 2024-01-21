/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_status.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnaslund <vnaslund@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 17:30:42 by vnaslund          #+#    #+#             */
/*   Updated: 2023/11/20 18:38:24 by vnaslund         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_take_fork(t_philo *philo)
{
	if (simulation_finished(philo->data))
		return ;
	pthread_mutex_lock(&philo->data->write_lock);
	printf("%ld %d has taken a fork\n",
		ft_gettime(philo->data) / 1000, philo->id);
	pthread_mutex_unlock(&philo->data->write_lock);
}

void	print_eating(t_philo *philo)
{
	if (simulation_finished(philo->data))
		return ;
	pthread_mutex_lock(&philo->data->write_lock);
	printf("%ld %d is eating\n", ft_gettime(philo->data) / 1000, philo->id);
	pthread_mutex_unlock(&philo->data->write_lock);
}

void	print_sleeping(t_philo *philo)
{
	if (simulation_finished(philo->data))
		return ;
	pthread_mutex_lock(&philo->data->write_lock);
	printf("%ld %d is sleeping\n",
		ft_gettime(philo->data) / 1000, philo->id);
	pthread_mutex_unlock(&philo->data->write_lock);
}

void	print_thinking(t_philo *philo)
{
	if (simulation_finished(philo->data))
		return ;
	pthread_mutex_lock(&philo->data->write_lock);
	printf("%ld %d is thinking\n",
		ft_gettime(philo->data) / 1000, philo->id);
	pthread_mutex_unlock(&philo->data->write_lock);
}

void	print_died(t_philo *philo)
{
	if (simulation_finished(philo->data))
		return ;
	pthread_mutex_lock(&philo->data->write_lock);
	printf("%ld %d died\n", ft_gettime(philo->data) / 1000, philo->id);
	pthread_mutex_unlock(&philo->data->write_lock);
}
