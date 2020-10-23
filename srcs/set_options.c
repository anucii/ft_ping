/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_options.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdaufin <jdaufin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 17:26:35 by jdaufin           #+#    #+#             */
/*   Updated: 2020/10/23 18:13:31 by jdaufin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

extern t_options	g_options;

static void			handle_failure(char key)
{
	if (key == 'w')
		show_deadline_error();
	else if (key == 'W')
		show_timeout_error();
	else if (key == 't')
		show_ttl_error();
	else if (key == 'c')
		show_count_error();
	exit(EXIT_FAILURE);
}

static _Bool		check_integer(char *s, int *dest, int min_val)
{
	intmax_t		val;
	_Bool			val_ok;

	if ((!s) || (!dest))
		return (0);
	val = ft_atoimax(s);
	val_ok = (val >= (intmax_t)min_val) && (val <= INT32_MAX);
	if (val_ok)
		*dest = (int)val;
	return (val_ok);
}

static void			check_positive_quantity(char key, char *argv[], int val_pos)
{
	int				quantity;

	if (check_integer(argv[val_pos], &quantity, 1))
	{
		if (key == 't')
		{
			if (quantity > 255)
				handle_failure(key);
			g_options.ttl = (unsigned int)quantity;
		}
		else if (key == 'c')
			g_options.count = quantity;
		return ;
	}
	handle_failure(key);
}

static void			check_quantity(char key, char *argv[], int val_pos)
{
	int				duration;

	if (check_integer(argv[val_pos], &duration, 0))
	{
		if (key == 'w')
			g_options.deadline = (unsigned int)duration;
		else if (key == 'W')
			g_options.timeout = (unsigned int)duration;
		return ;
	}
	handle_failure(key);
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
			check_quantity(c, argv, next_pos);
		else if (c == 'W')
			check_quantity(c, argv, next_pos);
		else if (c == 't')
			check_positive_quantity(c, argv, next_pos);
		else if (c == 'c')
			check_positive_quantity(c, argv, next_pos);
	}
}
