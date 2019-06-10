/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiboitel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/22 21:32:48 by tiboitel          #+#    #+#             */
/*   Updated: 2017/08/31 19:33:28 by tiboitel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

static int	 	ft_usage(void)
{
	printf("server: illegal option --\nusage: server [port]\n");
	return (-1);
}

int				main(int argc, char **argv)
{
	size_t		i;

	i = 0;
	if (argc != 2)
		return (ft_usage());
	while (i < ft_strlen(argv[1]))
	{
		if (!ft_isdigit(argv[1][i]))
		{
			return (ft_usage());
		}
		i++;
	}
	server_start(ft_atoi(argv[1]));
	return (0);
}
