/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdaufin <jdaufin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/15 18:29:53 by jdaufin           #+#    #+#             */
/*   Updated: 2020/10/23 12:09:40 by jdaufin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

t_options	g_options;

int			main(int argc, char *argv[])
{
	char	address[MAX_FQDN];
	char	ip_address[INET6_ADDRSTRLEN];

	ft_bzero(address, MAX_FQDN);
	ft_bzero(ip_address, INET6_ADDRSTRLEN);
	if (!parse_args(argc, argv, address) || g_options.help)
	{
		show_help();
		return (g_options.help ? EXIT_SUCCESS : EXIT_FAILURE);
	}
	resolve_address(address, ip_address);
	printf("PING %s (%s)\n", address, ip_address);
	return (EXIT_SUCCESS);
}
