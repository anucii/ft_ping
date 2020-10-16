/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_local_address.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdaufin <jdaufin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/15 18:45:28 by jdaufin           #+#    #+#             */
/*   Updated: 2020/10/16 10:49:25 by jdaufin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

static void	set_hints(struct addrinfo *hints)
{
	hints->ai_family = AF_INET;
	hints->ai_socktype = 0;
	hints->ai_flags = AI_ADDRCONFIG | AI_ALL;
	hints->ai_protocol = 0;
	hints->ai_canonname = NULL;
	hints->ai_addr = NULL;
	hints->ai_next = NULL;
}

static void display_addr(char *addr)
{
	if (addr == NULL)
	{
		return;
	}
	printf("%s\n", addr);
}

char	*get_local_address()
{
	char *localdomain = "localhost";
	char *localaddress;
	char *ipv6localaddress;
	struct addrinfo hints;
	struct addrinfo *result;
	struct addrinfo *next;
	int s;

	localaddress = malloc(32);
	ipv6localaddress = malloc(32);
	if ((localaddress == NULL) || (ipv6localaddress == NULL))
	{
		return (NULL);
	}
	memset(&hints, 0, sizeof(struct addrinfo));
	set_hints(&hints);
	s = getaddrinfo(localdomain, NULL, NULL, &result);
	if ((s != 0) || (result == NULL))
	{
		fprintf(stderr, "%s\n", gai_strerror(s));
		return (NULL);
	}
	memset(localaddress, 0, 32);
	//memset(ipv6localaddress, 0, 32);
	next = result;
	while (next)
	{
		struct sockaddr debug;
		debug = *(next->ai_addr);
		inet_ntop(AF_INET, next->ai_addr->sa_data, localaddress, 31);
		//inet_ntop(AF_INET6, next->ai_addr, ipv6localaddress, 31);
		display_addr(localaddress);
		//display_addr(ipv6localaddress);
		next = next->ai_next;
	}

	return (localaddress);
}
