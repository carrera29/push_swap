/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   long_stack.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clcarrer <clcarrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 11:46:54 by clcarrer          #+#    #+#             */
/*   Updated: 2022/10/28 10:38:02 by clcarrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	is_shortest_b(t_push *p, t_node **list, t_node **last)
{
	p->rot = 0;
	p->rev = 0;
	p->curr = *list;
	while (p->curr->next != NULL)
	{
		if (p->curr->p == p->min || p->curr->p == p->max)
			break ;
		p->curr = p->curr->next;
		p->rot++;
	}
	p->curr = *last;
	while (p->curr->prev != NULL)
	{
		if (p->curr->p == p->min || p->curr->p == p->max)
			break ;
		p->curr = p->curr->prev;
		p->rev++;
	}
	if (p->rot <= p->rev)
		return (p->rot);
	p->rot = -1;
	return (p->rev += 1);
}

int	is_shortest_a(t_push *p, int max, t_node **list, t_node **last)
{
	p->rot = 0;
	p->rev = 0;
	p->curr = *list;
	while ((p->curr->p < p->min || p->curr->p > max) && (p->curr->next != NULL))
	{
		p->curr = p->curr->next;
		p->rot++;
	}
	p->curr = *last;
	while ((p->curr->p < p->min || p->curr->p > max) && (p->curr->prev != NULL))
	{
		p->curr = p->curr->prev;
		p->rev++;
	}
	if (p->rot <= p->rev)
		return (p->rot);
	p->rot = -1;
	return (p->rev += 1);
}

void	push_stack_b(t_push *p, t_node **list_a, t_node **list_b)
{
	p->min = (p->i / 2) - 1;
	p->max = (p->i / 2) + 1;
	p->n = p->i - 1;
	while (p->n-- > 1)
	{
		p->steps = is_shortest_b(p, list_b, &p->last_b);
		while (p->steps--)
		{
			if (p->rot != -1)
				rotate(list_b, &p->last_b, 1);
			else
				reverse_rotate(list_b, &p->last_b, 1);
		}
		push(list_b, list_a, 1);
		if ((*list_a)->p == p->max)
		{
			rotate(list_a, &p->last, 0);
			p->max++;
		}
		else
			p->min--;
	}
	push(list_b, list_a, 1);
	if ((*list_a)->p > (*list_a)->next->p)
		rotate(list_a, &p->last, 0);
}

void	sort_stack_a(t_push *p, t_node **list_a, t_node **list_b)
{
	p->steps = is_shortest_a(p, p->mp, list_a, &p->last);
	while (p->steps--)
	{
		if (p->rot != -1)
			rotate(list_a, &p->last, 0);
		else
			reverse_rotate(list_a, &p->last, 0);
	}
	push(list_a, list_b, 0);
	p->n--;
}

void	long_stack(t_push *p, int x, t_node **list_a, t_node **list_b)
{
	p->min = (p->i / 2) + 1;
	p->max = p->i - 1;
	while (p->min <= p->max)
	{
		p->mp = ((p->max - p->min) / x) + p->min;
		p->n = p->mp - p->min + 1;
		while (p->n != 0)
			sort_stack_a(p, list_a, list_b);
		p->min = p->mp + 1;
		if (x > 1)
			x--;
		if (p->min == p->i)
		{
			p->max = (p->i / 2) - 1;
			p->min = 0;
			x = 4;
			if (p->i > 100)
				x = 7;
		}
	}
	p->last_b = *list_b;
	while (p->last_b->next != NULL)
		p->last_b = p->last_b->next;
	push_stack_b(p, list_a, list_b);
}
