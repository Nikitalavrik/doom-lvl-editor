/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   choice_win_bar.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbratsla <tbratsla@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 11:29:33 by tbratsla          #+#    #+#             */
/*   Updated: 2019/11/30 11:29:34 by tbratsla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_editor.h"

void	draw_background(t_editor *editor)
{
	int		x;
	int		y;
	Uint32	*pic;

	x = C_WIDTH;
	while (x < 1024)
	{
		y = 0;
		while (y < C_HEIGHT)
		{
			pic = editor->new_win->sur->pixels + y * editor->new_win->sur->pitch +
			x * editor->new_win->sur->format->BytesPerPixel;
			*pic = 0xcccccc;
			y++;
		}
		x++;
	}
}

void	draw_caption(t_editor *editor, t_coord coord, SDL_Window *win, char *caption)
{
	SDL_Color	color;
	SDL_Surface	*message;
	SDL_Rect	f;

	f.x = coord.x - 190;
	f.y = coord.y + 5;
	color = (SDL_Color){0, 0, 0, 0};
	message = TTF_RenderText_Solid(editor->font1, caption, color);
	SDL_BlitSurface(message, NULL, SDL_GetWindowSurface(win), &f);
	SDL_UpdateWindowSurface(win);
	SDL_FreeSurface(message);
}

void 	add_text_to_space(t_editor *editor, t_coord coord, SDL_Window *win, char *text)
{
	SDL_Color	color;
	SDL_Surface	*message;
	SDL_Rect	f;

	f.x = coord.x + 5;
	f.y = coord.y + 5;
	color = (SDL_Color){0, 0, 0, 0};
	message = TTF_RenderText_Solid(editor->font1, text, color);
	SDL_BlitSurface(message, NULL, SDL_GetWindowSurface(win), &f);
	SDL_UpdateWindowSurface(win);
	SDL_FreeSurface(message);
}

t_coord		get_input_coord(int x, int y)
{
	t_coord coord;

	coord.x = x;
	coord.y = y;
	coord.x1 = x + 80;
	coord.y1 = y + 20;
	// printf("coord.x = %i\ncoord.y = %i\ncoord.x1 = %i\ncoord.y1 = %i\n\n", coord.x, coord.y, coord.x1, coord.y1);
	return (coord);
}

void		draw_white_space(t_coord coord, SDL_Surface *surf)
{
	int 	y;
	Uint32	*pic;

	y = coord.y;
	while (coord.x < coord.x1)
	{
		coord.y = y;
		while (coord.y < coord.y1)
		{
			pic = surf->pixels + coord.y * surf->pitch +
			coord.x * surf->format->BytesPerPixel;
			*pic = BACKGROUND;
			coord.y++;
		}
		coord.x++;
	}
}

void		draw_right_menu(t_editor *editor)
{
	draw_background(editor);
	draw_caption(editor, editor->new_win->ws_coord1, editor->new_win->win, "Wall angle:");
	draw_caption(editor, editor->new_win->ws_coord2, editor->new_win->win, "Height the wall:");
	draw_caption(editor, editor->new_win->ws_coord3, editor->new_win->win, "Height wall above the floor:");
	draw_caption(editor, editor->new_win->ws_coord4, editor->new_win->win, "Transparency:");
	draw_white_space(editor->new_win->ws_coord1, editor->new_win->sur);
	draw_white_space(editor->new_win->ws_coord2, editor->new_win->sur);
	draw_white_space(editor->new_win->ws_coord3, editor->new_win->sur);
	draw_white_space(editor->new_win->ws_coord4, editor->new_win->sur);
	add_text_to_space(editor, editor->new_win->ws_coord1, editor->new_win->win, "0");
	add_text_to_space(editor, editor->new_win->ws_coord2, editor->new_win->win, "0");
	add_text_to_space(editor, editor->new_win->ws_coord3, editor->new_win->win, "0");
	add_text_to_space(editor, editor->new_win->ws_coord4, editor->new_win->win, "0");
}
