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
#include <string.h>

typedef struct s_philo		t_philo;
typedef struct s_table		t_table;
typedef pthread_mutex_t		t_mutex;

typedef struct s_table
{
	unsigned int philos;
	unsigned int forks;
	unsigned int meals;
}				t_table;

typedef struct s_philo
{
	int				index;
	unsigned int	philo_id;
	unsigned int	meals;
	bool			has_taken_two_forks;
	time_t				time_to_die;
	time_t 			time_to_eat;
	time_t 			time_to_sleep;
	time_t 			time_last_meal;
	time_t 			is_eating;
	time_t 			is_sleeping;
	time_t 			is_thinking;
	t_table				*table;
}				t_philo;


int	ft_atoi(const char *string);
long	ft_atol(const char *s);
int	ft_isdigit(char c);
void	ft_putstr_fd(const char *s, int fd);
int	ft_perror(char *str);
void	ft_usleep(u_int64_t time_in_ms);
void	*ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t nmemb, size_t size);
void	ft_putendl_fd(const char *s, int fd);
char	*ft_strjoin(char const *s1, char const *s2);
void 	free_table(t_table *table);
t_table * init_table(char *const *argv, t_table *table);


#endif //PHILO_H