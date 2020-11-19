/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dynarray_free.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdaufin <jdaufin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 11:22:35 by jdaufin           #+#    #+#             */
/*   Updated: 2020/11/19 15:42:23 by jdaufin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

void	dynarray_free(t_dynarray *addr)
{
	if (!(addr && addr->array))
		return ;
	ft_memdel((void **)&(addr->array));
	addr->capacity = 0;
	addr->last_val_index = 0;
}
