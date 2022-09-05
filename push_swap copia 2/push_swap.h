/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chloeplatt <chloeplatt@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 09:30:41 by clcarre           #+#    #+#             */
/*   Updated: 2022/09/05 14:56:43 by chloeplatt       ###   ########.fr       */
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
	int	n;
}	t_push;

// write numbers
int		ft_atoi(const char *str);

// move_numbers
void	free_node(t_node **list);
void	insert_end_node(t_node **list, int value, int position);
void	insert_beginning_node(t_node **list, int value, int position);
int		swap(t_node **list);
int		rotate(t_node **list);
int		reverse_rotate(t_node **list);
int		push(t_node **pusher, t_node **to_list);

#endif