/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdaufin <jdaufin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/20 18:22:32 by jdaufin           #+#    #+#             */
/*   Updated: 2020/12/10 17:03:41 by jdaufin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	size_t	ft_backwd(char **pdst, const char **psrc, size_t size)
{
	int	count;

	count = (((int)size - 1 > (int)(ft_strlen(psrc[0]))) ? \
			(int)ft_strlen(psrc[0]) : (int)size - 1);
	pdst[0][count] = '\0';
	while (--count >= 0)
		pdst[0][count] = psrc[0][count];
	return (ft_strlen(psrc[0]));
}

static size_t	ft_forwd(char **pdst, const char **psrc, size_t size)
{
	size_t	count;
	size_t	max;

	count = 0;
	max = ((size - 1 > (ft_strlen(psrc[0]))) ? \
			ft_strlen(psrc[0]) : size - 1);
	while (count < max)
	{
		pdst[0][count] = psrc[0][count];
		count++;
	}
	pdst[0][count] = '\0';
	return (ft_strlen(psrc[0]));
}

size_t			ft_strlcpy(char *dst, const char *src, size_t size)
{
	if (dst > src)
		return (ft_backwd(&dst, &src, size));
	else
		return (ft_forwd(&dst, &src, size));
}
