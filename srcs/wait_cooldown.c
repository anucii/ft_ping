/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_cooldown.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdaufin <jdaufin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 16:46:45 by jdaufin           #+#    #+#             */
/*   Updated: 2021/04/29 21:00:47 by jdaufin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

void	wait_cooldown(void)
{
	t_timeval	cursor;
	time_t		end;

	gettimeofday(&cursor, NULL);
	end = cursor.tv_sec + 1;
	while (cursor.tv_sec < end)
	{
		gettimeofday(&cursor, NULL);
	}
}
