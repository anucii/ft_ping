/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstpop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdaufin <jdaufin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/05 14:31:23 by jdaufin           #+#    #+#             */
/*   Updated: 2020/12/10 17:03:41 by jdaufin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstpop(t_list **alst)
{
	t_list	*buf[2];
	_Bool	uniq;

	if (!(alst && *alst))
		return ;
	buf[0] = *alst;
	uniq = (*alst)->next ? 0 : 1;
	while (buf[0]->next)
	{
		buf[1] = buf[0];
		buf[0] = buf[0]->next;
	}
	ft_lstdelone(&buf[0], &ft_linkdel);
	if (!uniq)
		buf[1]->next = NULL;
}
