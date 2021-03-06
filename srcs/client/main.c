/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiboitel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/04 18:53:40 by tiboitel          #+#    #+#             */
/*   Updated: 2018/10/08 17:52:12 by tiboitel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

void		ft_usage(void)
{
	printf("Usage: client [host-name] [port]");
}

int			main(int argc, char **argv)
{
	t_ftp_client	*client;

	if (argc != 3)
	{
		ft_usage();
		return (0);
	}
	if ((client = client_create()) == NULL)
		return (-1);
	if ((client_init(client, argv[1], ft_atoi(argv[2])) < 0))
		return (-1);
	client_start(client);
	client_close(client);
	return (0);
}
