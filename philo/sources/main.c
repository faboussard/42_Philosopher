/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faboussa <faboussa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 14:04:26 by faboussa          #+#    #+#             */
/*   Updated: 2024/05/28 14:04:26 by faboussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *routine()
{
	int i;
	t_mutex mutex_mails;

	pthread_mutex_init(&mutex_mails, NULL);
	i = 10;
	while (i > 0)
	{
		pthread_mutex_lock(&mutex_mails);
		pthread_mutex_unlock(&mutex_mails);
		i--;
	}
	pthread_mutex_destroy(&mutex_mails);
	return (NULL);
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

void create_threads(t_table *table)
{
	unsigned int philos;
	unsigned int i;

	i = 0;
	philos = table->num_of_philos;
	pthread_t th[philos];
	while (i < philos)
	{
		if (pthread_create(th + i, NULL, &routine, NULL) != 0)
		{
			ft_putendl_fd("Failed to create thread", STDERR_FILENO);
			return;
		}
		i++;
	}
}

void terminate_threads(t_table *table)
{
	unsigned int philos;
	unsigned int i;

	i = 0;
	philos = table->num_of_philos;
	pthread_t th[philos];

	while (i < philos)
	{
		if (pthread_join(th[i], NULL) != 0)
		{
			ft_putendl_fd("Failed to liberate thread", STDERR_FILENO);
			return;
		}
		i++;
	}
}

void init_philos(t_table *table, char **argv)
{
	unsigned int num_of_philos;
	unsigned int i;
	unsigned int j;

	i = 0;
	num_of_philos = table->num_of_philos;
	table->philo = ft_calloc(num_of_philos, sizeof(t_philo));
	while (i < num_of_philos)
	{
		j = 2;
		table->philo[i].index = i;
		table->philo[i].has_taken_two_forks = false;
		table->philo[i].time_to_die = ft_atoi(argv[j++]);
		table->philo[i].time_to_eat = ft_atoi(argv[j++]);
		table->philo[i].time_to_sleep = ft_atoi(argv[j++]);
		if (argv[j])
			table->philo[i].number_of_meals = ft_atoi(argv[j]);
		table->philo[i].time_last_meal = current_time();
		i++;
	}
}

void launch_party(t_table *table)
{
	create_threads(table);
	terminate_threads(table);
}

void exit_with_error(t_table *table, char const *error_msg, int error_code)
{
	free_table(table);
	ft_putendl_fd(error_msg, STDERR_FILENO);
	exit(error_code);
}

int main(int argc, char **argv)
{
	t_table *table;

	table = NULL;
	if ((argc != 5 && argc != 6) || !valid_args(argc, argv))
		exit_with_error(table, "arguments are not valid.", EXIT_FAILURE);
	init_table(argv, &table);
	init_philos(table, argv);
	launch_party(table);
	free_table(table);
	return (0);
}