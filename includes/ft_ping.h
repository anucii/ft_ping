/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdaufin <jdaufin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/15 18:28:42 by jdaufin           #+#    #+#             */
/*   Updated: 2020/11/19 15:37:30 by jdaufin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PING_H
# define FT_PING_H
# include "libft.h"
# include <stdio.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <netdb.h>
# include <arpa/inet.h>

# define MAX_FQDN 255
# define DYNARR_BUF 512 // TODO : reduce value to test reallocations

typedef	struct	s_options
{
	_Bool			help;
	_Bool			verbose;
	int				count;
	unsigned int	timeout;
	unsigned int	deadline;
	unsigned int	ttl;
}				t_options;

typedef struct	s_pkglen
{
	unsigned short	tot_len;
	unsigned short	data_len;
}				t_pkglen;

typedef struct	s_dynarray
{
	double	*array;
	size_t	capacity;
	size_t	last_val_index;
}				t_dynarray;

typedef struct addrinfo	t_addrinfo;

typedef struct sockaddr	t_sockaddr;

typedef struct sockaddr_in	t_sockaddr_in;

typedef struct sockaddr_in6	t_sockaddr_in6;

typedef struct in_addr	t_in_addr;

typedef struct in6_addr	t_in6_addr;

void			show_help(void);
void			show_count_error(void);
void			show_timeout_error(void);
void			show_deadline_error(void);
void			show_ttl_error(void);
void			show_unknown_address(char *address);
void			set_options(char c, char *argv[], int pos, int argc, \
	t_options *options);
void			parse_address(char *param, char *dest);
void			resolve_address(char *input, char *ip_dest, char *fqdn);
_Bool			parse_args(int argc, char *argv[], char *target_address, \
	t_options *options);

_Bool			dynarray_init(t_dynarray *parray);
_Bool			dynarray_add(t_dynarray *parray, double val);
void			dynarray_free(t_dynarray *parray);
size_t			dynarray_getbuflen(void);

#endif
