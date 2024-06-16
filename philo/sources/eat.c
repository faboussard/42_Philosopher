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

//static void choose_fork(t_philo *philo, pthread_mutex_t **first_fork, pthread_mutex_t **left_fork)
//{
//	if (philo->l_fork_mutex < philo->r_fork_mutex)
//	{
//		(*first_fork) = philo->l_fork_mutex;
//		(*left_fork) = philo->r_fork_mutex;
//	}
//	else
//	{
//		(*first_fork) = philo->r_fork_mutex;
//		(*left_fork) = philo->l_fork_mutex;
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
//static void release_forks(t_philo *philo, pthread_mutex_t *first_fork, pthread_mutex_t *left_fork)
//{
//	philo->first_fork = 0;
//	philo->left_fork = 0;
//	pthread_mutex_unlock(left_fork);
//	pthread_mutex_unlock(first_fork);
//}
//
//void eat(t_philo *philo, int i)
//{
//	pthread_mutex_t *first_fork;
//	pthread_mutex_t *left_fork;
//
//	choose_fork(philo, &first_fork, &left_fork);
//	pthread_mutex_lock(first_fork);
//	philo->first_fork = 1;
//	if (!print_msg(philo, "has taken a fork", i))
//	{
//		philo->first_fork = 0;
//		pthread_mutex_unlock(first_fork);
//		return;
//	}
//	pthread_mutex_lock(left_fork);
//	philo->left_fork = 1;
//	if (!print_msg(philo, "has taken a fork", i))
//	{
//		release_forks(philo, first_fork, left_fork);
//		return;
//	}
//	if (!print_msg(philo, "is eating", i))
//	{
//		release_forks(philo, first_fork, left_fork);
//		return;
//	}
//	update_time_last_meal(philo);
//	ft_usleep(philo->time_to_eat, philo);
//	release_forks(philo, first_fork, left_fork);
//}

static void release_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->l_fork_mutex);
	if (philo->left_fork == TAKEN)
		philo->left_fork = FREE;
	pthread_mutex_unlock(&philo->l_fork_mutex);
	pthread_mutex_lock(philo->r_fork_mutex);
	if (*(philo->right_fork) == TAKEN)
		*(philo->right_fork) = FREE;
	pthread_mutex_unlock(philo->r_fork_mutex);
	philo->nbr_forks = 0;
}

static int	take_left_fork(t_philo *philo, int i)
{
	pthread_mutex_lock(&philo->l_fork_mutex);
	if (philo->left_fork == FREE)
	{
		philo->left_fork = TAKEN;
		if (!print_msg(philo, MSG_FORK, i))
		{
			pthread_mutex_unlock(&philo->l_fork_mutex);
			return 0;
		}
		philo->nbr_forks++;
	}
	pthread_mutex_unlock(&philo->l_fork_mutex);
	return 1;
}

static int	take_right_fork(t_philo *philo, int i)
{
	pthread_mutex_lock(philo->r_fork_mutex);
	if (*(philo->right_fork) == FREE)
	{
		*(philo->right_fork) = TAKEN;
		if (!print_msg(philo, MSG_FORK, i))
		{
			pthread_mutex_unlock(philo->r_fork_mutex);
			return 0;
		}
		philo->nbr_forks++;
	}
	pthread_mutex_unlock(philo->r_fork_mutex);
	return 1;
}

static int take_forks(t_philo *philo, int i)
{
	if (!take_left_fork(philo, i))
		return (2);
	if (!take_right_fork(philo, i))
		return (2);
	if (philo->nbr_forks == 2)
		return (SUCCESS);
	else
		return (FAILURE);
}

void	eat(t_philo *philo, int i)
{
	while (take_forks(philo, i) == FAILURE)
		usleep(philo->table->num_of_philos * 10);
	if (!print_msg(philo, MSG_EAT, i))
		return ;
	pthread_mutex_lock(&philo->meal_lock);
	philo->time_last_meal = get_time_in_ms();
	pthread_mutex_unlock(&philo->meal_lock);
	ft_usleep(philo->time_to_eat, philo);
	release_forks(philo);
}
