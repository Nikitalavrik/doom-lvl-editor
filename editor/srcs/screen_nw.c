/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screen_nw.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbratsla <tbratsla@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 18:17:13 by tbratsla          #+#    #+#             */
/*   Updated: 2020/01/21 18:17:15 by tbratsla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_editor.h"

void	add_textures_to_screen(t_editor *editor)
{
	int		x;
	int		y;
	int		k;

	x = 20;
	y = 20;
	k = 1;
	while (y + 128 < 148 * editor->doom->count_text / 4 + 20)
	{
		x = 20;
		while (x + 128 < C_WIDTH)
		{
			k %= editor->doom->count_text;
			if (k == 0)
				k++;
			put_text_to_screen(editor, y, x, &k);
			x += editor->new_win->delim_x;
		}
		y += editor->new_win->delim_y;
	}
}

void	add_sprites_to_screen(t_editor *editor)
{
	int		x;
	int		y;
	int		k;

	load_correct_scale_sprite(editor);
	x = 20;
	y = 20;
	k = 1;
	while (y + 128 < editor->new_win->mem_space)
	{
		x = 20;
		while (x + 128 < C_WIDTH)
		{
			k %= 8;
			put_text_to_screen(editor, y, x, &k);
			x += editor->new_win->delim_x;
		}
		y += editor->new_win->delim_y;
	}
}

void	ft_clear_new_screen(t_editor *editor)
{
	int		x;
	int		y;

	x = 0;
	while (x < C_WIDTH)
	{
		y = 0;
		while (y < 3000)
		{
			editor->new_win->screen[y][x] = 0xcccccc;
			y++;
		}
		x++;
	}
}

void	calc_pix(t_editor *editor, t_coord *c, int *k)
{
	if (editor->new_win->param_flag == 1 ||\
		editor->new_win->param_flag == 2)
		editor->new_win->screen[c->y][c->x] =\
	editor->doom->text[*k].tex[c->y1 * 128 + c->x1];
	else if (editor->new_win->param_flag == 3)
	{
		editor->new_win->screen[c->y][c->x] =\
		(Uint32)editor->new_win->\
		editor_sprite[*k].text[0].tex[c->y1 * 128 + c->x1];
	}
	c->x++;
	c->x1++;
}

void	put_text_to_screen(t_editor *editor, int y, int x, int *k)
{
	t_coord	c;
	int		old_x;

	c.x = x;
	c.y = y;
	c.y1 = 0;
	old_x = c.x;
	while (c.y1 < 128)
	{
		c.x1 = 0;
		c.x = old_x;
		while (c.x1 < 128)
			calc_pix(editor, &c, k);
		c.y1++;
		c.y++;
	}
	(*k)++;
}
