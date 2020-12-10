/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_echo_reply.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdaufin <jdaufin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 16:13:00 by jdaufin           #+#    #+#             */
/*   Updated: 2020/12/10 16:48:06 by jdaufin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

extern t_ping_shared_data	g_ping_data;

static void	fill_icmp_header(t_icmph *src, t_ip_icmp *hdr)
{
	hdr->icmp_type = 0;
	hdr->icmp_code = 0;
	hdr->icmp_cksum = 0;
	hdr->icmp_hun.ih_idseq.icd_id = src->un.echo.id;
	hdr->icmp_hun.ih_idseq.icd_seq = src->un.echo.sequence;
	hdr->icmp_cksum = icmp_checksum(hdr);
}

_Bool		send_echo_reply(t_icmph *src)
{
	t_ip_icmp	dest;
	_Bool		msg_sent;

	ft_bzero((void *)&dest, sizeof(t_ip_icmp));
	fill_icmp_header(src, &dest);
	msg_sent = sendto(g_ping_data.socket_fd, &dest, \
		(size_t)sizeof(t_ip_icmp), 0, &g_ping_data.target_addr, \
		sizeof(t_sockaddr)) > -1;
	return (msg_sent);
}
