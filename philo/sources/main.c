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
//
//	printf("test from threads\n");
//	sleep(3);
//	printf("ending\n");
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

	i = 1;
	while (argc > 1)
	{
		printf("%d\n", argc);
//		if (ft_atol(argv[argc]) < INT_MIN && ft_atol(argv[argc]) > INT_MAX)
//			return (false);
		while (argv[argc][i])
		{
			printf("%d\n", argv[argc][i]);
			if (!ft_isdigit(argv[argc][i]))
				return (false);
			i++;
		}
		argc--;
		printf("%d\n", argc);
		i = 1;
	}
	return (true);
}

int main(int argc, char **argv)
{
//	t_table *table;
//
//	table = NULL;

	if (argc != 6 && argc != 7 && !valid_args(argc, argv))
		return (1);
//	p_thread t1;
//
//	pthread_create(&t1, NULL, &routine, NULL);
//	pthread_join(t1, NULL);
	return (0);
}