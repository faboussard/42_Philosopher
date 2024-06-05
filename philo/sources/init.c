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

void	init_table(char *const *argv, t_table **table)
{
	*table = ft_calloc(1, sizeof(t_table));
	if (!*table)
		error_free_exit(NULL, "Malloc error\n", ENOMEM);
	(*table)->num_of_philos = ft_atoi(argv[1]);
	(*table)->threads = ft_calloc((*table)->num_of_philos, sizeof(pthread_t));
	if ((*table)->threads == NULL)
		error_free_exit(*table, "Malloc error\n", ENOMEM);
}

int	valid_args(int argc, char **argv)
{
	unsigned int	i;
	int				nb_arg;

	i = 0;
	nb_arg = argc - 1;
	while (nb_arg > 0)
	{
		if (ft_atol(argv[nb_arg]) <= 0 || ft_atol(argv[nb_arg]) > INT_MAX
			|| ft_atol(argv[nb_arg]) < INT_MIN)
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

void	init_philos(t_table *table, char **argv)
{
	size_t	i;
	size_t	j;

	i = 0;
	table->philo = ft_calloc(table->num_of_philos, sizeof(t_philo));
	if (table->philo == NULL)
		error_free_exit(table, "Malloc error\n", ENOMEM);
	while (i < table->num_of_philos)
	{
		j = 2;
		table->philo[i].table = table;
		table->philo[i].id = i;
		table->philo[i].has_taken_a_fork = false;
		table->philo[i].time_to_die = ft_atoi(argv[j++]);
		table->philo[i].time_to_eat = ft_atoi(argv[j++]);
		table->philo[i].time_to_sleep = ft_atoi(argv[j++]);
		if (argv[j])
			table->philo[i].number_of_meals = ft_atoi(argv[j]);
		table->philo[i].time_last_meal = get_time_in_ms();
		i++;
	}
}
