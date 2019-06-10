/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiboitel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/08 23:53:22 by tiboitel          #+#    #+#             */
/*   Updated: 2018/07/09 01:22:41 by tiboitel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <server.h>

static t_bool	is_directory(char *path)
{
	t_bool		flag;
	struct stat	stat_buffer;

	flag = TRUE;
	if (stat(path, &stat_buffer) != 0)
		flag = FALSE;
	flag = S_ISDIR(stat_buffer.st_mode);
	return (flag);
}

t_bool			is_before_root(char *path, char *root_directory)
{
	t_bool		flag;
	char		*buffer;

	buffer = NULL;
	flag = FALSE;
	if ((buffer = realpath(path, buffer)) == NULL)
		return (0);
	if (strncmp(buffer, root_directory, ft_strlen(root_directory)) != 0)
		flag = TRUE;
	return (flag);
}

int				check_right_directory(char *path)
{
	if (access(path, F_OK) == -1)
	{
		// No such file or directory
		return (ENOENT);
	}
	else if (access(path, R_OK) == -1)
	{
		return (EACCES);	
	}
	else if (is_directory(path) == FALSE)
	{
		return (ENOTDIR);
	}
	return (1);
}

int				change_directory(char *path)
{
	int			flag;

	flag = 0;
	if ((flag = check_right_directory(path)) == FALSE)
		return (flag);
	if ((flag = chdir(path)) != 0)
		return (flag);
	return (0);
}
