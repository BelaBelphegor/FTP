/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiboitel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/05 00:24:01 by tiboitel          #+#    #+#             */
/*   Updated: 2018/07/07 21:12:26 by tiboitel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "server.h"

void	handler_command_not_found(t_command *command, t_ftp_response *response)
{
	(void)command;
	response->code = 502;
	response->message = ft_strdup("Command not implemented");
	dprintf(response->send_fd, "%d %s %s", response->code, response->message, CLRF);
}
