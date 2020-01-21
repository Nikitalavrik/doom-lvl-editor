/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   choice_win.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbratsla <tbratsla@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 17:49:52 by tbratsla          #+#    #+#             */
/*   Updated: 2019/11/22 17:49:53 by tbratsla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_editor.h"

Uint32	get_pix_from_text(SDL_Surface *text, int x, int y)
{
	Uint32	*tmp;

	tmp = text->pixels + y * text->pitch +
		x * text->format->BytesPerPixel;
	return (*tmp);
}

void	ft_set_new_pixel(t_editor *editor, int x, int y)
{
	Uint32	*pic;

	if (x > 0 && x < C_WIDTH && y > 0 && y < C_HEIGHT)
	{
		pic = editor->new_win->sur->pixels + y * editor->new_win->sur->pitch +
		x * editor->new_win->sur->format->BytesPerPixel;
		*pic = 0x0062ff;
	}
}

void	draw_list_text(t_editor *editor)
{
	int		x;
	int		y;
	Uint32	*pic;

	y = 0;
	while (y < 712)
	{
		x = 0;
		while (x < C_WIDTH)
		{
			pic = editor->new_win->sur->pixels +\
			y * editor->new_win->sur->pitch +
			x * editor->new_win->sur->format->BytesPerPixel;
			*pic = editor->new_win->screen[y + editor->new_win->cam_y][x];
			x++;
		}
		y++;
	}
}

void	put_to_screen(t_editor *editor, int x, int y, Uint32 collor)
{
	editor->new_win->screen[y][x] = collor;
}

void	choice_win(t_editor *editor, SDL_Event event, int flag, void *param)
{
	new_win_init(editor, param, flag);
	if (flag == 1 || flag == 2)
		add_textures_to_screen(editor);
	else if (flag == 3)
		add_sprites_to_screen(editor);
	draw_first_rectangle(editor);
	draw_list_text(editor);
	draw_button(editor, 1);
	SDL_UpdateWindowSurface(editor->new_win->win);
	while (1)
	{
		while (SDL_PollEvent(&event))
			new_event(editor, event);
		if (!editor->new_win)
			return ;
		SDL_UpdateWindowSurface(editor->new_win->win);
	}
	SDL_StopTextInput();
}
