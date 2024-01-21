/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnaslund <vnaslund@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 16:23:29 by vnaslund          #+#    #+#             */
/*   Updated: 2023/11/21 16:09:42 by vnaslund         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_setstart(t_data *data)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL))
		exit_handler("gettimeofday fail", data);
	data->sim_start_time = (time.tv_sec * 1000000) + (time.tv_usec);
}

long	ft_gettime(t_data *data)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL))
		exit_handler("gettimeofday fail", data);
	return ((time.tv_sec * 1000000 + time.tv_usec) - data->sim_start_time);
}

void	ft_usleep(long sleep_time, t_data *data)
{
	long	start_time;
	long	time_passed;
	long	time_remaining;

	start_time = ft_gettime(data);
	while (ft_gettime(data) - start_time < sleep_time)
	{
		if (simulation_finished(data))
			return ;
		time_passed = ft_gettime(data) - start_time;
		time_remaining = sleep_time - time_passed;
		if (time_remaining > 1000)
			usleep(time_remaining / 2);
		else
		{
			while (ft_gettime(data) - start_time < sleep_time)
				;
		}
	}
}

void	synch_threads(t_data *data)
{
	while (!get_bool(&data->mutex, &data->all_threads_ready))
		;
}

void	prep_by_desync(t_philo *philo)
{
	long	wait_time;

	if (philo->data->nbr_of_philos % 2 == 0)
	{
		if (philo->id % 2 == 0)
			ft_usleep(10000, philo->data);
	}
	else
	{
		if (philo->id % 2 == 0)
		{
			wait_time = philo->data->time_to_eat * 2
				- philo->data->time_to_sleep;
			if (wait_time < 1)
				return ;
			ft_usleep(wait_time * 0.6, philo->data);
		}
	}
}
