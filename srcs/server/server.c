/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiboitel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/04 18:52:08 by tiboitel          #+#    #+#             */
/*   Updated: 2018/09/12 14:06:37 by tiboitel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

t_ftp_server	*server_create()
{
	t_ftp_server	*server;

	server = NULL;
	if (!(server = (t_ftp_server *)ft_memalloc(sizeof(t_ftp_server))))
		return (NULL);
	ft_bzero(server, sizeof(t_ftp_server));
	return (server);
}

int				server_init(t_ftp_server *server, int port)
{
	if ((server->root_directory = getcwd(server->root_directory, 4096)) == NULL)
	{
		dprintf(2, "server: Can not access the server root directory.\n");
	}
	server->current_directory = ft_strdup(server->root_directory);
	if (port < 0 || port > 60000)
	{
		dprintf(2, "server: Invalid port range.\n");
		return (-1);
	}
	server->port = port;
	if ((server->listen_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		dprintf(2, "server: Unable to create socket.\n");
		return (-1);
	}
	server->server_socket.sin_family = AF_INET;
	server->server_socket.sin_addr.s_addr = htonl(INADDR_ANY);
	server->server_socket.sin_port = htons(server->port);
	if ((bind(server->listen_fd, (struct sockaddr *)&(server->server_socket),
				sizeof(server->server_socket))) < 0)
	{
		dprintf(2, "server: Unable to bind server listening socket.\n");
		return (-1);
	}
	if (listen(server->listen_fd, 64) < 0)
	{
		dprintf(2, "server: Unable to listen on port %d\n", server->port);
		return (-1);
	}
	server->is_running = TRUE;
	return (1);
}

void			server_listen(t_ftp_server *server)
{
	server->is_running = TRUE;
	while(server->is_running)
	{
		server->socket_length = sizeof(server->client_socket);
		if ((server->send_fd = accept(server->listen_fd, (struct sockaddr *)&(server->client_socket), &(server->socket_length))) < 0)
			dprintf(2, "server: Unable to accept client on listening socket.\n");
		if ((server->pid = fork()) < 0)
		{
			dprintf(2, "server: Unable to fork new client. Server overload.\n");
			server->is_running = FALSE;
		}
		else
		{
			if (server->pid == 0)
			{
				close(server->listen_fd);
				send(server->send_fd, WELCOME_MSG, ft_strlen(WELCOME_MSG), 0);
				server_recv(server);
				server->is_running = FALSE;
			}
			else
				close(server->send_fd);
		}
		server->hit++;
	}
}

int				server_start(int port)
{
	t_ftp_server	*server;

	server = NULL;
	if ((server = server_create()) == NULL)
		return (-1);
	if ((server_init(server, port)) < 0)
		return (-1);
	while (server->is_running)
		server_listen(server);
	server_close(server);
	return (1);
}


int				server_close(t_ftp_server *server)
{
	dprintf(1, "Closing server PID: %d\n", server->pid);
	server->is_running = FALSE;
	if (get_command_callback() != NULL && server->pid != 0)
		command_callback_destroy(get_command_callback());
	server->is_running = FALSE;
	if (server->send_fd != 0)
		close(server->send_fd);
	if (server->root_directory != NULL)
		free(server->root_directory);
	if (server != NULL && server->pid != 0)
	{
		free(server);
		server = NULL;
	}
	return (1);
}
