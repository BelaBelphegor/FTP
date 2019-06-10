/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shared.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiboitel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/31 16:05:44 by tiboitel          #+#    #+#             */
/*   Updated: 2018/10/11 19:58:36 by tiboitel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SHARED_H
# define FT_SHARED_H

# include <libft.h>
# include <sys/socket.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <netdb.h>
# include <stdlib.h>
# include <arpa/inet.h>
# include <stdio.h>
# include <unistd.h>
# include <signal.h>
# include <errno.h>
# include <dirent.h>
# include <fcntl.h>
# include <sys/mman.h>

# define CLRF "\r\n"
# define BUFFER_SIZE 4096
# define TRUE 1
# define FALSE 0
# define WELCOME_MSG "Hello! Welcome on FT_P Server. Love from 42 !\n"
# define FOREACH_COMMAND(C) C(LS) C(CD) C(GET)  C(PUT) C(PWD) C(QUIT)
# define GENERATE_ENUM(ENUM) ENUM,
# define GENERATE_STRING(STRING) #STRING,

typedef char	t_bool;

/*
** Better to use FOREACH_COMMAND(GENERATE_ENUM) but it's forbidden at 42 school.
*/
enum					e_command
{
	LS, CD, GET, PUT, PWD, QUIT
};

static char const		*g_command_name_table[] =
{
	FOREACH_COMMAND(GENERATE_STRING)
};

typedef struct			s_packet
{
	int					id;
	char				size;
	char				*buffer;
}						t_packet;

typedef struct			s_command
{
	int					id;
	char				name[5];
	char				*args;
}						t_command;

typedef struct			s_ftp_response
{
	int					send_fd;
	int					code;
	char				*message;
	void				*context;
}						t_ftp_response;

typedef struct			s_command_callback
{
	void (*callback)(struct s_command *, struct s_ftp_response *);
}						t_command_callback;

struct s_command		*stoc(char *command);
t_command_callback		**command_callback_table_create(void);
t_command_callback		**get_command_callback(void);
void					command_callback_destroy(t_command_callback **command_callback_table);
int						get_command_id_by_name(const char *name);
#endif
