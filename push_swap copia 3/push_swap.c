/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clcarre <clcarrer@student.42madrid.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 09:21:32 by clcarre           #+#    #+#             */
/*   Updated: 2022/09/15 13:00:37 by clcarre          ###   ########.fr       */
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

// void	stack_b(t_push p, int n_max, t_node **list_a, t_node **list_b)
// {
// 	t_node	*last;
	
// 	last = *list_b;
// 	while (last->next != NULL)
// 		last = last->next;
// 	// if (curr->p == p.max)
// 	// {
// 	// 	push(list_b, list_a, 1);
// 	// 	p.max -= 1;
// 	// }
// 	if ((*list_b)->next->p == p.max)
// 		swap(list_b, 1);
// 	else if (last->p == p.max)
// 		reverse_rotate(list_b, &last, 1);
// 	else
// 		rotate(list_b, &last, 1);

// 	if (curr->next->p > curr->p)
// 		swap(list_b, 1);
// 	push(list_b, list_a, 1);
// 	push(list_b, list_a, 1);
// }

int	stack_a(t_push p, t_node **list_a, t_node **list_b, t_node **last)
{
	if (((*list_a)->p > p.min) && ((*list_a)->p <= p.mid))
	{
		push(list_a, list_b, 0);
		p.min++;
	}
	else if (((*list_a)->next->p > p.min) && ((*list_a)->p <= p.mid) && ((*list_a)->next->p < (*last)->p))
		swap(list_a, 0);
	else if (((*last)->p > p.min) && ((*list_a)->p <= p.mid))
		reverse_rotate(list_a, last, 0);
	else
		rotate(list_a, last, 0);
	return (p.min);
}

void	long_stack(t_push p, t_node **list_a, t_node **list_b, t_node **last)
{
	p.max = p.max - 2;
	printf("el num max es %d\n", p.max);
	p.min = (p.max / 2);
	printf("el num min es %d\n", p.min);
	p.mid = p.min - ((p.max - p.min)/ 2);
	printf("hay que hasta el num %d\n", p.mid);
	while (p.mid != p.max)
	{
		while (p.min != p.mid)
		{
			p.min = stack_a(p, list_a, list_b, last);
			// stack_b(p, list_a, list_b);
		}
		p.mid = p.min - ((p.max - p.min)/ 2);
		printf("ahora hay que pasar hasta el num %d\n", p.mid);
	}
	// three_numbers(list_a, last, 0);
}

int	main(int argc, char	**argv)
{
	t_node	*list_a;
	t_node	*list_b;
	t_node	*curr;
	t_node	*last;
	t_push	p;

	list_a = NULL;
	list_b = NULL;
	if (argc < 3)
		return (0);
	p.max = 1;
	while (argv[p.max])
		insert_end_node(&list_a, ft_atoi(argv[p.max++]), 0);
	if ((check_numbers(&list_a) == 0))
		return (0);
	simplify_num((p.max - 2), &list_a);
	last = list_a;
	while (last->next != NULL)
		last = last->next;
	// if (argc == 4)
	// 	three_numbers(&list_a, &last);
	// else if (argc == 6)
	// 	five_numbers(p, &list_a, &list_b, &last);
	long_stack(p, &list_a, &list_b, &last);
	curr = list_a;
	while (curr != NULL)
	{
		printf("A %d\n", curr->x);
		curr = curr->next;
	}
	curr = list_b;
	while (curr != NULL)
	{
		printf("B %d\n", curr->x);
		curr = curr->next;
	}
	free_node(&list_a);
	free_node(&list_b);
	return (0);
}
