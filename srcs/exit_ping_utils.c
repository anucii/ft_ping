/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_ping_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdaufin <jdaufin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 17:58:21 by jdaufin           #+#    #+#             */
/*   Updated: 2020/11/27 15:23:07 by jdaufin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

extern t_ping_shared_data	g_ping_data;

double	get_rtt_min()
{
	ssize_t	i;
	double	min;

	if (!g_ping_data.all_rtts.array)
		return (0);
	i = -1;
	min = g_ping_data.all_rtts.array[0];
	while (++i < (g_ping_data.all_rtts.last_val_index + 1))
		min = g_ping_data.all_rtts.array[i] < min ? \
			g_ping_data.all_rtts.array[i] : min;
	return (min);
}

double	get_rtt_max()
{
	ssize_t	i;
	double	max;

	if (!g_ping_data.all_rtts.array)
		return (0);
	i = -1;
	max = g_ping_data.all_rtts.array[0];
	while (++i < (g_ping_data.all_rtts.last_val_index + 1))
		max = g_ping_data.all_rtts.array[i] > max ? \
			g_ping_data.all_rtts.array[i] : max;
	return (max);
}

double	get_rtt_avg()
{
	ssize_t	i;
	double	average;
	double	sum;

	if (!g_ping_data.all_rtts.array)
		return (0);
	sum = 0;
	i = -1;
	while (++i < (g_ping_data.all_rtts.last_val_index + 1))
		sum += g_ping_data.all_rtts.array[i];
	average = sum / i;
	return (average);
}

double	get_rtt_mdev()
{
	ssize_t	i;
	double	mdev;
	double	average;
	double	deviation;
	double	dev_sum;

	if (!g_ping_data.all_rtts.array)
		return (0);
	i = -1;
	dev_sum = 0;
	average = get_rtt_avg();
	while (++i < (g_ping_data.all_rtts.last_val_index + 1))
	{
		deviation = average - g_ping_data.all_rtts.array[i];
		dev_sum += deviation > 0 ? deviation : -deviation;
	}
	mdev = dev_sum / i;
	return (mdev);
}
