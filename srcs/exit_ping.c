/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_ping.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdaufin <jdaufin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 17:35:23 by jdaufin           #+#    #+#             */
/*   Updated: 2021/04/29 22:17:45 by jdaufin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

extern t_ping_shared_data	g_ping_data;

_Bool			deadline_over(void)
{
	t_timeval	now;

	if (!g_ping_data.deadline_timestamp.tv_sec)
		return (0);
	if (gettimeofday(&now, NULL) != 0)
		return (0);
	return (now.tv_sec >= g_ping_data.deadline_timestamp.tv_sec);
}

void			exit_ping(int sig_value)
{
	if (g_ping_data.socket_fd > 0)
	{
		close(g_ping_data.socket_fd);
		g_ping_data.socket_fd = -2;
	}
	if (sig_value == SIGALRM && !deadline_over())
		return ;
	printf("--- %s ping statistics ---\n", g_ping_data.fqdn);
	printf(\
		"%d packets transmitted, %d received, %.0f%% packet loss, ", \
		g_ping_data.sent_packets, g_ping_data.received_packets, \
		100.0 * (g_ping_data.sent_packets - g_ping_data.received_packets) \
		/ g_ping_data.sent_packets);
	printf("time %.0fms\n", compute_rtt(g_ping_data.ping_first_timestamp));
	if (g_ping_data.received_packets > 0)
		printf("rtt min/avg/max/mdev = %1.3f/%1.3f/%1.3f/%1.3f ms\n", \
			get_rtt_min(), get_rtt_avg(), get_rtt_max(), get_rtt_mdev());
	dynarray_free(&g_ping_data.all_rtts);
	exit(EXIT_SUCCESS);
}
