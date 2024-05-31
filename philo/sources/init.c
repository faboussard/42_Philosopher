/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faboussa <faboussa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 14:04:26 by faboussa          #+#    #+#             */
/*   Updated: 2024/05/28 14:04:26 by faboussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void init_table(char *const *argv, t_table **table)
{
	*table = ft_calloc(1, sizeof(t_table));
	if (!*table)
		exit_with_error(NULL, "Malloc error\n", ENOMEM);
	ft_bzero(*table, sizeof(t_table));
	(*table)->num_of_philos = ft_atoi(argv[1]);
}

int	valid_args(int argc, char **argv)
{
	size_t	i;
	int	nb_arg;

	i = 0;
	nb_arg = argc - 1;
	while (nb_arg > 0)
	{
		if (ft_atol(argv[nb_arg]) < 0 || ft_atol(argv[nb_arg]) > INT_MAX || ft_atol(argv[nb_arg]) < INT_MIN)
			return (false);
		while (argv[nb_arg][i])
		{
			if (!ft_isdigit(argv[nb_arg][i]))
				return (false);
			i++;
		}
		nb_arg--;
		i = 0;
	}
	return (true);
}

void init_philos(t_table *table, char **argv)
{
	unsigned int num_of_philos;
	unsigned int i;
	unsigned int j;

	i = 0;
	num_of_philos = table->num_of_philos;
	table->philo = ft_calloc(num_of_philos, sizeof(t_philo));
	if (table->philo == NULL)
	{
		free(table);
		exit_with_error(table, "Malloc error\n", ENOMEM);
	}
	while (i < num_of_philos)
	{
		j = 2;
		table->philo[i].id = i;
		table->philo[i].has_taken_a_fork = false;
		table->philo[i].time_to_die = ft_atoi(argv[j++]);
		table->philo[i].time_to_eat = ft_atoi(argv[j++]);
		table->philo[i].time_to_sleep = ft_atoi(argv[j++]);
		if (argv[j])
			table->philo[i].number_of_meals = ft_atoi(argv[j]);
		table->philo[i].time_last_meal = current_time();
		i++;
	}
}


void init_forks(t_philo *philos, int philo_num)
{
	int i;

	for (i = 0; i < philo_num; i++)
	{
		philos[i].right_fork_mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
		if (philos[i].right_fork_mutex == NULL)
		{
			exit_with_error(philos[i].table, "Malloc error for right fork mutex\n", ENOMEM);
		}
		pthread_mutex_init(philos[i].right_fork_mutex, NULL);

		philos[i].left_fork_mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
		if (philos[i].left_fork_mutex == NULL)
		{
			exit_with_error(philos[i].table, "Malloc error for left fork mutex\n", ENOMEM);
		}
		pthread_mutex_init(philos[i].left_fork_mutex, NULL);
	}
}

void init_mutex(t_table *table)
{
	pthread_mutex_init(&table->meals_mutex, NULL);
	pthread_mutex_init(&table->print_mutex, NULL);
	init_forks(table->philo, table->num_of_philos);
}

void destroy_mutex(t_table *table)
{
	pthread_mutex_destroy(&table->meals_mutex);
	pthread_mutex_destroy(&table->print_mutex);
	pthread_mutex_destroy(table->philo->right_fork_mutex);
	pthread_mutex_destroy(table->philo->left_fork_mutex);
}