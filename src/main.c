/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 10:36:24 by rcompain          #+#    #+#             */
/*   Updated: 2026/01/16 16:10:37 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"
#include <sys/wait.h>
#include <unistd.h>

static void	free_array(char **s)
{
	int	i;

	i = 0;
	while (s && s[i])
		ft_freenull(s[i++]);
	ft_freenull(s);
}

static char	*find_path(t_data *data)
{
	int		i;
	int		flag;
	char	**paths;
	char	*test_path;

	i = 0;
	flag = 1;
	while (data->envp[i] && flag == 1)
	{
		if (ft_strncmp(data->envp[i], "PATH=", 5) == 0)
		{
			paths = ft_split(data->envp[i] + 5, ':');
			i = 0;
			while (paths && paths[i] && flag == 1)
			{
				test_path = ft_strjoin(paths[i], "/", 0, 0);
				test_path = ft_strjoin(test_path, data->cmd1[0], 1, 0);
				flag = access(test_path, X_OK);
				if (flag == 0)
					return (test_path);
				ft_freenull(test_path);
				i++;
			}
			free_array(paths);
		}
		i++;
	}
	return (NULL);
}

static void child_process(t_data *data)
{
	char *path;

	path = find_path(data);
	if (!path)
		exit_prog("WRONG PATH");
	dup2(int fd, int fd2);
	execve(path, data->cmd1, data->envp);
}

static void	init_data(t_data *data, char **av)
{
	data->infile = av[1];
	data->cmd1 = ft_split(av[2], ' ');
	data->cmd2 = ft_split(av[3], ' ');
	data->outfile = av[4];
}

int	main(int ac, char **av, char **envp)
{
	t_data	data;
	pid_t	pid;

	if (ac != 5)
		exit_prog("ERROR Arg");
	init_data(&data, av);
	data.envp = envp;
	pipe(data.fds);
	pid = fork();
	if (pid == 0)
		 child_process(&data);
	if (waitpid(pid, NULL, 0) < 0)
		exit_prog("ERROR Waitpid Failed");
	//parent
	return (0);
}
