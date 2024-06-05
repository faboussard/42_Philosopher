/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faboussa <faboussa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 16:00:45 by faboussa          #+#    #+#             */
/*   Updated: 2024/05/28 16:00:45 by faboussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void error_free(t_table *table, char const *error_msg)
{
	free_table(table);
	ft_putendl_fd(error_msg, STDERR_FILENO);
}
