/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clcarre <clcarrer@student.42madrid.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 09:21:32 by clcarre           #+#    #+#             */
/*   Updated: 2022/09/13 15:50:41 by clcarre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	check_numbers(t_node **list)
{
	t_node	*curr;
	t_node	*aux;
	int		unsorted;

	unsorted = 0;
	curr = *list;
	while (curr != NULL)
	{	
		aux = curr->next;
		while (aux != NULL)
		{
			if (curr->x == aux->x)
				return (0);
			if (curr->x > aux->x)
				unsorted = 1;
			aux = aux->next;
		}
		curr = curr->next;
	}
	return (unsorted);
}

void	simplify_num(int i, t_node **list)
{
	t_node	*curr;
	t_node	*aux;

	curr = *list;
	while (i > 0)
	{
		while (curr->p != 0 && curr != NULL)
			curr = curr->next;
		aux = curr->next;
		while (((curr->x > aux->x) || (aux->p != 0)) && aux->next != NULL)
			aux = aux->next;
		if (aux->next != NULL)
			curr = aux;
		else
		{
			if (aux->x > curr->x && aux->p == 0)
				curr = aux;
			curr->p = i--;
			curr = *list;
		}
	}
}

void	three_numbers(t_node **list, t_node **last, int i)
{
	if ((((*list)->p > (*list)->next->p) &&
		!(((*list)->p > (*list)->next->p) && ((*list)->p > (*last)->p) &&
		((*list)->next->p < (*last)->p))) || (((*list)->p < (*list)->next->p) &&
		((*list)->p < (*last)->p) && ((*list)->next->p > (*last)->p)))
			swap(list, i);
	if (((*list)->p > (*list)->next->p) && ((*list)->p > (*last)->p) &&
		((*list)->next->p < (*last)->p))
			rotate(list, last, i);
	if (((*list)->p < (*list)->next->p) && ((*list)->p > (*last)->p) &&
		((*list)->next->p > (*last)->p))
			reverse_rotate(list, last, i);
}

void	five_numbers(t_push *p, t_node **list_a, t_node **list_b, t_node **last)
{
	p->n = p->i - 5;
	while (p->n < (p->i - 3))
	{
		while ((*list_a)->p != p->n)
		{
			if ((*list_a)->next->p == p->n)
				swap(list_a, 0);
			else if ((*last)->p == p->n || (*last)->prev->p == p->n)
				reverse_rotate(list_a, last, 0);
			else
				rotate(list_a, last, 0);
		}
		push(list_a, list_b, 0);
		p->n++;
	}
	three_numbers(list_a, last, 0);
	push(list_b, list_a, 1);
	push(list_b, list_a, 1);
}

void	push_stack_b(t_push *p, int n_max, t_node **list_a, t_node **list_b)
{
	p->last = *list_b;
	while (p->last->next != NULL)
		p->last = p->last->next;
	while (n_max > 1)
	{	
		p->mp = (p->max / 5) + p->min;
		if ((*list_b)->p == n_max)
		{
			push(list_b, list_a, 1);
			n_max -= 1;
		}
		else if ((*list_b)->next->p == n_max)
			swap(list_b, 1);
		else if (p->last->p == n_max)
			reverse_rotate(list_b, &p->last, 1);
		else
			rotate(list_b, &p->last, 1);
	}
	if ((*list_b)->next->p > (*list_b)->p)
		swap(list_b, 1);
	push(list_b, list_a, 1);
	push(list_b, list_a, 1);
}

void	sort_stack_b(t_push *p, t_node **list_b)
{
	p->last_b = *list_b;
	while (p->last_b->next != NULL)
		p->last_b = p->last_b->next;
	if ((*list_b)->next->p > (*list_b)->p)
		swap(list_b, 1);
	else if (p->last_b->p > (*list_b)->p)
		reverse_rotate(list_b, &p->last_b, 1);
}

void	sort_stack_a(t_push *p, t_node **list_a, t_node **list_b, t_node **last)
{
	if (((*list_a)->next->p < p->mp) && ((*list_a)->next->p < (*list_a)->p))
		swap(list_a, 0);
	else if (((*last)->p < p->mp) && ((*last)->p < (*list_a)->p))
		reverse_rotate(list_a, last, 0);
	if ((*list_a)->p < p->mp)
	{
		push(list_a, list_b, 0);
		p->min++;
	}
	else
		rotate(list_a, last, 0);
	if ((*list_b) != NULL && (*list_b)->next != NULL)
		sort_stack_b(p, list_b);
}

void	long_stack(t_push *p, t_node **list_a, t_node **list_b, t_node **last)
{
	p->min = 0;
	p->max = p->i - 1;
	while (p->min <= (p->max - 5))
	{
		p->mp = (p->max / 5) + p->min;
		while (p->min != p->mp)
			sort_stack_a(p, list_a, list_b, last);
	}
	five_numbers(p, list_a, list_b, last);
	push_stack_b(p, (p->i - 6), list_a, list_b);
}

int	main(int argc, char	**argv)
{
	t_push	p;

	p.list_a = NULL;
	p.list_b = NULL;
	if (argc < 2)
		return (0);
	else if (argc == 2)
	{
		p.numbers = ft_split(argv[1], ' ');
		p.i = 0;
		while (p.numbers[p.i])
			insert_end_node(&p.list_a, ft_atoi(p.numbers[p.i++]), 0);
	}
	else
	{
		p.i = 1;
		while (argv[p.i])
			insert_end_node(&p.list_a, ft_atoi(argv[p.i++]), 0);
		p.i--;
	}
	if ((check_numbers(&p.list_a) == 0))
		return (0);
	simplify_num((p.i - 1), &p.list_a);
	p.last = p.list_a;
	while (p.last->next != NULL)
		p.last = p.last->next;
	if (p.i == 2 || p.i == 3)
		three_numbers(&p.list_a, &p.last, 0);
	else if (p.i == 4 || p.i == 5)
		five_numbers(&p, &p.list_a, &p.list_b, &p.last);
	else
		long_stack(&p, &p.list_a, &p.list_b, &p.last);
	// p.curr = p.list_a;
	// while (p.curr != NULL)
	// {
	// 	printf("A %d\n", p.curr->p);
	// 	p.curr = p.curr->next;
	// }
	// printf("\n");
	// p.curr = p.list_b;
	// while (p.curr != NULL)
	// {
	// 	printf("B %d\n", p.curr->p);
	// 	p.curr = p.curr->next;
	// }
	free_node(&p.list_a);
	free_node(&p.list_b);
	return (0);
}