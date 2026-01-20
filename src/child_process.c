/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 10:22:36 by rcompain          #+#    #+#             */
/*   Updated: 2026/01/20 11:49:20 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"
#include <fcntl.h>

static int	test_path(t_data *pipex, char *path, char **paths, char **cmd)
{
	int		find;
	char	*tmp;

	tmp = ft_strjoin(path, "/", 0, 0);
	tmp = ft_strjoin(tmp, cmd[0], 1, 0);
	find = access(tmp, X_OK);
	if (find == FAILURE)
	{
		ft_freenull(tmp);
		return (FAILURE);
	}
	pipex->path = ft_strdup(tmp, 0);
	ft_freenull(tmp);
	if (!pipex->path)
	{
		free_array(paths);
		exit_prog(pipex, 1);
	}
	return (SUCCES);
}

static int	find_path(t_data *pipex, char **cmd)
{
	int		i;
	int		find;
	char	**paths;

	i = -1;
	find = FAILURE;
	while (pipex->envp[++i] && find == FAILURE)
	{
		if (ft_strncmp(pipex->envp[i], "PATH=", 5) == 0)
		{
			paths = ft_split(pipex->envp[i] + 5, ':');
			if (!paths)
				exit_prog(pipex, 1);
			i = 0;
			while (paths && paths[i] && find == FAILURE)
			{
				find = test_path(pipex, paths[i], paths, cmd);
				i++;
			}
			free_array(paths);
			if (find == FAILURE)
				exit_prog(pipex, 5);
		}
	}
	return (find);
}

void	child_process_last(t_data *pipex)
{
	int	find;
	int	outfile_fd;

	outfile_fd = open(pipex->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (outfile_fd < 0)
		exit_prog(pipex, 2);
	find = find_path(pipex, pipex->cmd2);
	if (find == FAILURE)
		exit_prog(pipex, 3);
	dup2(pipex->fds[0], STDIN_FILENO);
	dup2(outfile_fd, STDOUT_FILENO);
	close(outfile_fd);
	close(pipex->fds[0]);
	close(pipex->fds[1]);
	execve(pipex->path, pipex->cmd2, pipex->envp);
	exit_prog(pipex, 4);
}

void	child_process_first(t_data *pipex)
{
	int	find;
	int	infile_fd;

	infile_fd = open(pipex->infile, O_RDONLY);
	if (infile_fd < 0)
		exit_prog(pipex, 2);
	find = find_path(pipex, pipex->cmd1);
	if (find == FAILURE)
		exit_prog(pipex, 3);
	dup2(infile_fd, STDIN_FILENO);
	dup2(pipex->fds[1], STDOUT_FILENO);
	close(infile_fd);
	close(pipex->fds[0]);
	close(pipex->fds[1]);
	execve(pipex->path, pipex->cmd1, pipex->envp);
	exit_prog(pipex, 4);
}
