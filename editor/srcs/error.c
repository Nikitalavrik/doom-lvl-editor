/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlavrine <nlavrine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 19:40:06 by nlavrine          #+#    #+#             */
/*   Updated: 2019/11/10 16:39:49 by nlavrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_editor.h"

void		error_message(char *message)
{
	int i;

	i = 0;
	while (message[i])
	{
		write(2, &(message[i]), 1);
		i++;
	}
}

void		print_error(char *manage, char *message)
{
	error_message(manage);
	error_message(message);
	exit(0);
}

void	draw_error_mess(t_editor *editor)
{
	SDL_Color	color;
	SDL_Surface	*message;
	SDL_Rect	f;

	color = (SDL_Color){255, 0, 0, 0};
	f.x = editor->width - MENU_WIDTH + 100;
	f.y = editor->height - 130;
	message = TTF_RenderText_Solid(editor->font1, "Error: empty feild!", color);
	SDL_BlitSurface(message, NULL, SDL_GetWindowSurface(editor->win), &f);
	SDL_FreeSurface(message);
}
