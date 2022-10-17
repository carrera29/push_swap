/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chloeplatt <chloeplatt@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 09:30:41 by clcarre           #+#    #+#             */
/*   Updated: 2022/10/17 16:46:01 by chloeplatt       ###   ########.fr       */
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
	t_node	*list_a;
	t_node	*list_b;
	t_node	*curr;
	t_node	*last;
	t_node	*last_b;
	char	**numbers;
	int		i;
	int		n;
	int		x;
	int		steps;
	int		n_zeros;
	int		rot;
	int		rev;
	int		min;
	int 	max;
	int 	mid;
	int		mp;
	int		stop;
}			t_push;

// write numbers
int		ft_atoi(const char *str);
char	**ft_split(char const *s, char c);

// move_numbers
void	free_node(t_node **list);
void	insert_end_node(t_node **list, int value, int position);
void	insert_beginning_node(t_node **list, int value, int position);
void	swap(t_node **list, int i);
void	rotate(t_node **list, t_node **last, int i);
void	reverse_rotate(t_node **list, t_node **last, int i);
void	push(t_node **pusher, t_node **to_list, int i);

#endif