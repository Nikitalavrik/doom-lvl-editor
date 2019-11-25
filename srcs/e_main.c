/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_main.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlavrine <nlavrine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 17:24:41 by nlavrine          #+#    #+#             */
/*   Updated: 2019/11/25 15:32:14 by nlavrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_editor.h"

int		main(int argc, char **argv)
{
	t_editor	*editor;

	ft_printf("Structure init ...\n");
	editor = init_editor();
	load_textures(editor);
	ft_printf("Let`s the play begin !\n");
	if (argc == 2)
	{
		load_map(editor->doom, argv[1]);
		convert_doom_to_editor(editor, editor->doom);
	}
	if (argc <= 2)
		main_loop(editor);
	return (0);
}
