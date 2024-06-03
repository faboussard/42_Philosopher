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
	bool dead = false;
	pthread_mutex_lock(&philo->table->death_detected_mutex);
	pthread_mutex_lock(&philo->last_meal_mutex);

	size_t time_since_last_meal = get_time_in_ms() - philo->time_last_meal;
	if (!philo->table->dead_detected && time_since_last_meal >= philo->time_to_die)
	{
		philo->table->dead_detected = true;
		dead = true;
		printf("%ld %d is dead\n", get_time_in_ms() - philo->table->start_time, philo->id + 1);
	}

	pthread_mutex_unlock(&philo->last_meal_mutex);
	pthread_mutex_unlock(&philo->table->death_detected_mutex);
	return dead;
}


void print_msg(t_philo *philo, char *msg)
{
	pthread_mutex_lock(&philo->table->death_detected_mutex);
	if (!philo->table->dead_detected)
	{
		pthread_mutex_lock(&philo->table->print_mutex);
		pthread_mutex_unlock(&philo->table->death_detected_mutex); // Déverrouiller avant d'imprimer pour éviter la contention
		printf("%ld %d %s\n", get_time_in_ms() - philo->table->start_time, philo->id + 1, msg);
		pthread_mutex_unlock(&philo->table->print_mutex);
	}
	else
	{
		pthread_mutex_unlock(&philo->table->death_detected_mutex);
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
		pthread_mutex_lock(&philo->table->death_detected_mutex);
		if (philo->table->dead_detected == true)
		{
			pthread_mutex_unlock(&philo->table->death_detected_mutex);
			return (pointer);
		}
		pthread_mutex_unlock(&philo->table->death_detected_mutex);
		if (eat(philo) == 0)
			return (pointer);
		printf("%d\n", 	philo->table->dead_detected);
		print_msg(philo, "is sleeping");
	pthread_mutex_lock(&philo->table->death_detected_mutex);
	if (philo->table->dead_detected == true)
	{
		pthread_mutex_unlock(&philo->table->death_detected_mutex);
		return (pointer);
	}
	pthread_mutex_unlock(&philo->table->death_detected_mutex);
	printf("%d\n", 	philo->table->dead_detected);
		ft_usleep(philo->time_to_sleep);
	printf("%d\n", 	philo->table->dead_detected);
		print_msg(philo, "is thinking");
	pthread_mutex_lock(&philo->table->death_detected_mutex);
	if (philo->table->dead_detected == true)
	{
		pthread_mutex_unlock(&philo->table->death_detected_mutex);
		return (pointer);
	}
	pthread_mutex_unlock(&philo->table->death_detected_mutex);
//	}
	return (pointer);
}

int eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->death_detected_mutex);
	if (philo->table->dead_detected == true)
	{
		pthread_mutex_unlock(&philo->table->death_detected_mutex);
		return (0);
	}
	pthread_mutex_unlock(&philo->table->death_detected_mutex);
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
	ft_usleep(philo->time_to_eat);
	pthread_mutex_unlock(&philo->last_meal_mutex);
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