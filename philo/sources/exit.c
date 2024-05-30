/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faboussa <faboussa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 16:00:45 by faboussa          #+#    #+#             */
/*   Updated: 2024/05/28 16:00:45 by faboussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void exit_with_error(t_table *table, char const *error_msg, int error_code)
{
	free_table(table);
	ft_putendl_fd(error_msg, STDERR_FILENO);
	exit(error_code);
}
