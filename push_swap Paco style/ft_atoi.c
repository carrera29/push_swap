/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chloeplatt <chloeplatt@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 08:32:08 by clcarre           #+#    #+#             */
/*   Updated: 2022/07/14 10:28:45 by chloeplatt       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	ft_atoi(const char *str)
{
	long int	s;
	long int	r;

	while (*str == 32 || (*str >= 9 && *str <= 13))
		str++;
	s = 1;
	if ((*str == '-') || (*str == '+'))
	{
		if (*str == '-')
			s *= -1;
		str++;
	}
	r = 0;
	while (*str >= 48 && *str <= 57)
	{
		if ((r * s) > 2147483647)
			return (-1);
		else if ((r * s) < -2147483647)
			return (0);
		r = (r * 10) + (*str - 48);
		str++;
	}
	return (s * r);
}
/*
int	main(void)
{
	printf("%d\n", ft_atoi("99999999999999999999999999"));
	printf("%d\n", atoi("99999999999999999999999999"));
	return (0);
}*/