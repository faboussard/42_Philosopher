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

bool is_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->death_mutex);
	if (!philo->table->dead_detected && (get_time_in_ms() - philo->time_last_meal) >= philo->time_to_die)
	{
		philo->table->dead_detected = true;
		printf("%ld %d is dead\n", get_time_in_ms() - philo->table->start_time, philo->id + 1);
		return (true);
	}
	pthread_mutex_unlock(&philo->table->death_mutex);
	return (false);
}

void *routine(void *pointer)
{
	t_philo *philo;

	philo = (t_philo *) pointer;
//	wait_threads(philo->table);
//	philo->table->start_time = get_time_in_ms();
	if (is_dead(philo))
		exit(0);
	if (philo->id % 2 == 0)
		ft_usleep(1);
	eat(philo);
	if (is_dead(philo))
		exit(0);
	printf("%ld %d is sleeping\n", get_time_in_ms() - philo->table->start_time, philo->id + 1);
	ft_usleep(philo->time_to_sleep);
	printf("%ld %d is thinking\n", get_time_in_ms() - philo->table->start_time, philo->id + 1);
	if (is_dead(philo))
		exit(0);
	return (pointer);
}

void eat(t_philo *philo)
{
	if (is_dead(philo))
		exit(0);
	if (philo->table->dead_detected)
		return;
	pthread_mutex_lock(philo->r_fork_mutex);
	printf("%ld %d has taken a fork\n", get_time_in_ms() - philo->table->start_time, philo->id + 1);
	philo->has_taken_a_fork = true;
	ft_usleep(1);
	if (is_dead(philo))
		exit(0);
	if (philo->table->dead_detected)
	{
		pthread_mutex_unlock(philo->r_fork_mutex);
		return;
	}
	pthread_mutex_lock(philo->l_fork_mutex);
	philo->has_taken_a_fork = true;
	printf("%ld %d has taken a fork\n", get_time_in_ms() - philo->table->start_time, philo->id + 1);
	philo->time_last_meal = get_time_in_ms();
	printf("%ld %d is eating\n", get_time_in_ms() - philo->table->start_time, philo->id + 1);
	ft_usleep(philo->time_to_eat);
	pthread_mutex_unlock(philo->r_fork_mutex);
	pthread_mutex_unlock(philo->l_fork_mutex);
}

void launch_party(t_table *table)
{
	table->start_time = get_time_in_ms();
	if (table->num_of_philos == 1)
	{
		printf("%ld %d is dead\n", get_time_in_ms() - table->start_time, table->philo->id + 1);
		return;
	}
	create_threads(table);
	terminate_threads(table);
}

int main(int argc, char **argv)
{
	t_table *table;

	table = NULL;
	if ((argc != 5 && argc != 6) || !valid_args(argc, argv))
		error_free_exit(table, "arguments are not valid.", EXIT_FAILURE);
	init_table(argv, &table);
	init_philos(table, argv);
	init_mutex(table);
	launch_party(table);
	destroy_mutex(table);
	free_table(table);
	return (0);
}