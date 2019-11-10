/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlavrine <nlavrine@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/27 15:36:05 by nlavrine          #+#    #+#             */
/*   Updated: 2018/10/27 15:36:06 by nlavrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstnew(void	const *content, size_t content_size)
{
	t_list	*ret;

	if ((ret = (t_list *)malloc(sizeof(t_list))))
	{
		if (!content)
		{
			ret->content = NULL;
			ret->content_size = 0;
		}
		else if ((ret->content = (void *)malloc(content_size)))
		{
			ft_memcpy(ret->content, content, content_size);
			ret->content_size = content_size;
		}
		ret->next = NULL;
		return (ret);
	}
	return (NULL);
}
