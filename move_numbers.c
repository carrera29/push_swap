/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_numbers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chloeplatt <chloeplatt@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 16:31:48 by clcarre           #+#    #+#             */
/*   Updated: 2022/10/07 18:41:28 by chloeplatt       ###   ########.fr       */
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

// int	main(int argc, char **argv)
// {
// 	t_node	*list_a;
// 	t_node	*list_b;
// 	t_node	*curr;
// 	t_node	*last;
// 	t_push	p;

// 	list_a = NULL;
// 	list_b = NULL;
// 	if (argc < 3)
// 		return (0);
// 	p.n_max = 1;
// 	while (argv[p.n_max])
// 		insert_end_node(&list_a, ft_atoi(argv[p.n_max++]), 0);
// 	push(&list_a, &list_b, 0);
// 	push(&list_a, &list_b, 0);
// 	push(&list_a, &list_b, 0);
// 	push(&list_a, &list_b, 0);
// 	push(&list_b, &list_a, 1);
// 	push(&list_b, &list_a, 1);
// 	curr = list_a;
// 	while (curr != NULL)
// 	{
// 		printf("A %d\n", curr->x);
// 		curr = curr->next;
// 	}
// 	printf("\n");
// 	curr = list_b;
// 	while (curr != NULL)
// 	{
// 		printf("B %d\n", curr->x);
// 		curr = curr->next;
// 	}
// }