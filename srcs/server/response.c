/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   response.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiboitel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/07 20:13:58 by tiboitel          #+#    #+#             */
/*   Updated: 2018/07/07 20:52:27 by tiboitel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

t_ftp_response	*ftp_response_create()
{
	t_ftp_response	*response;

	response = NULL;
	if ((response = (t_ftp_response *)malloc(sizeof(t_ftp_response))) == NULL)
		return (NULL);
	response->send_fd = 0;
	response->code = 0;
	response->message = NULL;
	return (response);
}

void			ftp_response_destroy(t_ftp_response *response)
{
	if (response == NULL)
		return ;
	if (response->message != NULL)
		free(response->message);
	response->message = NULL;
	free(response);
	response = NULL;
}
