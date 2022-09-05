/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chloeplatt <chloeplatt@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 09:21:32 by clcarre           #+#    #+#             */
/*   Updated: 2022/09/05 16:17:02 by chloeplatt       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
/*
sa : swap a / sb : swap b / ss : swap a & swap b
	1	->	3
	3	->	1
	2		2
    
pa : push a to b / pb : push b to a
	1	->				
	3				2	<-	2
	2		1		1		3

ra : rotate a /  rb : rotate b / rr : rotate a y rotate b al mismo tiempo
	1	->	3
	3	->	2
	2		1

rra : reverse rotate a / rrb : reverse rotate b / rrr : a y b al mismo tiempo
	1	->	2
	3	->	1
	2		3
*/

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

void	three_numbers(t_push p, t_node **list_a)
{
	t_node	*curr;

	curr = *list_a;
	if (((curr->p > curr->next->p) &&
		!((curr->p > curr->next->p) && (curr->p > curr->next->next->p) &&
		(curr->next->p < curr->next->next->p))) || ((curr->p < curr->next->p) &&
		(curr->p < curr->next->next->p) && (curr->next->p > curr->next->next->p)))
			p.n = p.n + swap(list_a);
	if ((curr->p > curr->next->p) && (curr->p > curr->next->next->p) &&
		(curr->next->p < curr->next->next->p))
			p.n = p.n + rotate(list_a);
	if ((curr->p < curr->next->p) && (curr->p > curr->next->next->p) &&
		(curr->next->p > curr->next->next->p))
			p.n = p.n + reverse_rotate(list_a);
}

void	five_numbers(t_push p, t_node **list_a, t_node **list_b)
{
	t_node	*curr_a;
	t_node	*curr_b;

	curr_a = *list_a;
	push(list_a, list_b);
	push(list_a, list_b);
	three_numbers(p, list_a);
	curr_b = *list_b;
	curr_a = *list_a;
	while (curr_b != NULL)
	{
		while (curr_a->p < curr_b->p)
		{
			printf("curr es %d, rotate\n", curr_a->x);
			p.n = p.n + rotate(list_a);
			curr_a = *list_a;
		}
		printf("push %d\n", curr_b->x);
		p.n = p.n + push(list_b, list_a);
		curr_b = *list_b;
		printf("curr b es %d\n", curr_b->x);
	}
	curr_a = *list_a;
	while (curr_a->p != 0)
	{
		p.n = p.n + rotate(list_a);
		curr_a = *list_a;
		printf("rotate y curr es %d\n", curr_a->x);
	}
}

int	main(int argc, char	**argv)
{
	t_node	*list_a;
	t_node	*list_b;
	t_node	*curr;
	t_push	p;

	list_a = NULL;
	list_b = NULL;
	if (argc < 3)
		return (0);
	p.i = 1;
	while (argv[p.i])
		insert_end_node(&list_a, ft_atoi(argv[p.i++]), 0);
	if ((check_numbers(&list_a) == 0))
		return (0);
	simplify_num((p.i - 2), &list_a);
	five_numbers(p, &list_a, &list_b);
	curr = list_a;
	while (curr != NULL)
	{
		printf("A %d\n", curr->x);
		curr = curr->next;
	}
	free_node(&list_a);
	free_node(&list_b);
	return (0);
}
