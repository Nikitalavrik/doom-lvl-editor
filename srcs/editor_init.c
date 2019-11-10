/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlavrine <nlavrine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/10 16:20:39 by nlavrine          #+#    #+#             */
/*   Updated: 2019/11/10 16:39:40 by nlavrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_editor.h"

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
	editor->win = SDL_CreateWindow("editor", 650, 300, WIDTH,
											HEIGHT, SDL_WINDOW_SHOWN);
	if (!editor->win)
		print_error("SDL : ", "window create error\n");
	editor->surf = SDL_GetWindowSurface(editor->win);
	editor->fg = (SDL_Color){252, 136, 3, 255};
	init_music_font(editor);
	return (editor);
}
