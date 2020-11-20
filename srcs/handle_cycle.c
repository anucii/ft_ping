/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_cycle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdaufin <jdaufin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 17:09:49 by jdaufin           #+#    #+#             */
/*   Updated: 2020/11/20 23:48:13 by jdaufin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

extern t_ping_shared_data	g_ping_data;

static void	close_socket(int sig_num)
{
	if (sig_num == SIGALRM)
	{
		close(g_ping_data.socket_fd);
		g_ping_data.socket_fd = -2;
	}
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
		alarm(options->deadline);
	while (1)
	{
		signal(SIGALRM, &close_socket);
		handle_round_trip(options, ++seq_num);
		if (++round_trips >= options-> count)
			break;
	}
}
