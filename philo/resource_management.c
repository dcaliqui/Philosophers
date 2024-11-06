/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resource_management.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcaliqui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 16:19:57 by dcaliqui          #+#    #+#             */
/*   Updated: 2024/10/28 16:19:59 by dcaliqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	allocate_resources(t_philosopher **philosophers,
	pthread_mutex_t **forks, int number_of_philosophers)
{
	*philosophers = malloc(sizeof(t_philosopher) * number_of_philosophers);
	if (!*philosophers)
		return (1);
	*forks = malloc(sizeof(pthread_mutex_t) * number_of_philosophers);
	if (!*forks)
	{
		free(*philosophers);
		return (1);
	}
	return (0);
}

void	init_philosopher(t_philosopher *philosopher, t_philo_data *data, int id)
{
	philosopher->id = id + 1;
	philosopher->meals_eaten = 0;
	philosopher->last_meal_time = data->params->start_time;
	philosopher->left_fork = &data->forks[id];
	if (id == 0)
		philosopher->right_fork = &data->forks[data->num_philosophers - 1];
	else
		philosopher->right_fork = &data->forks[id - 1];
	philosopher->time_to_die = data->params->time_to_die;
	philosopher->time_to_eat = data->params->time_to_eat;
	philosopher->time_to_sleep = data->params->time_to_sleep;
	philosopher->num_meals = data->params->number_of_meals;
	philosopher->start_time = data->params->start_time;
	philosopher->params = data->params;
	pthread_mutex_init(&philosopher->meals_mutex, NULL);
}

void	init_mutexes(pthread_mutex_t *forks, int number_of_philosophers)
{
	int	i;

	i = 0;
	while (i < number_of_philosophers)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
}

long	get_time_in_ms(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	clean_up_resources(t_philosopher *philosophers, pthread_mutex_t *forks,
			int number_of_philosophers)
{
	int	i;

	i = 0;
	while (i < number_of_philosophers)
	{
		pthread_join(philosophers[i].thread, NULL);
		pthread_mutex_destroy(&philosophers[i].meals_mutex);
		i++;
	}	
	free (philosophers);
	free(forks);
}
