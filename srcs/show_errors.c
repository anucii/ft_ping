/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_errors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdaufin <jdaufin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 18:04:09 by jdaufin           #+#    #+#             */
/*   Updated: 2020/10/23 17:53:37 by jdaufin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

void	show_count_error(void)
{
	printf("ft_ping: bad number of packets to transmit.\n");
}

void	show_timeout_error(void)
{
	printf("ft_ping: bad linger time.\n");
}

void	show_deadline_error(void)
{
	printf("ft_ping: bad wait time.\n");
}

void	show_ttl_error(void)
{
	printf("ft_ping: can't set unicast time-to-live: invalid argument\n");
}

void	show_unknown_address(char *address)
{
	printf("ft_ping: %s: Unknown name or service\n", address);
}
