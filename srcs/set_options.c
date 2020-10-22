/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_options.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdaufin <jdaufin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 17:26:35 by jdaufin           #+#    #+#             */
/*   Updated: 2020/10/22 18:37:36 by jdaufin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

extern t_options	g_options;

static _Bool		check_integer(char *s, int *dest)
{
	intmax_t		val;
	_Bool			val_ok;

	if ((!s) || (!dest))
		return (0);
	val = ft_atoimax(s);
	val_ok = (val >= 0) && (val <= INT32_MAX);
	if (val_ok)
		*dest = (int)val;
	return val_ok;
}

static void			check_count(char *argv[], int val_pos)
{
	int				count;

	if (check_integer(argv[val_pos], &count))
	{
		if (count > 0)
		{
			g_options.count = count;
			return;
		}
	}
	show_count_error();
	exit(EXIT_FAILURE);
}

static void			check_timeout(char *argv[], int val_pos)
{
	int				timeout;

	if (check_integer(argv[val_pos], &timeout))
	{
		g_options.timeout = (unsigned int)timeout;
		return;
	}
	show_timeout_error();
	exit(EXIT_FAILURE);
}

static void			check_deadline(char *argv[], int val_pos)
{
	int				deadline;

	if (check_integer(argv[val_pos], &deadline))
	{
		g_options.deadline = (unsigned int)deadline;
		return;
	}
	show_deadline_error();
	exit(EXIT_FAILURE);
}

void				set_options(char c, char *argv[], int pos, int argc)
{
	int				next_pos;

	g_options.help |= (c == 'h');
	g_options.verbose |= (c == 'v');
	if (g_options.ai_family != AF_INET6)
		g_options.ai_family = (c == '6') ? AF_INET6 : AF_INET; 
	next_pos = pos + 1;
	if (next_pos < argc)
	{
		if (c == 'w')
			check_deadline(argv, next_pos);
		else if (c == 'W')
			check_timeout(argv, next_pos);
		else if (c == 'c')
			check_count(argv, next_pos);
	}
}
