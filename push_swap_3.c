/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chloeplatt <chloeplatt@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 09:21:32 by clcarre           #+#    #+#             */
/*   Updated: 2022/10/17 17:06:44 by chloeplatt       ###   ########.fr       */
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
	t_node	*curr;

	curr = *list;
	if (((curr->p > curr->next->p) &&
		!((curr->p > curr->next->p) && (curr->p > curr->next->next->p) &&
		(curr->next->p < curr->next->next->p))) || ((curr->p < curr->next->p) &&
		(curr->p < curr->next->next->p) && (curr->next->p > curr->next->next->p)))
			swap(list, i);
	if ((curr->p > curr->next->p) && (curr->p > curr->next->next->p) &&
		(curr->next->p < curr->next->next->p))
			rotate(list, last, i);
	if ((curr->p < curr->next->p) && (curr->p > curr->next->next->p) &&
		(curr->next->p > curr->next->next->p))
			reverse_rotate(list, last, i);
}

void	five_numbers(t_push p, t_node **list_a, t_node **list_b, t_node **last)
{
	t_node	*curr_a;
	t_node	*last_a;

	p.i = 0;
	curr_a = *list_a;
	last_a = *last;
	while (p.i < 2)
	{
		while (curr_a->p != p.i)
		{
			if (last_a->p == p.i || last_a->prev->p == p.i)
				reverse_rotate(list_a, last, 0);
			else
				rotate(list_a, last, 0);
			curr_a = *list_a;
			last_a = *last;
		}
		push(list_a, list_b, 0);
		p.i++;
	}
	three_numbers(list_a, last, 0);
	push(list_b, list_a, 1);
	push(list_b, list_a, 1);
}

int	is_shortest(t_push *p, int num, t_node **list, t_node **last)
{
	p->rot = 0;
	p->rev = 0;
	p->curr = *list;
	while ((p->curr->p != num) && (p->curr->next != NULL))
	{
		p->curr = p->curr->next;
		p->rot++;
	}
	p->curr = *last;
	while ((p->curr->p != num) && (p->curr->prev != NULL))
	{
		p->curr = p->curr->prev;
		p->rev++;
	}
	if (p->rot <= p->rev)
	{	
		p->rev = -1;
		return (p->rot);
	}
	p->rot = -1;
	return (p->rev += 1);
}

void	push_to_a(t_push *p, int mid, t_node	**list_a, t_node **list_b)
{
	p->i = mid - p->min;
	while (p->i--)
	{
		p->steps = is_shortest(p, (p->n), list_b, &p->last_b);
		while (p->steps--)
		{
			if (p->rot != -1)
				rotate(list_b, &p->last_b, 1);
			else
				reverse_rotate(list_b, &p->last_b, 1);
		}
		push(list_b, list_a, 1);
		rotate(list_a, &p->last, 0);
		if (p->x == 0)
			p->n++;
		else
			p->n--;
	}
}

void	long_stack(t_push *p, int mid, t_node **list_a, t_node **list_b)
{
	p->max = p->i - 1;
	while (p->i--)
	{
		if ((*list_a)->p < mid)
			push(list_a, list_b, 0);
		else
			rotate(list_a, &p->last, 0);
	}
	p->last_b = *list_b;
	while (p->last_b->next != NULL)
		p->last_b = p->last_b->next;
	if (is_shortest(p, 0, list_b, &p->last_b) < is_shortest(p, (mid - 1), list_b, &p->last_b))
	{
		p->x = 0;
		p->n = p->min;
	}
	else
	{
		p->x = 1;
		p->n = mid - 1;
	}
	push_to_a(p, mid, list_a, list_b);
	long_stack(p, p->max, t_node **list_a, t_node **list_b)
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
		five_numbers(p, &p.list_a, &p.list_b, &p.last);
	else
		long_stack(&p, (p.i / 2), &p.list_a, &p.list_b);
	p.curr = p.list_a;
	while (p.curr != NULL)
	{
		printf("A %d\n", p.curr->p);
		p.curr = p.curr->next;
	}
	printf("\n");
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