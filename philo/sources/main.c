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

void *routine(void *pointer)
{
	t_philo *philo;

	philo = (t_philo *)pointer;
	if (philo->id % 2 == 0)
		ft_usleep(1);
	eat(philo);
//	think(philo);
//	sleep(philo);
	return (pointer);
}

void eat(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork_mutex);
	philo->has_taken_a_fork = true;
	printf("%ld %d has taken a fork\n", current_time(), philo->id);
	pthread_mutex_lock(philo->left_fork_mutex);
	philo->has_taken_a_fork = true;
//	pthread_mutex_lock(philo->print_mutex);
	printf("%ld %d has taken a fork\n", current_time(), philo->id);
	printf("%ld %d is eating\n", current_time(), philo->id);
//	pthread_mutex_unlock(philo->print_mutex);
	pthread_mutex_unlock(philo->right_fork_mutex);
	pthread_mutex_unlock(philo->left_fork_mutex);
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