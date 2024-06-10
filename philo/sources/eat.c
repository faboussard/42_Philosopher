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

//static void	get_first_and_second_fork(t_philo *philo, t_mutex **first_fork,
//		t_mutex **second_fork)
//{
//		(*first_fork) = philo->r_fork_mutex;
//		(*second_fork) = philo->l_fork_mutex;
//}

int	eat(t_philo *philo)
{
//	t_mutex	*first_fork;
//	t_mutex	*second_fork;

//	get_first_and_second_fork(philo, &first_fork, &second_fork);
	pthread_mutex_lock(philo->r_fork_mutex);
	if (dead_loop(philo) == 1)
	{
		pthread_mutex_unlock(philo->r_fork_mutex);
		return 0;
	}
	print_msg(philo, "has taken a fork");
	pthread_mutex_lock(philo->l_fork_mutex);
	if (dead_loop(philo) == 1)
	{
		pthread_mutex_unlock(philo->l_fork_mutex);
		pthread_mutex_unlock(philo->r_fork_mutex);
		return 0;
	}
	print_msg(philo, "has taken a fork");
	print_msg(philo, "is eating");
	pthread_mutex_lock(&philo->meal_lock);
	if (dead_loop(philo) == 1)
	{
		pthread_mutex_unlock(philo->l_fork_mutex);
		pthread_mutex_unlock(philo->r_fork_mutex);
		return 0;
	}
	philo->time_last_meal = get_time_in_ms();
	pthread_mutex_unlock(&philo->meal_lock);
	ft_usleep(philo->time_to_eat);
	pthread_mutex_unlock(philo->r_fork_mutex);
	pthread_mutex_unlock(philo->l_fork_mutex);
	return (1);
}
