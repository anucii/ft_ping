/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolve_address.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdaufin <jdaufin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/23 10:24:03 by jdaufin           #+#    #+#             */
/*   Updated: 2020/10/23 11:28:59 by jdaufin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

extern t_options	g_options;

static void			handle_failure(char *flawed_input)
{
	show_unknown_address(flawed_input);
	exit(EXIT_FAILURE);
}

static void			set_hints(t_addrinfo *hints)
{
	hints->ai_family = g_options.ai_family;
	hints->ai_socktype = SOCK_RAW;
	hints->ai_flags = AI_V4MAPPED | AI_ADDRCONFIG;
	hints->ai_protocol = IPPROTO_TCP;
	hints->ai_canonname = NULL;
	hints->ai_addr = NULL;
	hints->ai_next = NULL;
}

void				resolve_address(char *input, char *ip_dest)
{
	t_addrinfo		hints;
	t_addrinfo		*results;
	int				addr_ko;

	if (!input || !ip_dest)
		handle_failure(input);
	set_hints(&hints);
	addr_ko = getaddrinfo(input, NULL, &hints, &results);
	if (addr_ko || !results)
		handle_failure(input);
}
