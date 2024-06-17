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

int	init_mutex(t_table *table)
{
	int	i;

	i = 0;
	if (pthread_mutex_init(&table->print_mutex, NULL) != 0)
		return (0);
	if (pthread_mutex_init(&table->death_detected_mutex, NULL) != 0)
		return (0);
	if (pthread_mutex_init(&table->end_dinner_mutex, NULL) != 0)
		return (0);
	while (i < table->num_of_philos)
	{
		if (pthread_mutex_init(&table->philo[i].time_last_meal_lock, NULL) != 0)
			return (0);
		if (pthread_mutex_init(&table->philo[i].number_of_meals_mutex,
				NULL) != 0)
			return (0);
		if (pthread_mutex_init(&table->philo[i].l_fork_mutex, NULL) != 0)
			return (0);
		i++;
	}
	return (1);
}

void	destroy_mutex(t_table *table)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&table->print_mutex);
	pthread_mutex_destroy(&table->death_detected_mutex);
	pthread_mutex_destroy(&table->end_dinner_mutex);
	while (i < table->num_of_philos)
	{
		pthread_mutex_destroy(&table->philo[i].number_of_meals_mutex);
		pthread_mutex_destroy(&table->philo[i].time_last_meal_lock);
		pthread_mutex_destroy(&table->philo[i].l_fork_mutex);
		pthread_mutex_destroy(table->philo[i].r_fork_mutex);
		i++;
	}
}
