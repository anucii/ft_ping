/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdaufin <jdaufin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/15 21:40:50 by jdaufin           #+#    #+#             */
/*   Updated: 2020/12/10 17:03:41 by jdaufin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	tgt;
	char	*scast;
	size_t	size;
	size_t	count;

	count = 0;
	tgt = (char)c;
	scast = (char *)s;
	size = ft_strlen(s);
	while ((count < size) && (scast[count] != tgt))
		count++;
	if (scast[count] == tgt)
		return (&scast[count]);
	else
		return (NULL);
}
