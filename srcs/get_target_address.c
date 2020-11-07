/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_target_address.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdaufin <jdaufin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/15 18:45:28 by jdaufin           #+#    #+#             */
/*   Updated: 2020/11/07 13:18:39 by jdaufin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

extern char *g_fqdn;

static void	set_hints(t_addrinfo *hints)
{
	hints->ai_family = AF_INET;
	hints->ai_socktype = SOCK_RAW;
	hints->ai_flags = AI_V4MAPPED | AI_ADDRCONFIG | AI_CANONNAME;
	hints->ai_protocol = IPPROTO_ICMP;
	hints->ai_canonname = NULL;
	hints->ai_addr = NULL;
	hints->ai_next = NULL;
}

static void display_addr(char *addr, t_addrinfo *info)
{
	if ((!addr) || (!info))
	{
		return;
	}
	printf("%s, flags:0x%x family:%d, socktype:%d, protocol:%d\n", addr, \
		info->ai_flags, info->ai_family, info->ai_socktype, info->ai_protocol);
}

t_sockaddr	*get_target_address(char *str_addr)
{
	char localaddress[NI_MAXHOST];
	t_sockaddr *ret;
	t_addrinfo hints;
	t_addrinfo *results;
	t_addrinfo *next;
	int s;

	printf("NI_MAXHOST = %d\n", NI_MAXHOST);
	ret = (t_sockaddr *)malloc(sizeof(t_sockaddr));
	if (ret == NULL)
	{
		return (NULL);
	}

	memset(&hints, 0, sizeof(t_addrinfo));
	set_hints(&hints);
	s = getaddrinfo(str_addr, NULL, &hints, &results);
	if ((s != 0) || (results == NULL))
	{
		fprintf(stderr, "%s\n", gai_strerror(s));
		return (NULL);
	}
	memset(localaddress, 0, NI_MAXHOST);
	g_fqdn = (char *)malloc(256);
	if (g_fqdn == NULL)
	{
		fprintf(stderr, "Memory allocation for FQDN failed\n");
		return (NULL);
	}
	memset(g_fqdn, 0, 256);
	next = results;
	while (next)
	{
		t_sockaddr	*sockaddr;
		t_in_addr	*sockaddr_in;
		sockaddr = next->ai_addr;
		sockaddr_in = &((t_sockaddr_in *)sockaddr)->sin_addr;
		if (!inet_ntop(AF_INET, sockaddr_in, (char *)localaddress, sizeof(t_sockaddr_in)))
		{
			if (errno == EAFNOSUPPORT)
			{
				fprintf(stderr, "AF_INET is not a valid address family");
			}
			else if (errno == ENOSPC)
			{
				fprintf(stderr, "The converted address string would exceep %d bytes.", NI_MAXHOST);
			}
			else
			{
				fprintf(stderr, "Unknown error code : %d", errno);
			}
			
		}
		else if (next->ai_canonname)
			memcpy(g_fqdn, next->ai_canonname, 255);
		display_addr(localaddress, next);
		memcpy(ret, sockaddr, sizeof(t_sockaddr));
		next = next->ai_next;
	}

	return (ret);
}
