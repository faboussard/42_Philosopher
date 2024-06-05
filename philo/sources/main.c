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
		return (EXIT_FAILURE);
	launch_party(table);
	destroy_mutex(table);
	free_table(table);
	return (0);
}
