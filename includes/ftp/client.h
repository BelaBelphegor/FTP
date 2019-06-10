/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiboitel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/02 22:42:05 by tiboitel          #+#    #+#             */
/*   Updated: 2018/10/08 18:31:15 by tiboitel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_CLIENT_H
# define FT_CLIENT_H

# include <libft.h>
# include <sys/socket.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <netdb.h>
# include <stdlib.h>
# include <arpa/inet.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>

#define CLRF 		"\r\n"
#define BUFFER_SIZE 4096
#define TRUE		1
#define FALSE		0

typedef struct		s_ftp_client
{
	int				socket;
	char			*current_directory;
	char			prompt[256];
	char			running;
	char			last_command[256];
}					t_ftp_client;

t_ftp_client		*client_create(void);
int					client_init(t_ftp_client *client, const char *hostname, int port);
int					client_start(t_ftp_client *client);
int					client_connect(t_ftp_client *client);
void				client_close(t_ftp_client *client);

#endif
