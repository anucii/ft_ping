/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdaufin <jdaufin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 11:53:10 by jdaufin           #+#    #+#             */
/*   Updated: 2020/11/19 16:06:25 by jdaufin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

static _Bool	check_option(char *arg, char *argv[], \
	const t_argv_cursor cursor, t_options *options)
{
	char			*all_options;
	_Bool			has_match;
	int				i;

	has_match = 0;
	if (ft_strlen(arg) >= 2)
	{
		all_options = ft_strdup("vhcwWt");
		i = 0;
		has_match = 1;
		while (arg[++i])
		{
			has_match &= (ft_strchr(all_options, arg[i]) != NULL);
			if (has_match)
			{
				set_options(arg[i], argv, cursor, options);
			}
		}
		ft_strdel(&all_options);
	}
	return (has_match);
}

static _Bool	parse_args_execute(int argc, char *argv[], \
	char *target_address, t_options *options)
{
	int				i;
	char			*arg;
	t_argv_cursor	cursor;

	i = 0;
	cursor.argc = argc;
	while (++i < argc)
	{
		arg = argv[i];
		cursor.index = i;
		if (arg[0] == '-')
		{
			if (!check_option(arg, argv, cursor, options))
			{
				return (0);
			}
		}
		else
			parse_address(arg, target_address);
	}
	return (*target_address != 0);
}

_Bool			parse_args(int argc, char *argv[], \
	char *target_address, t_options *options)
{
	_Bool		args_ok;

	if ((argc < 2) || !argv)
	{
		return (0);
	}
	args_ok = parse_args_execute(argc, argv, \
		target_address, options);
	return (args_ok);
}
