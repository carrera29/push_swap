/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chloeplatt <chloeplatt@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 09:21:32 by clcarre           #+#    #+#             */
/*   Updated: 2022/10/07 18:58:18 by chloeplatt       ###   ########.fr       */
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

void	sort_a(t_push *p, int i, t_node **list_a, t_node **list_b, t_node **last)
{
	p->curr = *list_a;
	if ((((p->curr->p) >> i) & 1) == 0)
	{
		push(list_a, list_b, 0);
		p->n_zeros--;
	}
	else
		rotate(list_a, last, 0);
}

void push_swap(t_push *p, t_node **list_a, t_node **list_b, t_node **last)
{
	int			i;
	static int	n;

	i = 0;
	while (i < 32)
	{
		p->curr = *list_a;
		p->n_zeros = 0;
		while (p->curr != NULL)
		{
			if (((p->curr->p >> i) & 1) == 0)
				p->n_zeros++;
			p->curr = p->curr->next;
		}
		while (p->n_zeros != 0)
		{
			sort_a(p, i, list_a, list_b, last);
			n++;
		}
		p->curr = *list_b;
		while (p->curr != NULL)
		{
			push(list_b, list_a, 1);
			p->curr = p->curr->next;
			n++;
		}
		i++;
	}
}

int	main(int argc, char	**argv, char **envp)
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
	push_swap(&p, &p.list_a, &p.list_b, &p.last);
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
