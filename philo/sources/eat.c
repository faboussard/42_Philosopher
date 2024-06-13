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

//static void choose_fork(t_philo *philo, pthread_mutex_t **first_fork, pthread_mutex_t **second_fork)
//{
//	if (philo->l_fork_mutex < philo->r_fork_mutex)
//	{
//		(*first_fork) = philo->l_fork_mutex;
//		(*second_fork) = philo->r_fork_mutex;
//	}
//	else
//	{
//		(*first_fork) = philo->r_fork_mutex;
//		(*second_fork) = philo->l_fork_mutex;
//	}
//}
//
//void update_time_last_meal(t_philo *philo)
//{
//	pthread_mutex_lock(&philo->meal_lock);
//	philo->time_last_meal = get_time_in_ms();
//	pthread_mutex_unlock(&philo->meal_lock);
//}
//
//static void release_forks(t_philo *philo, pthread_mutex_t *first_fork, pthread_mutex_t *second_fork)
//{
//	philo->first_fork = 0;
//	philo->second_fork = 0;
//	pthread_mutex_unlock(second_fork);
//	pthread_mutex_unlock(first_fork);
//}
//
//void eat(t_philo *philo, int i)
//{
//	pthread_mutex_t *first_fork;
//	pthread_mutex_t *second_fork;
//
//	choose_fork(philo, &first_fork, &second_fork);
//	pthread_mutex_lock(first_fork);
//	philo->first_fork = 1;
//	if (!print_msg(philo, "has taken a fork", i))
//	{
//		philo->first_fork = 0;
//		pthread_mutex_unlock(first_fork);
//		return;
//	}
//	pthread_mutex_lock(second_fork);
//	philo->second_fork = 1;
//	if (!print_msg(philo, "has taken a fork", i))
//	{
//		release_forks(philo, first_fork, second_fork);
//		return;
//	}
//	if (!print_msg(philo, "is eating", i))
//	{
//		release_forks(philo, first_fork, second_fork);
//		return;
//	}
//	update_time_last_meal(philo);
//	ft_usleep(philo->time_to_eat, philo);
//	release_forks(philo, first_fork, second_fork);
//}

void release_forks(t_philo *philo)
{
	philo->first_fork = 0;
	philo->second_fork = 0;
	pthread_mutex_unlock(philo->l_fork_mutex);
	pthread_mutex_unlock(philo->r_fork_mutex);
}

void	eat(t_philo *philo, int i)
{
	pthread_mutex_lock(philo->r_fork_mutex);
	philo->first_fork = 1;
	if (!print_msg(philo, "has taken a fork", i))
	{
		philo->first_fork = 0;
		pthread_mutex_unlock(philo->r_fork_mutex);
		return ;
	}
	pthread_mutex_lock(philo->l_fork_mutex);
	philo->second_fork = 1;
	if (!print_msg(philo, "has taken a fork", i))
	{
		release_forks(philo);
		return ;
	}
	if (!print_msg(philo, "is eating", i))
	{
		release_forks(philo);
		return ;
	}
	pthread_mutex_lock(&philo->meal_lock);
	philo->time_last_meal = get_time_in_ms();
	pthread_mutex_unlock(&philo->meal_lock);
	ft_usleep(philo->time_to_eat, philo);
	release_forks(philo);
}
