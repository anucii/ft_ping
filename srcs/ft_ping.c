/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdaufin <jdaufin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/15 18:29:53 by jdaufin           #+#    #+#             */
/*   Updated: 2020/10/29 13:07:55 by jdaufin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

int	main(void)
{
	t_sockaddr *localaddress;

	localaddress = get_target_address();
	if (localaddress == NULL)
	{
		fprintf(stderr, "Erreur\n");
		return (-1);
	}
	handle_ping_cycle(localaddress);
	free(localaddress);
	return (0);
}
