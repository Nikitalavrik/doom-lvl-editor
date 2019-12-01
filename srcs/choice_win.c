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

void	draw_button(t_editor *editor, int button_num)
{
	SDL_Rect	rect1;
	SDL_Color	color;
	SDL_Surface	*message;
	SDL_Rect	f;

	rect1.x = editor->new_win->button_coord.x;
	rect1.y = editor->new_win->button_coord.y;
	rect1.w = editor->new_win->button_coord.x1 - editor->new_win->button_coord.x;
	rect1.h = editor->new_win->button_coord.y1 - editor->new_win->button_coord.y;
	SDL_BlitScaled(editor->button[button_num], NULL ,editor->new_win->sur, &rect1);
	f.x = rect1.x + 95;
	f.y = rect1.y + 10;
	color = (SDL_Color){200, 200, 100, 0};
	message = TTF_RenderText_Solid(editor->font1, "SAVE AND EXIT", color);
	SDL_BlitSurface(message, NULL, SDL_GetWindowSurface(editor->new_win->win), &f);
	SDL_UpdateWindowSurface(editor->new_win->win);
}

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
	while (y1 < 128)
	{
		x1 = 0;
		x = old_x;
		while (x1 < 128)
		{
			if (editor->new_win->param_flag == 1 || editor->new_win->param_flag == 2)
				editor->new_win->screen[y][x] = editor->doom->text[*k].tex[y1 * 128 + x1];
			else if (editor->new_win->param_flag == 3)
				editor->new_win->screen[y][x] = editor->doom->text[*k].tex[y1 * 128 + x1];
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

	coord.x = (editor->new_win->mouse.x / 148 * 148 + 20);
	coord.x1 = coord.x + 128;
	coord.y = ((editor->new_win->mouse.y + editor->new_win->cam_y) / 148 * 148 + 20);
	coord.y1 = coord.y + 128;
	editor->new_win->active_num.tex_num = editor->new_win->mouse.x / 148  +\
		(editor->new_win->mouse.y + editor->new_win->cam_y) / 148 * C_WIDTH / 148 ;
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

void		draw_first_rectangle(t_editor *editor)
{
	int		i;
	int		n;

	i = 0;
	n = 10;
	while (n > 0)
	{
		i = editor->new_win->active_num.coord.x - n;
		while (i < editor->new_win->active_num.coord.x1 + n)
		{
			put_to_screen(editor, i, editor->new_win->active_num.coord.y - n, 0x0062ff);
			put_to_screen(editor, i, editor->new_win->active_num.coord.y1 + n, 0x0062ff);
			i++;
		}
		i = editor->new_win->active_num.coord.y - n;
		while (i <= editor->new_win->active_num.coord.y1 + n)
		{
			put_to_screen(editor, editor->new_win->active_num.coord.x - n, i, 0x0062ff);
			put_to_screen(editor, editor->new_win->active_num.coord.x1 + n, i, 0x0062ff);
			i++;
		}
		n--;
	}
}

void	set_up_text(t_editor *editor, t_coord *coord)
{
	coord->x = editor->new_win->active_num.tex_num % 4 * 148 + 20;
	coord->y = editor->new_win->active_num.tex_num / 4 * 148 + 20;
	coord->x1 = coord->x + 128;
	coord->y1 = coord->y + 128;
}

void	new_win_init(t_editor *editor, void *param, int flag)
{
	int		i;

	i = 0;
	editor->new_win = ft_memalloc(sizeof(t_win));
	editor->new_win->win = SDL_CreateWindow("Textures", SDL_WINDOWPOS_UNDEFINED, \
		SDL_WINDOWPOS_UNDEFINED, 924,\
		712, 0);
	editor->new_win->sur = SDL_GetWindowSurface(editor->new_win->win);
	editor->new_win->win_id = SDL_GetWindowID(editor->new_win->win);
	editor->new_win->mem_space = 148 * editor->doom->count_text / 4 + 20;
	editor->new_win->screen = ft_memalloc(sizeof(Uint32 *) * editor->new_win->mem_space);
	while (i < editor->new_win->mem_space)
	{
		editor->new_win->screen[i] = ft_memalloc(sizeof(Uint32) * C_WIDTH);
		i++;
	}
	editor->new_win->cam_y = 0;
	editor->new_win->delim_x = 148;
	editor->new_win->delim_y = 148;
	editor->new_win->events = ft_memalloc(sizeof(t_ev));
	editor->new_win->active_num.tex_num = -1;
	editor->new_win->ws_coord1 = get_input_coord(C_WIDTH + 210, 20);
	editor->new_win->ws_coord2 = get_input_coord(C_WIDTH + 210, 60);
	editor->new_win->ws_coord3 = get_input_coord(C_WIDTH + 210, 100);
	editor->new_win->ws_coord4 = get_input_coord(C_WIDTH + 210, 140);
	editor->new_win->param = param;
	editor->new_win->button_coord.x = C_WIDTH + 5;
	editor->new_win->button_coord.y = C_HEIGHT - 50;
	editor->new_win->button_coord.x1 = editor->new_win->button_coord.x + 300;
	editor->new_win->button_coord.y1 = editor->new_win->button_coord.y + 32;
	if (flag == 1)
	{
		editor->new_win->param_par.line = (t_eline *)param;
		editor->new_win->active_num.tex_num = editor->new_win->param_par.line->num_of_textures - 1;
		set_up_text(editor,  &editor->new_win->active_num.coord);
	}
	else if (flag == 2)
	{
		editor->new_win->param_par.room = (t_room *)param;
		editor->new_win->active_num.tex_num = editor->new_win->param_par.room->num_of_textures - 1;
		set_up_text(editor,  &editor->new_win->active_num.coord);
	}
	else if (flag == 3)
		editor->new_win->param_par.sprite = (t_esprite *)param;
	editor->new_win->param_flag = flag;
	draw_right_menu(editor);
}

void		choice_win(t_editor *editor, SDL_Event event, int flag, void *param)
{
	SDL_StartTextInput();
	new_win_init(editor, param, flag);
	add_textures_to_screen(editor);
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
