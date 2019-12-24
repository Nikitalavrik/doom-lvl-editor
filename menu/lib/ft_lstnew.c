/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbahlai <tbahlai@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 11:35:52 by tbahlai           #+#    #+#             */
/*   Updated: 2018/11/07 12:39:32 by tbahlai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*list;
	void	*temp;

	temp = malloc(content_size);
	list = (t_list *)malloc(sizeof(t_list));
	if (!temp)
		return (NULL);
	if (!list)
	{
		free(temp);
		return (NULL);
	}
	if (content == NULL)
	{
		list->content_size = 0;
		temp = NULL;
	}
	else
	{
		ft_memcpy(temp, content, content_size);
		list->content_size = content_size;
	}
	list->next = NULL;
	list->content = temp;
	return (list);
}
