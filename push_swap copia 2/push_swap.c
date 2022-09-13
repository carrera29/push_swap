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

void	sort_stack_b(int n_max, t_node **list_a, t_node **list_b)
{
	t_node	*curr;
	t_node	*last;
	int		n_mid;
	
	last = *list_b;
	while (last->next != NULL)
		last = last->next;
	curr = *list_b; 
	int i = 0;
	while (n_max > 1)
	{	
		n_mid = (n_max / 2);
		while (n_max > n_mid)
		{
			if (curr->p == n_max)
			{
				push(list_b, list_a, 1);
				n_max -= 1;
			}
			else if (curr->next->p == n_max)
				swap(list_b, 1);
			else if (last->p == n_max)
				reverse_rotate(list_b, &last, 1);
			else
				rotate(list_b, &last, 1);
			curr = *list_b;
		}
		i++;
	}
	if (curr->next->p > curr->p)
		swap(list_b, 1);
	push(list_b, list_a, 1);
	push(list_b, list_a, 1);
}

void	long_stack(int n_max, t_node **list_a, t_node **list_b, t_node **last)
{
	t_node	*curr;
	int		n_min;
	int		n_mid;
	int		n;
	
	n_min = 0;
	curr = *list_a;
	while (curr->next->next->next != NULL)
	{
		n_mid = (n_max + n_min)/ 2;
		n = n_mid - n_min;
		while (n != 0)
		{
			if (curr->p < n_mid)
			{
				push(list_a, list_b, 0);
				n--;
			}
			else if ((curr->next->p < n_mid) && (curr->next->p < (*last)->p))
				swap(list_a, 0);
			else if ((*last)->p < n_mid)
				reverse_rotate(list_a, last, 0);
			else
				rotate(list_a, last, 0);
			curr = *list_a;
		}
		n_min = n_mid;
	}
	three_numbers(list_a, last, 0);
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
	p.n_max = 1;
	while (argv[p.n_max])
		insert_end_node(&list_a, ft_atoi(argv[p.n_max++]), 0);
	if ((check_numbers(&list_a) == 0))
		return (0);
	simplify_num((p.n_max - 2), &list_a);
	last = list_a;
	while (last->next != NULL)
		last = last->next;
	// if (argc == 4)
	// 	three_numbers(&list_a, &last);
	// else if (argc == 6)
	// 	five_numbers(p, &list_a, &list_b, &last);
	long_stack((p.i - 2), &list_a, &list_b, &last);
	sort_stack_b((p.i - 5), &list_a, &list_b);
	curr = list_a;
	while (curr != NULL)
	{
		printf("A %d\n", curr->x);
		curr = curr->next;
	}
	// curr = list_b;
	// while (curr != NULL)
	// {
	// 	printf("B %d\n", curr->x);
	// 	curr = curr->next;
	// }
	free_node(&list_a);
	free_node(&list_b);
	return (0);
}
