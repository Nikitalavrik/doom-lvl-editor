/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlavrine <nlavrine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/10 16:20:39 by nlavrine          #+#    #+#             */
/*   Updated: 2019/11/15 18:03:39 by nlavrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_editor.h"

void		coords_init(t_editor *editor, t_coords *size)
{
	t_coords	iterator;
	t_coords	**coords;

	size->x = 200;
	size->y = 150;
	coords = ft_memalloc(sizeof(t_coords *) * size->y);
	iterator.y = 0;
	while (iterator.y < size->y)
	{
		coords[iterator.y] = ft_memalloc(sizeof(t_coords) * size->x);
		iterator.y++;
	}
	editor->coords = coords;
}

void		coords_rerange(t_editor *editor)
{
	t_coords	iterator;

	iterator.y = 0;
	while (iterator.y < editor->size.y)
	{
		iterator.x = 0;
		while (iterator.x < editor->size.x)
		{
			editor->coords[iterator.y][iterator.x].x = (int)(iterator.x * SQUARE_SIZE * editor->zoom) - editor->center.x;
			editor->coords[iterator.y][iterator.x].y = (int)(iterator.y * SQUARE_SIZE * editor->zoom) - editor->center.y;
			if (!editor->coords[iterator.y][iterator.x].color)
				editor->coords[iterator.y][iterator.x].color = STANDART_COLOR;
			if (!editor->coords[iterator.y][iterator.x].inc)
				editor->coords[iterator.y][iterator.x].r = 2;
			// editor->coords[iterator.y][iterator.x].inc = 0;
			iterator.x++;
		}
		iterator.y++;
	}
}

void		init_music_font(t_editor *editor)
{
	TTF_Init();
	editor->font = TTF_OpenFont("fonts/Aller_b.ttf", 24);
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
		print_error("SDL : ", " mixer didn`t init\n");
	editor->music = Mix_LoadMUS("music/Majestic.mp3");
	if (!editor->music)
		print_error("SDL : ", "cant`t find music\n");
	// Mix_PlayMusic(editor->music, -1);
	editor->mouse = 0;
}

t_editor	*init_editor(void)
{
	t_editor	*editor;

	editor = ft_memalloc(sizeof(t_editor));
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
		print_error("SDL : ", "init error\n");
	editor->win = SDL_CreateWindow("editor", 150, 100, WIDTH,
											HEIGHT, SDL_WINDOW_SHOWN);
	if (!editor->win)
		print_error("SDL : ", "window create error\n");
	editor->surf = SDL_GetWindowSurface(editor->win);
	editor->fg = (SDL_Color){252, 136, 3, 255};
	editor->width = WIDTH;
	editor->height = HEIGHT;
	editor->zoom = 5;
	init_music_font(editor);
	coords_init(editor, &editor->size);
	editor->center.x = editor->size.x / 2 * SQUARE_SIZE * editor->zoom - (editor->width - MENU_WIDTH) / 2;
	editor->center.y = editor->size.y / 2 * SQUARE_SIZE * editor->zoom - (editor->height) / 2;
	editor->flags.t_f.select = 1;
	ft_printf("x = %i y = %i\n", editor->center.x, editor->center.y);
	return (editor);
}
