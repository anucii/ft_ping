/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_cycle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdaufin <jdaufin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 17:09:49 by jdaufin           #+#    #+#             */
/*   Updated: 2021/04/29 16:57:30 by jdaufin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

extern t_ping_shared_data	g_ping_data;

static void	set_deadline_timestamp(unsigned int deadline_secs)
{
	t_timeval				now;

	if (gettimeofday(&now, NULL))
		return ;
	g_ping_data.deadline_timestamp.tv_sec = now.tv_sec + (int)deadline_secs;
	g_ping_data.deadline_timestamp.tv_usec = now.tv_usec;
}

static int	remaining_seconds_to_deadline(void)
{
	t_timeval				now;
	int						remaining_secs;

	if (gettimeofday(&now, NULL))
		return (0);
	remaining_secs = (int)g_ping_data.deadline_timestamp.tv_sec - \
		(int)now.tv_sec;
	return (remaining_secs);
}

static int	create_icmp_socket(unsigned int *ttl)
{
	int socket_fd;

	socket_fd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
	if (socket_fd < 0)
	{
		if ((errno == EACCES) || (errno == EPERM))
		{
			fprintf(stderr, "ft_ping: user has insufficient permissions.\n");
		}
		else
		{
			fprintf(stderr, "ft_ping: ICMP socket creation failed.\n");
		}
		exit(EXIT_FAILURE);
	}
	setsockopt(socket_fd, IPPROTO_IP, IP_TTL, ttl, sizeof(int));
	return (socket_fd);
}

static void	handle_round_trip(t_options *options, \
	int seq_num)
{
	t_ip_icmp				ip_icmp;
	t_timeval				sending_time;

	g_ping_data.socket_fd = create_icmp_socket(&options->ttl);
	if (options->timeout > 0)
		alarm(options->timeout);
	if (g_ping_data.socket_fd == -1)
	{
		fprintf(stderr, "ft_ping: socket: creation failed.\n");
		exit(EXIT_FAILURE);
	}
	if (send_echo(&ip_icmp, &sending_time, seq_num))
		handle_reply(options, sending_time);
}

void		handle_cycle(char *ip_str, t_options *options)
{
	int						seq_num;
	int						round_trips;

	seq_num = 0;
	round_trips = 0;
	if (!dynarray_init(&g_ping_data.all_rtts))
	{
		fprintf(stderr, "ft_ping: rtt array allocation failed.\n");
		exit(EXIT_FAILURE);
	}
	printf("PING %s (%s)\n", g_ping_data.fqdn, ip_str);
	gettimeofday(&g_ping_data.ping_first_timestamp, NULL);
	if (options->deadline > 0)
		set_deadline_timestamp(options->deadline);
	while (1)
	{
		if (options->deadline > 0)
			alarm(remaining_seconds_to_deadline());
		handle_round_trip(options, ++seq_num);
		if ((options->count > 0) && (++round_trips >= options->count))
			break ;
		wait_cooldown();
	}
}
