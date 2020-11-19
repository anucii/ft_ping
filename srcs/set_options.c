/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_options.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdaufin <jdaufin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 17:26:35 by jdaufin           #+#    #+#             */
/*   Updated: 2020/11/19 16:06:05 by jdaufin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

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

static void			check_positive_quantity(char key, char *argv[], \
	int val_pos, t_options *options)
{
	int				quantity;

	if (check_integer(argv[val_pos], &quantity, 1))
	{
		if (key == 't')
		{
			if (quantity > 255)
				handle_failure(key);
			options->ttl = (unsigned int)quantity;
		}
		else if (key == 'c')
			options->count = quantity;
		return ;
	}
	handle_failure(key);
}

static void			check_quantity(char key, char *argv[], int val_pos, \
	t_options *options)
{
	int				duration;

	if (check_integer(argv[val_pos], &duration, 0))
	{
		if (key == 'w')
			options->deadline = (unsigned int)duration;
		else if (key == 'W')
			options->timeout = (unsigned int)duration;
		return ;
	}
	handle_failure(key);
}

void				set_options(char c, char *argv[], \
	const t_argv_cursor cursor, t_options *options)
{
	int				next_pos;

	options->help |= (c == 'h');
	options->verbose |= (c == 'v');
	next_pos = cursor.index + 1;
	if (next_pos < cursor.argc)
	{
		if (c == 'w')
			check_quantity(c, argv, next_pos, options);
		else if (c == 'W')
			check_quantity(c, argv, next_pos, options);
		else if (c == 't')
			check_positive_quantity(c, argv, next_pos, options);
		else if (c == 'c')
			check_positive_quantity(c, argv, next_pos, options);
	}
}
