/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-petr <pde-petr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 23:06:30 by pde-petr          #+#    #+#             */
/*   Updated: 2025/03/16 20:21:17 by pde-petr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex.h"
#include "stdlib.h"
#include "unistd.h"
#include <fcntl.h>

int	ft_parsing(char **argv, int ac, t_pip *exec)
{
	int	i;
	int	j;

	exec->infile = argv[1];
	exec->outfile = argv[ac - 1];
	i = 1;
	j = 0;
	exec->args = malloc(sizeof(char **) * ((ac - 2) + 1));
	if (exec->args == NULL)
	{
		free(exec);
		return (1);
	}
	while (++i < ac - 1)
	{
		exec->args[j] = ft_split(argv[i], ' ');
		if (exec->args[j++] == NULL)
		{
			free_tab_three_dim(exec->args);
			free(exec);
			return (1);
		}
	}
	exec->args[j] = NULL;
	return (0);
}
int	ft_check_perm(t_pip *exec)
{
	exec->fd_infile = open(exec->infile, O_RDONLY);
	if (exec->fd_infile == -1)
	{
		if (message_error_file(exec->infile, F_OK))
			perror("Crash Malloc Parsing");
		exec->fd_infile = open("/dev/null", O_RDONLY);
		if (exec->fd_infile == -1)
		{
			perror("Error opening /dev/null");
			return (1);
		}
	}
	exec->fd_outfile = open(exec->outfile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (exec->fd_outfile == -1)
	{
		if (message_error_file(exec->outfile, F_OK))
		{
			perror("Crash Malloc Parsing");
			return 1;
		}	
	}
	return (0);
}

int	ft_add_slash_to_env(t_pip *exec)
{
	char	*new_path;
	int		i;

	i = 0;
	while (exec->path_args[i])
		i++;
	while (--i >= 0)
	{
		new_path = ft_strjoin(exec->path_args[i], "/");
		if (new_path == NULL)
			return (1);
		free(exec->path_args[i]);
		exec->path_args[i] = new_path;
	}
	return (0);
}
int	ft_set_path_env(t_pip *exec, char **env)
{
	char *text;

	while (*env != NULL)
	{
		if (ft_strncmp(*env, "PATH=", 5) == 0)
		{
			text = ft_memchr(*env, '=', 5);
			text++;
			if (text == 0)
			{
				ft_printf("No path env");
				return (1);
			}
			exec->path_args = ft_split(text, ':');
			if (exec->path_args == NULL || ft_add_slash_to_env(exec) == 1)
			{
				ft_printf("Error Malloc");
				return (1);
			}
			break ;
		}
		env++;
	}
	return (0);
}