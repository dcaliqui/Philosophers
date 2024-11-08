/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcaliqui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 14:29:09 by dcaliqui          #+#    #+#             */
/*   Updated: 2024/10/25 14:30:45 by dcaliqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_params
{
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_meals;
	long			start_time;
	int				simulation_ended;
	int				num_philos;
	pthread_mutex_t	sim_mutex;
}	t_params;

typedef struct s_philosopher
{
	int				id;
	long			last_meal_time;
	int				meals_eaten;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_t		thread;
	long			start_time;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_meals;
	t_params		*params;
	pthread_mutex_t	meals_mutex;
}	t_philosopher;

typedef struct s_philo_data
{
	pthread_mutex_t	*forks;
	t_params		*params;
	int				num_philosophers;
}	t_philo_data;

void	*philosopher_routine(void *arg);
int		allocate_resources(t_philosopher **philosophers,
			pthread_mutex_t **forks, int number_of_philosophers);
void	init_philosopher(t_philosopher *philosopher,
			t_philo_data *data, int id);
void	init_mutexes(pthread_mutex_t *forks, int number_of_philosophers);
int		parse_arguments(int argc, char **argv, t_params *params);
int		check_philosopher_status(t_philosopher *philosopher, t_params *params);
int		check_meals_completed(t_philosopher *philosophers,
			t_params *params, int num_philos);
int		monitor_philosophers(t_philosopher *philosophers,
			t_params *params, int num_philos);
void	start_philosopher_threads(t_philosopher *philosophers,
			t_philo_data *data, int number_of_philosophers);
void	clean_up_resources(t_philosopher *philosophers, pthread_mutex_t *forks,
			int number_of_philosophers);
long	get_time_in_ms(void);
void	eat(t_philosopher *phil);
void	take_forks(t_philosopher *phil);

void	increment_meals_eaten(t_philosopher *phil);
void	release_forks(t_philosopher *phil);
int		parse_required_arguments(int argc, char **argv, t_params *params);
int		parse_optional_meal_argument(int argc, char **argv, t_params *params);
int		parse_arguments(int argc, char **argv, t_params *params);
int		ft_atoi(char *str);
int		get_meals_eaten(t_philosopher *phil);
int		is_valid_integer(const char *str);
int		ft_isdigit(char c);
int		is_numeric_string(char *str);
void	print_status(t_philosopher *phil, const char *status);
void	set_simulation_ended(t_params *params, int ended);
int		get_simulation_ended(t_params *params);

#endif
