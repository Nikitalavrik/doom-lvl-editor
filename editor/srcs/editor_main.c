/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlavrine <nlavrine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 16:01:36 by nlavrine          #+#    #+#             */
/*   Updated: 2020/02/23 16:36:58 by nlavrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_editor.h"

int		start_editor(SDL_Window *win)
{
	t_editor	*editor;

	editor = ft_memalloc(sizeof(t_editor));
	editor->win = win;
	if (!editor->win)
		print_error("SDL : ", "window create error\n");
	editor->surf = SDL_GetWindowSurface(editor->win);
	editor->fg = (SDL_Color){252, 136, 3, 255};
	editor->width = editor->surf->w;
	editor->height = editor->surf->h;
	editor->zoom = 2;
	init_music_font(editor);
	coords_init(editor, &editor->size);
	editor->center.x = editor->size.x / 2 * SQUARE_SIZE * editor->zoom - (editor->width - MENU_WIDTH) / 2;
	editor->center.y = editor->size.y / 2 * SQUARE_SIZE * editor->zoom - (editor->height) / 2;
	editor->flags.t_f.select = 1;
	editor->doom = ft_memalloc(sizeof(t_doom));
	editor->doom->x_aim = editor->width / 2;
	editor->doom->y_aim = editor->height * 0.62;
	editor->doom->gravity = 0.015;
	editor->doom->min_z = 0.5;
	editor->doom->w = editor->width;
	editor->doom->h = editor->height;
	editor->floor = 1;
	load_texture_wall(editor->doom);
	init_emenu_buttons(editor);
	init_skybox(editor->doom);
	editor->doom->z_buffer = (int*)ft_memalloc(sizeof(int) * editor->width * editor->height);
	editor->doom->window = editor->win;
	editor->doom->surface = editor->surf;
	editor->absolute_center.x = (editor->width - MENU_WIDTH) / 2;
	editor->absolute_center.y = (editor->height) / 2;
	// ft_printf("w = %i h = %i\n", editor->width, editor->height);
	load_textures(editor);
	generate_alpha_tab(editor->doom);
	main_loop(editor);
	return (0);
}
