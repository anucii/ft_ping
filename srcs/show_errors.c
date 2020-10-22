/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_errors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdaufin <jdaufin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 18:04:09 by jdaufin           #+#    #+#             */
/*   Updated: 2020/10/22 18:39:07 by jdaufin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

void	show_count_error()
{
	printf("ft_ping: bad number of packets to transmit.\n");
}

void	show_timeout_error()
{
	printf("ft_ping: bad linger time.\n");
}

void	show_deadline_error()
{
	printf("ft_ping: bad wait time.\n");
}
