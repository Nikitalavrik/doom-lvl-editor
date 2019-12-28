/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_test.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlavrine <nlavrine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/28 17:15:41 by nlavrine          #+#    #+#             */
/*   Updated: 2019/12/28 17:17:29 by nlavrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_editor.h"

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
