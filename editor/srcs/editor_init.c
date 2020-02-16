/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlavrine <nlavrine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/10 16:20:39 by nlavrine          #+#    #+#             */
/*   Updated: 2020/02/16 17:33:49 by nlavrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_editor.h"

void		init_music_font(t_editor *editor)
{
	TTF_Init();
	SDL_StartTextInput();
	editor->font = TTF_OpenFont("../fonts/Aller_b.ttf", 24);
	editor->font1 = TTF_OpenFont("../fonts/font1.ttf", 14);
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
		print_error("SDL : ", " mixer didn`t init\n");
	editor->music = Mix_LoadMUS("../music/Majestic.mp3");
	if (!editor->music)
		print_error("SDL : ", "cant`t find music\n");
	// Mix_PlayMusic(editor->music, -1);
	editor->mouse = 0;
}

t_editor	*init_editor(void)
{
	t_editor	*editor;
	char *num;

	editor = ft_memalloc(sizeof(t_editor));
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
		print_error("SDL : ", "init error\n");
	editor->win = SDL_CreateWindow("editor", 250, 200, E_WIDTH,
											E_HEIGHT, SDL_WINDOW_SHOWN);
	if (!editor->win)
		print_error("SDL : ", "window create error\n");
	editor->surf = SDL_GetWindowSurface(editor->win);
	editor->fg = (SDL_Color){252, 136, 3, 255};
	editor->width = E_WIDTH;
	editor->height = E_HEIGHT;
	editor->zoom = 2;
	editor->floor = 1;
	editor->flags.t_f.f_floor = 1;
	init_music_font(editor);
	coords_init(editor, &editor->size);
	editor->center.x = editor->size.x / 2 * SQUARE_SIZE * editor->zoom - (editor->width - MENU_WIDTH) / 2;
	editor->center.y = editor->size.y / 2 * SQUARE_SIZE * editor->zoom - (editor->height) / 2;
	editor->flags.t_f.select = 1;
	editor->doom = ft_memalloc(sizeof(t_doom));
	editor->doom->w = editor->width;
	editor->doom->h = editor->height;
	num = ft_itoa((unsigned short int)&editor->doom);
	editor->filename = ft_strdup(num);
	ft_memdel((void **)&num);
	editor->doom->igr_x = editor->doom->w / 2;
    editor->doom->igr_y = editor->doom->h / 2;
	editor->doom->x_aim = editor->width / 2;
	editor->doom->y_aim = editor->height * 0.62;
	editor->doom->gravity = 0.015;
	editor->doom->min_z = 0.5;
	load_texture_wall(editor->doom);
	init_skybox(editor->doom);
	init_emenu_buttons(editor);
	editor->doom->z_buffer = (int*)malloc(sizeof(int) * editor->height * editor->width);
	editor->doom->window = editor->win;
	editor->doom->surface = editor->surf;
	editor->absolute_center.x = (editor->width - MENU_WIDTH) / 2;
	editor->absolute_center.y = (editor->height) / 2;
	ft_printf("x = %i y = %i\n", editor->center.x, editor->center.y);
	return (editor);
}
