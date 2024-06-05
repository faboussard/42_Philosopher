/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faboussa <faboussa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 14:04:26 by faboussa          #+#    #+#             */
/*   Updated: 2024/06/03 16:55:17 by faboussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_forks_mutex(t_table *table)
{
	unsigned int	i;

	i = 0;
	table->forks = malloc(sizeof(pthread_mutex_t)
			* table->num_of_philos);
	if (table->forks == NULL)
		return (0);
	while (i < table->num_of_philos)
		pthread_mutex_init(&table->forks[i++], NULL);
	i = 0;
	while (i < table->num_of_philos)
	{
		table->philo[i].l_fork_mutex = &table->forks[i];
		table->philo[i].r_fork_mutex = &table->forks[(i + 1)
			% table->num_of_philos];
		i++;
	}
	return (1);
}

static void	destroy_philo_mutexes(const t_table *table, unsigned int i)
{
	while (i < table->num_of_philos)
	{
		pthread_mutex_destroy(&table->philo[i].number_of_meals_mutex);
		pthread_mutex_destroy(&table->philo[i].last_meal_mutex);
		pthread_mutex_destroy(&table->forks[i]);
		i++;
	}
}

static void	destroy_table_mutexes(t_table *table)
{
	pthread_mutex_destroy(&table->threads_created_mutex);
	pthread_mutex_destroy(&table->start_time_mutex);
	pthread_mutex_destroy(&table->print_mutex);
	pthread_mutex_destroy(&table->print_dead_mutex);
	pthread_mutex_destroy(&table->death_detected_mutex);
}

int	init_mutex(t_table *table)
{
	unsigned int	i;

	i = 0;
	pthread_mutex_init(&table->threads_created_mutex, NULL);
	pthread_mutex_init(&table->start_time_mutex, NULL);
	pthread_mutex_init(&table->print_mutex, NULL);
	pthread_mutex_init(&table->print_dead_mutex, NULL);
	pthread_mutex_init(&table->death_detected_mutex, NULL);
	if (!init_forks_mutex(table))
	{
		destroy_table_mutexes(table);
		error_free(table, "Error initializing fork mutexes");
		return (0);
	}
	while (i < table->num_of_philos)
	{
		pthread_mutex_init(&table->philo[i].last_meal_mutex, NULL);
		pthread_mutex_init(&table->philo[i].number_of_meals_mutex, NULL);
		i++;
	}
	return (1);
}

void	destroy_mutex(t_table *table)
{
	unsigned int	i;

	i = 0;
	destroy_table_mutexes(table);
	destroy_philo_mutexes(table, i);
}
