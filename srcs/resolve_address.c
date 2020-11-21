/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolve_address.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdaufin <jdaufin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/23 10:24:03 by jdaufin           #+#    #+#             */
/*   Updated: 2020/11/21 01:20:57 by jdaufin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

extern t_ping_shared_data	g_ping_data;

static void		handle_failure(char *flawed_input)
{
	show_unknown_address(flawed_input);
	exit(EXIT_FAILURE);
}

static void		set_hints(t_addrinfo *hints)
{
	hints->ai_family = AF_INET;
	hints->ai_socktype = SOCK_RAW;
	hints->ai_flags = AI_ADDRCONFIG | AI_CANONNAME;
	hints->ai_protocol = IPPROTO_TCP;
	hints->ai_canonname = NULL;
	hints->ai_addr = NULL;
	hints->ai_next = NULL;
}

static _Bool	ip_to_str(char *ip_dest, t_addrinfo *results, char *fqdn)
{
	t_sockaddr			*sockaddr;
	t_sockaddr_in		*sockaddr_in;
	t_in_addr			*in_addr;

	sockaddr = results->ai_addr;
	ft_bzero(fqdn, MAX_FQDN);
	if (results->ai_canonname)
		ft_strlen(results->ai_canonname) > (size_t)MAX_FQDN ? \
		ft_memcpy(fqdn, results->ai_canonname, MAX_FQDN) :\
		ft_strcpy(fqdn, results->ai_canonname);
	if (!sockaddr)
		return (0);
	sockaddr_in = (t_sockaddr_in *)sockaddr;
	in_addr = &(sockaddr_in->sin_addr);
	if (!inet_ntop(sockaddr->sa_family, in_addr, ip_dest, \
		sizeof(t_sockaddr_in)))
		return (0);
	ft_memcpy(&g_ping_data.target_addr, sockaddr, sizeof(t_sockaddr));
	return (1);
}

void			resolve_address(char *input, char *ip_dest, char *fqdn)
{
	t_addrinfo			hints;
	t_addrinfo			*results;
	int					addr_ko;

	if (!input || !ip_dest)
		handle_failure(input);
	set_hints(&hints);
	addr_ko = getaddrinfo(input, NULL, &hints, &results);
	if (addr_ko || !results || !ip_to_str(ip_dest, results, fqdn))
		handle_failure(input);
	freeaddrinfo(results);
}
