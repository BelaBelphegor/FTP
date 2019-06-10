/*************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiboitel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/18 22:24:00 by tiboitel          #+#    #+#             */
/*   Updated: 2018/10/08 19:28:06 by tiboitel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shared.h"

t_command		*stoc(char *command)
{
	t_command	*ret;
	int			command_length;
	char		*start_args;
	int			i;

	i = 0;
	ret = NULL;
	command_length = 0;
	if (!(ret = (t_command *)ft_memalloc(sizeof(t_command))))
		return (NULL);
	if ((start_args = strchr(command, ' ')) != NULL)
	{
		start_args[0] = '\0';
		ft_strncpy(ret->name, command, ft_strlen(command));
		command = start_args + 1;
		ret->args = ft_strndup(command, ft_strlen(command) - 1);
	}
	else
	{
		ft_bzero(ret->name, 5);
		if ((command_length = ft_strlen(command)) > 5)
			command_length = 5;
		ft_strncpy(ret->name, command, command_length - 1);
		ret->args = NULL;
	}
	dprintf(1, "Name: %s, Args: %s\n", ret->name, ret->args);
	ret->id = get_command_id_by_name((const char *)ret->name);
	return (ret);
}

int		get_command_id_by_name(const char *name)
{
	size_t		i;
	size_t		count;

	count = QUIT - LS + 1;
	i = 0;
	while (i < count)
	{
		if (ft_strcmp(name, g_command_name_table[i]) == 0)
			return (i);
		i++;
	}
	return (-1);
}

void				command_callback_destroy(t_command_callback **command_callback_table)
{
	int		i;

	i = 0;
	while (i < (QUIT - LS + 1))
	{
		if (command_callback_table[i] != NULL)
			free(command_callback_table[i]);
		command_callback_table[i] = NULL;
		i++;
	}
	if (command_callback_table != NULL)
		free(command_callback_table);
	command_callback_table = NULL;
}

t_command_callback	**get_command_callback(void)
{
	static t_command_callback	**command_callback_table;

	if (command_callback_table == NULL)
		command_callback_table = command_callback_table_create();
	return (command_callback_table);
}

t_command_callback	**command_callback_table_create(void)
{
	t_command_callback	**command_callback_table;
	int					i;

	command_callback_table = NULL;
	dprintf(1, "%d\n", (int)(QUIT - LS + 1));
	if ((command_callback_table = (t_command_callback **)malloc(sizeof(t_command_callback *) * (QUIT - LS  + 2))) == NULL)
	{
			dprintf(2, "Address: %d\n", (LS - QUIT + 1));
			dprintf(2, "Unable to allocate command_callback_table.\n");
			return (NULL);
	}
	i = 0;
	while (i < (QUIT - LS + 1))
	{
		command_callback_table[i] = (t_command_callback *)malloc(sizeof(t_command_callback));
		if (command_callback_table[i] == NULL)
		{
			dprintf(1, "Unable to allocate %d callback.\n", i);
			return (NULL);
		}
		i++;
	}
	command_callback_table[i] = NULL;
	return (command_callback_table);
}
