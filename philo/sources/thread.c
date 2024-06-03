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

void wait_threads(t_table *table)
{
	// Protéger l'accès à threads_created avec un mutex
	pthread_mutex_lock(&table->threads_created_mutex);
	while (table->threads_created == false)
	{
		;
		pthread_mutex_unlock(&table->threads_created_mutex);
		// Eviter un spinlock trop agressif
		usleep(1);
		pthread_mutex_lock(&table->threads_created_mutex);
	}
	pthread_mutex_unlock(&table->threads_created_mutex);

	table->start_time = get_time_in_ms();
}

void create_threads(t_table *table)
{
	unsigned int philos;
	unsigned int i;

	i = 0;
	philos = table->num_of_philos;
	pthread_t th[philos];
	while (i < philos)
	{
		if (pthread_create(th + i, NULL, &routine, (void *)&table->philo[i]) != 0)
		{
			ft_putendl_fd("Failed to create thread", STDERR_FILENO);
			return;
		}
		i++;
	}
//	pthread_mutex_lock(&table->threads_created_mutex);
//	table->threads_created = true;
//	pthread_mutex_unlock(&table->threads_created_mutex);
}

void terminate_threads(t_table *table)
{
	unsigned int philos;
	unsigned int i;

	i = 0;
	philos = table->num_of_philos;
	pthread_t th[philos];

	while (i < philos)
	{
		if (pthread_join(th[i], NULL) != 0)
		{
			ft_putendl_fd("Failed to liberate thread", STDERR_FILENO);
			return;
		}
		i++;
	}
}