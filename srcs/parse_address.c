/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_address.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdaufin <jdaufin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 19:40:25 by jdaufin           #+#    #+#             */
/*   Updated: 2020/10/23 15:59:15 by jdaufin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

static _Bool	is_fqdn(char *src)
{
	char		**address_parts;
	char		delimitor;
	int			i;

	if (!src)
		return (0);
	i = -1;
	delimitor = !ft_strchr(src, ':') ? '.' : ':';
	address_parts = ft_strsplit(src, delimitor);
	if (address_parts && *address_parts)
	{
		while (address_parts[++i])
			;
		ft_stabdel(&address_parts);
		return (delimitor == '.' ? (i > 1) : (i > 0));
	}
	else if (address_parts)
		free(address_parts);
	return (0);
}

static _Bool	is_alias(char *src)
{
	char		*trimmed_src;
	_Bool		alnum_alias;
	ssize_t		i;
	ssize_t		len;

	if (!src)
		return (0);
	trimmed_src = ft_strtrim(src);
	alnum_alias = 1;
	len = ft_strlen(trimmed_src);
	i = 0;
	while (trimmed_src[i])
	{
		alnum_alias &= ft_isalnum(trimmed_src[i]);
		i++;
	}
	ft_strdel(&trimmed_src);
	return (alnum_alias);
}

void			parse_address(char *param, char *dest)
{
	if (param && dest)
	{
		if (ft_strlen(param) <= MAX_FQDN)
		{
			if (is_fqdn(param) || is_alias(param))
				ft_strcpy(dest, param);
			return ;
		}
	}
	show_help();
	exit(EXIT_FAILURE);
}
