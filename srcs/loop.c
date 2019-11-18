/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlavrine <nlavrine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/03 13:38:31 by nlavrine          #+#    #+#             */
/*   Updated: 2019/11/18 15:38:53 by nlavrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_editor.h"

int		main_loop(t_editor *editor)
{
	int			quit;

	quit = 0;
	while (!quit)
	{
		ft_bzero(editor->surf->pixels, WIDTH * HEIGHT * sizeof(int));
		quit = detect_event(editor);
		draw_rooms(editor);
		draw_lines(editor, editor->lines);
		draw_cells(editor);
		check_alpha(editor);
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
