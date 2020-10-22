/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_address.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdaufin <jdaufin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 19:40:25 by jdaufin           #+#    #+#             */
/*   Updated: 2020/10/22 20:08:02 by jdaufin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

_Bool		is_fqdn(char *src)
{
	char	**address_parts;
	int		i;

	if (!src)
		return (0);
	i = -1;
	address_parts = ft_strsplit(src, '.');
	if (address_parts && *address_parts)
	{
		while (address_parts[++i])
			;
		ft_stabdel(&address_parts);
		return (i > 1);
	}
	else if (address_parts)
		free(address_parts);
	return (0);
}

void		parse_address(char *param, char *dest)
{
	if (param && dest)
	{
		if (ft_strlen(param) <= MAX_FQDN)
		{
			if (is_fqdn(param))
				ft_strcpy(dest, param);
			return ;
		}
	}
	show_help();
	exit(EXIT_FAILURE);
}
