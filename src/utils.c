/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clcarrer <clcarrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 08:05:55 by chloeplatt        #+#    #+#             */
/*   Updated: 2022/10/26 11:31:38 by clcarrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	free_node(t_push *p, t_node **list_a, t_node **list_b)
{
	p->curr = *list_a;
	p->i = 2;
	while (p->i--)
	{
		while (p->curr != NULL)
		{
			p->aux = p->curr;
			p->curr = p->curr->next;
			free(p->aux);
		}
		p->curr = *list_b;
	}
	*list_a = NULL;
	*list_b = NULL;
}

void	error_msg(t_push *p, t_node **list_a, t_node **list_b)
{
	free_node(p, list_a, list_b);
	exit (write(1, "Error\n", 6));
}

int	ft_atoi(t_push *p, const char *str)
{
	long long int	s;
	long long int	r;
	int				i;

	i = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	s = 1;
	if ((str[i] == '-') || (str[i] == '+'))
	{
		if (str[i] == '-')
			s *= -1;
		i++;
	}
	r = 0;
	while (str[i])
	{
		if (str[i] >= 48 && str[i] <= 57)
			r = (r * 10) + (str[i++] - 48);
		else
			error_msg(p, &p->list_a, &p->list_b);
		if ((r * s) > 2147483647 || (r * s) < -2147483648)
			error_msg(p, &p->list_a, &p->list_b);
	}
	return (s * r);
}
