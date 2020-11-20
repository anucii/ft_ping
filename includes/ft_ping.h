/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdaufin <jdaufin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/15 18:28:42 by jdaufin           #+#    #+#             */
/*   Updated: 2020/11/20 23:59:19 by jdaufin          ###   ########lyon.fr   */
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
# include <signal.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <errno.h>
# include <netinet/ip_icmp.h>
# include <netinet/ip.h>
# include <sys/time.h>

# define MAX_FQDN 255
# define DYNARR_BUF 512 // TODO : reduce value to test reallocations
# define ANCIL_LEN 255
# define ICMPH_LEN 65

typedef	struct	s_options
{
	_Bool			help;
	_Bool			verbose;
	int				count;
	unsigned int	timeout;
	unsigned int	deadline;
	unsigned int	ttl;
}				t_options;

typedef struct	s_argv_cursor
{
	int				index;
	int				argc;
}				t_argv_cursor;


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

typedef struct in_addr	t_in_addr;

typedef struct icmp		t_ip_icmp;

typedef struct timeval	t_timeval;

typedef struct msghdr	t_msghdr;

typedef struct iovec	t_iovec;

typedef struct icmphdr	t_icmph;

typedef struct iphdr	t_iph;

typedef struct 	s_ping_shared_data
{
	t_sockaddr		target_addr;
	char			fqdn[MAX_FQDN];
	int				socket_fd;
	t_timeval		ping_first_timestamp;
	t_timeval		deadline_timestamp;
	int				sent_packets;
	int				received_packets;
	t_dynarray		all_rtts;
}				t_ping_shared_data;

typedef struct 	s_msghdr_content
{
	char			msg_name[MAX_FQDN];
	char			msg_control[ANCIL_LEN];
	char			icmph[ICMPH_LEN];
}				t_msghdr_content;

typedef struct	s_icmph_meta
{
	unsigned short	id;
	unsigned short	seq_num;
	unsigned int	recv_len;
	unsigned int	hdr_len;
	unsigned char	ttl;
	double			round_trip_time;
}				t_icmph_meta;


void			show_help(void);
void			show_count_error(void);
void			show_timeout_error(void);
void			show_deadline_error(void);
void			show_ttl_error(void);
void			show_unknown_address(char *address);
void			set_options(char c, char *argv[], const t_argv_cursor cursor, \
	t_options *options);
void			parse_address(char *param, char *dest);
void			resolve_address(char *input, char *ip_dest, char *fqdn);
_Bool			parse_args(int argc, char *argv[], char *target_address, \
	t_options *options);

_Bool			dynarray_init(t_dynarray *parray);
_Bool			dynarray_add(t_dynarray *parray, double val);
void			dynarray_free(t_dynarray *parray);
size_t			dynarray_getbuflen(void);

void			handle_cycle(char *ip_str, t_options *options);
_Bool			send_echo(t_ip_icmp *ip_icpm, t_timeval *psending_time, \
	int seq_num);
void			handle_reply(t_options *options, const t_timeval sending_time);
double			compute_rtt(const t_timeval sending_time);
unsigned int 	ihl_words_to_bytes(unsigned int ip_header_32bits_words);
unsigned int	little_endian(unsigned short val);

#endif
