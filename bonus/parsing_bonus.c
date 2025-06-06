/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-petr <pde-petr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 23:06:30 by pde-petr          #+#    #+#             */
/*   Updated: 2025/04/05 19:22:51 by pde-petr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex.h"
#include "stdlib.h"
#include "unistd.h"
#include <fcntl.h>

static int	ft_check_text_arg_and_split(int ac, char **argv, t_pip *exec, int j)
{
	int	i;

	i = 1;
	while (++i < ac - 1)
	{
		exec->args[j] = ft_split(argv[i], ' ');
		if (exec->args[j] == NULL)
			return (1);
		j++;
	}
	exec->args[j] = NULL;
	if (exec->nb_pipes == -1)
		return (1);
	return (0);
}

int	ft_parsing(char **argv, int ac, t_pip *exec)
{
	int	j;

	j = 0;
	exec->infile = argv[1];
	exec->outfile = argv[ac - 1];
	exec->args = ft_calloc(((ac - 2) + 1), sizeof(char **));
	if (exec->args == NULL)
	{
		return (1);
	}
	if (ft_check_text_arg_and_split(ac, argv, exec, j) == 1)
		return (1);
	return (0);
}

int	ft_check_perm(t_pip *exec)
{
	exec->fd_infile = open(exec->infile, O_RDONLY);
	if (exec->fd_infile == -1)
	{
		perror(exec->infile);
		exec->error_first_pipe = 1;
	}
	exec->fd_outfile = open(exec->outfile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (exec->fd_outfile == -1)
	{
		perror(exec->outfile);
		exec->error_last_pipe = 1;
		if (exec->nb_pipes == 0)
			return (1);
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
	char	*text;

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
