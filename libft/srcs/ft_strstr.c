/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdaufin <jdaufin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/15 22:03:44 by jdaufin           #+#    #+#             */
/*   Updated: 2020/12/10 17:03:41 by jdaufin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *big, const char *little)
{
	size_t	ib;
	size_t	jb;
	size_t	il;
	char	*ret;

	ib = 0;
	if (ft_strlen(little))
	{
		while (big[ib])
		{
			il = 0;
			jb = ib;
			while (big[jb++] == little[il++])
			{
				if (!(little[il]))
					return ((ret = (char *)&big[ib]));
			}
			ib++;
		}
		return (NULL);
	}
	else
		return ((ret = (char *)big));
}
