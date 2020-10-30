/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdaufin <jdaufin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/15 18:29:53 by jdaufin           #+#    #+#             */
/*   Updated: 2020/10/30 16:27:00 by jdaufin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

int ttl;
extern int socket_fd;

void on_timeout(int signum)
{
	if (signum == SIGALRM)
	{
		close(socket_fd);
	}
}

int	main(int ac, char *av[])
{
	t_sockaddr *localaddress;
	char address[255];
	char *default_address = "google.com";
	int i;
	
	memset(address, 0, 255);
	ttl = ac == 3 ? atoi(av[2]) : 120;
	if (ac > 1)
	{
		memcpy(address, av[1], strlen(av[1]));
	}
	else
	{
		memcpy(address, default_address, strlen(default_address));
	}
	

	localaddress = get_target_address(address);
	if (localaddress == NULL)
	{
		fprintf(stderr, "Erreur\n");
		return (-1);
	}
	for (i = 0; i < 5; i++)
	{
		signal(SIGALRM, &on_timeout);
		handle_ping_cycle(localaddress, i);
	}
	free(localaddress);
	return (0);
}
