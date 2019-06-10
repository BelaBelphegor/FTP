/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiboitel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/09 01:42:19 by tiboitel          #+#    #+#             */
/*   Updated: 2018/10/08 17:44:46 by tiboitel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "server.h"

static void	args_free(char **args)
{
	int		i;

	i = 0;
	while (args[i] != NULL)
	{
		free(args[i]);
		args[i] = NULL;
		i++;
	}
	free(args);
	args = NULL;
}

char		*execute_with_pipe(const char *path, const char *args)
{
	int		fd[2];
	int		child_pid;
	char	buffer[4096];
	char	*output;
	char	*tmp;
	char**	args_array;

	pipe(fd);
	child_pid = fork();
	output = ft_strdup("");
	tmp = ft_strjoin("ls ", args);
	args_array = ft_strsplit(tmp, ' ');
	free(tmp);
	if (child_pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], 1);
		dup2(fd[1], 2);
		close(fd[1]);
		execv(path, args_array);
		args_free(args_array);
		exit(EXIT_FAILURE);
		return (NULL);
	}
	else
	{
		close(fd[1]);
		while (read(fd[0], buffer, sizeof(buffer) != 0))
		{
			tmp = ft_strdup(output);
			free(output);
			output = NULL;
			output = ft_strjoin(tmp, buffer);
			free(tmp);
			tmp = NULL;
			ft_bzero(buffer, 4096);
		}
	}
	return (output);
}
