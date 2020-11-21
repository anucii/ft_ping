/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdaufin <jdaufin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 23:58:46 by jdaufin           #+#    #+#             */
/*   Updated: 2020/11/21 01:24:40 by jdaufin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

extern t_ping_shared_data	g_ping_data;

static unsigned short	checksum(t_ip_icmp *hdr)
{
	unsigned short	sum;
	unsigned short	*array;
	int				i;
	int				size;

	size = sizeof(t_ip_icmp) / 2;
	i = -1;
	array = (unsigned short *)hdr;
	sum = 0;
	while (++i < size)
	{
		sum += array[i];
	}
	return (sum ^ 0xFFFF);
}

static void				fill_icmp_header(t_ip_icmp *hdr, int seq_num)
{
	hdr->icmp_type = 8;
	hdr->icmp_code = 0;
	hdr->icmp_cksum = 0;
	hdr->icmp_hun.ih_idseq.icd_id = (unsigned short)getpid();
	hdr->icmp_hun.ih_idseq.icd_seq = seq_num;
	hdr->icmp_cksum = checksum(hdr);
}

_Bool					send_echo(t_ip_icmp *ip_icmp, \
	t_timeval *psending_time, int seq_num)
{
	_Bool					msg_sent;

	ft_bzero((void *)ip_icmp, sizeof(t_ip_icmp));
	fill_icmp_header(ip_icmp, seq_num);
	gettimeofday(psending_time, NULL);
	msg_sent = sendto(g_ping_data.socket_fd, ip_icmp, \
		(size_t)sizeof(t_ip_icmp), 0, &g_ping_data.target_addr, \
		sizeof(t_sockaddr)) > -1;
	g_ping_data.sent_packets += msg_sent;
	if (!msg_sent)
		fprintf(stderr, "ft_ping: sendto: operation failed\n");
	return (msg_sent);
}
