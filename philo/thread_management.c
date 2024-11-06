/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_management.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcaliqui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 16:21:08 by dcaliqui          #+#    #+#             */
/*   Updated: 2024/10/28 16:21:10 by dcaliqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	start_philosopher_threads(t_philosopher *philosophers,
				t_philo_data *data, int number_of_philosophers)
{
	int	i;

	i = 0;
	while (i < number_of_philosophers)
	{
		init_philosopher(&philosophers[i], data, i);
		pthread_create(&philosophers[i].thread, NULL,
			philosopher_routine, &philosophers[i]);
		i++;
	}
}

void	set_simulation_ended(t_params *params, int ended)
{
	pthread_mutex_lock(&params->sim_mutex);
	params->simulation_ended = ended;
	pthread_mutex_unlock(&params->sim_mutex);
}

int	get_simulation_ended(t_params *params)
{
	int	ended;

	pthread_mutex_lock(&params->sim_mutex);
	ended = params->simulation_ended;
	pthread_mutex_unlock(&params->sim_mutex);
	return (ended);
}
