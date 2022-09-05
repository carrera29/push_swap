/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_numbers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chloeplatt <chloeplatt@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 16:31:48 by clcarre           #+#    #+#             */
/*   Updated: 2022/09/05 14:52:15 by chloeplatt       ###   ########.fr       */
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
	if ((*list) != NULL)
		(*list)->prev = new_node;
	*list = new_node;
}

int	swap(t_node **list)
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
	return (1);
}

int	rotate(t_node **list)
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
	free(aux);
	return (1);
}

int	reverse_rotate(t_node **list)
{
	t_node	*curr;
	t_node	*aux;
	int		value;
	int		position;

	if (*list == NULL || (*list)->next == NULL)
		exit (0);
	curr = *list;
	while (curr->next != NULL)
		curr = curr->next;
	value = curr->x;
	position = curr->p;
	aux = curr;
	if (curr->prev != NULL)
		curr = curr->prev;
	curr->next = NULL;
	insert_beginning_node(list, value, position);
	free(aux);
	return (1);
}

int	push(t_node **pusher, t_node **to_list)
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
	free(aux);
	return (1);
}
