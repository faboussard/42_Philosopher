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
		if (table->dead_detected)
			return ;
		i++;
	}
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