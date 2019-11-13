/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   room.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nikita <nikita@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 15:21:12 by nikita            #+#    #+#             */
/*   Updated: 2019/11/13 17:29:31 by nikita           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_editor.h"

t_coords     *check_room(t_editor *editor)
{
    t_point *begin;
    t_point *end;

    begin = editor->point;
    if (begin)
    {
        end = editor->point;
        while (end->next)
            end = end->next;
        if (end->coord == begin->coord)
            return (NULL);
    }
    return (end->coord);
}

void    close_room(t_editor *editor)
{
    t_coords    *last;

    if ((last = check_room(editor)))
    {
         push_point(&editor->point, last);
    }
    push_room(&editor->rooms, editor->point);
    editor->point = NULL;
}
