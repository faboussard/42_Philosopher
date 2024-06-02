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

/*
 * routine : le nombre de meals pris augmente.
 * tant que time to eat, le philosopher mange .
 * if time to eat = 0 , le philosopher pense.
 * if time to think = 0, le philosophe remange.
 */

void repeat()
{
	return ;
}
void *routine(void *pointer)
{
	t_philo *philo;

	philo = (t_philo *)pointer;
	if (philo->id % 2 == 0)
		ft_usleep(1);
	eat(philo);
//	sleep(philo);
//	think(philo);
    repeat();
	return (pointer);
}

bool is_dead(t_philo *philo)
{
	if (current_time() - philo->time_to_die <= 0)
	{
		philo->dead_flag = true;
		pthread_mutex_unlock(philo->fork_mutex);
		return (true); ;
	}
	return (false);
}

void eat(t_philo *philo)
{
//	if (is_dead(philo))
//		return ;
	pthread_mutex_lock(philo->fork_mutex);
	philo->has_taken_a_fork = true;
	printf("%ld %d has taken a fork\n", current_time(), philo->id);
	philo->time_last_meal = current_time();
	printf("%ld %d is eating\n", current_time(), philo->id);
	ft_usleep(philo->time_to_eat);
	pthread_mutex_unlock(philo->fork_mutex);
}

void launch_party(t_table *table)
{
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