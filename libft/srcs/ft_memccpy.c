/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdaufin <jdaufin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/15 15:24:47 by jdaufin           #+#    #+#             */
/*   Updated: 2020/12/10 17:03:41 by jdaufin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char	*ptr;
	unsigned char	tgt;
	unsigned char	*bsrc;
	unsigned char	*bdst;
	size_t			count;

	count = 0;
	tgt = (unsigned char)c;
	bsrc = (unsigned char *)src;
	bdst = (unsigned char *)dst;
	while ((count < n) && (bsrc[count] != tgt))
		count++;
	if (count == n)
	{
		ft_memcpy(dst, src, n);
		ptr = NULL;
	}
	else
	{
		ft_memcpy(dst, src, count + 1);
		ptr = &(bdst[count + 1]);
	}
	return ((void *)ptr);
}
