/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chloeplatt <chloeplatt@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 09:21:32 by clcarre           #+#    #+#             */
/*   Updated: 2022/09/02 12:30:13 by chloeplatt       ###   ########.fr       */
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

int	sort_b(t_node **list_a, t_node **list_b)
{
	t_node	*curr;
	int		n;

	n = 0;
	
	return (n + 1);
}

int	sort_a(int i, t_node **list_a, t_node **list_b, int	n_zeros)
{
	t_node	*curr;

	curr = *list_a;
	printf("curr es %d\n", curr->p);
	if ((((curr->p) >> i) & 1) == 0)
	{
		printf("push %d to B\n", curr->p);
		push(list_a, list_b);
		n_zeros--;
	}
	else
	{
		rotate(list_a);
		printf("rotate -> ahora curr es %d\n", curr->p);
	}
	return (n_zeros);
}

void push_swap(t_node **list_a, t_node **list_b, t_node **last)
{
	t_node		*curr;
	int			i;
	int			n_zeros;
	static int	n;

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
			n_zeros = sort_a(i, list_a, list_b, n_zeros);
			n++;
		}
		printf("\n");
		curr = *list_b;
		while (curr != NULL)
		{
			printf("push %d to A\n", curr->p);
			push(list_b, list_a);
			curr = curr->next;
			n++;
		}
		i++;
	}
	printf("el numero de pasos es %d\n", n);
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
	free_node(&list_a);
	free_node(&list_b);
	return (0);
}
