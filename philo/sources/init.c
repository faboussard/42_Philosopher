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
