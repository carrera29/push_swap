/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_numbers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clcarrer <clcarrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 16:31:48 by clcarre           #+#    #+#             */
/*   Updated: 2022/10/20 17:53:25 by clcarrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	free_node(t_push *p, t_node **list_a, t_node **list_b)
{
	p->curr = *list_a;
	p->i = 2;
	while (p->i--)
	{
		while (p->curr != NULL)
		{
			p->aux = p->curr;
			p->curr = p->curr->next;
			free(p->aux);
		}
		p->curr = *list_b;
	}
	*list_a = NULL;
	*list_b = NULL;
}

void	swap(t_node **list, int i)
{
	int	value;

	if (*list == NULL || (*list)->next == NULL)
		exit (0);
	value = (*list)->x;
	(*list)->x = (*list)->next->x;
	(*list)->next->x = value;
	value = (*list)->p;
	(*list)->p = (*list)->next->p;
	(*list)->next->p = value;
	if (i == 0)
		write(1, "sa\n", 3);
	else
		write(1, "sb\n", 3);
}

void	rotate(t_node **list, t_node **last, int i)
{
	t_node	*aux;
	int		value;
	int		position;

	if (*list == NULL || (*list)->next == NULL)
		exit (0);
	value = (*list)->x;
	position = (*list)->p;
	aux = *list;
	*list = (*list)->next;
	(*list)->prev = NULL;
	insert_end_node(list, value, position);
	*last = *list;
	while ((*last)->next != NULL)
		*last = (*last)->next;
	if (i == 0)
		write(1, "ra\n", 3);
	else
		write(1, "rb\n", 3);
	free(aux);
}

void	reverse_rotate(t_node **list, t_node **last, int i)
{
	t_node	*curr;
	t_node	*aux;
	int		value;
	int		position;

	if (*list == NULL || (*list)->next == NULL)
		exit (0);
	value = (*last)->x;
	position = (*last)->p;
	aux = *last;
	if ((*last)->prev != NULL)
		*last = (*last)->prev;
	(*last)->next = NULL;
	insert_beginning_node(list, value, position);
	if (i == 0)
		write(1, "rra\n", 4);
	else
		write(1, "rrb\n", 4);
	free(aux);
}

void	push(t_node **pusher, t_node **to_list, int i)
{
	t_node	*aux;
	int		value;
	int		position;

	if (*pusher == NULL)
		exit (0);
	value = (*pusher)->x;
	position = (*pusher)->p;
	aux = *pusher;
	*pusher = (*pusher)->next;
	if ((*pusher) != NULL)
		(*pusher)->prev = NULL;
	insert_beginning_node(to_list, value, position);
	if (i == 0)
		write(1, "pb\n", 3);
	else
		write(1, "pa\n", 3);
	free(aux);
}
