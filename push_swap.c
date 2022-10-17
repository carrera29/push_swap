/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chloeplatt <chloeplatt@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 09:21:32 by clcarre           #+#    #+#             */
/*   Updated: 2022/10/13 17:43:22 by chloeplatt       ###   ########.fr       */
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
	t_node	*curr_a;
	t_node	*last_a;

	p->i = 0;
	curr_a = *list_a;
	last_a = *last;
	while (p->i < 2)
	{
		while (curr_a->p != p->i)
		{
			if (last_a->p == p->i || last_a->prev->p == p->i)
				reverse_rotate(list_a, last, 0);
			else
				rotate(list_a, last, 0);
			curr_a = *list_a;
			last_a = *last;
		}
		push(list_a, list_b, 0);
		p->i++;
	}
	three_numbers(list_a, last, 0);
	push(list_b, list_a, 1);
	push(list_b, list_a, 1);
}

void	sort_stack_b(t_push *p, t_node **list_a, t_node **list_b, int i)
{
	p->last_b = *list_b;
	while (p->last_b->next != NULL)
		p->last_b = p->last_b->next;
	if (i == 1)
	{	
		if (p->last_b->p > (*list_b)->p)
		{
			printf("rrb %d por %d B\n", (*list_b)->p, p->last_b->p);
			reverse_rotate(list_b, &p->last_b, 1);
		}
		if (((*list_b)->next->p > (*list_b)->p))
		{
			printf("swap %d por %d B\n", (*list_b)->p, (*list_b)->next->p);
			swap(list_b, 1);
		}
	}
	else
	{
		while (p->mp != 0)
		{
			if ((*list_b)->p == (p->mp - 1))
			{
				printf("push %d a A\n", (*list_b)->p);
				push(list_b, list_a, 1);
				p->mp--;
			}
			else if ((*list_b)->next->p == (p->mp - 1))
				swap(list_b, 1);
			else if (p->last_b->p == (p->mp - 1))
				reverse_rotate(list_b, &p->last_b, 1);
			else
				rotate(list_b, &p->last_b, 1);
		}
		push(list_b, list_a, 1);
	}
}

void	sort_stack_a(t_push *p, t_node **list_a, t_node **list_b, t_node **last)
{
	if ((*list_a)->p <= p->mp && (*list_a)->p >= p->min)
	{
		printf("push %d to B\n", (*list_a)->p);
		push(list_a, list_b, 0);
		p->n--;
	}
	else if ((*list_a)->next->p <= p->mp && (*list_a)->next->p >= p->min &&
		(*list_a)->next->p < (*last)->p)
		swap(list_a, 0);
	else if ((((*last)->p <= p->mp && (*last)->p > p->min)) ||
		((*last)->prev->p <= p->mp && (*last)->prev->p >= p->min))
		reverse_rotate(list_a, last, 0);
	else
		rotate(list_a, last, 0);
}

void	long_stack(t_push *p, t_node **list_a, t_node **list_b, t_node **last)
{
	p->min = 0;
	p->max = p->i - 1;
	printf("max es %d\n", p->max);
	int i = 0;
	while (i < 2)//(p->mp < p->max)
	{
		p->mp = (p->max + p->min)/ 2;
		p->n = p->mp - p->min + 1;
		printf("mp es %d\n", p->mp);
		printf("n es %d\n", p->n);
		while (p->n != 0)
		{
			sort_stack_a(p, list_a, list_b, last);
			if ((*list_b)->next != NULL)
				sort_stack_b(p, list_a, list_b, 1);
		}
		p->n = p->mp - p->min + 1;
		sort_stack_b(p, list_a, list_b, 2);
		p->min = p->mp + 1;
		i++;
	}
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
	if (p.i == 2)
		three_numbers(&p.list_a, &p.last, 0);
	else if (p.i == 4)
		five_numbers(&p, &p.list_a, &p.list_b, &p.last);
	else
	{
		long_stack(&p, &p.list_a, &p.list_b, &p.last);
		// sort_stack_b((p.i - 6), &p.list_a, &p.list_b);
	}
	p.curr = p.list_a;
	while (p.curr != NULL)
	{
		printf("A %d\n", p.curr->p);
		p.curr = p.curr->next;
	}
	p.curr = p.list_b;
	while (p.curr != NULL)
	{
		printf("B %d\n", p.curr->p);
		p.curr = p.curr->next;
	}
	free_node(&p.list_a);
	free_node(&p.list_b);
	return (0);
}
