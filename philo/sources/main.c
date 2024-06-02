/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faboussa <faboussa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 14:04:26 by faboussa          #+#    #+#             */
/*   Updated: 2024/05/30 11:15:29 by faboussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void eat(t_philo *philo);

void is_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->death_mutex);
	if (!philo->table->dead_detected && (current_time() - philo->time_last_meal) >= philo->time_to_die)
	{
		philo->table->dead_detected = true;
		printf("%ld %d is dead\n", current_time(), philo->id);
	}
	pthread_mutex_unlock(&philo->table->death_mutex);
}

void *routine(void *pointer)
{
	t_philo *philo;

	philo = (t_philo *)pointer;
	while (!philo->table->dead_detected)
	{
		is_dead(philo);
		if (philo->id % 2 == 0)
			ft_usleep(1);
		eat(philo);
		is_dead(philo);
		printf("%ld %d is sleeping\n", current_time(), philo->id);
		ft_usleep(philo->time_to_sleep);
		is_dead(philo);
		printf("%ld %d is thinking\n", current_time(), philo->id);
		is_dead(philo);
		ft_usleep(1);
	}
	return (pointer);
}



void eat(t_philo *philo)
{
	is_dead(philo);
	pthread_mutex_lock(philo->r_fork_mutex);
	printf("%ld %d has taken a fork\n", current_time(), philo->id);
	philo->has_taken_a_fork = true;
	ft_usleep(1);
	pthread_mutex_lock(philo->l_fork_mutex);
	is_dead(philo);
	philo->has_taken_a_fork = true;
	printf("%ld %d has taken a fork\n", current_time(), philo->id);
	philo->time_last_meal = current_time();
	printf("%ld %d is eating\n", current_time(), philo->id);
	ft_usleep(philo->time_to_eat);
	pthread_mutex_unlock(philo->r_fork_mutex);
	pthread_mutex_unlock(philo->l_fork_mutex);
}

void launch_party(t_table *table)
{
	if (table->num_of_philos == 1)
	{
		printf("%ld %d is dead\n", current_time(), table->philo->id);
		return ;
	}
	create_threads(table);
	terminate_threads(table);
}

int main(int argc, char **argv)
{
	t_table *table;

	table = NULL;
	if ((argc != 5 && argc != 6) || !valid_args(argc, argv))
		exit_with_error(table, "arguments are not valid.", EXIT_FAILURE);
	init_table(argv, &table);
	init_philos(table, argv);
	init_mutex(table);
	launch_party(table);
	destroy_mutex(table);
	free_table(table);
	return (0);
}