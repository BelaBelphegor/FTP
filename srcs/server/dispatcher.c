/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatcher.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiboitel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/31 19:44:16 by tiboitel          #+#    #+#             */
/*   Updated: 2018/10/08 18:10:10 by tiboitel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

int		command_dispatcher(t_command *command, t_ftp_response *response)
{
	t_command_callback **command_callback_table;
	
	command_callback_table = NULL;
	if ((command_callback_table = get_command_callback()) == NULL)
	{
		dprintf(1, "Unable to allocate command_callback_table.\n");
		return (-1);
	}
	command_callback_table[LS]->callback = &handler_ls;
	command_callback_table[PWD]->callback = &handler_pwd;
	command_callback_table[CD]->callback = &handler_cd;
	command_callback_table[GET]->callback = &handler_get;
	command_callback_table[QUIT]->callback = &handler_quit;
	dprintf(1, "Start of callback dispatching\n");
	if (command->id >= 0
			&& command_callback_table[command->id] != NULL)
	{
		dprintf(1, "Calling callback id: %d\n", command->id);
		command_callback_table[command->id]->callback(command, response);
	}
	else
	{
		dprintf(1, "Unknown handler: %d\n", command->id);
		handler_command_not_found(command, response);
	}
	return (1);
}
