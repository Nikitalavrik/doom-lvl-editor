/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dlist.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlavrine <nlavrine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 14:17:34 by nikita            #+#    #+#             */
/*   Updated: 2019/11/16 15:08:42 by nlavrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_editor.h"

void		push_point(t_point **begin, t_coords *coord)
{
	t_point *iterator;
	t_point *new_point;

	new_point = ft_memalloc(sizeof(t_point));
	new_point->coord = coord;
	if (*begin)
	{
		iterator = *begin;
		new_point->next = iterator;
		iterator->prev = new_point;
		*begin = new_point;
	}
	else
		*begin = new_point;
}

void		pop_point(t_point **begin)
{
	t_point *next_begin;
	t_point *iterator;

	iterator = *begin;
	if (iterator && iterator->next)
	{
		next_begin = iterator->next;
		next_begin->prev = NULL;
		iterator->coord = NULL;
		ft_memdel((void **)&iterator);
		*begin = next_begin;
	}
	else if (iterator)
	{
		ft_memdel((void **)&iterator);
		*begin = NULL;
	}
}

void        push_room(t_room **begin, t_point *point)
{
	t_room *iterator;
	t_room *new_point;

	new_point = ft_memalloc(sizeof(t_room));
	new_point->point = point;
	if (*begin)
	{
		iterator = *begin;
		new_point->next = iterator;
		iterator->prev = new_point;
		*begin = new_point;
	}
	else
		*begin = new_point;
}