/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnaslund <vnaslund@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 15:05:32 by vnaslund          #+#    #+#             */
/*   Updated: 2023/11/21 16:36:07 by vnaslund         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_data	*data;

	if (argc != 5 && argc != 6)
	{
		printf("Error: Wrong number of args\nCorrect input: nbr_of_philos, ");
		printf("time to: die, eat, sleep and meal_limit(optional)");
		return (0);
	}
	data = malloc(sizeof(t_data));
	if (!data)
	{
		printf("Malloc error");
		return (1);
	}
	data->mem_allocated = false;
	ft_parse_input(argc, argv, data);
	init_data(data);
	start_dinner(data);
	clean_data(data);
	return (0);
}
