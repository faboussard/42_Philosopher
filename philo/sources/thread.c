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

int	philosopher_dead(t_philo *philo, size_t time_to_die)
{
	pthread_mutex_lock(&philo->meal_lock);
	if (get_time_in_ms() - philo->time_last_meal >= time_to_die)
		return (pthread_mutex_unlock(&philo->meal_lock), 1);
	pthread_mutex_unlock(&philo->meal_lock);
	return (0);
}

int	check_if_dead(t_philo *philos)
{
	size_t	i;

	i = 0;
	while (i < philos->table->num_of_philos)
	{
		if (philosopher_dead(&philos[i], philos[i].time_to_die))
		{
			print_msg(&philos[i], "died");
			pthread_mutex_lock(&philos->table->death_detected_mutex);
			philos->table->dead_detected = 1;
			pthread_mutex_unlock(&philos->table->death_detected_mutex);
			return (1);
		}
		i++;
	}
	return (0);
}

void	*monitor(void *pointer)
{
	t_philo	*philos;

	philos = (t_philo *)pointer;
	while (1)
	{
		if (check_if_dead(philos) == 1)
		{
			break;
		}
	}
	return (pointer);
}

int create_threads(t_table *table)
{
	pthread_t	    observer;
	unsigned int	i;
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

int terminate_threads(t_table *table, unsigned int number_of_threads)
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
