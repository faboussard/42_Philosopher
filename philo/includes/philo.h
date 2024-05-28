/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faboussa <faboussa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 14:39:59 by faboussa          #+#    #+#             */
/*   Updated: 2024/05/28 17:49:25 by faboussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <limits.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <stdbool.h>

typedef struct s_philo		t_philo;
typedef struct s_table		t_table;
typedef pthread_mutex_t		t_mutex;

typedef struct s_table
{
	int number_of_philo;
	int number_of_fork;
	int number_of_meals;
}				t_table;

typedef struct s_philo
{
	int				index;
	int				philo_id;
	bool			has_taken_two_forks;
	int				time_to_die;
	int 			time_to_eat;
	int 			time_to_sleep;
	int 			time_last_meal;
	int 			is_eating;
	int 			is_sleeping;
	int 			is_thinking;
	int				number_of_eat;
	int				eat_count;
}				t_philo;


int	ft_atoi(const char *string);
long	ft_atol(const char *s);
int	ft_isdigit(char c);
void	ft_putstr_fd(const char *s, int fd);
int	ft_error(char *str);
void	ft_usleep(long int time_in_ms);


#endif //PHILO_H