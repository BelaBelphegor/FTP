/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   receiver.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiboitel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/31 20:05:15 by tiboitel          #+#    #+#             */
/*   Updated: 2020/08/18 17:18:21 by tiboitel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

int		server_recv(t_ftp_server *server)
{
	char			buffer[BUFFER_SIZE];
	size_t			bytes_recv;
	t_command		*command;
	t_ftp_response	*response;

	ft_bzero(buffer, BUFFER_SIZE);
	bytes_recv = 0;
	while ((bytes_recv = recv(server->send_fd, buffer, BUFFER_SIZE - 1, 0)) > 0)
	{
		response = ftp_response_create();
		response->context = (void *)(server);
		dprintf(1, "Receives %zu Bytes. Buffer: %s\n", bytes_recv, buffer);
		response->send_fd = server->send_fd;
		// If mode is command
		if ((command = stoc(buffer)) == NULL) 
			dprintf(3, "Unable to parse command.\n");
		ft_bzero(buffer, BUFFER_SIZE);
		command_dispatcher(command, response);
		ftp_response_destroy(response);
		// Need to add if state is FILES
		if (ft_strncmp(command->name, "QUIT", 4) == 0)
		{
			server->is_running = FALSE;
			return (0);
		}
	}
	return (1);
}
