/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clcarre <clcarrer@student.42madrid.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 09:21:32 by clcarre           #+#    #+#             */
/*   Updated: 2022/07/13 16:05:37 by clcarre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "libft/ft_atoi.c"

void	insert_end_node(t_node **list, int value)
{
	t_node	*new_node;
	t_node	*curr;

	new_node = malloc(sizeof(t_node));
	if (!new_node)
		perror("malloc error");
	new_node->x = value;
	new_node->next = NULL;
	new_node->prev = NULL;
	if (*list == NULL)
		*list = new_node;
	else
	{
		curr = *list;
		while (curr->next != NULL)
			curr = curr->next;
		curr->next = new_node;
		new_node->prev = curr;
	}
}

void	swap(t_node **list)
{
	int	value;

	if (*list == NULL || (*list)->next == NULL)
		exit (0);
	value = (*list)->x;
	(*list)->x = (*list)->next->x;
	(*list)->next->x = value;
}

void	rotate(t_node **list)
{
	t_node	*curr;
	int		value;

	if (*list == NULL || (*list)->next == NULL)
		exit (0);
	value = (*list)->x;
	curr = *list;
	*list = (*list)->next;
	free(curr);
	insert_end_node(list, value);
}

int	main(int argc, char	**argv, char **envp)
{
	t_node	*list_a;
	t_node	*list_b;
	t_node	*curr;
	int		i;

	list_a = NULL;
	list_b = NULL;
	i = 1;
	while (argv[i])
		insert_end_node(&list_a, ft_atoi(argv[i++]));
	swap(&list_a);
	rotate(&list_a);
	curr = list_a;
	while (curr != NULL)
	{
		printf("%d\n", curr->x);
		curr = curr->next;
	}
	return (0);
}
