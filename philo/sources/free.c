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

void 	free_table(t_table *table)
{
	int i;

	i = 0;
	if (table == NULL)
		return ;
	if (table->philo)
	{
		while (table->philo[i].table)
		{
			free(table->philo[i].table);
			table->philo[i].table = NULL;
			i++;
		}
		free(table->forks);
		table->forks = NULL;
		free(table->philo);
		table->philo = NULL;
	}
	if (table->threads)
		free(table->threads);
	free(table);
	table = NULL;
}