/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlavrine <nlavrine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 17:24:41 by nlavrine          #+#    #+#             */
/*   Updated: 2019/11/16 17:32:18 by nlavrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_editor.h"

int		main(void)
{
	t_editor	*editor;

	ft_printf("Structure init ...\n");
	editor = init_editor();
	// load_textures(editor);
	ft_printf("Let`s the play begin !\n");
	main_loop(editor);
	return (0);
}
