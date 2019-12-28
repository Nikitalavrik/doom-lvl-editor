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
	SDL_FreeSurface(message);
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
			{
				editor->new_win->screen[y][x] = editor->doom->sp->text[*k].tex[y1 * 128 + x1];
			}
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

void	add_sprites_to_screen(t_editor *editor)
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
			k %= editor->doom->count_sp;
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

void		choice_win(t_editor *editor, SDL_Event event, int flag, void *param)
{
	SDL_StartTextInput();
	new_win_init(editor, param, flag);
	if (flag == 1 || flag == 2)
		add_textures_to_screen(editor);
	else
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
