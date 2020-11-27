/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_reply_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdaufin <jdaufin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 12:14:31 by jdaufin           #+#    #+#             */
/*   Updated: 2020/11/27 15:52:50 by jdaufin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

unsigned int	ihl_words_to_bytes(unsigned int ip_header_32bits_words)
{
	return (4 * ip_header_32bits_words);
}

unsigned int	little_endian(unsigned short val)
{
	unsigned short	little_end;
	unsigned short	big_end;

	little_end = val >> 8;
	big_end = 0xffff & (val << 8);
	return (big_end + little_end);
}

double			compute_rtt(const t_timeval sending_time)
{
	t_timeval				recv_time;
	double					round_trip_time;
	time_t					seconds_delta;
	suseconds_t				microseconds_delta;

	if (gettimeofday(&recv_time, NULL))
		return (0);
	seconds_delta = recv_time.tv_sec - sending_time.tv_sec;
	microseconds_delta = recv_time.tv_usec - sending_time.tv_usec;
	round_trip_time = (double)seconds_delta * 1000 \
		+ ((double)microseconds_delta / 1000);
	return (round_trip_time);
}
