/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdaufin <jdaufin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/15 18:28:42 by jdaufin           #+#    #+#             */
/*   Updated: 2020/10/29 13:07:37 by jdaufin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PING_H
# define FT_PING_H

# include <sys/types.h>
# include <sys/socket.h>
# include <netdb.h>
# include <stdio.h>
# include <arpa/inet.h>
# include <stdlib.h>
# include <errno.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <netinet/ip_icmp.h>

# define INET_ADDRLEN 128

typedef	struct addrinfo		t_addrinfo;
typedef	struct sockaddr		t_sockaddr;
typedef struct sockaddr_in	t_sockaddr_in;
typedef struct in_addr		t_in_addr;
typedef struct icmp			t_ip_icmp;

t_sockaddr	*get_target_address();
void		handle_ping_cycle(t_sockaddr *target);

#endif
