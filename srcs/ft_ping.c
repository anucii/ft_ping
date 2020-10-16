/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdaufin <jdaufin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/15 18:29:53 by jdaufin           #+#    #+#             */
/*   Updated: 2020/10/15 22:44:25 by jdaufin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

int	main(void)
{
	char *localaddress;

	localaddress = get_local_address();
	if (localaddress == NULL)
	{
		fprintf(stderr, "Erreur\n");
		return (-1);
	}
	printf("%s\n", localaddress);
	return (0);
}
