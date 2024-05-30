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

void *routine()
{
	int		i;
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

void launch_party(t_table *table)
{
	create_threads(table);
	terminate_threads(table);
}

int main(int argc, char **argv)
{
	t_table *table;

	table = NULL;
	if ((argc != 5 && argc != 6) || !valid_args(argc, argv))
		exit_with_error(table, "arguments are not valid.", EXIT_FAILURE);
	init_table(argv, &table);
	init_philos(table, argv);
	init_mutex(table);
	launch_party(table);
	free_table(table);
	return (0);
}