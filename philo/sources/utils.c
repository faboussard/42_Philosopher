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

u_int64_t	current_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
		ft_putendl_fd("Gettimeofday returned -1\n", STDERR_FILENO);
	return ((tv.tv_sec * (u_int64_t)1000) + (tv.tv_usec / 1000));
}

void	ft_usleep(u_int64_t time_in_ms)
{
	u_int64_t	start_time;

	start_time = current_time();
	while ((current_time() - start_time) < time_in_ms)
		usleep(time_in_ms / 10);
}