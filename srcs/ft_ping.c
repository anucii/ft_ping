/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdaufin <jdaufin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/15 18:29:53 by jdaufin           #+#    #+#             */
/*   Updated: 2020/11/20 16:15:04 by jdaufin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

t_ping_shared_data	g_ping_data;

static void			exit_ping(int sig_value)
{
	// TODO : display rtt bottom line from g_ping_data;
	(void)sig_value;
	if (g_ping_data.socket_fd > 0)
	{
		close(g_ping_data.socket_fd);
		g_ping_data.socket_fd = -2;
	}
	printf("--- %s ping statistics ---\n", g_ping_data.fqdn);
	printf("%d packets transmitted, %d received, TODO: percentage and time\n", \
		g_ping_data.sent_packets, g_ping_data.sent_packets);
	exit(EXIT_SUCCESS);
}

int					main(int argc, char *argv[])
{
	t_options	options;
	char		address_param[MAX_FQDN];
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
	resolve_address(address_param, ip_address, g_ping_data.fqdn);
	signal(SIGINT, &exit_ping);
	signal(SIGQUIT, &exit_ping);
	signal(SIGALRM, &exit_ping);
	handle_cycle(ip_address, &options);
	exit_ping(0);
}
