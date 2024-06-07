/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faboussa <faboussa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 15:35:26 by faboussa          #+#    #+#             */
/*   Updated: 2024/05/28 15:35:26 by faboussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t get_time_in_ms(void)
{
	struct timeval tv;

	if (gettimeofday(&tv, NULL) == -1)
		ft_putendl_fd("Gettimeofday returned -1\n", STDERR_FILENO);
	return ((tv.tv_sec * (size_t) 1000) + (tv.tv_usec / 1000));
}

void ft_usleep(size_t time_in_ms)
{
	size_t start_time;

	start_time = get_time_in_ms();
	while ((get_time_in_ms() - start_time) < time_in_ms)
		usleep(time_in_ms / 10);
}

bool another_one_bites_the_dust(t_philo *philo)
{
	bool dead_detected;

	pthread_mutex_lock(&philo->table->death_detected_mutex);
	dead_detected = philo->table->dead_detected;
	pthread_mutex_unlock(&philo->table->death_detected_mutex);
	return dead_detected;
}

bool is_dead(t_philo *philo)
{
	bool dead = false;
	size_t time_since_last_meal;

	if (another_one_bites_the_dust(philo))
		return (true);

	pthread_mutex_lock(&philo->last_meal_mutex);
	if (another_one_bites_the_dust(philo))
		return (true);
	time_since_last_meal = get_time_in_ms() - philo->time_last_meal;
	pthread_mutex_unlock(&philo->last_meal_mutex);

	if (time_since_last_meal >= philo->time_to_die)
	{
		pthread_mutex_lock(&philo->table->death_detected_mutex);
		philo->table->dead_detected = true;
		pthread_mutex_unlock(&philo->table->death_detected_mutex);
		pthread_mutex_lock(&philo->table->print_mutex);
		pthread_mutex_lock(&philo->table->start_time_mutex);
		printf("%ld %d died\n", get_time_in_ms() - philo->table->start_time, philo->id + 1);
		pthread_mutex_unlock(&philo->table->start_time_mutex);
		pthread_mutex_unlock(&philo->table->print_mutex);
	}
	return dead;
}

void print_msg(t_philo *philo, char *msg)
{
	size_t start_time;

	if (is_dead(philo))
		return;
	pthread_mutex_lock(&philo->table->start_time_mutex);

	start_time = philo->table->start_time;
	pthread_mutex_unlock(&philo->table->start_time_mutex);
	if (is_dead(philo))
		return;
	pthread_mutex_lock(&philo->table->print_mutex); // change the prntex mutex toanother in the is dead .
	printf("%ld %d %s\n", get_time_in_ms() - start_time,
		   philo->id + 1, msg);
	pthread_mutex_unlock(&philo->table->print_mutex);
}

