/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clcarrer <clcarrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 12:12:53 by clcarrer          #+#    #+#             */
/*   Updated: 2022/10/19 16:51:12 by clcarrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	check_numbers(t_push *p, t_node **list)
{
	p->unsorted = 1;
	p->curr = *list;
	while (p->curr != NULL)
	{	
		p->aux = p->curr->next;
		while (p->aux != NULL)
		{
			if (p->curr->x == p->aux->x)
			{
				write(1, "Error\n", 6);
				return (1);
			}
			if (p->curr->x > p->aux->x)
				p->unsorted = 0;
			p->aux = p->aux->next;
		}
		p->curr = p->curr->next;
	}
	return (p->unsorted);
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

void	insert_end_node(t_node **list, int value, int position)
{
	t_node	*new_node;
	t_node	*curr;

	new_node = malloc(sizeof(t_node));
	if (!new_node)
		perror("malloc error");
	new_node->x = value;
	new_node->p = position;
	new_node->next = NULL;
	if (*list == NULL)
	{
		new_node->prev = NULL;
		*list = new_node;
	}
	else
	{
		curr = *list;
		while (curr->next != NULL)
			curr = curr->next;
		new_node->prev = curr;
		curr->next = new_node;
	}
}

void	insert_beginning_node(t_node **list, int value, int position)
{
	t_node	*new_node;

	new_node = malloc(sizeof(t_node));
	if (!new_node)
		exit (0);
	new_node->x = value;
	new_node->p = position;
	new_node->prev = NULL;
	new_node->next = *list;
	if ((*list) != NULL)
		(*list)->prev = new_node;
	*list = new_node;
}

void	free_node(t_push p, t_node **list_a, t_node **list_b)
{
	t_node	*aux;
	t_node	*curr;

	curr = *list_a;
	p.i = 2;
	while (p.i--)
	{
		while (curr != NULL)
		{
			aux = curr;
			curr = curr->next;
			free(aux);
		}
		curr = *list_b;
	}
	*list_a = NULL;
	*list_b = NULL;
}
