/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdaufin <jdaufin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/15 18:29:53 by jdaufin           #+#    #+#             */
/*   Updated: 2021/04/29 16:49:36 by jdaufin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

t_ping_shared_data	g_ping_data;

int					main(int argc, char *argv[])
{
	t_options	options;
	char		address_param[MAX_FQDN];
	char		ip_address[INET6_ADDRSTRLEN];

	ft_bzero(&g_ping_data, sizeof(t_ping_shared_data));
	ft_bzero(&options, sizeof(t_options));
	options.timeout = 1;
	ft_bzero(address_param, MAX_FQDN);
	ft_bzero(ip_address, INET6_ADDRSTRLEN);
	if (!parse_args(argc, argv, address_param, &options) || options.help)
	{
		show_help();
		return (options.help ? EXIT_SUCCESS : EXIT_FAILURE);
	}
	resolve_address(address_param, ip_address, g_ping_data.fqdn);
	signal(SIGINT, &exit_ping);
	signal(SIGQUIT, &exit_ping);
	signal(SIGALRM, &exit_ping);
	handle_cycle(ip_address, &options);
	exit_ping(0);
}
