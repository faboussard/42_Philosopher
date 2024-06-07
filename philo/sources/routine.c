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

static void	until_you_die(t_philo *philo)
{
	while (true)
	{
		if (eat(philo) == 0)
			return ;
		if (is_dead(philo))
			return ;
		print_msg(philo, "is sleeping");
		if (is_dead(philo))
			return ;
		ft_usleep(philo->time_to_sleep);
		if (is_dead(philo))
			return ;
		print_msg(philo, "is thinking");
	}
}

static void	only_x_meals(t_philo *philo)
{
	while (true)
	{
		pthread_mutex_lock(&philo->number_of_meals_mutex);
		if (is_dead(philo))
		{
			pthread_mutex_unlock(&philo->number_of_meals_mutex);
			return;
		}
		if (philo->number_of_meals == 0)
		{
			pthread_mutex_unlock(&philo->number_of_meals_mutex);
			return ;
		}
		philo->number_of_meals--;
		pthread_mutex_unlock(&philo->number_of_meals_mutex);
		if (is_dead(philo))
			return ;
		if (eat(philo) == 0)
			return ;
		if (is_dead(philo))
			return ;
		print_msg(philo, "is sleeping");
		ft_usleep(philo->time_to_sleep);
		if (is_dead(philo))
			return ;
		print_msg(philo, "is thinking");
	}
}

void	*routine(void *pointer)
{
	t_philo	*philo;
	bool	has_meals;

	philo = (t_philo *)pointer;
	wait_threads(philo->table);
//	pthread_mutex_lock(&philo->table->start_time_mutex);
	philo->table->start_time = get_time_in_ms();
//	pthread_mutex_unlock(&philo->table->start_time_mutex);
	if (philo->id % 2 == 0)
		ft_usleep(philo->time_to_eat / 2);
	pthread_mutex_lock(&philo->number_of_meals_mutex);
	has_meals = philo->number_of_meals > 0;
	pthread_mutex_unlock(&philo->number_of_meals_mutex);
	if (has_meals)
		only_x_meals(philo);
	else
		until_you_die(philo);
	return (pointer);
}

void	launch_party(t_table *table)
{
	if (table->num_of_philos == 1)
	{
		table->start_time = get_time_in_ms();
		printf("0 1 has taken a fork\n");
		ft_usleep(table->philo->time_to_die);
		printf("%ld 1 died\n", get_time_in_ms() - table->start_time);
		return ;
	}
	if (!create_threads(table))
		return ;
	terminate_threads(table, table->num_of_philos);
}
