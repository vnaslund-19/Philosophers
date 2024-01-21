/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnaslund <vnaslund@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 18:14:36 by vnaslund          #+#    #+#             */
/*   Updated: 2023/11/21 15:59:47 by vnaslund         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_parse_input(int argc, char **argv, t_data *data)
{
	int	i;

	i = 0;
	while (++i < argc)
	{
		if (philo_syntax_error(argv[i]))
			exit_handler("Incorrect input", data);
	}
	data->nbr_of_philos = ft_atoi_long(argv[1]);
	data->time_to_die = ft_atoi_long(argv[2]) * 1000;
	data->time_to_eat = ft_atoi_long(argv[3]) * 1000;
	data->time_to_sleep = ft_atoi_long(argv[4]) * 1000;
	if (data->nbr_of_philos < 1)
		exit_handler("There needs to be at least 1 philosopher", data);
	if (data->time_to_die < 0 || data->time_to_eat < 0
		|| data->time_to_sleep < 0)
		exit_handler("Please enter a value between 0 and LONG_MAX", data);
	if (argc == 6)
	{
		data->meal_limit = ft_atoi_long(argv[5]);
		if (data->meal_limit < 0)
			exit_handler("Please enter a value between 0 and LONG_MAX", data);
	}
	else
		data->meal_limit = -1;
}

int	philo_syntax_error(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (1);
	}
	return (0);
}

long	ft_atoi_long(const char *str)
{
	int		i;
	int		sign;
	long	num;

	sign = 1;
	i = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'
		|| str[i] == '\v' || str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	num = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		num = num * 10 + str[i] - '0';
		i++;
	}
	return (num * sign);
}
