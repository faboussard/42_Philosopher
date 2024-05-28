/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faboussa <faboussa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 14:04:26 by faboussa          #+#    #+#             */
/*   Updated: 2024/05/28 14:04:26 by faboussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *routine()
{
	int mails;
	int i;
	t_mutex mutex_mails;

	pthread_mutex_init(&mutex_mails, NULL);
	mails = 0;
	i = 10;
	while (i > 0)
	{
		pthread_mutex_lock(&mutex_mails);
		mails++;
		pthread_mutex_unlock(&mutex_mails);
		printf("%d\n", mails);
		ft_usleep(3);
		printf("ending\n");
		i--;
	}
	pthread_mutex_destroy(&mutex_mails);
	return (NULL);
}


int	valid_args(int argc, char **argv)
{
	size_t	i;
	int	nb_arg;

	i = 0;
	nb_arg = argc - 1;
	while (nb_arg > 0)
	{
		if (ft_atol(argv[nb_arg]) < 0 || ft_atol(argv[nb_arg]) > INT_MAX || ft_atol(argv[nb_arg]) < INT_MIN)
			return (false);
		while (argv[nb_arg][i])
		{
			if (!ft_isdigit(argv[nb_arg][i]))
				return (false);
			i++;
		}
		nb_arg--;
		i = 0;
	}
	return (true);
}

void launch_party(t_table *table)
{
	unsigned int	philos;
	unsigned int i;

	i = 0;
	philos = table->philos;
	pthread_t th[philos];
	while (i < philos)
	{
		if (pthread_create(th + i, NULL, &routine, NULL) != 0)
		{
			ft_putendl_fd("Failed to create thread", STDERR_FILENO);
			return ;
		}
		if (pthread_join(th[i], NULL) != 0)
		{
			ft_putendl_fd("Failed to liberate thread", STDERR_FILENO);
			return ;
		}
		i++;
	}
}

int main(int argc, char **argv)
{
	t_table *table;

	table = NULL;
	if ((argc != 6 && argc != 7) || !valid_args(argc, argv))
	{
		ft_putendl_fd("arguments are not valid.", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	table = init_table(argv, table);
	if (table == NULL)
		return (EXIT_FAILURE);
	launch_party(table);
	free_table(table);
	return (0);
}