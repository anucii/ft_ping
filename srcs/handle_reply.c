/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_reply.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdaufin <jdaufin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 23:59:47 by jdaufin           #+#    #+#             */
/*   Updated: 2020/11/20 16:00:10 by jdaufin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

extern t_ping_shared_data	g_ping_data;

static void		display_result(t_icmph *picmph, \
	t_icmph_meta *pmetadata, char *addr_str, _Bool verbose)
{
	_Bool					matching_id;
	_Bool					type_is_reply;
	
	matching_id = pmetadata->id == (unsigned short)getpid();
	type_is_reply = picmph->type == ICMP_ECHOREPLY;
	if (matching_id && type_is_reply)
	{
		g_ping_data.received_packets += 1;
		dynarray_add(&g_ping_data.all_rtts, pmetadata->round_trip_time);
		printf("%d bytes from %s (%s): icmp_seq=%d ttl=%d time=%.1fms\n", \
			pmetadata->recv_len, g_ping_data.fqdn, addr_str, \
			pmetadata->seq_num, pmetadata->ttl, pmetadata->round_trip_time);
	}
	else if (matching_id && verbose)
		printf("%d bytes from %s (%s): type=%d code=%d\n", \
			pmetadata->recv_len, g_ping_data.fqdn, addr_str, \
			picmph->type, picmph->code);
	else if (matching_id)
		printf("From %s (%s) icmp_seq=%d Unexpected response type\n", \
			g_ping_data.fqdn, addr_str, pmetadata->seq_num);
}

static void		parse_reply(t_msghdr *pmsghdr, const double round_trip_time, _Bool verbose)
{
	t_in_addr		*in_addr;
	t_icmph			*picmph;
	t_iph			*piph;
	t_icmph_meta	metadata;
	char			addr_str[MAX_FQDN];

	ft_bzero(&metadata, sizeof(t_icmph_meta));
	in_addr = &((t_sockaddr_in *)pmsghdr->msg_name)->sin_addr;
	if (!inet_ntop(AF_INET, in_addr, addr_str, MAX_FQDN))
		ft_memcpy((void *)addr_str, "\0", 1);
	piph = (t_iph *)pmsghdr->msg_iov->iov_base;
	metadata.hdr_len = ihl_words_to_bytes(piph->ihl);
	metadata.ttl = piph->ttl;
	picmph = (t_icmph *)(pmsghdr->msg_iov->iov_base + metadata.hdr_len);
	metadata.id = picmph->un.echo.id;
	metadata.seq_num = picmph->un.echo.sequence;
	metadata.recv_len = little_endian(piph->tot_len) - metadata.hdr_len;
	metadata.round_trip_time = round_trip_time;
	display_result(picmph, &metadata, addr_str, verbose);
}

static void		prepare_msghdr(t_msghdr *pmsghdr, t_msghdr_content *pcontent, \
	t_iovec *iov)
{
	ft_bzero(pcontent, sizeof(t_msghdr_content));
	ft_bzero(pmsghdr, sizeof(t_msghdr));
	ft_bzero(iov, sizeof(t_iovec));
	iov->iov_base = &pcontent->icmph;
	iov->iov_len = ICMPH_LEN;
	pmsghdr->msg_iov = iov;
	pmsghdr->msg_iovlen = 1;
	pmsghdr->msg_name = pcontent->msg_name;
	pmsghdr->msg_namelen = MAX_FQDN;
	pmsghdr->msg_control = pcontent->msg_control;
	pmsghdr->msg_controllen = ANCIL_LEN;
}

void			handle_reply(t_options *options, const t_timeval sending_time)
{
	t_msghdr				msghdr;
	t_msghdr_content		content;
	t_iovec					iov;
	ssize_t					recv_res;
	double					round_trip_time;

	prepare_msghdr(&msghdr, &content, &iov);
	if (options->timeout > 0)
		alarm(options->timeout);
	recv_res = recvmsg(g_ping_data.socket_fd, &msghdr, 0);
	round_trip_time = compute_rtt(sending_time);
	if (recv_res > -1)
		parse_reply(&msghdr, round_trip_time, options->verbose);
	else
		fprintf(stderr, "ft_ping: recvmsg: operation failed");	
}
