/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdaufin <jdaufin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/15 18:29:53 by jdaufin           #+#    #+#             */
/*   Updated: 2020/10/30 12:01:53 by jdaufin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

int	main(void)
{
	t_sockaddr *localaddress;
	int i;

	localaddress = get_target_address();
	if (localaddress == NULL)
	{
		fprintf(stderr, "Erreur\n");
		return (-1);
	}
	for (i = 0; i < 5; i++)
	{
		signal(SIGALRM, SIG_DFL);
		handle_ping_cycle(localaddress, i);
	}
	free(localaddress);
	return (0);
}
