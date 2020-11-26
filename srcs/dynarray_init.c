/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dynarray_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdaufin <jdaufin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 11:21:32 by jdaufin           #+#    #+#             */
/*   Updated: 2020/11/26 18:58:16 by jdaufin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

_Bool	dynarray_init(t_dynarray *parray)
{
	double	*val_array;
	ssize_t	capacity;
	ssize_t	memsize;

	if (!parray)
		return (0);
	capacity = dynarray_getbuflen();
	memsize = capacity * sizeof(double);
	val_array = (double *)ft_memalloc(memsize);
	if (!val_array)
		return (0);
	ft_bzero(val_array, memsize);
	parray->array = val_array;
	parray->capacity = capacity;
	parray->last_val_index = -1;
	return (1);
}
