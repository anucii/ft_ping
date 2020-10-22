/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdaufin <jdaufin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 11:53:10 by jdaufin           #+#    #+#             */
/*   Updated: 2020/10/22 18:37:05 by jdaufin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

static _Bool	check_option(char *arg, char *argv[], int argc)
{
	char		*all_options;
	_Bool		has_match;
	int			i;

	has_match = 0;
	if (ft_strlen(arg) >= 2)
	{
		all_options = ft_strdup("vhcwW46");
		i = 0;
		has_match = 1;
		while (arg[++i])
		{
			has_match &= (ft_strchr(all_options, arg[i]) != NULL);
			if (has_match)
			{
				set_options(arg[i], argv, i, argc);
			}
		}
		ft_strdel(&all_options);
	}
	return (has_match);
}

static _Bool	parse_args_execute(int argc, char *argv[])
{
	int			i;
	char		*arg;

	i = 0;
	while (++i < argc)
	{
		arg = argv[i];
		if (arg[0] == '-')
		{
			if (!check_option(arg, argv, argc))
			{
				return (0);
			}
		}
	}
	return (1);
}

_Bool			parse_args(int argc, char *argv[])
{
	if ((argc < 2) || !argv)
	{
		return (0);
	}
	return (parse_args_execute(argc, argv));
}
