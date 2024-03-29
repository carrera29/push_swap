/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clcarrer <clcarrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 12:12:53 by clcarrer          #+#    #+#             */
/*   Updated: 2022/10/28 10:42:00 by clcarrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

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

int	check_numbers(t_push *p, t_node **list)
{
	t_node	*curr;
	t_node	*aux;

	p->n = 1;
	curr = *list;
	while (curr != NULL)
	{	
		aux = curr->next;
		while (aux != NULL)
		{
			if (curr->x == aux->x)
				error_msg(p, list, &p->list_b);
			if (curr->x > aux->x)
				p->n = 0;
			aux = aux->next;
		}
		curr = curr->next;
	}
	return (p->n);
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

void	check_in(t_push *p, char **argv)
{
	p->n = 1;
	while (argv[p->n])
	{
		p->number = ft_split(argv[p->n++], ' ');
		p->i = 0;
		while (p->number[p->i])
			insert_end_node(&p->list_a, ft_atoi(p, p->number[p->i++]), 0);
		free_split(p->number);
	}
	p->i = 0;
	p->last = p->list_a;
	while (p->last->next != NULL)
	{
		p->last = p->last->next;
		p->i++;
	}
	p->i++;
}
