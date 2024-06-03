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
	while (1)
	{
		pthread_mutex_lock(&table->threads_created_mutex);
//		printf("%d\n", 	table->threads_created);
//		pthread_mutex_lock(&table->threads_created_mutex);
		if (table->threads_created)
		{
//			pthread_mutex_unlock(&table->threads_created_mutex);
			break;
		}
//		pthread_mutex_unlock(&table->threads_created_mutex);
		// Eviter un spinlock trop agressif
		pthread_mutex_unlock(&table->threads_created_mutex);
		usleep(100);  // Attendre 100 microsecondes
	}

}


void create_threads(t_table *table)
{
	unsigned int philos;
	unsigned int i;

	i = 0;
	philos = table->num_of_philos;
	while (i < philos)
	{
		if (pthread_create(&table->threads[i], NULL, &routine, (void *)&table->philo[i]) != 0)
		{
			ft_putendl_fd("Failed to create thread", STDERR_FILENO);
			return ;
		}
		i++;
	}
//	pthread_mutex_lock(&table->threads_created_mutex);
	table->threads_created = true;
//	printf("%d\n", 	table->threads_created);
//	pthread_mutex_unlock(&table->threads_created_mutex);
}

void terminate_threads(t_table *table)
{
	unsigned int philos;
	unsigned int i;

	i = 0;
	philos = table->num_of_philos;
	while (i < philos)
	{
		if (pthread_join(table->threads[i], NULL) != 0)
		{
			ft_putendl_fd("Failed to liberate thread", STDERR_FILENO);
			return;
		}
		i++;
	}
}