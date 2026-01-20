/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 10:22:36 by rcompain          #+#    #+#             */
/*   Updated: 2026/01/18 11:18:04 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"
#include <fcntl.h>

static int	test_path(t_data *data, char *path, char **paths, char **cmd)
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
	data->path = ft_strdup(tmp, 0);
	ft_freenull(tmp);
	if (!data->path)
	{
		free_array(paths);
		exit_prog("ERR_MALLOC.\n");
	}
	return (SUCCES);
}

static int	find_path(t_data *data, char **cmd)
{
	int		i;
	int		find;
	char	**paths;

	i = 0;
	find = FAILURE;
	while (data->envp[i] && find == FAILURE)
	{
		if (ft_strncmp(data->envp[i], "PATH=", 5) == 0)
		{
			paths = ft_split(data->envp[i] + 5, ':');
			if (!paths)
				exit_prog("ERR_MALLOC.\n");
			i = 0;
			while (paths && paths[i] && find == FAILURE)
			{
				find = test_path(data, paths[i], paths, cmd);
				i++;
			}
			free_array(paths);
		}
		i++;
	}
	return (find);
}

void	child_process_cmd2(t_data *data)
{
	int	find;
	int	outfile_fd;

	outfile_fd = open(data->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (outfile_fd < 0)
		exit_prog("Outfile not found.\n");
	find = find_path(data, data->cmd2);
	if (find == FAILURE)
		exit_prog("Command not found.\n");
	dup2(data->fds[0], STDIN_FILENO);
	dup2(outfile_fd, STDOUT_FILENO);
	close(outfile_fd);
	close(data->fds[0]);
	close(data->fds[1]);
	write(2, data->path, ft_strlen(data->path));
	write(2, "\n", 1);
	execve(data->path, data->cmd2, data->envp);
	exit_prog("Execve Faillure cmd2.\n");
}

void	child_process_cmd1(t_data *data)
{
	int	find;
	int	infile_fd;

	infile_fd = open(data->infile, O_RDONLY);
	if (infile_fd < 0)
		exit_prog("Infile not found.\n");
	find = find_path(data, data->cmd1);
	if (find == FAILURE)
		exit_prog("Command not found.\n");
	dup2(infile_fd, STDIN_FILENO);
	dup2(data->fds[1], STDOUT_FILENO);
	close(infile_fd);
	close(data->fds[0]);
	close(data->fds[1]);
	write(2, data->path, ft_strlen(data->path));
	write(2, "\n", 1);
	execve(data->path, data->cmd1, data->envp);
	exit_prog("Execve Faillure cmd1.\n");
}
