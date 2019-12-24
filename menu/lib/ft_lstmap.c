/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbahlai <tbahlai@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 14:29:58 by tbahlai           #+#    #+#             */
/*   Updated: 2018/11/07 15:50:34 by tbahlai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*new;
	t_list	*step;

	if (!lst || !f)
		return (NULL);
	step = f(lst);
	new = step;
	while (lst->next)
	{
		lst = lst->next;
		if (!(step->next = f(lst)))
		{
			free(step->next);
			return (NULL);
		}
		step = step->next;
	}
	return (new);
}
