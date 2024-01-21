/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnaslund <vnaslund@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 13:09:08 by vnaslund          #+#    #+#             */
/*   Updated: 2023/11/21 16:14:13 by vnaslund         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*monitor_thread(void *param)
{
	int		i;
	t_data	*data;

	data = param;
	while (!all_threads_running(&data->mutex,
			&data->running_threads, data->nbr_of_philos))
		;
	while (!simulation_finished(data))
	{
		i = -1;
		while (++i < data->nbr_of_philos && !simulation_finished(data))
		{
			if (philo_died(data->philos[i]))
			{
				print_died(data->philos[i]);
				set_bool(&data->mutex, &data->end_simulation, true);
			}
		}
	}
	return (NULL);
}

bool	philo_died(t_philo *philo)
{
	if (get_bool(&philo->mutex, &philo->full))
		return (false);
	else if ((ft_gettime(philo->data)
			- get_long(&philo->mutex, &philo->last_meal_time))
		> philo->data->time_to_die)
		return (true);
	else
		return (false);
}

bool	all_threads_running(pthread_mutex_t *mutex, long *threads, long philos)
{
	bool	ret;

	ret = false;
	pthread_mutex_lock(mutex);
	if (*threads == philos)
		ret = true;
	pthread_mutex_unlock(mutex);
	return (ret);
}

bool	simulation_finished(t_data *data)
{
	return (get_bool(&data->mutex, &data->end_simulation));
}
