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

void print_msg(t_philo *philo, char *msg)
{
	pthread_mutex_lock(&philo->table->print_mutex);
	if (dead_loop(philo) == 1)
	{
		pthread_mutex_unlock(&philo->table->print_mutex);
		return;
	}
	printf("%ld %d %s\n", get_time_in_ms() - philo->table->start_time,
		   philo->id + 1, msg);
	pthread_mutex_unlock(&philo->table->print_mutex);
}

