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

void	*monitor(void *pointer)
{
	t_philo	*philos;

	philos = (t_philo *)pointer;
	while (1)
	{
		if (check_if_dead(philos) == 1)
		{
			break ;
		}
	}
	return (pointer);
}

int	create_threads(t_table *table)
{
	pthread_t		observer;
	int	i;
	bool			flag;

	i = 0;
	flag = 0;
	if (pthread_create(&observer, NULL, &monitor, table->philo) != 0)
		ft_putendl_fd("Failed to create thread", STDERR_FILENO);
	while (i < table->num_of_philos)
	{
		if (pthread_create(&table->philo[i].tid, NULL, &routine,
				(void *)&table->philo[i]) != 0)
		{
			flag = 1;
			ft_putendl_fd("Failed to create thread", STDERR_FILENO);
			terminate_threads(table, i);
		}
		i++;
	}
	if (pthread_join(observer, NULL) != 0)
		ft_putendl_fd("Failed to liberate observer thread", STDERR_FILENO);
	if (flag == 1)
		return (0);
	return (1);
}

int	terminate_threads(t_table *table, unsigned int number_of_threads)
{
	bool			flag;
	unsigned int	i;

	i = 0;
	flag = 0;
	while (i < number_of_threads)
	{
		if (pthread_join(table->philo[i].tid, NULL) != 0)
		{
			flag = 1;
			ft_putendl_fd("Failed to liberate thread", STDERR_FILENO);
		}
		i++;
	}
	if (flag == 1)
		return (0);
	return (1);
}
