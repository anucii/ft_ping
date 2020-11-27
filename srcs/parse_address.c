/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_address.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdaufin <jdaufin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 19:40:25 by jdaufin           #+#    #+#             */
/*   Updated: 2020/11/27 16:30:22 by jdaufin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

static _Bool	option_has_argument(char *argv[], int pos)
{
	char	*relevant_options;
	size_t	i;
	size_t	stop;

	if (ft_strlen(argv[pos]) != 2)
		return (0);
	i = 0;
	relevant_options = ft_strdup("cwWt");
	stop = ft_strlen(relevant_options);
	while (i < stop)
	{
		if (relevant_options[i] == argv[pos][1])
		{
			ft_strdel(&relevant_options);
			return (1);
		}
		i++;
	}
	ft_strdel(&relevant_options);
	return (0);
}

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

void			parse_address(char *argv[], int pos, char *param, char *dest)
{
	if ((pos > 1) && (argv[pos -1][0] == '-') \
		&& option_has_argument(argv, pos - 1))
		return ;
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
