/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argument_parser.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcaliqui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 16:20:16 by dcaliqui          #+#    #+#             */
/*   Updated: 2024/10/28 16:20:19 by dcaliqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	parse_required_arguments(int argc, char **argv, t_params *params)
{
	if (argc != 5 && argc != 6)
	{
		printf("Usage: number_philosophers time_die time_eat time_to_sleep\n");
		return (1);
	}
	if (!is_numeric_string(argv[2]) || !is_numeric_string(argv[3])
		|| !is_numeric_string(argv[4]))
	{
		printf("Error: All time values must be numeric.\n");
		return (1);
	}
	params->time_to_die = ft_atoi(argv[2]);
	params->time_to_eat = ft_atoi(argv[3]);
	params->time_to_sleep = ft_atoi(argv[4]);
	if (params->time_to_die < 60 || params->time_to_eat < 60
		|| params->time_to_sleep < 60)
	{
		printf("Error: times must be at least 60 ms.\n");
		return (1);
	}
	return (0);
}

int	parse_optional_meal_argument(int argc, char **argv, t_params *params)
{
	if (argc == 6)
	{
		if (!is_numeric_string(argv[5]))
		{
			printf("Error: All time values must be numeric.\n");
			return (1);
		}
		params->number_of_meals = atoi(argv[5]);
		if (params->number_of_meals <= 0)
		{
			printf("Error: number_of_meals must be a positive value.\n");
			return (1);
		}
	}
	else
	{
		params->number_of_meals = -1;
	}
	return (0);
}

int	parse_arguments(int argc, char **argv, t_params *params)
{
	if (parse_required_arguments(argc, argv, params))
		return (1);
	if (parse_optional_meal_argument(argc, argv, params))
		return (1);
	return (0);
}
