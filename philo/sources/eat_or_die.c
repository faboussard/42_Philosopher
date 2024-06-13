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

static int	philosopher_dead(t_philo *philo, size_t time_to_die)
{
	pthread_mutex_lock(&philo->meal_lock);
	if (get_time_in_ms() - philo->time_last_meal >= time_to_die)
		return (pthread_mutex_unlock(&philo->meal_lock), 1);
	pthread_mutex_unlock(&philo->meal_lock);
	return (0);
}

static int	end_dinner(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->end_dinner_mutex);
	if (philo->table->end_dinner == 1)
		return (pthread_mutex_unlock(&philo->table->end_dinner_mutex), 1);
	pthread_mutex_unlock(&philo->table->end_dinner_mutex);
	return (0);
}


int	check_if_dead(t_philo *philos)
{
	size_t	i;

	i = 0;
	while (i < philos->table->num_of_philos)
	{
		if (end_dinner(&philos[i]))
			return (1);
		if (philosopher_dead(&philos[i], philos[i].time_to_die))
		{
			print_msg(&philos[i], "died", 1);
			return (1);
		}
		i++;
	}
	return (0);
}