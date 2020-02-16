/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbahlai <tbahlai@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 13:18:31 by tbahlai           #+#    #+#             */
/*   Updated: 2018/11/14 15:23:07 by tbahlai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list *temp;

	if (!alst || !*alst || !del)
		return ;
	while (*alst)
	{
		del((*alst)->content, (*alst)->content_size);
		temp = *alst;
		*alst = (*alst)->next;
		free(temp);
	}
}
