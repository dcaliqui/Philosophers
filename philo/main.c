/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcaliqui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 14:18:45 by dcaliqui          #+#    #+#             */
/*   Updated: 2024/10/25 14:20:39 by dcaliqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	int				number_of_philosophers;
	t_params		params;
	t_philosopher	*philosophers;
	pthread_mutex_t	*forks;
	t_philo_data	data;

	number_of_philosophers = atoi(argv[1]);
	params.start_time = get_time_in_ms();
	params.simulation_ended = 0;
	if (parse_arguments(argc, argv, &params) != 0)
		return (1);
	if (allocate_resources(&philosophers, &forks, number_of_philosophers) != 0)
	{
		printf("Error allocating resources.\n");
		return (1);
	}
	pthread_mutex_init(&params.sim_mutex, NULL);
	init_mutexes(forks, number_of_philosophers);
	data.params = &params;
	data.forks = forks;
	data.num_philosophers = number_of_philosophers;
	start_philosopher_threads(philosophers, &data, number_of_philosophers);
	monitor_philosophers(philosophers, &params, number_of_philosophers);
	clean_up_resources(philosophers, forks, number_of_philosophers);
	return (0);
}
