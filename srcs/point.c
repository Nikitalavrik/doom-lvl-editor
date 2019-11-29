/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlavrine <nlavrine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 17:18:55 by nlavrine          #+#    #+#             */
/*   Updated: 2019/11/29 17:28:29 by nlavrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_editor.h"

void		push_point(t_epoint **begin, t_coords *coord)
{
	t_epoint *iterator;
	t_epoint *new_point;

	new_point = ft_memalloc(sizeof(t_epoint));
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

void		pop_point(t_epoint **begin)
{
	t_epoint *next_begin;
	t_epoint *iterator;

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

void	delete_stick_point(t_editor *editor)
{
	if (editor->point_cnt)
	{
		delete_stick_line_room(editor);
		editor->point_cnt = 0;
	}
}
