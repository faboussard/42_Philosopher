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
	bool dead;
	size_t time_since_last_meal;

	dead = false;
	pthread_mutex_lock(&philo->table->death_detected_mutex);
	if (philo->table->dead_detected)
	{
		pthread_mutex_unlock(&philo->table->death_detected_mutex);
		return (true);
	}
	pthread_mutex_unlock(&philo->table->death_detected_mutex);
	pthread_mutex_lock(&philo->table->death_detected_mutex);
	pthread_mutex_lock(&philo->last_meal_mutex);
	time_since_last_meal = get_time_in_ms() - philo->time_last_meal;
	if (time_since_last_meal >= philo->time_to_die)
	{
		philo->table->dead_detected = true;
		dead = true;
		printf("%ld %d is dead\n", get_time_in_ms() - philo->table->start_time, philo->id + 1);
	}
	pthread_mutex_unlock(&philo->last_meal_mutex);
	pthread_mutex_unlock(&philo->table->death_detected_mutex);
	return (dead);
}

void print_msg(t_philo *philo, char *msg)
{
	pthread_mutex_lock(&philo->table->death_detected_mutex);
	if (!philo->table->dead_detected)
	{
		pthread_mutex_lock(&philo->table->print_mutex);
		pthread_mutex_unlock(&philo->table->death_detected_mutex);
		pthread_mutex_lock(&philo->table->start_time_mutex);
		printf("%ld %d %s\n", get_time_in_ms() - philo->table->start_time, philo->id + 1, msg);
		pthread_mutex_unlock(&philo->table->start_time_mutex);
		pthread_mutex_unlock(&philo->table->print_mutex);
	}
	else
		pthread_mutex_unlock(&philo->table->death_detected_mutex);
}

void until_you_die(t_philo *philo)
{
	while (true)
	{
		if (is_dead(philo))
			return;
		if (eat(philo) == 0)
			return;
		if (is_dead(philo))
			return;
		print_msg(philo, "is sleeping");
		ft_usleep(philo->time_to_sleep);
		if (is_dead(philo))
			return;
		print_msg(philo, "is thinking");
	}
}

void only_x_meals(t_philo *philo)
{
	int i = 0;
	while (i < 5)
	{
//		pthread_mutex_unlock(&philo->number_of_meals_mutex);
		if (is_dead(philo))
			return ;
		if (eat(philo) == 0)
			return;
		if (is_dead(philo))
			return;
		print_msg(philo, "is sleeping");
		ft_usleep(philo->time_to_sleep);
		if (is_dead(philo))
			return;
		print_msg(philo, "is thinking");
//		pthread_mutex_lock(&philo->number_of_meals_mutex);
//		philo->number_of_meals--;
//		pthread_mutex_unlock(&philo->number_of_meals_mutex);
i++;
	}
}


void *routine(void *pointer)
{
	t_philo *philo;
//	bool has_meals;

//	has_meals = 1;
	philo = (t_philo *)pointer;
	wait_threads(philo->table);
	pthread_mutex_lock(&philo->table->start_time_mutex);
	philo->table->start_time = get_time_in_ms();
	pthread_mutex_unlock(&philo->table->start_time_mutex);
	if (philo->id % 2 == 0)
		ft_usleep(1);
//	pthread_mutex_lock(&philo->number_of_meals_mutex);
//	has_meals = philo->number_of_meals > 0;
//	printf("%d\n", has_meals);
//	pthread_mutex_unlock(&philo->number_of_meals_mutex);
//	if (has_meals)
//		only_x_meals(philo);
//	else
until_you_die(philo);
	return (pointer);
}

void get_first_and_second_fork(t_philo *philo, t_mutex **first_fork, t_mutex **second_fork)
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

bool take_forks(t_philo *philo)
{
	t_mutex *first_fork;
	t_mutex *second_fork;

	get_first_and_second_fork(philo, &first_fork, &second_fork);
	pthread_mutex_lock(first_fork);
	if (is_dead(philo))
	{
		pthread_mutex_unlock(first_fork);
		return false;
	}
	print_msg(philo, "has taken a fork");
	pthread_mutex_lock(second_fork);
	if (is_dead(philo))
	{
		pthread_mutex_unlock(second_fork);
		pthread_mutex_unlock(first_fork);
		return false;
	}
	print_msg(philo, "has taken a fork");
	return true;
}

void release_forks(t_philo *philo)
{
	pthread_mutex_t *first_fork, *second_fork;

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


int eat(t_philo *philo)
{
	if (!take_forks(philo))
	{
		return 0;
	}

	print_msg(philo, "is eating");

	pthread_mutex_lock(&philo->last_meal_mutex);
	philo->time_last_meal = get_time_in_ms();
	ft_usleep(philo->time_to_eat);
	pthread_mutex_unlock(&philo->last_meal_mutex);

	release_forks(philo);

	return 1;
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