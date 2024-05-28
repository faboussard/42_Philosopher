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

static int	ft_sign(const char *string)
{
	int	sign;

	sign = 1;
	if (*string == '-')
		sign *= -1;
	return (sign);
}

static const char	*ft_whitespace(const char *string)
{
	size_t	i;

	i = 0;
	while (*(string + i) == ' ' || *(string + i) == '\n' || *(string
															  + i) == '\t' || *(string + i) == '\v' || *(string + i) == '\r'
		   || *(string + i) == '\f')
		i++;
	return (string + i);
}

int	ft_atoi(const char *string)
{
	long	res;
	size_t	i;
	int		sign;

	i = 0;
	res = 0;
	string = ft_whitespace(string);
	sign = ft_sign(string);
	if (string[i] == '-' || string[i] == '+')
		i++;
	while (string[i] >= '0' && string[i] <= '9')
	{
		if (res > res * 10 + (string[i] - '0'))
			return ((sign > 0) * -1);
		res = res * 10 + (string[i] - '0');
		i++;
	}
	return ((int)(res * sign));
}

int	ft_isdigit(char c)
{
	return (c >= '0' && c <= '9');
}


long	ft_atol(const char *s)
{
	long	result;
	int		sign;

	result = 0;
	sign = 1;
	while (*s == ' ' || *s == '\t' || *s == '\n' || *s == '\r' || *s == '\f'
		   || *s == '\v')
		s++;
	if (*s == '-' || *s == '+')
	{
		if (*s == '-')
			sign = -1;
		s++;
	}
	while (ft_isdigit(*s))
		result = result * 10 + (*s++ - '0');
	return (result * sign);
}