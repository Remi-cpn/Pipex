/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 10:36:24 by rcompain          #+#    #+#             */
/*   Updated: 2026/01/20 11:42:35 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

static void	init_pipex(t_data *pipex, char **av)
{
	pipex->infile = av[1];
	pipex->cmd1 = ft_split(av[2], ' ');
	pipex->cmd2 = ft_split(av[3], ' ');
	pipex->outfile = av[4];
}

int	main(int ac, char **av, char **envp)
{
	t_data	pipex;
	pid_t	pid1;
	pid_t	pid2;

	if (ac != 5)
		exit_prog(&pipex, 1);
	init_pipex(&pipex, av);
	pipex.envp = envp;
	pipe(pipex.fds);
	pid1 = fork();
	if (pid1 == CHILD)
		child_process_first(&pipex);
	waitpid(pid1, NULL, 0);
	pid2 = fork();
	if (pid2 == CHILD)
		child_process_last(&pipex);
	close(pipex.fds[0]);
	close(pipex.fds[1]);
	waitpid(pid2, NULL, 0);
	exit_prog(&pipex, SUCCES);
	return (0);
}
