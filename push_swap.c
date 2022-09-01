/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chloeplatt <chloeplatt@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 09:21:32 by clcarre           #+#    #+#             */
/*   Updated: 2022/09/01 12:23:55 by chloeplatt       ###   ########.fr       */
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

void	sort_bits(int i, t_node **list_a, t_node **list_b, t_node **last)
{
	t_node	*curr;

	curr = *list_a;
	printf("curr es %d\n", curr->p);
	printf("last es %d\n", (*last)->p);
	while (((curr->p >> i) & 1) == 1)
	{
		if (((((curr->next->p >> i) & 1) == 0) && ((((*last)->p >> i) & 1) == 0) &&
			(curr->next->p < (*last)->p)) ||
				((((curr->next->p >> i) & 1) == 0) && ((((*last)->p >> i) & 1) == 1)))
		{
			printf("swap %d\n", curr->next->p);
			swap(list_a);
		}
		else if (((((curr->next->p >> i) & 1) == 0) && ((((*last)->p >> i) & 1) == 0) &&
			(curr->next->p > (*last)->p)) ||
				((((curr->next->p >> i) & 1) == 1) && ((((*last)->p >> i) & 1) == 0)))
		{
			printf("reverse rotate %d\n", (*last)->p);
			reverse_rotate(list_a, last);
		}
		else
		{
			rotate(list_a, last);
			curr = *list_a;
			printf("rotate -> ahora curr es %d\n", curr->p);
		}
		curr = *list_a;
	}
	printf("push %d to B\n", curr->p);
	push(list_a, list_b);
}

void	push_swap(t_node **list_a, t_node **list_b, t_node **last)
{
	t_node	*curr;
	int		i;
	int		n_zeros;

	i = 0;
	while (i < 32)
	{
		curr = *list_a;
		n_zeros = 0;
		while (curr != NULL)
		{
			if (((curr->p >> i) & 1) == 0)
				n_zeros++;
			curr = curr->next;
		}
		while (n_zeros != 0)
		{
			printf("\nPASO %d\n", n_zeros);
			sort_bits(i, list_a, list_b, last);
			n_zeros--;
		}
		curr = *list_b;
		printf("\n");
		while (curr != NULL)
		{
			push(list_b, list_a);
			printf("%d a A\n", curr->p);
			curr = curr->next;
		}
		printf("\n");
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
	push_swap(&list_a, &list_b, &last);
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
