/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdaufin <jdaufin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/15 18:29:53 by jdaufin           #+#    #+#             */
/*   Updated: 2020/10/22 20:26:02 by jdaufin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

t_options	g_options;

int			main(int argc, char *argv[])
{
	char	address[MAX_FQDN];

	ft_bzero(address, MAX_FQDN);
	if (!parse_args(argc, argv, address) || g_options.help)
	{
		show_help();
		return (g_options.help ? EXIT_SUCCESS : EXIT_FAILURE);
	}
	printf("PING %s\n", address);
	return (EXIT_SUCCESS);
}
