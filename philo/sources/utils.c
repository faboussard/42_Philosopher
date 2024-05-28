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

u_int64_t	actual_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
		ft_error("Gettimeofday returned -1\n");
	return ((tv.tv_sec * (u_int64_t)1000) + (tv.tv_usec / 1000));
}

void	ft_usleep(long int time_in_ms)
{
	u_int64_t	start_time;

	start_time = actual_time();
	while ((actual_time() - start_time) < time_in_ms)
		usleep(time_in_ms / 10);
}