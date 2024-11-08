/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcaliqui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 16:06:34 by dcaliqui          #+#    #+#             */
/*   Updated: 2024/10/25 16:06:37 by dcaliqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_philosopher_status(t_philosopher *philosopher, t_params *params)
{
	long	last_meal;

	pthread_mutex_lock(&philosopher->meals_mutex);
	last_meal = get_time_in_ms() - philosopher->last_meal_time;
	pthread_mutex_unlock(&philosopher->meals_mutex);
	if (last_meal >= params->time_to_die)
	{
		print_status(philosopher, "died");
		set_simulation_ended(params, 1);
		return (1);
	}
	return (0);
}

int	check_meals_completed(t_philosopher *philosophers,
		t_params *params, int num_philos)
{
	int	i;
	int	philos_full;

	i = 0;
	philos_full = 0;
	while (i < num_philos)
	{
		if (params->number_of_meals != -1
			&& get_meals_eaten(&philosophers[i]) >= params->number_of_meals)
			philos_full++;
		i++;
	}
	return (philos_full == num_philos);
}

int	monitor_philosophers(t_philosopher *philosophers, t_params *params, int num_philos)
{
	int 	i;
	long	current_time;

	while (1)
	{
		i = 0;
		while (i < num_philos)
		{
			pthread_mutex_lock(&params->sim_mutex);
			if (params->simulation_ended)
			{
				pthread_mutex_unlock(&params->sim_mutex);
				return (0);
			}
			pthread_mutex_unlock(&params->sim_mutex);
			current_time = get_time_in_ms();
			pthread_mutex_lock(&philosophers[i].meals_mutex);
			if ((current_time - philosophers[i].last_meal_time) >= params->time_to_die + 4)
			{
				print_status(&philosophers[i], "died");
				/*if (num_philos == 1)
					pthread_mutex_unlock(philosophers->right_fork);*/
				set_simulation_ended(params, 1);
				pthread_mutex_unlock(&philosophers[i].meals_mutex);
				return (1);
			}
			pthread_mutex_unlock(&philosophers[i].meals_mutex);
			i++;
		}
		if (check_meals_completed(philosophers, params, num_philos))
		{
			set_simulation_ended(params, 1);
			return (0);
		}
		usleep(50);
	}
}
