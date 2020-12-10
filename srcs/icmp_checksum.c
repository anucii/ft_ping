/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   icmp_checksum.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdaufin <jdaufin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 16:21:04 by jdaufin           #+#    #+#             */
/*   Updated: 2020/12/10 16:22:52 by jdaufin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

unsigned short	icmp_checksum(t_ip_icmp *hdr)
{
	unsigned short	sum;
	unsigned short	*array;
	int				i;
	int				size;

	size = sizeof(t_ip_icmp) / 2;
	i = -1;
	array = (unsigned short *)hdr;
	sum = 0;
	while (++i < size)
	{
		sum += array[i];
	}
	return (sum ^ 0xFFFF);
}
