/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_ping_cycle.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdaufin <jdaufin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/23 18:31:43 by jdaufin           #+#    #+#             */
/*   Updated: 2020/11/08 23:06:00 by jdaufin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

extern int ttl;
extern int socket_fd;
extern char *g_fqdn;

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

static void send_echo(t_sockaddr *target, t_ip_icmp *ip_icmp, int seq_num, t_timeval *psending_time)
{
	ssize_t		send_res;

	memset(ip_icmp, 0, sizeof(t_ip_icmp));
	fill_icmp_header(ip_icmp, seq_num);
	if (gettimeofday(psending_time, NULL) != 0)
		fprintf(stderr, "Timestamp error, n°%d\n", errno);
	send_res = sendto(socket_fd, ip_icmp, (size_t)sizeof(t_ip_icmp), 0, target, sizeof(t_sockaddr));
	if (send_res == -1)
		display_msg_error();
	else
		printf("%zd bytes sent\n", send_res);
}

static unsigned int ihl_words_to_bytes(unsigned int ip_header_32bits_words)
{
	return 4 * ip_header_32bits_words;
}

static void parse_reply(t_msghdr *pmsghdr, int seq_num, double rtt)
{
	t_sockaddr_in 	*peer_addr;
	t_in_addr		*in_addr;
	t_icmph			*picmph;
	t_iph			*piph;
	unsigned short 	id;
	char			addr_str[NI_MAXHOST];

	// TODO !!
	peer_addr = (t_sockaddr_in *)pmsghdr->msg_name;
	in_addr = &(peer_addr->sin_addr);
	if (!inet_ntop(AF_INET, in_addr, addr_str, NI_MAXHOST))
	{
		memcpy(addr_str, "UNKNOWN", sizeof("UNKNOWN"));
	}
	piph = (t_iph *)(pmsghdr->msg_iov->iov_base);
	picmph = (t_icmph *)(pmsghdr->msg_iov->iov_base + ihl_words_to_bytes(piph->ihl));
	id = picmph->un.echo.id;
	if (id == (unsigned short)getpid() && picmph->type == ICMP_ECHOREPLY)
			printf("Reply from %s (%s) - seq_num %d, ttl=%d, time=%.1fms\n", g_fqdn, addr_str,\
			 seq_num, piph->ttl, rtt);
	else if (picmph->type == ICMP_TIME_EXCEEDED)
			printf("From %s (%s) icmp_seq=%d Time to live exceeded\n", g_fqdn, addr_str, seq_num);

	//DBG
	/* unsigned char *cast = (unsigned char *)pmsghdr->msg_iov->iov_base;
	for (int i = 0; i < 64; i++)
	{
		if ((i % 16) == 0)
			printf("\n");
		printf("%.2x ", cast[i]);
	}
	printf("\n"); */
}

static double compute_rtt(const t_timeval sending_time)
{
	t_timeval	recv_time;
	double		round_trip_time;
	time_t		seconds_delta;
	suseconds_t	microseconds_delta;

	if (gettimeofday(&recv_time, NULL))
		return (0);
	seconds_delta = recv_time.tv_sec - sending_time.tv_sec;
	microseconds_delta = recv_time.tv_usec - sending_time.tv_usec;
	round_trip_time = (double)seconds_delta + ((double)microseconds_delta / 1000);
	return round_trip_time;
}

static void handle_reply(int seq_num, const t_timeval sending_time)
{
	t_msghdr	msghdr;
	ssize_t		recv_res;
	char		msg_name[255];
	char 		msg_ctrl[255];
	char		icmph[65];
	t_iovec		iov;
	//t_icmph		icmph;
	int			recv_err;
	double		round_trip_time;


	iov.iov_base = &icmph;
	iov.iov_len = 65;
	memset(msg_name, 0, 255);
	memset(msg_ctrl, 0, 255);
	memset(icmph, 0, 65);
	msghdr.msg_name = msg_name;
	msghdr.msg_control = msg_ctrl;
	msghdr.msg_controllen = 255;
	msghdr.msg_iov = &iov;
	msghdr.msg_iovlen = 1;

	alarm(5); // -W option value
	recv_res = recvmsg(socket_fd, &msghdr, 0);
	recv_err = errno;
	round_trip_time = compute_rtt(sending_time);
	if (recv_res > -1)
		parse_reply(&msghdr, seq_num, round_trip_time);
	else if (recv_err == EBADF)
		return ;
	else
		display_recv_error(recv_err);
}

void	handle_ping_cycle(t_sockaddr *target, int seq_num)
{
	t_ip_icmp	ip_icmp;
	t_timeval	sending_time;

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
	send_echo(target, &ip_icmp, seq_num, &sending_time);
	handle_reply(seq_num, sending_time);
	
	if (socket_fd != -2)
		close(socket_fd);
}
