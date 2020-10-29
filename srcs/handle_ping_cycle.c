/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_ping_cycle.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdaufin <jdaufin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/23 18:31:43 by jdaufin           #+#    #+#             */
/*   Updated: 2020/10/29 13:20:52 by jdaufin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

static int	create_icmp_socket()
{
	int			socket_fd;

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
	return (socket_fd);
}

static void	fill_icmp_header(t_ip_icmp *hdr)
{
	hdr->icmp_type = 8;
	hdr->icmp_code = 0;
}

static void display_msg_error()
{
	if (errno == EACCES)
		fprintf(stderr, "Message sending error : EACCESS\n");
	else if (errno == EAGAIN)
		fprintf(stderr, "Message sending error : EAGAIN\n");
	else if (errno == EWOULDBLOCK)
		fprintf(stderr, "Message sending error : EWOULDBLOCK\n");
	else if (errno == ECONNRESET)
		fprintf(stderr, "Message sending error : ECONNRESET\n");
	else
		fprintf(stderr, "Message sending error : %d\n", errno);
	
}

void	handle_ping_cycle(t_sockaddr *target)
{
	t_ip_icmp	ip_icmp;
	int 		socket_fd;
	ssize_t		msg_ret;

	if (!target)
	{
		fprintf(stderr, "Invalid target\n");
		exit(EXIT_FAILURE);
	}
	socket_fd = create_icmp_socket();
	if (socket_fd == -1)
	{
		fprintf(stderr, "Socket creation failed.\n");
		return;
	}
	fill_icmp_header(&ip_icmp);
	msg_ret = sendto(socket_fd, &ip_icmp, (size_t)sizeof(ip_icmp), 0, target, sizeof(t_sockaddr));
	if (msg_ret == -1)
		display_msg_error();
	else
		printf("%zd bytes sent\n.", msg_ret);
}
