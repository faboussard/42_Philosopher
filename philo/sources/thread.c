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

void	create_threads(t_table *table)
{
	unsigned int	i;
	unsigned int	j;

	j = 0;
	i = 0;
	while (i < table->num_of_philos)
	{
		if (pthread_create(&table->threads[i], NULL, &routine, // remplacer par philo->tid
				(void *)&table->philo[i]) != 0)
		{
			ft_putendl_fd("Failed to create thread", STDERR_FILENO);
			while (j < i)
			{
				if (pthread_join(table->threads[j++], NULL) != 0)
					ft_putendl_fd("Failed to liberate thread", STDERR_FILENO); // ajouter quel thread a plante
			}
			return ;
		}
		i++;
	}
	pthread_mutex_lock(&table->threads_created_mutex);
	table->threads_created = true;
	pthread_mutex_unlock(&table->threads_created_mutex);
}

void	terminate_threads(t_table *table)
{
	unsigned int	i;

	i = 0;
	while (i < table->num_of_philos)
	{
		if (pthread_join(table->threads[i], NULL) != 0)
			ft_putendl_fd("Failed to liberate thread", STDERR_FILENO);
		i++;
	}
}
