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

# include <errno.h>
# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

#define SUCCESS 0
#define FAILURE 1

enum {
	FREE,
	TAKEN,
};

# define MSG_FORK "\001\e[0;36m\002has taken a fork\001\e[m\002"
# define MSG_EAT "\001\e[0;35m\002is eating\001\e[m\002"
# define MSG_SLEEP "\001\e[0;33m\002is sleeping\001\e[m\002"
# define MSG_THINK "\001\e[0;37m\002is thinking\001\e[m\002"
# define MSG_DIE "\001\e[0;31m\002died\001\e[m\002"

typedef struct s_philo	t_philo;
typedef struct s_table	t_table;
typedef pthread_mutex_t	t_mutex;

typedef struct s_table
{
	int		num_of_philos;
	size_t				start_time;
	t_mutex				start_time_mutex;
	bool				dead_detected;
	int					end_dinner;
	t_mutex 			end_dinner_mutex;
	t_mutex				death_detected_mutex;
	t_mutex				print_mutex;
	t_philo				*philo;
}						t_table;

typedef struct s_philo
{
	pthread_t			tid;
	int		id;
	size_t				time_to_die;
	size_t				time_to_eat;
	size_t				time_to_sleep;
	int					number_of_meals;
	t_mutex				number_of_meals_mutex;
	size_t				time_last_meal;
	t_mutex				meal_lock;
	int				*right_fork;
	int				left_fork;
	int					nbr_forks;
	t_mutex				*r_fork_mutex;
	t_mutex			    l_fork_mutex;
	t_table				*table;
}						t_philo;

int						ft_atoi(const char *string);
long					ft_atol(const char *s);
int						ft_isdigit(char c);
void					*ft_bzero(void *s, size_t n);
void					*ft_calloc(size_t nmemb, size_t size);
void					ft_putendl_fd(const char *s, int fd);
char					*ft_strjoin(char const *s1, char const *s2);
void					free_table(t_table *table);
int						init_table(char *const *argv, t_table **table);
size_t					get_time_in_ms(void);
void					error_free(t_table *table, char const *error_msg);
int						valid_args(int argc, char **argv);
int						create_threads(t_table *table);
int						terminate_threads(t_table *table,
							unsigned int number_of_threads);
int						init_philos(t_table *table, char **argv);
void					launch_party(t_table *table);
void					*routine(void *data);
int						init_mutex(t_table *table);
void					destroy_mutex(t_table *table);
int print_msg(t_philo *philo, char *msg, int i);
void					eat(t_philo *philo, int i);
int						dead_loop(t_philo *philo);
int						ft_usleep(size_t ms, t_philo *philosopher);
int						check_if_dead(t_philo *philos);

#endif // PHILO_H