/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlavrine <nlavrine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/01 17:34:14 by mkhomich          #+#    #+#             */
/*   Updated: 2019/11/24 14:14:56 by nlavrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/doom.h"

void    vector(t_toch start, t_toch end, t_vec *res)
{
    res->x = start.x - end.x;
    res->y = start.y - end.y;
    res->z = start.z - end.z;
    res->len = sqrt(res->x * res->x + res->y * res->y + res->z * res->z);
}

void    grid_sec(t_doom *doom, t_sec *sec)
{
    int   x;
    int   y;

    y = 0;
    vector(doom->toch[sec->pts[0]], doom->toch[sec->pts[1]], &sec->v1);
    vector(doom->toch[sec->pts[1]], doom->toch[sec->pts[2]], &sec->v2);
    sec->tex_x = (sec->v2.len * 10) / 64.0;
    sec->tex_y = (sec->v1.len * 10) / 64.0;
    sec->toch = (t_toch**)malloc(sizeof(t_toch*) * (sec->tex_y + 2));
    while (y < sec->tex_y + 1)
    {
        x = 0;
        sec->toch[y] = (t_toch*)malloc(sizeof(t_toch) * (sec->tex_x + 2));
        while (x < sec->tex_x + 1)
        {
            if (x < sec->tex_x && y < sec->tex_y)
            {
                sec->toch[y][x].x = (doom->toch[sec->pts[1]].x - (sec->v2.x * (float)x) / sec->tex_x + (sec->v1.x * (float)y) / sec->tex_y);
				sec->toch[y][x].y = (doom->toch[sec->pts[1]].y - (sec->v2.y * (float)x) / sec->tex_x + (sec->v1.y * (float)y) / sec->tex_y);
				sec->toch[y][x].z = (doom->toch[sec->pts[1]].z - (sec->v2.z * (float)x) / sec->tex_x + (sec->v1.z * (float)y) / sec->tex_y);
            }
            else if (x >= sec->tex_x && y < sec->tex_y)
            {
                sec->toch[y][x].x = (doom->toch[sec->pts[1]].x - sec->v2.x + (sec->v1.x * (float)y) / sec->tex_y);
                sec->toch[y][x].y = (doom->toch[sec->pts[1]].y - sec->v2.y + (sec->v1.y * (float)y) / sec->tex_y);
                sec->toch[y][x].z = (doom->toch[sec->pts[1]].z - sec->v2.z + (sec->v1.z * (float)y) / sec->tex_y);
            }
            else if (x < sec->tex_x && y >= sec->tex_y)
            {
                sec->toch[y][x].x = (doom->toch[sec->pts[1]].x - (sec->v2.x * (float)x) / sec->tex_x + sec->v1.x);
                sec->toch[y][x].y = (doom->toch[sec->pts[1]].y - (sec->v2.y * (float)x) / sec->tex_x + sec->v1.y);
                sec->toch[y][x].z = (doom->toch[sec->pts[1]].z - (sec->v2.z * (float)x) / sec->tex_x + sec->v1.z);
            }
            else if (x >= sec->tex_x && y >= sec->tex_y)
            {
                sec->toch[y][x].x = (doom->toch[sec->pts[1]].x - sec->v2.x + sec->v1.x);
                sec->toch[y][x].y = (doom->toch[sec->pts[1]].y - sec->v2.y + sec->v1.y);
                sec->toch[y][x].z = (doom->toch[sec->pts[1]].z - sec->v2.z + sec->v1.z);
            }
            x++;
        }
        y++;
    }
}

