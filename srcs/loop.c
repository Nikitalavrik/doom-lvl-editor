/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlavrine <nlavrine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/03 13:38:31 by nlavrine          #+#    #+#             */
/*   Updated: 2019/11/30 13:49:15 by nlavrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_editor.h"

void	editor_loop(t_editor *editor)
{
	ft_bzero(editor->surf->pixels, E_WIDTH * E_HEIGHT * sizeof(int));
	coords_rerange(editor);
	draw_rooms(editor);
	draw_stick_room(editor);
	draw_lines(editor, editor->lines);
	draw_cells(editor);
	check_alpha(editor);
	draw_stick_line(editor);
}

void	doom_loop(t_editor *editor)
{
	bzero(editor->doom->z_buffer, sizeof(int) * WIDTH * HEIGHT);
	check_render(editor->doom);
	skybox(editor->doom);
	raycasting(editor->doom);
	print_sp_sec(editor->doom);
	print_aim(editor->doom);
}

int		main_loop(t_editor *editor)
{
	int			quit;

	quit = 0;
	while (!quit)
	{
		quit = detect_event(editor);
		if (editor->flags.t_f.visual)
			doom_loop(editor);
		else
			editor_loop(editor);
		SDL_UpdateWindowSurface(editor->win);
	}
	SDL_FreeSurface(editor->surf);
	SDL_DestroyWindow(editor->win);
	Mix_Quit();
	IMG_Quit();
	SDL_Quit();
	TTF_Quit();
	return (0);
}
