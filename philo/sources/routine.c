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

int eat(t_philo *philo);

bool is_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->death_detected_mutex);
	pthread_mutex_lock(&philo->table->philo->time_to_die_mutex);
	pthread_mutex_lock(&philo->last_meal_mutex);
	if (!philo->table->dead_detected && (get_time_in_ms() - philo->time_last_meal) >= (get_time_in_ms() - philo->time_to_die))
	{
		printf("LAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAa\n");
		philo->table->dead_detected = true;
		printf("%ld %d is dead\n", get_time_in_ms() - philo->table->start_time, philo->id + 1);
		pthread_mutex_unlock(&philo->last_meal_mutex);
		pthread_mutex_unlock(&philo->table->philo->time_to_die_mutex);
		pthread_mutex_unlock(&philo->table->death_detected_mutex);
		return (true);
	}
	pthread_mutex_unlock(&philo->last_meal_mutex);
	pthread_mutex_unlock(&philo->table->philo->time_to_die_mutex);
	pthread_mutex_unlock(&philo->table->death_detected_mutex);
	return (false);
}

void print_msg(t_philo *philo, char *msg)
{
	pthread_mutex_lock(&philo->last_meal_mutex);
	printf("last meal %ld %d\n", get_time_in_ms() - philo->time_last_meal, philo->id + 1);
	printf("time to die %ld %d\n", philo->time_to_die, philo->id + 1);
	pthread_mutex_unlock(&philo->last_meal_mutex);
	if (!is_dead(philo))
	{
		pthread_mutex_lock(&philo->table->print_mutex);
		printf("%ld %d %s\n", get_time_in_ms() - philo->table->start_time, philo->id + 1, msg);
		pthread_mutex_unlock(&philo->table->print_mutex);
	}
}

void *routine(void *pointer)
{
	t_philo *philo;

	philo = (t_philo *) pointer;
	wait_threads(philo->table);
	philo->table->start_time = get_time_in_ms();
//	while (42)
//	{
		if (philo->id % 2 == 0)
			ft_usleep(1);
		if (eat(philo) == 0)
			return (pointer);
//		printf("%d\n", 	philo->table->dead_detected);
		print_msg(philo, "is sleeping");
//	printf("%d\n", 	philo->table->dead_detected);
		ft_usleep(philo->time_to_sleep);
//	printf("%d\n", 	philo->table->dead_detected);
		print_msg(philo, "is thinking");
//	}
	return (pointer);
}

int eat(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork_mutex);
	if (is_dead(philo))
	{
		pthread_mutex_unlock(philo->r_fork_mutex);
		return(0);
	}
	print_msg(philo, "has taken a fork");
	philo->has_taken_a_fork = true;
	pthread_mutex_lock(philo->l_fork_mutex);
	if (is_dead(philo))
	{
		pthread_mutex_unlock(philo->l_fork_mutex);
		pthread_mutex_unlock(philo->r_fork_mutex);
		return(0);
	}
	philo->has_taken_a_fork = true;
	print_msg(philo, "has taken a fork");
	print_msg(philo, "is eating");
	pthread_mutex_lock(&philo->last_meal_mutex);
	philo->time_last_meal = get_time_in_ms();
	pthread_mutex_unlock(&philo->last_meal_mutex);
	ft_usleep(philo->time_to_eat);
	pthread_mutex_unlock(philo->r_fork_mutex);
	pthread_mutex_unlock(philo->l_fork_mutex);
	return (1);
}

void launch_party(t_table *table)
{
	if (table->num_of_philos == 1)
	{
		table->start_time = get_time_in_ms();
		printf("%ld %d is dead\n", get_time_in_ms() - table->start_time, table->philo->id + 1);
		return ;
	}
	create_threads(table);
	terminate_threads(table);
}