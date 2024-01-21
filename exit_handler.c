/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnaslund <vnaslund@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 18:16:02 by vnaslund          #+#    #+#             */
/*   Updated: 2023/11/21 13:03:24 by vnaslund         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	clean_data(t_data *data)
{
	int	i;

	i = -1;
	while (data->philos[++i])
	{
		pthread_mutex_destroy(&data->philos[i]->mutex);
		free(data->philos[i]);
	}
	free(data->philos);
	i = -1;
	while (data->forks[++i])
	{
		pthread_mutex_destroy(&data->forks[i]->fork);
		free(data->forks[i]);
	}
	free(data->forks);
	pthread_mutex_destroy(&data->write_lock);
	pthread_mutex_destroy(&data->mutex);
	free(data);
}

void	exit_handler(char *str, t_data *data)
{
	if (data->mem_allocated)
		clean_data(data);
	else
		free(data);
	printf("Error: %s\n", str);
	exit(1);
}
