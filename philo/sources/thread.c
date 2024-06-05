/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faboussa <faboussa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 14:04:26 by faboussa          #+#    #+#             */
/*   Updated: 2024/05/28 14:04:26 by faboussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	wait_threads(t_table *table)
{
	pthread_mutex_lock(&table->threads_created_mutex);
	while (table->threads_created == false)
	{
		pthread_mutex_unlock(&table->threads_created_mutex);
		pthread_mutex_lock(&table->threads_created_mutex);
	}
	pthread_mutex_unlock(&table->threads_created_mutex);
}

int create_threads(t_table *table)
{
	unsigned int	i;
	bool			flag;

	i = 0;
	flag = 0;
	while (i < table->num_of_philos)
	{
		if (pthread_create(&table->threads[i], NULL, &routine,
				(void *)&table->philo[i]) != 0)
		{
			flag = 1;
			printf("Failed to create thread %u", i);
			terminate_threads(table, i);
		}
		i++;
	}
	if (flag == 1)
		return (0);
	pthread_mutex_lock(&table->threads_created_mutex);
	table->threads_created = true;
	pthread_mutex_unlock(&table->threads_created_mutex);
	return (1);
}

int terminate_threads(t_table *table, unsigned int number_of_philos)
{
	bool			flag;
	unsigned int	i;

	i = 0;
	flag = 0;
	while (i < number_of_philos)
	{
		if (pthread_join(table->threads[i], NULL) != 0)
		{
			flag = 1;
			printf("Failed to liberate thread %u", i);
		}
		i++;
	}
	if (flag == 1)
		return (0);
	return (1);
}
