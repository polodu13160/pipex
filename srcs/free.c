/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-petr <pde-petr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 23:05:46 by pde-petr          #+#    #+#             */
/*   Updated: 2025/04/05 17:04:17 by pde-petr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "stdlib.h"
#include <unistd.h>

void	free_tab_three_dim(char ***tab)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (tab[i])
	{
		j = 0;
		while (tab[i][j])
		{
			free(tab[i][j]);
			j++;
		}
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	free_tab_two_dim(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

int	finish(t_pip *exec)
{
	int	value_return;

	value_return = 0;
	if (exec->pids != NULL)
		free(exec->pids);
	if (exec->fd_infile != -1)
		close(exec->fd_infile);
	else
		value_return = 1;
	if (exec->fd_outfile != -1)
		close(exec->fd_outfile);
	else
		value_return = 1;
	if (exec->args != NULL)
		free_tab_three_dim(exec->args);
	if (exec->path_args != NULL)
		free_tab_two_dim(exec->path_args);
	if (exec->path_absolut_exec != NULL)
		free(exec->path_absolut_exec);
	if (exec->error_malloc_child == 1 || exec->error != 0)
		value_return = exec->error;
	return (value_return);
}
