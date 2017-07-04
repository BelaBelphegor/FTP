/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiboitel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/04 18:41:01 by tiboitel          #+#    #+#             */
/*   Updated: 2017/07/04 18:56:45 by tiboitel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SERVER_H
# define FT_SERVER_H
# include <libft.h>
# include <sys/socket.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <netdb.h>
# include <stdlib.h>
# include <arpa/inet.h>
# include <stdio.h>
# include <unistd.h>

#define CLRF 		"\r\n"
#define BUFFER_SIZE 4096
#define TRUE		1
#define FALSE		0

typedef	char bool;
typedef	struct		s_ftp_server
{
	int						pid;
	int						listen_fd;
	int						send_fd;
	int						port;
	struct sockaddr_in		client_socket;
	struct sockaddr_in		server_socket;
	unsigned int			socket_lenght;
	int						hit;
	bool					is_running;
}					t_ftp_server;
#endif
