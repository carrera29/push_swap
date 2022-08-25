/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clcarre <clcarrer@student.42madrid.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 09:30:41 by clcarre           #+#    #+#             */
/*   Updated: 2022/08/22 16:40:15 by clcarre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <unistd.h>
# include <stdio.h>
// malloc() // free()
# include <stdlib.h>

typedef struct node
{
	int			x;
	int			p;
	struct node	*next;
	struct node	*prev;
}	t_node;

typedef struct push_swap
{
	int	i;
	int	c;
	int	x;
}	t_push;

// write numbers
int		ft_atoi(const char *str);

// move_numbers
void	free_node(t_node **list);
void	insert_end_node(t_node **list, int value, int position);
void	insert_beginning_node(t_node **list, int value, int position);
void	swap(t_node **list);
void	rotate(t_node **list);
void	reverse_rotate(t_node **list);
void	push(t_node **pusher, t_node **to_list);

#endif