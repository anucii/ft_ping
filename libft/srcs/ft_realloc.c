/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdaufin <jdaufin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/05 21:06:51 by jdaufin           #+#    #+#             */
/*   Updated: 2020/12/10 17:03:41 by jdaufin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_realloc(void **addr, size_t oldsize, size_t newsize)
{
	void	*swap;

	if (!addr)
		return (NULL);
	if (!(*addr && oldsize && newsize))
		return (NULL);
	swap = ft_memalloc(oldsize);
	ft_memmove(swap, *addr, oldsize);
	ft_memdel(addr);
	*addr = ft_memalloc(newsize);
	*addr = ft_memmove(*addr, swap, oldsize);
	ft_memdel(&swap);
	return (*addr);
}
