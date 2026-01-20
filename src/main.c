/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 10:36:24 by rcompain          #+#    #+#             */
/*   Updated: 2026/01/20 16:19:15 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"
#include <unistd.h>

static void	close_fd(t_data *pipex)
{
	int	i;

	i = 0;
	while (i < pipex->nbr_fds)
	{
		close(pipex->fds[i][0]);
		close(pipex->fds[i][1]);
		i++;
	}
}

static void	pipeline(t_data *pipex)
{
	pid_t	*pid;
	int		i;

	pid = ft_calloc(pipex->nbr_cmd, sizeof(pid_t));
	if (!pid)
		exit_prog(pipex, ERROR);
	pid[0] = fork();
	if (pid[0] == CHILD)
		child_process_first(pipex);
	i = 0;
	while (++i < pipex->nbr_cmd - 1)
	{
		pid[i] = fork();
		if (pid[i] == CHILD)
			child_process(pipex, pipex->cmd[i], i);
	}
	pid[i] = fork();
	if (pid[i] == CHILD)
		child_process_last(pipex);
	close_fd(pipex);
	i = 0;
	while (i < pipex->nbr_cmd)
		waitpid(pid[i++], NULL, 0);
}

static void	init_pipex(t_data *pipex, int ac, char **av, char **envp)
{
	int	i;

	pipex->infile = av[1];
	pipex->nbr_cmd = ac - 3;
	pipex->cmd = ft_calloc(pipex->nbr_cmd + 1, sizeof(char **));
	if (!pipex->cmd)
		exit_prog(pipex, ERROR);
	i = 0;
	while (i < pipex->nbr_cmd)
	{
		pipex->cmd[i] = ft_split(av[i + 2], ' ');
		if (!pipex->cmd[i])
			exit_prog(pipex, ERROR);
		i++;
	}
	pipex->outfile = av[ac - 1];
	pipex->envp = envp;
	pipex->nbr_fds = pipex->nbr_cmd - 1;
}

int	main(int ac, char **av, char **envp)
{
	t_data	pipex;
	int		i;

	if (ac < 5)
		exit_prog(&pipex, ERROR);
	init_pipex(&pipex, ac, av, envp);
	i = 0;
	pipex.fds = ft_calloc(pipex.nbr_fds, sizeof(int *));
	while (i < pipex.nbr_fds)
	{
		pipex.fds[i] = ft_calloc(2, sizeof(int));
		pipe(pipex.fds[i++]);
	}
	pipeline(&pipex);
	exit_prog(&pipex, SUCCES);
	return (0);
}
