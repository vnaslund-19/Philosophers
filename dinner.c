/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnaslund <vnaslund@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 14:24:56 by vnaslund          #+#    #+#             */
/*   Updated: 2023/11/21 16:18:00 by vnaslund         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	start_dinner(t_data *data)
{
	int	i;

	ft_setstart(data);
	if (data->meal_limit == 0)
		return ;
	else if (data->nbr_of_philos == 1)
	{
		pthread_create(&data->philos[0]->thread_id,
			NULL, one_philo_sim, (void *)(data->philos[0]));
	}
	else
	{
		i = -1;
		while (++i < data->nbr_of_philos)
			pthread_create(&data->philos[i]->thread_id,
				NULL, dinner_simulation, (void *)(data->philos[i]));
	}
	set_bool(&data->mutex, &data->all_threads_ready, true);
	pthread_create(&data->monitor, NULL, monitor_thread, (void *)data);
	i = -1;
	while (++i < data->nbr_of_philos)
		pthread_join(data->philos[i]->thread_id, NULL);
	set_bool(&data->mutex, &data->end_simulation, true);
	pthread_join(data->monitor, NULL);
}

void	*dinner_simulation(void *param)
{
	t_philo	*philo;

	philo = param;
	synch_threads(philo->data);
	increase_long(&philo->data->mutex, &philo->data->running_threads);
	prep_by_desync(philo);
	while (!simulation_finished(philo->data))
	{
		if (get_bool(&philo->mutex, &philo->full))
			return (NULL);
		philo_eat(philo);
		philo_sleep(philo);
		philo_think(philo);
	}
	return (NULL);
}

void	*one_philo_sim(void *param)
{
	t_philo	*philo;

	philo = param;
	increase_long(&philo->data->mutex, &philo->data->running_threads);
	print_take_fork(philo);
	while (!simulation_finished(philo->data))
		;
	return (NULL);
}
