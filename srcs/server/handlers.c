/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiboitel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/18 22:19:13 by tiboitel          #+#    #+#             */
/*   Updated: 2018/11/29 18:20:16 by tiboitel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	handler_ls(t_command *command, t_ftp_response *response)
{
	char			*buffer;

	if (command->args == NULL)
		command->args = ft_strdup(".");
	if (command == NULL || command->args == NULL)
	{
		dprintf(2, "Arguments or name error\n");
	}
	if ((buffer = execute_with_pipe("/bin/ls", command->args)) != NULL)
	{
		response->code = 200;
		response->message = ft_strdup("The requested action has been successfully completed");
	}
	else
	{
		response->code = 404;
		response->message = ft_strdup("Request action not taken. File unavailable.");
	}
	dprintf(response->send_fd, "%d %s%s%s %s", response->code, response->message, CLRF, buffer, CLRF);
}

void	handler_cd(t_command *command, t_ftp_response *response)
{
	int			flag;
	char		*root_directory;

	flag = 0;
	root_directory = ((t_ftp_server *)(response->context))->root_directory;
	if (command->args == NULL)
		command->args = ft_strdup(root_directory);
	if (is_before_root(command->args, root_directory) == TRUE || (flag = change_directory(command->args)) < 0)
	{
		response->code = 550;
		response->message = ft_strdup("Request action not taken. File unavailable (e.g file not found, no access).");
	}
	else
	{
		response->code = 200;
		response->message = ft_strdup("The requested action has been successfully completed");
	}
	dprintf(1, "CD Flag: %d, Command->args: %s\n", flag, command->args);
	dprintf(response->send_fd, "%d %s%s", response->code, response->message, CLRF);
}

void	handler_pwd(t_command *command, t_ftp_response *response)
{
	char	buffer[256];

	(void)command;
	ft_bzero(buffer, 256);
	if (getcwd(buffer, sizeof(buffer)) == NULL)
			perror("getcwd() error\n");
	response->code = 212;
	response->message = ft_strdup("Directory status");
	dprintf(response->send_fd, "%d %s%s%s%s", response->code, response->message, CLRF, buffer, CLRF);

}

void	handler_get(t_command *command, t_ftp_response *response)
{
	int				fd;
	struct stat		stats;
	char			*buffer;

	(void)command;
	(void)response;
	if ((fd = open(command->args, O_RDONLY)) < 0 ||
		fstat(fd, &stats) < 0 || 
			S_ISDIR(stats.st_mode))
	{
		dprintf(1, "Handler get: file unavailable.");
		response->code = 550;
		response->message = ft_strdup("The requested file is not available.");
	}
	else
	{
		dprintf(1, "Handler get: file available");
		buffer = mmap(0, stats.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
		close(fd);	
		response->code = 200;
		response->message = ft_strdup(" The requested action has been successfully completed");
	}
	dprintf(response->send_fd, "%d, %s%s", response->code, response->message, CLRF);
	if (stats.st_size > 0)
		send(response->send_fd, buffer, stats.st_size, 0);
	send(response->send_fd, CLRF, ft_strlen(CLRF), 0);
}

void	handler_put(t_command *command, t_ftp_response *response)
{
	(void)command;
	(void)response;
}

void	handler_quit(t_command *command, t_ftp_response *response)
{
	(void)command;
	response->code = 231;
	response->message = ft_strdup("User logged out. Service terminated.");
	dprintf(response->send_fd, "%d %s%s", response->code, response->message, CLRF);
}
