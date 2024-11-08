/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_routine.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcaliqui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 16:19:26 by dcaliqui          #+#    #+#             */
/*   Updated: 2024/10/28 16:19:35 by dcaliqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_forks(t_philosopher *phil)
{
	if(phil->params->num_philos == 1)
	{
		pthread_mutex_lock(phil->right_fork);
		print_status(phil, "has taken a fork");
		return ;
	}
	if (phil->id % 2 == 0)
	{
		pthread_mutex_lock(phil->left_fork);
		print_status(phil, "has taken a fork");
		pthread_mutex_lock(phil->right_fork);
		print_status(phil, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(phil->right_fork);
		print_status(phil, "has taken a fork");
		pthread_mutex_lock(phil->left_fork);
		print_status(phil, "has taken a fork");
	}
}

void	eat(t_philosopher *phil)
{
	pthread_mutex_lock(&phil->meals_mutex);
	phil->last_meal_time = get_time_in_ms();
	pthread_mutex_unlock(&phil->meals_mutex);
	print_status(phil, "is eating");
	usleep(phil->time_to_eat * 1000);
	pthread_mutex_lock(&phil->meals_mutex);
	phil->meals_eaten++;
	pthread_mutex_unlock(&phil->meals_mutex);
}

void	release_forks(t_philosopher *phil)
{
	if(phil->params->num_philos == 1)
	{
		pthread_mutex_unlock(phil->right_fork);
		return ;
	}
	if (phil->id % 2 == 0)
	{
		pthread_mutex_unlock(phil->right_fork);
		pthread_mutex_unlock(phil->left_fork);
	}
	else
	{
		pthread_mutex_unlock(phil->left_fork);
		pthread_mutex_unlock(phil->right_fork);
	}
}

void	*philosopher_routine(void *arg)
{
	t_philosopher	*phil;

	phil = (t_philosopher *)arg;
	while (!get_simulation_ended(phil->params)
		&& (phil->num_meals == -1 || get_meals_eaten(phil) < phil->num_meals))
	{
		if (phil->id % 2 == 0)
			usleep(1000);
		take_forks(phil);
		eat(phil);
		release_forks(phil);
		print_status(phil, "is sleeping");
		usleep(phil->time_to_sleep * 1000);
		print_status(phil, "is thinking");
	}
	return (NULL);
}

int	get_meals_eaten(t_philosopher *phil)
{
	int	meals;

	pthread_mutex_lock(&phil->meals_mutex);
	meals = phil->meals_eaten;
	pthread_mutex_unlock(&phil->meals_mutex);
	return (meals);
}

void	print_status(t_philosopher *phil, const char *status)
{
	long	timestamp;

	pthread_mutex_lock(&phil->params->sim_mutex);
	if (phil->params->simulation_ended == 1)
	{
		pthread_mutex_unlock(&phil->params->sim_mutex);
		return ;
	}
	timestamp = get_time_in_ms() - phil->start_time;
	printf("%ld %d %s\n", timestamp, phil->id, status);
	pthread_mutex_unlock(&phil->params->sim_mutex);
}
