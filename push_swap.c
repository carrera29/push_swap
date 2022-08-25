/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clcarre <clcarrer@student.42madrid.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 09:21:32 by clcarre           #+#    #+#             */
/*   Updated: 2022/08/25 14:09:00 by clcarre          ###   ########.fr       */
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
			curr->p = i;
			i--;
			curr = *list;
		}
	}
}

void	push_swap(int i, t_node **list_a, t_node **list_b, t_node *last)
{
	t_node	*curr;

	curr = *list_a;
	if (((curr->p >> i) & 1) == 1)
	{
		if (((((last)->p >> i) & 1) == 0) || (((curr->next->p >> i) & 1) == 0))
		{
			while (((((last)->p >> i) & 1) == 0)
				|| (((curr->next->p >> i) & 1) == 0))
				i++;
			if (((curr->next->p >> (i - 1)) & 1) == 0)
			{
				printf("swap\n");
				swap(list_a);
			}
			else
			{
				printf("reverse rotate\n");
				reverse_rotate(list_a);
			}
		}
		else
		{
			printf("rotate\n");
			rotate(list_a);
		}
		curr = *list_a;
	}
	if (((curr->p >> i) & 1) == 0)
	{
		printf("push b\n");
		push(list_a, list_b);
	}
}

void	sort_list(t_node **list_a, t_node **list_b, t_node *last)
{
	t_node	*curr;
	int		i;
	int		bit;

	i = 0;
	while (i < 1)
	{
		curr = *list_a;
		bit = 1;
		while (curr != NULL)
		{
			if (((curr->p >> i) & 1) == 0)
				bit++;
			curr = curr->next;
		}
		while (bit-- != 0)
			push_swap(i, list_a, list_b, last);
		i++;
	}
}

int	main(int argc, char	**argv, char **envp)
{
	t_node	*list_a;
	t_node	*list_b;
	t_node	*curr;
	t_node	*last;
	int		i;

	list_a = NULL;
	list_b = NULL;
	if (argc < 3)
		return (0);
	i = 1;
	while (argv[i])
		insert_end_node(&list_a, ft_atoi(argv[i++]), 0);
	if ((check_numbers(&list_a) == 0))
		return (0);
	simplify_num((i - 2), &list_a);
	last = list_a;
	while (last->next != NULL)
		last = last->next;
	sort_list(&list_a, &list_b, last);
	curr = list_a;
	while (curr != NULL)
	{
		printf("A %d\n", curr->x);
		curr = curr->next;
	}
	printf("\n");
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
