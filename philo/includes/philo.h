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
#include <errno.h>

typedef struct s_philo		t_philo;
typedef struct s_table		t_table;
typedef pthread_mutex_t		t_mutex;

typedef struct s_table
{
	int 			num_of_philos;
	pthread_mutex_t *forks;
	size_t			start_time;
	bool	 		dead_detected;
	t_mutex			death_detected_mutex;
	bool			threads_created;
	t_mutex			threads_created_mutex;
	pthread_t		*threads;
	t_mutex			print_mutex;
	t_philo 		*philo;
}				t_table;

typedef struct s_philo
{
	unsigned		id;
	bool			has_taken_a_fork;
	bool 			dead_flag;
	size_t 			time_to_die;
	t_mutex 		time_to_die_mutex;
	size_t 			time_to_eat;
	size_t 			time_to_sleep;
	size_t 			number_of_meals;
	size_t 			time_last_meal;
	t_mutex 		last_meal_mutex;
	t_mutex 		*r_fork_mutex;
	t_mutex 		*l_fork_mutex;
	t_table 		*table;
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
void init_table(char *const *argv, t_table **table);
size_t	get_time_in_ms(void);
void error_free_exit(t_table *table, char const *error_msg, int error_code);
int	valid_args(int argc, char **argv);
void create_threads(t_table *table);
void terminate_threads(t_table *table);
void init_philos(t_table *table, char **argv);
void launch_party(t_table *table);
void *routine(void *data);
void init_mutex(t_table *table);
void destroy_mutex(t_table *table);
void wait_threads(t_table *table);
void print_msg(t_philo *philo, char *msg);


#endif //PHILO_H