/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_numbers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clcarre <clcarrer@student.42madrid.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 16:31:48 by clcarre           #+#    #+#             */
/*   Updated: 2022/08/25 12:13:20 by clcarre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	free_node(t_node **list)
{
	t_node	*aux;
	t_node	*curr;

	curr = *list;
	while (curr != NULL)
	{
		aux = curr;
		curr = curr->next;
		free(aux);
	}
	*list = NULL;
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
	if (new_node->next != NULL)
		(*list)->next->prev = new_node;
	*list = new_node;
}

void	swap(t_node **list)
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
}

void	rotate(t_node **list)
{
	t_node	*curr;
	int		value;
	int		position;

	if (*list == NULL || (*list)->next == NULL)
		exit (0);
	value = (*list)->x;
	position = (*list)->p;
	curr = *list;
	*list = (*list)->next;
	free(curr);
	insert_end_node(list, value, position);
}

void	reverse_rotate(t_node **list)
{
	t_node	*curr;
	t_node	*aux;
	int		value;
	int		position;

	curr = malloc(sizeof(t_node));
	aux = malloc(sizeof(t_node));
	if (!aux || !curr || *list == NULL || (*list)->next == NULL)
		exit (0);
	curr = *list;
	while (curr->next != NULL)
		curr = curr->next;
	value = curr->x;
	position = curr->p;
	aux = curr;
	curr = curr->prev;
	curr->next = NULL;
	free(aux);
	insert_beginning_node(list, value, position);
}

void	push(t_node **pusher, t_node **to_list)
{
	t_node	*aux;
	int		value;
	int		position;

	aux = malloc(sizeof(t_node));
	if (!aux || *pusher == NULL)
		exit (0);
	value = (*pusher)->x;
	position = (*pusher)->p;
	aux = *pusher;
	*pusher = (*pusher)->next;
	insert_beginning_node(to_list, value, position);
	free(aux);
}
