/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiboitel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/18 19:42:42 by tiboitel          #+#    #+#             */
/*   Updated: 2020/08/18 18:27:32 by tiboitel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

t_ftp_client		*client_create(void)
{
	t_ftp_client	*client;

	client = NULL;
	if (!(client = (t_ftp_client *)ft_memalloc(sizeof(t_ftp_client))))
		return (NULL);
	ft_bzero(client, sizeof(t_ftp_client));
	return (client);
}

int						client_init(t_ftp_client *client, const char *host, int port)
{
	struct hostent		*hostname;
	struct sockaddr_in	server;

	ft_memcpy(client->prompt, "ftp> ", 5);
	hostname = gethostbyname(host);
	if (hostname == NULL)
		return (-1);
	server.sin_family = AF_INET;
	server.sin_port = htons(port);
	server.sin_addr.s_addr = *((unsigned long *)hostname->h_addr);
	if ((client->socket = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		return (-1);
	if (connect(client->socket, (struct sockaddr  *)&server, sizeof(server)) < 0)
		return (-1);
	return (1);
}

int					client_start(t_ftp_client *client)
{
	char 	buffer[4096];
	int		bytes_received;

	ft_bzero(buffer, 4096 - 1);
	client->running = TRUE;
	bytes_received = 0;
	while (client->running)
	{
		while ((bytes_received = recv(client->socket, buffer,  4096- 1, 0)) > 0)
		{
			dprintf(1, "%s\n", buffer);
			if (ft_strncmp(client->last_command, "QUIT", 4) == 0)
			{
				client->running = FALSE;
				return (0);
			}
			if (ft_strncmp(client->last_command, "GET", 3) == 0)
			{
				// Create function create file.
				int		fd;
				char	*data;
				char	*filename;

				if (buffer[0] != '5') // Very dirty solution. We need to parse the header. Not just reading the first code.
				{
					filename = strrchr(client->last_command, ' ') + 1; // SEGV HERE.
					filename = ft_strndup(filename, ft_strlen(filename) - 1);
					if (filename != NULL && strlen(filename) > 0)
					{
						fd = open(filename, O_WRONLY | O_CREAT, 0666);
						data = strchr(buffer, '\n') + 1;
						dprintf(fd, "%s", data);
						free(filename);
						filename = NULL;
						close(fd);
					}
				}
			}
			ft_bzero(buffer, 4096 - 1);
			dprintf(1, "%s", client->prompt);
			read(0, buffer, sizeof(buffer));
			send(client->socket, buffer, ft_strlen(buffer), 0);
			ft_memcpy(client->last_command, buffer, 5);
			ft_bzero(buffer, 4096 - 1);
			dprintf(0, "Last command is: %s", client->last_command);
			bytes_received = 0;
		}
	}
	return (-1);
}

void		client_close(t_ftp_client *client)
{
	close(client->socket);
	free(client);
	client = NULL;
}
