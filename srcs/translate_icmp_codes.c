/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translate_icmp_codes.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdaufin <jdaufin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 20:40:38 by jdaufin           #+#    #+#             */
/*   Updated: 2021/04/29 20:55:42 by jdaufin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

void	translate_icmp_type(char *dst, uint8_t type)
{
	if (type == ICMP_DEST_UNREACH)
		ft_strcpy(dst, "Destination Unreachable");
	else if (type == ICMP_TIME_EXCEEDED)
		ft_strcpy(dst, "Time-To-Live Exceeded");
	else if (type == ICMP_PARAMETERPROB)
		ft_strcpy(dst, "Parameter problem");
	else
		ft_strcpy(dst, "Unexpected response type");
}