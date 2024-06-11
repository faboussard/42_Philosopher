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
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	ft_usleep(size_t ms, t_philo *philosopher)
{
	size_t	start_time;

	start_time = get_time_in_ms();
	usleep(ms * 1000 * 0.9);
	while ((get_time_in_ms() - start_time) < ms
	       && !dead_loop(philosopher))
	{
		usleep(500);
	}
	return (0);
}

int print_msg(t_philo *philo, char *msg)
{
	size_t	time;

	time = get_time_in_ms() - philo->table->start_time;
	pthread_mutex_lock(&philo->table->death_detected_mutex);
	pthread_mutex_lock(&philo->table->print_mutex);
	if (philo->table->dead_detected == 1)
	{
		pthread_mutex_unlock(&philo->table->print_mutex);
		pthread_mutex_unlock(&philo->table->death_detected_mutex);
		return 0;
	}
	printf("%ld %d %s\n", time, philo->id + 1, msg);
	if (ft_strcmp(msg, "died") == 0)
		philo->table->dead_detected = 1;
	pthread_mutex_unlock(&philo->table->print_mutex);
	pthread_mutex_unlock(&philo->table->death_detected_mutex);
	return 1;
}

