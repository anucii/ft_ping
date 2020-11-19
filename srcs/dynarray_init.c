/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dynarray_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdaufin <jdaufin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 11:21:32 by jdaufin           #+#    #+#             */
/*   Updated: 2020/11/19 15:43:16 by jdaufin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

_Bool	dynarray_init(t_dynarray *parray)
{
	double	*val_array;
	size_t	capacity;
	size_t	memsize;

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
	parray->last_val_index = 0;
	return (1);
}
