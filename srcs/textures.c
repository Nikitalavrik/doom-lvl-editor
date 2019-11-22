/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlavrine <nlavrine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 14:20:14 by nlavrine          #+#    #+#             */
/*   Updated: 2019/11/10 16:47:33 by nlavrine         ###   ########.fr       */
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
	text = SDL_ConvertSurface(tmp, editor->surf->format, 0 );
	SDL_FreeSurface(tmp);
	return (text);
}

void	load_textures(t_editor *editor)
{
	// int	i;

	// editor->textures[0] =load_texture("./texture/glass_light_blue.png", wolf);
	// editor->textures[1] = load_texture("./texture/brick.png", editor);
	// editor->textures[2] =\
	// load_texture("./texture/redstone_lamp_on.png", editor);
	// editor->textures[3] =\
	// load_texture("./texture/crafting_table_front.png", editor);
	// editor->textures[4] = load_texture("./texture/diamond_block.png", editor);
	// editor->textures[5] = load_texture("./texture/diamond_ore.png", editor);
	// editor->textures[6] = load_texture("./texture/glass_lime.png", editor);
	// editor->textures[7] = load_texture("./texture/gravel.png", editor);
	// editor->textures[8] = load_texture("./texture/redstone_block.png", editor);
	editor->textures[0] = load_texture("textures/Bookshell.png", editor);
	editor->textures[1] = load_texture("textures/MultibrickD.png", editor);
	editor->textures[2] = load_texture("textures/wallbrick.png", editor);
	editor->textures[3] = load_texture("textures/wallbrick2.png", editor);
	editor->textures[4] = load_texture("textures/BluegreyL.png", editor);
	editor->textures[5] = load_texture("textures/floor2.png", editor);
	editor->textures[6] = load_texture("textures/Stonemold2D.png", editor);
	editor->textures[7] = load_texture("textures/WoodbrickswasD.png", editor);
	editor->textures[8] = load_texture("textures/floor.png", editor);
	// i = 0;
	// while (i < NUMBER_OF_TEXTURES)
	// {
	// 	if (!editor->textures[i])
	// 		print_error(ft_itoa(i), " : num of textures didn`t load\n");
	// 	i++;
	// }
}
