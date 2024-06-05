/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faboussa <faboussa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 14:04:26 by faboussa          #+#    #+#             */
/*   Updated: 2024/05/30 11:15:29 by faboussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	get_first_and_second_fork(t_philo *philo, t_mutex **first_fork,
		t_mutex **second_fork)
{
	if (philo->id % 2 == 0)
	{
		(*first_fork) = philo->r_fork_mutex;
		(*second_fork) = philo->l_fork_mutex;
	}
	else
	{
		(*first_fork) = philo->l_fork_mutex;
		(*second_fork) = philo->r_fork_mutex;
	}
}

static bool	take_forks(t_philo *philo)
{
	t_mutex	*first_fork;
	t_mutex	*second_fork;

	get_first_and_second_fork(philo, &first_fork, &second_fork);
	pthread_mutex_lock(first_fork);
	if (is_dead(philo))
	{
		pthread_mutex_unlock(first_fork);
		return (false);
	}
	print_msg(philo, "has taken a fork");
	pthread_mutex_lock(second_fork);
	if (is_dead(philo))
	{
		pthread_mutex_unlock(second_fork);
		pthread_mutex_unlock(first_fork);
		return (false);
	}
	pthread_mutex_unlock(second_fork);
	pthread_mutex_unlock(first_fork);
	print_msg(philo, "has taken a fork");
	return (true);
}

static void	release_forks(t_philo *philo)
{
	t_mutex	*first_fork;
	t_mutex	*second_fork;

	if (philo->id % 2 == 0)
	{
		first_fork = philo->r_fork_mutex;
		second_fork = philo->l_fork_mutex;
	}
	else
	{
		first_fork = philo->l_fork_mutex;
		second_fork = philo->r_fork_mutex;
	}
	pthread_mutex_unlock(second_fork);
	pthread_mutex_unlock(first_fork);
}

int	eat(t_philo *philo)
{
	if (!take_forks(philo))
		return (0);
	print_msg(philo, "is eating");
	pthread_mutex_lock(&philo->last_meal_mutex);
	philo->time_last_meal = get_time_in_ms();
	ft_usleep(philo->time_to_eat);
	pthread_mutex_unlock(&philo->last_meal_mutex);
	release_forks(philo);
	return (1);
}
