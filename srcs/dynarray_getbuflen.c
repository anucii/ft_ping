/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dynarray_getbuflen.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdaufin <jdaufin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 11:33:23 by jdaufin           #+#    #+#             */
/*   Updated: 2020/11/26 18:55:22 by jdaufin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

ssize_t	dynarray_getbuflen(void)
{
	ssize_t buf_len;

	buf_len = DYNARR_BUF > 16 ? (ssize_t)DYNARR_BUF : 16;
	return (buf_len);
}
