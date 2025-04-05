/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   messages.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-petr <pde-petr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 13:16:07 by pde-petr          #+#    #+#             */
/*   Updated: 2025/04/05 17:00:19 by pde-petr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex.h"
#include "stdlib.h"

int	message_error(char *first_message, char *last_message)
{
	last_message = ft_strjoin(last_message, "\n");
	if (last_message == NULL)
	{
		perror("malloc error");
		return (1);
	}
	first_message = ft_strjoin(first_message, last_message);
	if (first_message == NULL)
	{
		free(last_message);
		perror("malloc error");
		return (1);
	}
	ft_putstr_fd(first_message, 2);
	free(last_message);
	free(first_message);
	return (0);
}

void	message_output(int statuetemp, t_pip *exec, pid_t pidvalue)
{
	int	i;

	i = 0;
	while (i < exec->nb_pipes && pidvalue != exec->pids[i])
		i++;
	if ((i == 0 && exec->error_first_pipe == 0) || (i == exec->nb_pipes && exec->error_last_pipe == 0) || (i > 0 && i < exec->nb_pipes))
	{
		if (WEXITSTATUS(statuetemp) != 0)
		{
			if (exec->args[i][0] == NULL)
				message_error("", ": Command not found");
			else if (WEXITSTATUS(statuetemp) == 126)
				message_error(exec->args[i][0], ": Permission denied");
			else
				message_error(exec->args[i][0], ": Command not found");
		}
	}
}
