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

int	main(int argc, char **argv)
{
	t_table	*table;

	table = NULL;
	if ((argc != 5 && argc != 6) || !valid_args(argc, argv))
	{
		error_free(table, "arguments are not valid.");
		return (EXIT_FAILURE);
	}
	if (!init_table(argv, &table))
		return (EXIT_FAILURE);
	if (!init_philos(table, argv))
		return (EXIT_FAILURE);
	if (!init_mutex(table))
	{
		error_free(table, "error initializing mutex.");
		return (EXIT_FAILURE);
	}
	launch_party(table);
	destroy_mutex(table);
	free_table(table);
	return (0);
}
