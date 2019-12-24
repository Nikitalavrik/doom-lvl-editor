/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbahlai <tbahlai@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 13:18:31 by tbahlai           #+#    #+#             */
/*   Updated: 2018/11/07 17:48:50 by tbahlai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list *temp;

	if (!alst || !*alst)
		return ;
	while (*alst)
	{
		del((*alst)->content, (*alst)->content_size);
		temp = *alst;
		*alst = (*alst)->next;
		free(temp);
	}
}
