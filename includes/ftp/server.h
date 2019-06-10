/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiboitel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/04 18:41:01 by tiboitel          #+#    #+#             */
/*   Updated: 2018/10/08 19:28:10 by tiboitel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SERVER_H
# define FT_SERVER_H

# include <signal.h>
# include "shared.h"

typedef	struct				s_ftp_server
{
	int						pid;
	int						listen_fd;
	int						send_fd;
	int						port;
	struct sockaddr_in		client_socket;
	struct sockaddr_in		server_socket;
	unsigned int			socket_length;
	int						hit;
	t_bool					is_running;
	char					*root_directory;
	char					*current_directory;
}							t_ftp_server;

enum						e_ftp_state
{
	COMMANDS, FILES
};

int							server_start(int port);
int							server_recv(t_ftp_server *server);
int							server_close();
t_ftp_response				*ftp_response_create(void);
void						ftp_response_destroy(t_ftp_response *response);
void						handler_ls(t_command *command, t_ftp_response *response);
void						handler_pwd(t_command *command, t_ftp_response *response);
void						handler_cd(t_command *command, t_ftp_response *response);
void						handler_get(t_command *command, t_ftp_response *response);

void						handler_quit(t_command *command, t_ftp_response *response);
void						handler_command_not_found(t_command *command, t_ftp_response *response);
int							command_dispatcher(t_command *command, t_ftp_response *response);
int							change_directory(char *path);
t_bool						is_before_root(char *path, char *root_directory);
char						*execute_with_pipe(const char *path, const char *args);
#endif
