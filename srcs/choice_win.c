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
			pic = editor->new_win->sur->pixels + y * editor->new_win->sur->pitch +
			x * editor->new_win->sur->format->BytesPerPixel;
			*pic = editor->new_win->screen[y + editor->new_win->cam_y][x];
			x++;
		}
		y++;
	}
}

void	put_text_to_screen(t_editor *editor, int y, int x, int *k)
{
	int		x1;
	int		y1;
	int		old_x;

	y1 = 0;
	old_x = x;
	while (y1 < 64)
	{
		x1 = 0;
		x = old_x;
		while (x1 < 64)
		{
			editor->new_win->screen[y][x] =\
			get_pix_from_text(editor->textures[*k % TEXTNUM], x1, y1);
			x++;
			x1++;
		}
		y1++;
		y++;
	}
	(*k)++;
}

void	put_to_screen(t_editor *editor, int x, int y, Uint32 collor)
{
	editor->new_win->screen[y][x] = collor;
}

void	add_textures_to_screen(t_editor *editor)
{
	int		x;
	int		y;
	int		k;

	x = 20;
	y = 20;
	k = 0;
	while (y + 64 < 3000)
	{
		x = 20;
		while (x + 64 < C_WIDTH)
		{
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

t_coord		get_coord(t_editor *editor)
{
	t_coord	coord;

	coord.x = (editor->new_win->mouse.x / 84 * 84 + 20);
	coord.x1 = coord.x + 64;
	coord.y = ((editor->new_win->mouse.y + editor->new_win->cam_y) / 84 * 84 + 20);
	coord.y1 = coord.y + 64;
	editor->new_win->active_num.tex_num = editor->new_win->mouse.x / 84  +\
		(editor->new_win->mouse.y + editor->new_win->cam_y) / 84 * C_WIDTH / 84 ;
	editor->new_win->active_num.coord.x = coord.x;
	editor->new_win->active_num.coord.y = coord.y;
	editor->new_win->active_num.coord.x1 = coord.x1;
	editor->new_win->active_num.coord.y1 = coord.y1;
	return (coord);
}

void		remove_rectangle(t_editor *editor)
{
	int		i;
	int		n;

	n = 10;
	while (n > 0)
	{
		i = editor->new_win->active_num.coord.x - n;
		while (i < editor->new_win->active_num.coord.x1 + n)
		{
			put_to_screen(editor, i, editor->new_win->active_num.coord.y - n, 0x000000);
			put_to_screen(editor, i, editor->new_win->active_num.coord.y1 + n, 0x000000);
			i++;
		}
		i = editor->new_win->active_num.coord.y - n;
		while (i <= editor->new_win->active_num.coord.y1 + n)
		{
			put_to_screen(editor, editor->new_win->active_num.coord.x - n, i, 0x000000);
			put_to_screen(editor, editor->new_win->active_num.coord.x1 + n, i, 0x000000);
			i++;
		}
		n--;
	}
	draw_list_text(editor);
}

void		draw_rectangle(t_editor *editor)
{
	t_coord	coord;
	int		i;
	int		n;

	i = 0;
	n = 10;
	if (editor->new_win->active_num.tex_num > -1)
		remove_rectangle(editor);
	coord = get_coord(editor);
	while (n > 0)
	{
		i = coord.x - n;
		while (i < coord.x1 + n)
		{
			put_to_screen(editor, i, coord.y - n, 0x0062ff);
			put_to_screen(editor, i, coord.y1 + n, 0x0062ff);
			i++;
		}
		i = coord.y - n;
		while (i <= coord.y1 + n)
		{
			put_to_screen(editor, coord.x - n, i, 0x0062ff);
			put_to_screen(editor, coord.x1 + n, i, 0x0062ff);
			i++;
		}
		n--;
	}
	draw_list_text(editor);
}

void	new_win_init(t_editor *editor)
{
	int		i;

	i = 0;
	editor->new_win = ft_memalloc(sizeof(t_win));
	editor->new_win->win = SDL_CreateWindow("Textures", SDL_WINDOWPOS_UNDEFINED, \
		SDL_WINDOWPOS_UNDEFINED, 1024,\
		712, 0);
	editor->new_win->sur = SDL_GetWindowSurface(editor->new_win->win);
	editor->new_win->win_id = SDL_GetWindowID(editor->new_win->win);
	editor->new_win->screen = ft_memalloc(sizeof(Uint32 *) * 3000);
	while (i < 3000)
	{
		editor->new_win->screen[i] = ft_memalloc(sizeof(Uint32) * C_WIDTH);
		i++;
	}
	editor->new_win->cam_y = 0;
	editor->new_win->delim_x = 84;
	editor->new_win->delim_y = 84;
	editor->new_win->events = ft_memalloc(sizeof(t_ev));
	editor->new_win->active_num.tex_num = -1;
	editor->new_win->input_text = ft_strdup("");
}

void		draw_white_space(t_editor *editor)
{
	t_coord coord;
	Uint32	*pic;

	coord.x = C_WIDTH + 20;
	coord.y = 20;
	coord.x1 = coord.x + 100;
	coord.y1 = 40;
	while (coord.x < coord.x1)
	{
		coord.y = 20;
		while (coord.y < coord.y1)
		{
			pic = editor->new_win->sur->pixels + coord.y * editor->new_win->sur->pitch +
			coord.x * editor->new_win->sur->format->BytesPerPixel;
			*pic = BACKGROUND;
			coord.y++;
		}
		coord.x++;
	}
}

void		choice_win(t_editor *editor, SDL_Event event, int flag)
{
	flag++;
	SDL_StartTextInput();
	new_win_init(editor);
	add_textures_to_screen(editor);
	draw_list_text(editor);
	draw_white_space(editor);
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
