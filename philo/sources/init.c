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

int	init_table(char *const *argv, t_table **table)
{
	*table = ft_calloc(1, sizeof(t_table));
	if (!*table)
	{
		error_free(NULL, "Malloc error\n");
		return (0);
	}
	(*table)->num_of_philos = ft_atoi(argv[1]);
	(*table)->start_time = get_time_in_ms();
	return (1);
}

void init_philo(t_table *table, char *const *argv, int i, int j)
{
	table->philo[i].table = table;
	table->philo[i].id = i + 1;
	table->philo[i].time_to_die = ft_atoi(argv[j++]);
	table->philo[i].time_to_eat = ft_atoi(argv[j++]);
	table->philo[i].time_to_sleep = ft_atoi(argv[j++]);
	table->philo[i].left_fork = 0;
	if (argv[j])
		table->philo[i].number_of_meals = ft_atoi(argv[j]);
	else
		table->philo[i].number_of_meals = -1;
	table->philo[i].time_last_meal = get_time_in_ms();
	if (i == 0)
	{
		table->philo[i].r_fork_mutex = &(table->philo[table->num_of_philos - 1].l_fork_mutex);
		table->philo[i].right_fork = &(table->philo[table->num_of_philos - 1].left_fork);
	}
	else
	{
		table->philo[i].r_fork_mutex = &(table->philo[i - 1].l_fork_mutex);
		table->philo[i].right_fork = &(table->philo[i - 1].left_fork);
	}
}

int	init_philos(t_table *table, char **argv)
{
	int	i;
	int	j;

	i = 0;
	table->philo = ft_calloc(table->num_of_philos, sizeof(t_philo));
	if (table->philo == NULL)
		return (error_free(table, "Malloc error\n"), 0);
	while (i < table->num_of_philos)
	{
		j = 2;
		init_philo(table, argv, i, j);
		i++;
	}
	return (1);
}
