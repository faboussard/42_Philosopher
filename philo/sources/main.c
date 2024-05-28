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

//void *routine()
//{
//	int mails;
//	int i;
//	t_mutex mutex_mails;
//
//	mails = 0;
//	i = 10;
//	while (i > 0)
//	{
//		pthread_mutex_lock(&mutex_mails);
//		mails++;
//		pthread_mutex_unlock(&mutex_mails);
//		printf("%d\n", mails);
//		sleep(3);
//		printf("ending\n");
//		i--;
//	}
//}
//

// faire mes data strcutures

//faier la fonction init table

//bien proteger les threads
//tous les ouvrir en meme temps
// tous les fermer en meme temps

//faire un mutex pour chaque variable

// faire la fonction ft-usleep

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
//	t_table *table;
//
//	table = NULL;

	if ((argc != 6 && argc != 7) || !valid_args(argc, argv))
		return (1);
//	p_thread t1;
//	// faire le nombre de philosopher. et les verifier a chaquoifois.
//
//	//voir ou faire toutes les initiatlisations de mutex.
//	pthread_mutex_init(&mutex_mails, NULL);
//
//
//
//	pthread_create(&t1, NULL, &routine, NULL);
//
//	//faire pour tous les philos.
//	pthread_join(t1, NULL);
	return (0);
}