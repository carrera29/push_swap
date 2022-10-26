/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clcarrer <clcarrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 09:30:41 by clcarre           #+#    #+#             */
/*   Updated: 2022/10/26 12:25:39 by clcarrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <unistd.h>
# include <stdio.h>
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
	t_node	*aux;
	t_node	*last;
	t_node	*last_b;
	char	**number;
	int		unsorted;
	int		i;
	int		n;
	int		x;
	int		d;
	int		steps;
	int		rot;
	int		rev;
	int		min;
	int		max;
	int		mid;
	int		mp;
}			t_push;

//		utils
void	free_node(t_push *p, t_node **list_a, t_node **list_b);
void	error_msg(t_push *p, t_node **list_a, t_node **list_b);
int		ft_atoi(t_push *p, const char *str);

//		split
char	**ft_split(char const *s, char c);

//		check_in
void	simplify_num(int i, t_node **list);
int		check_numbers(t_push *p, t_node **list);
void	insert_beginning_node(t_node **list, int value, int position);
void	insert_end_node(t_node **list, int value, int position);
void	check_in(t_push *p, char **argv);

//		move_numbers
void	swap(t_node **list, int i);
void	rotate(t_node **list, t_node **last, int i);
void	reverse_rotate(t_node **list, t_node **last, int i);
void	push(t_node **pusher, t_node **to_list, int i);

//		long_stack
int		is_shortest_b(t_push *p, t_node **list, t_node **last);
int		is_shortest_a(t_push *p, int max, t_node **list, t_node **last);
void	push_stack_b(t_push *p, t_node **list_a, t_node **list_b);
void	sort_stack_a(t_push *p, t_node **list_a, t_node **list_b);
void	long_stack(t_push *p, t_node **list_a, t_node **list_b);

#endif