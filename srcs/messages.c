/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   messages.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-petr <pde-petr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 13:16:07 by pde-petr          #+#    #+#             */
/*   Updated: 2025/03/21 23:57:44 by pde-petr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "stdlib.h"

int	message_error(char *first_message, char *last_message)
{
	last_message = ft_strjoin(last_message, "\n");
	if (last_message == NULL)
		return (1);
	first_message = ft_strjoin(first_message, last_message);
	if (first_message == NULL)
	{
		free(last_message);
		return (1);
	}
	ft_putstr_fd(first_message, 2);
	free(last_message);
	free(first_message);
	return (0);
}

int	message_error_file(char *file, int type)
{
	char	*message;

	if (access(file, type) == 0)
	{
		file = ft_strjoin(file, "\n");
		if (file == NULL)
			return (1);
		message = ft_strjoin("Permission denied: ", file);
	}
	else
	{
		file = ft_strjoin(file, "\n");
		if (file == NULL)
			return (1);
		message = ft_strjoin("No such file or directory: ", file);
	}
	free(file);
	if (message == NULL)
		return (1);
	ft_putstr_fd(message, 2);
	free(message);
	return (0);
}
