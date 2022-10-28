/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chloeplatt <chloeplatt@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 09:21:32 by clcarre           #+#    #+#             */
/*   Updated: 2022/10/27 19:11:24 by chloeplatt       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	three_numbers(t_node **list, t_node **last, int i)
{
	if ((((*list)->p > (*list)->next->p) && \
		!(((*list)->p > (*list)->next->p) && ((*list)->p > (*last)->p) && \
		((*list)->next->p < (*last)->p))))
		swap(list, i);
	else if (((*list)->p < (*list)->next->p)
		&& ((*list)->p < (*last)->p) && ((*list)->next->p > (*last)->p))
		swap(list, i);
	if (((*list)->p > (*list)->next->p) && ((*list)->p > (*last)->p)
		&& ((*list)->next->p < (*last)->p))
		rotate(list, last, i);
	if (((*list)->p < (*list)->next->p) && ((*list)->p > (*last)->p)
		&& ((*list)->next->p > (*last)->p))
		reverse_rotate(list, last, i);
}

void	five_numbers(t_push *p, t_node **list_a, t_node **list_b, t_node **last)
{
	p->min = 0;
	p->max = -1;
	while (p->min != p->i - 3)
	{
		p->steps = is_shortest_b(p, list_a, last);
		while (p->steps--)
		{
			if (p->rot != -1)
				rotate(list_a, last, 0);
			else
				reverse_rotate(list_a, last, 0);
		}
		push(list_a, list_b, 0);
		p->min++;
	}
	three_numbers(list_a, last, 0);
	push(list_b, list_a, 1);
	push(list_b, list_a, 1);
}

void	push_swap(t_push *p, t_node **list_a, t_node **list_b)
{
	int	x;

	simplify_num((p->i - 1), list_a);
	if (p->i == 2 || p->i == 3)
		three_numbers(list_a, &p->last, 0);
	else if (p->i == 4 || p->i == 5)
		five_numbers(p, list_a, list_b, &p->last);
	else
	{
		x = 2;
		if (p->i > 100)
			x = 7;
		long_stack(p, x, list_a, list_b);
	}
}

int	main(int argc, char	**argv)
{
	t_push	p;

	p.list_a = NULL;
	p.list_b = NULL;
	if (argc > 1)
		check_in(&p, argv);
	if (check_numbers(&p, &p.list_a) == 0)
		push_swap(&p, &p.list_a, &p.list_b);
	p.curr = p.list_a;
	while (p.curr->next != NULL)
	{
		printf("A -> %d\n", p.curr->p);
		p.curr = p.curr->next;
	}
	p.curr = p.list_b;
	while (p.curr->next != NULL)
	{
		printf("B -> %d\n", p.curr->p);
		p.curr = p.curr->next;
	}
	free_node(&p, &p.list_a, &p.list_b);
	return (0);
}