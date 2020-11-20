/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_cycle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdaufin <jdaufin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 17:09:49 by jdaufin           #+#    #+#             */
/*   Updated: 2020/11/21 00:22:16 by jdaufin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

extern t_ping_shared_data	g_ping_data;

static void	set_deadline_timestamp(unsigned int deadline_secs)
{
	t_timeval				now;

	if (gettimeofday(&now, NULL))
		return;
	g_ping_data.deadline_timestamp.tv_sec = now.tv_sec + (int)deadline_secs;
	g_ping_data.deadline_timestamp.tv_usec = now.tv_usec;
}

static int	remaining_seconds_to_deadline()
{
	t_timeval				now;
	int						remaining_secs;

	if (gettimeofday(&now, NULL))
		return (0);
	remaining_secs = (int)g_ping_data.deadline_timestamp.tv_sec - (int)now.tv_sec;

	return (remaining_secs);
}

static int	create_icmp_socket(unsigned int *ttl)
{
	int socket_fd;

	socket_fd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
	if (socket_fd < 0)
	{
		fprintf(stderr, "ICMP socket creation failed, ");
		if (errno == EACCES)
			fprintf(stderr, "EACCESS\n");
		else if (errno == EAFNOSUPPORT)
			fprintf(stderr, "EAFNOSUPPORT\n");
		else if (errno == EINVAL)
			fprintf(stderr, "EINVAL\n");
		else if (errno == EMFILE)
			fprintf(stderr, "EMFILE\n");
		else if (errno == ENFILE)
			fprintf(stderr, "ENFILE\n");
		else if (errno == ENOBUFS)
			fprintf(stderr, "ENOBUFS\n");
		else if (errno == ENOMEM)
			fprintf(stderr, "ENOMEM\n");
		else if (errno == EPROTONOSUPPORT)
			fprintf(stderr, "EPROTONOSUPPORT\n");
		else if (errno == EPERM)
			fprintf(stderr, "EPERM - operation not permitted\n");
		else
			fprintf(stderr, ", errno: %d\n", errno);
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
	//TODO : send_echo, parse_reply, handle statistics and timer.
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
		if (++round_trips >= options-> count)
			break;
	}
}
