/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chloeplatt <chloeplatt@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 09:21:32 by clcarre           #+#    #+#             */
/*   Updated: 2022/08/20 20:49:30 by chloeplatt       ###   ########.fr       */
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

void    sort_numbers(t_node **list, int i)
{
	t_node	*curr;
	t_node	*aux;

	curr = *list;
	while (i > 0)
	{
		while (curr->p != 0)
			curr = curr->next;
		aux = curr->next;
		while (aux != NULL)
		{
			if ((curr->x < aux->x) && (aux->p != 0))
				curr = aux;
			if (aux->next == NULL)
			{
				curr->p = i;
				curr = *list;
				i--;
			}
			aux = aux->next;
		}
	}
}

// void	push_swap(t_push p, t_node **list_a, t_node **list_b, t_node *last)
// {
// 	t_node	*curr;

// 	p.i = 0;
// 	curr = *list_a;
// 	while (curr != NULL)
// 	{
// 		if (((curr->x >> p.i) & 1) == 1)
// 		{
// 			if (((last->x >> p.i) & 1) == 0)
// 				reverse_rotate(list_a);
// 			else if (((curr->next->x >> p.i) & 1) == 0)
// 				swap(list_a);
// 			else
// 				rotate(list_a);
// 		}
// 		if (((curr->x >> p.i) & 1) == 0)
// 			push(list_a, list_b);
// 		else
// 			curr = curr->next;
// 	}
// }

int	main(int argc, char	**argv, char **envp)
{
	t_node	*list_a;
	t_node	*list_b;
	t_node	*curr;
	t_node	*last;
	t_push	p;

	list_a = NULL;
	list_b = NULL;
	p.i = 1;
	while (argv[p.i])
		insert_end_node(&list_a, ft_atoi(argv[p.i++]));
	if (p.i <= 1)
		return (0);
	sort_numbers(&list_a, (p.i - 2));
	last = list_a;
	while (last->next != NULL)
		last = last->next;
	// push_swap(p, &list_a, &list_b, last);
	curr = list_a;
	while (curr != NULL)
	{
		printf("A %d\n", curr->x);
		curr = curr->next;
	}
	curr = list_a;
	printf("\n");
	while (curr != NULL)
	{
		printf("B %d\n", curr->p);
		curr = curr->next;
	}
	free_node(&list_a);
	free_node(&list_b);
	return (0);
}
