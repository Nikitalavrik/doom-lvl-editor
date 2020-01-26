/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlavrine <nlavrine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 14:20:14 by nlavrine          #+#    #+#             */
/*   Updated: 2020/01/26 16:19:24 by nlavrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_editor.h"

SDL_Surface		*load_texture(char *path, t_editor *editor)
{
	SDL_Surface		*tmp;
	SDL_Surface		*text;

	tmp = IMG_Load(path);
	if (tmp == NULL)
	{
		SDL_FreeSurface(tmp);
		ft_putstr("ERROR: cannot load texture (");
		ft_putstr(path);
		ft_putendl(")");
		exit(1);
	}
	text = SDL_ConvertSurface(tmp, editor->surf->format, 0);
	SDL_FreeSurface(tmp);
	return (text);
}

void			load_textures(t_editor *editor)
{
	editor->button[0] = load_texture("../text/widgets_1.png", editor);
	editor->button[1] = load_texture("../text/widgets_2.png", editor);
	editor->button[2] = load_texture("../text/widgets_3.png", editor);
	editor->button[3] = load_texture("../text/grey_circle.png", editor);
	editor->button[4] = load_texture("../text/green_boxTick.png", editor);
	editor->button[5] = load_texture("../text/green_button07.png", editor);
	editor->button[6] = load_texture("../text/green_button08.png", editor);
	editor->button[7] = load_texture("../text/green_button09.png", editor);
	editor->button[8] = load_texture("../text/green_button02.png", editor);
	editor->button[9] = load_texture("../text/green_button00.png", editor);
	editor->button[10] = load_texture("../text/green_button05.png", editor);
}
