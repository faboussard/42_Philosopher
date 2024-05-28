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
	return (NULL);
}

int	valid_args(int argc, char **argv)
{
	size_t	i;
	int	nb_arg;

	i = 1;
	nb_arg = argc - 1;
	while (nb_arg > 0)
	{
		if (ft_atoi(argv[nb_arg]) < 0 || ft_atol(argv[nb_arg]) < INT_MIN || ft_atol(argv[nb_arg]) > INT_MAX)
			return (false);
		while (argv[nb_arg][i])
		{
			if (!ft_isdigit(argv[nb_arg][i]))
				return (false);
			i++;
		}
		nb_arg--;
		i = 1;
	}
	return (true);
}

int main(int argc, char **argv)
{
	t_table *table;
	pthread_t t1;

	table = NULL;

	if ((argc != 6 && argc != 7) || !valid_args(argc, argv))
		return (1);
	// faire le nombre de philosopher. et les verifier a chaquoifois.

	//voir ou faire toutes les initiatlisations de mutex.



	pthread_create(&t1, NULL, &routine, NULL);

	//faire pour tous les philos.
	pthread_join(t1, NULL);
	return (0);
}