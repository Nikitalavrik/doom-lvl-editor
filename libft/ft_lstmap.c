/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlavrine <nlavrine@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/27 18:05:53 by nlavrine          #+#    #+#             */
/*   Updated: 2018/10/27 18:05:54 by nlavrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*ret;

	ret = NULL;
	if (lst && f)
	{
		if (lst->next)
			ret = ft_lstmap(lst->next, f);
		ft_lstadd(&ret, f(lst));
		return (ret);
	}
	return (NULL);
}
