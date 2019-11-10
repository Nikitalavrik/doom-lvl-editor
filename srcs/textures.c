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

void	load_textures(t_editor *editor)
{
	int	i;

	editor->textures[0] = IMG_Load("textures/Bookshell.png");
	editor->textures[1] = IMG_Load("textures/MultibrickD.png");
	editor->textures[2] = IMG_Load("textures/wallbrick.png");
	editor->textures[3] = IMG_Load("textures/wallbrick2.png");
	editor->textures[4] = IMG_Load("textures/BluegreyL.png");
	editor->textures[5] = IMG_Load("textures/floor2.png");
	editor->textures[6] = IMG_Load("textures/Stonemold2D.png");
	editor->textures[7] = IMG_Load("textures/WoodbrickswasD.png");
	editor->textures[8] = IMG_Load("textures/floor.png");
	i = 0;
	while (i < NUMBER_OF_TEXTURES)
	{
		if (!editor->textures[i])
			print_error(ft_itoa(i), " : num of textures didn`t load\n");
		i++;
	}
}
