/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clcarrer <clcarrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 09:21:32 by clcarre           #+#    #+#             */
/*   Updated: 2022/10/20 18:15:56 by clcarrer         ###   ########.fr       */
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
	simplify_num((p->i - 1), list_a);
	p->last = *list_a;
	while (p->last->next != NULL)
		p->last = p->last->next;
	if (p->i == 2 || p->i == 3)
		three_numbers(list_a, &p->last, 0);
	else if (p->i == 4 || p->i == 5)
		five_numbers(p, list_a, list_b, &p->last);
	else
	{
		p->d = 2;
		if (p->i > 100)
			p->d = 4;
		long_stack(p, list_a, list_b, &p->last);
	}
}

void	check_in(t_push *p, int argc, char **argv)
{
	if (argc == 2)
	{
		p->numbers = ft_split(argv[1], ' ');
		p->i = 0;
		while (p->numbers[p->i])
			insert_end_node(&p->list_a, ft_atoi(p->numbers[p->i++]), 0);
	}
	else
	{
		p->i = 1;
		while (argv[p->i])
			insert_end_node(&p->list_a, ft_atoi(argv[p->i++]), 0);
		p->i--;
	}
	p->curr = p->list_a;
	while (p->curr->next != NULL)
	{
		ft_is_integer(p, p->curr->p);
		p->curr = p->curr->next;
	}
}

int	main(int argc, char	**argv)
{
	t_push	p;

	p.list_a = NULL;
	p.list_b = NULL;
	if (argc > 1)
		check_in(&p, argc, argv);
	if (check_numbers(&p, &p.list_a) == 0)
		push_swap(&p, &p.list_a, &p.list_b);
	free_node(&p, &p.list_a, &p.list_b);
	return (0);
}

// p.curr = p.list_a;
// while (p.curr != NULL)
// {
// 	printf("A %d\n", p.curr->x);
// 	p.curr = p.curr->next;
// }