/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdaufin <jdaufin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/15 18:29:53 by jdaufin           #+#    #+#             */
/*   Updated: 2020/11/19 16:35:42 by jdaufin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

t_ping_shared_data	g_ping_data;

static int			exit_ping()
{
	// TODO : display rtt bottom line from g_ping_data;
	return (EXIT_SUCCESS);
}

int					main(int argc, char *argv[])
{
	t_options	options;
	char		address_param[MAX_FQDN];
	char		fqdn[MAX_FQDN];
	char		ip_address[INET6_ADDRSTRLEN];

	ft_bzero(&g_ping_data, sizeof(t_ping_shared_data));
	ft_bzero(&options, sizeof(t_options));
	ft_bzero(address_param, MAX_FQDN);
	ft_bzero(ip_address, INET6_ADDRSTRLEN);
	if (!parse_args(argc, argv, address_param, &options) || options.help)
	{
		show_help();
		return (options.help ? EXIT_SUCCESS : EXIT_FAILURE);
	}
	resolve_address(address_param, ip_address, fqdn);
	// TODO handle ping cycle
	printf("PING %s (%s)\n", fqdn, ip_address); // move to ping_cycle() ?
	return (exit_ping());
}
