/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdaufin <jdaufin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/15 18:28:42 by jdaufin           #+#    #+#             */
/*   Updated: 2020/10/22 18:28:42 by jdaufin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PING_H
# define FT_PING_H
# include "libft.h"
# include <stdio.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <netdb.h>

# define MAX_FQDN 255

typedef	struct	s_options
{
	_Bool			help;
	_Bool			verbose;
	int				ai_family;
	int				count;
	unsigned int	timeout;
	unsigned int	deadline;
}				t_options;

void			show_help();
void			show_count_error();
void			show_timeout_error();
void			show_deadline_error();
void			set_options(char c, char *argv[], int pos, int argc);
_Bool			parse_args(int argc, char *argv[]);

#endif
