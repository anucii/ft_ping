/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_ping_cycle.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdaufin <jdaufin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/23 18:31:43 by jdaufin           #+#    #+#             */
/*   Updated: 2020/10/30 23:45:40 by jdaufin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

extern int ttl;
extern int socket_fd;

static int	create_icmp_socket()
{
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
	setsockopt(socket_fd, IPPROTO_IP, IP_TTL, &ttl, sizeof(ttl));
	return (socket_fd);
}

static unsigned short checksum(t_ip_icmp *hdr)
{
	unsigned short 	sum;
	unsigned short 	*array;
	int				i, size;

	size = sizeof(t_ip_icmp) / 2;
	i = -1;
	array = (unsigned short *)hdr;
	sum = 0;

	while (++i < size)
	{
		sum += array[i];
	}

	return sum ^ 0xFFFF;
}

static void	fill_icmp_header(t_ip_icmp *hdr, int seq_num)
{
	hdr->icmp_type = 8;
	hdr->icmp_code = 0;
	hdr->icmp_cksum = 0;
	hdr->icmp_hun.ih_idseq.icd_id = (unsigned short)getpid();
	hdr->icmp_hun.ih_idseq.icd_seq = seq_num;

	hdr->icmp_cksum = checksum(hdr);
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

static void display_recv_error(int err_num)
{
	fprintf(stderr, "Message receive error : %d\n", err_num);
}

static void send_echo(t_sockaddr *target, t_ip_icmp *ip_icmp, int seq_num)
{
	ssize_t		send_res;

	memset(ip_icmp, 0, sizeof(t_ip_icmp));
	fill_icmp_header(ip_icmp, seq_num);
	send_res = sendto(socket_fd, ip_icmp, (size_t)sizeof(t_ip_icmp), 0, target, sizeof(t_sockaddr));
	if (send_res == -1)
		display_msg_error();
	else
		printf("%zd bytes sent\n", send_res);
}

static void parse_reply(t_msghdr *pmsghdr, int seq_num)
{
	printf("Reply: %s - seq_num %d\n", pmsghdr ? "exists" : "null", seq_num);
}

static void handle_reply(int seq_num)
{
	t_msghdr	msghdr;
	ssize_t		recv_res;
	char		msg_name[255];
	char 		msg_ctrl[255];
	t_iovec		iovec[2];
	int			recv_err;


	memset(msg_name, 0, 255);
	memset(msg_ctrl, 0, 255);
	msghdr.msg_name = msg_name;
	msghdr.msg_control = msg_ctrl;
	msghdr.msg_iov = iovec;
	msghdr.msg_iovlen = 1;

	alarm(5); // -W option value
	recv_res = recvmsg(socket_fd, &msghdr, 0);
	recv_err = errno;
	if (recv_res > -1)
		parse_reply(&msghdr, seq_num);
	else if (recv_err == EBADF)
		return ;
	else
		display_recv_error(recv_err);
}

void	handle_ping_cycle(t_sockaddr *target, int seq_num)
{
	t_ip_icmp	ip_icmp;

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
	send_echo(target, &ip_icmp, seq_num);
	handle_reply(seq_num);
	
	if (socket_fd != -2)
		close(socket_fd);
}
