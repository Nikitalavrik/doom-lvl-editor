/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   os_check.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlavrine <nlavrine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 15:25:05 by nlavrine          #+#    #+#             */
/*   Updated: 2020/01/30 15:53:54 by nlavrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_editor.h"

int		check_file_in_dir(char *filename)
{
	struct dirent	*rd;
	DIR				*dir;

	dir = opendir("saves");
	if (dir)
	{	
		while ((rd = readdir(dir)))
		{
			if (!ft_strcmp(rd->d_name, filename))
			{
				ft_printf("Find same file {%s}\n", filename);
				closedir(dir);
				return (0);
			}
		}
		closedir(dir);
	}
	else
	{
		ft_printf("Create dir saves\n");
		mkdir("saves", 0700);
	}
	return (1);
}
