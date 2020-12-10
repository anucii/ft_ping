/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putwstr_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdaufin <jdaufin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/19 14:35:39 by jdaufin           #+#    #+#             */
/*   Updated: 2020/12/10 17:03:41 by jdaufin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putwstr_fd(const wchar_t *s, int fd)
{
	unsigned char	*mbs;
	t_wslen			wslen;

	if (s && ft_wcstrlen(s, &wslen) && (mbs = ft_wcstombs(s)))
	{
		write(fd, mbs, wslen.bytes);
		ft_memdel((void **)&mbs);
	}
}
