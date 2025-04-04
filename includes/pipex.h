/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-petr <pde-petr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 15:18:44 by pde-petr          #+#    #+#             */
/*   Updated: 2025/04/04 19:23:40 by pde-petr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

typedef struct s_pip
{
	char	*infile;
	char	*outfile;
	char	***args;
	int		fd_infile;
	int		fd_outfile;
	char	**path_args;
	char	*path_absolut_exec;
	int		error_malloc_child;
	int		error;
	char	**env;
	int		nb_pipes;
	int		error_first_pipe;
	int		error_last_pipe;
}			t_pip;

int			ft_execve_first(int *fd, t_pip *exec);
int			ft_execve_last(int *fd, t_pip *exec);
void		free_tab_three_dim(char ***tab);
void		free_tab_two_dim(char **tab);
int			finish(t_pip *exec);
int			ft_parsing(char **argv, int ac, t_pip *exec);
int			ft_check_perm(t_pip *exec);
int			ft_add_slash_to_env(t_pip *exec);
int			ft_set_path_env(t_pip *exec, char **env);
int			ft_pipex(t_pip *exec);
int			main(int ac, char **argv, char **env);
int			message_error(char *first_message, char *last_message);
int			ft_execve_middle(int *fd, t_pip *exec, int exec_args, int *new_fd);
void		exec_to_env(t_pip *exec, int i, int arg_exec);
#endif